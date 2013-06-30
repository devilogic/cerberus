#include <stdlib.h>

#include "Common.h"
#include "ChaosVmAth.h"

// 当保护指令时出错的错误回调提升函数
__void __INTERNAL_FUNC__ VmpThisInstructionErrorNotification(__integer iError, __char *pInstHex, __char *pInst, __integer iInstLength, __offset ofOffset) {
	if (iError == __VMP_INST_NOT_SUPPORT__) {
		printf("[-] Vmp instruction:[%s]%s(%d bytes) in %d offset not support\r\n", pInstHex, pInst, iInstLength, ofOffset);
	}
}
