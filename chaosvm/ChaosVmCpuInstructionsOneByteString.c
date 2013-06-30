__byte g_RepLoopConditonTable[] = {
	0xFF,/*未使用*/
	0xFF,/*未使用*/
	__EFLAG_RESET__,   /*0xF2 REPNE  -> ZF == __EFLAG_RESET__*/
	__EFLAG_SET__,     /*0xF3 REPE   -> ZF == __EFLAG_SET__*/
};

/*
 * 串指令
 */

/*
 * MOVS
 * The address of the source operand is read from the DS:ESI or
 * the DS:SI registers (depending on the address-size attribute of the instruction, 32 or 16, respectively).
 * The address of the destination operand is read from the ES:EDI or the ES:DI registers
 * (again depending on the address-size attribute of the instruction). The DS segment may be overridden
 * with a segment override prefix, but the ES segment cannot be overridden.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalMOVS8(PCHAOSVM_CPU pCPU) {
	__byte bInt8Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), bInt8Tmp);
		__MM_WRITE_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), bInt8Tmp);
	}

	/* 
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__ ) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 1;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 1;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 1;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 1;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalMOVS16(PCHAOSVM_CPU pCPU) {
	__word wInt16Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32( __CPU_GR16__(pCPU, CHAOSVM_R_SI)), wInt16Tmp);
		__MM_WRITE_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32( __CPU_GR16__(pCPU, CHAOSVM_R_DI)), wInt16Tmp);
	} else {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), wInt16Tmp);
		__MM_WRITE_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), wInt16Tmp);
	}

	/*
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 2;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 2;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 2;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 2;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalMOVS32(PCHAOSVM_CPU pCPU) {
	__dword dwInt32Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), dwInt32Tmp);
		__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), dwInt32Tmp);
	} else {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), dwInt32Tmp);
		__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), dwInt32Tmp);
	}

	/*
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 4;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 4;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 4;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 4;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * SCAS
 *
 * The memory operand address is read from
 * ES:(E)DI register (depending on the address-size attribute of the instruction and the current
 * operational mode). Note that ES cannot be overridden with a segment override prefix.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSCAS8(PCHAOSVM_CPU pCPU) {
	__byte bInt8Tmp;

	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), bInt8Tmp);
	}

	__InternalCMP8__(pCPU, __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL), bInt8Tmp);

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 1;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 1;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSCAS16(PCHAOSVM_CPU pCPU) {
	__word wInt16Tmp;

	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), wInt16Tmp);
	} else {
		__MM_READ_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), wInt16Tmp);
	}

	__InternalCMP16__(pCPU, __CPU_GR16__(pCPU, CHAOSVM_R_AX), wInt16Tmp);

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 2;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 2;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSCAS32(PCHAOSVM_CPU pCPU) {
	__dword dwInt32Tmp;

	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), dwInt32Tmp);
	} else {
		__MM_READ_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), dwInt32Tmp);
	}

	__InternalCMP32__(pCPU, __CPU_GR32__(pCPU, CHAOSVM_R_EAX), dwInt32Tmp);

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 4;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 4;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * STOS
 *
 * stores a byte, word, or doubleword from the AL, AX, or
 * EAX register (respectively) into the destination operand. The destination operand is a memory
 * location, the address of which is read from either the ES:EDI or ES:DI register (depending on
 * the address-size attribute of the instruction and the mode of operation). The ES segment cannot
 * be overridden with a segment override prefix.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSTOS8(PCHAOSVM_CPU pCPU) {
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_WRITE_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
	} else {
		__MM_WRITE_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), __CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
	}

	/*修改EDI*/
	if (__CPU_EFLAG_GET__(pCPU,CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 1;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 1;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSTOS16(PCHAOSVM_CPU pCPU) {
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_WRITE_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), __CPU_GR16__(pCPU, CHAOSVM_R_AX));
	} else {
		__MM_WRITE_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), __CPU_GR16__(pCPU, CHAOSVM_R_AX));
	}

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 2;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 2;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalSTOS32(PCHAOSVM_CPU pCPU) {
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32( __CPU_GR16__(pCPU, CHAOSVM_R_DI) ), __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	} else {
		__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), __CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	}

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 4;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 4;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * LODS
 *
 * Loads a byte, word, or doubleword from the source operand into the AL, AX, or EAX register,
 * respectively. The source operand is a memory location, the address of which is read from the
 * DS:EDI or the DS:SI registers (depending on the address-size attribute of the instruction, 32 or
 * 16, respectively). The DS segment may be overridden with a segment override prefix.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalLODS8(PCHAOSVM_CPU pCPU) {
	__byte bInt8Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), bInt8Tmp);
	}

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, bInt8Tmp);

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 1;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 1;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalLODS16(PCHAOSVM_CPU pCPU) {
	__word wInt16Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), wInt16Tmp);
	} else {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), wInt16Tmp);
	}

	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = wInt16Tmp;

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 2;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 2;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalLODS32(PCHAOSVM_CPU pCPU) {
	__dword dwInt32Tmp;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), dwInt32Tmp);
	} else {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), dwInt32Tmp);
	}

	__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = dwInt32Tmp;

	/*
	 * 修改EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 4;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 4;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * CMPS
 *
 * Compares the byte, word, doubleword, or quadword specified with the first source operand with
 * the byte, word, doubleword, or quadword specified with the second source operand and sets the
 * status flags in the EFLAGS register according to the results.
 * Both source operands are located in memory. The address of the first source operand is read
 * from DS:SI, DS:ESI or RSI (depending on the address-size attribute of the instruction is 16, 32,
 * or 64, respectively). The address of the second source operand is read from ES:DI, ES:EDI or
 * RDI (again depending on the address-size attribute of the instruction is 16, 32, or 64). The DS
 * segment may be overridden with a segment override prefix, but the ES segment cannot be overridden.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalCMPS8(PCHAOSVM_CPU pCPU) {
	__byte bInt8TmpSrc,bInt8TmpDest;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), bInt8TmpSrc);
		__MM_READ_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), bInt8TmpDest);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), bInt8TmpSrc);
		__MM_READ_UINT8_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), bInt8TmpDest);
	}

	__InternalCMP8__(pCPU, bInt8TmpSrc, bInt8TmpDest);


	/*
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 1;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 1;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 1;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 1;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalCMPS16(PCHAOSVM_CPU pCPU)
{
	__word wInt16TmpSrc, wInt16TmpDest;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), wInt16TmpSrc);
		__MM_READ_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), wInt16TmpDest);
	} else {
		__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), wInt16TmpSrc);
		__MM_READ_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), wInt16TmpDest);
	}

	__InternalCMP16__(pCPU, wInt16TmpSrc, wInt16TmpDest);


	/*
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 2;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 2;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 2;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 2;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalCMPS32(PCHAOSVM_CPU pCPU) {
	__dword dwInt32TmpSrc, dwInt32TmpDest;
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)) {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_SI)), dwInt32TmpSrc);
		__MM_READ_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_DI)), dwInt32TmpDest);
	} else {
		__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), __CPU_GR32__(pCPU, CHAOSVM_R_ESI), dwInt32TmpSrc);
		__MM_READ_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_ES), __CPU_GR32__(pCPU, CHAOSVM_R_EDI), dwInt32TmpDest);
	}

	__InternalCMP32__(pCPU, dwInt32TmpSrc, dwInt32TmpDest);


	/*
	 * 修改ESI/EDI
	 */
	if (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_DF) == __EFLAG_SET__) {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) -= 4;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) -= 4;
	} else {
		__CPU_GR32__(pCPU, CHAOSVM_R_ESI) += 4;
		__CPU_GR32__(pCPU, CHAOSVM_R_EDI) += 4;
	}
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOVSB_A4(PCHAOSVM_CPU pCPU) {//[A4]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOVSB_A4", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
			__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
			Status = InternalMOVS8(pCPU);
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		Status = InternalMOVS8(pCPU);
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_MOVSD_A5(PCHAOSVM_CPU pCPU) {//[A5]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_MOVSD_A5", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalMOVS16(pCPU);
			}
		} else {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalMOVS32(pCPU);
			}
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			Status = InternalMOVS16(pCPU);
		} else {
			Status = InternalMOVS32(pCPU);
		}
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SCASB_AE(PCHAOSVM_CPU pCPU) {//[AE]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SCASB_AE", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
			__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;

			Status = InternalSCAS8(pCPU);
			if (!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
				break;
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		Status = InternalSCAS8(pCPU);
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_SCASD_AF(PCHAOSVM_CPU pCPU) {//[AF]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_SCASD_AF", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;

				Status = InternalSCAS16(pCPU);
				if (!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
					break;
			}
		} else {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;

				Status = InternalSCAS32(pCPU);
				if(!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
					break;
			}
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			Status = InternalSCAS16(pCPU);
		} else {
			Status = InternalSCAS32(pCPU);
		}
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_STOSB_AA(PCHAOSVM_CPU pCPU) {//[AA]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_STOSB_AA", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
			__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
			Status = InternalSTOS8(pCPU);
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		Status = InternalSTOS8(pCPU);
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;
	
	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_STOS_AB(PCHAOSVM_CPU pCPU) {//[AB]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_STOS_AB", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalSTOS16(pCPU);
			}
		} else {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalSTOS32(pCPU);
			}
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			Status = InternalSTOS16(pCPU);
		} else {
			Status = InternalSTOS32(pCPU);
		}
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;
	
	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_LODSB_AC(PCHAOSVM_CPU pCPU) {//[AC]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LODSB_AC", pCPU);
	__ExecuteInstBefore__(pCPU);
	if(__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
			__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
			Status = InternalLODS8(pCPU);
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		Status = InternalLODS8(pCPU);
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_LODS_AD(PCHAOSVM_CPU pCPU) {//[AD]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_LODS_AD", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalLODS16(pCPU);
			}
		} else {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalLODS32(pCPU);
			}
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			Status = InternalLODS16(pCPU);
		} else {
			Status = InternalLODS32(pCPU);
		}
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMPSB_A6(PCHAOSVM_CPU pCPU) {//[A6]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMPSB_A6", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		while (__CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
			__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
			Status = InternalCMPS8(pCPU);

			if(!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
				break;
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		Status = InternalCMPS8(pCPU);
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;
	
	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_CMPSD_A7(PCHAOSVM_CPU pCPU) {//[A7]
	CPU_STATUS Status = __CPU_STATUS_EXECUTE_SUCCESS__;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_CMPSD_A7", pCPU);
	__ExecuteInstBefore__(pCPU);
	if (__IS_INSTRUCTION_PREFIX_REP_ENABLE__(pCPU)) {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalCMPS16(pCPU);

				if(!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
					break;
			}
		} else {
			while( __CPU_GR32__(pCPU, CHAOSVM_R_ECX) && __CPU_STATUS_SUCCESS__(Status)) {
				__CPU_GR32__(pCPU, CHAOSVM_R_ECX)--;
				Status = InternalCMPS32(pCPU);

				if (!((__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF) == g_RepLoopConditonTable[__INSTRUCTION_REPEAT_PREFIX__(pCPU) & 0x0F])))
					break;
			}
		}
		__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_STRING__);
	} else {
		if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
			Status = InternalCMPS16(pCPU);
		} else {
			Status = InternalCMPS32(pCPU);
		}
	}

	if (!__CPU_STATUS_SUCCESS__(Status))
		return Status;

	pCPU->bOpcodeLength += 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	__ExecuteInstAfter__(pCPU);
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

