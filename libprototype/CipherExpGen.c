#define __CipherExpGoNext__(pConfigure)		(__bool)(RollIt((pConfigure)->CipherExpRollArray))
#define __CipherExpIsKey__(pConfigure)		(__bool)(RollIt((pConfigure)->CipherExpRollArray))

__INLINE__ LOGIC_OPT __INTERNAL_FUNC__ GenerateReverseLogicOpt(LOGIC_OPT Opt) {
	LOGIC_OPT ReverseOpt = LOGIC_NONE;
	switch (Opt){
	case LOGIC_ROL:
		ReverseOpt = LOGIC_ROR;
		break;
	case LOGIC_ROR:
		ReverseOpt = LOGIC_ROL;
		break;
	case LOGIC_XOR:
		ReverseOpt = LOGIC_XOR;
		break;
	}
	return ReverseOpt;
}

__INLINE__ __void __INTERNAL_FUNC__ AsmLogicXor(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(XOR);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmLogicRol(ASMER_TYPE DestReg, __byte bImmediate, PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(ROL);WriteInst(DestReg);WriteInst(COMMA);
	__WriteImmediateOnBit__(ASMER_8_BITS, bImmediate);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmLogicRor(ASMER_TYPE DestReg, __byte bImmediate, PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(ROR);WriteInst(DestReg);WriteInst(COMMA);
	__WriteImmediateOnBit__(ASMER_8_BITS, bImmediate);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmLogicOpt(LOGIC_OPT Opt, ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {

}

__INLINE__ PCIPHEREXP __INTERNAL_FUNC__ CreateCipherExp() {
	PCIPHEREXP pCipherExp = __logic_new__(CIPHEREXP, 1);
	memset(pCipherExp, 0, sizeof(CIPHEREXP));
	return pCipherExp;
}

__INLINE__ LOGIC_OPT __INTERNAL_FUNC__ GenerateCipherOptWithNot() {
	LOGIC_OPT Opt = LOGIC_XOR + (GetRandDword() % (__MAX_LOGIC_OPT__ + 1));
	return Opt;
}

__INLINE__ LOGIC_OPT __INTERNAL_FUNC__ GenerateCipherOpt() {
	LOGIC_OPT Opt = LOGIC_XOR + (GetRandDword() % __MAX_LOGIC_OPT__);
	return Opt;
}

__void __INTERNAL_FUNC__ GenerateCipherExpOptObject(PCIPHEREXP pCipherExp, PPROTOTYPE_CONFIGURE pProtoTypeConfigure, LOGIC_OPT pPrevOpt) {
	if ((pPrevOpt == LOGIC_ROL) || (pPrevOpt == LOGIC_ROR)) {
		pCipherExp->ValBit = GetRandValBit();
		pCipherExp->dwVal = GetRandDword();
	} else {
		if (__CipherExpIsKey__(pProtoTypeConfigure))
			pCipherExp->bKey = TRUE;
		else {
			pCipherExp->ValBit = GetRandValBit();
			pCipherExp->dwVal = GetRandDword();
		}
	}


	// 是否拥有NOT操作符
	if (GenerateCipherOptWithNot() == MATH_NOT)
		pCipherExp->bNot = TRUE;
}

PCIPHEREXP __INTERNAL_FUNC__ GenerateCipherExpNext(PPROTOTYPE_CONFIGURE pProtoTypeConfigure, LOGIC_OPT pPrevOpt) {
	PCIPHEREXP pCipherMathExp = CreateCipherExp();
	GenerateCipherExpOptObject(pCipherMathExp, pProtoTypeConfigure, pPrevOpt);

	// 有下一个表达式
	if (__CipherExpGoNext__(pProtoTypeConfigure)) {
		pCipherMathExp->Opt = GenerateCipherOpt();
		pCipherMathExp->pNextExp = GenerateCipherExpNext(pProtoTypeConfigure, pCipherMathExp->Opt);
	}
	return pCipherMathExp;
}

PCIPHEREXP __INTERNAL_FUNC__ GenerateCipherExp(PPROTOTYPE_CONFIGURE pProtoTypeConfigure) {
	/*
	 * 第一个表达式为变量表达式
	 */
	PCIPHEREXP pCipherMathExp = CreateCipherExp();
	if (GenerateCipherOptWithNot() == MATH_NOT)//是否拥有NOT操作
		pCipherMathExp->bNot = TRUE;

	// 有下一个表达式
	if (__CipherExpGoNext__(pProtoTypeConfigure)) {
		pCipherMathExp->Opt = GenerateCipherOpt();
		pCipherMathExp->pNextExp = GenerateCipherExpNext(pProtoTypeConfigure, pCipherMathExp->Opt);
	}
	return pCipherMathExp;
}

PCIPHEREXP __INTERNAL_FUNC__ GenerateCipherExpression(PPROTOTYPE_CONFIGURE pProtoTypeConfigure) {
	PCIPHEREXP pCipherExp = GenerateCipherExp(pProtoTypeConfigure);
	return pCipherExp;
}

PCIPHEREXP __INTERNAL_FUNC__ ReverseCipherExp(PCIPHEREXP pCipherExp) {
	PCIPHEREXP pReverseCipherExp = CreateCipherExp();
	
	return pReverseCipherExp;
}

__integer __INTERNAL_FUNC__ CountCipherNode(PCIPHEREXP pCipherExp) {
	__integer iCount = 0;
	while (pCipherExp) {
		pCipherExp = pCipherExp->pNextExp;
		iCount++;
	}
	return iCount;
}

PCIPHEREXP __INTERNAL_FUNC__ ReverseCipherExpression(PCIPHEREXP pCipherExp) {
	/*
	 * 再压入操作符号与操作节点时
	 * 链中第一个节点不压入栈
	 * 最后一个操作符号不压入栈
	 *
	 * 逆向式中的第一个节点肯定没有操作符号
	 */
	__bool bIsFirst = TRUE;
	LOGIC_OPT *pOpt = NULL;
	PCIPHEREXP pReverseCipherExp = NULL, *pReverseCipherExpPoint = NULL;
	PCIPHEREXP pCurrCipherExp = pCipherExp;
	PSTACK pOptStack = init_stack(0);
	__integer i = 0, iCipherNodeCount = CountCipherNode(pCipherExp);
	PSTACK pCipherExpNodeStack = init_stack(sizeof(CIPHEREXP) * iCipherNodeCount);
	for (i = 0; i < iCipherNodeCount; i++) {
		if (i == 0) {//舍弃第一个节点
			push_stack(pOptStack, &(pCurrCipherExp->Opt), sizeof(LOGIC_OPT));
		} else if (i == iCipherNodeCount-1) {
			push_stack(pCipherExpNodeStack, pCurrCipherExp, sizeof(CIPHEREXP));
		} else {
			push_stack(pOptStack, &(pCurrCipherExp->Opt), sizeof(LOGIC_OPT));
			push_stack(pCipherExpNodeStack, pCurrCipherExp, sizeof(CIPHEREXP));
		}
		pCurrCipherExp = pCurrCipherExp->pNextExp;
	}

	/*
	 * 首先扩充第一个节点(变量)
	 */
	pReverseCipherExpPoint = &pReverseCipherExp;
	do {
		pOpt = (LOGIC_OPT *)pop_stack(pOptStack, sizeof(LOGIC_OPT));
		(*pReverseCipherExpPoint) = CreateCipherExp();

		// 如果是第一个节点
		if (bIsFirst) {
			(*pReverseCipherExpPoint)->bNot = pCipherExp->bNot;//第一个变量是否拥有NOT操作
			(*pReverseCipherExpPoint)->Opt = GenerateReverseLogicOpt(*pOpt);	
			bIsFirst = FALSE;
		} else {
			if (!pOpt)
				(*pReverseCipherExpPoint)->Opt = LOGIC_NONE;
			else
				(*pReverseCipherExpPoint)->Opt = *pOpt;
			pCurrCipherExp = (PCIPHEREXP)pop_stack(pCipherExpNodeStack, sizeof(CIPHEREXP));
			(*pReverseCipherExpPoint)->bKey = pCurrCipherExp->bKey;
			(*pReverseCipherExpPoint)->bNot = pCurrCipherExp->bNot;
			(*pReverseCipherExpPoint)->dwVal = pCurrCipherExp->dwVal;
		}/* end else */
		pReverseCipherExpPoint = &((*pReverseCipherExpPoint)->pNextExp);
	} while (pOpt);
	free_stack(pOptStack);
	free_stack(pCipherExpNodeStack);
	return pReverseCipherExp;
}

__void __INTERNAL_FUNC__ ReleaseCipherExp(PCIPHEREXP *pCipherExpPoint) {
	PCIPHEREXP pCurrCipherExp = (*pCipherExpPoint);
	PCIPHEREXP pSwitchCipherExp = NULL;
	while (pCurrCipherExp) {
		pSwitchCipherExp = pCurrCipherExp->pNextExp;
		__logic_delete__(pCurrCipherExp);
		pCurrCipherExp = pSwitchCipherExp;
	}
	(*pCipherExpPoint) = NULL;
}

__INLINE__ ASMER_TYPE __INTERNAL_FUNC__ SelectCipherExpReg(PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {
	ASMER_TYPE CurrReg;
	do {
		CurrReg = RandReg(pCipherExpAsmConfigure->Bit);
	} while ((CurrReg == pCipherExpAsmConfigure->ResultReg) || 
		(CurrReg == pCipherExpAsmConfigure->VarReg) || 
		(CurrReg == pCipherExpAsmConfigure->KeyReg) || 
		(CurrReg == R_ESP) ||
		(CurrReg == R_EBP));
	return CurrReg;
}

LOGIC_OPT __INTERNAL_FUNC__ AsmCipherExpOnSingleNode(PCIPHEREXP pCipherExp, __bool bFirstNode, ASMER_TYPE SwitchReg, \
													PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure, __bool bReverse,\
													LOGIC_OPT Opt) {
	if (pCipherExp->bNot) {
		if (bFirstNode) {//是第一个变量
			if (!bReverse) {
				WriteInst(LINESTART);WriteInst(NOT);WriteInst(pCipherExpAsmConfigure->VarReg);WriteInst(LINEND);
			}
			WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);WriteInst(pCipherExpAsmConfigure->VarReg);WriteInst(LINEND);
		} else if (pCipherExp->bKey) {
			WriteInst(LINESTART);WriteInst(NOT);WriteInst(pCipherExpAsmConfigure->KeyReg);WriteInst(LINEND);
			WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);WriteInst(pCipherExpAsmConfigure->KeyReg);WriteInst(LINEND);
		} else {
			if ((Opt == LOGIC_ROL) || (Opt == LOGIC_ROR)) {
				/*
				 * 如果是循环左移或者循环右移
				 * 目前不做任何操作
				 */
			} else {
				ASMER_TYPE TmpReg;
				do { TmpReg = SelectCipherExpReg(pCipherExpAsmConfigure); } while (TmpReg == SwitchReg);

				WriteInst(LINESTART);WriteInst(MOV);WriteInst(TmpReg);WriteInst(COMMA);
				__WriteImmediateOnBit__(pCipherExp->ValBit, pCipherExp->dwVal);WriteInst(LINEND);
				WriteInst(LINESTART);WriteInst(NOT);WriteInst(TmpReg);WriteInst(LINEND);
				WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);WriteInst(TmpReg);WriteInst(LINEND);
			}
		}/* end else */
	} else {
		if (bFirstNode) {//是第一个变量
			WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);WriteInst(pCipherExpAsmConfigure->VarReg);WriteInst(LINEND);
		} else if (pCipherExp->bKey) {
			WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);WriteInst(pCipherExpAsmConfigure->KeyReg);WriteInst(LINEND);
		} else {
			if ((Opt == LOGIC_ROL) || (Opt == LOGIC_ROR)) {
				/*
				 * 如果是循环左移或者循环右移
				 * 目前不做任何操作
				 */
			} else {
				WriteInst(LINESTART);WriteInst(MOV);WriteInst(SwitchReg);WriteInst(COMMA);
				__WriteImmediateOnBit__(pCipherExp->ValBit, pCipherExp->dwVal);WriteInst(LINEND);
			}
		}/* end else */
	}/* end else */

	return pCipherExp->Opt;
}

/*
 * 参数:
 * pCipherExp:当前节点
 * Opt:上一个节点的操作符
 * SwitchReg:上一个节点的值
 */
__void __INTERNAL_FUNC__ AsmCipherExpCodeOnRun(PCIPHEREXP pCipherExp, LOGIC_OPT Opt, ASMER_TYPE SwitchReg, \
											   PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure, __bool bReverse) {
	LOGIC_OPT CurrOpt;
	ASMER_TYPE TmpReg;

	if (!pCipherExp) {//如果是末尾则将计算结果存入结果寄存器
		WriteInst(LINESTART);WriteInst(MOV);WriteInst(pCipherExpAsmConfigure->ResultReg);WriteInst(COMMA);WriteInst(SwitchReg);WriteInst(LINEND);
		return;
	}
	
	do { TmpReg = SelectCipherExpReg(pCipherExpAsmConfigure); } while (TmpReg == SwitchReg);//选择一个临时寄存器

	CurrOpt = AsmCipherExpOnSingleNode(pCipherExp, FALSE, TmpReg, pCipherExpAsmConfigure, bReverse, Opt);
	
	/*
	 * 进行指令分析
	 */
	switch (Opt) {
	case LOGIC_ROL:
		AsmLogicRol(SwitchReg, (__byte)pCipherExp->dwVal, pCipherExpAsmConfigure);
	break;
	case LOGIC_ROR:
		AsmLogicRor(SwitchReg, (__byte)pCipherExp->dwVal, pCipherExpAsmConfigure);
	break;
	case LOGIC_XOR:
		AsmLogicXor(SwitchReg, TmpReg, pCipherExpAsmConfigure);
	break;
	}

	AsmCipherExpCodeOnRun(pCipherExp->pNextExp, CurrOpt, SwitchReg, pCipherExpAsmConfigure, bReverse);
	return;
}

__void __INTERNAL_FUNC__ AsmCipherExpCode(PCIPHEREXP pCipherExp, PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure, __bool bReverse) {
	ASMER_TYPE SwitchReg;
	LOGIC_OPT Opt;
	if (!(pCipherExp->pNextExp)) {//只有一个节点
		AsmCipherExpOnSingleNode(pCipherExp, TRUE, pCipherExpAsmConfigure->ResultReg, pCipherExpAsmConfigure, bReverse, LOGIC_NONE);
		return;
	}

	/*
	 * 两个节点以上,首先处理掉第一个节点
	 */
	SwitchReg = SelectCipherExpReg(pCipherExpAsmConfigure);
	Opt = AsmCipherExpOnSingleNode(pCipherExp, TRUE, SwitchReg, pCipherExpAsmConfigure, bReverse, LOGIC_NONE);
	AsmCipherExpCodeOnRun(pCipherExp->pNextExp, Opt, SwitchReg, pCipherExpAsmConfigure, bReverse);
} 

__INLINE__ __void __INTERNAL_FUNC__ InitCipherExpReg(PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure) {
	pCipherExpAsmConfigure->VarReg = RandReg(pCipherExpAsmConfigure->Bit);
	do {
		pCipherExpAsmConfigure->KeyReg = RandReg(pCipherExpAsmConfigure->Bit);
	} while (pCipherExpAsmConfigure->KeyReg == pCipherExpAsmConfigure->VarReg);
	do {
		pCipherExpAsmConfigure->ResultReg = RandReg(pCipherExpAsmConfigure->Bit);
	} while ((pCipherExpAsmConfigure->ResultReg == pCipherExpAsmConfigure->VarReg) || (pCipherExpAsmConfigure->ResultReg == pCipherExpAsmConfigure->KeyReg));
}

__memory __INTERNAL_FUNC__ GenerateCipherExpCode(PCIPHEREXP pCipherExp, __integer *piOutBinSize, \
												 PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE pCipherExpAsmConfigure, __integer iImageBase, \
												 __bool bReverse) {
	__memory pCipherExpCode = NULL;
	__integer iBinSize = 0;
	ASM_SOURCE AsmSource;

	// 产生默认的汇编代码结构
	GenerateDefAsmSource(&AsmSource);
	InitAssembler(&AsmSource, NULL);

	// 首先选择寄存器
	InitCipherExpReg(pCipherExpAsmConfigure);

	// 进行汇编
	AsmCipherExpCode(pCipherExp, pCipherExpAsmConfigure, bReverse);
	if (bReverse) {
		if (pCipherExp->bNot) {
			WriteInst(LINESTART);WriteInst(NOT);WriteInst(pCipherExpAsmConfigure->ResultReg);WriteInst(LINEND);
		}
	}/* end if */
	WriteInst(END);//写入源代码结束标记
	pCipherExpCode = Assembler(&AsmSource, &iBinSize, iImageBase);
	*piOutBinSize = iBinSize;
	return pCipherExpCode;
}
