#if !defined(__THUNKCODER_H__)
#define __THUNKCODER_H__

#include "Common.h"
#include "ThunkCoderConfigure.h"
#include "RandRoll.h"
#include "JunkCodeGen.h"
#include "ProtoType.h"
#include "FlowCodeGen.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __DEF_THUNKCODER_ALIGNMENT__		128
#define __DEF_MAX_THUNKCODER_ARG__			6
#define __DEF_THUNKCODER_VAR_ALIGNMENT__	4

typedef enum _THUNKCODER_TYPE {
	TKT_JUNKCODE = 0,
	TKT_FRAME,
} THUNKCODER_TYPE;

/*
 * 局部变量
 */
typedef struct _LOCAL_VARIABLE {
	__integer iOffset;//离EBP的偏移
	__integer iSize;//变量的大小
} LOCAL_VARIABLE, *PLOCAL_VARIABLE;

/*
 * 花指令函数
 */
typedef struct _THUNKCODER_PROCEDURE {
	__offset ofOffset;//离这个区域的开头的偏移
	__integer iSize;//大小
	__integer iArgumentCount;//参数个数
	__integer iStackSize;//栈大小
	__integer iLocalVarCount;//局部变量个数
	PFLOWCODER pFlowCoder;//流程代码
} THUNKCODER_PROCEDURE, *PTHUNKCODER_PROCEDURE;

/*
 * 花指令函数执行链
 */
typedef struct _THUNKCODER {
	struct _THUNKCODER *pNext;//下一个节点
	THUNKCODER_TYPE Type;//类型
	__offset ofOffset;//离这个区域的开头的偏移
	__integer iSize;//大小
	__memory pJunkCode;//垃圾代码
	PLOCAL_VARIABLE pLocalVariable;//局部变量
	struct _THUNKCODER *CallOutList;//调用其他的花指令区域链表
	PFLOWCODER pFlowCoder;//流程代码
} THUNKCODER, *PTHUNKCODER;

PTHUNKCODER __API__ GenerateThunkCode(PTHUNKCODER_CONFIGURE pThunkCoderConfigure);
__memory __API__ AssemblerThunkCode(PTHUNKCODER pThunkCoder, PTHUNKCODER_CONFIGURE pThunkCoderConfigure);
__void __API__ ReleaseThunkCode(PTHUNKCODER *pThunkCodePoint);

#if defined(__cplusplus)
}
#endif

#endif
