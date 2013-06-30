CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_ES(PCHAOSVM_CPU pCPU) {//[26]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_ES", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_ES;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_ES__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_CS(PCHAOSVM_CPU pCPU) {//[2E]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_CS", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_CS;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_CS__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_SS(PCHAOSVM_CPU pCPU) {//[36]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_SS", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_SS;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_SS__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_DS(PCHAOSVM_CPU pCPU) {//[3E]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_DS", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_DS;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_DS__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_FS(PCHAOSVM_CPU pCPU) {//[64]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_FS", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_FS;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_FS__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_FuncOne_Prefix_Segment_GS(PCHAOSVM_CPU pCPU) {//[65]
	__byte bPrefixByte;
	__byte bCodeByte;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_FuncOne_Prefix_Segment_GS", pCPU);
	/*
	 * 指向机器码下一个字节
	 */
	bPrefixByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];
	pCPU->bOpcodeLength++;
	bCodeByte = pCPU->OpcodeBuffer[pCPU->bOpcodeLength];

	/*
	 * 设置前缀标志
	 */
	pCPU->bDataSegmentRegister = CHAOSVM_SR_GS;

#if defined(__USE_INSTRUCTION_INFORMATION__)
	/*
	 * 填写指令信息
	 */
	pCPU->InstructionInfomation.wPrefix = __CPU_INSTRUCTION_PREFIX_SEGMENTOVERRIDE_GS__;
	pCPU->InstructionInfomation.bPrefixLength++;
	pCPU->InstructionInfomation.bInstructionLength++;
#endif

	return pCPU->OneOpcodeTableEntry[bCodeByte].DispatchFunction(pCPU);
}