/*
 * MOVָ��
 */

// 0xB0;		MOV;		AL,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B0(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register AL
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B0", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB1;		MOV;		CL,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B1(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register CL
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B1", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_CL, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB2;		MOV;		DL,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B2(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register DL
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B2", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_DL, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB3;		MOV;		BL,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B3(PCHAOSVM_CPU pCPU) {
	/*
	* MOV    MOV immediate byte into byte register BL
	* Prefix Enable: None
	*/
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B3", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_BL, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB4;		MOV;		AH,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B4(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register AH
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B4", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB5;		MOV;		CH,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B5(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register CH
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B5", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_CH, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB6;		MOV;		DH,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B6(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register DH
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B6", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_DH, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB7;		MOV;		BH,Ib;			MOV;	MOV immediate byte into byte register;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B7(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate byte into byte register BH
	 * Prefix Enable: None
	 */
	__byte bInt8Code;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B7", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_BH, bInt8Imm);

	pCPU->bOpcodeLength += 2;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB8;		MOV;		rAX,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B8(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B8", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xB9;		MOV;		rCX,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_B9(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_B9", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBA;		MOV;		rDX,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BA(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BA", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBB;		MOV;		rBX,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BB(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BB", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBC;		MOV;		rSP,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BC(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BC", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_SP) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBD;		MOV;		rBP,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BD(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BD", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBE;		MOV;		rSI,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BE(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BE", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 0xBF;		MOV;		rDI,Iv;		MOV;
CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_BF(PCHAOSVM_CPU pCPU) {
	/*
	 * MOV    MOV immediate data (depending on operand-size attribute) into register
	 * Prefix Enable: Operand-Size
	 */
	__byte bInt8Code;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_BF", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8Code);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
		__CPU_GR16__(pCPU, CHAOSVM_R_DI) =  wInt16Imm;
		pCPU->bOpcodeLength += 1 + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32Imm);
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = dwInt32Imm;
		pCPU->bOpcodeLength += 1 + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_A0(PCHAOSVM_CPU pCPU) {//[A0]
	/* 
	 * MOV AL,moffs8*    Move byte at (seg:offset) to AL.
	 * Prefix Enable: Address-Size
	 */
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_A0", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__word wInt16ImmOffset;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16ImmOffset);
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), bInt8Tmp);
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8Tmp);
		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32ImmOffset;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32ImmOffset);
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8Tmp);
		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_A1(PCHAOSVM_CPU pCPU) {//[A1]
	/* 
	 * MOV AX,moffs16*   Move word at (seg:offset) to AX.
	 * MOV EAX,moffs32*  Move doubleword at	(seg:offset) to EAX.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_A1", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU))
	{
		/*
		 * 16λѰַ
		 */
		__word wInt16ImmOffset;

		__ExecuteInstBefore__(pCPU);
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16ImmOffset);
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), wInt16Tmp);
			__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16Tmp;
		} else {
			__dword wInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), wInt32Tmp);
			__CPU_GR32__(pCPU, CHAOSVM_R_EAX) =  wInt32Tmp;
		}
		pCPU->bOpcodeLength += 3;
	} else {
		/*
		 * 32λѰַ
		 */
		__dword dwInt32ImmOffset;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32ImmOffset);
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, wInt16Tmp);
			__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16Tmp;
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, dwInt32Tmp);
			__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32Tmp;
		}
		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_A2(PCHAOSVM_CPU pCPU) {//[A2]
	/*
	 * MOV moffs8,AL    Move AL to (seg:offset).
	 * Prefix Enable: Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_A2", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__word wInt16ImmOffset;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16ImmOffset);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
		pCPU->bOpcodeLength += 3;
	} else {
		__dword dwInt32ImmOffset;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32ImmOffset);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_A3(PCHAOSVM_CPU pCPU) {//[A3]
	/* 
	 * MOV moffs16*,AX   Move AX to (seg:offset).
	 * MOV moffs32*,EAX  Move EAX to (seg:offset).
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_A3", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		/*
		 * 16λѰַ
		 */
		__word wInt16ImmOffset;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16ImmOffset);
		if(__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), __CPU_GR16__(pCPU, CHAOSVM_R_AX));
		} else {
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(wInt16ImmOffset), __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
		}

		pCPU->bOpcodeLength += 3;
	} else {
		/*
		 * 32λѰַ
		 */
		__dword dwInt32ImmOffset;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32ImmOffset);
		if(__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, __CPU_GR16__(pCPU, CHAOSVM_R_AX));
		} else {
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), dwInt32ImmOffset, __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
		}

		pCPU->bOpcodeLength += 5;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_88(PCHAOSVM_CPU pCPU) {//[88]
	/*
	 * MOV r/m8,r8      Move r8 to r/m8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_88", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
	} else {
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
	}

	pCPU->bOpcodeLength += (1 + Args.bLength);

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_89(PCHAOSVM_CPU pCPU) {//[89]
	/*
	 * MOV r/m16,r16    Move r16 to r/m16.
	 * MOV r/m32,r32    Move r32 to r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_89", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = __CPU_GR16__(pCPU, Args.bRegOpcode);
		} else {
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR16__(pCPU, Args.bRegOpcode));
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = __CPU_GR32__(pCPU, Args.bRegOpcode);
		} else {
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR32__(pCPU, Args.bRegOpcode));
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_8A(PCHAOSVM_CPU pCPU) {//[8A]
	/*
	 * MOV r8,r/m8     Move r/m8 to r8.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_8A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_8B(PCHAOSVM_CPU pCPU) {//[8B]
	/*
	 * MOV r16,r/m16    Move r/m16 to r16.
	 * MOV r32,r/m32    Move r/m32 to r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_8B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR16__(pCPU, Args.bRegOpcode) = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = wInt16Tmp;
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR32__(pCPU, Args.bRegOpcode) = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = dwInt32Tmp;
		}
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;
	
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_8C(PCHAOSVM_CPU pCPU) {//[8C]
	/*
	 * MOV r/m16,Sreg**     Move segment register to r/m16.
	 * Prefix Enable: None
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_8C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = __CPU_SR__(pCPU, Args.bRegOpcode);
	} else {
		__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_SR__(pCPU, Args.bRegOpcode));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOV_8E(PCHAOSVM_CPU pCPU) {//[8E]
	/*
	 * MOV Sreg,r/m16**    Move r/m16 to segment register
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOV_8E", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__CPU_SR__(pCPU, Args.bRegOpcode) = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
	} else {
		__word wInt16Tmp;
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16Tmp);
		__CPU_SR__(pCPU, Args.bRegOpcode) = wInt16Tmp;
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


