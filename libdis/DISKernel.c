#include "DISKernel.h"

/*
 * 需要引出的全局变量
 */
__NEED_EXPORT__ DIS_CONFIGURE g_DISConfigure = {0};															//DIS的配置结构

/*
 * 私有全局变量
 */

/*
 * 私有函数声明
 */
// 扩展函数
#include "DISExFunctions.c"

/*
 * 宏函数
 */
// 处理步骤函数返回值,第11步不能返回到入口标志,会造成无限的循环
#define __HandleDISStepReturnValue__(n, x)				{\
	if (__DIS_SUCCESS__(x)) {\
		if ((x & __DIS_ERROR_SUCCESS_GOTO__) == __DIS_ERROR_SUCCESS_GOTO__) {\
			if (x == __DIS_ERROR_SUCCESS_GOTO_0__) goto _call_back_0;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_0__) && (n != 0)) goto _call_back_0;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_1__) && (n != 1)) goto _call_back_1;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_2__) && (n != 2)) goto _call_back_2;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_3__) && (n != 3)) goto _call_back_3;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_4__) && (n != 4))  goto _call_back_4;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_5__) && (n != 5)) goto _call_back_5;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_6__) && (n != 6)) goto _call_back_6;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_7__) && (n != 7))goto _call_back_7;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_8__) && (n != 8)) goto _call_back_8;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_9__) && (n != 9)) goto _call_back_9;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_A__) && (n != 10)) goto _call_back_10;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_B__) && (n != 11)) goto _call_back_11;\
			else if ((x == __DIS_ERROR_SUCCESS_GOTO_ORIG_ENTRY__) && (n != 11)) goto _call_back_11;\
		}\
	} else return FALSE;\
}

/*
 * 函数定义
 */
#include "DISEntry.c"
#include "DISEntryInDll.c"
