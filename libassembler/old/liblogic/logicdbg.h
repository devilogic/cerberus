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
#ifndef _LOGICDBG_V_1_0_H_
#define _LOGICDBG_V_1_0_H_

/*
 * 头文件
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
 * 文件标识
 */
#define __LOGIC_DEBUG__		0xFFFFFFFF

/*
 * 宏函数定义
 */
/* 调试开关 */
#ifdef _DEBUG
#define logic_malloc(l) debug_memory_alloc((unsigned long)(l), __FILE__, __LINE__)
#define logic_free(p) debug_memory_free((void *)(p))
#define logic_leak() debug_check_leak()
#else
#define logic_malloc(l) malloc(l)
#define logic_free(p) free(p)
#define logic_leak()
#endif

/*
 * 函数声明
 */
/* 内存分配 */
void *debug_memory_alloc(unsigned long, const char *, unsigned long);
/* 内存释放 */
void debug_memory_free(void *);
/* 显示内存链 */
void debug_check_leak(void);

#endif
