__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uByte(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __byte *puInt8) {
	if (pCPU->bOpcodeLength + 1 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*puInt8 =  *(__byte *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer]);
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uWord(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __word *puInt16) {
	if (pCPU->bOpcodeLength + 2 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*puInt16 = *(__word *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer]);
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_uDword(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __dword *puInt32) {
	if (pCPU->bOpcodeLength + 4 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*puInt32 = *(__dword *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer] );
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sByte(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __char *pInt8) {
	if (pCPU->bOpcodeLength + 1 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*pInt8 =  *(__char *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer]);
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sWord(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __word *pInt16) {
	if (pCPU->bOpcodeLength + 2 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*pInt16 = *(__sword *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer]);
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadImm_sDword(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __dword *pInt32) {
	if (pCPU->bOpcodeLength + 4 >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	*pInt32 = *(__sdword *)(&pCPU->OpcodeBuffer[bImmIndexInOpcodeBuffer]);
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}
