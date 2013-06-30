/*
 * XOR
 */

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_30(PCHAOSVM_CPU pCPU) {//[30]
	/*
	 * XOR r/m8, r8     r/m8 XOR r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_30", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if(Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, \
						InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
						__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_31(PCHAOSVM_CPU pCPU) {//[31]
	/*
	 * XOR r/m16, r16        r/m16 XOR r16.
	 * XOR r/m32, r32        r/m32 XOR r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_31", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalXOR16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalXOR32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_32(PCHAOSVM_CPU pCPU) {//[32]
	/*
	 * XOR r8, r/m8    r8 XOR r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_32", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
						__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp) );
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_33(PCHAOSVM_CPU pCPU) {//[33]
	/*
	 * XOR r16, r/m16    r16 XOR r/m16.
	 * XOR r32, r/m32    r32 XOR r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_33", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_34(PCHAOSVM_CPU pCPU) {
	/*
	 * XOR AL, imm8     AL XOR imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_34", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XOR_35(PCHAOSVM_CPU pCPU) {//[35]
	/*
	 * XOR AX, imm16      AX XOR imm16.
	 * XOR EAX, imm32     EAX XOR imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XOR_35", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);
		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * OR
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_08(PCHAOSVM_CPU pCPU) {//[08]
	/*
	 * OR r/m8, r8     r/m8 OR r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_08", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, \
						InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
						__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_09(PCHAOSVM_CPU pCPU) {//[09]
	/*
	 * OR r/m16, r16        r/m16 OR r16.
	 * OR r/m32, r32        r/m32 OR r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_09", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalOR16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalOR16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalOR32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalOR32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_0A(PCHAOSVM_CPU pCPU) {//[0A]
	/*
	 * OR r8, r/m8    r8 OR r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_0A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
						__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_0B(PCHAOSVM_CPU pCPU) {//[0B]
	/*
	 * OR r16, r/m16    r16 OR r/m16.
	 * OR r32, r/m32    r32 OR r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_0B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalOR16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalOR16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalOR32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalOR32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_0C(PCHAOSVM_CPU pCPU) {//[0C]
	/*
	 * OR AL, imm8     AL OR imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_0C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OR_0D(PCHAOSVM_CPU pCPU) {//[0D]
	/*
	 * OR AX, imm16      AX OR imm16.
	 * OR EAX, imm32     EAX OR imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OR_0D", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength+1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalOR16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength+1, dwInt32Imm);
		__CPU_GR32__(pCPU,  CHAOSVM_R_EAX) = InternalOR32(pCPU, __CPU_GR32__(pCPU,  CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


/*
 * AND
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_20(PCHAOSVM_CPU pCPU) {//[20]
	/*
	 * AND r/m8, r8     r/m8 AND r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_20", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), \
						__CPU_GR8_GET__(pCPU, Args.bRegOpcode)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_21(PCHAOSVM_CPU pCPU) {//[21]
	/*
	 * AND r/m16, r16        r/m16 AND r16.
	 * AND r/m32, r32        r/m32 AND r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_21", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalAND16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalAND16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = InternalAND32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																				__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalAND32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_22(PCHAOSVM_CPU pCPU) {//[22]
	/*
	 * AND r8, r/m8    r8 AND r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_22", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode), \
															__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_23(PCHAOSVM_CPU pCPU) {//[23]
	/*
	 * AND r16, r/m16    r16 AND r/m16.
	 * AND r32, r/m32    r32 AND r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_23", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalAND16(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), \
																__CPU_GR16__(pCPU, Args.bRegOpcode));
		}
		else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = InternalAND16(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalAND32(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), \
																__CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = InternalAND32(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_24(PCHAOSVM_CPU pCPU) {//[24]
	/*
	 * AND AL, imm8     AL AND imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_24", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm));

	pCPU->bOpcodeLength += 2;

	__ExecuteInstAfter__(pCPU);
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_AND_25(PCHAOSVM_CPU pCPU) {//[25]
	/*
	 * AND AX, imm16      AX AND imm16.
	 * AND EAX, imm32     EAX AND imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_AND_25", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = InternalAND16(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);

		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = InternalAND32(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * TESTÖ¸Áî
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_TEST_A8(PCHAOSVM_CPU pCPU) {//[A8]
	/*
	 * TEST AL, imm8    AND imm8 with AL; set SF,ZF, PF according to result.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_TEST_A8", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);
	__InternalTEST8__(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_TEST_A9(PCHAOSVM_CPU pCPU) {//[A9]
	/*
	 * TEST AX, imm16    AND imm16 with AX; set SF, ZF, PF according to result.
	 * TEST EAX, imm32   AND imm32 with EAX; set SF, ZF, PF according to result.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_TEST_A9", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__InternalTEST16__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Imm);
		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__InternalTEST32__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Imm);
		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_TEST_84(PCHAOSVM_CPU pCPU) {//[84]
	/*
	 * TEST r/m8, r8     AND r8 with r/m8; set SF, ZF,PF according to result.
	 * Prefix Enable: Address-Size
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_TEST_84", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__InternalTEST8__(pCPU, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalTEST8__(pCPU, __CPU_GR8_GET__(pCPU, Args.bRegOpcode) , bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_TEST_85(PCHAOSVM_CPU pCPU) {//[85]
	/*
	 * TEST r/m16, r16    AND r16 with r/m16; set SF, ZF, PF according to result.
	 * TEST r/m32, r32    AND r32 with r/m32; set SF, ZF, PF according to result.
	 * Prefix Enable: Operand-Size,Address-Size
	 * 0x85;		TEST;		Ev,Gv;
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_TEST_85", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__InternalTEST16__(pCPU, __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalTEST16__(pCPU, __CPU_GR16__(pCPU, Args.bRegOpcode), wInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			__InternalTEST32__(pCPU, __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalTEST32__(pCPU, __CPU_GR32__(pCPU, Args.bRegOpcode), dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


