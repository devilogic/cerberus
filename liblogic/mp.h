/*
 * 介绍:多倍精度乘法
 * 作者:玩命
 * 开始日期:2011-7-28
 * 结束日期:2011-7-28
 *
 */
//#if !defined(__MP_H__)
//#define __MP_H__

///*
// * 头文件
// */
//#include "headfile.h"
//
//#if defined(__cplusplus)
//extern "C"
//{
//#endif
//
///*
// * 文件标识
// */
//#define __LOGIC_MP__		0xFFFFFFFF
//
///* 
// * 调试选项
// */
////#define DEBUG_MP		1
//
///*
// * 宏定义
// */
///* 默认哈希树种子数量 */
//#define MAX_MP_NUMBER				32
///* 默认哈希树种子数量 */
//#define MP_RADIX					4294967296.0//0x100000000
///* 正数 */
//#define POSITIVE					0
///* 负数 */
//#define NEGATIVE					1
//
///*
// * 宏函数
// */
///* 数等于0 */
//#define _mp_is_zero_(a) ((a)->n == 0)
///* 数等于1 */
//#define _mp_is_one_(a) ((a)->n == 1 && (a)->v[0] == 1)
//
///*
// * 函数结构声明
// */
//
//
///*
// * 结构定义
// */
///* 多精度倍乘结构 */
//typedef struct _MP_TYPE{
//	/* 这个结构有多少个数字 */
//	__integer n;
//	/* 结构的数值 */
//	__dword v[MAX_MP_NUMBER];
//} MP_TYPE, *PMP_TYPE;
//
///* 更大的多精度倍乘结构 */
//typedef struct _EX_MP_TYPE{
//	/* 这个结构有多少个数字 */
//	__integer n;
//	/* 结构的数值 */
//	__dword v[2 * MAX_MP_NUMBER];
//} EX_MP_TYPE, *PEX_MP_TYPE;
//
///* 带符号的多精度倍乘结构 */
//typedef struct _SIGNED_MP_TYPE {
//	/* 符号位 */
//	__byte sign;
//	/* 数值 */
//	MP_TYPE num;
//} SIGNED_MP_TYPE, *PSIGNED_MP_TYPE;
//
///* 带符号的更大多精度倍乘结构 */
//typedef struct _SIGNED_MP_TYPE {
//	/* 符号位 */
//	__byte sign;
//	/* 数值 */
//	EX_MP_TYPE num;
//} SIGNED_MP_TYPE, *PSIGNED_MP_TYPE;
//
///*
// * 函数声明
// */
///* 清空MP结构 */
//__void __API__ mp_clear(PMP_TYPE);
///* 清空带标记的MP结构 */
//__void __API__ signed_mp_clear(PSIGNED_MP_TYPE);
///* 复制MP结构 */
//__void __API__ mp_copy(PMP_TYPE, PMP_TYPE);
///* 复制符号MP结构 */
//__void __API__ signed_mp_copy(PSIGNED_MP_TYPE, PSIGNED_MP_TYPE);
///* 计算MP结构的位数 */
//__integer __API__ mp_bits(PMP_TYPE);
///* 计算以e为底以MP为顶的对数值 */
//__double __API__ mp_e_log(PMP_TYPE);
///* 计算MP结构加上MP结构 */
//__void __API__ mp_add_mp(PMP_TYPE, PMP_TYPE, PMP_TYPE);
///* 计算MP结构加上一个数字 */
//__void __API__ mp_add_integer(PMP_TYPE, __integer, PMP_TYPE);
///* 计算MP结构减去MP结构 */
//__void __API__ mp_sub_mp(PMP_TYPE, PMP_TYPE, PMP_TYPE);
///* 计算MP结构减去一个数字 */
//__void __API__ mp_sub_integer(PMP_TYPE, __integer, PMP_TYPE);
///* 带符号位MP结构加法 */
//__void __API__ signed_mp_add(PSIGNED_MP_TYPE, PSIGNED_MP_TYPE, PSIGNED_MP_TYPE);
///* 带符号位MP结构减法 */
//__void __API__ signed_mp_sub(PSIGNED_MP_TYPE, PSIGNED_MP_TYPE, PSIGNED_MP_TYPE);
///* 将MP数值右移n位,最大移动位数为32 * MAX_MP_NUMBER */
//__void __API__ mp_rshift(PMP_TYPE, __integer, PMP_TYPE);

//#if defined(__cplusplus)
//}
//#endif
//
//#endif