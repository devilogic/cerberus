#include "MathExpGen.h"

/*
 * 1.使用GenerateMathExp产生一个pMathExp表达式结构
 * 2.使用GetMathExpVariableNumber(pMathExp)获取表达式中变量的个数
 * 3.生成一个pMathExpAsmGenConfigure的变量并对其分配栈空间与栈基
 * 4.使用GenerateMathExpAsmSource(pMathExp, pMathExpAsmGenConfigure)生成汇编源代码pAsmSource结构
 * 5.使用Assembler函数进行汇编
 * 6.使用ReleaseMathExp(&pMathExp)释放表达式的内存
 *
 * !注:VarReg是衡量寄存器,在运算中只负责转移变量数据,不负责进行运算
 */

#define __OpObjectIsVariable__()						(GetRandDword() % 2 == 0)
//#define __ConstToMathExpOptBitConst__()\
//	if (pMathExp->Bit == ASMER_8_BITS) pMathExp->dwVal = pMathExp->dwVal & 0xFF;\
//	else if (pMathExp->Bit == ASMER_16_BITS) pMathExp->dwVal = pMathExp->dwVal & 0xFFFF;\
//	else if (pMathExp->Bit == ASMER_32_BITS) pMathExp->dwVal = pMathExp->dwVal & 0xFFFFFFFF;
#define __WriteImmediateOnBit__(Bit, Immediate){\
	__dword dwImmediate = 0;\
	if ((Bit) == ASMER_8_BITS) {\
		dwImmediate = (Immediate) & 0xFF;\
		WriteImmediate((__memory)&dwImmediate, (Bit));\
	} else if ((Bit) == ASMER_16_BITS) {\
		dwImmediate = (Immediate) & 0xFFFF;\
		WriteImmediate((__memory)&dwImmediate, (Bit));\
	} else if ((Bit) == ASMER_32_BITS) {\
		dwImmediate = (Immediate) & 0xFFFFFFFF;\
		WriteImmediate((__memory)&dwImmediate, (Bit));}}

#define __WriteImmediateOnBitButTokenIs32Bits__(Bit, Immediate){\
	__dword dwImmediate = 0;\
	if ((Bit) == ASMER_8_BITS) {\
		dwImmediate = (Immediate) & 0xFF;\
		WriteImmediate((__memory)&dwImmediate, ASMER_32_BITS);\
	} else if ((Bit) == ASMER_16_BITS) {\
		dwImmediate = (Immediate) & 0xFFFF;\
		WriteImmediate((__memory)&dwImmediate, ASMER_32_BITS);\
	} else if ((Bit) == ASMER_32_BITS) {\
		dwImmediate = (Immediate) & 0xFFFFFFFF;\
		WriteImmediate((__memory)&dwImmediate, ASMER_32_BITS);}}

#define __GenerateMathOpt__()				(MATH_OPT)(GetRandDword() % __MAX_MATH_OPT__ + 1)
#define __GenerateMathOptWithOutNot__()		(MATH_OPT)(GetRandDword() % (__MAX_MATH_OPT__ - 1) + 1)
#define __HasPassMathExp__(pConfigure)		(RollIt((pConfigure)->MathExpRollArray))
#define __HasSubMathExp__(pConfigure)		(RollIt((pConfigure)->MathExpRollArray))

__INLINE__ ASMER_BIT __INTERNAL_FUNC__ GetRandValBit() {
	ASMER_BIT Bit;
	__integer iIndex = (GetRandDword() % 3) + 1;
	switch (iIndex) {
	case 1:
		Bit = ASMER_8_BITS;
	break;
	case 2:
		Bit = ASMER_16_BITS;
	break;
	case 3:
		Bit = ASMER_32_BITS;
	break;
	}
	return Bit;
}

__INLINE__ MATH_OPT __INTERNAL_FUNC__ GenerateMathOpt() {
	MATH_OPT Opt = __GenerateMathOpt__();
	return Opt;
}

__INLINE__ MATH_OPT __INTERNAL_FUNC__ GenerateMathOptWithOutNot() {
	MATH_OPT Opt = __GenerateMathOptWithOutNot__();
	return Opt;
}

__INLINE__ MATH_OPT __INTERNAL_FUNC__ GenerateReverseMathOpt(MATH_OPT Opt) {
	MATH_OPT ReverseOpt = MATH_NONE;
	switch (Opt){
	case MATH_ADD:
		ReverseOpt = MATH_SUB;
	break;
	case MATH_SUB:
		ReverseOpt = MATH_ADD;
	break;
	case MATH_MUL:
		ReverseOpt = MATH_DIV;
	break;
	case MATH_DIV:
		ReverseOpt = MATH_MUL;
	break;
	case MATH_XOR:
		ReverseOpt = MATH_XOR;
	break;
	}
	return ReverseOpt;
}

/*
 * 只产生一层根表达式模型,不决定子表达式是什么
 * 只决定运算符与分配主副表达式结构的内存
 * 生成后,如果有子表达式则无常量值,无子表达式则
 * 一定有常量值或者变量
 * 被动表达式不能再有被动表达式,只能拥有子表达式
 */
__INLINE__ PMATHEXP __INTERNAL_FUNC__ CreateMathExp() {
	PMATHEXP pMathExp = __logic_new__(MATHEXP, 1);
	memset(pMathExp, 0, sizeof(MATHEXP));
	return pMathExp;
}

__INLINE__ ASMER_TYPE __INTERNAL_FUNC__ RandReg(ASMER_BIT Bit) {
	ASMER_TYPE CurrReg = NONE;
	if (Bit == ASMER_8_BITS) {
		CurrReg = R_AL + (GetRandDword() % 8);
	} else if (Bit == ASMER_16_BITS) {
		do {
			CurrReg = R_AX + (GetRandDword() % 8);
		} while (CurrReg == R_SP);
	} else if (Bit == ASMER_32_BITS) {
		do {
			CurrReg = R_EAX + (GetRandDword() % 8);
		} while (CurrReg == R_ESP);
	}
	return CurrReg;
}

__INLINE__ ASMER_TYPE __INTERNAL_FUNC__ SelectCurrReg(PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE CurrReg;
	do {
		CurrReg = RandReg(pMathExpAsmConfigure->Bit);
	} while ((CurrReg == pMathExpAsmConfigure->ResultReg) || 
		(CurrReg == pMathExpAsmConfigure->VarReg) || 
		(CurrReg == pMathExpAsmConfigure->TmpReg) ||
		(CurrReg == R_ESP) || (CurrReg == R_SP));
	return CurrReg;
}

PMATHEXP __INTERNAL_FUNC__ GenerateMathRootExp(PPROTOTYPE_CONFIGURE pProtoTypeConfigure) {
	MATH_OPT Opt;
	PMATHEXP pMathExp = CreateMathExp();

	// 是否存在被动表达式
	if (__HasPassMathExp__(pProtoTypeConfigure)) {//拥有被动表达式
		/*
		 * 随机选定一个操作符
		 * 如果是NOT操作符设定后
		 * 重新生成操作符
		 */
		Opt = GenerateMathOpt();
		if (Opt == MATH_NOT) {
			pMathExp->bNot = TRUE;
			Opt = GenerateMathOptWithOutNot();
			pMathExp->Opt = Opt;
		} else
			pMathExp->Opt = Opt;
		// 进入生成被动表达式
		pMathExp->pPassivityExp = CreateMathExp();
		// 被动表达式是否需要NOT操作符
		Opt = GenerateMathOpt();
		if (Opt == MATH_NOT)
			pMathExp->pPassivityExp->bNot = TRUE;

		///*
		// * 最后验证被动表达式是否是一个变量,如果是一个变量则
		// * 验证当前操作符是否是一个除法操作,如果为除法操作则
		// * 重新生成操作符
		// */
		//if (pMathExp->pPassivityExp->bVariable) {
		//	while (pMathExp->Opt == MATH_DIV) {
		//		pMathExp->Opt = GenerateMathOptWithOutNot();
		//	}
		//}/* end if */
	} else {//没有被动表达式
		Opt = GenerateMathOpt();
		if (Opt == MATH_NOT)
			pMathExp->bNot = TRUE;
	}
	return pMathExp;
}

/*
 * 产生变量或者常数
 */
__void __INTERNAL_FUNC__ GenerateMathExpOptObject(PMATHEXP pMathExp) {
	if (__OpObjectIsVariable__())
		pMathExp->bVariable = TRUE;
	else {
		pMathExp->ValBit = GetRandValBit();
		pMathExp->dwVal = GetRandDword();//随机选定一个常数
	}
}

/*
 * 产生子数学计算表达式链
 * 这里采用宽度优先算法,先生成子表达式
 */
PMATHEXP __INTERNAL_FUNC__ GenerateMathExp(PPROTOTYPE_CONFIGURE pProtoTypeConfigure) {
	PMATHEXP pMathExp = GenerateMathRootExp(pProtoTypeConfigure);//产生一个根
	PMATHEXP pPassMathExp = pMathExp->pPassivityExp;
	/*
	 * 决定主表达式是否有子表达式
	 * 如果没有子表达式则随机选定一个常数
	 */
	if (__HasSubMathExp__(pProtoTypeConfigure))
		pMathExp->pSubExp = GenerateMathExp(pProtoTypeConfigure);
	else
		GenerateMathExpOptObject(pMathExp);

	// 生成被动表达式的子表达式
	if (pPassMathExp) {
		if (__HasSubMathExp__(pProtoTypeConfigure))
			pPassMathExp->pSubExp = GenerateMathExp(pProtoTypeConfigure);
		else
			GenerateMathExpOptObject(pPassMathExp);
	}/* end if */
	return pMathExp;
}

__dword __INTERNAL_FUNC__ GetMathExpVariableNumber(PMATHEXP pMathExp) {
	PMATHEXP pCurr = pMathExp, pPassMathExp = pCurr->pPassivityExp;
	__integer iVarCount = 0;
	// 计算子表达式的变量个数
	if (pCurr->pSubExp)
		iVarCount += GetMathExpVariableNumber(pCurr->pSubExp);
	
	// 计算被动表达式的变量个数
	if (pPassMathExp)
		iVarCount += GetMathExpVariableNumber(pPassMathExp);

	// 计算自身是否是变量
	if (pCurr->bVariable)
		iVarCount++;

	return iVarCount;
}

__dword __INTERNAL_FUNC__ GetMathExpImmediateNumber(PMATHEXP pMathExp) {
	PMATHEXP pCurr = pMathExp, pPassMathExp = pCurr->pPassivityExp;
	__integer iImmediateCount = 0;
	// 计算子表达式的变量个数
	if (pCurr->pSubExp)
		iImmediateCount += GetMathExpImmediateNumber(pCurr->pSubExp);

	// 计算被动表达式的变量个数
	if (pPassMathExp)
		iImmediateCount += GetMathExpImmediateNumber(pPassMathExp);

	// 计算自身是否是变量
	if (!(pCurr->bVariable))
		iImmediateCount++;

	return iImmediateCount;
}

__INLINE__ ASM_BLOCK_TYPE __INTERNAL_FUNC__ ReturnAsmBlockType(PMATHEXP pMathExp) {
	if (pMathExp->bNot) {//存在NOT操作符
		if (pMathExp->pPassivityExp) {//存在被动表达式
			if (pMathExp->pSubExp) {//存在子表达式
				return ASM_BLOCK_TYPE_NOT_SUB_PASSIV;
			} else {//不存在子表达式
				if (pMathExp->bVariable)//为变量
					return ASM_BLOCK_TYPE_NOT_VAR_PASSIV;
				else//为常量
					return ASM_BLOCK_TYPE_NOT_CONST_PASSIV;
			}
		} else {//不存在被动表达式
			if (pMathExp->pSubExp) {//存在子表达式
				return ASM_BLOCK_TYPE_NOT_SUB;
			} else {//不存在子表达式
				if (pMathExp->bVariable)//为变量
					return ASM_BLOCK_TYPE_NOT_VAR;
				else//为常量
					return ASM_BLOCK_TYPE_NOT_CONST;
			}
		}
	} else {//不存在NOT操作符
		if (pMathExp->pPassivityExp) {//存在被动表达式
			if (pMathExp->pSubExp) {//存在子表达式
				return ASM_BLOCK_TYPE_SUB_PASSIV;
			} else {//不存在子表达式
				if (pMathExp->bVariable)//为变量
					return ASM_BLOCK_TYPE_VAR_PASSIV;
				else//为常量
					return ASM_BLOCK_TYPE_CONST_PASSIV;
			}
		} else {//不存在被动表达式
			if (pMathExp->pSubExp) {//存在子表达式
				return ASM_BLOCK_TYPE_SUB;
			} else {//不存在子表达式
				if (pMathExp->bVariable)//为变量
					return ASM_BLOCK_TYPE_VAR;
				else//为常量
					return ASM_BLOCK_TYPE_CONST;
			}
		}	
	}/* end else */

	return ASM_BLOCK_TYPE_NONE;
}

__void __INTERNAL_FUNC__ AsmBlock(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure);//函数声明
__INLINE__ __void __INTERNAL_FUNC__ AsmAdd(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(ADD);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmSub(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(SUB);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmMul(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MUL);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmDiv(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {

	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(R_EAX);WriteInst(COMMA);WriteInst(DestReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(DIV);WriteInst(SourceReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(DestReg);WriteInst(COMMA);WriteInst(R_EAX);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmMod(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(R_EAX);WriteInst(COMMA);WriteInst(DestReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(DIV);WriteInst(SourceReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(DestReg);WriteInst(COMMA);WriteInst(R_EDX);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmOr(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(OR);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmAnd(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(ADD);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmXor(ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(DestReg);WriteInst(COMMA);WriteInst(SourceReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmOpt(MATH_OPT Opt, ASMER_TYPE DestReg, ASMER_TYPE SourceReg, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	switch (Opt) {
	case MATH_ADD:{
		AsmAdd(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_SUB:{
		AsmSub(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_MUL:{
		AsmMul(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_DIV:{
		AsmDiv(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_MOD:{
		AsmMod(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_OR:{
		AsmOr(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_AND:{
		AsmAnd(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	case MATH_XOR:{
		AsmXor(DestReg, SourceReg, pMathExpAsmConfigure);
	}break;
	}
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnVar(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(COMMA);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnConst(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(COMMA);
	__WriteImmediateOnBitButTokenIs32Bits__(pMathExp->ValBit, pMathExp->dwVal);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotVar(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(COMMA);WriteInst(pMathExpAsmConfigure->VarReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(NOT);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotConst(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	WriteInst(LINESTART);WriteInst(MOV);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(COMMA);
	__WriteImmediateOnBitButTokenIs32Bits__(pMathExp->ValBit, pMathExp->dwVal);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(NOT);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnVarPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlockOnVar(pMathExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotVarPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlockOnNotVar(pMathExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnConstPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlockOnConst(pMathExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotConstPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlockOnNotConst(pMathExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnSub(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	AsmBlock(pMathExp->pSubExp, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotSub(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	AsmBlock(pMathExp->pSubExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(NOT);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnSubPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlock(pMathExp->pSubExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

__INLINE__ __void __INTERNAL_FUNC__ AsmBlockOnNotSubPassiv(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASMER_TYPE TmpReg = pMathExpAsmConfigure->TmpReg;
	AsmBlock(pMathExp->pPassivityExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(PUSH);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	AsmBlock(pMathExp->pSubExp, pMathExpAsmConfigure);
	WriteInst(LINESTART);WriteInst(NOT);WriteInst(pMathExpAsmConfigure->ResultReg);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(POP);WriteInst(TmpReg);WriteInst(LINEND);
	AsmOpt(pMathExp->Opt, pMathExpAsmConfigure->ResultReg, TmpReg, pMathExpAsmConfigure);
}

/*
 * 汇编优先级
 * 被动表达式 > 子表达式 > 主动表达式
 * 方向:从右节点向左向上
 */
__void __INTERNAL_FUNC__ AsmBlock(PMATHEXP pMathExp, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	ASM_BLOCK_TYPE AsmBlockType = ReturnAsmBlockType(pMathExp);//返回表达式类型

	switch (AsmBlockType) {
	case ASM_BLOCK_TYPE_NOT_SUB_PASSIV:
		AsmBlockOnNotSubPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_SUB_PASSIV:
		AsmBlockOnSubPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_NOT_SUB:
		AsmBlockOnNotSub(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_SUB:
		AsmBlockOnSub(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_NOT_CONST_PASSIV:
		AsmBlockOnNotConstPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_CONST_PASSIV:
		AsmBlockOnConstPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_NOT_VAR_PASSIV:
		AsmBlockOnNotVarPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_VAR_PASSIV:
		AsmBlockOnVarPassiv(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_NOT_CONST:
		AsmBlockOnNotConst(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_NOT_VAR:
		AsmBlockOnNotVar(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_CONST:
		AsmBlockOnConst(pMathExp, pMathExpAsmConfigure);
	break;
	case ASM_BLOCK_TYPE_VAR:
		AsmBlockOnVar(pMathExp, pMathExpAsmConfigure);
	break;
	}/* end switch */
}

/*
 * 生成数学表达式
 */
PMATHEXP __INTERNAL_FUNC__ GenerateMathExpression(PPROTOTYPE_CONFIGURE pProtoTypeConfigure) {
	PMATHEXP pMathExp = GenerateMathExp(pProtoTypeConfigure);
	return pMathExp;
}

__INLINE__ __void __INTERNAL_FUNC__ InitMathExpReg(PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure) {
	pMathExpAsmConfigure->VarReg = RandReg(pMathExpAsmConfigure->Bit);
	do {
		pMathExpAsmConfigure->TmpReg = RandReg(pMathExpAsmConfigure->Bit);
	} while (pMathExpAsmConfigure->TmpReg == pMathExpAsmConfigure->VarReg);
	do {
		pMathExpAsmConfigure->ResultReg = RandReg(pMathExpAsmConfigure->Bit);
	} while ((pMathExpAsmConfigure->ResultReg == pMathExpAsmConfigure->VarReg) || (pMathExpAsmConfigure->ResultReg == pMathExpAsmConfigure->TmpReg));
}

/*
 * 形成与上下文无关的汇编代码
 */
__memory __INTERNAL_FUNC__ GenerateMathExpCode(PMATHEXP pMathExp, __integer *piOutBinSize, PPROTOTYPE_MATHEXP_ASM_CONFIGURE pMathExpAsmConfigure, __integer iImageBase) {
	__memory pMathExpCode = NULL;
	__integer iBinSize = 0;
	ASM_SOURCE AsmSource;

	// 产生默认的汇编代码结构
	GenerateDefAsmSource(&AsmSource);
	InitAssembler(&AsmSource, NULL);

	// 首先选择寄存器
	InitMathExpReg(pMathExpAsmConfigure);

	// 进行汇编
	AsmBlock(pMathExp, pMathExpAsmConfigure);
	WriteInst(END);//写入源代码结束标记
	pMathExpCode = Assembler(&AsmSource, &iBinSize, iImageBase);
	*piOutBinSize = iBinSize;
	return pMathExpCode;
}

/*
 * 删除节点采用深度优先算法
 */
__void __INTERNAL_FUNC__ ReleaseMathExp(PMATHEXP *pMathExpPoint) {
	PMATHEXP pCurr = *pMathExpPoint;

	if (pCurr->pSubExp)
		ReleaseMathExp(&(pCurr->pSubExp));

	if (pCurr->pPassivityExp)
		ReleaseMathExp(&(pCurr->pPassivityExp));

	__logic_delete__(pCurr);
	*pMathExpPoint = NULL;
	return;
}

#include "CipherExpGen.c"
