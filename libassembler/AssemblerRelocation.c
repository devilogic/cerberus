#include "AssemblerRelocation.h"

__INLINE__ __bool __INTERNAL_FUNC__ IsFlowInstruction(PASM_OBJ pAsmObj) {
	switch (pAsmObj->Inst) {
	case JA:
	case JAE:
	case JB:
	case JBE:
	case JC:
	case JCXZ:
	case JECXZ:
	case JRCXZ:
	case JE:
	case JG:
	case JGE:
	case JL:
	case JLE:
	case JNA:
	case JNAE:
	case JNB:
	case JNBE:
	case JNC:
	case JNE:
	case JNG:
	case JNGE:
	case JNL:
	case JNLE:
	case JNO:
	case JNP:
	case JNS:
	case JNZ:
	case JO:
	case JP:
	case JPE:
	case JPO:
	case JS:
	case JZ:
	case JMP:
	case CALL: {
		return TRUE;
	}break;
	}
	return FALSE;
}

__INLINE__ __offset __INTERNAL_FUNC__ CalcFlowOffset(__address addrSourceAddress, __address addrDestAddress, __byte bInstLength) {
	// 计算偏移
	__offset ofOffset = 0;
	if (addrDestAddress >= addrSourceAddress)
		ofOffset = addrDestAddress - addrSourceAddress - bInstLength;
	else
		ofOffset = ~(addrSourceAddress - addrDestAddress + bInstLength - 1);

	return ofOffset;
}

__INLINE__ __void __INTERNAL_FUNC__ RelocationFlow(__memory pBin, PASM_OBJ pAsmObj, __integer iLoadBase) {
	PASMER_OPERAND pCurrOpt = &(pAsmObj->Operand[0]);
	__char *pAddrLabelSymbolName = pAsmObj->pAddrLabelSymbolName;
	// 修复跳转指令偏移量
	switch (pAsmObj->Inst) {
	case JA:
	case JAE:
	case JB:
	case JBE:
	case JC:
	case JCXZ:
	case JECXZ:
	case JRCXZ:
	case JE:
	case JG:
	case JGE:
	case JL:
	case JLE:
	case JNA:
	case JNAE:
	case JNB:
	case JNBE:
	case JNC:
	case JNE:
	case JNG:
	case JNGE:
	case JNL:
	case JNLE:
	case JNO:
	case JNP:
	case JNS:
	case JNZ:
	case JO:
	case JP:
	case JPE:
	case JPO:
	case JS:
	case JZ: {
		// 这里也只能有这一种情况, pSymbolNode不为NULL说明需要标号转换
		if ((pCurrOpt->Type == OP_IMM) && (pCurrOpt->bAddrLabel)) {
			// 目前只有一种地址标号
			PASMER_SYMBOL_NODE pSymbolNode;
			pSymbolNode = QuerySymbolFromTable(pAddrLabelSymbolName);
			if (pSymbolNode->Type == AST_ADDR_LAB) {
				__offset ofOffset = pCurrOpt->ofRelocationFixOffset;
				__address addrSourceAddress = pAsmObj->ofOffset + iLoadBase;
				__address addrDestAddress = (pSymbolNode->ofOffset) + iLoadBase;

				if (pCurrOpt->ValBit == ASMER_16_BITS) {//16位情况 
					__word wFlowOffset = \
					(__word)CalcFlowOffset(addrSourceAddress, addrDestAddress, pAsmObj->bInstLength);
					*(__word *)(pBin + ofOffset) = wFlowOffset;
				} else if (pCurrOpt->ValBit == ASMER_32_BITS) {//32位情况
					__dword dwFlowOffset = \
					(__dword)CalcFlowOffset(addrSourceAddress, addrDestAddress, pAsmObj->bInstLength);
					*(__dword *)(pBin + ofOffset) = dwFlowOffset;
				}
			}/* end else if */
		}/* end if */
	} break;
	case JMP:
	case CALL: {
		if ((pCurrOpt->Type == OP_IMM) && (pCurrOpt->bAddrLabel)) {
			PASMER_SYMBOL_NODE pSymbolNode;
			pSymbolNode = QuerySymbolFromTable(pAddrLabelSymbolName);
			if (pSymbolNode->Type == AST_ADDR_LAB) {
				__offset ofOffset = pCurrOpt->ofRelocationFixOffset;
				__address addrSourceAddress = pAsmObj->ofOffset + iLoadBase;
				__address addrDestAddress = (pSymbolNode->ofOffset) + iLoadBase;

				if (pCurrOpt->ValBit == ASMER_16_BITS) {
					__word wFlowOffset = \
						(__word)CalcFlowOffset(addrSourceAddress, addrDestAddress, pAsmObj->bInstLength);
					*(__word *)(pBin + ofOffset) = wFlowOffset;
				} else if (pCurrOpt->ValBit == ASMER_32_BITS) {
					__dword dwFlowOffset = \
						(__dword)CalcFlowOffset(addrSourceAddress, addrDestAddress, pAsmObj->bInstLength);
					*(__dword *)(pBin + ofOffset) = dwFlowOffset;
				}
			}/* end if */ 
		} else if ((pCurrOpt->Type == OP_MEM) && (pCurrOpt->bAddrLabel)) {
			PASMER_SYMBOL_NODE pSymbolNode;
			pSymbolNode = QuerySymbolFromTable(pAddrLabelSymbolName);
			if (pSymbolNode->Type == AST_ADDR_LAB) {
				__offset ofOffset = pCurrOpt->ofRelocationFixOffset;
				if (pCurrOpt->ValBit == ASMER_16_BITS)
					*(__word *)(pBin + ofOffset) = \
						(__word)((pSymbolNode->ofOffset) + iLoadBase);
				else if (pCurrOpt->ValBit == ASMER_32_BITS)
					*(__dword *)(pBin + ofOffset) = \
					(__dword)((pSymbolNode->ofOffset) + iLoadBase);
			}
		} else {
			// 出错
		}/* end else */ 
	}break;
	}/* end switch */
}

/*
 * 建立地址标号偏移
 */
__void __INTERNAL_FUNC__ BuildAddrLabelInfo(PASM_OBJ pAsmObjList) {
	PASM_OBJ pCurr = pAsmObjList;
	__offset ofOffset = 0;
	while (pCurr) {
		if (pCurr->bAddrLabel)//设置地址标号偏移
			pCurr->pSymbolNode->ofOffset = ofOffset;
		ofOffset += pCurr->bInstLength;
		pCurr = pCurr->pNext;
	}
}

/*
 * 重新定位基地址, 以及跳转指令的偏移量
 */ 
__memory __INTERNAL_FUNC__ Relocation(__memory pBin, PASM_OBJ pAsmObjList, __integer iLoadBase) {
	PASM_OBJ pCurr = pAsmObjList;
	while (pCurr) {
		// 重定位标号, pSymbolNode不为空则表示使用地址标号
		__integer i;
		for (i = 0; i < pCurr->bOperandCount; i++) {
			if (pCurr->Operand[i].bAddrLabel) {
				// 如果是流程指令,则进入流程指令修复函数
				if (IsFlowInstruction(pCurr))
					RelocationFlow(pBin, pCurr, iLoadBase);
				else {
					PASMER_SYMBOL_NODE pSymbolNode;
					pSymbolNode = QuerySymbolFromTable(pCurr->pAddrLabelSymbolName);
					if (pSymbolNode->Type == AST_ADDR_LAB) {//目前就此一种类型
						__offset ofOffset = pCurr->Operand[i].ofRelocationFixOffset;
						if (pCurr->Operand[i].ValBit == ASMER_16_BITS)
							*(__word *)(pBin + ofOffset) = \
								(__word)((pSymbolNode->ofOffset) + iLoadBase);
						else if (pCurr->Operand[i].ValBit == ASMER_32_BITS)
							*(__dword *)(pBin + ofOffset) = \
								(__dword)((pSymbolNode->ofOffset) + iLoadBase);
					}/* end if */
				}/* end else */
			}/* end if */
		}/* end for */
		pCurr = pCurr->pNext;
	}/* end while */
	return pBin;
}
