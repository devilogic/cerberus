#if !defined(__ENCODER_H__)
#define __ENCODER_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "AssemblerCommon.h"

#define OPEX_NONE 0xFF
	
__byte __INTERNAL_FUNC__ GetModRM(PASM_OBJ pAsmObj);
__byte __INTERNAL_FUNC__ GetSIB(PASM_OBJ pAsmObj);
__byte __INTERNAL_FUNC__ GetREX(PASM_OBJ pAsmObj);	
__integer __INTERNAL_FUNC__ MakeCode(PASM_OBJ pAsmObj, __byte bOpEx);
	
#if defined(__cplusplus)
}
#endif

#endif
