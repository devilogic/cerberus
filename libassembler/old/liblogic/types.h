/*
* 定义自己的类型
* 作者:玩命
* 开始日期:2009-6-13
* 结束日期:2008-6-13
* 
* 替代版本
* 修改者:玩命
* 开始日期:2008-12-29
* 结束日期:2008-12-29
* 修改部分:增加了指针类型
*
*/
#ifndef _TYPE_V_1_0_H_
#define _TYPE_V_1_0_H_
/*
 * 布尔值
 */
/* 真 */
#define T 0x01
/* 假 */
#define F 0x00

/*
 * 数据类型
 */
/* 布尔型 */
typedef unsigned char bool_t;
/* 无符号型 */
typedef unsigned char byte_t;
typedef unsigned short word_t;
typedef unsigned long dword_t;
typedef unsigned float f16_t;
typedef unsigned double f32_t;

/* 有符号型 */
typedef signed char sbyte_t;
typedef signed short sword_t;
typedef signed long sdword_t;
typedef signed float sf16_t;
typedef signed double sf32_t;


#endif
