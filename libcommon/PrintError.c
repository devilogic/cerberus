#include "PrintError.h"
#include <stdio.h>
#include <Windows.h>
__void __INTERNAL_FUNC__ LogicPrintError(__char *szMsg, __integer iErrNo, __integer iLine, __char *szFile) {
	__char DebugBuffer[1024] = {0};
	sprintf(DebugBuffer,"<Error>%s(%d):%s Error[%d]\n", szFile, iLine, szMsg, iErrNo);
	OutputDebugStringA(DebugBuffer);
}
