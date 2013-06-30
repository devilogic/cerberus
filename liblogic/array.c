/*
 * 头文件
 */
#include "array.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 作者:玩命
 * 开始日期:2011-7-11
 * 完成日期:2010-7-11
 * 参数:
 *    size:队列长度
 *    auto_plus:是否开启自动增长,当队列用尽时
 * 返回值:
 * 说明:
 *	  初始化队列内存.
 */
PARRAY __API__ init_array(__integer size, __bool auto_plus) {
	PARRAY keep = NULL;
	__memory buffer = NULL;
	if (size == 0) size = __DEF_MAX_ARRAY_SIZE__;
	buffer = logic_malloc(size);
	keep = logic_malloc(sizeof(ARRAY));
	keep->i = 0;
	keep->j = 0;
	keep->size = __DEF_MAX_ARRAY_SIZE__;
	keep->buffer = buffer;
	keep->auto_plus = auto_plus;
	return keep;
}

/*
 * 作者:玩命
 * 开始日期:2011-7-11
 * 完成日期:2011-7-11
 * 参数:
 *    a:队列结构.
 *    v:压入数据的指针.
 *    size:要压入的长度.
 * 返回值:
 * 说明:
 *	  压入数据到栈.
 */
__memory __API__ set_array(PARRAY a, __void *v, __integer size) {
	__integer curr_size = a->i + size;
	__memory p = a->buffer + a->i;
	if (curr_size >= a->size) {
		if (a->auto_plus) {
			// 开启自动增长
			__memory tmp = logic_malloc(__DEF_MAX_ARRAY_SIZE__ + (a->size - a->j));
			__logic_memcpy__(tmp, (a->buffer + a->j), (a->size - a->j));
			logic_free(a->buffer);
			a->buffer = tmp;//新的堆栈
			a->size = __DEF_MAX_ARRAY_SIZE__;
			a->i = a->j = 0;
		} else 
			return NULL;
	}
	
	__logic_memcpy__(p, (__memory)v, size);
	a->i += size;
	return (__memory)v;
}

/*
 * 作者:玩命
 * 开始日期:2011-7-11
 * 完成日期:2011-7-11
 * 参数:
 *    a:队列结构.
 *    size:要弹出的长度.
 * 返回值:
 * 说明:
 *	  弹出数据从栈.
 */
__memory  __API__ get_array(PARRAY a, __integer size) {
	__memory v = NULL;
	__integer i = a->i, j = a->j;

	if (j + size > i) return NULL;
	v = (__memory)(a->buffer + j);
	a->j += size;//增加索引
	return v;
}

/*
 * 作者:玩命
 * 开始日期:2011-7-11
 * 完成日期:2011-7-11
 * 参数:
 *    a:队列内存指针.
 * 返回值:
 * 说明:
 *	  释放队列内存.
 */
__void __API__ free_array(PARRAY *a) {
	if ((*a)->buffer) logic_free((*a)->buffer);
	logic_free(*a);
	(*a) = NULL;
}

#if defined(__cplusplus)
}
#endif