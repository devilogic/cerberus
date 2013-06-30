__integer __INTERNAL_FUNC__ CountProcedureList(PPROCEDURE pProcedure) {
	__integer iCount = 0;
	PPROCEDURE pCurrProcCount = pProcedure;
	while (pCurrProcCount) {
		if (!(pCurrProcCount->bBlock))//忽略非代码块
			iCount++;
		pCurrProcCount = pCurrProcCount->pNext;
	}
	return iCount;
}

__integer __INTERNAL_FUNC__ CountAllBloackList(PPROCEDURE pProcedure) {
	__integer iCount = 0;
	PPROCEDURE pCurrProcCount = pProcedure;
	while (pCurrProcCount) {
		iCount++;
		pCurrProcCount = pCurrProcCount->pNext;
	}
	return iCount;
}

#define __JmpUpOffsetByAnalyzeJmpEnd__(Offset, InstLen) ((~(Offset) + 1) - (InstLen))
__INLINE__ __memory __INTERNAL_FUNC__ AnalyzeJmpEnd(__memory pMem, __address ImageBase, __address addrCurrMemoryAddress, ud_t *pud_obj) {
	__integer iRva = 0;
	__memory pJmpTo = NULL;

	// 如果是动态跳转则直接退出
	if (pud_obj->operand[0].type == UD_OP_MEM)
		return NULL;

	if (pud_obj->operand[0].offset == 8) {
		// 8位
		__byte bOffset = pud_obj->operand[0].lval.ubyte;
		if (__IsNegative8__(bOffset)) {
			iRva = addrCurrMemoryAddress - __JmpUpOffsetByAnalyzeJmpEnd__(bOffset, pud_obj->inp_ctr) - ImageBase;
			pJmpTo = pMem + AnalyzerRva2Raw(pMem, iRva);
		}
	} else if (pud_obj->operand[0].offset == 16) {
		// 16位
		__word wOffset = pud_obj->operand[0].lval.uword;
		if (__IsNegative16__(wOffset)) {
			iRva = addrCurrMemoryAddress - __JmpUpOffsetByAnalyzeJmpEnd__(wOffset, pud_obj->inp_ctr) - ImageBase;
			pJmpTo = pMem + AnalyzerRva2Raw(pMem, iRva);
		}
	} else if (pud_obj->operand[0].offset == 32) {
		// 32位
		__dword dwOffset = pud_obj->operand[0].lval.udword;
		if (__IsNegative32__(dwOffset) == TRUE)
		{
			iRva = addrCurrMemoryAddress - __JmpUpOffsetByAnalyzeJmpEnd__(dwOffset, pud_obj->inp_ctr) - ImageBase;
			pJmpTo = pMem + AnalyzerRva2Raw(pMem, iRva);
		}
	}
	return pJmpTo;
}

/*
 * 预处理结尾的函数的结尾有以下情况
 * 1:有一个JMP指令直接跳转到分析出的最后一个RET指令或之前
 * 2:再次寻找到ret语句
 * 3:函数末尾特征
 */
__INLINE__ __offset __INTERNAL_FUNC__ PredictProcEnd(__memory pMem, __address ImageBase, __memory pStart, \
													 __address addrStartMemoryAddress, __memory pRet, PANALYZE_CONFIGURE pAnalyzeConfigure) {
	__offset ofOffset = 0;
	__memory pCurr = pStart;
	__memory pJmpEnd = NULL;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, pStart, __MAX_PROCEDURE_LENGTH__);//默认一个函数的最大长度为4096
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	while (ud_disassemble(&ud_obj)) {
		pCurr += ofOffset;
		ofOffset += ud_obj.inp_ctr;
		if (ud_obj.mnemonic == UD_Ijmp) {
			/*
			 * 如果有一条指令是JMP且它跳转的目标地址是否与输入的ret指令相同或者小于
			 * 那么这个位置就是函数的结尾
			 */
			pJmpEnd = AnalyzeJmpEnd(pMem, ImageBase, addrStartMemoryAddress, &ud_obj);
			if ((!pJmpEnd) || (pJmpEnd <= pRet))
				return ofOffset;
		} else if (ud_obj.mnemonic == UD_Iret) {
			return ofOffset;
		} else if (ud_obj.mnemonic == UD_Inop) {
			if (!(pAnalyzeConfigure->bNopIsNotEnd))
				return ofOffset - ud_obj.inp_ctr;
		} else if (ud_obj.mnemonic == UD_Iint3) {
			if (!(pAnalyzeConfigure->bInt3IsNotEnd))
				return ofOffset - ud_obj.inp_ctr;
		} else if ((ud_obj.mnemonic == UD_Iadd) && (ud_obj.inp_ctr == 2) && (*(__word *)&(ud_obj.inp_sess) == 0)) {
			if (!(pAnalyzeConfigure->bZeroIsNotEnd))
				return ofOffset - ud_obj.inp_ctr;
		} else {
			// 自定的函数末尾特征码
		}
	}
	return ofOffset;
}

__INLINE__ PINSTRUCTION_JMP __INTERNAL_FUNC__ FindMaxJccTargetMemoryAddress(__address addrCurrMemoryAddress, PX86INSTRUCTION pInstructListHeader) {
	PINSTRUCTION_JMP pFind = NULL;
	PX86INSTRUCTION pCurrent = pInstructListHeader;
	while (pCurrent) {
		// 这里只判断JCC为偏移跳转的情况
		if ((pCurrent->bJmp) && (pCurrent->InstructionJmp.JmpType == JMP_TYPE_JCC_OFFSET)) {
			// 校验是否是向下跳
			if (pCurrent->InstructionJmp.JmpWay == JMP_WAY_DOWN) {
				// 校验它的跳转地址是否大于当前指令的地址
				if (pCurrent->InstructionJmp.addrTargetMemoryAddress > addrCurrMemoryAddress) {
					addrCurrMemoryAddress = pCurrent->InstructionJmp.addrTargetMemoryAddress;
					pFind = &(pCurrent->InstructionJmp);
				}
			}
		}
		pCurrent = pCurrent->pNext;
	}/* end while */
	return pFind;
}

__INLINE__ PX86INSTRUCTION __INTERNAL_FUNC__ FindLastRet(PX86INSTRUCTION pInstructListHeader) {
	PX86INSTRUCTION pFind = NULL;
	PX86INSTRUCTION pCurrent = pInstructListHeader;

	while (pCurrent) {
		if (pCurrent->ud_obj.mnemonic == UD_Iret) {
			pFind = pCurrent;
		}
		pCurrent = pCurrent->pNext;
	}/* end while */
	return pFind;
}

__INLINE__ __bool __INTERNAL_FUNC__ IsProcEnd(ud_t *pud_obj, PX86INSTRUCTION pInstructListHeader, PX86INSTRUCTION pInstruction, \
											  __bool *pPredictProcEnd, __integer *piEndSize) {
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	// 查看当前指令是否是ret, retn如果是,遍历跳转指令表,查看是否有JCC指令跳转到其后
	PANALYZE_CONFIGURE pAnalyzeConfigure = &(__GetProgramFromInstruction__(pInstruction)->AnalyzeConfigure);
	if (pud_obj->mnemonic == UD_Iret) {
		// 回溯跳转链,找到最大的跳转地址,如果存在则做预结束点分析
		PINSTRUCTION_JMP pMaxJmpEnd = FindMaxJccTargetMemoryAddress(pInstruction->addrCurrMemoryAddress, pInstructListHeader);
		if (pMaxJmpEnd == NULL)
			return TRUE;//没有JCC跳转
		
		if (pMaxJmpEnd->addrTargetMemoryAddress <= pInstruction->addrCurrMemoryAddress)
			return TRUE;//最后的JCC跳转最大跳转到当前指令
		else {//目标地址在当前ret之后
			__memory pDeepStart = pMaxJmpEnd->pTargetFileAddress;
			__address addrDeepStartMemoryAddress = pMaxJmpEnd->addrTargetMemoryAddress;
			__memory pRet = pInstruction->pCurrFileAddress;
			__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
			__integer iRet = PredictProcEnd(pMem, ImageBase, pDeepStart, addrDeepStartMemoryAddress, pRet, pAnalyzeConfigure);
			/*
			 * jcc lab1
			 * -> ret
			 * ...
			 * ...
			 * lab1:
			 * ...
			 * ...
			 * -> ret <- 这次的末尾
			 * iRet = 从lab1到这次末尾的长度
			 * 这里最后还要加上第一个ret到lab1的距离
			 */
			*piEndSize = iRet + (__integer)(pDeepStart - pRet);
			*pPredictProcEnd = TRUE;
		}
	} else if (pud_obj->mnemonic == UD_Ijmp) {
		PX86INSTRUCTION pLastRet = NULL;
		__address addrTargetAddress = 0;

		// 如果是向上跳转
		if (pInstruction->InstructionJmp.JmpWay == JMP_WAY_UP) {
			/*
			 * lab1:
			 * ...
			 * ...
			 * ret
			 * ...
			 * ...
			 * jmp lab1 <- 这里是末尾
			*/
			pLastRet = FindLastRet(pInstructListHeader);
			if (pLastRet) {
				addrTargetAddress = pInstruction->InstructionJmp.addrTargetMemoryAddress;
				if (addrTargetAddress <= pLastRet->addrCurrMemoryAddress)
					return TRUE;
			}
		}
	} else if (pud_obj->mnemonic == UD_Inop) {
		if (!(pAnalyzeConfigure->bNopIsNotEnd))
			return TRUE;
	} else if (pud_obj->mnemonic == UD_Iint3) {
		if (!(pAnalyzeConfigure->bInt3IsNotEnd))
			return TRUE;
	} else if ((pud_obj->mnemonic == UD_Iadd) && (pud_obj->inp_ctr == 2) && (*(__word *)&(pud_obj->inp_sess) == 0)) {
		if (!(pAnalyzeConfigure->bZeroIsNotEnd))
			return TRUE;
	} else {
		// 自定的函数末尾特征码
	}

	return FALSE;
}

PPROCEDURE __INTERNAL_FUNC__ InitProcedure(LPVOID pParents)
{
	PPROCEDURE pProcedure = __logic_new__(PROCEDURE, 1);
	if (!(pProcedure)) return NULL;
	ZeroMemory(pProcedure, sizeof(PROCEDURE));
	pProcedure->pParents = pParents;
	return pProcedure;
}

__void __INTERNAL_FUNC__ ReleaseProcedureRefFromList(PPROCEDURE_REFFROM *pRefFormListPoint) {
	PPROCEDURE_REFFROM pCurr = *pRefFormListPoint, pTmp = NULL;
	while (pCurr) {
		pTmp = pCurr->pNext;
		__logic_delete__(pCurr);
		pCurr = pTmp;
	}
	*pRefFormListPoint = NULL;
}

__INLINE__ __void __INTERNAL_FUNC__ ReleaseProcedure(PPROCEDURE *pProcedurePoint) {
	if ((*pProcedurePoint)->pInstruction)
		ReleaseInstructionList(&((*pProcedurePoint)->pInstruction));
	if ((*pProcedurePoint)->pProcedureRefForm)
		ReleaseProcedureRefFromList(&((*pProcedurePoint)->pProcedureRefForm));
	__logic_delete__(*pProcedurePoint);
	*pProcedurePoint = NULL;
}

__void __INTERNAL_FUNC__ ReleaseProcedureList(PPROCEDURE *pProcedureHeaderPoint) {
	PPROCEDURE pCurr = *pProcedureHeaderPoint, pTmp = NULL;
	while (pCurr) {
		pTmp = pCurr->pNext;
		ReleaseProcedure(&pCurr);
		pCurr = pTmp;
	}
	*pProcedureHeaderPoint = NULL;
}

__INLINE__ PINSTRUCTION_JMP __INTERNAL_FUNC__ GetInstructionJmpListHeader(PPROCEDURE pProcedure) {
	PX86INSTRUCTION pInstruction = pProcedure->pInstruction;
	PINSTRUCTION_JMP pInstructionJmpListHeader = NULL, *pCurrInstructionJmpPoint = &pInstructionJmpListHeader;
	while (pInstruction) {
		if (pInstruction->bJmp) {
			*pCurrInstructionJmpPoint = &(pInstruction->InstructionJmp);
			pCurrInstructionJmpPoint = &((*pCurrInstructionJmpPoint)->pNext);
		}
		pInstruction = pInstruction->pNext;
	}

	return pInstructionJmpListHeader;
}

/*
 * 获取单个函数帧
 * 使用IsProcEnd函数鉴别末尾,不处理中间遇到的CALL指令
 */
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ GetProcFrame(__memory pMem, __memory pStart, __integer iBlockMaxSize, PPROGRAM pParents) {
	PPROCEDURE pProcedure = InitProcedure(pParents);
	PX86INSTRUCTION pInstructionPrev = NULL, *pInstructionPoint = &(pProcedure->pInstruction);
	__address ImageBase = pParents->ImageBase;
	__offset ofOffset = 0;
	__integer iContinueSize = 0, iInstCount = 0;
	__bool bPredictProcEnd = FALSE;//是否启用预测函数结尾
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_input_buffer(&ud_obj, pStart, iBlockMaxSize);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	/*
	 * 预测结尾分析
	 * 可以在为遍历完指令流时,预先知道函数的末尾
	 */
	// 获取整个函数框架
	while (ud_disassemble(&ud_obj)) {
		__memory pCurrent = pStart + ofOffset;

		// 如果是未知指令,则记录它的数量
		if (ud_obj.mnemonic == UD_Iinvalid)
			(pProcedure->iInvalidOpcodeCount)++;

		*pInstructionPoint = InitInstruction(pProcedure, pInstructionPrev);
		AnalyzeInstructionPass1(&ud_obj, pMem, ImageBase, pCurrent, ofOffset, *pInstructionPoint);
		pInstructionPrev = *pInstructionPoint;

		// 判断是否到达函数末尾,常规分析
		if (IsProcEnd(&ud_obj, pProcedure->pInstruction, *pInstructionPoint, &bPredictProcEnd, &iContinueSize)) {
			ofOffset += ud_obj.inp_ctr;
			iInstCount++;
			goto _end_while;
		}

		/*
		 * 如果进入这里则说明当前指令必定是ret指令
		 */
		if (bPredictProcEnd) {
			// 将反汇编的缓冲区长度设置为
			// 从当前指令到预测出的函数结尾
			__memory pRetNextInstruction = (*pInstructionPoint)->pCurrFileAddress + ud_obj.inp_ctr;//得到ret指令下一条指令的位置
			ofOffset += ud_obj.inp_ctr;//将当前指令的长度加入偏移值内
			ud_set_input_buffer(&ud_obj, pRetNextInstruction, (size_t)iContinueSize);//ud_obj会重新初始化
			pInstructionPoint = &((*pInstructionPoint)->pNext);
			iInstCount++;
			bPredictProcEnd = FALSE;
			continue;//直接进入下一轮
		}

		// 移动指针
		pInstructionPoint = &((*pInstructionPoint)->pNext);
		ofOffset += ud_obj.inp_ctr;
		iInstCount++;
	}/* end while */
_end_while:

	// 填充函数基本信息
	pProcedure->addrMemoryStartAddress = pParents->ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pStart - pMem));
	pProcedure->pFileStartAddress = pStart;
	pProcedure->iSize = (__integer)ofOffset;
	pProcedure->iInstCount = iInstCount;
	pProcedure->pInstructionJmp = GetInstructionJmpListHeader(pProcedure);
	return pProcedure;
}

///*
// * 复制一个函数的内容到另一个函数
// * 返回pTo
// */
//__INLINE__ PPROCEDURE __INTERNAL_FUNC__ CopyProcedureData(PPROCEDURE pTo, PPROCEDURE pFrom) {
//	pTo->addrAllocStackMemoryAddress = pFrom->addrAllocStackMemoryAddress;
//	pTo->addrMemoryStartAddress = pFrom->addrMemoryStartAddress;
//	pTo->AllocStackType = pFrom->AllocStackType;
//	pTo->bBlock = pFrom->bBlock;
//	pTo->bEntry = pFrom->bEntry;
//	pTo->iInstCount = pFrom->iInstCount;
//	pTo->iInvalidOpcodeCount = pFrom->iInvalidOpcodeCount;
//	pTo->iSize = pFrom->iSize;
//	pTo->iStackSize = pFrom->iStackSize;
//	pTo->pAllocStackFileAddress = pFrom->pAllocStackFileAddress;
//	pTo->pFileStartAddress = pFrom->pFileStartAddress;
//	pTo->pInstruction = pFrom->pInstruction;
//	pTo->pInstructionJmp = pFrom->pInstructionJmp;
//	pTo->pParents = pFrom->pParents;
//	pTo->pProcedureRefForm = pFrom->pProcedureRefForm;
//	pTo->pNext = pFrom->pNext;
//	return pTo;
//}

/*
 * 链表排序
 * 从低地址到高地址的顺序
 * 使用泡沫排序
 */
//#define __CopyProcedureData__(pTo, pFrom){\
//	PPROCEDURE __pToLink__ = (pTo)->pNext;\
//	memcpy((pTo), (pFrom), sizeof(PROCEDURE));\
//	(pTo)->pNext = __pToLink__;}
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ SortProcedureList(PPROCEDURE pProcedureHeader) {
	PPROCEDURE p = NULL, q = NULL, t = NULL;
	__bool b = FALSE;

	// 如果只有一个节点,直接退出
	if (!(pProcedureHeader->pNext))
		return pProcedureHeader;
	
	q = p = pProcedureHeader;
	while (1) {

		// 每次新的循环都重新设置标志
		b = FALSE;

		// 重新设置p的值到起点
		p = q;

		// 每次上一次的节点都设置为NULL
		t = NULL;

		while (p) {
			// 后一个节点不为空
			if (p->pNext) {

				// 前一个节点的地址 大于 后一个节点的地址
				if (p->addrMemoryStartAddress > p->pNext->addrMemoryStartAddress) {
					PPROCEDURE m = NULL, n = NULL;

					m = p;
					n = p->pNext;

					if (t) t->pNext = n;//如果上一个节点不为NULL

					m->pNext = n->pNext;
					n->pNext = m;

					p = n;//回退一个节点,在下面的语句p = p->pNext执行后p会进入下一个节点

					// 设置标志,表示这一次排序未完成
					b = TRUE;
				}
			}

			// 如果t是NULL,则表示记录头节点
			if (!t) q = p;

			t = p;//记录上一个节点
			p = p->pNext;//移动到下一个节点
		}/* end while */
		
		// 每次循环完毕都检测排序是否完成,退出循环
		if (!b) break;
	}

	return q;
}

__INLINE__ __integer __INTERNAL_FUNC__ FindInlineProcedure(PPROCEDURE pProcedureListHeader) {
	__integer iCount = 0;
	PPROCEDURE pCheckProcedure = pProcedureListHeader;
	while (pCheckProcedure) {
		if (pCheckProcedure->pNext) {
			if (pCheckProcedure->addrMemoryStartAddress + pCheckProcedure->iSize > pCheckProcedure->pNext->addrMemoryStartAddress) {
				pCheckProcedure->pNext->bInline = TRUE;
				pCheckProcedure->pNext->pFatherProcedure = pCheckProcedure;
			}
		}
		pCheckProcedure = pCheckProcedure->pNext;
	}
}

__INLINE__ __bool __INTERNAL_FUNC__ SetProcToReferenceFromList(PPROCEDURE pProcedure, PPROCEDURE pRefFromProc) {
	PPROCEDURE_REFFROM *pCurr = &(pProcedure->pProcedureRefForm);
	if (!(*pCurr)) {
		pProcedure->pProcedureRefForm = __logic_new__(PROCEDURE_REFFROM, 1);
		pProcedure->pProcedureRefForm->pProcedure = (__void *)pRefFromProc;
		pProcedure->pProcedureRefForm->pNext = NULL;
		return FALSE;
	} else {
		// 寻找开是否在链中
		while (*pCurr) {
			// 在链中直接返回
			if ((*pCurr)->pProcedure == pRefFromProc)
				return TRUE;
			pCurr = &((*pCurr)->pNext);
		}
	}
	
	// 增加
	*pCurr = __logic_new__(PROCEDURE_REFFROM, 1);
	(*pCurr)->pProcedure = pRefFromProc;
	(*pCurr)->pNext = NULL;
	return FALSE;
}

__INLINE__ PPROCEDURE __INTERNAL_FUNC__ IsInProcedureList(PPROCEDURE pProcedureList, __address addrGotoAddress) {
	PPROCEDURE pCurr = pProcedureList;
	while (pCurr) {
		__address addrEndAddress = pCurr->addrMemoryStartAddress + pCurr->iSize;
		if ((addrGotoAddress >= pCurr->addrMemoryStartAddress) && (addrGotoAddress < addrEndAddress))
			return pCurr;
		pCurr = pCurr->pNext;
	}
	return NULL;
}

/*
 * 通过已经鉴别出来的函数,分析出以当前函数的跳出
 * 通过函数中的中CALL跳转来进行识别
 * 函数返回跳出的计数
 */
#define __GotoOutProcedure__(addrGotoMemoryAddress)	(((addrGotoMemoryAddress) < addrMemoryStart) || (addrGotoMemoryAddress >= addrMemoryEnd))
__void __INTERNAL_FUNC__ Procedure2Procedure(__memory pMem, PPROCEDURE pProcedureListHeader, PPROCEDURE pProcedure) {
	PINSTRUCTION_JMP pInstructionJmp = pProcedure->pInstructionJmp;
	__address addrMemoryStart = pProcedure->addrMemoryStartAddress;
	__address addrMemoryEnd = addrMemoryStart + pProcedure->iSize;
	PPROGRAM pParents = __GetProcedureParents__(pProcedure);
	PPROCEDURE *pMainProcedurePointEnd = &pProcedureListHeader;//函数链末尾指针
	while (*pMainProcedurePointEnd) pMainProcedurePointEnd = &((*pMainProcedurePointEnd)->pNext);//移动主链到末尾
	// 检查要扫描的函数是否在主函数链中,如果不在主函数链中则链接到末尾
	if (!IsInProcedureList(pProcedureListHeader, addrMemoryStart)) {
		*pMainProcedurePointEnd = pProcedure;
		pMainProcedurePointEnd = &((*pMainProcedurePointEnd)->pNext);
	}
	
	// 遍历指令链,如果存在CALL指令,则进入新的函数领域
	while (pInstructionJmp) {
		if ((pInstructionJmp->JmpType == JMP_TYPE_CALL_OFFSET) || (pInstructionJmp->JmpType == JMP_TYPE_JMP_OFFSET)) {
			__address addrTargetMemoryAddress = 0;
			// 检验跳转目标是否有效
			if (pInstructionJmp->bTargetAddressIsInvalid)
				goto _continue;
			addrTargetMemoryAddress = pInstructionJmp->addrTargetMemoryAddress;//获取目标的内存地址
			// 如果是跳到函数外
			if (__GotoOutProcedure__(addrTargetMemoryAddress)) {
				__memory pProcStart = pInstructionJmp->pTargetFileAddress;
				PPROCEDURE pNewProcedure = NULL;
				PPROCEDURE pTargetProcedure = IsInProcedureList(pProcedureListHeader, addrTargetMemoryAddress);
				pInstructionJmp->bJmpOut = TRUE;
				// 如果目标函数已经得到分析则略过
				if (pTargetProcedure) {
					// 检测跳转后函数的引用链
					SetProcToReferenceFromList(pTargetProcedure, pProcedure);
					goto _continue;
				}

				pNewProcedure = GetProcFrame(pMem, pProcStart, __MAX_PROCEDURE_LENGTH__, pParents);
				if (!pNewProcedure)
					goto _continue;
				
				// 设定新的函数跳转引用
				SetProcToReferenceFromList(pNewProcedure, pProcedure);
				Procedure2Procedure(pMem, pProcedureListHeader, pNewProcedure);
			}
		}/* end if */
_continue:
		pInstructionJmp = pInstructionJmp->pNext;
	}
	return;
}

PPROCEDURE __INTERNAL_FUNC__ FindEntryProcedure(PPROCEDURE pProcedureList) {
	PPROCEDURE pCurr = pProcedureList;
	while (pCurr) {
		if (pCurr->bEntry)
			return pCurr;
		pCurr = pCurr->pNext;
	}
	return NULL;
}

/*
 * 使用JMP指令进行鉴别
 * 如果是纯数据区返回TRUE,反之返回FALSE
 */
__INLINE__ __bool __INTERNAL_FUNC__ AbyssAnalyze(__memory pMem, __address ImageBase, __memory pCurr, __integer iSize) {
	__address addrStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurr - pMem));
	__offset ofOffset = 0;
	PX86INSTRUCTION pInstruction = NULL, pPrevInstruction = NULL, *pCurrInstructionPoint = &pInstruction;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	ud_set_input_buffer(&ud_obj, pCurr, iSize); 

	// 使用第一次指令派遣函数进行分析
	while (ud_disassemble(&ud_obj)) {
		__address addrCurrentAddress = addrStartAddress + ofOffset;
		*pCurrInstructionPoint = __logic_new__(X86INSTRUCTION, 1);
		__logic_memset__((*pCurrInstructionPoint), 0, sizeof(X86INSTRUCTION));
		(*pCurrInstructionPoint)->addrCurrMemoryAddress = addrCurrentAddress;
		(*pCurrInstructionPoint)->addrMemoryBlockStart = addrStartAddress;
		(*pCurrInstructionPoint)->iBlockSize = iSize;
		(*pCurrInstructionPoint)->pMem = pMem;
		__logic_memcpy__(&((*pCurrInstructionPoint)->ud_obj), &ud_obj, sizeof(ud_t));
		(*pCurrInstructionPoint)->pPrev = pPrevInstruction;//设置上层指令
		(*pCurrInstructionPoint)->pNext = NULL;

		// 执行分析
		InstructionDispatcher(g_pAnalyzeDataDispatcher, *pCurrInstructionPoint);
		if ((*pCurrInstructionPoint)->bErrorLogicInstruction) {//如果遇到逻辑错误指令则直接退出
			ReleaseInstructionList(&pInstruction);
			return TRUE;
		}

		// 链接链表
		if (pPrevInstruction)
			pPrevInstruction->pNext = (*pCurrInstructionPoint);

		pPrevInstruction = (*pCurrInstructionPoint);
		pCurrInstructionPoint = &((*pCurrInstructionPoint)->pNext);//下一个节点
		ofOffset += (__integer)ud_insn_len(&ud_obj);
	}/* end while */

	/*
	 * 如果没有错误指令,则进入更加深入的分析流程
	 */

	// 释放指令链表
	ReleaseInstructionList(&pInstruction);
	return FALSE;
}

/*
 * 如果是纯数据区域直接返回TRUE,反之返回FALSE
 */
__INLINE__ __bool __INTERNAL_FUNC__ DeepAnalyzeBlock(__memory pMem, __address ImageBase, __memory pCurr, __integer iSize, PANALYZE_CONFIGURE pAnalyzeConfigure) {
	__bool bBlock = FALSE;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	ud_set_input_buffer(&ud_obj, pCurr, iSize);

	while (ud_disassemble(&ud_obj)) {
		enum ud_mnemonic_code mnemonic = ud_obj.mnemonic;
		if ((mnemonic == UD_Iinvalid) && (!(pAnalyzeConfigure->bDisInvalidOpcodeIsData))) {
			bBlock = TRUE;
			return bBlock;
		}
	}

	/*
	 * 进行深度分析
	 */
	bBlock = AbyssAnalyze(pMem, ImageBase, pCurr, iSize);

	return bBlock;
}

/*
 * 预读分析阶段,在分区处理是时进行,数据与代码区域
 * 范围的界定,纯数据区域返回TRUE,反之为FALSE
 */
__INLINE__ __bool __INTERNAL_FUNC__ PredictBlockEnd(__memory pMem, __address ImageBase, __memory pCurr, __integer iSize, \
													__integer *piOutSize, PANALYZE_CONFIGURE pAnalyzeConfigure) {
	__bool bBlock = FALSE;
	__offset ofOffset = 0;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	ud_set_input_buffer(&ud_obj, pCurr, iSize);
	while (ud_disassemble(&ud_obj)) {
		enum ud_mnemonic_code mnemonic = ud_obj.mnemonic;
		if ((mnemonic == UD_Inop) || \
			(mnemonic == UD_Iint3) || \
			((mnemonic == UD_Iadd) && (ud_obj.inp_ctr == 2) && (*(__word *)&(ud_obj.inp_sess) == 0))) {
			/*
			 * 到达结束条件
			 * 检查是否到达了用户定义代码的最小范围,如果没到直接视为数据
			 * 如果大于等于则进入深入鉴别
			 */
			if (ofOffset < pAnalyzeConfigure->bCodeMixSize)
				bBlock = TRUE;
			else
				// 进入深度分析
				bBlock = DeepAnalyzeBlock(pMem, ImageBase, pCurr, ofOffset, pAnalyzeConfigure);
			*piOutSize = (__integer)ofOffset;
			return bBlock;
		}/* end if */
		ofOffset += (__integer)ud_insn_len(&ud_obj);
	}

	// 这里做深度鉴别
	bBlock = DeepAnalyzeBlock(pMem, ImageBase, pCurr, iSize, pAnalyzeConfigure);
	*piOutSize = (__integer)ofOffset;
	return bBlock;
}

/*
 * 进行分区处理
 * 以NOP,INT3,0,无效指令编码字符进行分区标志
 * 遇到NOP或者INT3,0,无效指令编码则将扫描过的区域
 * 作为一个区块摘出,继续查询,如果其后的数据有很长
 * 一段为连续的 NOP,INT3,0字节则将此视做绝对无效区域,
 * 在扫描过程中,如果遇到无效指令直接忽略当作这个区域
 * 的一部分如果遇到有效指令,则进入预分析阶段,尝试向前
 * 分析如果分析的指令长度小于最小代码长度则直接忽略.如果
 * 大于则将此区域继续分析,往返以上流程.直到完毕
 */
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ FormatBlock(__memory pMem, __address ImageBase, __memory pStart, __integer iSize, PANALYZE_CONFIGURE pAnalyzeConfigure) {
	__integer iBlockEndSignCount = 0;
	__offset ofOffset = 0;
	PPROCEDURE pBlock = NULL;
	PPROCEDURE *pCurrBlockPoint = &pBlock;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	ud_set_input_buffer(&ud_obj, pStart, iSize);

	while (ud_disassemble(&ud_obj)) {
		enum ud_mnemonic_code mnemonic = ud_obj.mnemonic;
		if ((mnemonic == UD_Inop) || \
			(mnemonic == UD_Iint3) || \
			((mnemonic == UD_Iadd) && (ud_obj.inp_ctr == 2) && (*(__word *)&(ud_obj.inp_sess) == 0)))
			iBlockEndSignCount += (__integer)ud_insn_len(&ud_obj);
		else {
			/*
			 * 遇到有效指令了
			 * 现在该进入预读分析阶段,这里还有一个判断
			 * 标志是剩余长度,如果其后的长度小于最小代码
			 * 长度直接将这段代码视作为数据
			 */
			__integer iRemainSize = iSize - (__integer)ofOffset;
			__memory pCurr = pStart + (__integer)ofOffset;
			if (iRemainSize >= pAnalyzeConfigure->bCodeMixSize) {
				/*
				 * 进入预读分析阶段
				 * 在这里开始判断,如果预读处理分析的结果为单纯的数据块则
				 * 与先前分析的区域进行合并
				 * 否则单独为前面分析的块分配内存
				 */
				__integer iOutSize = 0;
				if (PredictBlockEnd(pMem, ImageBase, pCurr, iRemainSize, &iOutSize, pAnalyzeConfigure))
					iBlockEndSignCount += iOutSize;//进行合并
				else {
					/*
					 * 判断上一组区块标记是否为0如果不为则分配空间存储它
					 */
					if (iBlockEndSignCount) {
						(*pCurrBlockPoint) = __logic_new__(PROCEDURE, 1);
						__logic_memset__((*pCurrBlockPoint), 0, sizeof(PROCEDURE));
						(*pCurrBlockPoint)->bBlock = TRUE;//数据区域
						(*pCurrBlockPoint)->pFileStartAddress = pCurr - iBlockEndSignCount;
						(*pCurrBlockPoint)->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)((*pCurrBlockPoint)->pFileStartAddress - pMem));
						(*pCurrBlockPoint)->iSize = iBlockEndSignCount;
						pCurrBlockPoint = &((*pCurrBlockPoint)->pNext);
						iBlockEndSignCount = 0;//清空标志记录计数
					}
					// 设定此段为代码区域
					(*pCurrBlockPoint) = __logic_new__(PROCEDURE, 1);
					__logic_memset__((*pCurrBlockPoint), 0, sizeof(PROCEDURE));
					(*pCurrBlockPoint)->bBlock = FALSE;//代码区域
					(*pCurrBlockPoint)->pFileStartAddress = pCurr;
					(*pCurrBlockPoint)->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurr - pMem));
					(*pCurrBlockPoint)->iSize = iOutSize;
					pCurrBlockPoint = &((*pCurrBlockPoint)->pNext);
				}

				// 重新设定反汇编指针
				pCurr += iOutSize;
				(__integer)ofOffset += iOutSize;
				iRemainSize -= iOutSize;//剩余长度
				ud_set_input_buffer(&ud_obj, pCurr, iRemainSize);
				continue;
			} else {
				// 进入到这里就是进入到分析的末尾
				(*pCurrBlockPoint) = __logic_new__(PROCEDURE, 1);
				__logic_memset__((*pCurrBlockPoint), 0, sizeof(PROCEDURE));
				(*pCurrBlockPoint)->bBlock = TRUE;//表示有可能是数据
				iBlockEndSignCount += iRemainSize;
				(*pCurrBlockPoint)->iSize = iBlockEndSignCount;
				(*pCurrBlockPoint)->pFileStartAddress = pCurr;
				(*pCurrBlockPoint)->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurr - pMem));
				pCurrBlockPoint = &((*pCurrBlockPoint)->pNext);
				iBlockEndSignCount = 0;//清空标志记录计数
			}
		}
		(__integer)ofOffset += ud_insn_len(&ud_obj);
	}

	/*
	 * 处理组后一个纯区域块
	 * 两种情况造成这种现象
	 * 1) 整个分析的数据都是纯数据区
	 * 2) 被分析的数据最后一个区域是纯数据区
	 */
	if (iBlockEndSignCount) {
		__memory pBlockZoon = NULL;
		// 第一种情况
		if (iBlockEndSignCount == iSize)
			pBlockZoon = pStart;
		else
			pBlockZoon = pStart + iSize - iBlockEndSignCount;
		(*pCurrBlockPoint) = __logic_new__(PROCEDURE, 1);
		__logic_memset__((*pCurrBlockPoint), 0, sizeof(PROCEDURE));
		(*pCurrBlockPoint)->bBlock = TRUE;//表示有可能是数据
		(*pCurrBlockPoint)->iSize = iBlockEndSignCount;
		(*pCurrBlockPoint)->pFileStartAddress = pBlockZoon;
		(*pCurrBlockPoint)->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pBlockZoon - pMem));
		pCurrBlockPoint = &((*pCurrBlockPoint)->pNext);
		iBlockEndSignCount = 0;//清空标志记录计数
	}

	return pBlock;
}

/*
 * 进行预分析,识别出数据
 * 如果分析出不是数据,则进行代码识别
 */	
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ AnalyzeData(__memory pMem, __address ImageBase, __memory pCurr, __integer iSize, PPROCEDURE pProcedureList, PPROGRAM pParents) {
	PPROCEDURE pFormatBlockList = NULL, pCurrBlock = NULL;
	PANALYZE_CONFIGURE pAnalyzeConfigure = &(pParents->AnalyzeConfigure);
	// 如果此块的长度小于用户指定长度
	if (iSize < pAnalyzeConfigure->bCodeMixSize) {
		PPROCEDURE *pCurrMainPoint = &pProcedureList;
		PPROCEDURE pBlock = __logic_new__(PROCEDURE, 1);
		__logic_memset__(pBlock, 0, sizeof(PROCEDURE));
		pBlock->bBlock = TRUE;
		pBlock->pFileStartAddress = pCurr;
		pBlock->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurr - pMem));
		pBlock->iSize = iSize;
		pBlock->pNext = NULL;

		while (*pCurrMainPoint) pCurrMainPoint = &((*pCurrMainPoint)->pNext);
		*pCurrMainPoint = pBlock;
		return pProcedureList;
	}

	/*
	 * 开始对这个块进行有效的分区
	 * 分区完毕后对链中的代码块进行函数帧分析
	 * 初次分析
	 */
	pFormatBlockList = FormatBlock(pMem, ImageBase, pCurr, iSize, pAnalyzeConfigure);

	/*
	 * 遍历此链表进行分析
	 * 如果遇到代码块则进入并开始代码分析
	 */
	pCurrBlock = pFormatBlockList;
	while (pCurrBlock) {
		if (!(pCurrBlock->bBlock)) {//为代码块
			// 进行分析
			PPROCEDURE pProcedure = NULL;

			// 获取函数帧
			pProcedure = GetProcFrame(pMem, pCurrBlock->pFileStartAddress, pCurrBlock->iSize, pParents);

			/*
			 * 调用Procedure2Procedure过后形成的函数链中存在两种函数,一种是函数存在在已有的
			 * 未知区域中,一种是在做第一次扫描时分析到的函数
			 */
			Procedure2Procedure(pMem, pProcedureList, pProcedure);
		} else {
			// 直接连接到主链
			PPROCEDURE *pCurrMainPoint = &pProcedureList;
			while (*pCurrMainPoint) pCurrMainPoint = &((*pCurrMainPoint)->pNext);
			*pCurrMainPoint = __logic_new__(PROCEDURE, 1);
			__logic_memcpy__(*pCurrMainPoint, pCurrBlock, sizeof(PROCEDURE));
			(*pCurrMainPoint)->pNext = NULL;
		}
		pCurrBlock = pCurrBlock->pNext;
	}

	// 销毁分析链
	ReleaseProcedureList(&pFormatBlockList);
	return pProcedureList;
}

/*
 * 内存块队列
 */
typedef struct _CODE_BLOCK {
	__memory pPoint;//指针
	__integer iSize;//长度
} CODE_BLOCK, *PCODE_BLOCK;

/*
 * 找寻所有不在链上的内存区域,并归结到链上
 */
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ AnalyzeProcedurePass1DiscoveryUnknowZoon(__memory pMem, PPROCEDURE pProcedureList, PPROGRAM pParents) {
	__integer iCodeSize = pParents->iCodeSegSize;
	__integer iCurrSize = 0, iBlockSize = 0, iRemainSize = iCodeSize;
	__memory pNow = NULL;
	__memory pStart = pParents->pCodeSeg;
	__memory pCurr = pStart;
	__address ImageBase = pParents->ImageBase;
	PPROCEDURE pCurrProcedure = pProcedureList, pUnknowProcedureList = NULL;

	// 产生指令分析分派函数
	g_pAnalyzeDataDispatcher = MakeAnalyzeDataFromInstructionDispatcher();

_new_analyze:
	while (pCurrProcedure) {
		pNow = pCurrProcedure->pFileStartAddress;
		iCurrSize = pCurrProcedure->iSize;

		if (pCurr == pNow) {//如果相当则直接略过
			pCurr += iCurrSize;
			iRemainSize -= iCurrSize;
		} else if (pCurr < pNow) {//分析这个代码块
			iBlockSize = (__integer)(pNow - pCurr);
			iRemainSize -= iBlockSize;
			goto _handler;
		} else {//pCurr > pNow
			// 内联函数
		}
		pCurrProcedure = pCurrProcedure->pNext;
	}

	// 判断是否到达末尾
	if (iRemainSize) {
		iBlockSize = iRemainSize;
		goto _handler;
	}

	// 释放派遣表
	DestroyDispatcherList(&g_pAnalyzeDataDispatcher);
	return pProcedureList;

// 这里为处理函数所在
_handler:
	/*
	 * 这里的处理和前一次处理有个区别就是不知道当前这个区域是
	 * 数据还是代码,所有首先要做数据鉴别
	 */
	pUnknowProcedureList = AnalyzeData(pMem, ImageBase, pCurr, iBlockSize, pProcedureList, pParents);
	pProcedureList = SortProcedureList(pProcedureList);//排序

	// 重新设定所有初始值,然后重新来过
	pCurr = pStart;
	iRemainSize = iCodeSize;//重新设定长度
	pUnknowProcedureList = NULL;
	pCurrProcedure = pProcedureList;
	__PrintProcedureListCount__(pProcedureList);
	goto _new_analyze;//重新进入新的一次分析
}

/*
 * 将不在函数链上的区域直接视为数据并链接到链上
 */
__INLINE__ PPROCEDURE __INTERNAL_FUNC__ LinkUnknowZoonToProcedureListAsBlock(__memory pMem, PPROCEDURE pProcedureList, PPROGRAM pParents) {
	__integer iCurrSize = 0, iBlockSize = 0;
	__address ImageBase = pParents->ImageBase;
	PPROCEDURE pCurrProcedure = pProcedureList, pPrevProcedure = NULL;
	__memory pCurr = pParents->pCodeSeg;
	__memory pNow = pCurrProcedure->pFileStartAddress;

	while (pCurrProcedure) {
		pNow = pCurrProcedure->pFileStartAddress;
		iCurrSize = pCurrProcedure->iSize;

		if (pCurr == pNow) {//如果相当则直接略过
			pCurr += iCurrSize;
		} else if (pCurr < pNow) {
			PPROCEDURE pCurrBlockPoint = NULL;

			pCurrBlockPoint = __logic_new__(PROCEDURE, 1);
			__logic_memset__(pCurrBlockPoint, 0, sizeof(PROCEDURE));
			pCurrBlockPoint->bBlock = TRUE;//数据区域
			pCurrBlockPoint->pFileStartAddress = pCurr;
			pCurrBlockPoint->addrMemoryStartAddress = ImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurr - pMem));
			iBlockSize = (__integer)(pNow - pCurr);//块的大小
			pCurrBlockPoint->iSize = iBlockSize;
			pCurrBlockPoint->pNext = NULL;

			// 插入到合适的位置
			if (pPrevProcedure) pPrevProcedure->pNext = pCurrBlockPoint;
			else pProcedureList = pCurrBlockPoint;
			pCurrBlockPoint->pNext = pCurrProcedure;

			// pCurr指针移动
			pCurr = pNow + iCurrSize;
		} else {//pCurr > pNow
			// 发现INLINE函数,直接跳过
			pCurr = pPrevProcedure->pFileStartAddress + pPrevProcedure->iSize;
		}

		pPrevProcedure = pCurrProcedure;//记录上一个函数
		pCurrProcedure = pCurrProcedure->pNext;
	}/* end while */

	pCurrProcedure = SortProcedureList(pProcedureList);
	return pCurrProcedure;
}

/*
 * 第一次遍历分析
 */
PPROCEDURE __INTERNAL_FUNC__ AnalyzeProcedurePass1(PPROGRAM pParents) {
	__memory pMem = pParents->pMem;
	__integer iSize = 0;
	PPROCEDURE pProcedureHeader = NULL, pEnteryProcedure = NULL;
	__integer iEntryRva = pParents->iEntryRva;
	__memory pStart = pMem + AnalyzerRva2Raw(pMem, iEntryRva);
	__integer iInlineProcCount = 0;
	__integer iCodeSize = pParents->iCodeSegSize;
	__integer iCodeSegRaw = pParents->pCodeSeg - pMem;
	__integer iBlockMaxSize = iCodeSize - (iEntryRva - AnalyzerRaw2Rva(pMem, iCodeSegRaw));

	// 生成派遣表
	g_pPass1Dispatcher = MakeAnalyzeInstructionPass1Dispatcher();

	// 首先鉴别出入口函数
	pEnteryProcedure = GetProcFrame(pMem, pStart, iBlockMaxSize, pParents);
	if (!pEnteryProcedure)
		return NULL;
	pEnteryProcedure->bEntry = TRUE;

	/*
	 * 通过入口函数鉴别出其他函数
	 * 由于此函数要进行递归, 首次调用链头为自己
	 */
	Procedure2Procedure(pMem, pEnteryProcedure, pEnteryProcedure);
	__PrintProcedureListCount__(pEnteryProcedure);

	pProcedureHeader = SortProcedureList(pEnteryProcedure);//对函数帧链表进行排序
	__PrintProcedureListCount__(pProcedureHeader);
	__CheckProcedureList1__(pProcedureHeader);
	__CheckProcedureList2__(pProcedureHeader);

	/*
	 * 寻找内联函数
	 */
	iInlineProcCount = FindInlineProcedure(pProcedureHeader);
	pParents->iInlineProcCount = iInlineProcCount;

	/*
	 * 如果不开启未知区域探测,则把未在链上的区域当作数据处理
	 */
	if (pParents->AnalyzeConfigure.bEnableDiscoveryUnknowZoon) {
		// 进行未知区域探索
		pProcedureHeader = AnalyzeProcedurePass1DiscoveryUnknowZoon(pMem, pProcedureHeader, pParents);
		__PrintProcedureListCount__(pProcedureHeader);
	} else {
		// 不进行未知区域探测
		pProcedureHeader = LinkUnknowZoonToProcedureListAsBlock(pMem, pProcedureHeader, pParents);
		__PrintProcedureListCount__(pProcedureHeader);
	}

	// 这里进行两项错误型检查,在调试模式下使用
	__CheckSameAddressProcedure__(pProcedureHeader);
	__CheckInstructionsParents__(pProcedureHeader);
	__CheckProcedureList1__(pProcedureHeader);
	__CheckProcedureList2__(pProcedureHeader);

	DestroyDispatcherList(&g_pPass1Dispatcher);//释放派遣表
	return pProcedureHeader;
}

