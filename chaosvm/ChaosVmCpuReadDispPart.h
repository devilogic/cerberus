#if !defined(__CHAOSVM_CPU_READDISPPART__H__)
#define __CHAOSVM_CPU_READDISPPART__H__

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadDispPart(PCHAOSVM_CPU pCPU, __memory pDispStart, __byte bSizeToReadByte, __memory pData);

#define __READ_DISP_INT8_SAFE__(pCPU, pDispStart, INT8_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDispPart(pCPU, pDispStart, sizeof(__char), &(INT8_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DISP_INT16_SAFE__(pCPU, pDispStart, INT16_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDispPart(pCPU, pDispStart, sizeof(__sword), &(INT16_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_DISP_INT32_SAFE__(pCPU, pDispStart, INT32_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadDispPart(pCPU, pDispStart, sizeof(__sdword), &(INT32_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#endif
