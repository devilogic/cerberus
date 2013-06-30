/*
 * 不处理16地址的情况
 */
BYTE g_LinkingBuffer[32];//链接临时缓冲区
DWORD g_dwLinkingCount = 0;//链接计数

#define PREFIX_66				0x66

typedef enum _OPT_FORM
{
	OF_NONE = 0,
	
	/* op imm */
	OF_I8,
	OF_I32,

	/* op mem */
	OF_M8,
	OF_M32,

	/* op reg */
	OF_R8,
	OF_R32,

	/* op reg, imm */
	OF_R8_I8,
	OF_R32_I32,
	OF_R32_I8,

	/* op reg, mem */
	OF_R8_M8,
	OF_R32_M32,

	/* op reg, reg */
	OF_R8_R8,
	OF_R32_R32,

	/* op mem, imm */
	OF_M8_I8,
	OF_M32_I32,
	OF_M32_I8,

	/* op mem, reg */
	OF_M8_R8,
	OF_M32_R32,

	/* 三个操作符,目前只有IMUL使用 */
	/* opt reg, mem, imm */
	OF_R8_M8_I8,
	OF_R32_M32_I8,
	OF_R32_M32_I32,

	/* opt reg, reg, imm */
	OF_R8_R8_I8,
	OF_R32_R32_I8,
	OF_R32_R32_I32
} OPT_FORM;

OPT_FORM CHARM_INTERNAL_FUNC GetOptForm(PASM_OBJ pAsmObj)
{
	PASMER_OPERAND pCurrOpt0 = &(pAsmObj->Operand[0]);
	PASMER_OPERAND pCurrOpt1 = &(pAsmObj->Operand[1]); 
	PASMER_OPERAND pCurrOpt2 = &(pAsmObj->Operand[2]);
	BYTE bOperandCount = pAsmObj->bOperandCount;

	if (bOperandCount == 1)
	{
		// op imm
		if (pCurrOpt0->Type == ASMER_OP_IMM)
		{
			if (pCurrOpt0->Bit == ASMER_8_BITS)
				return OF_I8;
			else
				return OF_I32;
		}
		// op mem
		else if (pCurrOpt0->Type == ASMER_OP_MEM)
		{
			if (pCurrOpt0->Bit == ASMER_8_BITS)
				return OF_M8;
			else
				return OF_M32;
		}
		// op reg
		else if (pCurrOpt0->Type == ASMER_OP_REG)
		{
			if (pCurrOpt0->Bit == ASMER_8_BITS)
				return OF_R8;
			else
				return OF_R32;
		}
	}/* end if */
	else if (bOperandCount == 2)
	{
		// op mem, xxx
		if (pCurrOpt0->Type == ASMER_OP_MEM)
		{
			// op mem, imm
			if (pCurrOpt1->Type == ASMER_OP_IMM)
			{
				if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS))
					return OF_M8_I8;
				else// op0 = 16|32bits
				{
					if (pCurrOpt1->Bit == ASMER_8_BITS)// op1 = 8bits
						return OF_M32_I8;
					else// op1 = 16|32bits
					{
						if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS)) ||
							((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS)))
							return OF_M32_I32;
						else
							return OF_NONE;
					}
				}/* end else */
			}/* end if */
			// op mem, reg
			else if (pCurrOpt1->Type == ASMER_OP_REG)
			{
				if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS))
					return OF_M8_R8;
				else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS)) ||
						((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS)))
					return OF_M32_R32;
				else
					return OF_NONE;
			}
			else
			{
				return OF_NONE;
			}
		}/* end if */
		// op reg, XXX
		else if (pCurrOpt0->Type == ASMER_OP_REG)
		{
			// op reg, imm
			if (pCurrOpt1->Type == ASMER_OP_IMM)
			{
				if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS))
						return OF_R8_I8;
				else // op0 = 16|32bits
				{
					if (pCurrOpt1->Bit == ASMER_8_BITS)// op1 = 8bits
						return OF_R32_I8;
					else// op1 = 16|32bits
					{
						if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS)) ||
							((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS)))
							return OF_R32_I32;
						else
							return OF_NONE;
					}
				}
			}/* end if */
			// op reg, mem
			else if (pCurrOpt1->Type == ASMER_OP_MEM)
			{
				if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS))
					return OF_R8_M8;
				else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS)) ||
					((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS)))
					return OF_R32_M32;
				else
					return OF_NONE;
			}
			// op reg, reg
			else if (pCurrOpt1->Type == ASMER_OP_REG)
			{
				if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS))
					return OF_R8_R8;
				else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS)) ||
					((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS)))
					return OF_R32_R32;
				else
					return OF_NONE;
			}
			else
			{
				return OF_NONE;
			}
		}/* end else if */
	}/* end else if */
	else if (bOperandCount == 3)
	{
		// op reg, mem, imm
		if ((pCurrOpt0->Type = ASMER_OP_REG) && (pCurrOpt1->Type == ASMER_OP_MEM) && (pCurrOpt2->Type == ASMER_OP_IMM))
		{
			if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS))
				return OF_R8_M8_I8;
			else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS)) ||
				((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS)))
				return OF_R32_M32_I8;
			else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS) && (pCurrOpt2->Bit == ASMER_16_BITS)) ||
					((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS) && (pCurrOpt2->Bit == ASMER_32_BITS)))
				return OF_R32_M32_I32;
			else
				return OF_NONE;
		}
		// op reg, reg, imm
		else if ((pCurrOpt0->Type = ASMER_OP_REG) && (pCurrOpt1->Type == ASMER_OP_REG) && (pCurrOpt2->Type == ASMER_OP_IMM))
		{
			if ((pCurrOpt0->Bit == ASMER_8_BITS) && (pCurrOpt1->Bit == ASMER_8_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS))
				return OF_R8_R8_I8;
			else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS)) ||
				((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS) && (pCurrOpt2->Bit == ASMER_8_BITS)))
				return OF_R32_R32_I8;
			else if (((pCurrOpt0->Bit == ASMER_16_BITS) && (pCurrOpt1->Bit == ASMER_16_BITS) && (pCurrOpt2->Bit == ASMER_16_BITS)) ||
				((pCurrOpt0->Bit == ASMER_32_BITS) && (pCurrOpt1->Bit == ASMER_32_BITS) && (pCurrOpt2->Bit == ASMER_32_BITS)))
				return OF_R32_R32_I32;
			else
				return OF_NONE;
		}
	}
	
	return OF_NONE;
}

VOID CHARM_INTERNAL_FUNC InputByteToLinkBuffer(BYTE Byte, DWORD dwPoint)
{
	g_LinkingBuffer[dwPoint] = Byte;
}

VOID CHARM_INTERNAL_FUNC InputBytesToLinkBuffer(LPBYTE pBytes, DWORD dwSize, DWORD dwPoint)
{
	memcpy(&g_LinkingBuffer[dwPoint], pBytes, dwSize);
}

#define __ModrmToByte__()		(*(BYTE *)&(pAsmObj->CompilingInternal.ModRM))
#define __SibToByte__()			(*(BYTE *)&(pAsmObj->CompilingInternal.SIB))

#include "AssemblerFillModrmSib.cpp"
DWORD CHARM_INTERNAL_FUNC GenerateModrmSib(PASM_OBJ pAsmObj, DWORD dwPoint, BYTE bOpEx)
{
	DWORD dwCount = FillModRMSIB(pAsmObj, bOpEx);
	DWORD dwCurrPoint = dwPoint;
	if (dwCount == 1)
	{
		InputByteToLinkBuffer(__ModrmToByte__(), dwCurrPoint);dwCurrPoint++;
	}
	else
	{
		InputByteToLinkBuffer(__ModrmToByte__(), dwCurrPoint);dwCurrPoint++;
		InputByteToLinkBuffer(__SibToByte__(), dwCurrPoint);dwCurrPoint++;
	}

	// 遍历并设置偏移
	for (int i = 0; i < pAsmObj->bOperandCount; i++)
	{
		if ((pAsmObj->Operand[i].Type == ASMER_OP_MEM) && (pAsmObj->Operand[i].OffsetBit != ASMER_0_BITS))
		{
			if (pAsmObj->Operand[i].OffsetBit == ASMER_8_BITS)
			{
				BYTE bDisp8 = pAsmObj->Operand[i].Val.uByte;
				InputByteToLinkBuffer(bDisp8, dwCurrPoint);dwCurrPoint++;
				dwCount++;
			}
			else if (pAsmObj->Operand[i].OffsetBit == ASMER_32_BITS)
			{
				DWORD dwDisp32 = 0;
				// 地址标号拥有为32位
				if (pAsmObj->Operand[i].CompilingInternal.pSymbolNode != NULL)//设置要重定位的位置,当前的链接缓冲位置 + 当前缓冲编译的字节数
					pAsmObj->Operand[i].CompilingInternal.dwRelocationPoint = g_dwLinkingCount + dwCurrPoint;
				else
					dwDisp32 = pAsmObj->Operand[i].Val.uDword;
				InputBytesToLinkBuffer((LPBYTE)&dwDisp32, 4, dwCurrPoint);dwCurrPoint += 4;
				dwCount += 4;
			}
			// 每条指令只可能出现一次偏移量
			break;
		}
	}

	return dwCount;
}

#define __AsmOptIs8Bit__(bOpInd)				(pAsmObj->Operand[(bOpInd)].Bit == ASMER_8_BITS)
#define __AsmOptIs16Bit__(bOpInd)				(pAsmObj->Operand[(bOpInd)].Bit == ASMER_16_BITS)
#define __AsmOptIs32Bit__(bOpInd)				(pAsmObj->Operand[(bOpInd)].Bit == ASMER_32_BITS)

BOOL CHARM_INTERNAL_FUNC SetImmediateIsAddrLabel(PASM_OBJ pAsmObj, BYTE bOpIdx, DWORD dwCount, ASMER_BIT Bit)
{
	if ((pAsmObj->Operand[bOpIdx].CompilingInternal.pSymbolNode != NULL) &&
		((pAsmObj->Operand[bOpIdx].CompilingInternal.pSymbolNode->Type == AST_ADDR_LAB) ||
		(pAsmObj->Operand[bOpIdx].CompilingInternal.pSymbolNode->Type == AST_ADDR_VALUE_LAB)))
	{
		pAsmObj->Operand[bOpIdx].OffsetBit = Bit;
		pAsmObj->Operand[bOpIdx].CompilingInternal.dwRelocationPoint = g_dwLinkingCount + dwCount;
		return TRUE;
	}

	return FALSE;
}

#define __NormalSetImmediateIsAddrLabel__(pAsmObj, bOpIdx, dwCount, Bit)\
	if (SetImmediateIsAddrLabel((pAsmObj), (bOpIdx), (dwCount), (Bit)) == TRUE){\
		if ((Bit) == ASMER_16_BITS){\
			WORD wImm16 = 0;\
			InputBytesToLinkBuffer((LPBYTE)&wImm16, 2, (dwCount));\
			(dwCount) += 2;\
		} else if ((Bit) == ASMER_32_BITS){\
			DWORD dwImm32 = 0;\
			InputBytesToLinkBuffer((LPBYTE)&dwImm32, 4, (dwCount));\
			(dwCount) += 4;\
		}\
	} else {\
		if ((Bit) == ASMER_16_BITS){\
			WORD wImm16 = (pAsmObj)->Operand[(bOpIdx)].Val.uWord;\
			InputBytesToLinkBuffer((LPBYTE)&wImm16, 2, (dwCount));\
			(dwCount) += 2;\
		} else if ((Bit) == ASMER_32_BITS){\
			DWORD dwImm32 = (pAsmObj)->Operand[bOpIdx].Val.uDword;\
			InputBytesToLinkBuffer((LPBYTE)&dwImm32, 4, (dwCount));\
			(dwCount) += 4;\
		}\
	}

/*
 * ADD通用的模板
 * 适用于常见的2操作数指令
 * 只要与ADD指令有相同模板的都适用
 * 适用以下的形式:
 *
 * op ib                          OPT AL, imm8
 * op iw|d                        OPT AX|EAX, imm16|32
 * op /dig ib                     OPT r/m8, imm8
 * op /dig iw|d                   OPT r/m16|32, imm16|32
 * op /dig iw|d                   OPT r/m16|32, imm8
 * op /r                          OPT r/m8, r8
 * op /r                          OPT r/m16|32, r16|32
 * op /r                          OPT r8, r/m8
 * op /r                          OPT r16|32, r/m16|32
 *
 * 所用到的指令有
 * ADD, SUB, AND, OR, XOR, CMP
 */
DWORD CHARM_INTERNAL_FUNC LinkingAddTemplate(PASM_OBJ pAsmObj,
											 /* OPT AL, imm8*/
											 BYTE bOpAlImm8,
											 /* OPT AX|EAX, imm16|32 */
											 BYTE bOpEaxImm32,
											 /* OPT r/m8, imm8 */
											 BYTE bOpRm8Imm8,
											 BYTE bOpRm8Imm8Ex,
											 /* OPT r/m16|32, imm16|32 */
											 BYTE bOpRm32Imm32,
											 BYTE bOpRm32Imm32Ex,
											 /* OPT r/m16|32, imm8 */
											 BYTE bOpRm32Imm8,
											 BYTE bOpRm32Imm8Ex,
											 /* OPT r/m8, r8 */
											 BYTE bOpRm8R8,
											 /* OPT r/m32, r32 */
											 BYTE bOpRm32R32,
											 /* OPT r8, rm8 */
											 BYTE bOpR8Rm8,
											 /* OPT r32, rm32 */
											 BYTE bOpR32Rm32)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	// 判断形势
	switch (OptForm)
	{
	case OF_R8_I8:
	case OF_M8_I8:
		{
			// op AL, imm8
			if (pAsmObj->Operand[0].Base == ASMER_REG_AL)
			{
				InputByteToLinkBuffer(bOpAlImm8, dwCount);dwCount++;
			}
			else
			{
				InputByteToLinkBuffer(bOpRm8Imm8, dwCount);dwCount++;
				dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpRm8Imm8Ex);
			}
			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R32_I32:
	case OF_M32_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
				// op AX, imm16
				if (pAsmObj->Operand[0].Base == ASMER_REG_AX)
				{
					InputByteToLinkBuffer(bOpEaxImm32, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(bOpRm32Imm32, dwCount);dwCount++;
					dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpRm32Imm32Ex);
				}
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_16_BITS);
			}
			else// if (__AsmOptIs32Bit__(0) == TRUE)
			{
				// op EAX, imm32
				if (pAsmObj->Operand[0].Base == ASMER_REG_EAX)
				{
					InputByteToLinkBuffer(bOpEaxImm32, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(bOpRm32Imm32, dwCount);dwCount++;
					dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpRm32Imm32Ex);
				}
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_32_BITS);
			}
		}break;
	case OF_R32_I8:
	case OF_M32_I8:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(bOpRm32Imm8, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpRm32Imm8Ex);

			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R8_R8:
	case OF_M8_R8:
		{
			InputByteToLinkBuffer(bOpRm8R8, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R8_M8:
		{
			InputByteToLinkBuffer(bOpR8Rm8, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R32_R32:
	case OF_M32_R32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(bOpRm32R32, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R32_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(bOpR32Rm32, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	default: return 0; 
	}/* end switch */
	return dwCount;
}

/*
 * MUL通用的模板
 * 只要与MUL指令有相同模板的都适用
 * 适用以下的形式:
 *
 * F6 /dig                       OPT r/m8
 * F7 /dig                       OPT r/m16|32
 *
 * 所用到的指令有
 * DIV, IDIV, NOT
 */
DWORD CHARM_INTERNAL_FUNC LinkingMulTemplate(PASM_OBJ pAsmObj, BYTE bOpEx)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	// 判断形势
	switch (OptForm)
	{
	case OF_R8:
	case OF_M8:
		{
			InputByteToLinkBuffer(0xF6, dwCount);dwCount++;
		}break;
	case OF_R32:
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0xF7, dwCount);dwCount++;
		}break;
	default: return 0;
	}

	dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpEx);
	return dwCount;
}

/*
 * SHL通用的模板
 * 只要与SHL指令有相同模板的都适用
 * 适用以下的形式:
 * D0 /dig                        OPT r/m8, 1
 * D2 /dig                        OPT r/m8, Cl
 * C0 /dig ib                     OPT r/m8, imm8
 * D1 /dig                        OPT r/m16|32, 1
 * D3 /dig                        OPT r/m16|32, Cl
 * C1 /dig ib                     OPT r/m16|32, imm8
 *
 * 所用到的指令有
 * SHL, SHR, ROL, ROR
 */
DWORD CHARM_INTERNAL_FUNC LinkingShlTemplate(PASM_OBJ pAsmObj, BYTE bOpEx)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;

	// 判断形势
	switch (OptForm)
	{
	case OF_R8_I8:
	case OF_M8_I8:
	case OF_R32_I8:
	case OF_M32_I8:
		{
			if (__AsmOptIs8Bit__(0) == TRUE)
			{
				if (pAsmObj->Operand[1].Val.uByte == 1)
				{
					InputByteToLinkBuffer(0xD0, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(0xC0, dwCount);dwCount++;
				}
				dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpEx);
			}
			else
			{
				if (__AsmOptIs16Bit__(0) == TRUE)
				{
					InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
				}

				if (pAsmObj->Operand[1].Val.uByte == 1)
				{
					InputByteToLinkBuffer(0xD1, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(0xC1, dwCount);dwCount++;
				}
				dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpEx);
			}
			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R8_R8:
		{
			if (pAsmObj->Operand[1].Base != ASMER_REG_CL) return 0;
			InputByteToLinkBuffer(0xD2, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpEx);
		}break;
	// OF_R32_R8 <-标准型是没有的,SHL类型中的特例
	default:
		{
			// 筛选条件
			if ((pAsmObj->Operand[0].Type != ASMER_OP_REG) || (pAsmObj->Operand[1].Type != ASMER_OP_REG) ||
				(pAsmObj->Operand[1].Base != ASMER_REG_CL) || (pAsmObj->Operand[0].Bit == ASMER_8_BITS))
			{
				return 0;
			}

			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0xD3, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, bOpEx);
		}
	}

	return dwCount;
}

/*
 * Jcc通用的模板
 * 只要与Jcc指令有相同模板的都适用
 * 适用以下的形式:
 * op cb                          Jcc rel8
 * 0F op cw|d                     Jcc rel16|32
 *
 * 所用到的指令有
 * JZ, JNZ, JA, JB, JAE, JBE
 */
DWORD CHARM_INTERNAL_FUNC LinkingJccTemplate(PASM_OBJ pAsmObj, BYTE bOp)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;

	// 判断形势
	switch (OptForm)
	{
	case OF_I8:
		{
			InputByteToLinkBuffer(bOp, dwCount);dwCount++;
			BYTE bImm8 = pAsmObj->Operand[0].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0x0F, dwCount);dwCount++;
			InputByteToLinkBuffer(bOp, dwCount);dwCount++;
		
			// 这里在最后的重定位将重新修复
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_32_BITS);
			}
		}break;
	default: return 0;
	}

	return 0;
}

/*
 * 90
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingNop(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0x90, 0);
	return 1;
}

/*
 * 04 ib                          ADD AL, imm8
 * 05 ib                          ADD AX|EAX, imm16|32
 * 80 /0 ib                       ADD r/m8, imm8
 * 81 /0 iw|d                     ADD r/m16|32, imm16|32
 * 83 /0 ib                       ADD r/m16/32, imm8
 * 00 /r                          ADD r/m8, r8
 * 01 /r                          ADD r/m16|32, r16|32
 * 02 /r                          ADD r8, r/m8
 * 03 /r                          ADD r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingAdd(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x04, 0x05, 0x80, 0, 0x81, 0, 0x83, 0, 0x00, 0x01, 0x02, 0x03);
}

/*
 * 2C ib                          SUB AL, imm8
 * 2D iw|d                        SUB AX|EAX, imm16|32
 * 80 /5 ib                       SUB r/m8, imm8
 * 81 /5 iw|d                     SUB r/m16|32, imm16|32
 * 83 /5 ib                       SUB r/m16|32, imm8
 * 28 /r                          SUB r/m8, r8
 * 29 /r                          SUB r/m16|32, r16|32
 * 2A /r                          SUB r8, r/m8
 * 2B /r                          SUB r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingSub(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x2C, 0x2D, 0x80, 5, 0x81, 5, 0x83, 5, 0x28, 0x29, 0x2A, 0x2B);
}

/*
 * F6 /4                          MUL r/m8
 * F7 /4                          MUL r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingMul(PASM_OBJ pAsmObj)
{
	return LinkingMulTemplate(pAsmObj, 4);
}

/*
 * F6 /5                          IMUL r/m8
 * F7 /5                          IMUL r/m16|32
 * 0F AF /r                       IMUL r16|32, r/m16|32
 * 6B /r ib                       IMUL r16|32, r/m16|32, imm8
 * 6B /r ib                       IMUL r16|32, imm8
 * 69 /r iw|d                     IMUL r16|32, r/m16|32, imm16|32
 * 69 /r iw|d                     IMUL r16|32, imm16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingIMul(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_R8:
	case OF_M8:
		{
			InputByteToLinkBuffer(0xF6, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 5);
		}break;
	case OF_R32:
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0xF7, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 5);
		}break;
	case OF_R32_R32:
	case OF_R32_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0x0F, dwCount);dwCount++;
			InputByteToLinkBuffer(0xAF, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R32_I8:
	case OF_R32_R32_I8:
	case OF_R32_M32_I8:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0x69, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
			BYTE bImm8;
			if (pAsmObj->bOperandCount == 2)
				bImm8 = pAsmObj->Operand[1].Val.uByte;
			else if (pAsmObj->bOperandCount == 3)
				bImm8 = pAsmObj->Operand[2].Val.uByte;
			else
				return 0;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R32_I32:
	case OF_R32_R32_I32:
	case OF_R32_M32_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0x6B, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
			
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				WORD wImm16;
				if (pAsmObj->bOperandCount == 2)
				{
					__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_16_BITS);
				}
				else if (pAsmObj->bOperandCount == 3)
				{
					__NormalSetImmediateIsAddrLabel__(pAsmObj, 2, dwCount, ASMER_16_BITS);
				}
				else
					return 0;
			}
			else
			{
				DWORD dwImm32;
				if (pAsmObj->bOperandCount == 2)
				{
					__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_32_BITS);
				}
				else if (pAsmObj->bOperandCount == 3)
				{
					__NormalSetImmediateIsAddrLabel__(pAsmObj, 2, dwCount, ASMER_32_BITS);
				}
				else
					return 0;
			}
		}break;
	default: return 0;
	}

	return dwCount;
}

/*
 * F6 /6                          DIV r/m8
 * F7 /6                          DIV r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingDiv(PASM_OBJ pAsmObj)
{
	return LinkingMulTemplate(pAsmObj, 6);
}

/*
 * F6 /7                          IDIV r/m8
 * F7 /7                          IDIV r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingIDiv(PASM_OBJ pAsmObj)
{
	return LinkingMulTemplate(pAsmObj, 7);
}

/*
 * F6 /2                          NOT r/m8
 * F7 /2                          NOT r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingNot(PASM_OBJ pAsmObj)
{
	return LinkingMulTemplate(pAsmObj, 2);
}

/*
 * 24 ib                          AND AL, imm8
 * 25 iw|d                        AND AX|EAX, imm16|32
 * 80 /4 ib                       AND r/m8, imm8
 * 81 /4 iw|d                     AND r/m16|32, imm16|32
 * 83 /4 ib                       AND r/m16|32, imm8
 * 20 /r                          AND r/m8, r8
 * 21 /r                          AND r/m16|32, r16|32
 * 22 /r                          AND r8, r/m8
 * 23 /r                          AND r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingAnd(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x24, 0x25, 0x80, 4, 0x81, 4, 0x83, 4, 0x20, 0x21, 0x22, 0x23);
}

/*
 * 0C ib                          OR AL, imm8
 * 0D iw|d                        OR AX|EAX, imm16|32
 * 80 /1 ib                       OR r/m8, imm8
 * 81 /1 iw|d                     OR r/m16|32, imm16|32
 * 83 /1 ib                       OR r/m16|32, imm8
 * 08 /r                          OR r/m8, r8
 * 09 /r                          OR r/m16|32, r16|32
 * 0A /r                          OR r8, r/m8
 * 0B /r                          OR r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingOr(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x0C, 0x0D, 0x80, 1, 0x81, 1, 0x83, 1, 0x08, 0x09, 0x0A, 0x0B);
}

/*
 * 34 ib                          XOR AL, imm8
 * 35 iw|d                        XOR AX|EAX, imm16|32
 * 80 /6 ib                       XOR r/m8, imm8
 * 81 /6 iw|d                     XOR r/m16|32, imm16|32
 * 83 /6 ib                       XOR r/m16|32, imm8
 * 30 /r                          XOR r/m8, r8
 * 31 /r                          XOR r/m16|32, r16|32
 * 32 /r                          XOR r8, r/m8
 * 33 /r                          XOR r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingXor(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x34, 0x35, 0x80, 6, 0x81, 6, 0x83, 6, 0x30, 0x31, 0x32, 0x33);
}

/*
 * D0 /4                          SHL r/m8, 1
 * D2 /4                          SHL r/m8, Cl
 * C0 /4 ib                       SHL r/m8, imm8
 * D1 /4                          SHL r/m16|32, 1
 * D3 /4                          SHL r/m16|32, Cl
 * C1 /4 ib                       SHL r/m16|32, imm8
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingShl(PASM_OBJ pAsmObj)
{
	return LinkingShlTemplate(pAsmObj, 4);
}

/*
 * D0 /5                          SHR r/m8, 1
 * D2 /5                          SHR r/m8, Cl
 * C0 /5 ib                       SHR r/m8, imm8
 * D1 /5                          SHR r/m16|32, 1
 * D3 /5                          SHR r/m16|32, Cl
 * C1 /5 ib                       SHR r/m16|32, imm8
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingShr(PASM_OBJ pAsmObj)
{
	return LinkingShlTemplate(pAsmObj, 5);
}

/*
 * D0 /0                          ROL r/m8, 1
 * D2 /0                          ROL r/m8, Cl
 * C0 /0 ib                       ROL r/m8, imm8
 * D1 /0                          ROL r/m16|32, 1
 * D3 /0                          ROL r/m16|32, Cl
 * C1 /0 ib                       ROL r/m16|32, imm8
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingRol(PASM_OBJ pAsmObj)
{
	return LinkingShlTemplate(pAsmObj, 0);
}

/*
 * D0 /1                          ROR r/m8, 1
 * D2 /1                          ROR r/m8, Cl
 * C0 /1 ib                       ROR r/m8, imm8
 * D1 /1                          ROR r/m16|32, 1
 * D3 /1                          ROR r/m16|32, Cl
 * C1 /1 ib                       ROR r/m16|32, imm8
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingRor(PASM_OBJ pAsmObj)
{
	return LinkingShlTemplate(pAsmObj, 1);
}

/*
 * 88 /r                          MOV r/m8, r8
 * 89 /r                          MOV r/m16|32, r16|32
 * 8A /r                          MOV r8, r/m8
 * 8B /r                          MOV r16|32, r/m16|32
 * B0 + rb                        MOV r8, imm8
 * B8 + rw|d                      MOV r16|32, imm16|32
 * C6 /0                          MOV r/m8, imm8
 * C7 /0                          MOV r/m16|32, imm16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingMov(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_R8_R8:
	case OF_M8_R8:
		{
			InputByteToLinkBuffer(0x88, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R8_M8:
		{
			InputByteToLinkBuffer(0x8A, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R8_I8:
		{
			BYTE bOp = 0xB0;
			BYTE bIndex;
			 __GetRegisterIndex__(bIndex, pAsmObj->Operand[0].Base);
			InputByteToLinkBuffer(bOp + bIndex, dwCount);dwCount++;
			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_M8_I8:
		{
			InputByteToLinkBuffer(0xC6, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R32_R32:
	case OF_R32_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0x8B, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_M32_R32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0x89, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R32_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			BYTE bOp = 0xB8;
			BYTE bIndex;
			__GetRegisterIndex__(bIndex, pAsmObj->Operand[0].Base);
			InputByteToLinkBuffer(bOp + bIndex, dwCount);dwCount++;

			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_32_BITS);
			}
		}break;
	case OF_M32_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xC7, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_32_BITS);
			}
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * 8D /r                          LEA r16|32, m
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingLea(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_R32_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0x8D, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * AA                             STOSB
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingStosb(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xAA, 0);
	return 1;
}

/*
 * AB                             STOSW
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingStosw(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(PREFIX_66, 0);
	InputByteToLinkBuffer(0xAB, 1);
	return 2;
}

/*
 * AB                             STOSD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingStosd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xAB, 1);
	return 1;
}

/*
 * AC                             LODSB
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingLodsb(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xAC, 0);
	return 1;
}

/*
 * AD                             LODSW
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingLodsw(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(PREFIX_66, 0);
	InputByteToLinkBuffer(0xAD, 1);
	return 2;
}

/*
 * AD                             LODSD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingLodsd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xAD, 0);
	return 1;
}

/*
 * A4                             MOVSB
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingMovsb(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xA4, 0);
	return 1;
}

/*
 * A5                             MOVSW
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingMovsw(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(PREFIX_66, 0);
	InputByteToLinkBuffer(0xA5, 1);
	return 2;
}

/*
 * A5                             MOVSD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingMovsd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xA5, 0);
	return 1;
}

/*
 * FC                             CLD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingCld(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xFC, 0);
	return 1;
}

/*
 * FD                             STD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingStd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xFD, 0);
	return 1;
}

/*
 * FF /6                          PUSH r/m16|32
 * 50 + iw|d                      PUSH r16|32
 * 6A                             PUSH imm8
 * 68                             PUSH imm16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPush(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_R32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			BYTE bOp = 0x50, bIndex;
			__GetRegisterIndex__(bIndex, pAsmObj->Operand[0].Base);
			InputByteToLinkBuffer(bOp + bIndex, dwCount);dwCount++;
		}break;
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xFF, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 6);
		}break;
	case OF_I8:
		{
			InputByteToLinkBuffer(0x6A, dwCount);dwCount++;
			BYTE bImm8 = pAsmObj->Operand[0].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0x68, dwCount);dwCount++;

			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_32_BITS);
			}
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * 8F /0                          POP r/m16|32
 * 58 + iw|d                      POP r16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPop(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_R32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			BYTE bOp = 0x58, bIndex;
			__GetRegisterIndex__(bIndex, pAsmObj->Operand[0].Base);
			InputByteToLinkBuffer(bOp + bIndex, dwCount);dwCount++;
		}break;
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0x8F, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * 60                             PUSHAD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPushad(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0x60, 0);
	return 1;
}

/*
 * 61                             POPAD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPopad(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0x61, 0);
	return 1;
}

/*
 * 9C                             PUSHFD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPushfd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0x9C, 0);
	return 1;
}

/*
 * 9D                             POPFD
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingPopfd(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0x9D, 0);
	return 1;
}

/*
 * C3                             RET
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingRet(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xC3, 0);
	return 1;
}

/*
 * C2 iw                          RETN imm16
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingRetn(PASM_OBJ pAsmObj)
{
	DWORD dwCount = 0;
	InputByteToLinkBuffer(0xC2, 0);dwCount++;
	WORD wImm16 = pAsmObj->Operand[0].Val.uWord;
	InputBytesToLinkBuffer((LPBYTE)&wImm16, 2, dwCount);dwCount += 2;
	return dwCount;
}

/*
 * EB cb                          JMP rel8
 * E9 cw|d                        JMP rel16|32
 * FF /4                          JMP r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJmp(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_I8:
		{
			InputByteToLinkBuffer(0xEB, dwCount);dwCount++;
			BYTE bImm8 = pAsmObj->Operand[0].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xE9, dwCount);dwCount++;

			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_32_BITS);
			}
		}break;
	case OF_R32:
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xFF, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 4);
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * E8 cw|d                        CALL rel16|32
 * FF /2                          CALL r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingCall(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	switch (OptForm)
	{
	case OF_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xE8, dwCount);dwCount++;

			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_16_BITS);
			}
			else
			{
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 0, dwCount, ASMER_32_BITS);
			}
		}break;
	case OF_R32:
	case OF_M32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;
			}
			InputByteToLinkBuffer(0xFF, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, 2);
		}break;
	default: return 0;
	}
	return dwCount;
}

/*
 * E2 cb                          LOOP rel8
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingLoop(PASM_OBJ pAsmObj)
{
	InputByteToLinkBuffer(0xE2, 0);
	BYTE bImm8 = pAsmObj->Operand[0].Val.uByte;
	InputByteToLinkBuffer(bImm8, 1);
	return 2;
}

/*
 * 74 cb                          JZ rel8
 * 0F 74 cw|d                     JZ rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJz(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x74);
}

/*
 * 75 cb                          JNZ rel8
 * 0F 75 cw|d                     JNZ rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJnz(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x75);
}

/*
 * 87 cb                          JA rel8
 * 0F 87 cw|d                     JA rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJa(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x87);
}

/*
 * 82 cb                          JB rel8
 * 0F 82 cw|d                     JB rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJb(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x82);
}

/*
 * 83 cb                          JAE rel8
 * 0F 83 cw|d                     JAE rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJae(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x83);
}

/*
 * 86 cb                          JBE rel8
 * 0F 86 cw|d                     JBE rel16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingJbe(PASM_OBJ pAsmObj)
{
	return LinkingJccTemplate(pAsmObj, 0x86);
}

/*
 * 3C ib                          CMP AL, imm8
 * 3D iw|d                        CMP AX|EAX, imm16|32
 * 80 /7 ib                       CMP r/m8, imm8
 * 81 /7 iw|d                     CMP r/m16|32, imm16|32
 * 83 /7 ib                       CMP r/m16|32, imm8
 * 38 /r                          CMP r/m8, r8
 * 39 /r                          CMP r/m16|32, r16|32
 * 3A /r                          CMP r8, r/m8
 * 3B /r                          CMP r16|32, r/m16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingCmp(PASM_OBJ pAsmObj)
{
	return LinkingAddTemplate(pAsmObj, 0x3C, 0x3D, 0x80, 7, 0x81, 7, 0x83, 7, 0x38, 0x39, 0x3A, 0x3B);
}

/*
 * A8 ib                          TEST AL, imm8
 * A9 iw|d                        TEST AX|EAX, imm16|32
 * F6 /0 ib                       TEST r/m8, imm8
 * F7 /0 iw|d                     TEST r/m16|32, imm16|32
 * 84 /r                          TEST r/m8, r8
 * 85 /r                          TEST r/m16|32, r16|32
 */
INLINE DWORD CHARM_INTERNAL_FUNC LinkingTest(PASM_OBJ pAsmObj)
{
	OPT_FORM OptForm = GetOptForm(pAsmObj);
	DWORD dwCount = 0;
	// 判断形势
	switch (OptForm)
	{
	case OF_R8_I8:
	case OF_M8_I8:
		{
			// op AL, imm8
			if (pAsmObj->Operand[0].Base == ASMER_REG_AL)
			{
				InputByteToLinkBuffer(0xA8, dwCount);dwCount++;
			}
			else
			{
				InputByteToLinkBuffer(0xF6, dwCount);dwCount++;
				dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
			}
			BYTE bImm8 = pAsmObj->Operand[1].Val.uByte;
			InputByteToLinkBuffer(bImm8, dwCount);dwCount++;
		}break;
	case OF_R32_I32:
	case OF_M32_I32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
				// op AX, imm16
				if (pAsmObj->Operand[0].Base == ASMER_REG_AX)
				{
					InputByteToLinkBuffer(0xA9, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(0xF7, dwCount);dwCount++;
					dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
				}
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_16_BITS);
			}
			else// if (__AsmOptIs32Bit__(0) == TRUE)
			{
				// op EAX, imm32
				if (pAsmObj->Operand[0].Base == ASMER_REG_EAX)
				{
					InputByteToLinkBuffer(0xA9, dwCount);dwCount++;
				}
				else
				{
					InputByteToLinkBuffer(0xF7, dwCount);dwCount++;
					dwCount += GenerateModrmSib(pAsmObj, dwCount, 0);
				}
				__NormalSetImmediateIsAddrLabel__(pAsmObj, 1, dwCount, ASMER_32_BITS);
			}
		}break;
	case OF_R8_R8:
	case OF_M8_R8:
		{
			InputByteToLinkBuffer(0x84, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	case OF_R32_R32:
	case OF_M32_R32:
		{
			if (__AsmOptIs16Bit__(0) == TRUE)
			{
				InputByteToLinkBuffer(PREFIX_66, dwCount);dwCount++;//设置前缀
			}
			InputByteToLinkBuffer(0x85, dwCount);dwCount++;
			dwCount += GenerateModrmSib(pAsmObj, dwCount, OPEX_NONE);
		}break;
	default: return 0; 
	}/* end switch */
	return dwCount;
}

INLINE DWORD CHARM_INTERNAL_FUNC LinkingOneInst(PASM_OBJ pAsmObj)
{
	ASMER_INST Inst = pAsmObj->Inst;
	DWORD dwBinSize = 0;

	switch (Inst)
	{
	case ASMER_NOP:
		{
			dwBinSize = LinkingNop(pAsmObj);
		}break;
	case ASMER_ADD:
		{
			dwBinSize = LinkingAdd(pAsmObj);
		}break;
	case ASMER_SUB:
		{
			dwBinSize = LinkingSub(pAsmObj);
		}break;
	case ASMER_MUL:
		{
			dwBinSize = LinkingMul(pAsmObj);
		}break;
	case ASMER_IMUL:
		{
			dwBinSize = LinkingIMul(pAsmObj);
		}break;
	case ASMER_DIV:
		{
			dwBinSize = LinkingDiv(pAsmObj);
		}break;
	case ASMER_IDIV:
		{
			dwBinSize = LinkingIDiv(pAsmObj);
		}break;
	case ASMER_NOT:
		{
			dwBinSize = LinkingNot(pAsmObj);
		}break;
	case ASMER_AND:
		{
			dwBinSize = LinkingAnd(pAsmObj);
		}break;
	case ASMER_OR:
		{
			dwBinSize = LinkingOr(pAsmObj);
		}break;
	case ASMER_XOR:
		{
			dwBinSize = LinkingXor(pAsmObj);
		}break;
	case ASMER_SHL:
		{
			dwBinSize = LinkingShl(pAsmObj);
		}break;
	case ASMER_SHR:
		{
			dwBinSize = LinkingShr(pAsmObj);
		}break;
	case ASMER_ROL:
		{
			dwBinSize = LinkingRol(pAsmObj);
		}break;
	case ASMER_ROR:
		{
			dwBinSize = LinkingRor(pAsmObj);
		}break;
	case ASMER_MOV:
		{
			dwBinSize = LinkingMov(pAsmObj);
		}break;
	case ASMER_LEA:
		{
			dwBinSize = LinkingLea(pAsmObj);
		}break;
	case ASMER_STOSB:
		{
			dwBinSize = LinkingStosb(pAsmObj);
		}break;
	case ASMER_STOSW:
		{
			dwBinSize = LinkingStosw(pAsmObj);
		}break;
	case ASMER_STOSD:
		{
			dwBinSize = LinkingStosd(pAsmObj);
		}break;
	case ASMER_LODSB:
		{
			dwBinSize = LinkingLodsb(pAsmObj);
		}break;
	case ASMER_LODSW:
		{
			dwBinSize = LinkingLodsw(pAsmObj);
		}break;
	case ASMER_LODSD:
		{
			dwBinSize = LinkingLodsd(pAsmObj);
		}break;
	case ASMER_MOVSB:
		{
			dwBinSize = LinkingMovsb(pAsmObj);
		}break;
	case ASMER_MOVSW:
		{
			dwBinSize = LinkingMovsw(pAsmObj);
		}break;
	case ASMER_MOVSD:
		{
			dwBinSize = LinkingMovsd(pAsmObj);
		}break;
	case ASMER_CLD:
		{
			dwBinSize = LinkingCld(pAsmObj);
		}break;
	case ASMER_STD:
		{
			dwBinSize = LinkingStd(pAsmObj);
		}break;
	case ASMER_PUSH:
		{
			dwBinSize = LinkingPush(pAsmObj);
		}break;
	case ASMER_POP:
		{
			dwBinSize = LinkingPop(pAsmObj);
		}break;
	case ASMER_PUSHAD:
		{
			dwBinSize = LinkingPushad(pAsmObj);
		}break;
	case ASMER_POPAD:
		{
			dwBinSize = LinkingPopad(pAsmObj);
		}break;
	case ASMER_PUSHFD:
		{
			dwBinSize = LinkingPushfd(pAsmObj);
		}break;
	case ASMER_POPFD:
		{
			dwBinSize = LinkingPopfd(pAsmObj);
		}break;
	case ASMER_RET:
		{
			dwBinSize = LinkingRet(pAsmObj);
		}break;
	case ASMER_RETN:
		{
			dwBinSize = LinkingRetn(pAsmObj);
		}break;
	case ASMER_JMP:
		{
			dwBinSize = LinkingJmp(pAsmObj);
		}break;
	case ASMER_CALL:
		{
			dwBinSize = LinkingCall(pAsmObj);
		}break;
	case ASMER_LOOP:
		{
			dwBinSize = LinkingLoop(pAsmObj);
		}break;
	case ASMER_JZ:
		{
			dwBinSize = LinkingJz(pAsmObj);
		}break;
	case ASMER_JNZ:
		{
			dwBinSize = LinkingJnz(pAsmObj);
		}break;
	case ASMER_JA:
		{
			dwBinSize = LinkingJa(pAsmObj);
		}break;
	case ASMER_JB:
		{
			dwBinSize = LinkingJb(pAsmObj);
		}break;
	case ASMER_JAE:
		{
			dwBinSize = LinkingJae(pAsmObj);
		}break;
	case ASMER_JBE:
		{
			dwBinSize = LinkingJbe(pAsmObj);
		}break;
	case ASMER_CMP:
		{
			dwBinSize = LinkingCmp(pAsmObj);
		}break;
	case ASMER_TEST:
		{
			dwBinSize = LinkingTest(pAsmObj);
		}break;
	}/* end switch */
	return dwBinSize;
}
