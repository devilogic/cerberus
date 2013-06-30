#if !defined(__THUNKCODERCONFIGURE_H__)
#define __THUNKCODERCONFIGURE_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 花指令构造配置结构
 */
typedef struct _THUNKCODER_CONFIGURE {
	struct {
		__integer iJunkCodeMinSize;//垃圾指令最小长度
		__integer iJunkCodeMaxSize;//垃圾指令最大长度
	} JunkCodeSize;
	__integer iThunkCoderAlignment;//花指令代码块对齐力度
	__integer iThunkCoderFrameArgumentsMax;//花指令函数最大参数个数
	__integer iMathExpRollProb;//数学表达式骰子概率

	// 各种骰子队列
	__bool ThunkCoderLayoutRollArray[100];//花指令布局图骰子队列
	__bool FlowCoderRollArray[100];//指令流程骰子队列
	__bool JunkCoderRollArray[100];//垃圾指令骰子队列
	__bool MathExpRollArray[100];//数学表达式骰子队列
} THUNKCODER_CONFIGURE, *PTHUNKCODER_CONFIGURE;

#if defined(__cplusplus)
}
#endif

#endif
