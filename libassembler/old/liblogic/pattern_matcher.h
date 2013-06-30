/*
 * 定义:模式匹配算法.
 * 作者:玩命
 * 开始日期:2009-7-5
 * 结束日期:2009-7-19
 * 
 * 替代版本
 * 修改者:-
 * 开始日期:-
 * 结束日期:-
 * 修改部分:-
 *
 */
#ifndef _PATTERN_MATCHER_V_1_0_H_
#define _PATTERN_MATCHER_V_1_0_H_
/*
 * 头文件
 */
#include "headfile.h"
#include "hashtree.h"

/* 
 * 文件标识
 */
#define __LOGIC_PATTERN_MATCHER__		0xFFFFFFFF

/* 
 * 调试选项
 */
//#define DEBUG_PATTERN_MATCHER		1

/*
 * 宏定义
 */
/* BM算法 */
#define LPM_BM					0x01
/* WM算法 */
#define LPM_WM					0x02
/* 哈希表类型 */
#define HASH_TYPE				word_t
/* 移动表长度 */
#define BWSHIFTABLESIZE			(64*1024)
/* 哈希表长度 */
#define HASHTABLESIZE			BWSHIFTABLESIZE
/* 哈希字节长度 */
#define HASHBYTES16				2

/*
 * 函数类型指针
 */
/* 输出函数 */
/* 1:模式ID,2:偏移,3:模式,4:模式长度,5:文本指针 */
/* 返回T:找到一个直接返回,返回F:继续搜索直到全部文本搜索完毕 */
typedef bool_t (*wm_get1)(dword_t, dword_t, const byte_t *, dword_t, const byte_t *);

/*
 * 结构定义
 */
/* BM模式结构 */
typedef struct _BM_PATTERN {
	/* 坏字符数组 */
	dword_t *bc;
	/* 好后缀数组 */
	dword_t *gs;
} BM_PATTERN, *PBM_PATTERN;

/* WM模式结构 */
typedef struct _WM_PATTERN {
	/* 下一个模式 */
	struct _WM_PATTERN *next;
	/* 模式的ID */
	dword_t id;
	/* 模式 */
	byte_t *ptn;
	/* 模式长度 */
	dword_t ptnlen;
	/* BM模式 */
	PBM_PATTERN bm_ptn;
} WM_PATTERN, *PWM_PATTERN;

/* WM结构 */
typedef struct _WM {
	/* 方法 */
	dword_t method;
	/* 模式链表 */
	PWM_PATTERN ptn_list;
	/* 模式的数量 */
	dword_t max_ptn;
	/* 模式队列 */
	PWM_PATTERN ptn_array;
	/* 哈希表每组的数量 */
	dword_t *group_nums;
	/* 字哈希表节点数量 */
	dword_t hash_entries;
	/* 字节哈希表*/
	HASH_TYPE bhash[0x100];
	/* 字哈希表 */
	HASH_TYPE *whash;
	/* 记录不同长度模式的个数 */
	dword_t *lengths;
	/* 单字节移动表 */
	word_t bshift[0x100];
	/* 字移动表 */
	byte_t *wshift;
	/* 移动表移动的长度 */
	word_t shift_len;
	/* 使用宽移动算法 */
	bool_t shift_large;
	/* 所有模式中最小的长度 */
	dword_t smallest;
	/* 所有模式中最大的长度 */
	dword_t largest;
	/* 所有模式中长度的平均值 */
	dword_t avg;
	/* 所有模式总长度 */
	dword_t total;
	/* 搜索算法 */
	dword_t (*search)(struct _WM *, const byte_t *, dword_t, wm_get1);
} WM, *PWM;

/*
 * 函数声明
 */
/* BM算法生成坏字符规则 */
dword_t *bm_make_bc(const byte_t *, dword_t);
/* BM算法生成好后缀规则 */
dword_t *bm_make_gs(const byte_t *, dword_t);
/* BM算法匹配 */
dword_t bm_matcher(const byte_t *, dword_t, const byte_t *, dword_t);
/* BM算法匹配 */
dword_t bm_matcherex(const byte_t *, dword_t, const byte_t *, dword_t, dword_t *, dword_t *);
/* WM初始化 */
PWM init_wm(void);
/* WM释放 */
void free_wm(PWM *);
/* WM增加模式 */
PWM_PATTERN add_wm_pattern(PWM, dword_t, const byte_t *, dword_t);
/* WM匹配 */
dword_t wm_matcher(PWM, const byte_t *, dword_t, wm_get1);

#endif