#include "JunkCodeGen.h"

#define __ContinueGenerateJunkCode__()			(RollIt(pThunkCoderConfigure->JunkCoderRollArray))
__memory __INTERNAL_FUNC__ GenerateJunkCode(__integer *piOutSize, PTHUNKCODER_CONFIGURE pThunkCoderConfigure) {
	// 在最大和最小之间选取一个长度
	__integer iCount = 0;
	__memory pJunkCode = NULL;
	__integer iDifference = (pThunkCoderConfigure->JunkCodeSize->iJunkCodeMaxSize - pThunkCoderConfigure->JunkCodeSize->iJunkCodeMinSize) + 1;
	__integer iJunkCodeSize = (__integer)(GetRandDword() % iDifference);
	iJunkCodeSize += pThunkCoderConfigure->JunkCodeSize->iJunkCodeMinSize;

	
	pJunkCode = __logic_new__(__byte, iJunkCodeSize);
	while (__ContinueGenerateJunkCode__())
		pJunkCode[iCount++] = (__byte)GetRandDword();
	*piOutSize = iCount;
	return pJunkCode;
}
