/*
 * 介绍:二叉哈希树
 * 作者:玩命
 * 开始日期:2008-6-13
 * 结束日期:2009-6-13
 *
 * 替代版本2
 * 修改者:玩命
 * 开始日期:2009-12-24
 * 结束日期:2009-12-24
 * 修改部分:增加了哈希树节点值属性,并且增加了释放时所用的回调函数
 *
 * 替代版本
 * 修改者:玩命
 * 开始日期:2008-12-29
 * 结束日期:2009-1-8
 * 修改部分:增加了哈系树转换链表的函数,修改了删除函数
 *
 */
#if !defined(__HASHTREE_H__)
#define __HASHTREE_H__

/*
 * 头文件
 */
#include "headfile.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 文件标识
 */
#define __LOGIC_HASHTREE__		0xFFFFFFFF

/* 
 * 调试选项
 */
//#define DEBUG_HASHTREE		1

/*
 * 宏定义
 */
/* 默认哈希树种子数量 */
#ifdef DEBUG_HASHTREE
#define DEF_HASHTREE_PRIME				0x01
#else
#define DEF_HASHTREE_PRIME				0x05
#endif

/*
 * 宏函数
 */
/* 复制节点 */
#define _copy_node_hashtree_(d, s)	__logic_memcpy__(d, s, sizeof(HASHTREE_NODE))
/* 清空节点 */
#define _clean_node_hashtree_(d)	__logic_memset__(d, 0, sizeof(HASHTREE_NODE))
/* 释放值 */
#define _free_value_hashnode_(d)\
	if ((d)->value) {\
		if ((d)->free_value) (d)->free_value((d)->value);\
		else logic_free((d)->value);\
	(d)->value = NULL;}

/*
 * 函数结构声明
 */
typedef __void (__INTERNAL_FUNC__ *FPHashNodeValueFreeCallBack)(__memory);

/*
 * 结构定义
 */
/* 哈希节点名字长度 */
#define HASHTREE_NODE_NAME_SIZE		512
/* 哈希树节点 */
typedef struct _HASHTREE_NODE {
	/* 节点是否为空 */
	__bool empty;
	/* 节点名 */
	__byte *name;
	/* 节点名长度 */
	__integer name_len;
	/* 值内存指针 */
	__memory value;
	/* 释放值回调函数 */
	FPHashNodeValueFreeCallBack free_value;
	/* 父节点 */
	struct _HASHTREE_NODE *parents;
	/* 左节点 */
	struct _HASHTREE_NODE *left;
	/* 右节点 */
	struct _HASHTREE_NODE *right;
} HASHTREE_NODE, *PHASHTREE_NODE;

/* 哈希树 */
typedef struct _HASHTREE {
	/* 哈希树根节点数量 */
	__integer prime;
	/* 哈希节点集合 */
	PHASHTREE_NODE node_set;
	/* 节点数量 */
	__integer node_count;
	/* 释放节点值函数 */
	FPHashNodeValueFreeCallBack free_value;
} HASHTREE, *PHASHTREE;

/* 哈希树链表 */
typedef struct _HASHLIST_NODE {
	/* 哈希节点 */
	PHASHTREE_NODE hashnode;
	/* 下一个节点 */
	struct _HASHLIST_NODE *next;
} HASHLIST_NODE, *PHASHLIST_NODE;

/*
 * 函数声明
 */
/* 初始化哈希树 */
PHASHTREE __API__ init_hashtree(__integer, FPHashNodeValueFreeCallBack);
/* 释放哈希树 */
__void __API__ free_hashtree(PHASHTREE *);
/* 增加一个节点到树 */
PHASHTREE_NODE __API__ add_node_hashtree(PHASHTREE, __byte *, __integer, __memory);
/* 查询节点 */
PHASHTREE_NODE __API__ query_node_hashtree(PHASHTREE, __byte *, __integer);
/* 删除节点 */
__bool __API__ del_node_hashtree(PHASHTREE, __byte *, __integer);
/* 计算哈希树节点 */
__integer __API__ count_node_hashtree(PHASHTREE);
/* 哈希树转换链表 */
PHASHLIST_NODE __API__ hashtree_2_linkedlist(PHASHTREE);
/* 释放哈希树链表 */
__void __API__ free_hashtree_linkedlist(PHASHLIST_NODE *);

#if defined(__cplusplus)
}
#endif

#endif
