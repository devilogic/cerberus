#if !defined(__LCRYPTO_H__)
#define __LCRYPTO_H__

#include "crc.h"
#include "xor.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__integer __API__ EuclidAlgorithm(__integer m, __integer n);
__integer __API__ EuclidAlgorithmEx(__integer m, __integer n, __integer *pa, __integer *pb);

#if defined(__cplusplus)
}
#endif

#endif
