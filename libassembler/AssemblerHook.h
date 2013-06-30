#if !defined(__ASSEMBLERHOOK_H__)
#define __ASSEMBLERHOOK_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "AssemblerCommon.h"

/*
 * HOOKº¯ÊýÔ­ÐÍ
 */ 
typedef __integer (__INTERNAL_FUNC__ *FPAssemblerHook)(__memory pInstMem, PASM_OBJ pAsmObj, __offset ofCurrentOffset);
	
#if defined(__cplusplus)
}
#endif

#endif
