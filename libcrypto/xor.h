#if !defined(__XOR_H__)
#define __XOR_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__dword __API__ PolyXorKey(__dword dwKey);
__void __API__ XorArray(__dword dwKey, __memory pPoint, __memory pOut, __integer iLength);
__void __API__ XorCoder(__memory pKey, __memory pBuffer, __integer iLength);
__void __API__ XorKey32Bits(__dword dwKeyContext, __memory pKey, __integer iKeyLength);

#if defined(__cplusplus)
}
#endif

#endif