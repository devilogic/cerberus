#if !defined(__DYNAMICARRAY_H__)
#define __DYNAMICARRAY_H__

#include "Configure.h"
#include "TypeDef.h"
#include "LogicCrt.h"

#if defined(__cplusplus)
extern "C"
{
#endif
 
#define __MemPut64Bits__(MemPtr, Data)\
	*(MemPtr)++ = (__byte)(((Data) >> 56) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 48) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 40) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 32) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 24) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 16) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 8) & 0xFF),\
	*(MemPtr)++ = (__byte)((Data) & 0xFF)

#define __MemPut32Bits__(MemPtr, Data)\
	*(MemPtr)++ = (__byte)(((Data) >> 24) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 16) & 0xFF),\
	*(MemPtr)++ = (__byte)(((Data) >> 8) & 0xFF),\
	*(MemPtr)++ = (__byte)((Data) & 0xFF)

#define __MemPut16Bits__(MemPtr, Data)\
	*(MemPtr)++ = (__byte)(((Data) >> 8) & 0xFF),\
	*(MemPtr)++ = (__byte)((Data) & 0xFF)

#define __MemPut8Bits__(MemPtr, Data)\
	*(MemPtr)++ = (__byte)Data

#define __MemGet64Bits__(MemPtr)\
	((MemPtr) += 8, ((__qword)(MemPtr)[-8] << 56) | ((__qword)(MemPtr)[-7] << 48) |\
	((__qword)(MemPtr)[-6] << 40) | ((__qword)(MemPtr)[-5] << 32) |\
	((__qword)(MemPtr)[-4] << 24 ) | ((__qword)(MemPtr)[-3] << 16) |\
	((__qword)(MemPtr)[-2] << 8 ) | (__qword)(MemPtr)[-1])

#define __MemGet32Bits__(MemPtr)\
	((MemPtr) += 4, ((__dword)(MemPtr)[-4] << 24) | ((__dword)(MemPtr)[-3] << 16) |\
	((__dword)(MemPtr)[-2] << 8) | (__dword)(MemPtr)[-1])

#define __MemGet16Bits__(MemPtr)\
	((MemPtr) += 2, (__word)(MemPtr)[-2] << 8) | ((__word)(MemPtr)[-1]) 

#define __MemGet8Bits__(MemPtr)\
	((__byte) *(MemPtr)++)

#define __ToBytePtr__(MemPtr) (__byte *)(MemPtr)
#define __ToWordPtr__(MemPtr) (__word *)(MemPtr)
#define __ToDwordPtr__(MemPtr) (__dword *)(MemPtr)
#define __ToQwordPtr__(MemPtr) (__qword *)(MemPtr)
#define __ToFloatPtr__(MemPtr) (__float *)(MemPtr)
#define __ToDoublePtr__(MemPtr) (__double *)(MemPtr)

#define __ToCharPtr__(MemPtr) (__char *)(MemPtr)
#define __TosWordPtr__(MemPtr) (__sword *)(MemPtr)
#define __TosDwordPtr__(MemPtr) (__sdword *)(MemPtr)
#define __TosQwordPtr__(MemPtr) (__sqword *)(MemPtr)
#define __TosFloatPtr__(MemPtr) (__sfloat *)(MemPtr)
#define __TosDoublePtr__(MemPtr) (__sdouble *)(MemPtr)

#define __ToIntegerPtr__(MemPtr) (__integer *)(MemPtr)

__integer __INTERNAL_FUNC__ InputValueToMemory(__memory *pMemoryPoint, __integer iPoint, __memory pValue, __integer iValueSize);
__memory __INTERNAL_FUNC__ GetValueFormMemory(__memory pMemory, __integer iPoint, __integer iValueSize);

#if defined(__cplusplus)
}
#endif

#endif
