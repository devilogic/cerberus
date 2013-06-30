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
#if !defined(__PATTERN_MATCHER_H__)
#define __PATTERN_MATCHER_H__
/*
 * 头文件
 */
#include "headfile.h"
#include "hashtree.h"

#if defined(__cplusplus)
extern "C"
{
#endif

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
#define HASH_TYPE				__word
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
typedef __bool (__API__ *wm_get1)(__integer, __integer, const __byte *, __integer, const __byte *);

/*
 * 结构定义
 */
/* BM模式结构 */
typedef struct _BM_PATTERN {
	/* 坏字符数组 */
	__integer *bc;
	/* 好后缀数组 */
	__integer *gs;
} BM_PATTERN, *PBM_PATTERN;

/* WM模式结构 */
typedef struct _WM_PATTERN {
	/* 下一个模式 */
	struct _WM_PATTERN *next;
	/* 模式的ID */
	__integer id;
	/* 模式 */
	__byte *ptn;
	/* 模式长度 */
	__integer ptnlen;
	/* BM模式 */
	PBM_PATTERN bm_ptn;
} WM_PATTERN, *PWM_PATTERN;

/* WM结构 */
typedef struct _WM {
	/* 方法 */
	__integer method;
	/* 模式链表 */
	PWM_PATTERN ptn_list;
	/* 模式的数量 */
	__integer max_ptn;
	/* 模式队列 */
	PWM_PATTERN ptn_array;
	/* 哈希表每组的数量 */
	__integer *group_nums;
	/* 字哈希表节点数量 */
	__integer hash_entries;
	/* 字节哈希表*/
	HASH_TYPE bhash[0x100];
	/* 字哈希表 */
	HASH_TYPE *whash;
	/* 记录不同长度模式的个数 */
	__integer *lengths;
	/* 单字节移动表 */
	__word bshift[0x100];
	/* 字移动表 */
	__byte *wshift;
	/* 移动表移动的长度 */
	__word shift_len;
	/* 使用宽移动算法 */
	__bool shift_large;
	/* 所有模式中最小的长度 */
	__integer smallest;
	/* 所有模式中最大的长度 */
	__integer largest;
	/* 所有模式中长度的平均值 */
	__integer avg;
	/* 所有模式总长度 */
	__integer total;
	/* 搜索算法 */
	__integer (__INTERNAL_FUNC__ *search)(struct _WM *, const __byte *, __integer, wm_get1);
} WM, *PWM;

/*
 * 函数声明
 */
/* BM算法生成坏字符规则 */
__integer * __API__ bm_make_bc(const __byte *, __integer);
/* BM算法生成好后缀规则 */
__integer * __API__ bm_make_gs(const __byte *, __integer);
/* BM算法匹配 */
__integer __API__ bm_matcher(const __byte *, __integer, const __byte *, __integer);
/* BM算法匹配 */
__integer __API__ bm_matcherex(const __byte *, __integer, const __byte *, __integer, __integer *, __integer *);
/* WM初始化 */
PWM __API__ init_wm(__void);
/* WM释放 */
__void __API__ free_wm(PWM *);
/* WM增加模式 */
PWM_PATTERN __API__ add_wm_pattern(PWM, __integer, const __byte *, __integer);
/* WM匹配 */
__integer __API__ wm_matcher(PWM, const __byte *, __integer, wm_get1);

#if defined(__cplusplus)
}
#endif

#endif
