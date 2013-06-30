/*
 * 头文件
 */
#include "stack.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 作者:玩命
 * 开始日期:2010-4-21
 * 完成日期:2010-4-21
 * 参数:
 *    size:堆栈长度
 *    auto_plus:是否开启自动增长,当堆栈用尽时
 * 返回值:
 * 说明:
 *	  初始化栈内存.
 */
PSTACK __API__ init_stack(__integer size, __bool auto_plus) {
	PSTACK keep = NULL;
	__memory stack = NULL;
	if (size == 0) size = __DEF_MAX_STACK_SIZE__;
	stack = logic_malloc(size);
	keep = logic_malloc(sizeof(STACK));
	keep->i = 0;
	keep->size = __DEF_MAX_STACK_SIZE__;
	keep->stack = stack;
	keep->auto_plus = auto_plus;
	return keep;
}

/*
 * 作者:玩命
 * 开始日期:2010-4-21
 * 完成日期:2010-4-21
 * 参数:
 *    stack:堆栈结构.
 *    v:压入数据的指针.
 *    size:要压入的长度.
 * 返回值:
 * 说明:
 *	  压入数据到栈.
 */
__memory __API__ push_stack(PSTACK stack, __void *v, __integer size) {
	__integer curr_size = stack->i + size;
	__memory p = stack->stack + stack->i;
	if (curr_size >= stack->size) {
		if (stack->auto_plus) {
			// 开启自动增长
			__memory tmp = logic_malloc(__DEF_MAX_STACK_SIZE__ + stack->size);
			__logic_memcpy__(tmp, stack->stack, stack->size);
			logic_free(stack->stack);
			stack->stack = tmp;//新的堆栈
			stack->size += __DEF_MAX_STACK_SIZE__;
		} else 
			return NULL;
	}
	
	__logic_memcpy__(p, (__memory)v, size);
	stack->i += size;
	return (__memory)v;
}

/*
 * 作者:玩命
 * 开始日期:2010-4-21
 * 完成日期:2010-4-21
 * 参数:
 *    stack:堆栈结构.
 *    size:要弹出的长度.
 * 返回值:
 * 说明:
 *	  弹出数据从栈.
 */
__memory  __API__ pop_stack(PSTACK stack, __integer size) {
	__memory v;
	__integer i = stack->i - size;
	__integer curr_size = stack->i;
	if (curr_size < size) return NULL;
	v = stack->stack + i;
	stack->i -= size;
	return v;
}

/*
 * 作者:玩命
 * 开始日期:2010-4-21
 * 完成日期:2010-4-21
 * 参数:
 *    stack:栈内存指针.
 * 返回值:
 * 说明:
 *	  释放堆栈内存.
 */
__void __API__ free_stack(PSTACK *stack) {
	if ((*stack)->stack) logic_free((*stack)->stack);
	logic_free(*stack);
	(*stack) = NULL;
}

#if defined(__cplusplus)
}
#endif