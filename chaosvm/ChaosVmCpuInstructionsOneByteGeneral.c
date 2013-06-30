CPU_STATUS __INTERNAL_FUNC__ FuncOne_UnImplement(PCHAOSVM_CPU pCPU) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_UnImplement", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  %02X\n", __CPU_EIP__(pCPU), pCPU->OpcodeBuffer[pCPU->bOpcodeLength]);
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_InvalidOpcode(PCHAOSVM_CPU pCPU) {//[F1]
	// 读取出错，此处设置访问中断
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_InvalidOpcode", pCPU);
	pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_UD__;
	__CPU_SET_INTERRUPT_OCCUR__(pCPU);
	return __CPU_STATUS_INVALID_OPCODE__;
}

/*
 * 前缀指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_66(PCHAOSVM_CPU pCPU) {//[66]
	/*
	 * Change DEFAULT operand size. (66)
	 */
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_66", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 切换操作数长度类型
	 */
	pCPU->bOperandType = (pCPU->bDefaultOperandType == __CPU_OPERAND_TYPE_32__) ? __CPU_OPERAND_TYPE_16__ : __CPU_OPERAND_TYPE_32__;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix |= __CPU_INSTRUCTION_PREFIX_CHANGE_OPERAND_SIZE__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_67(PCHAOSVM_CPU pCPU) {//[67]
	/*
	 *Change DEFAULT address size. (67)
	 */
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_67", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 切换寻址长度类型
	 */
	pCPU->bAddressingMode = ~(pCPU->bDefaultAddressingMode);

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix |= __CPU_INSTRUCTION_PREFIX_CHANGE_ADDRESS_SIZE__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_F2(PCHAOSVM_CPU pCPU) {//[F2]
	/*
	 * Repeat prefixes. (F2)
	 */
	__byte bCodeByte;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_F2", pCPU);

	/*指向机器码下一个字节*/
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀
	 */
	pCPU->bRepPrefixEnable = 0xF2;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*填写指令信息*/
	pCPU->InstructionInfomation.wPrefix |= __CPU_INSTRUCTION_PREFIX_REPNZ__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	Status = pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
	pCPU->bRepPrefixEnable = 0;
	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_F3(PCHAOSVM_CPU pCPU) {//[F3]
	/*
	 *Repeat prefixes. (F3)
	 */
	__byte bCodeByte;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_F3", pCPU);

	/*
	 * 指向机器码下一个字节
	 */
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀
	 */
	pCPU->bRepPrefixEnable = 0xF3;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix |= __CPU_INSTRUCTION_PREFIX_REPZ__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	Status = pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
	pCPU->bRepPrefixEnable = 0;
	return Status;
}

/*
 * 2012.2.8日后分别处理每个段前缀,此函数废弃
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_SegOverride(PCHAOSVM_CPU pCPU) {//[2E,36,3E,26,64,65]
	/*
	 * Segment override prefixes(change DEFAULT segment). (2E, 36, 3E, 26, 64, 65)
	 */
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_SegOverride", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	switch(bPrefixByte) {
	case 0x2E:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_CS;
	break;
	case 0x26:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_ES;
	break;
	case 0x36:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_SS;
	break;
	case 0x3E:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_DS;
	break;
	case 0x64:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_FS;
	break;
	case 0x65:
		pCPU->bDataSegmentRegister = CHAOSVM_SR_GS;
	break;
	}
#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	switch(bPrefixByte) {
	case 0x2E:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_CS__;
	break;
	case 0x26:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_ES__;
	break;
	case 0x36:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_SS__;
	break;
	case 0x3E:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_DS__;
	break;
	case 0x64:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_FS__;
	break;
	case 0x65:
		pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_GS__;
	break;
	}
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_Prefix_F0(PCHAOSVM_CPU pCPU) {//[F0]
	/*
	 * LOCK prefix. (F0)
	 */
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Prefix_F0", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 不需要设置任何前缀
	 */

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix |= __CPU_INSTRUCTION_PREFIX_LOCK__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

/*
 * PUSH指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_68(PCHAOSVM_CPU pCPU) {//[68]
	/*
	 * PUSH imm16    Push sign-extended imm16. Stack pointer is incremented by the size of stack pointer.
	 * PUSH imm32    Push sign-extended imm32. Stack pointer is incremented by the size of stack pointer.
	 * Prefix Enable: Operand-Size
	 *
	 * 注:虽然白皮书上说“sign-extended”、“Stack pointer is incremented by the size of stack pointer”，但实际测试结果是
	 * 没有进行符号扩展，16位操作数模式下压入16位，32位操作数模式下压入32位。
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_68", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__sword swImmInt16;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, swImmInt16);
		__InternalPush_sWord__(pCPU, swImmInt16);

		pCPU->bOpcodeLength += 3;
	} else {
		__sdword sdwImmInt32;
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, sdwImmInt32);
		__InternalPush_sDword__(pCPU, sdwImmInt32);

		pCPU->bOpcodeLength += 5;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU))
		pCPU->InstructionInfomation.bInstructionLength += 3;
	else
		pCPU->InstructionInfomation.bInstructionLength += 5;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_6A(PCHAOSVM_CPU pCPU) {//[6A]
	/*
	 * PUSH imm8    Push sign-extended imm8. Stack pointer is incremented by the size of stack pointer.
	 * Prefix Enable: None
	 */

	__char bImmInt8;
	__sdword sdwImmInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_6A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bImmInt8);
	sdwImmInt32 = INT8_TO_INT32(bImmInt8);

	__InternalPush_sDword__(pCPU, sdwImmInt32);

	pCPU->bOpcodeLength += 2;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_50(PCHAOSVM_CPU pCPU) {
	// PUSH rAX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_50", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif
	
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_51(PCHAOSVM_CPU pCPU) {
	// PUSH rCX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_51", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_CX));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ECX));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_52(PCHAOSVM_CPU pCPU) {
	// PUSH rDX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_52", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DX));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDX));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_53(PCHAOSVM_CPU pCPU) {
	// PUSH rBX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_53", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BX));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBX));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_54(PCHAOSVM_CPU pCPU) {
	// PUSH rSP
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_54", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SP));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESP));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_55(PCHAOSVM_CPU pCPU) {
	// PUSH rBP
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_55", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_BP));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBP));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_56(PCHAOSVM_CPU pCPU) {
	// PUSH rSI
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_56", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_SI));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_ESI));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_57(PCHAOSVM_CPU pCPU) {
	// PUSH rDI
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_57", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_DI));
	} else {
		__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EDI));
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_ES(PCHAOSVM_CPU pCPU) {//[06]
	/*
	 * PUSH ES
	 * Length: 1
	 */

	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_ES", pCPU);
	__ExecuteInstBefore__(pCPU);
	dwInt32 = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_ES));
	__InternalPush_uDword__(pCPU, dwInt32);
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_CS(PCHAOSVM_CPU pCPU) {//[0E]
	/*
	 * PUSH CS
	 * Length: 1
	 */
	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_CS", pCPU);
	__ExecuteInstBefore__(pCPU);
	dwInt32 = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_CS));
	__InternalPush_uDword__(pCPU, dwInt32);
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_SS(PCHAOSVM_CPU pCPU) {//[16]
	/*
	 * PUSH SS
	 * Length: 1
	 */
	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_SS", pCPU);
	__ExecuteInstBefore__(pCPU);
	dwInt32 = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_SS));
	__InternalPush_uDword__(pCPU, dwInt32);
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSH_DS(PCHAOSVM_CPU pCPU) {//[1E]
	/*
	 * PUSH DS
	 * Length: 1
	 */

	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSH_DS", pCPU);
	__ExecuteInstBefore__(pCPU);
	dwInt32 = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_DS));
	__InternalPush_uDword__(pCPU, dwInt32);
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * POP指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_58(PCHAOSVM_CPU pCPU) {
	 // Pop rAX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_58", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_59(PCHAOSVM_CPU pCPU) {
	// Pop rCX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_59", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5A(PCHAOSVM_CPU pCPU) {
	// Pop rDX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5B(PCHAOSVM_CPU pCPU) {
	// Pop rBX
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5C(PCHAOSVM_CPU pCPU) {
	// Pop rSP
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_SP) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5D(PCHAOSVM_CPU pCPU) {
	// Pop rBP
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5D", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5E(PCHAOSVM_CPU pCPU) {
	// Pop rSI
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5E", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	* 填写指令信息
	*/
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_5F(PCHAOSVM_CPU pCPU) {
	// Pop rDI
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_5F", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16;
		__InternalPop_uWord__(pCPU, wInt16);
		__CPU_GR16__(pCPU, CHAOSVM_R_DI) = wInt16;
	} else {
		__dword dwInt32;
		__InternalPop_uDword__(pCPU, dwInt32);
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = dwInt32;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_ES(PCHAOSVM_CPU pCPU) {//[07]
	/*
	 * POP ES
	 * Length: 1
	 */

	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_ES", pCPU);
	__ExecuteInstBefore__(pCPU);
	__InternalPop_uDword__(pCPU, dwInt32);
	__CPU_SR__(pCPU, CHAOSVM_SR_ES) = __Low16__(dwInt32);
	pCPU->bOpcodeLength += 1;


#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
	pCPU->InstructionInfomation.AffectedRegister.bType = __CPU_INSTRUCTION_REG_TYPE_SR__;
	pCPU->InstructionInfomation.AffectedRegister.bIndex = CHAOSVM_SR_ES;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_SS(PCHAOSVM_CPU pCPU) {//[17]
	/*
	 * POP SS
	 * Length: 1
	 */

	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_SS", pCPU);
	__ExecuteInstBefore__(pCPU);
	__InternalPop_uDword__(pCPU, dwInt32);
	__CPU_SR__(pCPU, CHAOSVM_SR_SS) = __Low16__(dwInt32);
	pCPU->bOpcodeLength += 1;


#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
	pCPU->InstructionInfomation.AffectedRegister.bType = __CPU_INSTRUCTION_REG_TYPE_SR__;
	pCPU->InstructionInfomation.AffectedRegister.bIndex = CHAOSVM_SR_SS;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POP_DS(PCHAOSVM_CPU pCPU) {//[1F]
	/*
	 * POP DS
	 * Length: 1
	 */

	__dword dwInt32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POP_DS", pCPU);
	__ExecuteInstBefore__(pCPU);
	__InternalPop_uDword__(pCPU, dwInt32);
	__CPU_SR__(pCPU, CHAOSVM_SR_DS) = __Low16__(dwInt32);
	pCPU->bOpcodeLength += 1;


#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
	pCPU->InstructionInfomation.AffectedRegister.bType = __CPU_INSTRUCTION_REG_TYPE_SR__;
	pCPU->InstructionInfomation.AffectedRegister.bIndex = CHAOSVM_SR_DS;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * PUSHAD/POPAD指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSHAD_60(PCHAOSVM_CPU pCPU) {//[60]
	/* 
	 * PUSHAD   Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
	 */
	/*
	 * IF OperandSize = 32 (* PUSHAD instruction *)
	 * THEN
	 * Temp ← (ESP);
	 * Push(EAX);
	 * Push(ECX);
	 * Push(EDX);
	 * Push(EBX);
	 * Push(Temp);
	 * Push(EBP);
	 * Push(ESI);
	 * Push(EDI);
	 * ELSE (* OperandSize = 16, PUSHA instruction *)
	 * Temp ← (SP);
	 * Push(AX);
	 * Push(CX);
	 * Push(DX);
	 * Push(BX);
	 * Push(Temp);
	 * Push(BP);
	 * Push(SI);
	 * Push(DI);
	 * FI
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSHAD_60", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16StackBuffer[8];

		wInt16StackBuffer[7] = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		wInt16StackBuffer[6] = __CPU_GR16__(pCPU, CHAOSVM_R_CX);
		wInt16StackBuffer[5] = __CPU_GR16__(pCPU, CHAOSVM_R_DX);
		wInt16StackBuffer[4] = __CPU_GR16__(pCPU, CHAOSVM_R_BX);
		wInt16StackBuffer[3] = __CPU_GR16__(pCPU, CHAOSVM_R_SP);
		wInt16StackBuffer[2] = __CPU_GR16__(pCPU, CHAOSVM_R_BP);
		wInt16StackBuffer[1] = __CPU_GR16__(pCPU, CHAOSVM_R_SI);
		wInt16StackBuffer[0] = __CPU_GR16__(pCPU, CHAOSVM_R_DI);

		__MM_WRITE_BLOCK_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), (__CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 2*8), 2*8, (__byte *)(&wInt16StackBuffer[0]));
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 2*8;
	} else {
		__dword dwInt32StackBuffer[8];

		dwInt32StackBuffer[7] = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		dwInt32StackBuffer[6] = __CPU_GR32__(pCPU, CHAOSVM_R_ECX);
		dwInt32StackBuffer[5] = __CPU_GR32__(pCPU, CHAOSVM_R_EDX);
		dwInt32StackBuffer[4] = __CPU_GR32__(pCPU, CHAOSVM_R_EBX);
		dwInt32StackBuffer[3] = __CPU_GR32__(pCPU, CHAOSVM_R_ESP);
		dwInt32StackBuffer[2] = __CPU_GR32__(pCPU, CHAOSVM_R_EBP);
		dwInt32StackBuffer[1] = __CPU_GR32__(pCPU, CHAOSVM_R_ESI);
		dwInt32StackBuffer[0] = __CPU_GR32__(pCPU, CHAOSVM_R_EDI);

		__MM_WRITE_BLOCK_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), (__CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 4*8), 4*8, (__byte *)(&dwInt32StackBuffer[0]));
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 4*8;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POPAD_61(PCHAOSVM_CPU pCPU) {//[61]
	/* 
	 * POPAD   Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
	 */
	/*
	 * IF OperandSize = 32 (* Instruction = POPAD *)
	 * THEN
	 * EDI ← Pop();
	 * ESI ← Pop();
	 * EBP ← Pop();
	 * Increment ESP by 4; (* Skip next 4 bytes of stack *)
	 * EBX ← Pop();
	 * EDX ← Pop();
	 * ECX ← Pop();
	 * EAX ← Pop();
	 * ELSE (* OperandSize = 16, instruction = POPA *)
	 * DI ← Pop();
	 * SI ← Pop();
	 * BP ← Pop();
	 * Increment ESP by 2; (* Skip next 2 bytes of stack *)
	 * BX ← Pop();
	 * DX ← Pop();
	 * CX ← Pop();
	 * FI;
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POPAD_61", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16StackBuffer[8];

		__MM_READ_BLOCK_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), 2*8, (__byte *)(&wInt16StackBuffer[0]));

		__CPU_GR16__(pCPU, CHAOSVM_R_DI) = wInt16StackBuffer[0];
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) = wInt16StackBuffer[1];
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) = wInt16StackBuffer[2];
		//__CPU_GR16__(pCPU, CHAOSVM_R_SP) = wInt16StackBuffer[3];
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) = wInt16StackBuffer[4];
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = wInt16StackBuffer[5];
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) = wInt16StackBuffer[6];
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16StackBuffer[7];

		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 2*8;
	} else {
		__dword dwInt32StackBuffer[8];

		__MM_READ_BLOCK_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), 4*8, (__byte *)(&dwInt32StackBuffer[0]));

		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = dwInt32StackBuffer[0];
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = dwInt32StackBuffer[1];
		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = dwInt32StackBuffer[2];
		//__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = dwInt32StackBuffer[3];
		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = dwInt32StackBuffer[4];
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = dwInt32StackBuffer[5];
		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = dwInt32StackBuffer[6];
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32StackBuffer[7];

		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 4*8;
	}
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif

	__ExecuteInstAfter__(pCPU);
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_NOP_90(PCHAOSVM_CPU pCPU) {//[90]
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_NOP_90", pCPU);
	__ExecuteInstBefore__(pCPU);
	pCPU->bOpcodeLength += 1;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 条件跳转指令
 */
/*
 * 0x70;		Jcc;		Ib;			;	O;
 * 0x71;		Jcc;		Ib;			;	NO;
 * 0x72;		Jcc;		Ib;			;	B/NAE/C;
 * 0x73;		Jcc;		Ib;			;	NB/AE/NC;
 * 0x74;		Jcc;		Ib;			;	Z/E;
 * 0x75;		Jcc;		Ib;			;	NZ/NE;
 * 0x76;		Jcc;		Ib;			;	BE/NA;
 * 0x77;		Jcc;		Ib;			;	NBE/A;
 * 0x78;		Jcc;		Ib;			;	S;
 * 0x79;		Jcc;		Ib;			;	NS;
 * 0x7A;		Jcc;		Ib;			;	P/PE;
 * 0x7B;		Jcc;		Ib;			;	NP/PO;
 * 0x7C;		Jcc;		Ib;			;	L/NGE;
 * 0x7D;		Jcc;		Ib;			;	NL/GE;
 * 0x7E;		Jcc;		Ib;			;	LE/NG;
 * 0x7F;		Jcc;		Ib;			;	NLE/G;
 */
// 70
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_70(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_70", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 71
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_71(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_71", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[1].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 72
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_72(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_72", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[2].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 73
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_73(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_73", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[3].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 74
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_74(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_74", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[4].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}

	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	* 填写指令信息
	*/
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 75
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_75(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_75", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[5].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);

	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 76
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_76(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_76", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[6].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 77
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_77(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_77", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[7].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 78
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_78(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_78", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[8].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 79
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_79(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_79", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[9].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	* 填写指令信息
	*/
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7A
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7A(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7A", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0A].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	* 填写指令信息
	*/
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7B
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7B(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7B", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0B].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7C
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7C(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7C", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0C].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7D
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7D(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7D", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0D].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7E
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7E(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7E", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0E].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

// 7F
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Jcc_7F(PCHAOSVM_CPU pCPU) {
	__byte bCodeByte;
	__byte bRelOffset8;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_Jcc_7F", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bCodeByte);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	pCPU->bOpcodeLength += 2;

	if (pCPU->EFlagConditionTableEntry[0x0F].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * JMP指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_JMP_E9(PCHAOSVM_CPU pCPU) {//[E9]
	/*
	 * JMP rel16    Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.
	 * JMP rel32    Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits
	 * Prefix Enable: Operand-Size
	 * 0xE9;		JMP;		Jz;			JMP;	;
	 */
	CPU_STATUS Status;
	__address addrNewEIP;
	__word wRelOffset16;
	__dword dwRelOffset32;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_JMP_E9", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JMP_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wRelOffset16);
		pCPU->bOpcodeLength += 3;
		addrNewEIP = __CalculateJmpAddress_Offset_16Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, wRelOffset16);
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwRelOffset32);
		pCPU->bOpcodeLength += 5;
		addrNewEIP = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwRelOffset32);
	}

	Status = ChaosVmCpuInternalCallHookRoutineJmp(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), addrNewEIP, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEIP;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU))
		pCPU->InstructionInfomation.bInstructionLength += 3;
	else
		pCPU->InstructionInfomation.bInstructionLength += 5;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_JMP_EB(PCHAOSVM_CPU pCPU) {//[EB]
	/*
	 * JMP rel8    Jump short, RIP = RIP + 8-bit displacement sign extended to 64-bits
	 * Prefix Enable: None
	 * 0xEB;		JMP;		Jb;			JMP;	;
	 */
	__address addrNewEIP;
	CPU_STATUS Status;
	__byte bRelOffset8;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_JMP_EB", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bRelOffset8);

	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JMP_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	pCPU->bOpcodeLength += 2;
	addrNewEIP = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bRelOffset8);

	Status = ChaosVmCpuInternalCallHookRoutineJmp(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), addrNewEIP, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if(Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEIP;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 2;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * CALL指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_CALL_E8(PCHAOSVM_CPU pCPU) {//[E8]
	/*
	 * CALL rel16    Call near, relative, displacement relative to next instruction.
	 * CALL rel32    Call near, relative, displacement relative to next instruction. 32-bit displacement sign extended to 64-bits in 64-bit mode.
	 * Prefix Enable: Operand-Size
	 * 0xE8;		CALL;		Jz;			CALL;	;
	 */
	__word wRelOffset16;
	__dword dwRelOffset32;
	CPU_STATUS Status;
	__address addrNewEIP;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CALL_E8", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_CALL_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wRelOffset16);
		pCPU->bOpcodeLength += 3;
		addrNewEIP = __CalculateJmpAddress_Offset_16Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, wRelOffset16);
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwRelOffset32);
		pCPU->bOpcodeLength += 5;
		addrNewEIP = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwRelOffset32);
	}

	Status = ChaosVmCpuInternalCallHookRoutineCall(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), addrNewEIP, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 * EIP增加
		 */
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__InternalPushNextAsNearRetAddress__(pCPU, pCPU->bOpcodeLength);
		__CPU_EIP__(pCPU) = addrNewEIP;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU))
		pCPU->InstructionInfomation.bInstructionLength += 3;
	else
		pCPU->InstructionInfomation.bInstructionLength += 5;
#endif

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * RET指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_RET_C3(PCHAOSVM_CPU pCPU) {//[C3]
	/*
	 * RET    Near return to calling procedure.
	 */
	/*
	 * if( IS_INSTRUCTION_ADDRESS_MODE_16(pCPU) )
	 * {
	 * __word uInt16RetAddress;
	 * InternalPop_UINT16(pCPU, uInt16RetAddress);
	 * CPU_IP(pCPU) = uInt16RetAddress;
	 * } 
	 * else
	 * {
	 * UINT32 uInt32RetAddress;
	 * InternalPop_UINT32(pCPU, uInt32RetAddress);
	 * __CPU_EIP__(pCPU) = uInt32RetAddress;
	 * }
	 */
	CPU_STATUS Status;
	__dword dwInt32RetAddress;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_RET_C3", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_RET_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__InternalPop_uDword__(pCPU, dwInt32RetAddress);
	pCPU->bOpcodeLength += 1;

	Status = ChaosVmCpuInternalCallHookRoutineRet(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), dwInt32RetAddress, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 * 退出前重新将返回地址压入堆栈中,
		 */
		__InternalPush_uDword__(pCPU, dwInt32RetAddress);
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = dwInt32RetAddress;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.bInstructionLength += 1;
#endif
	
	__ExecuteInstAfter__(pCPU);
	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_RETN_C2(PCHAOSVM_CPU pCPU) {//[C2]
	/*
	 * RET imm16    Near return to calling procedure
	 */
	CPU_STATUS Status;
	__word wInt16Imm;
	__dword dwInt32RetAddress;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_RETN_C2", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_RET_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
	__InternalPop_uDword__(pCPU, dwInt32RetAddress);

	pCPU->bOpcodeLength += 3;

	Status = ChaosVmCpuInternalCallHookRoutineRet(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), dwInt32RetAddress, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 * 退出前平衡堆栈, 保证虚拟机退出之后,直接返回到压入的函数中
		 */
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) +=  wInt16Imm;
		__InternalPush_uDword__(pCPU, dwInt32RetAddress);
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = dwInt32RetAddress;
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) +=  wInt16Imm;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * LOOP指令
 */
/*
 * 0xE0;		LOOPNE;		Jb;			LOOPNE;	LOOPNZ;
 * 0xE1;		LOOPE;		Jb;			LOOPE;	LOOPZ;
 * 0xE2;		LOOP;		Jb;			LOOP;	LOOP;
 * 0xE3;		JrCXZ;		Jb;			JrCXZ;	Jump short if RCX register is 0.JECXZ rel8 Valid Valid Jump short if ECX register is 0.;
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_LOOPE_E0(PCHAOSVM_CPU pCPU) {//[E0]
	/* 
	 * LOOPE Decrement count; jump short if count ≠ 0 and ZF = 0.
	 */
	CPU_STATUS Status;
	__byte bInt8RelOffset;
	__address addrNewEip;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LOOPE_E0", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8RelOffset);

	__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
	pCPU->bOpcodeLength += 2;
	if ((0 != __CPU_GR32__(pCPU, CHAOSVM_R_ECX) ) && (0 == __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF))) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bInt8RelOffset);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_LOOPNE_E1(PCHAOSVM_CPU pCPU) {//[E1]
	/* 
	 * LOOPNE  Decrement count; jump short if count ≠ 0 and ZF = 1.
	 */
	CPU_STATUS Status;
	__byte bInt8RelOffset;
	__address addrNewEip;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LOOPNE_E1", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8RelOffset);


	__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
	pCPU->bOpcodeLength += 2;
	if ((0 != __CPU_GR32__(pCPU, CHAOSVM_R_ECX) ) && ( 1 == __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF))) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bInt8RelOffset);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_LOOP_E2(PCHAOSVM_CPU pCPU) {//[E2]
	/* 
	 * LOOP  Decrement count; jump short if count ≠ 0.
	 */
	CPU_STATUS Status;
	__byte bInt8RelOffset;
	__address addrNewEip;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LOOP_E2", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8RelOffset);

	__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
	pCPU->bOpcodeLength += 2;
	if (0 != __CPU_GR32__(pCPU, CHAOSVM_R_ECX)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bInt8RelOffset);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_JRCXZ_E3(PCHAOSVM_CPU pCPU) {//[E3]
	/* 
	 * JRCXZ   Jump short if RCX register is 0.
	 */
	CPU_STATUS Status;
	__byte bInt8RelOffset;
	__address addrNewEip;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_JRCXZ_E3", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8RelOffset);

	pCPU->bOpcodeLength += 2;
	if (0 == __CPU_GR32__(pCPU, CHAOSVM_R_ECX)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_8Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, bInt8RelOffset);
		bGoto = TRUE;
	} else {
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	}
	addrNewEip = __CPU_EIP__(pCPU);
	if (bGoto)
		Status = ChaosVmCpuInternalCallHookRoutineJcc(pCPU, addrNewEip, pCPU->bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;

	// 从返回状态判断执行流程
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 */
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if (Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = addrNewEip;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * CLC STC CLI STI CLD STD 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_CLC_F8(PCHAOSVM_CPU pCPU) {//[F8]
	/* 
	 * CLC
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CLC_F8", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_STC_F9(PCHAOSVM_CPU pCPU) {//[F9]
	/* 
	 * STC
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_STC_F9", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CLI_FA(PCHAOSVM_CPU pCPU) {//[FA]
	/* 
	 * CLI 
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CLI_FA", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_IF, __EFLAG_RESET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_STI_FB(PCHAOSVM_CPU pCPU) {//[FB]
	/*
	 * STI 
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_STI_FB", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_IF, __EFLAG_SET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CLD_FC(PCHAOSVM_CPU pCPU) {//[FC]
	/* 
	 * CLD 
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CLD_FC", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_DF, __EFLAG_RESET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_STD_FD(PCHAOSVM_CPU pCPU) {//[FD]
	/*
	 * STD
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_STD_FD", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_DF, __EFLAG_SET__);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 符号扩展指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_CWDE_98(PCHAOSVM_CPU pCPU) {//[98]
	/*
	 * CBW    AX ← sign-extend of AL.
	 * CWDE   EAX ← sign-extend of AX.
	 */
	/*
	 * IF OperandSize = 16 (* Instruction = CBW *)
	 * THEN
	 * AX ← SignExtend(AL);
	 * ELSE IF (OperandSize = 32, Instruction = CWDE)
	 * EAX ← SignExtend(AX); FI;
	 * FI;
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CWDE_98", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = INT16_TO_UINT16(INT8_TO_INT16(__CPU_GR8__(pCPU, CHAOSVM_R_AL)));
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = INT32_TO_UINT32(INT16_TO_INT32( __CPU_GR16__(pCPU, CHAOSVM_R_AX)));	
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CDQ_99(PCHAOSVM_CPU pCPU) {//[99]
	/*
	 * CWD  DX:AX ← sign-extend of AX.
	 * CDQ  EDX:EAX ← sign-extend of EAX.
	 */
	/*
	 * IF OperandSize = 16 (* CWD instruction *)
	 * THEN
	 * DX ← SignExtend(AX);
	 * ELSE IF OperandSize = 32 (* CDQ instruction *)
	 * EDX ← SignExtend(EAX); FI;
	 * FI;
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CDQ_99", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__sdword sdwInt32Tmp;
		sdwInt32Tmp = INT16_TO_INT32(UINT16_TO_INT16(__CPU_GR16__(pCPU, CHAOSVM_R_AX)));
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = __High16__(INT32_TO_UINT32(sdwInt32Tmp));
	} else {
		__sqword sqwInt64Tmp;
		sqwInt64Tmp = INT32_TO_INT64( UINT32_TO_INT32(__CPU_GR32__(pCPU, CHAOSVM_R_EAX)));
		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = __High32__(INT64_TO_UINT64(sqwInt64Tmp));
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * PUSHF/POPF 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_PUSHFD_9C(PCHAOSVM_CPU pCPU) {//[9C]
	/*
	 * PUSHF    Push lower 16 bits of EFLAGS.
	 * PUSHFD   Push EFLAGS.
	 */

	__dword dwInt32EFlags;
	__word wInt16EFlags;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_PUSHFD_9C", pCPU);
	__ExecuteInstBefore__(pCPU);
	dwInt32EFlags = ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF) & 0x1) << __EFLAG_INDEX_CF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_PF)) & 0x1) << __EFLAG_INDEX_PF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF)) & 0x1) << __EFLAG_INDEX_AF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF)) & 0x1) << __EFLAG_INDEX_ZF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF)) & 0x1) << __EFLAG_INDEX_SF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_TF)) & 0x1) << __EFLAG_INDEX_TF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_IF)) & 0x1) << __EFLAG_INDEX_IF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF)) & 0x1) << __EFLAG_INDEX_DF__)
		| ((UINT8_TO_UINT32(__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF)) & 0x1) << __EFLAG_INDEX_OF__)
		| __EFLAG_OR_MASK__;

	wInt16EFlags = UINT32_TO_UINT16(dwInt32EFlags);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPush_uWord__(pCPU, wInt16EFlags);
	} else {
		__InternalPush_uDword__(pCPU, dwInt32EFlags);
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_POPFD_9D(PCHAOSVM_CPU pCPU) {//[9D]
	/*
	 * POPF    Pop top of stack into lower 16 bits of EFLAGS.
	 * POPF    Pop top of stack into EFLAGS.
	 */

	__word wInt16EFlags = 0;
	__dword dwInt32EFlags = 0;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_POPFD_9D", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__InternalPop_uWord__(pCPU, wInt16EFlags);
		dwInt32EFlags = UINT16_TO_UINT32(wInt16EFlags);
	} else {
		__InternalPop_uDword__(pCPU, dwInt32EFlags);
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_CF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_PF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_AF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_ZF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_SF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_TF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_TF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_IF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_IF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_DF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_DF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, UINT32_TO_UINT8((dwInt32EFlags >> __EFLAG_INDEX_OF__) & 0x1));

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * ENTER/LEAVE指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_ENTER_C8(PCHAOSVM_CPU pCPU) {//[C8]
	/*
	 * 此处只处理 ENTER imm16, 0 的情况
	 * ENTER imm16, 0    Create a stack frame for a procedure.
	 *
	 * PUSH EBP
	 * MOV EBP,ESP
	 * SUB ESP,imm16
	 */

	__word wInt16Imm;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_ENTER_C8", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16Imm);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 3, bInt8Imm);

	if (bInt8Imm) {
		/*
		 * ENTER第2个参数不为0
		 */
		__CPU_DBG_OUTPUT__(pCPU, "%08X  Warning: ENTER Instruction Fault\n", __CPU_EIP__(pCPU));
	}

	__InternalPush_uDword__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EBP));
	__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = __CPU_GR32__(pCPU, CHAOSVM_R_ESP);
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= wInt16Imm;

	pCPU->bOpcodeLength += 4;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_LEAVE_C9(PCHAOSVM_CPU pCPU) {//[C9]
	/*
	 * 此处只处理 ENTER imm16, 0 的情况
	 * LEAVE    Set ESP to EBP, then pop EBP.
	 *
	 * MOV ESP,EBP
	 * POP EBP
	 */
	__dword dwInt32OldEBP;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LEAVE_C9", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = __CPU_GR32__(pCPU, CHAOSVM_R_EBP);
	__InternalPop_uDword__(pCPU, dwInt32OldEBP);
	__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = dwInt32OldEBP;

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * INT 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_INT3_CC(PCHAOSVM_CPU pCPU) {//[CC]
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INT3_CC", pCPU);
	__ExecuteInstBefore__(pCPU);
	pCPU->InterruptInfomation.bInterruptId = 3;
	pCPU->InterruptInfomation.dwErrorCode = 0;
	pCPU->bOpcodeLength += 1;

	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_INT__);
	__CPU_SET_INTERRUPT_OCCUR__(pCPU);

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_INTERRRUPT_OCCUR__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INT_CD(PCHAOSVM_CPU pCPU) {//[CD]
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INT_CD", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8Imm);

	pCPU->InterruptInfomation.bInterruptId = bInt8Imm;
	pCPU->InterruptInfomation.dwErrorCode = 0;
	pCPU->bOpcodeLength += 2;

	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_INT__);
	__CPU_SET_INTERRUPT_OCCUR__(pCPU);

	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_INTERRRUPT_OCCUR__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_INTO_CE(PCHAOSVM_CPU pCPU) {//[CE]
	/*
	 * INTO             Interrupt 4—if overflow flag is 1.
	 */
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_INTO_CE", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF) == __EFLAG_SET__) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_OF__;
		pCPU->InterruptInfomation.dwErrorCode = 0;

		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_INT__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		Status = __CPU_STATUS_INTERRRUPT_OCCUR__;
	}
	pCPU->bOpcodeLength += 1;

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * LEA 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_LEA_8D(PCHAOSVM_CPU pCPU) {//[8D]
	/*
	 * LEA r16,m     Store effective address for m in register r16.
	 * LEA r32,m     Store effective address for m in register r32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LEA_8D", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		__ExecuteInstAfter__(pCPU);
		return __CPU_STATUS_INVALID_OPCODE__;
	}

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, Args.bRegOpcode) = __Low16__(Args.EffectiveAddress.addrAddress);
	} else {
		__CPU_GR32__(pCPU, Args.bRegOpcode) = Args.EffectiveAddress.addrAddress;
	}
	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * XCHG 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_86(PCHAOSVM_CPU pCPU) {//[86]
	/*
	 * 86   XCHG r8, r/m8       Exchange byte from r/m8 with r8 (byte register).
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_86", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (Args.bIsEAReg) {
		__byte bInt8SwapTmp;
		bInt8SwapTmp = __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex);
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, bInt8SwapTmp);
	} else {
		__byte bInt8Value;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Value);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR8_GET__(pCPU, Args.bRegOpcode));
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, bInt8Value);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_87(PCHAOSVM_CPU pCPU) {//[87]
	/*
	 * XCHG r/m16, r16           Exchange r16 with word from r/m16.
	 * XCHG r16, r/m16           Exchange word from r/m16 with r16.
	 * XCHG r/m32, r32           Exchange r32 with doubleword from r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_87", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		if (Args.bIsEAReg) {
			wInt16SwapTmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = __CPU_GR16__(pCPU, Args.bRegOpcode);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = wInt16SwapTmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16SwapTmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__CPU_GR16__(pCPU, Args.bRegOpcode) = wInt16SwapTmp;
		}
	} else {
		__dword dwInt32SwapTmp;
		if (Args.bIsEAReg) {
			dwInt32SwapTmp = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = __CPU_GR32__(pCPU, Args.bRegOpcode);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = dwInt32SwapTmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32SwapTmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__CPU_GR32__(pCPU, Args.bRegOpcode) = dwInt32SwapTmp;
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RCX_91(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rCX
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RCX_91", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_CX);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_ECX);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RDX_92(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rDX
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RDX_92", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_DX);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_EDX);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RBX_93(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rBX
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RBX_93", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_BX);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_EBX);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RSP_94(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rSP
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RSP_94", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_SP);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_ESP);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RBP_95(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rBP
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RBP_95", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_BP);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_EBP);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RSI_96(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rSI
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RSI_96", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_SI);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_ESI);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_XCHG_RAX_RDI_97(PCHAOSVM_CPU pCPU) {
	/*
	 * XCHG rAX,rDI
	 */
	/*
	 * XCHG AX, r16    Exchange r16 with AX.
	 * XCHG r16, AX    Exchange AX with r16.
	 * XCHG EAX, r32   Exchange r32 with EAX.
	 */

	__byte bInt8CodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XCHG_RAX_RDI_97", pCPU);
	__ExecuteInstBefore__(pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16SwapTmp;
		wInt16SwapTmp = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __CPU_GR16__(pCPU, CHAOSVM_R_DI);
		__CPU_GR16__(pCPU, bInt8CodeByte & 0x7) = wInt16SwapTmp;
	} else {
		__dword dwInt32SwapTmp;
		dwInt32SwapTmp = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __CPU_GR32__(pCPU, CHAOSVM_R_EDI);
		__CPU_GR32__(pCPU, bInt8CodeByte & 0x7) = dwInt32SwapTmp;
	}

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * LAHF/SAHF 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_LAHF_9F(PCHAOSVM_CPU pCPU) {//[9F]
	/*
	 * LAHF      Load: AH ←EFLAGS(SF:ZF:0:AF:0:PF:1:CF).
	 *
	 * Description
	 * Moves the low byte of the EFLAGS register (which includes status flags SF, ZF, AF, PF, and
	 * CF) to the AH register. Reserved bits 1, 3, and 5 of the EFLAGS register are set in the AH
	 * register as shown in the “Operation” section below.
	 *
	 * Operation
	 * AH ← EFLAGS(SF:ZF:0:AF:0:PF:1:CF);
	 */
	__byte bInt8EFlags;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LAHF_9F", pCPU);
	__ExecuteInstBefore__(pCPU);
	bInt8EFlags =  
		((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF) & 0x1) << __EFLAG_INDEX_CF__)
		| ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_PF) & 0x1) << __EFLAG_INDEX_PF__)
		| ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_AF) & 0x1) << __EFLAG_INDEX_AF__)
		| ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) & 0x1) << __EFLAG_INDEX_ZF__)
		| ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) & 0x1) << __EFLAG_INDEX_SF__)
		| __EFLAG_OR_MASK__;

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, bInt8EFlags);

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SAHF_9E(PCHAOSVM_CPU pCPU) {//[9E]
	/*
	 * SAHF    Loads SF, ZF, AF, PF, and CF from AH into EFLAGS register.
	 *
	 * Description
	 * Loads the SF, ZF, AF, PF, and CF flags of the EFLAGS register with values from the corresponding
	 * bits in the AH register (bits 7, 6, 4, 2, and 0, respectively). Bits 1, 3, and 5 of register
	 * AH are ignored; the corresponding reserved bits (1, 3, and 5) in the EFLAGS register remain as
	 * shown in the “Operation” section below.
	 * 
	 * Operation
	 * RFLAGS(SF:ZF:0:AF:0:PF:1:CF) ← AH;
	 */
	__byte bInt8EFlags;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SAHF_9E", pCPU);
	__ExecuteInstBefore__(pCPU);
	bInt8EFlags = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AH);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((bInt8EFlags >> __EFLAG_INDEX_CF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, ((bInt8EFlags >> __EFLAG_INDEX_PF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, ((bInt8EFlags >> __EFLAG_INDEX_AF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, ((bInt8EFlags >> __EFLAG_INDEX_ZF__) & 0x1));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, ((bInt8EFlags >> __EFLAG_INDEX_SF__) & 0x1));

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncOne_XLAT_D7(PCHAOSVM_CPU pCPU) {//[D7]
	/*
	 * XLATB           Set AL to memory byte DS:[(E)BX + unsigned AL].
	 */
	__byte bInt8Tmp;
	__dword dwInt32Address;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_XLAT_D7", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Address;
		wInt16Address = __CPU_GR16__(pCPU, CHAOSVM_R_BX) + UINT8_TO_UINT16(__CPU_GR8_AL__(pCPU) );
		dwInt32Address = UINT16_TO_UINT32(wInt16Address);
	} else {
		dwInt32Address = __CPU_GR32__(pCPU, CHAOSVM_R_EBX) + UINT8_TO_UINT32(__CPU_GR8_AL__(pCPU));
	}
	__MM_READ_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_DS), dwInt32Address, bInt8Tmp);
	__CPU_GR8_AL__(pCPU) = bInt8Tmp;

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SALC_D6(PCHAOSVM_CPU pCPU) {//[D6]
	/*
	 * SALC          An undocumented op code
	 *
	 * this instruction sets AL=FF if the Carry Flag is set (CF=1), or resets AL=00 if the Carry Flag is clear (CF=0). 
	 * SALC doesn't change any flags,
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SALC_D6", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_GR8_AL__(pCPU) = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF) == __EFLAG_SET__) ? (0xFF) : 0;

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMC_F5(PCHAOSVM_CPU pCPU) {//[F5]
	/*
	 * CMC      Complement CF flag.
	 *
	 * Operation
	 * EFLAGS.CF[bit 0]← NOT EFLAGS.CF[bit 0];
	 * Flags Affected
	 * The CF flag contains the complement of its original value. The OF, ZF, SF, AF, and PF flags are unaffected.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMC_F5", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF) == __EFLAG_SET__) ? __EFLAG_RESET__ : __EFLAG_SET__ ));

	pCPU->bOpcodeLength += 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 2字节指令(0FXX)解析入口
 */
CPU_STATUS __INTERNAL_FUNC__ FuncOne_Two_MainDispatch(PCHAOSVM_CPU pCPU) {//[0F]
	__byte bInt8CodeByte;
	CPU_STATUS Status;

	__ExecuteInstBefore__(pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	pCPU->bOpcodeLength++;
	bInt8CodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	Status = pCPU->TwoByteOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);
	__ExecuteInstAfter__(pCPU);
	return Status;
}


