/*
 * AnalysePrefix
 * 参数
 * pDisasmContext   DISASM_CONTEXT类型的指针，调用者分配空间
 * pCode            指向指令流的指针
 * 
 * 返回值
 * 指令流中前缀的字节数
 */
__byte __INTERNAL_FUNC__ AnalysePrefix(PDISASM_CONTEXT pDisasmContext, __byte *pCode, __byte bMaxLength) {
	__integer i = 0;
	__byte bPrefixLength = 0;

	if (bMaxLength >= 4)
		bMaxLength = 4;
	memset(pDisasmContext, 0, sizeof(DISASM_CONTEXT));
	for (i = 0; i < bMaxLength; i++) {
		if(((*pCode) == 0x26) || ((*pCode) == 0x2E) || ((*pCode) == 0x36) ||
			((*pCode) == 0x3E) || ((*pCode) == 0x64) || ((*pCode) == 0x65)) {
			pCode++;
			bPrefixLength++;
			continue;
		}
		
		if (((*pCode) == 0xF2)||((*pCode) == 0xF3)) {
			pDisasmContext->bIsRep = (*pCode);
			pCode++;
			bPrefixLength++;
			continue;
		}

		if ((*pCode) == 0x67) {
			pDisasmContext->bIsAddressSize16 = TRUE;
			pCode++;
			bPrefixLength++;
			continue;
		}

		if ((*pCode) == 0x66) {
			pDisasmContext->bIsOperandSize16 = 1;
			pCode++;
			bPrefixLength++;
			continue;
		}

		break;
	}
	pDisasmContext->bPrefixLength = bPrefixLength;
	return bPrefixLength;
}

/*
 * 判断指令序列是否CALL指令（忽略前缀）
 * 在StepOver中使用
 *
 * 返回值
 * 0 -> 不是CALL指令
 * n -> 此条CALL指令的字节数
 */
__byte __INTERNAL_FUNC__ IsCall(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength) {
	DISASM_CONTEXT DisasmContext;
	__byte bInstructionLength = 0;
	__byte bPrefixLength = AnalysePrefix(&DisasmContext,pCode, bMaxLength);
	switch(pCode[bPrefixLength]) {
	case 0x9A:{
		if (DisasmContext.bIsOperandSize16)
			bInstructionLength = 1 + 4;
		else
			bInstructionLength = 1 + 6;
	}break;
	case 0xE8:{
		if (DisasmContext.bIsOperandSize16)
			bInstructionLength = 1 + 2;
		else
			bInstructionLength = 1 + 4;
	}break;
	case 0xFF:{
		__byte bRegOpcode;
		__byte bLength = 0;
		if (DisasmContext.bIsAddressSize16)
			GetInstructionArgsLength16(pCPU, pCode + 1, bMaxLength - 1 - bPrefixLength, &bLength);
		else
			GetInstructionArgsLength32(pCPU, pCode + 1, bMaxLength - 1 - bPrefixLength, &bLength);
			bRegOpcode = (pCode[1] & 0x38) >> 3;
			if ((bRegOpcode == 2) || (bRegOpcode == 3))
				bInstructionLength = 1 + bLength;
			else//不是CALL指令
				bInstructionLength = 0;
	}break;
	default:
		bInstructionLength = 0;
	}
	return ((bInstructionLength) ? (bInstructionLength + bPrefixLength) : 0);
}

/*
 * 判断指令序列是否是带前缀的串指令
 * 在StepOver中使用
 *
 * 返回值
 * 0 -> 不是带前缀的串指令指令
 * n -> 此条带前缀的串指令的字节数
 */
__byte __INTERNAL_FUNC__ IsRepString(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength) {
	DISASM_CONTEXT DisasmContext;
	__byte bInstructionLength = 0;
	__byte bPrefixLength = AnalysePrefix(&DisasmContext, pCode, bMaxLength);
	if (!DisasmContext.bIsRep)//没有重复前缀
		return 0;

	switch(pCode[bPrefixLength]){
	case 0xA4:
	case 0xA5:
	case 0xA6:
	case 0xA7:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xAF:{
		bInstructionLength = 1;
	}break;
	default:
		bInstructionLength = 0;
	}
	return  ((bInstructionLength) ? (bInstructionLength + bPrefixLength) : 0);
}


/*
 * 获得CALL指令的长度
 *
 * 返回值
 * 0 -> 不是CALL指令
 * n -> 此条CALL指令的字节数
 */
__byte __INTERNAL_FUNC__ GetCallLength(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength, PDISASM_CONTEXT pDisasmContext) {
	__byte bInstructionLength = 0;
	switch(pCode[0]){
	case 0x9A:{
		if (pDisasmContext->bIsOperandSize16)
			bInstructionLength = 1 + 4;
		else
			bInstructionLength = 1 + 6;
	}break;
	case 0xE8:{
		if (pDisasmContext->bIsOperandSize16)
			bInstructionLength = 1 + 2;
		else
			bInstructionLength = 1 + 4;
	}break;
	case 0xFF:{
		__byte bRegOpcode;
		__byte bLength = 0;
		if (pDisasmContext->bIsAddressSize16)
			GetInstructionArgsLength16(pCPU, pCode + 1, bMaxLength - 1, &bLength);
		else 
			GetInstructionArgsLength32(pCPU, pCode + 1, bMaxLength - 1, &bLength);

		bRegOpcode = (pCode[1] & 0x38) >> 3;
		if ((bRegOpcode == 2) || (bRegOpcode == 3))
			bInstructionLength = 1 + bLength;
		else//不是CALL指令
			bInstructionLength = 0;
	}break;
	default:
		bInstructionLength = 0;
	}
	return  bInstructionLength;
}

/*
 * 获得JMP指令的长度
 *
 * 返回值
 * 0 -> 不是CALL指令
 * n -> 此条CALL指令的字节数
 */
__byte __INTERNAL_FUNC__ GetJMPLength(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength, PDISASM_CONTEXT pDisasmContext){

	__byte bInstructionLength = 0;
	switch(pCode[0]){
	case 0xEB: {
			bInstructionLength = 2;
	}break;
	case 0xE9: {
		if (pDisasmContext->bIsOperandSize16)
			bInstructionLength = 1 + 2;
		else
			bInstructionLength = 1 + 4;
	}break;
	case 0xFF:{
		__byte bRegOpcode;
		__byte bLength = 0;
		if (pDisasmContext->bIsAddressSize16)
			GetInstructionArgsLength16(pCPU, pCode + 1, bMaxLength - 1, &bLength);
		else
			GetInstructionArgsLength32(pCPU, pCode + 1, bMaxLength - 1, &bLength);
		bRegOpcode = (pCode[1] & 0x38) >> 3;
		if ((bRegOpcode == 4) || (bRegOpcode == 5))
			bInstructionLength = 1 + bLength;
		else//不是JMP指令
			bInstructionLength = 0;
		bInstructionLength = 1 + bLength;
	}break;
	case 0xEA:{
		if (pDisasmContext->bIsOperandSize16)
			bInstructionLength = 1 + 2 + 2;
		else
			bInstructionLength = 1 + 2 + 4;
	}break;
	default:
		bInstructionLength = 0;
	}
	return bInstructionLength;
}

/*
 * 获得RET指令的长度
 *
 * 返回值
 * 0 -> 不是RET指令
 * n -> 此条RET指令的字节数
 */
__byte __INTERNAL_FUNC__ GetRetLength(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength, PDISASM_CONTEXT pDisasmContext) {
	__byte bInstructionLength = 0;
	pDisasmContext = NULL;
	bMaxLength = 0;
	switch(pCode[0]) {
	case 0xC2:{
		bInstructionLength = 3;
	}break;
	case 0xC3:{
		bInstructionLength = 1;
	}break;
	default:
		bInstructionLength = 0;
	}
	return bInstructionLength;
}

__byte __INTERNAL_FUNC__ GetInstructionLength(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength) {
	DISASM_CONTEXT DisasmContext;
	__byte InstructionLength = 0;
	AnalysePrefix(&DisasmContext, pCode, bMaxLength);
	if ((InstructionLength = GetCallLength(pCPU, pCode + DisasmContext.bPrefixLength, bMaxLength - DisasmContext.bPrefixLength, &DisasmContext)))
		return InstructionLength + DisasmContext.bPrefixLength;
	if((InstructionLength = GetJMPLength(pCPU, pCode + DisasmContext.bPrefixLength, bMaxLength - DisasmContext.bPrefixLength, &DisasmContext)))
		return InstructionLength + DisasmContext.bPrefixLength;
	if((InstructionLength = GetRetLength(pCPU, pCode + DisasmContext.bPrefixLength, bMaxLength - DisasmContext.bPrefixLength, &DisasmContext)))
		return InstructionLength + DisasmContext.bPrefixLength;
	return 0;
}


