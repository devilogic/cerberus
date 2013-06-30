#if !defined(__RANDROLL_H__)
#define __RANDROLL_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__dword __INTERNAL_FUNC__ GetRandDword();
__bool __INTERNAL_FUNC__ RollIt(__bool *pInBoolArray);
__void __INTERNAL_FUNC__ MakeRandArray(__bool *pOutBoolArray, __dword dwSeed);

#if defined(__cplusplus)
}
#endif

#endif
