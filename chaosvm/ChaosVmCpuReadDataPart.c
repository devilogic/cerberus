__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmReadDataPart(PCHAOSVM_CPU pCPU, __byte bImmIndexInOpcodeBuffer, __byte bSizeToReadByte, __memory pData) {
	__dword dwData = 0;
	if (pCPU->bOpcodeLength + bSizeToReadByte >= pCPU->bOpcodeMaxLength) {
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INCOMPLETE_OPCODE__);
		return __CPU_STATUS_INCOMPLETE_OPCODE__;
	}

	dwData = pCPU->pMmReadDataPart(pCPU, pCPU->pUserContext, bImmIndexInOpcodeBuffer, bSizeToReadByte);

	switch (bSizeToReadByte) {
	case 1:
		*(__byte *)pData = *(__dword *)(&dwData);
	break;
	case 2:
		*(__word *)pData = *(__dword *)(&dwData);
	break;
	case 4:
		*(__dword *)pData = *(__dword *)(&dwData);
	break;
	default:
		*(__dword *)pData = *(__dword *)(&dwData);
	}
	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}
