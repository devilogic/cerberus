/*
 * 介绍:线性表
 * 作者:玩命
 * 开始日期:2009-1-1
 * 结束日期:2009-1-1
 * 
 * 替代版本
 * 修改者:-
 * 开始日期:-
 * 结束日期:-
 * 修改部分:-
 *
 */
#if !defined(__LINKEDLIST_H__)
#define __LINKEDLIST_H__

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
#define __LOGIC_LINKEDLIST__		0xFFFFFFFF

/*
 * 调试选项
 */
//#define DEBUG_LINKEDLIST		1

/*
 * 结构定义
 */
/* 链表节点 */
typedef struct _LINKEDLIST_NODE {
	/* 上一个节点 */
	struct _LINKEDLIST_NODE *previous;
	/* 下一个节点 */
	struct _LINKEDLIST_NODE *next;
} LINKEDLIST_NODE, *PLINKEDLIST_NODE;

/*
 * 宏函数定义
 */
/* 创建一个链表节点 */
#define _create_linkedlist_node_(p_linkedlist_node) {\
	p_linkedlist_node = (PLINKEDLIST_NODE)logic_malloc(sizeof(LINKEDLIST_NODE));\
	p_linkedlist_node->previous = NULL;\
	p_linkedlist_node->next = NULL;\
}
/* 复制一个链表节点 */
#define _copy_linkedlist_node_(d, s) __logic_memcpy__(d, s, sizeof(LINKEDLIST_NODE))
/* 清空一个链表节点 */
#define _clean_linkedlist_node_(d) __logic_memset__(d, 0, sizeof(LINKEDLIST_NODE))

/*
 * 函数声明
 */
/* 初始化一个链表 */
PLINKEDLIST_NODE __API__ init_linkedlist(__integer);
/* 删除一个链表 */
__void __API__ free_linkedlist(PLINKEDLIST_NODE *);
/* 在某个位置添加一个节点 */
PLINKEDLIST_NODE __API__ add_node_linkedlist(PLINKEDLIST_NODE, PLINKEDLIST_NODE, __integer);
/* 删除某个位置上的节点 */
__bool __API__ del_node_linkedlist(PLINKEDLIST_NODE *, __integer);
/* 获取某位置的节点 */
PLINKEDLIST_NODE __API__ query_node_linkedlist(PLINKEDLIST_NODE, __integer);
/* 获取链表节点数 */
__integer __API__ get_count_linkedlist(PLINKEDLIST_NODE);
/* 在末尾添加一个节点 */
__void __API__ add_node_tail_linkedlist(PLINKEDLIST_NODE, PLINKEDLIST_NODE);

#if defined(__cplusplus)
}
#endif

#endif
