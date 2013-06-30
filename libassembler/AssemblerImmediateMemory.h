#if !defined(__ASSEMBLERIMMEDIATEMEMORY_H__)
#define __ASSEMBLERIMMEDIATEMEMORY_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__EXTERN__ __memory g_pImmediateMemory;
__EXTERN__ __integer g_iImmediateMemoryMaxSize;

__memory __INTERNAL_FUNC__ InitImmediateMemory(__integer iMaxSize);	
__void __INTERNAL_FUNC__ FreeImmediateMemory();
__memory __INTERNAL_FUNC__ GetImmediate(__integer iValueSize);	
__void __INTERNAL_FUNC__ BackImmediate(__integer iValueSize);
__void __INTERNAL_FUNC__ ResetImmediate(__memory pMemory, __integer iSize);
	
#if defined(__cplusplus)
}
#endif

#endif
