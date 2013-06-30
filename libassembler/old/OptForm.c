

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_1Opt(PASM_OBJ pAsmObj) {
	PASMER_OPERAND pOpt0 = &(pAsmObj->Operand[0]);
	// op imm
	// op mem
	// op reg
	if (pOpt0->Type == OP_IMM) {
		if (pOpt0->Bit == ASMER_8_BITS)
			return OF_I8;
		else if (pOpt0->Bit == ASMER_16_BITS)
			return OF_I16;
		else if (pOpt0->Bit == ASMER_32_BITS)
			return OF_I32;
		else if (pOpt0->BIt == ASMER_64_BITS)
			return OF_I64;
	} else if (pOpt0->Type == OP_MEM) {
		if (pOpt0->Bit == ASMER_8_BITS)
			return OF_M8;
		else if (pOpt0->Bit == ASMER_16_BITS)
			return OF_M16;
		else if (pOpt0->Bit == ASMER_32_BITS)
			return OF_M32;
		else if (pOpt0->Bit == ASMER_64_BITS)
			return OF_M64;
	} else if (pOpt0->Type == OP_REG) {
		if (pOpt0->Bit == ASMER_8_BITS)
			return OF_R8;
		else if (pOpt0->Bit == ASMER_16_BITS)
			return OF_R16;
		else if (pOpt0->Bit == ASMER_32_BITS)
			return OF_R32;
		else if (pOpt0->Bit == ASMER_64_BITS)
			return OF_R64;		
	}
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpRegImm(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R8_I8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R16_I8;	
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R16_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R32_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R32_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R32_I32;	
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R64_I8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R64_I16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R64_I32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS))
		return OF_R64_I64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpRegMem(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R8_M8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R16_M8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R16_M16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R32_M8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R32_M16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R32_M32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R64_M8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R64_M16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R64_M32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS))
		return OF_R64_M64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpRegReg(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R8_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R16_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R16_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R32_R8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R32_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R32_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R64_R8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R64_R16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R64_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS))
		return OF_R64_R64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpMemImm(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R8_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R16_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R16_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R32_R8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R32_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R32_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_R64_R8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_R64_R16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_R64_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS))
		return OF_R64_R64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpMemReg(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_M8_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_M16_R8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_M16_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_M32_R8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_M32_R16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_M32_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_8_BITS))
		return OF_M64_R8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_16_BITS))
		return OF_M64_R16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_32_BITS))
		return OF_M64_R32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS))
		return OF_M64_R64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_2Opt(PASM_OBJ pAsmObj) {
	PASMER_OPERAND pOpt0 = &(pAsmObj->Operand[0]);
	PASMER_OPERAND pOpt1 = &(pAsmObj->Operand[1]);

    // op reg, imm
	// op reg, mem
	// op reg, reg
	// op mem, imm
	// op mem, reg

	if ((pOpt0->Type == OP_REG) && (pOpt1->Type == OP_IMM))
		return ToOptForm_OpRegImm(pOpt0, pOpt1);
	else if ((pOpt0->Type == OP_REG) && (pOpt1->Type == OP_MEM))
		return ToOptForm_OpRegMem(pOpt0, pOpt1);
	else if ((pOpt0->Type == OP_REG) && (pOpt1->Type == OP_REG))
		return ToOptForm_OpRegReg(pOpt0, pOpt1);
	else if ((pOpt0->Type == OP_MEM) && (pOpt1->Type == OP_IMM))
		return ToOptForm_OpMemImm(pOpt0, pOpt1);
	else if ((pOpt0->Type == OP_MEM) && (pOpt1->Type == OP_REG))
		return ToOptForm_OpMemReg(pOpt0, pOpt1);
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpRegMemImm(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1, PASMER_OPERAND pOpt2) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R8_M8_I8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R16_M16_I8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R16_M16_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R32_M32_I8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R32_M32_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_32_BITS))
		return OF_R32_M32_I32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R64_M64_I8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R64_M64_I16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_32_BITS))
		return OF_R64_M64_I32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_64_BITS))
		return OF_R64_M64_I64;
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_OpRegRegImm(PASMER_OPERAND pOpt0, PASMER_OPERAND pOpt1, PASMER_OPERAND pOpt2) {
	if ((pOpt0->Bit == ASMER_8_BITS) && (pOpt1->Bit == ASMER_8_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R8_R8_I8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R16_R16_I8;
	else if ((pOpt0->Bit == ASMER_16_BITS) && (pOpt1->Bit == ASMER_16_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R16_R16_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R32_R32_I8;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R32_R32_I16;
	else if ((pOpt0->Bit == ASMER_32_BITS) && (pOpt1->Bit == ASMER_32_BITS) && (pOpt2->Bit == ASMER_32_BITS))
		return OF_R32_R32_I32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_8_BITS))
		return OF_R64_R64_I8;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_16_BITS))
		return OF_R64_R64_I16;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_32_BITS))
		return OF_R64_R64_I32;
	else if ((pOpt0->Bit == ASMER_64_BITS) && (pOpt1->Bit == ASMER_64_BITS) && (pOpt2->Bit == ASMER_64_BITS))
		return OF_R64_R64_I64;
	return OF_NONE;	
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm_3Opt(PASM_OBJ pAsmObj) {
	PASMER_OPERAND pOpt0 = &(pAsmObj->Operand[0]);
	PASMER_OPERAND pOpt1 = &(pAsmObj->Operand[1]);
	PASMER_OPERAND pOpt2 = &(pAsmObj->Operand[2]);
	// opt reg, mem, imm
	// opt reg, reg, imm
	if ((pOpt0->Type == OP_REG) && (pOpt1->Type == OP_MEM) && (pOpt2->Type == OP_IMM))
		return ToOptForm_OpRegMemImm(pOpt0, pOpt1, pOpt2);
	else if ((pOpt0->Type == OP_REG) && (pOpt1->Type == OP_REG) && (pOpt2->Type == OP_IMM))
		return ToOptForm_OpRegRegImm(pOpt0, pOpt1, pOpt2);
	return OF_NONE;
}

__INLINE__ OPT_FORM __INTERNAL_FUNC__ ToOptForm(PASM_OBJ pAsmObj) {
	__byte bOperandCount = pAsmObj->bOperandCount;
	if (bOperandCount == 0)
		return OF_OP;
	else if (bOperandCount == 1)
		return ToOptForm_1Opt(pAsmObj);
	else if (bOperandCount == 2)
		return ToOptForm_2Opt(pAsmObj);
	else if (bOperandCount == 3)
		return ToOptForm_3Opt(pAsmObj);
	
	return OF_NONE;
}
