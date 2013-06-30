/*
 * 介绍:队列操作
 * 作者:玩命
 * 开始日期:2011-7-11
 * 结束日期:2011-7-11
 *
 */
#if !defined(__ARRAY_H__)
#define __ARRAY_H__

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
#define __DEF_MAX_ARRAY_SIZE__	1024

/*
 * 宏函数
 */

/*
 * 结构定义
 */
/* 队列结构定义 */
typedef struct _ARRAY {
	__bool auto_plus;//自动增长,当队列耗尽时
	__memory buffer;//队列内存
	__integer i;//当前索引
	__integer j;//取值的索引
	__integer size;//队列大小
} ARRAY, *PARRAY;

/*
 * 函数声明
 */
/* 初始化队列 */
PARRAY __API__ init_array(__integer, __bool);
/* 压入 */
__memory __API__ set_array(PARRAY, __void *, __integer);
/* 弹出 */
__memory __API__ get_array(PARRAY, __integer);
/* 释放队列内存 */
__void __API__ free_array(PARRAY *);

#if defined(__cplusplus)
}
#endif

#endif
