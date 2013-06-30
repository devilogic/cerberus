/*
 * 介绍:堆栈操作
 * 作者:玩命
 * 开始日期:2010-4-21
 * 结束日期:2010-4-21
 *
 * 替代版本
 * 修改者:玩命
 * 开始日期:2010-6-18
 * 结束日期:2010-6-18
 * 修改部分:增加了堆栈动态增长功能,当压栈时内存耗尽
 * 函数会自动增加内存
 */
#if !defined(__STACK_H__)
#define __STACK_H__

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
#define __LOGIC_STACK__		0xFFFFFFFF

/* 
 * 调试选项
 */
//#define DEBUG_STACK		1

/*
 * 宏定义
 */
#define __DEF_MAX_STACK_SIZE__	1024

/*
 * 宏函数
 */

/*
 * 结构定义
 */
/* 栈结构定义 */
typedef struct _STACK {
	__bool auto_plus;//自动增长,当堆栈耗尽时
	__memory stack;//栈内存
	__integer i;//当前索引
	__integer size;//栈大小
} STACK, *PSTACK;

/*
 * 函数声明
 */
/* 初始化堆栈 */
PSTACK __API__ init_stack(__integer, __bool);
/* 压入 */
__memory __API__ push_stack(PSTACK, __void *, __integer);
/* 弹出 */
__memory __API__ pop_stack(PSTACK, __integer);
/* 释放堆栈内存 */
__void __API__ free_stack(PSTACK *);

#if defined(__cplusplus)
}
#endif

#endif
