/*
 * 2字节指令(0F XX)
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_UnImplement(PCHAOSVM_CPU pCPU) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_UnImplement", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  0F%02X\n", __CPU_EIP__(pCPU), pCPU->OpcodeBuffer[pCPU->bOpcodeLength]);
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncTwo_IncorrectOpcode007F(PCHAOSVM_CPU pCPU) {//[04,24,25,26,27,36,37,0A,0C,0E,0F,19,1A,1B,1C,1D,1E,39,3B,3C,3D,3E,3F,7A,7B,A6,A7,B8,FF]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_IncorrectOpcode007F", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	return __CPU_STATUS_INVALID_OPCODE__;
}

/*
 * 控制寄存器操作指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F20(PCHAOSVM_CPU pCPU) {//[20]
	/*
	 * MOV Rd,Cd
	 *
	 * MOV r32,CR0    Move CR0 to r32.
	 * MOV r32,CR2    Move CR2 to r32.
	 * MOV r32,CR3    Move CR3 to r32.
	 * MOV r32,CR4    Move CR4 to r32.
	 *
	 * R   The R/M field of the ModR/M byte may refer only to a general register
	 * C   The reg field of the ModR/M byte selects a control register
	 * d   Doubleword,regardless of operand-size attribute
	 */
	__byte bInt8ModRMByte;
	__byte bInt8GR32Index;
	__byte bInt8CRIndex;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F20", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8ModRMByte);

	bInt8GR32Index = bInt8ModRMByte & 0x7;
	bInt8CRIndex = (bInt8ModRMByte >> 3) & 0x7;

	/*
	 * 不具体实现
	 */

	pCPU->bOpcodeLength += 2;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F22(PCHAOSVM_CPU pCPU) {//[22]
	/*
	 * MOV Cd,Rd
	 *
	 * MOV CR0,r32    Move r32 to CR0.
	 * MOV CR2,r32    Move r32 to CR2.
	 * MOV CR3,r32    Move r32 to CR3.
	 * MOV CR4,r32    Move r32 to CR4.
	 *
	 * R   The R/M field of the ModR/M byte may refer only to a general register
	 * C   The reg field of the ModR/M byte selects a control register
	 * d   Doubleword,regardless of operand-size attribute
	 */
	__byte bInt8ModRMByte;
	__byte bInt8GR32Index;
	__byte bInt8CRIndex;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F22", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8ModRMByte);

	bInt8GR32Index = bInt8ModRMByte & 0x7;
	bInt8CRIndex = (bInt8ModRMByte >> 3) & 0x7;

	/*
	 * 不具体实现
	 */

	pCPU->bOpcodeLength += 2;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

/*
 * 调试寄存器操作指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F21(PCHAOSVM_CPU pCPU) {//[21]
	/*
	 * MOV Rd,Dd
	 *
	 * MOV r32, DR0-DR7    Move debug register to r32
	 *
	 * R   The R/M field of the ModR/M byte may refer only to a general register
	 * D   The reg field of the ModR/M byte selects debug control register
	 * d   Doubleword,regardless of operand-size attribute
	 */
	__byte bInt8ModRMByte;
	__byte bInt8GR32Index;
	__byte bInt8DRIndex;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F21", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8ModRMByte);

	bInt8GR32Index = bInt8ModRMByte & 0x7;
	bInt8DRIndex = (bInt8ModRMByte >> 3) & 0x7;

	/*
	 * 不具体实现
	 */

	pCPU->bOpcodeLength += 2;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F23(PCHAOSVM_CPU pCPU) {//[23]
	/*
	 * MOV Dd,Rd
	 *
	 * MOV DR0-DR7,r32    Move r32 to debug register
	 *
	 * R   The R/M field of the ModR/M byte may refer only to a general register
	 * D   The reg field of the ModR/M byte selects debug control register
	 * d   Doubleword,regardless of operand-size attribute
	 */
	__byte bInt8ModRMByte;
	__byte bInt8GR32Index;
	__byte bInt8DRIndex;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F23", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1, bInt8ModRMByte);

	bInt8GR32Index = bInt8ModRMByte & 0x7;
	bInt8DRIndex = (bInt8ModRMByte >> 3) & 0x7;

	/*
	 * 不具体实现
	 */

	pCPU->bOpcodeLength += 2;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}
/*
 * 条件跳转指令
 */
// 80
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_80(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_80", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 81
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_81(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_81", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[1].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 82
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_82(PCHAOSVM_CPU pCPU) {
	/*
	* Jcc  Jz                    Long displacement jump on condition;
	* Prefix Enable: Operand-Size
	*/

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_82", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[2].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 83
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_83(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_83", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[3].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 84
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_84(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_84", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[4].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 85
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_85(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_85", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[5].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 86
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_86(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_86", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[6].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 87
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_87(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_87", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[7].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 88
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_88(PCHAOSVM_CPU pCPU) {
	/*
	* Jcc  Jz                    Long displacement jump on condition;
	* Prefix Enable: Operand-Size
	*/

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_88", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[8].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 89
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_89(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_89", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[9].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8A
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8A(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8A", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0A].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8B
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8B(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8B", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0B].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8C
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8C(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8C", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0C].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8D
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8D(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8D", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0D].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8E
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8E(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8E", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0E].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

// 8F
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_Jcc_Long_8F(PCHAOSVM_CPU pCPU) {
	/*
	 * Jcc  Jz                    Long displacement jump on condition;
	 * Prefix Enable: Operand-Size
	 */

	__dword dwInt32RelOffset;
	__byte bInt8CodeByte;
	__address addrNewEip;
	CPU_STATUS Status;
	__bool bGoto = FALSE;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_Jcc_Long_8F", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JCC_FAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16RelOffset;
		__READ_DATA_INT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1, wInt16RelOffset);
		dwInt32RelOffset = UINT16_TO_UINT32(wInt16RelOffset);
		pCPU->bOpcodeLength += 1 + 2;
		bGoto = TRUE;
	} else {
		__READ_DATA_INT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1, dwInt32RelOffset);
		pCPU->bOpcodeLength += 1 + 4;
	}

	if (pCPU->EFlagConditionTableEntry[0x0F].FlagTest(pCPU)) {
		__CPU_EIP__(pCPU) = __CalculateJmpAddress_Offset_32Bits__(__CPU_EIP__(pCPU), pCPU->bOpcodeLength, dwInt32RelOffset);
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

	return Status;
}

/*
 * 条件置位指令
 */
// 90
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_90(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_90", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 91
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_91(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_91", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[1].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 92
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_92(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_92", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[2].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 93
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_93(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_93", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[3].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 94
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_94(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_94", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[4].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 95
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_95(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_95", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[5].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 96
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_96(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_96", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[6].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 97
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_97(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_97", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[7].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 98
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_98(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_98", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[8].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 99
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_99(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_99", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[9].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9A
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9A(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9A", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0A].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9B
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9B(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9B", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0B].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9C
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9C(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9C", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0C].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9D
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9D(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9D", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0D].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9E
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9E(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9E", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0E].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// 9F
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SETcc_9F(PCHAOSVM_CPU pCPU) {
	/*
	 * SETcc  Set Byte on Condition;
	 * Prefix Enable: Address-Size
	 *
	 * Sets the destination operand to 0 or 1 depending on the settings of the status flags (CF, SF, OF,
	 * ZF, and PF) in the EFLAGS register. The destination operand points to a byte register or a byte
	 * in memory. The condition code suffix (cc) indicates the condition being tested for.
	 *
	 */
	__byte bInt8CodeByte;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SETcc_9F", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (pCPU->EFlagConditionTableEntry[0x0F].FlagTest(pCPU)) {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 1);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 1);
		}
	} else {
		if (Args.bIsEAReg) {
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, 0);
		} else {
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, 0);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * PUSH/POP  FS/GS 指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_PUSH_FS_0FA0(PCHAOSVM_CPU pCPU) {//[A0]
	/*
	 * PUSH FS
	 */
	__dword dwInt32Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_PUSH_FS_0FA0", pCPU);
	dwInt32Tmp = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_FS));
	__InternalPush_uDword__(pCPU, dwInt32Tmp);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_POP_FS_0FA1(PCHAOSVM_CPU pCPU) {//[A1]
	/*
	 * PUSH FS
	 */
	__dword dwInt32Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_POP_FS_0FA1", pCPU);
	__InternalPop_uDword__(pCPU, dwInt32Tmp);
	__CPU_SR__(pCPU, CHAOSVM_SR_FS) = __Low16__(dwInt32Tmp);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_PUSH_GS_0FA8(PCHAOSVM_CPU pCPU) {//[A8]
	/*
	 * PUSH GS
	 */
	__dword dwInt32Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_PUSH_GS_0FA8", pCPU);
	dwInt32Tmp = UINT16_TO_UINT32(__CPU_SR__(pCPU, CHAOSVM_SR_GS));
	__InternalPush_uDword__(pCPU, dwInt32Tmp);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_POP_GS_0FA9(PCHAOSVM_CPU pCPU) {//[A9]
	/*
	 *PUSH GS
	 */
	__dword dwInt32Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_POP_GS_0FA9", pCPU);
	__InternalPop_uDword__(pCPU, dwInt32Tmp);
	__CPU_SR__(pCPU, CHAOSVM_SR_GS) = __Low16__(dwInt32Tmp);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * MOVZX/MOVSX  指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOVZX_0FB6(PCHAOSVM_CPU pCPU) {//[B6]
	/*
	 * MOVZX r16, r/m8    Move byte to word with zeroextension.
	 * MOVZX r32, r/m8    Move byte to doubleword, zeroextension
	 *
	 * Prefix Enable: OperandSize,Address-Size
	 */
	__byte bInt8Tmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOVZX_0FB6", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (Args.bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, Args.bRegOpcode) = UINT8_TO_UINT16(bInt8Tmp);
	} else {
		__CPU_GR32__(pCPU, Args.bRegOpcode) = UINT8_TO_UINT32(bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOVZX_0FB7(PCHAOSVM_CPU pCPU) {//[B7]
	/*
	 * MOVZX r32, r/m16 Valid Valid Move word to doubleword, zero-extension.
	 *
	 * Prefix Enable: Address-Size
	 */
	__word bInt16Tmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOVZX_0FB7", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		bInt16Tmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
	} else {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
	}
	__CPU_GR32__(pCPU, Args.bRegOpcode) = UINT16_TO_UINT32(bInt16Tmp);

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOVSX_0FBE(PCHAOSVM_CPU pCPU) {//[BE]
	/*
	 * MOVSX r16, r/m8    Move byte to word with signextension.
	 * MOVSX r32, r/m8    Move byte to doubleword with sign-extension.
	 *
	 * Prefix Enable: OperandSize,Address-Size
	 */
	__char bInt8Tmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOVSX_0FBE", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (Args.bIsEAReg) {
		bInt8Tmp = UINT8_TO_INT8(__CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex));
	} else {
		__MM_READ_INT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8Tmp);
	}

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__CPU_GR16__(pCPU, Args.bRegOpcode) = INT16_TO_UINT16( INT8_TO_INT16(bInt8Tmp));
	} else {
		__CPU_GR32__(pCPU, Args.bRegOpcode) = INT32_TO_UINT32( INT8_TO_INT32(bInt8Tmp));
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOVSX_0FBF(PCHAOSVM_CPU pCPU) {//[BF]
	/*
	 * MOVSX r32, r/m16    Move word to doubleword, with sign-extension.
	 *
	 * Prefix Enable: Address-Size
	 */
	__sword swInt16Tmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOVSX_0FBF", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (Args.bIsEAReg) {
		swInt16Tmp = UINT16_TO_INT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
	} else {
		__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, swInt16Tmp);
	}

	__CPU_GR32__(pCPU, Args.bRegOpcode) = INT32_TO_UINT32(INT16_TO_INT32(swInt16Tmp));

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * BTX指令
 */
/*
 * BT(bit test)指令选择第一个操作数的第n位并将其拷贝到进位标志中。
 * BTS(bit test and set)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将第n位置位。
 * BTR(bit test and reset)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将第n位清零。
 * BTC(bit test and complement)指令选择第一个操作数的第n位并将其拷贝到进位标志中，同时将这个数据位取反。
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BT_0FA3(PCHAOSVM_CPU pCPU) {//[A3]
	/*
	 * BT r/m16, r16   Store selected bit in CF flag.
	 * BT r/m32, r32   Store selected bit in CF flag.
	 * Prefix Enable: Operand-Size,Address-Size
	 *
	 * Comment: Selects the bit in a bit string (specified with the first operand, called the bit base) 
	 * at the bitposition designated by the bit offset (specified by the second operand) and 
	 * stores the value of the bit in the CF flag.
	 */
	__byte bInt8BitTmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BT_0FA3", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));						
		} else {
			__word bInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
			bInt8BitTmp = GET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
		}
	} else {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));						
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BTR_0FB3(PCHAOSVM_CPU pCPU) {//[B3]
	/*
	 * BTR r/m16, r16    Store selected bit in CF flag and clear.
	 * BTR r/m32, r32    Store selected bit in CF flag and clear.
	 */
	__byte bInt8BitTmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BTR_0FB3", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = RESET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));					
		} else {
			__word bInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
			bInt8BitTmp = GET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			bInt16Tmp = RESET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = RESET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));					
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			dwInt32Tmp = RESET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BTS_0FAB(PCHAOSVM_CPU pCPU) {//[AB]
	/*
	 * BTS r/m16, r16    Store selected bit in CF flag and set.
	 * BTS r/m32, r32    Store selected bit in CF flag and set.
	 */
	__byte bInt8BitTmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BTS_0FAB", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = SET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));					
		} else {
			__word bInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
			bInt8BitTmp = GET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			bInt16Tmp = SET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = SET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));					
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			dwInt32Tmp = SET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BTC_0FBB(PCHAOSVM_CPU pCPU) {//[BB]
	/*
	 * BTC r/m16, r16    Store selected bit in CF flag and complement.
	 * BTC r/m32, r32    Store selected bit in CF flag and complement.
	 */
	__byte bInt8BitTmp;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BTC_0FBB", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = COMPLEMENT_BIT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR16__(pCPU, Args.bRegOpcode));					
		} else {
			__word bInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
			bInt8BitTmp = GET_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			bInt16Tmp = COMPLEMENT_BIT16(bInt16Tmp, __CPU_GR16__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt16Tmp);
		}
	} else {
		if (Args.bIsEAReg) {
			bInt8BitTmp = GET_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = COMPLEMENT_BIT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex), __CPU_GR32__(pCPU, Args.bRegOpcode));					
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
			bInt8BitTmp = GET_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			dwInt32Tmp = COMPLEMENT_BIT32(dwInt32Tmp, __CPU_GR32__(pCPU, Args.bRegOpcode));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, (bInt8BitTmp ? __EFLAG_SET__ : __EFLAG_RESET__));

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_IMUL_0FAF(PCHAOSVM_CPU pCPU) {//[AF]
	/*
	 * IMUL r16, r/m16    word register ← word register * r/m16.
	 * IMUL r32, r/m32    doubleword register ← doubleword register * r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_IMUL_0FAF", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__sword swInt16Tmp;
		if (Args.bIsEAReg) {
			swInt16Tmp = UINT16_TO_INT16(__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, swInt16Tmp);
		}
		__CPU_GR16__(pCPU, Args.bRegOpcode) = __InternalIMUL2_16__(pCPU, UINT16_TO_INT16(__CPU_GR16__(pCPU, Args.bRegOpcode)), swInt16Tmp);
	} else {
		__dword sdwInt32Tmp;
		if (Args.bIsEAReg) {
			sdwInt32Tmp = UINT32_TO_INT32(__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex));
		} else {
			__MM_READ_INT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, sdwInt32Tmp);

		}
		__CPU_GR32__(pCPU, Args.bRegOpcode) = __InternalIMUL2_32__(pCPU, UINT32_TO_INT32(__CPU_GR32__(pCPU, Args.bRegOpcode)), sdwInt32Tmp);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * XADD
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_XADD_0FC0(PCHAOSVM_CPU pCPU) {//[C0]
	/*
	 * XADD r/m8, r8      Exchange r8 and r/m8; load sum into r/m8.
	 */
	__byte bInt8TmpRM;
	__byte bInt8TmpR;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_XADD_0FC0", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	bInt8TmpR = __CPU_GR8_GET__(pCPU, Args.bRegOpcode);
	if (Args.bIsEAReg) {
		bInt8TmpRM = __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, bInt8TmpRM);

		bInt8TmpRM = InternalADD8(pCPU, bInt8TmpRM, bInt8TmpR);
		__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, bInt8TmpRM);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8TmpRM);
		__CPU_GR8_SET__(pCPU, Args.bRegOpcode, bInt8TmpRM);
		bInt8TmpRM = InternalADD8(pCPU, bInt8TmpRM, bInt8TmpR);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8TmpRM);
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_XADD_0FC1(PCHAOSVM_CPU pCPU) {//[C1]
	/*
	 * XADD r/m16, r16     Exchange r16 and r/m16; load sum into r/m16.
	 * XADD r/m32, r32     Exchange r32 and r/m32; load sum into r/m32.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_XADD_0FC1", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16TmpRM;
		__word wInt16TmpR;
		wInt16TmpR = __CPU_GR16__(pCPU, Args.bRegOpcode);
		if (Args.bIsEAReg) {
			wInt16TmpRM = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = wInt16TmpRM;

			wInt16TmpRM = InternalADD16(pCPU, wInt16TmpRM, wInt16TmpR);
			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wInt16TmpRM;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16TmpRM);
			__CPU_GR16__(pCPU, Args.bRegOpcode) = wInt16TmpRM;
			wInt16TmpRM = InternalADD16(pCPU, wInt16TmpRM, wInt16TmpR);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16TmpRM);
		}
	} else {
		__dword dwInt32TmpRM;
		__dword dwInt32TmpR;
		dwInt32TmpR = __CPU_GR32__(pCPU, Args.bRegOpcode);
		if (Args.bIsEAReg) {
			dwInt32TmpRM = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = dwInt32TmpRM;

			dwInt32TmpRM = InternalADD32(pCPU, dwInt32TmpRM, dwInt32TmpR);
			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwInt32TmpRM;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32TmpRM);
			__CPU_GR32__(pCPU, Args.bRegOpcode) = dwInt32TmpRM;
			dwInt32TmpRM = InternalADD32(pCPU, dwInt32TmpRM, dwInt32TmpR);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32TmpRM);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


/*
 * CMPXCHG指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_CMPXCHG_0FB0(PCHAOSVM_CPU pCPU) {//[B0]
	/*
	 * CMPXCHG r/m8, r8      Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. 
	 * Else, clear  ZF and load r/m8 into AL.
	 *
	 * Flags Affected
	 * The ZF flag is set if the values in the destination operand and register AL, AX, or EAX are equal;
	 * otherwise it is cleared. The CF, PF, AF, SF, and OF flags are set according to the results of the
	 * comparison operation.
	 */
	__byte bInt8TmpRM;
	__byte bInt8TmpR;
	__byte bInt8TmpAL;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_CMPXCHG_0FB0", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	bInt8TmpAL = __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL);
	bInt8TmpR = __CPU_GR8_GET__(pCPU, Args.bRegOpcode);
	if (Args.bIsEAReg) {
		bInt8TmpRM = __CPU_GR8_GET__(pCPU, Args.EffectiveAddress.bRegIndex);
		/*
		 * Compare AL with r/m8.
		 */
		__InternalCMP8__(pCPU, bInt8TmpAL, bInt8TmpRM);

		if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == __EFLAG_SET__) {
			/*
			 * If equal, ZF is set and r8 is loaded into r/m8. 
			 */
			__CPU_GR8_SET__(pCPU, Args.EffectiveAddress.bRegIndex, bInt8TmpR);
		} else {
			/* 
			 * Else, clear  ZF and load r/m8 into AL.
			 */
			__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8TmpRM);
		}
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8TmpRM);

		/*
		 * Compare AL with r/m8.
		 */
		__InternalCMP8__(pCPU, bInt8TmpAL, bInt8TmpRM);

		if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == __EFLAG_SET__) {
			/*
			 * If equal, ZF is set and r8 is loaded into r/m8. 
			 */
			__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, bInt8TmpR);
		} else {
			/* 
			 * Else, clear  ZF and load r/m8 into AL.
			 */
			__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8TmpRM);
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_CMPXCHG_0FB1(PCHAOSVM_CPU pCPU) {//[B1]
	/*
	 * CMPXCHG r/m16, r16    Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. 
	 * Else, clear ZF and load r/m16 into AX.
	 * CMPXCHG r/m32, r32    Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. 
	 * Else, clear ZF and load r/m32 into EAX.
	 *
	 * Flags Affected
	 * The ZF flag is set if the values in the destination operand and register AL, AX, or EAX are equal;
	 * otherwise it is cleared. The CF, PF, AF, SF, and OF flags are set according to the results of the
	 * comparison operation.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_CMPXCHG_0FB1", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式
		 */
		__word wInt16TmpRM;
		__word wInt16TmpR;
		__word wInt16TmpAX;
		wInt16TmpAX = __CPU_GR16__(pCPU, CHAOSVM_R_AX);
		wInt16TmpR = __CPU_GR16__(pCPU, Args.bRegOpcode);
		if (Args.bIsEAReg) {
			wInt16TmpRM = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * Compare AX with r/m16.
			 */
			__InternalCMP16__(pCPU, wInt16TmpAX, wInt16TmpRM);

			if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == __EFLAG_SET__) {
				/*
				 * If equal, ZF is set and r16 is loaded into r/m16. 
				 */
				__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wInt16TmpR;
			} else {
				/* 
				 * Else, clear  ZF and load r/m16 into AX.
				 */
				__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16TmpRM;
			}
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16TmpRM);

			/*
			 * Compare AX with r/m16.
			 */
			__InternalCMP16__(pCPU, wInt16TmpAX, wInt16TmpRM);

			if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == __EFLAG_SET__) {
				/*
				 * If equal, ZF is set and r16 is loaded into r/m16. 
				 */
				__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wInt16TmpR);
			} else {
				/* 
				 * Else, clear  ZF and load r/m16 into AX.
				 */
				__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16TmpRM;
			}
		}
	} else {
		/*
		 * 32位操作数模式
		 * 32位操作数模式
		 */
		__dword dwInt32TmpRM;
		__dword dwInt32TmpR;
		__dword dwInt32TmpEAX;
		dwInt32TmpEAX = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);
		dwInt32TmpR = __CPU_GR32__(pCPU, Args.bRegOpcode);
		if (Args.bIsEAReg) {
			dwInt32TmpRM = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * Compare EAX with r/m32.
			 */
			__InternalCMP32__(pCPU, dwInt32TmpEAX, dwInt32TmpRM);

			if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == __EFLAG_SET__) {
				/*
				 * If equal, ZF is set and r32 is loaded into r/m32. 
				 */
				__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwInt32TmpR;
			} else {
				/* 
				 * Else, clear  ZF and load r/m32 into EAX.
				 */
				__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32TmpRM;
			}
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32TmpRM);

			/*
			 * Compare EAX with r/m32.
			 */
			__InternalCMP32__(pCPU, dwInt32TmpEAX, dwInt32TmpRM);

			if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF)==__EFLAG_SET__) {
				/*
				 * If equal, ZF is set and r32 is loaded into r/m32. 
				 */
				__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwInt32TmpR);
			} else {
				/* 
				 * Else, clear  ZF and load r/m32 into EAX.
				 */
				__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32TmpRM;
			}
		}
	}

	pCPU->bOpcodeLength += 1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// C8
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FC8(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FC8", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_AX) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_EAX);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// C9
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FC9(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FC9", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_CX) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_ECX);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_ECX) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CA
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCA(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCA", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_DX) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_EDX);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CB
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCB(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCB", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_BX) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_EBX);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_EBX) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CC
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCC(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCC", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_SP) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_ESP);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CD
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCD(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCD", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		* 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		*/
		__CPU_GR16__(pCPU, CHAOSVM_R_BP) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_EBP);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_EBP) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CE
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCE(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCE", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_SI) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_ESI);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

// CF
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_BSWAP_0FCF(PCHAOSVM_CPU pCPU) {
	/*
	 * BSWAP r32    Reverses the byte order of a 32-bit register.
	 *
	 * Operation
	 * DEST[7:0] ← TEMP[31:24];
	 * DEST[15:8] ← TEMP[23:16];
	 * DEST[23:16] ← TEMP[15:8];
	 * DEST[31:24] ← TEMP[7:0];
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_BSWAP_0FCF", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位操作数模式时,扩展为32位,高16为0,所以交换后低16位是0
		 */
		__CPU_GR16__(pCPU, CHAOSVM_R_DI) = 0;
	} else {
		__dword BSWAP_Tmp32_1, BSWAP_Tmp32_2;
		__dword BSWAP_Tmp32 = __CPU_GR32__(pCPU, CHAOSVM_R_EDI);

		/*
		 * 交换0,3字节
		 */
		BSWAP_Tmp32_1 = (BSWAP_Tmp32 & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 24) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 24;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0x00FFFFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFFFF00) | BSWAP_Tmp32_2;

		/*
		 * 交换1,2字节
		 */
		BSWAP_Tmp32_1 = ((BSWAP_Tmp32 >> 8) & 0xFF);
		BSWAP_Tmp32_2 = ((BSWAP_Tmp32 >> 16) & 0xFF);

		BSWAP_Tmp32_1 = BSWAP_Tmp32_1 << 16;
		BSWAP_Tmp32_2 = BSWAP_Tmp32_2 << 8;

		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFF00FFFF) | BSWAP_Tmp32_1;
		BSWAP_Tmp32 = (BSWAP_Tmp32 & 0xFFFF00FF) | BSWAP_Tmp32_2;

		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) = BSWAP_Tmp32;
	}

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 特殊指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F30(PCHAOSVM_CPU pCPU) {//[30]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F30", pCPU);
	/*
	 *WRMSR
	 */
	__CPU_UNREFERENCED_PARAMETER__(pCPU);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F32(PCHAOSVM_CPU pCPU) {//[32]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F32", pCPU);
	/*
	 * RDMSR
	 */
	__CPU_UNREFERENCED_PARAMETER__(pCPU);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_MOV_0F31(PCHAOSVM_CPU pCPU) {//[31]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_MOV_0F31", pCPU);
	/*
	 * RDTSC
	 */
	__CPU_UNREFERENCED_PARAMETER__(pCPU);

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

/*
 * SYSENTER/SYSEXIT指令
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SYSENTER_0F34(PCHAOSVM_CPU pCPU) {//[34]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SYSENTER_0F34", pCPU);
	/*
	 * SYSENTER
	 */

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SYSEXIT_0F35(PCHAOSVM_CPU pCPU) {//[35]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SYSEXIT_0F35", pCPU);
	/*
	 * SYSEXIT
	 */

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_CPUID_0FA2(PCHAOSVM_CPU pCPU) {//[A2]
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_CPUID_0FA2", pCPU);
	/*
	 * CPUID
	 */

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_IGNORE__;
}
