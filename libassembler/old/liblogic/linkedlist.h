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
#ifndef _LINKEDLIST_V_1_0_H_
#define _LINKEDLIST_V_1_0_H_
/*
 * 头文件
 */
#include "headfile.h"

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
#define _copy_linkedlist_node_(d, s) memcpy(d, s, sizeof(LINKEDLIST_NODE))
/* 清空一个链表节点 */
#define _clean_linkedlist_node_(d) memset(d, 0, sizeof(LINKEDLIST_NODE))

/*
 * 函数声明
 */
/* 初始化一个链表 */
PLINKEDLIST_NODE init_linkedlist(dword_t);
/* 删除一个链表 */
void free_linkedlist(PLINKEDLIST_NODE *);
/* 在某个位置添加一个节点 */
PLINKEDLIST_NODE add_node_linkedlist(PLINKEDLIST_NODE, PLINKEDLIST_NODE, dword_t);
/* 删除某个位置上的节点 */
bool_t del_node_linkedlist(PLINKEDLIST_NODE *, dword_t);
/* 获取某位置的节点 */
PLINKEDLIST_NODE query_node_linkedlist(PLINKEDLIST_NODE, dword_t);
/* 获取链表节点数 */
dword_t get_count_linkedlist(PLINKEDLIST_NODE);
/* 在末尾添加一个节点 */
void add_node_tail_linkedlist(PLINKEDLIST_NODE, PLINKEDLIST_NODE);

#endif
