/*
 * 头文件
 */
#include "pattern_matcher.h"
#include <math.h>

/*
 * 宏函数
 */
/* x是否小于y */
#define _mix_(x, y) (((x) < (y)) ? (x) : (y))
/* x是否大于y */
#define _max_(x, y) (((x) > (y)) ? (x) : (y))
/* 哈希值计算 */
#define _hash16_(p) ((word_t)(((*p)<<8) | *(p+1)))

/*
 * 函数声明
 */
/* BM算法生成后缀位置 */
static void bm_make_suffixes(const byte_t *, dword_t, dword_t *);
/* 对比两个内存长度 */
static dword_t bcompare(const byte_t *, dword_t, const byte_t *, dword_t);
/* 对比函数,用于qsort算法 */
static dword_t qsortcmp(const byte_t *, const byte_t *);
/* WM模式分析 */
static bool_t analyze_wm_pattern(PWM);
/* WM算法预处理,建立模式组与哈希表 */
static bool_t build_hashtbl_patgrps(PWM);
/* WM算法坏字节规则表 */
static void wm_badchar_tbl(PWM);
/* WM算法坏字规则表 */
static bool_t wm_badword_tbl(PWM);
/* WM搜索函数检查单字节 */
dword_t wm_search_normal(PWM);
/* WM搜索函数使用坏字节表 */
dword_t wm_searchex_bc(PWM);
/* WM搜索函数使用坏字表 */
dword_t wm_searchex_bw(PWM);
/* WM搜索哈希数字匹配 */
dword_t wm_group_matcher(PWM, dword_t, const byte_t *, const byte_t *, dword_t, wm_get1);
/* WM预处理 */
bool_t perp_wm_patterns(PWM);

/*
 * 函数定义
 */
/*
 * 作者:玩命
 * 开始日期:2009-7-7
 * 完成日期:2009-7-7
 * 参数:
 *    ptn:模式.
 *    ptnlen:模式长度.
 * 返回值:
 *	  成功:产生skip数组.
 *    失败:NULL.
 * 说明:
 *    BM算法生成坏字符规则.
 */
dword_t *bm_make_bc(const byte_t *ptn, dword_t ptnlen) {
	dword_t i;
	dword_t *bc = NULL;
	bc = (dword_t *)logic_malloc(sizeof(dword_t) * 0x100);
	if (!bc) return NULL;
	/* 默认移动位置为模式长度 */
	for (i = 0; i < 0x100; i++)
		bc[i] = ptnlen;
	/* 
	 * 将每个字符的重叠位置移动为最末索引与当前字符索引的差值
	 * 这样保持了算法的正确性
	 */
	for (i = 0; i < ptnlen - 1; i++)
		bc[ptn[i]] = ptnlen - 1 - i;
	return bc;
}/* end bm_make_bc */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    ptn:模式指针.
 *    ptnlen:模式长度.
 *    suffixes:长度为ptnlen + 1的数组指针.
 * 返回值:
 *	  成功:suffixes数组指针.
 *    失败:NULL.
 * 说明:
 *    BM算法生成后缀数组.
 */
static void bm_make_suffixes(const byte_t *ptn, dword_t ptnlen, dword_t *suffixes) {
	sdword_t f = 0, g = 0, i = 0;
	suffixes[ptnlen - 1] = ptnlen;
	g = ptnlen - 1;
	for (i = ptnlen - 2; i >= 0; i--) {
		if (i > g && suffixes[i + ptnlen - 1 - f] < i - g)
			suffixes[i] = suffixes[i + ptnlen - 1 - f];
		else {
			if (i < g) g = i;
			f = i;
			while(g >= 0 && ptn[g] == ptn[g + ptnlen - 1 - f]) g--;
			suffixes[i] = f - g;
		}/* end else */
	}/* end for */
}/* end bm_make_suffixes */


/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    ptn:模式指针.
 *    ptnlen:模式长度.
 * 返回值:
 *	  成功:好后缀数组指针.
 *    失败:NULL.
 * 说明:
 *    BM算法生成好后缀规则.
 */
dword_t *bm_make_gs(const byte_t *ptn, dword_t ptnlen) {
	sdword_t i = 0, j = 0;
	dword_t *suffixes = NULL, *gs = NULL;
	suffixes = (dword_t *)logic_malloc(sizeof(dword_t) * (ptnlen + 1));
	if (!suffixes) return NULL;
	gs = (dword_t *)logic_malloc(sizeof(dword_t) * (ptnlen + 1));
	if (!gs) {
		logic_free(suffixes);
		return NULL;
	}
	/* 生成后缀 */
	bm_make_suffixes(ptn, ptnlen, suffixes);
	for (i = 0; i < ptnlen; i++) gs[i] = ptnlen;
	j = 0;
	for (i = ptnlen - 1; i >= 0; i--)
		if (suffixes[i] == i + 1)
			for (; j < ptnlen - 1 - i; j++)
				if (gs[j] == ptnlen) gs[j] = ptnlen - 1 - i;

	for (i = 0; i <= ptnlen - 2; i++)
		gs[ptnlen - 1 - suffixes[i]] = ptnlen - 1 - i;
	logic_free(suffixes);
	return gs;
}/* end bm_make_gs */

/*
 * 作者:玩命
 * 开始日期:2009-7-5
 * 完成日期:2009-7-5
 * 参数:
 *    tg:要检查的内存.
 *    tglen:内存的长度.
 *    ptn:模式.
 *    ptnlen:模式长度.
 * 返回值:
 *	  找到:索引.
 *    未找到:-1.
 * 说明:
 *    BM算法的模式匹配.
 */
dword_t bm_matcher(const byte_t *tg, dword_t tglen, const byte_t *ptn, dword_t ptnlen) {
	sdword_t i = 0, j = 0;
	dword_t *bc = NULL, *gs = NULL;
	assert(tg && tglen && ptn && ptnlen);
	/* 预处理 */
	bc = bm_make_bc(ptn, ptnlen);
	if (!bc) return -1;
	gs = bm_make_gs(ptn, ptnlen);
	if (!gs) return -1;
	/* 寻找 */
	while (j <= tglen - ptnlen) {
		for (i = ptnlen - 1; i >= 0 && ptn[i] == tg[i + j]; i--);
		if (i < 0) {
			logic_free(bc);
			logic_free(gs);
			return j;
			/* j += gs[0]; */
		} else
			j += _max_(gs[i], bc[tg[i + j]] - ptnlen + 1 + i);
	}
	return -1;
}/* end bm_matcher */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    tg:要检查的内存.
 *    tglen:内存的长度.
 *    ptn:模式.
 *    ptnlen:模式长度.
 *    bc:坏字符表.
 *    gs:好后缀表.
 * 返回值:
 *	  找到:索引.
 *    未找到:-1.
 * 说明:
 *    BM算法的模式匹配.
 */
dword_t bm_matcherex(const byte_t *tg, dword_t tglen, const byte_t *ptn, dword_t ptnlen, dword_t *bc, dword_t *gs) {
	sdword_t i = 0, j = 0;
	assert(tg && tglen && ptn && ptnlen && bc && gs);
	/* 寻找 */
	while (j <= tglen - ptnlen) {
		for (i = ptnlen - 1; i >= 0 && ptn[i] == tg[i + j]; i--);
		if (i < 0) {
			return j;
			/* j += gs[0]; */
		} else
			j += _max_(gs[i], bc[tg[i + j]] - ptnlen + 1 + i);
	}
	return -1;
}/* end bm_matcherex */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 * 返回值:
 *	  成功:WM结构指针.
 *    未找到:NULL.
 * 说明:
 *    WM初始化.
 */
PWM init_wm(void) {
	PWM p = (PWM)logic_malloc(sizeof(WM));
	if (!p) return NULL;
	memset(p, 0, sizeof(WM));
	p->smallest = 0xFFFFFFFF;
	return p;
}/* end init_wm */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    pwm:指向wm的指针的指针.
 * 返回值:
 * 说明:
 *    WM释放.
 */
void free_wm(PWM *pwm) {
	PWM p = *pwm;
	PWM_PATTERN p_ptn, p_tmp;
	assert(pwm && p);
	if (p->lengths) logic_free(p->lengths);
	if (p->ptn_array) logic_free(p->ptn_array);
	if (p->group_nums) logic_free(p->group_nums);
	if (p->whash) logic_free(p->whash);
	if ((*pwm)->shift_large) logic_free(p->wshift);
	p_ptn = p->ptn_list;
	while (p_ptn) {
		p_tmp = p_ptn->next;
		if (p_ptn->ptn) logic_free(p_ptn->ptn);
		/* 释放BM结构 */
		if (p_ptn->bm_ptn) {
			logic_free(p_ptn->bm_ptn->bc);
			logic_free(p_ptn->bm_ptn->gs);
			logic_free(p_ptn->bm_ptn);
		}
		logic_free(p_ptn);
		p_ptn = p_tmp;
	}
	logic_free(p);
	*pwm = NULL;
}/* end pwm */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    wm:指向wm的指针.
 *    id:模式的id.
 *    ptn:模式指针.
 *    ptnlen:模式长度.
 * 返回值:
 *    成功:模式结构指针.
 *    失败:NULL.
 * 说明:
 *    WM增加模式.
 */
PWM_PATTERN add_wm_pattern(PWM wm, dword_t id, const byte_t *ptn, dword_t ptnlen) {
	PWM_PATTERN plist = NULL, p = NULL;
	assert(wm && ptn && ptnlen);
	/* 寻找是否模式已经加入,如果已加入则返回模式的指针 */
	for (plist = wm->ptn_list; plist; plist = plist->next)
		if (plist->ptnlen == ptnlen)
			if (memcmp(ptn, plist->ptn, ptnlen) == 0) return plist;
	/* 分配空间 */
	p = (PWM_PATTERN)logic_malloc(sizeof(WM_PATTERN));
	if (!p) return NULL;
	memset(p, 0, sizeof(WM_PATTERN));
	p->ptn = (byte_t *)logic_malloc(ptnlen);
	if (!(p->ptn)) {
		logic_free(p);
		return NULL;
	}
	p->id = id;
	memcpy(p->ptn, ptn, ptnlen);
	p->ptnlen = ptnlen;
	p->next = wm->ptn_list;
	wm->ptn_list = p;
	
	(wm->max_ptn)++;
	if (ptnlen < wm->smallest) wm->smallest = ptnlen;
	if (ptnlen > wm->largest) wm->largest = ptnlen;
	wm->total += ptnlen;
	wm->avg = wm->total / wm->max_ptn;
	return p;
}/* end add_wm_pattern */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    s1:指向要对比的指针.
 *    l1:指针长度.
 *    s2:指向要对比的指针.
 *    l2:指针长度.
 * 返回值:
 *    -1:s1 < s2.
 *    0:s1 = s2.
 *    1:s1 > s2.
 * 说明:
 *    对比两个内存长度.
 */
static dword_t bcompare(const byte_t *s1, dword_t l1, const byte_t *s2, dword_t l2) {
	dword_t stat; 
	if (l1 == l2) return memcmp(s1, s2, l1);
	else if(l1 < l2) {
		if ((stat = memcmp(s1, s2, l1))) return stat;
		return -1;
	} else {
		if ((stat = memcmp(s1, s2, l2))) return stat;
		return +1;
	}
	return stat;
}/* end bcompare */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    s1:指向要对比的指针.
 *    l1:指针长度.
 *    s2:指向要对比的指针.
 *    l2:指针长度.
 * 返回值:
 *    -1:s1 < s2.
 *    0:s1 = s2.
 *    1:s1 > s2.
 * 说明:
 *    对比函数,用于qsort算法.
 */
static dword_t qsortcmp(const byte_t *s1, const byte_t *s2) {
	PWM_PATTERN r1= (PWM_PATTERN)s1; 
	PWM_PATTERN r2= (PWM_PATTERN)s2; 
	return bcompare(r1->ptn, r1->ptnlen, r2->ptn, r2->ptnlen);
}/* end qsortcmp */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    wm:WM结构指针.
 * 返回值:
 *    成功:T.
 *    失败:F.
 * 说明:
 *    WM模式分析.
 */
static bool_t analyze_wm_pattern(PWM wm) {
	dword_t i = 0; 
	wm->lengths = (dword_t *)logic_malloc(sizeof(dword_t) * (wm->largest + 1));
	if (!wm->lengths) return F;
	memset(wm->lengths, 0, sizeof(dword_t) * (wm->largest + 1));
	/* 记录每个模式长度的个数 */
	for(i = 0; i < wm->max_ptn; i++) wm->lengths[wm->ptn_array[i].ptnlen]++;
	return T;
}/* end analyze_wm_pattern */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    wm:WM结构指针.
 * 返回值:
 *    成功:T.
 *    失败:F.
 * 说明:
 *    WM算法预处理,建立模式组与哈希表.
 */
static bool_t build_hashtbl_patgrps(PWM wm) {
	word_t sindex, hindex, ningroup;
	dword_t i;
	/* 分配4字节的哈希表 */
	wm->hash_entries = HASHTABLESIZE;
	wm->whash = (HASH_TYPE *)logic_malloc(sizeof(HASH_TYPE) * (wm->hash_entries));
	if (!wm->whash) return F;
	/* 给哈希表初始值 */
	for (i = 0; i < wm->hash_entries; i++) wm->whash[i] = (HASH_TYPE) - 1;
	/* 给字节哈希表初始值 */
	for (i = 0; i < 0x100; i++) wm->bhash[i] = (HASH_TYPE) - 1;
	/* 增加模式到哈希表 */
	for (i = 0; i < wm->max_ptn; i++) {
		if (wm->ptn_array[i].ptnlen > 1) {
			/* 取模式的前缀 */
			hindex = _hash16_(wm->ptn_array[i].ptn);  
			sindex = wm->whash[hindex] = i;
			ningroup = 1;
			/* 计算以此前缀开头的模式数量 */
			while((++i < wm->max_ptn) && (hindex == _hash16_(wm->ptn_array[i].ptn))) ningroup++;
			wm->group_nums[sindex] = ningroup;
			i--;
		} else if( wm->ptn_array[i].ptnlen == 1) {
			hindex = wm->ptn_array[i].ptn[0];
			sindex = wm->bhash[hindex] = i;
			ningroup = 1;
			/* 计算单字节的哈希表 */
			while((++i < wm->max_ptn) && (hindex == wm->ptn_array[i].ptn[0]) && (wm->ptn_array[i].ptnlen == 1)) ningroup++;
			wm->group_nums[sindex] = ningroup;
			i--;
		}/* end else if */
	}/* end for */
	return T;
}/* end build_hashtbl_patgrps */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 * 返回值:
 * 说明:
 *    WM算法坏字节规则表.
 */
static void wm_badchar_tbl(PWM wm) {
	word_t k, m, cindex, shift;
	dword_t small_value = 0xFFFFFFFF, large_value = 0, i;
	/* 决定最大长度与最小长度 */
	for (i = 0; i < wm->max_ptn; i++) {
		if (wm->ptn_array[i].ptnlen < small_value ) small_value = wm->ptn_array[i].ptnlen; 
		if (wm->ptn_array[i].ptnlen > large_value ) large_value = wm->ptn_array[i].ptnlen; 
	}/* end for */
	m = (word_t)small_value;
	if (m > 255) m = 255;
	wm->shift_len = m;

	/* 初始化移动表,最大的移动长度为256个字符 */
	for (i = 0; i < 0x100; i++) wm->bshift[i] = m;
	/* 处理坏字节移动 */
	for (i = 0; i < wm->max_ptn; i++) {
		/* 处理每个模式 */
		for (k = 0; k < m; k++) {
			shift = (m - 1 - k);
			/* 最大只允许255字节的移动 */
			if (shift > 255) shift = 255;
			cindex = wm->ptn_array[i].ptn[k];
			/* 保证不漏匹配,哪个小取哪个 */
			if (shift < wm->bshift[cindex]) wm->bshift[cindex] = shift;
		}/* end for */
	}/* end for */
}/* end wm_badchar_tbl */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 * 返回值:
 *    成功:T.
 *    失败:F.
 * 说明:
 *    WM算法坏字规则表.
 */
static bool_t wm_badword_tbl(PWM wm) { 
	word_t shift = 0, k, m, cindex;
	dword_t small_value = 0xFFFFFFFF, large_value = 0, i;

	wm->wshift = (byte_t *)logic_malloc(BWSHIFTABLESIZE * sizeof(byte_t));
	if (!wm->wshift) return F;
	/* 决定最大长度与最小长度 */
	for (i = 0; i < wm->max_ptn; i++) {
		if (wm->ptn_array[i].ptnlen < small_value ) small_value = wm->ptn_array[i].ptnlen; 
		if (wm->ptn_array[i].ptnlen > large_value ) large_value = wm->ptn_array[i].ptnlen;
	}
	/* 最大移动长度为最小模式长度,但是不能超过255 */
	m = (word_t)small_value;
	if (m > 255) m = 255;  
	wm->shift_len = m;

	/* 初始化默认表 */ 
	for (i = 0; i < BWSHIFTABLESIZE; i++) wm->wshift[i] = m - 1;

	/* 坏字移动表 */
	for (i = 0; i < wm->max_ptn; i++) {
		for (k = 0; k < m - 1; k++) {
			shift = m - 2 - k;
			/* 最大255个字节的移动 */
			if( shift > 255 ) shift = 255;
			/* 这里产生字移动表 */
			cindex = (wm->ptn_array[i].ptn[k] | (wm->ptn_array[i].ptn[k+1] << 8));
			if (shift < wm->wshift[cindex]) wm->wshift[cindex] = shift; 
		}/* end for */
	}/* end for */
	return T;
}/* end wm_badword_tbl */

/*
 * 作者:玩命
 * 开始日期:2009-7-13
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构数组.
 *    index:哈希表的哈希值.
 *    text:搜索的文本.
 *    currt:当前文本.
 *    left:离文本头的偏移.
 *    get1:输出函数.
 * 返回值:
 *    没有找完:返回找到的数目.
 *    全部找玩:找到的数目+1取负数,+1的原因为使返回的结果为负数,
 *             如果全部找玩,但是没有找到任何模式则返回-(0+1).
 * 说明:
 *    WM匹配输出函数.
 */
/* WM搜索哈希数字匹配 */
sdword_t wm_group_matcher(PWM wm, dword_t index, const byte_t *text, const byte_t *currt, dword_t left, wm_get1 get1) {
	dword_t nfound = 0;
	sdword_t k;
	PWM_PATTERN patrn, patrnEnd;
	/* 处理哈希组模式在正确的文本后缀 */
	patrn = &wm->ptn_array[index];
	patrnEnd = patrn + wm->group_nums[index];

	/* 循环匹配在组中的每个模式 */
	for (; patrn < patrnEnd; patrn++) { 
		byte_t *p, *q;
		/* 如果模式大于文本,直接忽略 */
		if (left < patrn->ptnlen) continue;

		/* 设置相反的字符串匹配 */ 
		k = patrn->ptnlen - HASHBYTES16 - 1;
		q = patrn->ptn + HASHBYTES16;      
		p = currt + HASHBYTES16;

		/* 对比字符串从后向前 */
		while (k >= 0 && (q[k] == p[k])) k--;
		/* 进行匹配 */
		if (k < 0) {
			nfound++;
			if (get1) 
				if (get1(patrn->id, (dword_t)(currt - text), patrn->ptn, patrn->ptnlen, text))
					return -(nfound + 1);
		 }/* end if */
	}/* end for */
	return nfound; 
}/* end wm_group_matcher */

/*
 * 作者:玩命
 * 开始日期:2009-7-13
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 *    text:搜索的文本.
 *    n:文本的长度.
 *    get1:输出函数.
 * 返回值:
 *    找到的模式数量.
 * 说明:
 *    WM搜索函数检查单字节.
 */
dword_t wm_search_normal(PWM wm, const byte_t *text, dword_t n, wm_get1 get1) {
	dword_t left = 0, index = 0, nfound = 0;
	sdword_t ng = 0;
	byte_t *currt, *endt, *cmpt;
	PWM_PATTERN patrn, patrnEnd;

	left = n; 
	endt = text + n;

	/* 文本长度比移动步数长度短 */
	if (n < wm->shift_len) return 0;

	/* 处理每个文本的后缀,从左向右 */
	for (currt = text, cmpt = text + wm->shift_len - 1; cmpt < endt; currt++, cmpt++, left--) {
		/* 检测单字节的模式 */
		if ((index = wm->bhash[*currt]) != (HASH_TYPE) - 1) {
			patrn = &wm->ptn_array[index];
			patrnEnd = patrn + wm->group_nums[index];

			for (; patrn < patrnEnd; patrn++) {
				nfound++;
				if (get1) 
					if (get1(wm->ptn_array[index].id, (dword_t)(currt - text), patrn->ptn, patrn->ptnlen, text))
						return nfound;
			}/* end if */
		}/* end if */
		
		/* 如果只剩一个字符则直接退出 */
		if (left == 1) return nfound;

		/* 开始2字节以上模式的寻找 */
		if ((index = wm->whash[((*currt) << 8) | *(currt + 1)]) == (HASH_TYPE) - 1) continue;
		/* 匹配这组正确的后缀 */
		ng = wm_group_matcher(wm, index, text, currt, left, get1);
		if (ng < 0) {
			ng = -ng;
			ng--;
			nfound += ng;
			return nfound; 
		} else
			nfound += ng;
	}/* end for */
	return nfound;
}/* end wm_search_normal */ 

/*
 * 作者:玩命
 * 开始日期:2009-7-13
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 *    text:搜索的文本.
 *    n:文本的长度.
 *    get1:输出函数.
 * 返回值:
 *    找到的模式数量.
 * 说明:
 *    WM搜索函数使用坏字节表.
 */
dword_t wm_searchex_bc(PWM wm, const byte_t *text, dword_t n, wm_get1 get1) {
	dword_t left, index, nfound, tshift;
	sdword_t ng; 
	byte_t *currt, *endt, *cmpt;
	nfound = 0;

	left = n;
	endt  = text + n;

	/* 如果文本小于最小移动的长度 */
	if (n < wm->shift_len) return 0;

	/* 处理每个文本的后缀 */
	for (currt = text, cmpt = text + wm->shift_len - 1; cmpt < endt; currt++, cmpt++, left--) {
		/* 使用坏字节表 */
		while ((tshift = wm->bshift[*cmpt]) > 0) {
			cmpt += tshift; currt += tshift; left -= tshift;
			if (cmpt >= endt) return nfound;

			tshift = wm->bshift[*cmpt];
			cmpt += tshift; currt += tshift; left -= tshift;
			if (cmpt >= endt) return nfound;
		}

		/* 到达最后一个字符,1字节字符的匹配已经完毕,直接返回 */
		if (left == 1) return nfound;

		/* 测试2字节前缀 */
		if ((index = wm->whash[((*currt)<<8) | *(currt+1)]) == (HASH_TYPE) - 1) continue;

		/* 匹配后缀 */ 
		ng = wm_group_matcher(wm, index, text, currt, left, get1);
		if (ng < 0) {
			ng = -ng;
			ng--;
			nfound += ng; 
			return nfound; 
		} else nfound += ng;
	}/* end for */
	return nfound; 
}/* end wm_searchex_bc */

/*
 * 作者:玩命
 * 开始日期:2009-7-13
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 *    text:搜索的文本.
 *    n:文本的长度.
 *    get1:输出函数.
 * 返回值:
 *    找到的模式数量.
 * 说明:
 *    WM搜索函数使用坏字表.
 */
dword_t wm_searchex_bw(PWM wm, const byte_t *text, dword_t n, wm_get1 get1) {
	dword_t left, index, nfound, tshift;
	sdword_t ng;
	byte_t *currt, *endt, *cmpt;
	nfound = 0;
	left = n;
	endt = text + n; 

	/* 如果文本小于最小移动的长度 */
	if (n < wm->shift_len) return 0;

	/* 处理每个文本的后缀 */ 
	for (currt = text, cmpt = text + wm->shift_len - 1; cmpt < endt; currt++, cmpt++, left--) {
		/* 使用坏字表 */
		tshift = wm->wshift[((*cmpt)<<8) | *(cmpt-1)];
		while (tshift) {
			cmpt += tshift;  currt += tshift; left -= tshift;
			if (cmpt >= endt) return nfound; 
			tshift = wm->wshift[((*cmpt)<<8) | *(cmpt-1)];
		}/* end while */
		if (left == 1) return nfound;  

		if ((index = wm->whash[((*currt)<<8 ) | *(currt+1)]) == (HASH_TYPE) - 1) continue;

		/* 匹配后缀 */
		ng = wm_group_matcher(wm, index, text, currt, left, get1);
		if (ng < 0) { 
			ng = -ng; 
			ng--;
			nfound += ng;
			return nfound; 
		} else nfound += ng;
	}/* end for */
	return nfound;
}/* end wm_searchex_bw */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-12
 * 参数:
 *    wm:WM结构指针.
 *    text:搜索的文本.
 *    n:文本的长度.
 *    get1:输出函数.
 * 返回值:
 *    成功:T.
 *    失败:F.
 * 说明:
 *    WM预处理.
 */
bool_t perp_wm_patterns(PWM wm) {
	dword_t i;
	PWM_PATTERN plist;
	assert(wm);

	/* 生成指向模式队列指针的数组 */
	wm->ptn_array = (PWM_PATTERN)logic_malloc(sizeof(WM_PATTERN) * (wm->max_ptn));
	if (!wm->ptn_array) return F;
	/* 生成记录哈希表入口数量的队列 */
	wm->group_nums = (dword_t *)logic_malloc(sizeof(dword_t) * (wm->max_ptn));
	if (!wm->group_nums) {
		logic_free(wm->ptn_array);
		return F;
	}
	/* 复制列表节点到队列 */
	for (i = 0, plist = wm->ptn_list; plist && i < wm->max_ptn; plist = plist->next)
		memcpy(&(wm->ptn_array[i++]), plist, sizeof(WM_PATTERN));

	/* 分析模式 */
	if (!analyze_wm_pattern(wm)) {
		logic_free(wm->ptn_array);
		logic_free(wm->group_nums);
		return F;
	}

	/* 给模式排序 */ 
	qsort(wm->ptn_array, wm->max_ptn, sizeof(WM_PATTERN), qsortcmp); 

	/* 构建哈希表,模式组,预处理Wu - Manber算法 */
	if (!build_hashtbl_patgrps(wm)) {
		logic_free(wm->ptn_array);
		logic_free(wm->group_nums);
		logic_free(wm->lengths);
		return F;
	}/* end if */
	
	/* 选择匹配算法 */
	if (wm->max_ptn < 5) wm->method = LPM_BM;
	else wm->method = LPM_WM;

	/* 建立Wu-Manber算法 */
	if (wm->method == LPM_WM) {
		/* 构建坏字节符规则表 */
		wm_badchar_tbl(wm); 
		/* 构建坏字规则表 */
		if ((wm->shift_len > 1) && wm->shift_large)
			wm_badword_tbl(wm);

		/* 模式移动为1个字节 */
		if( wm->shift_len == 1) wm->search = wm_search_normal;
		/* 最小的模式 > 1字节 */ 
		else if((wm->shift_len > 1) && !wm->shift_large) wm->search = wm_searchex_bc;
		/* 最小的模式 > 1字节 - 我们询问是否使用字移动代替 */ 
		else if((wm->shift_len >  1) && wm->shift_large && wm->wshift) wm->search = wm_searchex_bw;
		/* 最小的模式 > 1字节 */
		else wm->search = wm_search_normal;
	}/* end if */

	/* 初始化BM算法数据 */
	if (wm->method == LPM_BM) {
		dword_t k;
		/* 分配并构建每个模式的坏字符表与好后缀表 */
		for (k = 0; k < wm->max_ptn; k++) {
			wm->ptn_array[k].bm_ptn = (PBM_PATTERN)logic_malloc(sizeof(BM_PATTERN));
			if (!wm->ptn_array[k].bm_ptn) {
				logic_free(wm->ptn_array);
				logic_free(wm->group_nums);
				logic_free(wm->lengths);
				return F;
			}
			wm->ptn_array[k].bm_ptn->bc = bm_make_bc(wm->ptn_array[k].ptn, wm->ptn_array[k].ptnlen);
			wm->ptn_array[k].bm_ptn->gs = bm_make_gs(wm->ptn_array[k].ptn, wm->ptn_array[k].ptnlen);
		}/* end for */
	}/* end if */
	return T;
}/* end perp_wm_patterns */

/*
 * 作者:玩命
 * 开始日期:2009-7-12
 * 完成日期:2009-7-19
 * 参数:
 *    wm:WM结构指针.
 * 返回值:
 *    成功:返回找到的个数.
 *    失败:-1.
 * 说明:
 *    WM匹配.
 */
dword_t wm_matcher(PWM wm, const byte_t * text, dword_t n, wm_get1 get1) {
	assert(wm && text && n);
	/* 这里做预处理 */
	if (!perp_wm_patterns(wm)) {
		free_wm(&wm);
		return -1;
	}
	/* 如果是BM算法 */
	if (wm->method == LPM_BM) {
		dword_t i, j, nfound = 0;
		PBM_PATTERN p = NULL;
		for (i = 0; i < wm->max_ptn; i++) {
			p = wm->ptn_array[i].bm_ptn;
			j = bm_matcherex(text, n, wm->ptn_array[i].ptn, wm->ptn_array[i].ptnlen, p->bc, p->gs);
			/* 找到 */
			if (j != -1) {
				nfound++;
				if (get1) get1(wm->ptn_array[i].id, j, wm->ptn_array[i].ptn, wm->ptn_array[i].ptnlen, text);
			}/* end if */
		}
		return nfound;
	} else return wm->search(wm, text, n, get1);
}/* end wm_matcher */
