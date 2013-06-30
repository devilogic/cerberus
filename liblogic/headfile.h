#if !defined(__HEADFILE_H__)
#define __HEADFILE_H__

/*
 * 文件标识
 */
#define __LOGIC_HEADERFILE__		0xFFFFFFFF

/*
 * 头文件
 */
#include "logicdbg.h"

/*
 * 宏函数
 */
/* 最大 */
#define __min__(a,b)		((a) < (b)? (a) : (b))
/* 最小 */
#define __max__(a,b)		((a) > (b)? (a) : (b))


#endif
