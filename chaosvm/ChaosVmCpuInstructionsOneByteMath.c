/*
 * ADD指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_00(PCHAOSVM_CPU pCPU) {//[00]
	/*
	 * ADD r/m8, r8     r/m8 ADD r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_00", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, InternalADD8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
																			__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalADD8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_01(PCHAOSVM_CPU pCPU) {//[01]
	/*
	 * ADD r/m16, r16        r/m16 ADD r16.
	 * ADD r/m32, r32        r/m32 ADD r32.
	 */

	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_01", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalADD16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalADD16(pCPU, wInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalADD32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalADD32(pCPU, dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}



CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_02(PCHAOSVM_CPU pCPU) {//[02]
	/*
	 * ADD r8, r/m8    r8 ADD r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_02", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalADD8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
															__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalADD8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) ,bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_03(PCHAOSVM_CPU pCPU) {//[03]
	/*
	 * ADD r16, r/m16    r16 ADD r/m16.
	 * ADD r32, r/m32    r32 ADD r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_03", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalADD16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), \
																__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalADD16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalADD32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalADD32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_04(PCHAOSVM_CPU pCPU) {//[04]
	/*
	 * ADD AL, imm8     AL ADD imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_04", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalADD8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADD_05(PCHAOSVM_CPU pCPU) {//[05]
	/*
	 * ADD AX, imm16      AX ADD imm16.
	 * ADD EAX, imm32     EAX ADD imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADD_05", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalADD16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalADD32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * ADC指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_10(PCHAOSVM_CPU pCPU) {//[10]
	/*
	 * ADC r/m8, r8     r/m8 ADC r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_10", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, InternalADC8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
																			__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalADC8(pCPU , bInt8Tmp, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_11(PCHAOSVM_CPU pCPU) {//[11]
	/*
	 * ADC r/m16, r16        r/m16 ADC r16.
	 * ADC r/m32, r32        r/m32 ADC r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_11", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalADC16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalADC16(pCPU, wInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalADC32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalADC32(pCPU, dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_12(PCHAOSVM_CPU pCPU) {//[12]
	/*
	 * ADC r8, r/m8    r8 ADC r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_12", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalADC8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
															__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalADC8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_13(PCHAOSVM_CPU pCPU) {//[13]
	/*
	 * ADC r16, r/m16    r16 ADC r/m16.
	 * ADC r32, r/m32    r32 ADC r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_13", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalADC16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), \
																__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalADC16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalADC32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), \
																__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalADC32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_14(PCHAOSVM_CPU pCPU) {//[14]
	/*
	 * ADC AL, imm8     AL ADC imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_14", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalADC8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_ADC_15(PCHAOSVM_CPU pCPU) {//[15]
	/*
	 * ADC AX, imm16      AX ADC imm16.
	 * ADC EAX, imm32     EAX ADC imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ADC_15", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalADC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalADC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * INC RX/ERX指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_40(PCHAOSVM_CPU pCPU) {
	 // INC rAX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_40", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_41(PCHAOSVM_CPU pCPU) {
	// INC rCX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_41", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_CX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ECX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_42(PCHAOSVM_CPU pCPU) {
	// INC rDX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_42", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_43(PCHAOSVM_CPU pCPU) {
	// INC rBX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_43", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_44(PCHAOSVM_CPU pCPU) {
	// INC rSP
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_44", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_SP) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SP));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESP));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_45(PCHAOSVM_CPU pCPU) {
	// INC rBP
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_45", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BP));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBP));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_46(PCHAOSVM_CPU pCPU) {
	// INC rSI
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_46", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SI));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESI));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INC_47(PCHAOSVM_CPU pCPU) {
	// INC rDI
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INC_47", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_DI) = InternalINC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DI));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = InternalINC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDI));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * SUB 指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_28(PCHAOSVM_CPU pCPU) {//[28]
	/*
	 * SUB r/m8, r8     r/m8 SUB r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_28", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
																			__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_29(PCHAOSVM_CPU pCPU) {//[29]
	/*
	 * SUB r/m16, r16        r/m16 SUB r16.
	 * SUB r/m32, r32        r/m32 SUB r32.
	 */

	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_29", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSUB16(pCPU, wInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalSUB32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSUB32(pCPU, dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_2A(PCHAOSVM_CPU pCPU) {//[2A]
	/*
	 * SUB r8, r/m8    r8 SUB r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_2A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
															__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_2B(PCHAOSVM_CPU pCPU) {//[2B]
	/*
	 * SUB r16, r/m16    r16 SUB r/m16.
	 * SUB r32, r/m32    r32 SUB r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_2B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalSUB32(pCPU,  __CPU_GR32__(pCPU, Args.bRegOpcode), \
																__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalSUB32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_2C(PCHAOSVM_CPU pCPU) {//[2C]
	/*
	 * SUB AL, imm8     AL SUB imm8.
	 */

	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_2C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SUB_2D(PCHAOSVM_CPU pCPU) {//[2D]
	/*
	 * SUB AX, imm16      AX SUB imm16.
	 * SUB EAX, imm32     EAX SUB imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SUB_2D", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalSUB32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * SBB 指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_18(PCHAOSVM_CPU pCPU) {//[18]
	/*
	 * SBB r/m8, r8     r/m8 SBB r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_18", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, InternalSBB8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
																			__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSBB8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) );
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_19(PCHAOSVM_CPU pCPU) {//[19]
	/*
	 * SBB r/m16, r16        r/m16 SBB r16.
	 * SBB r/m32, r32        r/m32 SBB r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_19", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSBB16(pCPU, wInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSBB32(pCPU, dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_1A(PCHAOSVM_CPU pCPU) {//[1A]
	/*
	 * SBB r8, r/m8    r8 SBB r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_1A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalSBB8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
						__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalSBB8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_1B(PCHAOSVM_CPU pCPU) {//[1B]
	/*
	 * SBB r16, r/m16    r16 SBB r/m16.
	 * SBB r32, r/m32    r32 SBB r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_1B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), \
																__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), \
																__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_1C(PCHAOSVM_CPU pCPU) {//[1C]
	/*
	 * SBB AL, imm8     AL SBB imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_1C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalSBB8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SBB_1D(PCHAOSVM_CPU pCPU) {//[1D]
	/*
	 * SBB AX, imm16      AX SBB imm16.
	 * SBB EAX, imm32     EAX SBB imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SBB_1D", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * CMP 指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_38(PCHAOSVM_CPU pCPU) {//[38]
	/*
	 * CMP r/m8, r8     r/m8 CMP r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_38", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);

	if (Args.bIsEAReg) {
		__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalCMP8__(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_39(PCHAOSVM_CPU pCPU) {//[39]
	/*
	 * CMP r/m16, r16        r/m16 CMP r16.
	 * CMP r/m32, r32        r/m32 CMP r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_39", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalCMP16__(pCPU, wInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
		}
	} else {
		if (Args.bIsEAReg) {
			__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalCMP32__(pCPU, dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_3A(PCHAOSVM_CPU pCPU) {//[3A]
	/*
	 * CMP r8, r/m8    r8 CMP r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_3A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_3B(PCHAOSVM_CPU pCPU) {//[3B]
	/*
	 * CMP r16, r/m16    r16 CMP r/m16.
	 * CMP r32, r/m32    r32 CMP r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_3B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_3C(PCHAOSVM_CPU pCPU) {//[3C]
	/*
	 * CMP AL, imm8     AL CMP imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_3C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMP_3D(PCHAOSVM_CPU pCPU) {//[3D]
	/*
	 * CMP AX, imm16      AX CMP imm16.
	 * CMP EAX, imm32     EAX CMP imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMP_3D", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}
	
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * DEC RX/ERX指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_48(PCHAOSVM_CPU pCPU) {
	// DEC rAX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_48", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_49(PCHAOSVM_CPU pCPU) {
	// DEC rCX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_49", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_CX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ECX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4A(PCHAOSVM_CPU pCPU) {
	// DEC rDX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4B(PCHAOSVM_CPU pCPU) {
	// DEC rBX
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BX));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBX));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4C(PCHAOSVM_CPU pCPU) {
	// DEC rSP
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_SP) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SP));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESP));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4D(PCHAOSVM_CPU pCPU) {
	// DEC rBP
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4D", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BP));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBP));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4E(PCHAOSVM_CPU pCPU) {
	// DEC rSI
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4E", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SI));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESI));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DEC_4F(PCHAOSVM_CPU pCPU) {
	// DEC rDI
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DEC_4F", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);


	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_DI) = InternalDEC16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DI));

	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = InternalDEC32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDI));
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * IMUL指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_IMUL_6B(PCHAOSVM_CPU pCPU) {//[6B]
	/*
	 * IMUL r16, r/m16, imm8     word register ← r/m16 * signextended immediate byte.
	 * IMUL r32, r/m32, imm8     doubleword register ← r/m32 * sign-extended immediate byte.
	 */
	__char bInt8Imm;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_IMUL_6B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + Args.bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__sword swInt16Tmp;
		if (Args.bIsEAReg) {
			swInt16Tmp = UINT16_TO_INT16( __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, swInt16Tmp);
		}
		__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalIMUL3_16(pCPU, swInt16Tmp, INT8_TO_INT16(bInt8Imm));
	} else {
		__sdword sdwInt32Tmp;
		if (Args.bIsEAReg) {
			sdwInt32Tmp = UINT32_TO_INT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, sdwInt32Tmp);
		}
		__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalIMUL3_32(pCPU, sdwInt32Tmp, INT8_TO_INT32(bInt8Imm) );
	}

	pCPU->bOpcodeLength += 1 + 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_IMUL_69(PCHAOSVM_CPU pCPU) {//[69]
	/*
	 * IMUL r16, r/m16, imm16 word register ← r/m16 *immediate word.
	 * IMUL r32, r/m32, imm32 doubleword register ← r/m32 * immediate doubleword.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_IMUL_69", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__sword swInt16Imm;
		__sword swInt16Tmp;

		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + Args.bLength, swInt16Imm);

		if (Args.bIsEAReg) {
			swInt16Tmp = UINT16_TO_INT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, swInt16Tmp);
		}
		__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalIMUL3_16(pCPU, swInt16Tmp, swInt16Imm);

		pCPU->bOpcodeLength += 1 + 2 + Args.bLength;
	} else {
		__sdword sdwInt32Imm;
		__sdword sdwInt32Tmp;

		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + Args.bLength, sdwInt32Imm);

		if (Args.bIsEAReg) {
			sdwInt32Imm = UINT32_TO_INT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, sdwInt32Tmp);
		}
		__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalIMUL3_32(pCPU, sdwInt32Tmp, sdwInt32Imm);

		pCPU->bOpcodeLength += 1 + 4 + Args.bLength;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 调整指令实现
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_DAA_27(PCHAOSVM_CPU pCPU) {//[27]
	/*
     * DAA    Decimal adjust AL after addition.
     *
	 * Operation
	 * IF 64-Bit Mode
	 * THEN
	 * #UD;
	 * ELSE
	 * old_AL ← AL;
	 * old_CF ← CF;
	 * CF ← 0;
	 * IF (((AL AND 0FH) > 9) or AF = 1)
	 * THEN
	 * AL ← AL + 6;
	 * CF ← old_CF or (Carry from AL ← AL + 6);
	 * AF ← 1;
	 * ELSE
	 * AF ← 0;
	 * FI;
	 * IF ((old_AL > 99H) or (old_CF = 1))
	 * THEN
	 * AL ← AL + 60H;
	 * CF ← 1;
	 * ELSE
	 * CF ← 0;
	 * FI;
	 * FI;
	 * 
	 * Flags Affected
	 * The CF and AF flags are set if the adjustment of the value results in a decimal carry in either
	 * digit of the result (see the “Operation” section above). The SF, ZF, and PF flags are set according
	 * to the result. The OF flag is undefined.
 	 */
	__byte bOldAL;
	__byte bOldCF;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DAA_27", pCPU);
	__ExecuteInstBefore__(pCPU);
	bOldAL = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL);
	bOldCF = __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);

	if (((__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF) > 9) || __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF) == __EFLAG_SET__) {
		__word wInt16Tmp;
		wInt16Tmp =  UINT8_TO_UINT16(__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL)) + 6;
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __Low8__(wInt16Tmp));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (__High8__(wInt16Tmp) || bOldCF) ? __EFLAG_SET__ : __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_RESET__);
	}

	if ((bOldAL > 0x99) || (bOldCF == 1)) {
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) + 0x60);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_DAS_2F(PCHAOSVM_CPU pCPU) {//[2F]
	/*
	 * DAS           Decimal adjust AL after subtraction.
     * 
	 * Operation
	 * IF 64-Bit Mode
	 * THEN
	 * #UD;
	 * ELSE
	 * bOldAL ← AL;
	 * bOldCF ← CF;
	 * CF ← 0;
	 * IF (((AL AND 0FH) > 9) or AF = 1)
	 * THEN
	 * AL ← AL - 6;
	 * CF ← old_CF or (Borrow from AL ← AL - 6);
	 * AF ← 1;
	 * ELSE
	 * AF ← 0;
	 * FI;
	 * IF ((old_AL > 99H) or (old_CF = 1))
	 * THEN
	 * AL ← AL - 60H;
	 * CF ← 1;
	 * ELSE
	 * CF ← 0;
	 * FI;
	 * FI;
     *
	 * Flags Affected
	 * The CF and AF flags are set if the adjustment of the value results in a decimal borrow in either
	 * digit of the result (see the “Operation” section above).
	 */
	__byte bOldAL;
	__byte bOldCF;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_DAS_2F", pCPU);
	__ExecuteInstBefore__(pCPU);
	bOldAL = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL);
	bOldCF = __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);

	if (((__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF) > 9) || __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF) == __EFLAG_SET__) {
		__word wInt16Tmp;
		wInt16Tmp =  UINT8_TO_UINT16(__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL)) - 6;
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __Low8__(wInt16Tmp) );

		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (__High8__(wInt16Tmp) || bOldCF) ? __EFLAG_SET__ : __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_RESET__);
	}

	if ((bOldAL > 0x99) || (bOldCF == 1)) {
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) - 0x60);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AAA_37(PCHAOSVM_CPU pCPU) {//[37]
	/*
	 * AAA    ASCII adjust AL after addition.
     *
	 * Operation
	 * IF 64-Bit Mode
	 * THEN
	 * #UD;
	 * ELSE
	 * IF ((AL AND 0FH) > 9) or (AF = 1)
	 * THEN
	 * AL ← AL + 6;
	 * AH ← AH + 1;
	 * AF ← 1;
	 * CF ← 1;
	 * AL ← AL AND 0FH;
	 * ELSE
	 * AF ← 0;
	 * CF ← 0;
	 * AL ← AL AND 0FH;
	 * FI;
	 * FI;
	 * 
	 * Flags Affected
	 * The AF and CF flags are set to 1 if the adjustment results
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AAA_37", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (((__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF) > 9) || __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF) == __EFLAG_SET__) {
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) + 6);
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AH) + 1);

		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);

		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);

		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF);
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AAS_3F(PCHAOSVM_CPU pCPU) {//[3F]
	/*
	 * AAS     ASCII adjust AL after subtraction.
	 * 
	 * Operation
	 * IF 64-bit mode
	 * THEN
	 * #UD;
	 * ELSE
	 * IF ((AL AND 0FH) > 9) or (AF = 1)
	 * THEN
	 * AL ← AL – 6;
	 * AH ← AH – 1;
	 * AF ← 1;
	 * CF ← 1;
	 * AL ← AL AND 0FH;
	 * ELSE
	 * CF ← 0;
	 * AF ← 0;
	 * AL ← AL AND 0FH;
	 * FI;
	 * FI;
	 * 
	 * Flags Affected
	 * The AF and CF flags are set to 1 if there is a decimal
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AAS_3F", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (((__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF) > 9) || __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF) == __EFLAG_SET__) {
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) - 6);
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AH) - 1);

		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);

		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);

		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL) & 0xF);
	}
	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AAD_D5(PCHAOSVM_CPU pCPU) {//[D5]
	/*
	 * D5 0A	AAD            ASCII adjust AX before division.
	 * D5 ib	(No mnemonic)  Adjust AX before division
	 * 
	 * Operation
	 * IF 64-Bit Mode
	 * THEN
	 * #UD;
	 * ELSE
	 * tempAL ← AL;
	 * tempAH ← AH;
	 * AL ← (tempAL + (tempAH * imm8)) AND FFH;
	 * (* imm8 is set to 0AH for the AAD mnemonic.*)
	 * AH ← 0;
	 * FI;
	 *
	 * Flags Affected
	 * The SF, ZF, and PF flags are set according to the resulting binary value in the AL register; the
	 * OF, AF, and CF flags are undefined.
	 */
	__byte bInt8TmpAL;
	__byte bInt8TmpAH;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AAD_D5", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	bInt8TmpAL = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL);
	bInt8TmpAH = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AH);

	bInt8TmpAL = UINT16_TO_UINT8(UINT8_TO_UINT16(bInt8TmpAL) + (UINT8_TO_UINT16(bInt8TmpAH) * UINT8_TO_UINT16(bInt8Imm)));
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8TmpAL);
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, 0);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AAM_D4(PCHAOSVM_CPU pCPU) {//[D4]
	/*
	 * D4 0A AAM              ASCII adjust AX after multiply.
	 * D4 ib (No mnemonic)    Adjust AX after multiply to number base imm8.
	 *
	 * Operation
	 * IF 64-Bit Mode
	 * THEN
	 * #UD;
	 * ELSE
	 * tempAL ← AL;
	 * AH ← tempAL / imm8; (* imm8 is set to 0AH for the AAM mnemonic *)
	 * AL ← tempAL MOD imm8;
	 * FI;
	 * The immediate value (imm8) is taken from the second byte of the instruction.
	 *	
	 * Flags Affected
	 * The SF, ZF, and PF flags are set according to the resulting binary value in the AL register. The
	 * OF, AF, and CF flags are undefined.
	 */
	__byte bInt8TmpAL;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AAM_D4", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	bInt8TmpAL = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL);
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, (bInt8TmpAL/bInt8Imm));
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, (bInt8TmpAL%bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}
