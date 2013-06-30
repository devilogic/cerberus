#if !defined(__XRAND_H__)
#define __XRAND_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__dword __API__ GenerateRandomNumber();
__bool __API__ RandRoll(__bool *pInBoolArray);
__void __API__ GenerateRollArray(__bool *pOutBoolArray, __integer iSeed);

#if defined(__cplusplus)
}
#endif

#endif
