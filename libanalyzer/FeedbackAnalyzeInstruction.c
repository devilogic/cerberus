/*
 * mov %reg, imm
 * mov %reg, dword ptr [address]
 * lea %reg, [address]
 */
MOVTYPE __INTERNAL_FUNC__ FeedbackAnalyzeInstruction(PX86INSTRUCTION pInstruction, enum ud_type OpRegister, __address *paddrAddress, \
													 __memory *pHookSaveFileAddress, __bool *pbIndirect) {
	ud_t *pud_obj = NULL;
	__memory pMem = NULL;
	PANALYZE_CONFIGURE pAnalyzeConfigure = NULL;

	pud_obj = &(pInstruction->ud_obj);

	if (!pInstruction)
		return MOV_NONE;

	if (pInstruction->bInvalid)
		return MOV_NONE;

	if ((pud_obj->mnemonic != UD_Imov) && (pud_obj->mnemonic != UD_Ilea))
		return MOV_NONE;

	if ((pud_obj->operand[0].type != UD_OP_REG) && (pud_obj->operand[0].base != OpRegister))
		return MOV_NONE;

	if ((pud_obj->pfx_opr == 0x66) || (pud_obj->pfx_adr == 0x67))
		return MOV_NONE;

	// 获取映射指针以及分析配置结构指针
	pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
	pAnalyzeConfigure = &(__GetProgramFromInstruction__(pInstruction)->AnalyzeConfigure);

	if (pud_obj->mnemonic == UD_Imov) {
		if (pud_obj->operand[1].type == UD_OP_IMM) {
			__dword dwImm = pud_obj->operand[1].lval.udword;
			*paddrAddress = (__address)dwImm;
			*pHookSaveFileAddress = pInstruction->pCurrFileAddress + 1;//opcode
			*pbIndirect = FALSE;
			return MOV_REG_IMM;
		} else if ((pud_obj->operand[1].type == UD_OP_MEM) && (pud_obj->operand[1].base == UD_NONE) && \
				(pud_obj->operand[1].index == UD_NONE) && (pud_obj->operand[1].offset)) {
			__dword dwImm = pud_obj->operand[1].lval.udword;
			*paddrAddress = (__address)dwImm;
			if (pud_obj->operand[0].base == UD_R_EAX)
				*pHookSaveFileAddress = pInstruction->pCurrFileAddress + 1;//opcode
			else
				*pHookSaveFileAddress = pInstruction->pCurrFileAddress + 2;//opcode modrm
			*pbIndirect = TRUE;
			return MOV_REG_MEM;
		}
	} else if (pud_obj->mnemonic == UD_Ilea) {
		if ((pud_obj->operand[1].type == UD_OP_MEM) && (pud_obj->operand[1].base == UD_NONE) && \
			(pud_obj->operand[1].index == UD_NONE) && (pud_obj->operand[1].offset)) {
			__dword dwImm = pud_obj->operand[1].lval.udword;
			*paddrAddress =(__address)dwImm;
			*pHookSaveFileAddress = pInstruction->pCurrFileAddress + 2;//opcode modrm
			*pbIndirect = FALSE;
			return LEA_REG_MEM;
		}
	}
	
	return MOV_NONE;
}
