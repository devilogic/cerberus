#include "ThunkCoder.h"

__void __API__ ReleaseThunkCode(PTHUNKCODER *pThunkCodePoint)
{
	
}

#define __MAX_THUNKCODE_LAYOUT_NODE__				1000
#define __ContinueGenerateThunkCoderNode__()		(RandRoll(pThunkCoderConfigure->ThunkCoderLayoutRollArray))
#define __GenerateThunkCoderType__()				((THUNKCODER_TYPE)(GenerateRandomNumber() % 2))
__INLINE__ THUNKCODER_TYPE* __INTERNAL_FUNC__ GenerateThunkCoderLayout(__integer *piOutCount, PTHUNKCODER_CONFIGURE pThunkCoderConfigure) {
	__integer iCount = 0;
	THUNKCODER_TYPE *pThunkCoderLayout = __logic_new__(THUNKCODER_TYPE, __MAX_THUNKCODE_LAYOUT_NODE__);
	while ((__ContinueGenerateThunkCoderNode__()) && (iCount < __MAX_THUNKCODE_LAYOUT_NODE__))
		pThunkCoderLayout[iCount++] = __GenerateThunkCoderType__();
	*piOutCount = iCount;
	return pThunkCoderLayout;
}

#define __GenerateThunkCoderArgCount__()			(GenerateRandomNumber() % (pThunkCoderConfigure->iThunkCoderFrameArgumentsMax))
__INLINE__ __void __INTERNAL_FUNC__ GenerateThunkCoderFrame(PTHUNKCODER pThunkCoderFrame, PTHUNKCODER_CONFIGURE pThunkCoderConfigure)
{
	pThunkCoderFrame->iArgumentCount = __GenerateThunkCoderArgCount__();//参数个数
	pThunkCoderFrame->pDummyCode = GenerateDummyCode(pThunkCoderConfigure);
	pThunkCoderFrame->pFlowCoder = GenerateFlowCoder(pThunkCoderConfigure);
}

/*
 * 生成花指令算法
 * 1.首先生成一组框架
 * 使用垃圾指令将生成的函数框架隔开,形如:
 * JUNKCODE
 * FRAM
 * JUNKCODE
 * FRAM
 * JUNKCODE
 * ...
 */

#define __CreateThunkCoder__(pThunkCoder)\
	(pThunkCoder) = __logic_new__(THUNKCODER, 1);\
	memset((pThunkCoder), 0, sizeof(THUNKCODER));
PTHUNKCODER __API__ GenerateThunkCode(PTHUNKCODER_CONFIGURE pThunkCoderConfigure) {
	__integer iLayoutCount = 0;
	__offset ofOffset = 0;
	THUNKCODER_TYPE ThunkCoderType;
	PTHUNKCODER pThunkCoder = NULL, *pThunkCoderPoint = &pThunkCoder;
	THUNKCODER_TYPE *pThunkCoderLayout = GenerateThunkCoderLayout(&iLayoutCount, pThunkCoderConfigure);
	
	// 根据布局图生成
	ofOffset = 0;
	for (int i = 0; i < iLayoutCount; i++) {
		__CreateThunkCoder__(*pThunkCoderPoint);
		ThunkCoderType = pThunkCoderLayout[i];
		(*pThunkCoderPoint)->Type = ThunkCoderType;
		(*pThunkCoderPoint)->ofOffset = ofOffset;
		if (ThunkCoderType == TKT_JUNKCODE) {
			__integer iJunkCodeSize = 0;
			(*pThunkCoderPoint)->pJunkCode = GenerateJunkCode(&iJunkCodeSize, pThunkCoderConfigure);
			(*pThunkCoderPoint)->iSize = __Alig__(iJunkCodeSize, pThunkCoderConfigure->iThunkCoderAlignment);//计算对齐
		} else if (ThunkCoderType == TKT_FRAME) {
			GenerateThunkCoderFrame(*pThunkCoderPoint);
		}
		ofOffset += (*pThunkCoderPoint)->iSize;
		pThunkCoderPoint = &((*pThunkCoderPoint)->pNext);
	}

	return pThunkCoder;
}

__memory __API__ AssemblerThunkCode(PTHUNKCODER pThunkCoder, PTHUNKCODER_CONFIGURE pThunkCoderConfigure) {
	return NULL;
}
