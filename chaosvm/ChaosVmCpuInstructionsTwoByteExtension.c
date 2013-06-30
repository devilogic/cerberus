/*
 * 0FBA XX
 */
/*
 * BT(bit test)指令选择第一个操作数的第n位并将其拷贝到进位标志中。
 * BTS(bit test and set)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将第n位置位。
 * BTR(bit test and reset)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将第n位清零。
 * BTC(bit test and complement)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将这个数据位取反。
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_IncorrectOpcode_0FBA(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_IncorrectOpcode_0FBA", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_UnImplement_0FBA(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_UnImplement_0FBA", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  0FBA /%02X\n", __CPU_EIP__(pCPU), pArgs->bRegOpcode);
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_BT_0FBA_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * BT r/m16, imm8       Store selected bit in CF flag.
	 * BT r/m32, imm8        Store selected bit in CF flag
	 */
	__byte bInt8BitTmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_BT_0FBA_4", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));					
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			bInt8BitTmp = GET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
		}
	} else {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));							
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_BTS_0FBA_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * BTS r/m16, imm8    Store selected bit in CF flag and set.
	 * BTS r/m32, imm8    Store selected bit in CF flag and set.
	 */
	__byte bInt8BitTmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_BTS_0FBA_5", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));	
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = SET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));					
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			bInt8BitTmp = GET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			wInt16Tmp = SET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = SET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			dwInt32Tmp = SET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_BTR_0FBA_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * BTR r/m16, imm8    selected bit in CF flag and clear.
	 * BTR r/m32, imm8    selected bit in CF flag and clear.
	 */
	__byte bInt8BitTmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_BTR_0FBA_6", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));	
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = RESET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));					
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			bInt8BitTmp = GET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			wInt16Tmp = RESET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = RESET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			dwInt32Tmp = RESET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForTwo_BTC_0FBA_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * BTC r/m16, imm8    Store selected bit in CF flag and complement.
	 * BTC r/m32, imm8    Store selected bit in CF flag and complement.
	 */
	__byte bInt8BitTmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForTwo_BTC_0FBA_7", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));	
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = COMPLEMENT_BIT16(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT16(bInt8Imm));					
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			bInt8BitTmp = GET_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			wInt16Tmp = COMPLEMENT_BIT16(wInt16Tmp, UINT8_TO_UINT16(bInt8Imm));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = COMPLEMENT_BIT32(__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), UINT8_TO_UINT32(bInt8Imm));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			dwInt32Tmp = COMPLEMENT_BIT32(dwInt32Tmp, UINT8_TO_UINT32(bInt8Imm));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_OpcodeExtDispatch_0FBA(PCHAOSVM_CPU pCPU) {//[BA]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_OpcodeExtDispatch_0FBA", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntry0FBA[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}
