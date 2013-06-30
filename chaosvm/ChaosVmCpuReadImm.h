#if !defined(__CHAOSVM_CPU_READIMM__H__)
#define __CHAOSVM_CPU_READIMM__H__

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uByte(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __byte *puInt8);
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uWord(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __word *puInt16);
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uDword(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __dword *puInt32);
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sByte(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __char *pInt8);
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sWord(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __word *pInt16);
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sDword(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __dword *pInt32);

#define __READ_IMM_UINT8_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT8_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_uByte(pCPU, ImmIndexInOpcodeBuffer, &(UINT8_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_IMM_UINT16_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT16_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_uWord(pCPU, ImmIndexInOpcodeBuffer, &(UINT16_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_IMM_UINT32_SAFE__(pCPU, ImmIndexInOpcodeBuffer, UINT32_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_uDword(pCPU, ImmIndexInOpcodeBuffer, &(UINT32_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_IMM_INT8_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT8_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_sByte(pCPU, ImmIndexInOpcodeBuffer, &(INT8_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_IMM_INT16_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT16_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_sWord(pCPU, ImmIndexInOpcodeBuffer, &(INT16_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#define __READ_IMM_INT32_SAFE__(pCPU, ImmIndexInOpcodeBuffer, INT32_Var) \
	if (!__CPU_STATUS_SUCCESS__(ChaosVmReadImm_sDword(pCPU, ImmIndexInOpcodeBuffer, &(INT32_Var)))){ \
	return __GET_LAST_STATUS__(pCPU);}

#endif
