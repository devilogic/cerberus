/*
 * FF XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_UnImplement_FF(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_UnImplement_FF", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  FF /%02X\n", __CPU_EIP__(pCPU), pArgs->bRegOpcode);	
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_INC_FF_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * INC r/m16    Increment r/m word by 1.
	 * INC r/m32    Increment r/m doubleword by 1.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_INC_FF_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalINC16(pCPU, wInt16Tmp);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalINC16(pCPU, wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalINC32(pCPU, dwInt32Tmp);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalINC32(pCPU, dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_DEC_FF_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * DEC r/m16    Decrement r/m16 by 1.
	 * DEC r/m32    Decrement r/m32 by 1.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_DEC_FF_1", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if(pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalDEC16(pCPU, wInt16Tmp);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalDEC16(pCPU, wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalDEC32(pCPU, dwInt32Tmp);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalDEC32(pCPU, dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_CALL_FF_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * CALL r/m16    Call near, absolute indirect, address given in r/m16.
	 * CALL r/m32    Call near, absolute indirect, address given in r/m32.
	 * Prefix Enable: Operand-Size,Address-Size
	 */

	__dword dwNewEIP;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_CALL_FF_2", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_CALL_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));

	/*
	 * 下一条的指令地址压入栈中，但不修改ESP寄存器
	 */
	__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 4, (__CPU_EIP__(pCPU) + (pCPU->bOpcodeLength + 1 + pArgs->bLength)));

	/*
	 * 测试表明，在16位操作数模式下，16位的地址无符号扩展到32位，然后填入EIP
	 */
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			dwNewEIP = UINT16_TO_UINT32(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			dwNewEIP = UINT16_TO_UINT32(wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			dwNewEIP = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwNewEIP = dwInt32Tmp;
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	Status = ChaosVmCpuInternalCallHookRoutineCall(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), dwNewEIP, pCPU->bOpcodeLength);
	if (Status == __CPU_STATUS_HOOK_HANDLE__) {
		/*
		 * 此CALL已经被处理，直接返回
		 * 增加EIP
		 */
		__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	} else if( Status == __CPU_STATUS_HOOK_STOP_CPU__) {
		/*
		 * 退出
		 */
		Status = __CPU_STATUS_IMMEDIATELY_EXIT__;
	} else if(Status == __CPU_STATUS_HOOK_NOT_HANDLE__) {
		__CPU_EIP__(pCPU) = (__address)dwNewEIP;
		__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 4;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_JMP_FF_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * JMP r/m16    Jump near, absolute indirect, address = sign-extended r/m16. Not supported in 64-bit mode.
	 * JMP r/m32    Jump near, absolute indirect, address = sign-extended r/m32. Not supported in 64-bit mode.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	CPU_STATUS Status;
	__dword dwNewEIP;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_JMP_FF_4", pCPU);
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_FLOW_CONTROL__);
	__CPU_INSTR_TYPE_FLOW_CONTROL_SET__(pCPU, __INSTR_SUB_TYPE_FLOW_CONTROL_JMP_NEAR__, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU));
	/*
	 * 测试表明，在16位操作数模式下，16位的地址无符号扩展到32位，然后填入EIP
	 */
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if(pArgs->bIsEAReg) {
			dwNewEIP = UINT16_TO_UINT32(__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			dwNewEIP = UINT16_TO_UINT32(wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			dwNewEIP =  __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) ;
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwNewEIP = dwInt32Tmp;
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	Status = ChaosVmCpuInternalCallHookRoutineJmp(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), dwNewEIP, pCPU->bOpcodeLength);
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
	} else if (Status == __CPU_STATUS_HOOK_NOT_HANDLE__ ) {
		__CPU_EIP__(pCPU) = (__address)dwNewEIP;
		Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	}

	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_PUSH_FF_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * PUSH r/m16    Push r/m16.
	 * PUSH r/m32    Push r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_PUSH_FF_6", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			__InternalPush_uWord__(pCPU, wInt16Tmp)
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalPush_uWord__(pCPU, wInt16Tmp)
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			__InternalPush_uDword__(pCPU, dwInt32Tmp)
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalPush_uDword__(pCPU, dwInt32Tmp)
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_FF(PCHAOSVM_CPU pCPU) {//[FF]
	/*
	 * Group5
	 */
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_FF", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryFF[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * FE XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_FE(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_FE", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_INC_FE_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * INC r/m8    Increment r/m byte by 1.
	 */
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_INC_FE_0", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalINC8(pCPU,bInt8Tmp);
		__CPU_GR8_SET__(pCPU,pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalINC8(pCPU, bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_DEC_FE_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * DEC r/m8    Decrement r/m8 by 1.
	 */
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_DEC_FE_1", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalDEC8(pCPU,bInt8Tmp);
		__CPU_GR8_SET__(pCPU,pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	}
	else
	{
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalDEC8(pCPU,bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_FE(PCHAOSVM_CPU pCPU) {//[FE]
	/*
	 * Group4
	 */
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_FE", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryFE[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * C6 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_C6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_C6", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_MOV_C6_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * MOV r/m8, imm8      Move imm8 to r/m8.
	 * Prefix Enable: Address-Size
	 * ModR/M: MOD = 3 , Reg = 0
	 */

	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_MOV_C6_0", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Imm);
	} else {
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Imm);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_C6(PCHAOSVM_CPU pCPU) {//[C6]
	/*Group11*/

	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_C6", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryC6[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * C7 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_C7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_C7", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_MOV_C7_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * MOV r/m16, imm16 Valid Valid Move imm16 to r/m16.
	 * MOV r/m32, imm32 Valid Valid Move imm32 to r/m32.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_MOV_C7_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;

		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);
		if(pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) =  wInt16Imm;
		} else {
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Imm);
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;

		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Imm;
		} else {
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Imm);
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_C7(PCHAOSVM_CPU pCPU) {//[C7]
	/*
	 * Group11
	 */
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_C7", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	/*
	 * bIsEAReg = 1 说明 ModR/M位的 MOD = 11B
	 */
	Status = pCPU->PargsDispatchTableEntryC7[Args.bIsEAReg][Args.bRegOpcode].DispatchFunction(pCPU, &Args);
	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * F6 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_F6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_F6", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_UnImplement_F6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_UnImplement_F6", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  F6 /%02X\n", __CPU_EIP__(pCPU), pArgs->bRegOpcode);	
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_TEST_F6_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * TEST r/m8, imm8    AND imm8 with r/m8; set SF, ZF, PF according to result
	 * Prefix Enable: Address-Size
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_TEST_F6_0", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);
	if (pArgs->bIsEAReg) {
		__InternalTEST8__(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm);
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalTEST8__(pCPU, bInt8Tmp, bInt8Imm);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_NOT_F6_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * NOT r/m8    Reverse each bit of r/m8.
	 * Prefix Enable: Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_NOT_F6_2", pCPU);
	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, ~(__CPU_GR8_GET__(pCPU,pArgs->EffectiveAddress.bRegIndex)));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = ~bInt8Tmp;
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_NEG_F6_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * NEG r/m8    Two's complement negate r/m8.
	 * Prefix Enable: Address-Size
     * 
	 * Flags Affected
	 * The CF flag set to 0 if the source operand is 0; otherwise it is set to 1. The OF, SF, ZF, AF, and
	 * PF flags are set according to the result.
     * 
	 * IF DEST = 0
	 * THEN CF ← 0;
	 * ELSE CF ← 1;
	 * FI;
	 * DEST ← [– (DEST)]
	 */
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_NEG_F6_3", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalNEG8(pCPU, bInt8Tmp);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalNEG8(pCPU, bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_MUL_F6_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * MUL r/m8     Unsigned multiply (AX ← AL * r/m8).
	 */

	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_MUL_F6_4", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		InternalMUL8(pCPU, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		InternalMUL8(pCPU, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IMUL_F6_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * IMUL r/m8*     AX← AL * r/m byte.
	 */

	__char bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IMUL_F6_5", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = UINT8_TO_INT8(__CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		InternalIMUL1_8(pCPU, bInt8Tmp);
	} else {
		__MM_READ_INT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		InternalIMUL1_8(pCPU, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_DIV_F6_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * DIV r/m8    Unsigned divide AX by r/m8, with result stored in AL ← Quotient, AH ← Remainder
	 */

	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_DIV_F6_6", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		__InternalDIV8_SAFE__(pCPU, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalDIV8_SAFE__(pCPU, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IDIV_F6_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * IDIV r/m8    Signed divide AX by r/m8, with result stored in: AL ← Quotient, AH ← Remainder.
	 */

	__char bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IDIV_F6_7", pCPU);
	if(pArgs->bIsEAReg) {
		bInt8Tmp = UINT8_TO_INT8( __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex) );
		__InternalIDIV8_SAFE__(pCPU, bInt8Tmp);
	} else {
		__MM_READ_INT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalIDIV8_SAFE__(pCPU, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_F6(PCHAOSVM_CPU pCPU) {//[F6]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_F6", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);
	Status = pCPU->PargsDispatchTableEntryF6[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * F7 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_F7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_F7", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_UnImplement_F7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_UnImplement_F7", pCPU);
	__CPU_DBG_OUTPUT__(pCPU, "UnImplement Opcode: %08X|  F7 /%02X\n", __CPU_EIP__(pCPU), pArgs->bRegOpcode);
	return __CPU_STATUS_UNIMPLEMENT_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_TEST_F7_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * TEST r/m16,imm16    AND imm16 with r/m16; set SF, ZF, PF according to result.
	 * TEST r/m32,imm32    AND imm32 with r/m32; set SF, ZF, PF according to result.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_TEST_F7_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);
		if(pArgs->bIsEAReg) {
			__InternalTEST16__(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalTEST16__(pCPU, wInt16Tmp, wInt16Imm);
		}

		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);
		if (pArgs->bIsEAReg) {
			__InternalTEST32__(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalTEST32__(pCPU, dwInt32Tmp, dwInt32Imm);
		}

		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;

	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_NOT_F7_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * NOT r/m16    Reverse each bit of r/m16.
	 * NOT r/m32    Reverse each bit of r/m32.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_NOT_F7_2", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = ~__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  ~wInt16Tmp;
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = ~__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  ~dwInt32Tmp;
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_NEG_F7_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * NEG r/m16    Two's complement negate r/m16.
	 * NEG r/m32    Two's complement negate r/m32.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_NEG_F7_3", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalNEG16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalNEG16(pCPU, wInt16Tmp);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		if(pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalNEG32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalNEG32(pCPU, dwInt32Tmp);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_MUL_F7_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * MUL r/m16    Unsigned multiply (DX:AX ← AX * r/m16).
	 * MUL r/m32    Unsigned multiply (EDX:EAX ← EAX * r/m32).
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_MUL_F7_4", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if(pArgs->bIsEAReg) {
			InternalMUL16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			InternalMUL16(pCPU, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			InternalMUL32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			InternalMUL32(pCPU, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IMUL_F7_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * IMUL r/m16        DX:AX ← AX * r/m word.
	 * IMUL r/m32        EDX:EAX ← EAX * r/m32.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IMUL_F7_5", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if(pArgs->bIsEAReg) {
			InternalIMUL1_16(pCPU, UINT16_TO_INT16( __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex)));
		} else {
			__sword swInt16Tmp;
			__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, swInt16Tmp);
			InternalIMUL1_16(pCPU, swInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			InternalIMUL1_32(pCPU, UINT32_TO_INT32( __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex)));
		} else {
			__sdword sdwInt32Tmp;
			__MM_READ_INT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, sdwInt32Tmp);
			InternalIMUL1_32(pCPU, sdwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_DIV_F7_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * DIV r/m16    Unsigned divide DX:AX by r/m16, with result stored in AX ← Quotient, DX ← Remainder.
	 * DIV r/m32    Unsigned divide EDX:EAX by r/m32, with result stored in EAX ← Quotient, EDX ← Remainder.
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_DIV_F7_6", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if(pArgs->bIsEAReg) {
			__InternalDIV16_SAFE__(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalDIV16_SAFE__(pCPU, wInt16Tmp);
		}
	} else {
		if (pArgs->bIsEAReg) {
			__InternalDIV32_SAFE__(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex));
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalDIV32_SAFE__(pCPU, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IDIV_F7_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * IDIV r/m16    Signed divide DX:AX by r/m16, with result stored in AX ← Quotient, DX ← Remainder.
	 * IDIV r/m32 Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX ← Quotient, EDX ← Remainder
	 * Prefix Enable: Operand-Size,Address-Size
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IDIV_F7_7", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		if (pArgs->bIsEAReg) {
			__InternalIDIV16_SAFE__(pCPU, UINT16_TO_INT16( __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex)));
		} else {
			__sword swInt16Tmp;
			__MM_READ_INT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, swInt16Tmp);
			__InternalIDIV16_SAFE__(pCPU, swInt16Tmp);
		}
	} else {
		if(pArgs->bIsEAReg) {
			__InternalIDIV32_SAFE__(pCPU, UINT32_TO_INT32( __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex)));
		} else {
			__sdword sdwInt32Tmp;
			__MM_READ_INT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, sdwInt32Tmp);
			__InternalIDIV32_SAFE__(pCPU, sdwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_F7(PCHAOSVM_CPU pCPU) {//[F7]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_F7", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);
	Status = pCPU->PargsDispatchTableEntryF7[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * 80 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADD_80_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADD r/m8, imm8    Add imm8 to r/m8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADD_80_0", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalADD8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalADD8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_OR_80_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * OR r/m8, imm8    r/m8 OR imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_OR_80_1", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalOR8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalOR8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADC_80_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADC r/m8, imm8    Add with carry imm8 to r/m8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADC_80_2", pCPU);
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalADC8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalADC8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SBB_80_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SBB r/m8, imm8    Subtract with borrow imm8 from r/m8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SBB_80_3", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalSBB8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSBB8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_AND_80_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * AND r/m8, imm8    r/m8 AND imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_AND_80_4", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalAND8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalAND8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SUB_80_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SUB r/m8, imm8    Subtract imm8 from r/m8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SUB_80_5", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalSUB8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSUB8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_XOR_80_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * XOR r/m8, imm8    r/m8 XOR imm8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_XOR_80_6", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, InternalXOR8(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm));
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalXOR8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_CMP_80_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * CMP r/m8, imm8    Compare imm8 with r/m8.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_CMP_80_7", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex), bInt8Imm);
	} else {
		__byte bInt8Tmp;
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		__InternalCMP8__(pCPU, bInt8Tmp, bInt8Imm);
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_80(PCHAOSVM_CPU pCPU) {//[80]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_80", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntry80[Args.bRegOpcode].DispatchFunction( pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * 81 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADD_81_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADD r/m16, imm16    Add imm16 to r/m16.
	 * ADD r/m32, imm32    Add imm32 to r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADD_81_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADD16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalADD16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADD32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalADD32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_OR_81_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * OR r/m16, imm16      r/m16 OR imm16.
	 * OR r/m32, imm32      r/m32 OR imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_OR_81_1", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalOR16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalOR16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalOR32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalOR32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADC_81_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADC r/m16, imm16    Add with carry imm16 to r/m16.
	 * ADC r/m32, imm32    Add with CF imm32 to r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADC_81_2", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADC16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalADC16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADC32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalADC32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SBB_81_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SBB r/m16, imm16     Subtract with borrow imm16 from r/m16.
	 * SBB r/m32, imm32     Subtract with borrow imm32 from r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SBB_81_3", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalSBB16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalSBB32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_AND_81_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * AND r/m16, imm16    r/m16 AND imm16.
	 * AND r/m32, imm32    r/m32 AND imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_AND_81_4", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalAND16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalAND16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if(pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalAND32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalAND32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SUB_81_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SUB r/m16, imm16    Subtract imm16 from r/m16.
	 * SUB r/m32, imm32    Subtract imm32 from r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SUB_81_5", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalSUB16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSUB32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalSUB32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_XOR_81_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * XOR r/m16, imm16    r/m16 XOR imm16.
	 * XOR r/m32, imm32    r/m32 XOR imm32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_XOR_81_6", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalXOR16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalXOR32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_CMP_81_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * CMP r/m16, imm16    Compare imm16 with r/m16.
	 * CMP r/m32, imm32    Compare imm32 with r/m32.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_CMP_81_7", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		__READ_DATA_UINT16_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, wInt16Imm);

		if (pArgs->bIsEAReg) {
			__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalCMP16__(pCPU, wInt16Tmp, wInt16Imm);
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 2;
	} else {
		__dword dwInt32Imm;
		__READ_DATA_UINT32_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, dwInt32Imm);

		if (pArgs->bIsEAReg) {
			__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalCMP32__(pCPU, dwInt32Tmp, dwInt32Imm);
		}
		pCPU->bOpcodeLength += 1 + pArgs->bLength + 4;
	}

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_81(PCHAOSVM_CPU pCPU) {//[81]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_81", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);
	Status = pCPU->PargsDispatchTableEntry81[Args.bRegOpcode].DispatchFunction( pCPU, &Args);;

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * 83 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADD_83_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADD r/m16, imm8     Add sign-extended imm8 to r/m16.
	 * ADD r/m32, imm8     Add sign-extended imm8 to r/m32.
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADD_83_0", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16( INT8_TO_INT16(Int8Imm));
		if(pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADD16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalADD16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32( INT8_TO_INT32(Int8Imm) );
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADD32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalADD32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_OR_83_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * OR r/m16, imm8    r/m16 OR imm8 (signextended).
	 * OR r/m32, imm8    r/m32 OR imm8 (signextended).
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_OR_83_1", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16( INT8_TO_INT16(Int8Imm) );
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalOR16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalOR16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32( INT8_TO_INT32(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalOR32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalOR32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ADC_83_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ADC r/m16, imm8    Add with CF sign-extended imm8 to r/m16.
	 * ADC r/m32, imm8    Add with CF sign-extended imm8 into r/m32..
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ADC_83_2", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16( INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADC16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalADC16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32(INT8_TO_INT32(Int8Imm));
		if(pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalADC32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalADC32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SBB_83_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SBB r/m16, imm8    Subtract with borrow signextended imm8 from r/m16.
	 * SBB r/m32, imm8    Subtract with borrow signextended imm8 from r/m32.
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SBB_83_3", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16(INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSBB16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalSBB16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32(INT8_TO_INT32(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSBB32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalSBB32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_AND_83_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * AND r/m16, imm8    r/m16 AND imm8 (signextended).
	 * AND r/m32, imm8    r/m32 AND imm8 (signextended).
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_AND_83_4", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16(INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalAND16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalAND16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32(INT8_TO_INT32(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalAND32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalAND32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SUB_83_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SUB r/m16, imm8    Subtract sign-extended imm8 from r/m16.
	 * SUB r/m32, imm8    Subtract sign-extended imm8 from r/m32.
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SUB_83_5", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16(INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSUB16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalSUB16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32( INT8_TO_INT32(Int8Imm) );
		if(pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalSUB32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalSUB32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_XOR_83_6(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * XOR r/m16, imm8     r/m16 XOR imm8 (signextended).
	 * XOR r/m32, imm8     r/m32 XOR
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_XOR_83_6", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16(INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalXOR16(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp =  InternalXOR16(pCPU, wInt16Tmp, wInt16Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp)
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32(INT8_TO_INT32(Int8Imm));
		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = InternalXOR32(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp =  InternalXOR32(pCPU, dwInt32Tmp, dwInt32Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp)
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_CMP_83_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * CMP r/m16, imm8     Compare imm8 with r/m16.
	 * CMP r/m32, imm8     Compare imm8 with r/m32.
	 */
	__char Int8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_CMP_83_7", pCPU);
	__READ_DATA_INT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, Int8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Imm;
		wInt16Imm = INT16_TO_UINT16(INT8_TO_INT16(Int8Imm));
		if (pArgs->bIsEAReg) {
			__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex), wInt16Imm);
		} else {
			__word wInt16Tmp;
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			__InternalCMP16__(pCPU, wInt16Tmp, wInt16Imm);
		}
	} else {
		__dword dwInt32Imm;
		dwInt32Imm = INT32_TO_UINT32( INT8_TO_INT32(Int8Imm) );
		if (pArgs->bIsEAReg) {
			__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex), dwInt32Imm);
		} else {
			__dword dwInt32Tmp;
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			__InternalCMP32__(pCPU, dwInt32Tmp, dwInt32Imm);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_83(PCHAOSVM_CPU pCPU) {//[83]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_83", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntry83[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * 8F XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_InvalidOpcode_8F(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_InvalidOpcode_8F", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_POP_8F_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * POP r/m16     Pop top of stack into m16; increment stack pointer.
	 * POP r/m32     Pop top of stack into m32; increment stack pointer.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_POP_8F_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		__InternalPop_uWord__(pCPU, wInt16Tmp);

		if (pArgs->bIsEAReg) {
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		__InternalPop_uDword__(pCPU, dwInt32Tmp);

		if (pArgs->bIsEAReg) {
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}
	pCPU->bOpcodeLength += 1 + pArgs->bLength;

	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_8F(PCHAOSVM_CPU pCPU) {//[8F]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_8F", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntry8F[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}
