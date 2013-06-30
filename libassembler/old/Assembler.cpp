// 公共变量
PASM_TOKEN g_pTokenList = NULL;
DWORD *g_pConstList = NULL;
DWORD g_dwConstIndex = 0;
DWORD g_dwTokenIndex = 0;
BOOL g_bCompilingError = FALSE;

ASM_TOKEN CHARM_INTERNAL_FUNC NextToken()
{
	if (g_pTokenList == NULL)
	{
		g_bCompilingError = TRUE;
		return ASMER_TK_ERROR;
	}
	else if (g_pTokenList[g_dwTokenIndex] == ASMER_TK_END)
	{
		g_pTokenList = NULL;
		g_pConstList = NULL;
		g_dwTokenIndex = 0;
		g_dwConstIndex = 0;
		g_bCompilingError = FALSE;
		return ASMER_TK_END;
	}

	return g_pTokenList[g_dwTokenIndex++];
}

DWORD CHARM_INTERNAL_FUNC NextConst()
{
	if (g_pConstList == NULL)
	{
		return 0;
	}
	return g_pConstList[g_dwConstIndex++];
}

VOID CHARM_INTERNAL_FUNC ResetConst(DWORD dwNewConst)
{
	if (g_pConstList == NULL)
	{
		return;
	}
	g_pConstList[g_dwConstIndex] = dwNewConst;
}

INLINE VOID CHARM_INTERNAL_FUNC BackConst()
{
	g_dwConstIndex--;
}

INLINE VOID CHARM_INTERNAL_FUNC BackToken()
{
	g_dwTokenIndex--;
}

INLINE DWORD CHARM_INTERNAL_FUNC GetNowConstIndex()
{
	return g_dwConstIndex;
}

INLINE DWORD CHARM_INTERNAL_FUNC GetNowTokenIndex()
{
	return g_dwTokenIndex;
}

BOOL CHARM_INTERNAL_FUNC MatchToken(ASM_TOKEN Token)
{
	if (NextToken() != Token)
	{
		g_bCompilingError = TRUE;
		return FALSE;
	}

	return TRUE;
}

/*
 * !注:文件位置不能改动
 */
#include "AssemblerSymbolTable.cpp"
#include "AssemblerCompiling.cpp"
#include "AssemblerLinking.cpp"

VOID CHARM_INTERNAL_FUNC ReleaseAsmObjList(PASM_OBJ *pAsmObjListPoint)
{
	PASM_OBJ pCurr = *pAsmObjListPoint, pTmp = NULL;
	while (pCurr != NULL)
	{
		pTmp = pCurr->pNext;
		__delete__(pCurr);
		pCurr = pTmp;
	}

	*pAsmObjListPoint = NULL;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC Compiling(PASM_SOURCE pAsmSource)
{
	g_pTokenList = pAsmSource->pAsmTokenList;
	g_pConstList = pAsmSource->pConstList;
	g_dwTokenIndex = g_dwConstIndex = g_dwSymbolIndex = 0;
	g_bCompilingError = FALSE;

	PASM_OBJ pAsmObjList = NULL, *pAsmObjPoint = &pAsmObjList;

	while (TRUE)
	{
		*pAsmObjPoint = AnalyzeAsmOneInst();

		// 检查是否出现错误
		if (g_bCompilingError == TRUE)
		{
			ReleaseAsmObjList(&pAsmObjList);
			return NULL;
		}
		else if (*pAsmObjPoint == NULL)
		{
			// 检查是否编译完毕一行指令
			break;
		}
		pAsmObjPoint = &((*pAsmObjPoint)->pNext);
	}

	return pAsmObjList;
}

INLINE PASM_OBJ CHARM_INTERNAL_FUNC SetAddrLabelInfo(PASM_OBJ pAsmObj)
{
	// 避免多次定义标号
	if ((pAsmObj->Inst == ASMER_PSEUDO_ADDR_LAB) || (pAsmObj->Inst == ASMER_PSEUDO_ADDR_VALUE_LAB))
	{
		while ((pAsmObj->Inst == ASMER_PSEUDO_ADDR_LAB) || (pAsmObj->Inst == ASMER_PSEUDO_ADDR_VALUE_LAB))
		{
			pAsmObj->dwOffset = g_dwLinkingCount;
			pAsmObj->CompilingInternal.pSymbolNode->dwOffset = g_dwLinkingCount;// 设置偏移
			pAsmObj = pAsmObj->pNext;//返回下一个节点
		}
		return pAsmObj;
	}

	// 不是地址标号则直接返回
	return pAsmObj;
}

INLINE BOOL CHARM_INTERNAL_FUNC IsFlowInstruction(PASM_OBJ pAsmObj)
{
	switch (pAsmObj->Inst)
	{
	case ASMER_JA:
	case ASMER_JB:
	case ASMER_JAE:
	case ASMER_JBE:
	case ASMER_JZ:
	case ASMER_JNZ:
	case ASMER_JMP:
	case ASMER_CALL:
		{
			return TRUE;
		}break;
	}
	return FALSE;
}

INLINE DWORD CHARM_INTERNAL_FUNC CalcFlowOffset(DWORD dwSourceAddress, DWORD dwDestAddress, BYTE bInstLength)
{
	// 计算偏移
	DWORD dwOffset = 0;
	if (dwDestAddress >= dwSourceAddress)
	{
		dwOffset = dwDestAddress - dwSourceAddress - bInstLength;
	}
	else
	{
		dwOffset = ~(dwSourceAddress - dwDestAddress + bInstLength - 1);
	}

	return dwOffset;
}

INLINE VOID CHARM_INTERNAL_FUNC RelocationFlow(LPBYTE pBin, PASM_OBJ pAsmObj, DWORD dwLoadBase)
{
	PASMER_OPERAND pCurrOpt = &(pAsmObj->Operand[0]);
	// 修复跳转指令偏移量
	switch (pAsmObj->Inst)
	{
	case ASMER_JA:
	case ASMER_JB:
	case ASMER_JAE:
	case ASMER_JBE:
	case ASMER_JZ:
	case ASMER_JNZ:
		{
			// 这里也只能有这一种情况
			if ((pCurrOpt->Type == ASMER_OP_IMM) && (pCurrOpt->CompilingInternal.pSymbolNode != NULL))
			{
				// 两种地址标号
				if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					DWORD dwSourceAddress = pAsmObj->dwOffset + dwLoadBase;
					DWORD dwDestAddress = (pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase;

					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						WORD wFlowOffset = (WORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(WORD *)(pBin + dwOffset) = wFlowOffset;
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						DWORD dwFlowOffset = (DWORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(DWORD *)(pBin + dwOffset) = dwFlowOffset;
					}
				}
				else if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_VALUE_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					DWORD *pAddress = (DWORD *)((pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);

					DWORD dwSourceAddress = pAsmObj->dwOffset + dwLoadBase;
					DWORD dwDestAddress = *(DWORD *)pAddress;

					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						WORD wFlowOffset = (WORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(WORD *)(pBin + dwOffset) = wFlowOffset;
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						DWORD dwFlowOffset = (DWORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(DWORD *)(pBin + dwOffset) = dwFlowOffset;
					}
				}
			}
		}break;
	case ASMER_JMP:
	case ASMER_CALL:
		{
			if ((pCurrOpt->Type == ASMER_OP_IMM) && (pCurrOpt->CompilingInternal.pSymbolNode != NULL))
			{
				// 两种地址标号
				if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					DWORD dwSourceAddress = pAsmObj->dwOffset + dwLoadBase;
					DWORD dwDestAddress = (pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase;

					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						WORD wFlowOffset = (WORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(WORD *)(pBin + dwOffset) = wFlowOffset;
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						DWORD dwFlowOffset = (DWORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(DWORD *)(pBin + dwOffset) = dwFlowOffset;
					}
				}
				else if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_VALUE_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					DWORD *pAddress = (DWORD *)((pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);

					DWORD dwSourceAddress = pAsmObj->dwOffset + dwLoadBase;
					DWORD dwDestAddress = *(DWORD *)pAddress;

					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						WORD wFlowOffset = (WORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(WORD *)(pBin + dwOffset) = wFlowOffset;
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						DWORD dwFlowOffset = (DWORD)CalcFlowOffset(dwSourceAddress, dwDestAddress, pAsmObj->bInstLength);
						*(DWORD *)(pBin + dwOffset) = dwFlowOffset;
					}
				}
			}
			else if ((pCurrOpt->Type == ASMER_OP_MEM) && (pCurrOpt->CompilingInternal.pSymbolNode != NULL))
			{
				// 两种地址标号
				if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						*(WORD *)(pBin + dwOffset) = (WORD)((pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						*(DWORD *)(pBin + dwOffset) = (DWORD)((pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
					}
				}
				else if (pCurrOpt->CompilingInternal.pSymbolNode->Type == AST_ADDR_VALUE_LAB)
				{
					DWORD dwOffset = pCurrOpt->CompilingInternal.dwRelocationPoint;
					DWORD *pAddress = (DWORD *)((pCurrOpt->CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
					if (pCurrOpt->OffsetBit == ASMER_16_BITS)
					{
						*(WORD *)(pBin + dwOffset) = *(WORD *)pAddress;
					}
					else if (pCurrOpt->OffsetBit == ASMER_32_BITS)
					{
						*(DWORD *)(pBin + dwOffset) = *(DWORD *)pAddress;
					}
				}
			}/* end else */
		}break;
	}
}

INLINE LPBYTE CHARM_INTERNAL_FUNC Relocation(LPBYTE pBin, PASM_OBJ pAsmObjList, DWORD dwLoadBase)
{
	PASM_OBJ pCurr = pAsmObjList;
	while (pCurr != NULL)
	{
		if (pCurr->CompilingInternal.bRefAddrLabel == TRUE)
		{
			// 重定位标号
			for (int i = 0; i < pCurr->bOperandCount; i++)
			{
				if (pCurr->Operand[i].CompilingInternal.pSymbolNode != NULL)
				{
					// 如果是流程指令,则进入流程指令修复函数
					if (IsFlowInstruction(pCurr) == TRUE)
					{
						RelocationFlow(pBin, pCurr, dwLoadBase);
					}
					else
					{
						// 两种地址标号
						if (pCurr->Operand[i].CompilingInternal.pSymbolNode->Type == AST_ADDR_LAB)
						{
							DWORD dwOffset = pCurr->Operand[i].CompilingInternal.dwRelocationPoint;
							if (pCurr->Operand[i].OffsetBit == ASMER_16_BITS)
							{
								*(WORD *)(pBin + dwOffset) = (WORD)((pCurr->Operand[i].CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
							}
							else if (pCurr->Operand[i].OffsetBit == ASMER_32_BITS)
							{
								*(DWORD *)(pBin + dwOffset) = (DWORD)((pCurr->Operand[i].CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
							}
						}
						else if (pCurr->Operand[i].CompilingInternal.pSymbolNode->Type == AST_ADDR_VALUE_LAB)
						{
							DWORD dwOffset = pCurr->Operand[i].CompilingInternal.dwRelocationPoint;
							DWORD *pAddress = (DWORD *)((pCurr->Operand[i].CompilingInternal.pSymbolNode->dwOffset) + dwLoadBase);
							if (pCurr->Operand[i].OffsetBit == ASMER_16_BITS)
							{
								*(WORD *)(pBin + dwOffset) = *(WORD *)pAddress;
							}
							else if (pCurr->Operand[i].OffsetBit == ASMER_32_BITS)
							{
								*(DWORD *)(pBin + dwOffset) = *(DWORD *)pAddress;
							}
						}
					}/* end else */
				}/* end if */
			}/* end for */
		}/* end if */
		pCurr = pCurr->pNext;
	}
	return pBin;
}

#define MAX_TMP_LINKING_BUFFER_SIZE					0x1000
INLINE LPBYTE CHARM_INTERNAL_FUNC Linking(DWORD *pdwOutSize, PASM_OBJ pAsmObjList, DWORD dwLoadBase)
{
	LPBYTE pNowBin = g_LinkingBuffer, pBin = NULL;
	DWORD dwBinSize = 0, dwInstLength = 0;
	BYTE pTmp[MAX_TMP_LINKING_BUFFER_SIZE];//4KB的临时缓冲
	DWORD dwCount = 0;
	PASM_OBJ pCurr = pAsmObjList;
	g_dwLinkingCount = 0;//计数清0
	while (pCurr != NULL)
	{
		// 如果节点是地址标号则记录其位置并略过
		pCurr = SetAddrLabelInfo(pCurr);//这里也许会做移动指针操作
		if (pCurr == NULL) break;
		pCurr->dwOffset = g_dwLinkingCount;//当前指令偏移
		dwInstLength = LinkingOneInst(pCurr);
		if (dwInstLength == 0)//链接一条指令失败
		{
			// 如果pBin不为空则释放空间
			if (pBin != NULL) __delete__(pBin);
			// 释放OBJ链
			ReleaseAsmObjList(&pAsmObjList);
			*pdwOutSize = 0;
			return NULL;
		}
		// 设置指令长度
		pCurr->bInstLength = (BYTE)dwInstLength;
		g_dwLinkingCount += dwInstLength;//计数

		if (dwCount + dwInstLength <= MAX_TMP_LINKING_BUFFER_SIZE)
		{
			memcpy(pTmp + dwCount, pNowBin, dwInstLength);
			dwCount += dwInstLength;
		}
		else
		{
			if (pBin == NULL)//第一次满4KB
			{
				dwBinSize = dwCount + dwInstLength;
				pBin = __new__(BYTE, dwBinSize);
				memcpy(pBin, pTmp, dwCount);
				memcpy(pBin + dwCount, pNowBin, dwInstLength);
			}
			else
			{
				DWORD dwExchangeBinSize = dwBinSize;
				dwBinSize = dwBinSize + dwCount + dwInstLength;
				LPBYTE pExchange = __new__(BYTE, dwBinSize);
				memcpy(pExchange, pBin, dwExchangeBinSize);
				memcpy(pExchange + dwExchangeBinSize, pTmp, dwCount);
				memcpy(pExchange + dwExchangeBinSize + dwCount, pNowBin, dwInstLength);
				__delete__(pBin);
				pBin = pExchange;
			}
			memset(pTmp, 0, MAX_TMP_LINKING_BUFFER_SIZE);
			dwCount = 0;
		}
		pCurr = pCurr->pNext;
	}

	// 做最后的检测缓冲区
	if (pBin == NULL)
	{
		dwBinSize = dwCount;
		pBin = __new__(BYTE, dwBinSize);
		memcpy(pBin, pTmp, dwBinSize);
	}
	else if (dwCount != 0)
	{
		DWORD dwExchangeBinSize = dwBinSize;
		dwBinSize = dwBinSize + dwCount;
		LPBYTE pExchange = __new__(BYTE, dwBinSize);
		memcpy(pExchange, pBin, dwExchangeBinSize);
		memcpy(pExchange + dwExchangeBinSize, pTmp, dwCount);
		__delete__(pBin);
		pBin = pExchange;
	}

	*pdwOutSize = dwBinSize;
	return Relocation(pBin, pAsmObjList, dwLoadBase);
}

#define __AssemblerRunFailed__()\
	DestoryAsmerSymbolTable();\
	*pdwOutSize = 0;
#define __AssemblerRunExit__				__AssemblerRunFailed__
LPBYTE CHARM_INTERNAL_FUNC Assembler(DWORD *pdwOutSize, PASM_SOURCE pAsmSource, DWORD dwLoadBase)
{
	DWORD dwOutSize = 0;
	
	// 初始化符号表
	InitAsmerSymbolTable(pAsmSource);
	PASM_OBJ pAsmObjList = Compiling(pAsmSource);//编译
	if (pAsmObjList == NULL)
	{
		// 编译出错
		__AssemblerRunFailed__();
		return NULL;
	}

	LPBYTE pBin = Linking(&dwOutSize, pAsmObjList, dwLoadBase);//链接
	if (pBin == NULL)
	{
		// 链接出错
		__AssemblerRunFailed__();
		return NULL;
	}

	__AssemblerRunExit__();
	*pdwOutSize = dwOutSize;
	return pBin;
}
