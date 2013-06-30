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
#ifndef _HASHTREE_V_1_0_H_
#define _HASHTREE_V_1_0_H_

/*
 * 头文件
 */
#include "headfile.h"

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
#define _copy_node_hashtree_(d, s) memcpy(d, s, sizeof(HASHTREE_NODE))
/* 清空节点 */
#define _clean_node_hashtree_(d) memset(d, 0, sizeof(HASHTREE_NODE))
/* 释放值 */
#define _free_value_hashnode_(d)\
	if ((d)->value) {\
		if ((d)->free_value) (d)->free_value((d)->value);\
		else logic_free((d)->value);\
	(d)->value = NULL;}

/*
 * 函数结构声明
 */
typedef void (__cdecl *FPHashNodeValueFreeCallBack)(void *);

/*
 * 结构定义
 */
/* 哈希节点名字长度 */
#define HASHTREE_NODE_NAME_SIZE		512
/* 哈希树节点 */
typedef struct _HASHTREE_NODE {
	/* 节点是否为空 */
	bool_t empty;
	/* 节点名 */
	byte_t *name;
	/* 节点名长度 */
	dword_t name_len;
	/* 值内存指针 */
	void *value;
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
	dword_t prime;
	/* 哈希节点集合 */
	PHASHTREE_NODE node_set;
	/* 节点数量 */
	dword_t node_count;
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
PHASHTREE init_hashtree(dword_t, FPHashNodeValueFreeCallBack);
/* 释放哈希树 */
void free_hashtree(PHASHTREE *);
/* 增加一个节点到树 */
PHASHTREE_NODE add_node_hashtree(PHASHTREE, byte_t *, dword_t, void *);
/* 查询节点 */
PHASHTREE_NODE query_node_hashtree(PHASHTREE, byte_t *, dword_t);
/* 删除节点 */
bool_t del_node_hashtree(PHASHTREE, byte_t *, dword_t);
/* 计算哈希树节点 */
dword_t count_node_hashtree(PHASHTREE);
/* 哈希树转换链表 */
PHASHLIST_NODE hashtree_2_linkedlist(PHASHTREE);
/* 释放哈希树链表 */
void free_hashtree_linkedlist(PHASHLIST_NODE *);

#endif
