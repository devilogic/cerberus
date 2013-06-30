/*
 * 介绍:调试信息输出
 * 作者:玩命
 * 开始日期:2009-6-13
 * 结束日期:2008-6-13
 * 
 * 替代版本
 * 修改者:玩命
 * 开始日期:2008-12-29
 * 结束日期:2008-12-29
 * 修改部分:增加了调试所用的内存分配函数,用于记录
 * 内存泄漏
 *
 */
#if !defined(__LOGICDBG_H__)
#define __LOGICDBG_H__

/*
 * 头文件
 */
#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 文件标识
 */
#define __LOGIC_DEBUG__		0xFFFFFFFF

/*
 * 宏函数定义
 */
/* 调试开关 */
#ifdef _DEBUG
#define logic_malloc(l) debug_memory_alloc((__integer)(l), __FILE__, __LINE__)
#define logic_free(p) debug_memory_free((__memory)(p))
#define logic_leak() debug_check_leak()
#else
#define logic_malloc(l) __logic_new_size__(l)
#define logic_free(p) __logic_delete__(p)
#define logic_leak()
#endif

/*
 * 函数声明
 */
/* 内存分配 */
__memory __INTERNAL_FUNC__ debug_memory_alloc(__integer, const __memory, __integer);
/* 内存释放 */
__void __INTERNAL_FUNC__ debug_memory_free(__memory);
/* 显示内存链 */
__void __INTERNAL_FUNC__ debug_check_leak(__void);

#if defined(__cplusplus)
}
#endif

#endif
