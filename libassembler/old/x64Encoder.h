#if !defined(__X64ENCODER_H__)
#define __X64ENCODER_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "Encoder.h"
	
__integer __INTERNAL_FUNC__ Encoder(PASM_OBJ pAsmObj, __memory pInstBuf);
	
#if defined(__cplusplus)
}
#endif

#endif
