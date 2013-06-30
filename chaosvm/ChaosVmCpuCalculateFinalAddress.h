#if !defined(__CHAOSVMCPUCALCULATEFINALADDRESS_H__)
#define __CHAOSVMCPUCALCULATEFINALADDRESS_H__

__INLINE__ __address __INTERNAL_FUNC__ CalculateFinalAddress(__address addrCurrAddress, __dword dwDisplacement, __integer iSize);
__INLINE__ __address __INTERNAL_FUNC__ CalculateJmpAddress(__address addrCurrAddress, __dword dwInstLength, __dword dwOffset, __integer iSize);

#define __CalculateFinalAddress_Offset_8Bits__(addrCurrAddress, dwDisplacement)\
	CalculateFinalAddress((__address)(addrCurrAddress), (__dword)(dwDisplacement), sizeof(__byte))

#define __CalculateFinalAddress_Offset_16Bits__(addrCurrAddress, dwDisplacement)\
	CalculateFinalAddress((__address)(addrCurrAddress), (__dword)(dwDisplacement), sizeof(__word))

#define __CalculateFinalAddress_Offset_32Bits__(addrCurrAddress, dwDisplacement)\
	CalculateFinalAddress((__address)(addrCurrAddress), (__dword)(dwDisplacement), sizeof(__dword))

#define __CalculateJmpAddress_Offset_8Bits__(addrCurrAddress, dwInstLength, dwOffset)\
	CalculateJmpAddress((__address)addrCurrAddress, (__dword)dwInstLength, (__dword)dwOffset, sizeof(__byte))

#define __CalculateJmpAddress_Offset_16Bits__(addrCurrAddress, dwInstLength, dwOffset)\
	CalculateJmpAddress((__address)addrCurrAddress, (__dword)dwInstLength, (__dword)dwOffset, sizeof(__word))

#define __CalculateJmpAddress_Offset_32Bits__(addrCurrAddress, dwInstLength, dwOffset)\
	CalculateJmpAddress((__address)addrCurrAddress, (__dword)dwInstLength, (__dword)dwOffset, sizeof(__dword))

#endif
