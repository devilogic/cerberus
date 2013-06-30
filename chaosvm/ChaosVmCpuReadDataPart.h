#if !defined(__CHAOSVM_CPU_READDATAPART__H__)
#define __CHAOSVM_CPU_READDATAPART__H__

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadDataPart(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __byte bSizeToReadByte, __memory pData);

#define __READ_DATA_UINT8_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT8_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__byte), &(UINT8_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DATA_UINT16_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT16_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__word), &(UINT16_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DATA_UINT32_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT32_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__dword), &(UINT32_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DATA_INT8_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT8_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__char), &(INT8_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DATA_INT16_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT16_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__sword), &(INT16_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DATA_INT32_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT32_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDataPart(pCPU, ImmIndexInOpcodeBuffer, sizeof(__sdword), &(INT32_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#endif
