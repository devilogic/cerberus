#define __Is8BitRegisterTokenInAsmer__(Token)		(((Token) >= ASMER_TK_REG_AL) && ((Token) <= ASMER_TK_REG_BH))
#define __Is16BitRegisterTokenInAsmer__(Token)		(((Token) >= ASMER_TK_REG_AX) && ((Token) <= ASMER_TK_REG_DI))
#define __Is32BitRegisterTokenInAsmer__(Token)		(((Token) >= ASMER_TK_REG_EAX) && ((Token) <= ASMER_TK_REG_EDI))
#define __IsRegisterTokenInAsmer__(Token)			(((Token) >= ASMER_TK_REG_AL) && ((Token) <= ASMER_TK_REG_EDI))
#define __IsTypePtrTokenInAsmer__(Token)			(((Token) >= ASMER_TK_KW_BYTE_PTR) && ((Token) <= ASMER_TK_KW_DWORD_PTR))
#define __IsDisplacementTokenInAsmer__(Token)		(((Token) >= ASMER_TK_KW_DISPLACEMENT8) && ((Token) <= ASMER_TK_KW_DISPLACEMENT32))
#define __IsImmediateTokenInAsmer__(Token)			(((Token) >= ASMER_TK_KW_IMMEDIATE8) && ((Token) <= ASMER_TK_KW_IMMEDIATE32))
#define __IsScaleTokenInAsmer__(Token)				(((Token) >= ASMER_TK_KW_SCALE_1) && ((Token) <= ASMER_TK_KW_SCALE_8))
#define __IsAddrLabelTokenInAsmer__(Token)			(((Token) >= ASMER_TK_KW_ADDR_LAB) && ((Token) <= ASMER_TK_KW_ADDR_VALUE_LAB))
#define __IsMemEndTokenInAsmer__(Token)				(((Token) == ASMER_TK_KW_MEMEND))
#define __IsEspTokenInAsmer__(Token)				((Token) == ASMER_TK_REG_ESP)

#define __SetBitOnTypePtrToOpt__(Opt, TypePtr)\
	if ((TypePtr) == ASMER_TK_KW_BYTE_PTR)\
		(Opt).Bit = ASMER_8_BITS;\
	else if ((TypePtr) == ASMER_TK_KW_WORD_PTR)\
		(Opt).Bit = ASMER_16_BITS;\
	else if ((TypePtr) == ASMER_TK_KW_DWORD_PTR)\
		(Opt).Bit = ASMER_32_BITS;

#define __SetScaleTokenInAsmer__(Opt, Token)\
	if ((Token) == ASMER_TK_KW_SCALE_1) (Opt).Scale = AS_1;\
	else if ((Token) == ASMER_TK_KW_SCALE_2) (Opt).Scale = AS_2;\
	else if ((Token) == ASMER_TK_KW_SCALE_4) (Opt).Scale = AS_4;\
	else if ((Token) == ASMER_TK_KW_SCALE_8) (Opt).Scale = AS_8;

#define __SetBitOnRegisterToOpt__(Opt, Register)\
	if (__Is8BitRegisterTokenInAsmer__(Register) == TRUE)\
	(Opt).Bit = ASMER_8_BITS;\
	else if (__Is16BitRegisterTokenInAsmer__(Register) == TRUE)\
	(Opt).Bit = ASMER_16_BITS;\
	else if (__Is32BitRegisterTokenInAsmer__(Register) == TRUE)\
	(Opt).Bit = ASMER_32_BITS;

#define __SetBitOnDisplacementToOpt__(Opt, DispToken)\
	if ((DispToken) == ASMER_TK_KW_DISPLACEMENT8)\
	(Opt).OffsetBit = ASMER_8_BITS;\
	else if ((DispToken) == ASMER_TK_KW_DISPLACEMENT32)\
	(Opt).OffsetBit = ASMER_32_BITS;

#define __SetDisplacementToOpt__(Opt, DispToken)\
	if ((DispToken) == ASMER_TK_KW_DISPLACEMENT8)\
	(Opt).Val.uByte = (BYTE)NextConst();\
	else if ((DispToken) == ASMER_TK_KW_DISPLACEMENT32)\
	(Opt).Val.uDword = (DWORD)NextConst();

#define __SetBitOnImmediateToOpt__(Opt, ImmToken)\
	if ((ImmToken) == ASMER_TK_KW_IMMEDIATE8)\
	{(Opt).Bit = ASMER_8_BITS;(Opt).OffsetBit = ASMER_8_BITS;}\
	else if ((ImmToken) == ASMER_TK_KW_IMMEDIATE16)\
	{(Opt).Bit = ASMER_16_BITS;(Opt).OffsetBit = ASMER_16_BITS;}\
	else if ((ImmToken) == ASMER_TK_KW_IMMEDIATE32)\
	{(Opt).Bit = ASMER_32_BITS;(Opt).OffsetBit = ASMER_32_BITS;}

#define __SetImmediateToOpt__(Opt, ImmToken)\
	if ((ImmToken) == ASMER_TK_KW_IMMEDIATE8)\
	(Opt).Val.uByte = (BYTE)NextConst();\
	else if ((ImmToken) == ASMER_TK_KW_IMMEDIATE16)\
	(Opt).Val.uWord = (WORD)NextConst();\
	else if ((ImmToken) == ASMER_TK_KW_IMMEDIATE32)\
	(Opt).Val.uDword = (DWORD)NextConst();

/*
 * [displacement]
 */
INLINE BOOL CHARM_INTERNAL_FUNC AnalyzeMemOperandStartByDisplacement(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();
	if (__IsDisplacementTokenInAsmer__(Token) == FALSE) return FALSE;
	__SetBitOnDisplacementToOpt__(pAsmObj->Operand[bOptIndex], Token);
	__SetDisplacementToOpt__(pAsmObj->Operand[bOptIndex], Token);
	// 下面标记必须为结束符
	Token = NextToken();
	if (__IsMemEndTokenInAsmer__(Token) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 * [reg + $reg + displacement]
 * [reg + $reg]
 */
INLINE BOOL CHARM_INTERNAL_FUNC AnalyzeMemOperandNextByRegister(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();
	if (__Is32BitRegisterTokenInAsmer__(Token) != FALSE) return FALSE;
	__RegTokenToReg__(pAsmObj->Operand[bOptIndex].Base, Token);
	// 可能是偏移或者结束符
	Token = NextToken();
	if (__IsDisplacementTokenInAsmer__(Token) == TRUE)
	{
		BackToken();
		return AnalyzeMemOperandStartByDisplacement(pAsmObj, bOptIndex);
	}
	else if (__IsMemEndTokenInAsmer__(Token) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 * [$reg + reg + displacement]
 * [$reg + displacement]
 * [$reg]
 */
INLINE BOOL CHARM_INTERNAL_FUNC AnalyzeMemOperandStartByRegister(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();
	// 必须为寄存器
	if (__Is32BitRegisterTokenInAsmer__(Token) == FALSE) return FALSE;
	ASM_TOKEN Register = Token;

	// 下面应该是加号,减号或者结束符
	Token = NextToken();
	if (Token == ASMER_TK_KW_ADD)
	{
		Token = NextToken();
		// 可能为寄存器也可能为偏移
		if (__IsRegisterTokenInAsmer__(Token) == TRUE)
		{
			if (__IsEspTokenInAsmer__(Register) == TRUE) return FALSE;//Index寄存器不能为ESP
			__RegTokenToReg__(pAsmObj->Operand[bOptIndex].Index, Register);
			pAsmObj->Operand[bOptIndex].Scale = AS_1;//如果存在第二个寄存器则刻度为1
			BackToken();
			return AnalyzeMemOperandNextByRegister(pAsmObj, bOptIndex);
		}
		else if (__IsDisplacementTokenInAsmer__(Token) == TRUE)
		{
			__RegTokenToReg__(pAsmObj->Operand[bOptIndex].Base, Register);
			BackToken();
			return AnalyzeMemOperandStartByDisplacement(pAsmObj, bOptIndex);
		}
		else
		{
			return FALSE;
		}
	}
	else if (Token == ASMER_TK_KW_SUB)
	{
		Token = NextToken();
		// 这个标记只能为偏移
		if (__IsDisplacementTokenInAsmer__(Token) == FALSE) return FALSE;
		// 转换后重新设置当前偏移的值
		DWORD dwNowDisplacement = __ToNegative__(NextConst());
		BackConst();
		ResetConst(dwNowDisplacement);
		__RegTokenToReg__(pAsmObj->Operand[bOptIndex].Base, Register);
		BackToken();
		return AnalyzeMemOperandStartByDisplacement(pAsmObj, bOptIndex);
	}
	else if (__IsMemEndTokenInAsmer__(Token) == TRUE)
	{
		__RegTokenToReg__(pAsmObj->Operand[bOptIndex].Base, Register);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 * 处理标号
 */
INLINE BOOL CHARM_INTERNAL_FUNC ReferenceAddrLabel(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();
	if (__IsAddrLabelTokenInAsmer__(Token) == FALSE) return FALSE;
	
	// 获取到地址标号节点
	CHAR *pSymbolName = NextSymbol();
	PASMER_SYMBOL_NODE pSymbolNode = QuerySymbolFromTable(pSymbolName);
	if (pSymbolNode == NULL) return FALSE;//找不到符号

	PASMER_OPERAND pCurrOpt = &(pAsmObj->Operand[bOptIndex]);
	pCurrOpt->OffsetBit = ASMER_32_BITS;
	pCurrOpt->CompilingInternal.pSymbolNode = pSymbolNode;//设置标号引用节点
	pAsmObj->CompilingInternal.bRefAddrLabel = TRUE;
	return TRUE;
}
/*
 * [addr_label]
 */
INLINE BOOL CHARM_INTERNAL_FUNC AnalyzeMemOperandStartByAddrLabel(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	if (ReferenceAddrLabel(pAsmObj, bOptIndex) == FALSE) return FALSE;
	// 下一个标记一定是结束符
	ASM_TOKEN Token = NextToken();
	if (__IsMemEndTokenInAsmer__(Token) == FALSE) return FALSE;
	return TRUE;
}

INLINE BOOL CHARM_INTERNAL_FUNC AnalyzeMemOperand(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();
	if ((__Is32BitRegisterTokenInAsmer__(Token) == TRUE) || (__IsScaleTokenInAsmer__(Token) == TRUE) || 
		(__IsDisplacementTokenInAsmer__(Token) == TRUE) || (__IsAddrLabelTokenInAsmer__(Token) == TRUE))
	{
		// 第一个标记为刻度
		if (__IsScaleTokenInAsmer__(Token) == TRUE)
		{
			__SetScaleTokenInAsmer__(pAsmObj->Operand[bOptIndex], Token);//设置刻度
			return AnalyzeMemOperandStartByRegister(pAsmObj, bOptIndex);
		}
		// 第一个标记为寄存器
		else if (__Is32BitRegisterTokenInAsmer__(Token) == TRUE)
		{
			BackToken();
			return AnalyzeMemOperandStartByRegister(pAsmObj, bOptIndex);
		}
		// 第一个标记为偏移
		else if (__IsDisplacementTokenInAsmer__(Token) == TRUE)
		{
			BackToken();
			return AnalyzeMemOperandStartByDisplacement(pAsmObj, bOptIndex);
		}
		// 第一个标记是一个标号
		else if (__IsAddrLabelTokenInAsmer__(Token) == TRUE)
		{
			BackToken();
			return AnalyzeMemOperandStartByAddrLabel(pAsmObj, bOptIndex);
		}
		else
		{
			return FALSE;
		}
	}

	return FALSE;
}

BOOL CHARM_INTERNAL_FUNC CompilingOperand(PASM_OBJ pAsmObj, BYTE bOptIndex)
{
	ASM_TOKEN Token = NextToken();//读取一个标记
	(pAsmObj->bOperandCount)++;//增加操作数

	// 匹配Operand内容
	if (bOptIndex == 0)
	{
		// mem为目的操作数
		// reg
		if (__IsRegisterTokenInAsmer__(Token) == TRUE)
		{
			__SetBitOnRegisterToOpt__(pAsmObj->Operand[0], Token);
			pAsmObj->Operand[0].Type = ASMER_OP_REG;
			__RegTokenToReg__(pAsmObj->Operand[0].Base, Token);
			return TRUE;
		}
		// mem
		else if (__IsTypePtrTokenInAsmer__(Token) == TRUE)
		{
			__SetBitOnTypePtrToOpt__(pAsmObj->Operand[0], Token);//根据当前的Token设置当前的位数
			pAsmObj->Operand[0].Type = ASMER_OP_MEM;
			if (AnalyzeMemOperand(pAsmObj, bOptIndex) == FALSE)
				return FALSE;
			return TRUE;
		}
		// immediate
		else if (__IsImmediateTokenInAsmer__(Token) == TRUE)
		{
			pAsmObj->Operand[0].Type = ASMER_OP_IMM;
			__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
			__SetImmediateToOpt__(pAsmObj->Operand[0], Token);
			return TRUE;
		}
		// addr label
		else if (__IsAddrLabelTokenInAsmer__(Token) == TRUE)
		{
			BackToken();
			pAsmObj->Operand[0].Type = ASMER_OP_IMM;
			pAsmObj->Operand[0].Bit = ASMER_32_BITS;
			return ReferenceAddrLabel(pAsmObj, 0);
		}
		else
		{
			return FALSE;
		}
	}
	else if (bOptIndex == 1)
	{
		// mem为源操作数
		// reg
		if (__IsRegisterTokenInAsmer__(Token) == TRUE)
		{
			__SetBitOnRegisterToOpt__(pAsmObj->Operand[1], Token);
			pAsmObj->Operand[1].Type = ASMER_OP_REG;
			__RegTokenToReg__(pAsmObj->Operand[1].Base, Token);
			return TRUE;
		}
		// mem
		else if (__IsTypePtrTokenInAsmer__(Token) == TRUE)
		{
			__SetBitOnTypePtrToOpt__(pAsmObj->Operand[1], Token);//根据当前的Token设置当前的位数
			pAsmObj->Operand[1].Type = ASMER_OP_MEM;
			if (AnalyzeMemOperand(pAsmObj, bOptIndex) == FALSE)
				return FALSE;
			return TRUE;
		}
		// immediate
		else if (__IsImmediateTokenInAsmer__(Token) == TRUE)
		{
			pAsmObj->Operand[1].Type = ASMER_OP_IMM;
			__SetBitOnImmediateToOpt__(pAsmObj->Operand[1], Token);
			__SetImmediateToOpt__(pAsmObj->Operand[1], Token);
			return TRUE;
		}
		// addr label
		else if (__IsAddrLabelTokenInAsmer__(Token) == TRUE)
		{
			BackToken();
			pAsmObj->Operand[1].Type = ASMER_OP_IMM;
			pAsmObj->Operand[1].Bit = ASMER_32_BITS;
			return ReferenceAddrLabel(pAsmObj, 1);
		}
		else
		{
			return FALSE;
		}
	}
	else if (bOptIndex == 2)
	{
		// 目前只在IMul指令中使用
		// immediate
		if (__IsImmediateTokenInAsmer__(Token) == TRUE)
		{
			pAsmObj->Operand[2].Type = ASMER_OP_IMM;
			__SetBitOnImmediateToOpt__(pAsmObj->Operand[2], Token);
			__SetImmediateToOpt__(pAsmObj->Operand[2], Token);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

#define __CreateAsmObj__(InstOpt)\
	PASM_OBJ pAsmObj = __new__(ASM_OBJ, 1);\
	memset(pAsmObj, 0, sizeof(ASM_OBJ));\
	pAsmObj->Inst = (InstOpt);

#define __DestoryAsmObj__()\
	__delete__(pAsmObj);\
	pAsmObj = NULL;

#define __ErrorDestoryAsmObj__()\
	__DestoryAsmObj__();\
	g_bCompilingError = TRUE;

#define __Opt0IsImmHandler__()\
	if (pAsmObj->Operand[0].Type == ASMER_OP_IMM){\
		__ErrorDestoryAsmObj__();\
		return NULL;\
	}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingNop()
{
	__CreateAsmObj__(ASMER_NOP);
	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingAdd()
{
	__CreateAsmObj__(ASMER_ADD);
	
	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingSub()
{
	__CreateAsmObj__(ASMER_SUB);
	
	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingMul()
{
	__CreateAsmObj__(ASMER_MUL);
	
	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

/*
 * 这里处理语法不严谨,但在机器严格生成下并无大碍
 */
INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingIMul()
{
	__CreateAsmObj__(ASMER_IMUL);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 检测是否到达末尾
	if (MatchToken(ASMER_TK_KW_LINEND) == TRUE)
	{
		return pAsmObj;
	}

	BackToken();//回退一个标记
	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检测是否到达末尾
	if (MatchToken(ASMER_TK_KW_LINEND) == TRUE)
	{
		return pAsmObj;
	}

	BackToken();//回退一个标记
	// 第三个操作数
	if (CompilingOperand(pAsmObj, 2) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingDiv()
{
	__CreateAsmObj__(ASMER_DIV);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingIDiv()
{
	__CreateAsmObj__(ASMER_IDIV);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingNot()
{
	__CreateAsmObj__(ASMER_NOT);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingAnd()
{
	__CreateAsmObj__(ASMER_AND);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingOr()
{
	__CreateAsmObj__(ASMER_OR);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingXor()
{
	__CreateAsmObj__(ASMER_XOR);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingShl()
{

	__CreateAsmObj__(ASMER_SHL);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	/*
	 * 第二个操作数
	 * 是自己的特殊形式,不使用通用处理
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token == ASMER_TK_REG_CL)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_REG;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		__RegTokenToReg__(pAsmObj->Operand[1].Base, Token);
	}
	else if (Token == ASMER_TK_KW_IMMEDIATE8)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_IMM;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		pAsmObj->Operand[1].OffsetBit = ASMER_8_BITS;
		pAsmObj->Operand[1].Val.uByte = (BYTE)NextToken();
	}
	else
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingShr()
{
	__CreateAsmObj__(ASMER_SHR);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	/*
	 * 第二个操作数
	 * 是自己的特殊形式,不使用通用处理
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token == ASMER_TK_REG_CL)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_REG;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		__RegTokenToReg__(pAsmObj->Operand[1].Base, Token);
	}
	else if (Token == ASMER_TK_KW_IMMEDIATE8)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_IMM;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		pAsmObj->Operand[1].OffsetBit = ASMER_8_BITS;
		pAsmObj->Operand[1].Val.uByte = (BYTE)NextToken();
	}
	else
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingRol()
{
	__CreateAsmObj__(ASMER_ROL);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	/*
	 * 第二个操作数
	 * 是自己的特殊形式,不使用通用处理
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token == ASMER_TK_REG_CL)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_REG;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		__RegTokenToReg__(pAsmObj->Operand[1].Base, Token);
	}
	else if (Token == ASMER_TK_KW_IMMEDIATE8)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_IMM;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		pAsmObj->Operand[1].OffsetBit = ASMER_8_BITS;
		pAsmObj->Operand[1].Val.uByte = (BYTE)NextToken();
	}
	else
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingRor()
{
	__CreateAsmObj__(ASMER_ROR);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	/*
	 * 第二个操作数
	 * 是自己的特殊形式,不使用通用处理
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token == ASMER_TK_REG_CL)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_REG;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		__RegTokenToReg__(pAsmObj->Operand[1].Base, Token);
	}
	else if (Token == ASMER_TK_KW_IMMEDIATE8)
	{
		pAsmObj->Operand[1].Type = ASMER_OP_IMM;
		pAsmObj->Operand[1].Bit = ASMER_8_BITS;
		pAsmObj->Operand[1].OffsetBit = ASMER_8_BITS;
		pAsmObj->Operand[1].Val.uByte = (BYTE)NextToken();
	}
	else
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingMov()
{
	__CreateAsmObj__(ASMER_MOV);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingLea()
{
	__CreateAsmObj__(ASMER_LEA);

	/*
	 * 第一个操作数
	 * 必须是寄存器
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__Is32BitRegisterTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_REG;
	__RegTokenToReg__(pAsmObj->Operand[0].Base, Token);
	pAsmObj->Operand[0].Bit = ASMER_32_BITS;

	/*
	 * 第二个操作数
	 * 必须是内存
	 */
	Token = NextToken();
	if (Token != ASMER_OP_MEM)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	BackToken();
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingStosb()
{
	__CreateAsmObj__(ASMER_STOSB);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingStosw()
{
	__CreateAsmObj__(ASMER_STOSW);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingStosd()
{
	__CreateAsmObj__(ASMER_STOSD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingLodsb()
{
	__CreateAsmObj__(ASMER_LODSB);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingLodsw()
{
	__CreateAsmObj__(ASMER_LODSW);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingLodsd()
{
	__CreateAsmObj__(ASMER_LODSD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingMovsb()
{
	__CreateAsmObj__(ASMER_MOVSB);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingMovsw()
{
	__CreateAsmObj__(ASMER_MOVSW);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingMovsd()
{
	__CreateAsmObj__(ASMER_MOVSD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingCld()
{
	__CreateAsmObj__(ASMER_CLD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingStd()
{
	__CreateAsmObj__(ASMER_STD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPush()
{
	__CreateAsmObj__(ASMER_PUSH);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPop()
{
	__CreateAsmObj__(ASMER_POP);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPushad()
{
	__CreateAsmObj__(ASMER_PUSHAD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPopad()
{
	__CreateAsmObj__(ASMER_POPAD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPushfd()
{
	__CreateAsmObj__(ASMER_PUSHFD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingPopfd()
{
	__CreateAsmObj__(ASMER_POPFD);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingRet()
{
	__CreateAsmObj__(ASMER_RET);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingRetn()
{
	__CreateAsmObj__(ASMER_RETN);

	// 第一个操作数
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token != ASMER_TK_KW_IMMEDIATE16)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	pAsmObj->Operand[0].Bit = ASMER_16_BITS;
	pAsmObj->Operand[0].OffsetBit = ASMER_16_BITS;
	pAsmObj->Operand[0].Val.uWord = (WORD)NextConst();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJmp()
{
	__CreateAsmObj__(ASMER_JMP);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingCall()
{
	__CreateAsmObj__(ASMER_JMP);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingLoop()
{
	__CreateAsmObj__(ASMER_LOOP);

	/*
	 * 第一个操作数
	 * 只能为常数,并且只能是8位
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (Token != ASMER_TK_KW_IMMEDIATE8)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	pAsmObj->Operand[0].Bit = ASMER_8_BITS;
	pAsmObj->Operand[0].OffsetBit = ASMER_8_BITS;
	pAsmObj->Operand[0].Val.uByte = (BYTE)NextConst();

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJz()
{
	__CreateAsmObj__(ASMER_JZ);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJnz()
{
	__CreateAsmObj__(ASMER_JNZ);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJa()
{
	__CreateAsmObj__(ASMER_JA);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJb()
{
	__CreateAsmObj__(ASMER_JB);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJae()
{
	__CreateAsmObj__(ASMER_JAE);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingJbe()
{
	__CreateAsmObj__(ASMER_JBE);

	/*
	 * 第一个操作数
	 * 只能为常数
	 */
	ASM_TOKEN Token = NextToken();
	(pAsmObj->bOperandCount)++;
	if (__IsImmediateTokenInAsmer__(Token) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	pAsmObj->Operand[0].Type = ASMER_OP_IMM;
	__SetBitOnImmediateToOpt__(pAsmObj->Operand[0], Token);
	__SetImmediateToOpt__(pAsmObj->Operand[0], Token);

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingCmp()
{
	__CreateAsmObj__(ASMER_CMP);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingTest()
{
	__CreateAsmObj__(ASMER_TEST);

	// 第一个操作数
	if (CompilingOperand(pAsmObj, 0) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}
	// 检查第一个操作数
	__Opt0IsImmHandler__();

	// 第二个操作数
	if (CompilingOperand(pAsmObj, 1) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC CompilingAddrLabel(ASM_TOKEN Token)
{
	// 创建地址标号
	ASMER_SYMBOL_TYPE Type;
	ASMER_INST Inst;
	if (Token == ASMER_TK_KW_ADDR_LAB)
	{
		Inst = ASMER_PSEUDO_ADDR_LAB;
		Type = AST_ADDR_LAB;
	}
	else if (Token == ASMER_TK_KW_ADDR_VALUE_LAB)
	{
		Inst = ASMER_PSEUDO_ADDR_VALUE_LAB;
		Type = AST_ADDR_VALUE_LAB;
	}
	else
		return NULL;

	__CreateAsmObj__(Inst);
	CHAR *pSymbolName = NextSymbol();
	if (QuerySymbolFromTable(pSymbolName) != NULL)
	{
		// 标号重定义
		return NULL;
	}
	PASMER_SYMBOL_NODE pSymbolNode = AddSymbolToTable(pSymbolName, 0, Type);//增加符号
	pAsmObj->CompilingInternal.pSymbolNode = pSymbolNode;

	// 行结束符
	if (MatchToken(ASMER_TK_KW_LINEND) == FALSE)
	{
		__ErrorDestoryAsmObj__();
		return NULL;
	}

	// 继续汇编
	return pAsmObj;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC AnalyzeAsmOneInst()
{
	ASM_TOKEN Token = NextToken();
	PASM_OBJ pAsmObj = NULL;

	switch (Token)
	{
	case ASMER_TK_ERROR:
	case ASMER_TK_END:
		{
			return NULL;
		}break;
	case ASMER_TK_INST_NOP:
		{
			pAsmObj = CompilingNop();
		}break;
	case ASMER_TK_INST_ADD:
		{
			pAsmObj = CompilingAdd();
		}break;
	case ASMER_TK_INST_SUB:
		{
			pAsmObj = CompilingSub();
		}break;
	case ASMER_TK_INST_MUL:
		{
			pAsmObj = CompilingMul();
		}break;
	case ASMER_TK_INST_IMUL:
		{
			pAsmObj = CompilingIMul();
		}break;
	case ASMER_TK_INST_DIV:
		{
			pAsmObj = CompilingDiv();
		}break;
	case ASMER_TK_INST_IDIV:
		{
			pAsmObj = CompilingIDiv();
		}break;
	case ASMER_TK_INST_NOT:
		{
			pAsmObj = CompilingNot();
		}break;
	case ASMER_TK_INST_AND:
		{
			pAsmObj = CompilingAnd();
		}break;
	case ASMER_TK_INST_OR:
		{
			pAsmObj = CompilingOr();
		}break;
	case ASMER_TK_INST_XOR:
		{
			pAsmObj = CompilingXor();
		}break;
	case ASMER_TK_INST_SHL:
		{
			pAsmObj = CompilingShl();
		}break;
	case ASMER_TK_INST_SHR:
		{
			pAsmObj = CompilingShr();
		}break;
	case ASMER_TK_INST_ROL:
		{
			pAsmObj = CompilingRol();
		}break;
	case ASMER_TK_INST_ROR:
		{
			pAsmObj = CompilingRor();
		}break;
	case ASMER_TK_INST_MOV:
		{
			pAsmObj = CompilingMov();
		}break;
	case ASMER_TK_INST_LEA:
		{
			pAsmObj = CompilingLea();
		}break;
	case ASMER_TK_INST_STOSB:
		{
			pAsmObj = CompilingStosb();
		}break;
	case ASMER_TK_INST_STOSW:
		{
			pAsmObj = CompilingStosw();
		}break;
	case ASMER_TK_INST_STOSD:
		{
			pAsmObj = CompilingStosd();
		}break;
	case ASMER_TK_INST_LODSB:
		{
			pAsmObj = CompilingLodsb();
		}break;
	case ASMER_TK_INST_LODSW:
		{
			pAsmObj = CompilingLodsw();
		}break;
	case ASMER_TK_INST_LODSD:
		{
			pAsmObj = CompilingLodsd();
		}break;
	case ASMER_TK_INST_MOVSB:
		{
			pAsmObj = CompilingMovsb();
		}break;
	case ASMER_TK_INST_MOVSW:
		{
			pAsmObj = CompilingMovsw();
		}break;
	case ASMER_TK_INST_MOVSD:
		{
			pAsmObj = CompilingMovsd();
		}break;
	case ASMER_TK_INST_CLD:
		{
			pAsmObj = CompilingCld();
		}break;
	case ASMER_TK_INST_STD:
		{
			pAsmObj = CompilingStd();
		}break;
	case ASMER_TK_INST_PUSH:
		{
			pAsmObj = CompilingPush();
		}break;
	case ASMER_TK_INST_POP:
		{
			pAsmObj = CompilingPop();
		}break;
	case ASMER_TK_INST_PUSHAD:
		{
			pAsmObj = CompilingPushad();
		}break;
	case ASMER_TK_INST_POPAD:
		{
			pAsmObj = CompilingPopad();
		}break;
	case ASMER_TK_INST_PUSHFD:
		{
			pAsmObj = CompilingPushfd();
		}break;
	case ASMER_TK_INST_POPFD:
		{
			pAsmObj = CompilingPopfd();
		}break;
	case ASMER_TK_INST_RET:
		{
			pAsmObj = CompilingRet();
		}break;
	case ASMER_TK_INST_RETN:
		{
			pAsmObj = CompilingRetn();
		}break;
	case ASMER_TK_INST_JMP:
		{
			pAsmObj = CompilingJmp();
		}break;
	case ASMER_TK_INST_CALL:
		{
			pAsmObj = CompilingCall();
		}break;
	case ASMER_TK_INST_LOOP:
		{
			pAsmObj = CompilingLoop();
		}break;
	case ASMER_TK_INST_JZ:
		{
			pAsmObj = CompilingJz();
		}break;
	case ASMER_TK_INST_JNZ:
		{
			pAsmObj = CompilingJnz();
		}break;
	case ASMER_TK_INST_JA:
		{
			pAsmObj = CompilingJa();
		}break;
	case ASMER_TK_INST_JB:
		{
			pAsmObj = CompilingJb();
		}break;
	case ASMER_TK_INST_JAE:
		{
			pAsmObj = CompilingJae();
		}break;
	case ASMER_TK_INST_JBE:
		{
			pAsmObj = CompilingJbe();
		}break;
	case ASMER_TK_INST_CMP:
		{
			pAsmObj = CompilingCmp();
		}break;
	case ASMER_TK_INST_TEST:
		{
			pAsmObj = CompilingTest();
		}break;
	/* 伪指令的编译 */
	case ASMER_TK_KW_ADDR_LAB:
	case ASMER_TK_KW_ADDR_VALUE_LAB:
		{
			pAsmObj = CompilingAddrLabel(Token);
		}break;
	default:
		{
			g_bCompilingError = TRUE;
			return NULL;
		}
	}/* end switch */

	return pAsmObj;
}
