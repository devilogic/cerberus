#if !defined(__ASSEMBLERENCODER_H__)
#define __ASSEMBLERENCODER_H__

#if defined(__cplusplus)
extern "C"
{
#endif
	
#include "AssemblerCommon.h"

__integer __INTERNAL_FUNC__ Encoder(__memory pInstBuf, PASM_OBJ pAsmObj, __offset ofCurrentOffset);
	
#if defined(__cplusplus)
}
#endif

#endif
