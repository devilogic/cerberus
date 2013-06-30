#include "PowerProtecterAth.h"
#include "Support.h"
#include "lcrypto.h"

#include "PowerProtecterThunkCoder.c"

/*
 * 全局变量
 */
POWER_PROTECTER_ATTACH_CONFIGURE g_PowerProtecterAttachConfigure = {0};

/*
 * 参数:
 *	ofRVA:指令的RVA
 *	pInstructions:记录的指令链
 *	iCount:指令链的计数
 *
 * 介绍:
 *	确定指定的地址是否是需要加密的指令
 */
__INLINE__ PPOWER_PROTECTER_INSTRUCTION __INTERNAL_FUNC__ ThisInstructionIsNeedProtect(__offset ofRVA, PPOWER_PROTECTER_INSTRUCTION pInstructions, __integer iCount) {
	__integer i = 0;
	for (i = 0; i < iCount; i++) {
		if (ofRVA == pInstructions->Instruction.ofMemRVA)
			return pInstructions;
		pInstructions++;
	}
	return NULL;
}

/*
 * 参数:
 *	ofStartRVA:函数的起始RVA
 *	ofEndRVA:函数结束RVA
 *	ofTargetRVA:跳转的目标内存RVA
 *
 * 介绍:
 *	跳转指令是否向外跳转
 */
__INLINE__ __bool __INTERNAL_FUNC__ IsJmpGotoOut(__offset ofStartRVA, __offset ofEndRVA, __offset ofTargetRVA) {
	if ((ofTargetRVA < ofStartRVA) || (ofTargetRVA >= ofEndRVA))
		return TRUE;
	return FALSE;
}

/*
 * 参数:
 *	pud_obj:反汇编结构,用来记录指令的汇编信息
 *
 * 介绍:
 *	判断一条指令是否是流程指令
 */
__INLINE__ POWER_PROTECTER_FLOW_TYPE __INTERNAL_FUNC__ IsFlowInstruction(ud_t *pud_obj) {
	switch (pud_obj->mnemonic) {
	case UD_Ijo: return PPFT_JO; break;
	case UD_Ijno: return PPFT_JNO; break;
	case UD_Ijb: return PPFT_JB; break;
	case UD_Ijae: return PPFT_JAE; break;
	case UD_Ijz: return PPFT_JZ; break;
	case UD_Ijnz: return PPFT_JNZ; break;
	case UD_Ijbe: return PPFT_JBE; break;
	case UD_Ija: return PPFT_JA; break;
	case UD_Ijs: return PPFT_JS; break;
	case UD_Ijns: return PPFT_JNS; break;
	case UD_Ijp: return PPFT_JP; break;
	case UD_Ijnp: return PPFT_JNP; break;
	case UD_Ijl: return PPFT_JL; break;
	case UD_Ijge: return PPFT_JGE; break;
	case UD_Ijle: return PPFT_JLE; break;
	case UD_Ijg: return PPFT_JG; break;
	case UD_Ijcxz: return PPFT_JCXZ; break;
	case UD_Ijecxz: return PPFT_JECXZ; break;
	case UD_Ijrcxz: return PPFT_JRCXZ; break;
	case UD_Iloopnz: return PPFT_LOOPNE; break;
	case UD_Iloope: return PPFT_LOOPE; break;
	case UD_Iloop: return PPFT_LOOP; break;
	case UD_Ijmp: return PPFT_JMP; break;
	case UD_Icall: return PPFT_CALL; break;
	case UD_Iret: return PPFT_RET; break;
	}
	return PPFT_NONE;
}

/*
 * 参数:
 *	pud_obj:反汇编结构,用来记录指令的汇编信息
 *
 * 介绍:
 *	检测流程指令是否是偏移相对寻址类型,如果是则返回这条流程指令的具体类型,否则返回PPFT_NONE
 */
__INLINE__ POWER_PROTECTER_FLOW_TYPE __INTERNAL_FUNC__ IsFlowInstructionByOffset(ud_t *pud_obj) {
	POWER_PROTECTER_FLOW_TYPE Type = PPFT_NONE;

	Type = IsFlowInstruction(pud_obj);
	if (Type != PPFT_NONE) {
		// 检测是否是直接的偏移
		if (pud_obj->operand[0].type == UD_OP_JIMM)
			return Type;
		else if (Type == PPFT_RET)
			return Type;
	}

	return PPFT_NONE;
}

/*
 * 参数:
 *	pMem:被保护程序的文件映射
 *	pud_obj:反汇编结构
 *	ofProcMemRVA:函数的内存RVA
 *	iProcSize:函数的长度
 *	pInstruction:要加密的指令
 *	pEncryptInstruction:加密指令的结构的指针(写入点)
 *
 * 介绍:
 *	加密指定的指令
 */
__INLINE__ __void __INTERNAL_FUNC__ PowerProtectThisInstruction(__memory pMem, ud_t *pud_obj, __offset ofProcMemRVA, __integer iProcSize, \
	PPOWER_PROTECTER_INSTRUCTION pInstruction, PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pEncryptInstruction) {
	__memory pFileAddress = NULL;
	__integer iInstLength = 0;
	__offset ofRVA = 0;
	POWER_PROTECTER_FLOW_TYPE JmpType = PPFT_NONE;
	__offset ofProcEndMemRVA = 0;

	// 计算出函数的结尾
	ofProcEndMemRVA = ofProcMemRVA + iProcSize;

	iInstLength = pud_obj->inp_ctr;
	pFileAddress = pud_obj->inp_buff;
	pFileAddress -= iInstLength;

	// 设置基本信息
	pEncryptInstruction->ofMemRVA = pInstruction->Instruction.ofMemRVA;
	ofRVA = pEncryptInstruction->ofMemRVA;

	// 获取这条指令的类型
	JmpType = IsFlowInstructionByOffset(pud_obj);

	/*
	 * 这里是流程与非流程指令公用的设置部分
	 */

	// 设置这条指令的跳转类型
	pEncryptInstruction->JmpType = JmpType;

	// 指令长度
	pEncryptInstruction->iInstLen = iInstLength;

	// 如果这条指令是偏移跳转指令
	if (JmpType != PPFT_NONE) {

		// 如果是流程指令直接进行异常处理
		if (iInstLength == 1) {
			*(__byte *)pFileAddress = PowerProtecterRandGetExceptionInst();
		} else {
			__integer iRemainSize = 0;
			*(__byte *)pFileAddress = PowerProtecterRandGetExceptionInst();
			iRemainSize = iInstLength - 1;
			PowerProtecterGetJmpThunkCode(pFileAddress + 1, iRemainSize);
		}

		// 如果是返回指令
		if (JmpType == PPFT_RET) {
			// 记录要返回的参数个数
			pEncryptInstruction->iRetSize = pud_obj->operand[0].lval.udword;//记录它的参数长度
			pEncryptInstruction->bOut = TRUE;
			pEncryptInstruction->ofTargetMemRVA = 0;//RET指令的目标地址为0
		} else {
			// 计算他们的目的地址
			__offset ofTargetRVA = 0;
			__offset ofOffset = 0;
			ofOffset = pud_obj->operand[0].lval.udword;
			if (pud_obj->operand[0].size == 8) {
				__byte bOffset = 0;
				bOffset = pud_obj->operand[0].lval.ubyte;
				if (__IsNegative8__(bOffset)) {
					ofTargetRVA = (__offset)CalcTargetAddress(8, (__address)ofRVA, bOffset, iInstLength, TRUE);
				} else {
					ofTargetRVA = (__offset)CalcTargetAddress(8, (__address)ofRVA, bOffset, iInstLength, FALSE);
				}
			} else if (pud_obj->operand[0].size == 16) {
				__word wOffset = 0;
				wOffset = pud_obj->operand[0].lval.uword;
				if (__IsNegative16__(wOffset)) {
					ofTargetRVA = (__offset)CalcTargetAddress(16, (__address)ofRVA, wOffset, iInstLength, TRUE);
				} else {
					ofTargetRVA = (__offset)CalcTargetAddress(16, (__address)ofRVA, wOffset, iInstLength, FALSE);
				}
			} else if (pud_obj->operand[0].size == 32) {
				__dword dwOffset = 0;
				dwOffset = pud_obj->operand[0].lval.udword;
				if (__IsNegative32__(dwOffset)) {
					ofTargetRVA = (__offset)CalcTargetAddress(32, (__address)ofRVA, dwOffset, iInstLength, TRUE);
				} else {
					ofTargetRVA = (__offset)CalcTargetAddress(32, (__address)ofRVA, dwOffset, iInstLength, FALSE);
				}
			}
			// 检测是否跳出函数
			if (IsJmpGotoOut(ofProcMemRVA, ofProcEndMemRVA, ofTargetRVA)) {
				if (JmpType == PPFT_CALL)//CALL指令不属于向外部跳转的指令
					pEncryptInstruction->bOut = FALSE;
				else
					pEncryptInstruction->bOut = TRUE;
			} else 
				pEncryptInstruction->bOut = FALSE;

			// 设置目的地址
			pEncryptInstruction->ofTargetMemRVA = ofTargetRVA;
		}/* end else */
	} else {
		// 这些是非流程指令
		// 保存这条指令
		__logic_memset__(pEncryptInstruction->InstBuf, 0x90, __POWER_PROTECTER_MAX_INSTRUCTION_BUFFER_SIZE__);
		__logic_memcpy__(pEncryptInstruction->InstBuf, pFileAddress, iInstLength);

		// 这条指令是否有监视的内存地址
		if (pInstruction->bWatched) {
			__memory pWatchFileAddress = NULL;
			__integer iWatchSize = 0;
			__dword dwKey = 0;

			pEncryptInstruction->bIsWatched = TRUE;
			pEncryptInstruction->WatchRecord.ofMemRVA = pInstruction->WatchRecord.ofMemRVA;
			pEncryptInstruction->WatchRecord.iSize = pInstruction->WatchRecord.iSize;

			pWatchFileAddress = pMem + Rva2Raw(pMem, pEncryptInstruction->WatchRecord.ofMemRVA);
			iWatchSize = pEncryptInstruction->WatchRecord.iSize;

			// 计算监视内存的Key
			dwKey = crc32(pWatchFileAddress, iWatchSize);
			XorArray(dwKey, pEncryptInstruction->InstBuf, pEncryptInstruction->InstBuf, iInstLength);

		} else {
			// 使用默认的KEY进行加密
			__dword dwKey = 0;

			pEncryptInstruction->bIsWatched = FALSE;
			dwKey = GenerateRandomNumber();//随机产生密钥
			XorArray(dwKey, pEncryptInstruction->InstBuf, pEncryptInstruction->InstBuf, iInstLength);
			pEncryptInstruction->dwKey = dwKey;//设置密钥
		}

		// 非流程指令,在最后在异常指令
		if (iInstLength == 1) {
			*(__byte *)pFileAddress = PowerProtecterRandGetExceptionInst();
		} else {
			__integer iRemainSize = 0;
			*(__byte *)pFileAddress = PowerProtecterRandGetExceptionInst();
			iRemainSize = iInstLength - 1;
			PowerProtecterGetJmpThunkCode(pFileAddress + 1, iRemainSize);
		}

		pEncryptInstruction->bOut = FALSE;//无跳转
	}/* end else */
}

/*
 * 参数:
 *	pMem:被保护程序的文件映射
 *	pProcFileAddress:函数的文件地址
 *	ofProcMemRVA:函数的RVA
 *	iProcSize:函数的长度
 *	pProtectInstructions:要加密的指令
 *	iProtectInstCount:要保护指令的个数
 *	pPowerProtecterEncryptInstruction:加密指令结构的指针(写入点)
 *	pPowerProtecterEncryptProcedure:加密函数的结构的指针(写入点)
 *
 * 介绍:
 *	加密指定的函数函数
 */
__INLINE__ __integer __INTERNAL_FUNC__ PowerProtectProcedure(__memory pMem, __memory pProcFileAddress, __offset ofProcMemRVA, __integer iProcSize, \
	PPOWER_PROTECTER_INSTRUCTION pProtectInstructions, __integer iProtectInstCount, PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pPowerProtecterEncryptInstruction, \
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pPowerProtecterEncryptProcedure) {
	__integer iFlowInstCount = 0;
	__integer iInstLength = 0;
	__offset ofOffset = 0;
	__memory pCurr = NULL;
	__offset ofCurrMemRVA = 0;
	PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pEncryptInstruction = NULL;
	PPOWER_PROTECTER_INSTRUCTION pNowProtectInstruction = NULL;
	ud_t ud_obj = {0};

	pCurr = pProcFileAddress;
	ofCurrMemRVA = ofProcMemRVA;

	pEncryptInstruction = pPowerProtecterEncryptInstruction;

	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, pProcFileAddress, iProcSize);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	while (ud_disassemble(&ud_obj)) {
		iInstLength = ud_obj.inp_ctr;//指令长度

		// 如果是其他指令则判断是否在保护范围内区域
		pNowProtectInstruction = ThisInstructionIsNeedProtect(ofCurrMemRVA, pProtectInstructions, iProtectInstCount);
		if (pNowProtectInstruction) {
			/*
			 * 如果是用户指定的保护指令
			 */
			PowerProtectThisInstruction(pMem, &ud_obj, ofCurrMemRVA, iProcSize, pNowProtectInstruction, pEncryptInstruction);
			pEncryptInstruction++;//移动到下一个加密指令结构
		} else if (IsFlowInstructionByOffset(&ud_obj) != PPFT_NONE) {
			/*
			 * 如果是流程指令则必进行保护
			 */
			POWER_PROTECTER_INSTRUCTION PowerProtecterInstruction = {0};
			PowerProtecterInstruction.bWatched = FALSE;
			PowerProtecterInstruction.Instruction.ofMemRVA = ofCurrMemRVA;
			PowerProtecterInstruction.Instruction.iSize = iInstLength;
			pNowProtectInstruction = &PowerProtecterInstruction;

			PowerProtectThisInstruction(pMem, &ud_obj, ofCurrMemRVA, iProcSize, pNowProtectInstruction, pEncryptInstruction);
			pEncryptInstruction++;//移动到下一个加密指令结构
			iFlowInstCount++;
		}
		
		// 记录相关信息
		ofOffset += iInstLength;
		pCurr += iInstLength;
		ofCurrMemRVA += iInstLength;
	}

	return iFlowInstCount;
}

/*
 * 参数:
 *	pProcedure:函数文件地址
 *	iProcSize:函数长度
 *	pKeyProcedure:密钥函数文件地址
 *	iKeyProcSize:密钥函数长度
 *	pInstructions:指令的文件地址
 *	iInstructionSize:指令的长度
 *	pPowerProtecterEncryptProcedure:解密函数结构
 *
 * 介绍:
 *	使用函数的明文产生一个密钥X, 用X加密指令保护结构
 *	使用密钥函数KP产生一个密钥Y, 用Y加密函数P产生密文C0
 *	使用    C0    产生一个密钥Z, 用Z加密记录密钥函数地址的区域内存产生密文C1 //用Z加密当前函数的原始地址
 */
__INLINE__ __void __INTERNAL_FUNC__ PowerProtecterEncryptProcedure(__memory pProcedure, __integer iProcSize, __memory pKeyProcedure, __integer iKeyProcSize, \
	__memory pInstructions, __integer iInstructionSize, PPOWER_PROTECTER_ENCRYPT_PROCEDURE pPowerProtecterEncryptProcedure) {
	__dword dwKeyX = 0;
	__dword dwKeyY = 0;
	__dword dwKeyZ = 0;
	__memory pKeyProcedureRecord = NULL;

	// 获取密钥函数记录结构地址
	pKeyProcedureRecord = (__memory)&(pPowerProtecterEncryptProcedure->KeyProcedure);

	/*
	 * 产生密钥X,Y
	 * 使用被保护函数明文产生密钥X
	 * 使用密钥函数的明文产生密钥Y
	 */
	dwKeyX = crc32(pProcedure, iProcSize);
	dwKeyY = crc32(pKeyProcedure, iKeyProcSize);

	/*
	 * 加密指令结构
	 * 使用被保护函数的明文作为密钥的算子加密指令结构
	 * 要解密完被保护函数后才可以使用它的明文解密出指令结构
	 */
	XorArray(dwKeyX, pInstructions, pInstructions, iInstructionSize);

	/*
	 * 加密函数体
	 * 使用密钥函数作为算子加密被保护函数
	 */
	XorArray(dwKeyY, pProcedure, pProcedure, iProcSize);

	/*
	 * 产生密钥Z
	 * 使用被保护函数的密文产生密钥Z
	 */
	dwKeyZ = crc32(pProcedure, iProcSize);

	/*
	 * 加密记录结构
	 */
	XorArray(dwKeyZ, pKeyProcedureRecord, pKeyProcedureRecord, sizeof(POWER_PROTECTER_WATCH_RECORD));
	//XorArray(dwKeyZ, (__memory)&(pPowerProtecterEncryptProcedure->ofProcRVA), (__memory)&(pPowerProtecterEncryptProcedure->ofProcRVA), sizeof(__offset));

	return;
}

/*
 * 参数:
 *	iIndex:当前函数的索引
 *	pMem:被保护目标程序的文件映射指针
 *	pProcedure:被保护函数的记录结构
 *	pKeyProcedure:密钥函数的记录结构
 *	pInstructions:被保护指令的记录结构
 *	iEncryptInstCount:被保护指令的计数
 *	pEncryptProcedure:加密函数
 *
 * 介绍:
 *	保护当前指定的函数,失败返回NULL,成功返回下一个加密函数结构
 */
PPOWER_PROTECTER_ENCRYPT_PROCEDURE __INTERNAL_FUNC__ PowerProtectThisProcedure(__integer iIndex, __memory pMem, PPOWER_PROTECTER_PROCEDURE_RECORD pProcedure, \
	PPOWER_PROTECTER_WATCH_RECORD pKeyProcedure, PPOWER_PROTECTER_INSTRUCTION pInstructions, __integer iEncryptInstCount, \
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure) {
	
	__memory pProcedureFileAddress = NULL;
	__offset ofProcMemRVA = 0;
	__memory pKeyProcedureFileAddress = NULL;
	__offset ofKeyProcMemRVA = 0;
	__memory pEncryptProcedureBuffer = NULL;
	PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pEncryptInstructions = NULL;
	__integer iProcSize = 0;
	__integer iKeyProcSize = 0;
	__integer iTotalSize = 0;
	__integer iFlowInstCount = 0;

	pProcedureFileAddress = pProcedure->pFileAddress;
	ofProcMemRVA = pProcedure->ofMemRVA;
	pKeyProcedureFileAddress = pKeyProcedure->pFileAddress;
	ofKeyProcMemRVA = pKeyProcedure->ofMemRVA;
	iProcSize = pProcedure->iSize;
	iKeyProcSize = pKeyProcedure->iSize;

	// 得到对应的结构地址
	pEncryptProcedureBuffer = (__memory)pEncryptProcedure + sizeof(POWER_PROTECTER_ENCRYPT_PROCEDURE);
	pEncryptInstructions = (PPOWER_PROTECTER_ENCRYPT_INSTRUCTION)(pEncryptProcedureBuffer + iProcSize);

	// 力量保护这个函数
	iFlowInstCount = 0;
	iFlowInstCount = PowerProtectProcedure(pMem, pProcedureFileAddress, ofProcMemRVA, iProcSize, pInstructions, iEncryptInstCount, pEncryptInstructions, pEncryptProcedure);
	iEncryptInstCount += iFlowInstCount;//附加上流程指令

	// 复制保护后的结果
	__logic_memcpy__(pEncryptProcedureBuffer, pProcedureFileAddress, iProcSize);

	// 设置花指令
	if (g_PowerProtecterAttachConfigure.pGenPowerProtecterInvokeThunkCode) {
		__memory pInvokeThunkCode = NULL;
		FPGenPowerProtecterInvokeThunkCode pGenInvokeThunkCode = g_PowerProtecterAttachConfigure.pGenPowerProtecterInvokeThunkCode;
		pInvokeThunkCode = pGenInvokeThunkCode(iProcSize);
		if (!pInvokeThunkCode) {
			// 分配空间失败
		}
		__logic_memcpy__(pProcedureFileAddress, pInvokeThunkCode, iProcSize);
		if (pInvokeThunkCode) __logic_delete__(pInvokeThunkCode);
	} else {
		__logic_memset__(pProcedureFileAddress, 0x90, iProcSize);
	}

	// 填充加密函数结构
	pEncryptProcedure->iProcSize = iProcSize;
	pEncryptProcedure->KeyProcedure.ofMemRVA = pKeyProcedure->ofMemRVA;
	pEncryptProcedure->KeyProcedure.iSize = pKeyProcedure->iSize;
	pEncryptProcedure->iEncryptInstCount = iEncryptInstCount;
	pEncryptProcedure->bInit = FALSE;
	__logic_memset__(&(pEncryptProcedure->LocalCriticalSection), 0, sizeof(CRITICAL_SECTION));
	pEncryptProcedure->iHandleCount = 0;
	pEncryptProcedure->pRunSpace = NULL;
	iTotalSize = sizeof(POWER_PROTECTER_ENCRYPT_PROCEDURE) + iProcSize + sizeof(POWER_PROTECTER_ENCRYPT_INSTRUCTION) * iEncryptInstCount;
	iTotalSize = Alig(iTotalSize, __POWER_PROTECT_ENCRYPT_PROCEDURE_ALIGN__, TRUE);//总长度
	pEncryptProcedure->iTotalSize = iTotalSize;
	pEncryptProcedure->ofProcRVA = pProcedure->ofMemRVA;

	// 加密函数与部分结构
	PowerProtecterEncryptProcedure(pEncryptProcedureBuffer, iProcSize, pKeyProcedureFileAddress, iKeyProcSize, (__memory)pEncryptInstructions, iEncryptInstCount * sizeof(POWER_PROTECTER_ENCRYPT_INSTRUCTION), pEncryptProcedure);

	// 返回下一个函数的加密结构指针
	return (PPOWER_PROTECTER_ENCRYPT_PROCEDURE)((__memory)pEncryptProcedure + pEncryptProcedure->iTotalSize);
}

/*
 *
 * 参数:
 *	pMem:被保护程序映射的内存指针
 *	pRecord:记录了要保护的信息
 *
 * 介绍:
 *	核算所有加密函数结构的长度
 */
__integer __API__ PowerProtecterAthCountAllEncryptProceduresSize(__memory pMem, PPOWER_PROTECTER_PROCEDURE pRecord) {
	__integer iTotalSize = 0;
	__integer i = 0;
	__integer iCount = 0;
	__integer iEncryptInstSize = 0;
	__integer iSize = 0;
	__address addrImageBase = 0;
	__integer iFlowCount = 0;
	ud_t ud_obj = {0};

	addrImageBase = GetNtHeader(pMem)->OptionalHeader.ImageBase;
	iCount = pRecord->iCount;

	for (i = 0; i < iCount; i++) {
		__memory pProcFileAddress = NULL;
		__integer iProcSize = 0;
		__address addrProcMemAddress = 0;

		addrProcMemAddress = pRecord->Procedure[i].addrMemAddress;
		pProcFileAddress = pMem + Rva2Raw(pMem, addrProcMemAddress - addrImageBase);
		iProcSize = pRecord->Procedure[i].iSize;

		// 这里分析这个函数的流程指令计数
		ud_init(&ud_obj);
		ud_set_input_buffer(&ud_obj, pProcFileAddress, iProcSize);
		ud_set_mode(&ud_obj, 32);
		ud_set_syntax(&ud_obj, UD_SYN_INTEL);
		while (ud_disassemble(&ud_obj)) {
			POWER_PROTECTER_FLOW_TYPE Type = PPFT_NONE;
			Type = IsFlowInstructionByOffset(&ud_obj);
			if (Type != PPFT_NONE)
				iFlowCount++;
		}

		// 计算最终所需的数据
		iEncryptInstSize = (iFlowCount + pRecord->iInstructionCount[i]) * sizeof(POWER_PROTECTER_ENCRYPT_INSTRUCTION);//计算加密指令总长度
		// 加密后函数的长度 + 函数加密结构长度 + 解密指令结构总长度
		iSize = pRecord->Procedure[i].iSize + sizeof(POWER_PROTECTER_ENCRYPT_PROCEDURE) + iEncryptInstSize;
		iSize = Alig(iSize, __POWER_PROTECT_ENCRYPT_PROCEDURE_ALIGN__, TRUE);
		iTotalSize += iSize;
	}

	return iTotalSize;
}

/*
 * 参数:
 *	pMem:被保护目标程序的文件映射指针
 *	addrImageBase:映射的基地址
 *	pRecord:保护信息记录结构
 *
 * 介绍:
 *	设置被保护函数的文件地址
 */
__INLINE__ __void __INTERNAL_FUNC__ PowerProtecterSetFileAddress(__memory pMem, __address addrImageBase, PPOWER_PROTECTER_PROCEDURE pRecord) {
	__integer i = 0;
	__integer iCount = pRecord->iCount;

	// 设置每个函数文件地址指针
	for (i = 0; i < iCount; i++) {
		// 被保护函数
		pRecord->Procedure[i].ofMemRVA = pRecord->Procedure[i].addrMemAddress - addrImageBase;
		pRecord->Procedure[i].pFileAddress = pMem + Rva2Raw(pMem, pRecord->Procedure[i].ofMemRVA);

		// 密钥函数
		pRecord->KeyProcedure[i].ofMemRVA = pRecord->KeyProcedure[i].addrMemAddress - addrImageBase;
		pRecord->KeyProcedure[i].pFileAddress = pMem + Rva2Raw(pMem, pRecord->KeyProcedure[i].ofMemRVA);
	}
}

/*
 * 参数:
 *	pMem:被保护目标程序的文件映射指针
 *	addrImageBase:映射的基地址
 *	pRecord:保护信息记录结构
 *	pEncryptProcedures:加密函数结构的指针
 *
 * 介绍:
 *	按下确定按钮,保护选定的函数
 */
__void __API__ PowerProtectAthGo(__memory pMem, PPOWER_PROTECTER_PROCEDURE pRecord, PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedures) {
	__integer i = 0;
	__integer iCount = 0;
	__integer iEncryptInstCount = 0;
	__address addrImageBase = 0;
	PPOWER_PROTECTER_INSTRUCTION pInstructions = NULL;
	PPOWER_PROTECTER_PROCEDURE_RECORD pProcedure = NULL;
	PPOWER_PROTECTER_WATCH_RECORD pKeyProcedure = NULL;
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pCurrEncryptProcedure = NULL;
	PIMAGE_NT_HEADERS pNtHdr = NULL;

	// 获取NT头
	pNtHdr = GetNtHeader(pMem);

	// 获取基地址
	addrImageBase = pNtHdr->OptionalHeader.ImageBase;

	// 记录的总数
	iCount = pRecord->iCount;

	// 设置每个函数文件地址指针
	PowerProtecterSetFileAddress(pMem, addrImageBase, pRecord);

	pCurrEncryptProcedure = pEncryptProcedures;//指向第一个加密函数结构
	for (i = 0; i < iCount; i++) {
		pProcedure = &(pRecord->Procedure[i]);
		pKeyProcedure = &(pRecord->KeyProcedure[i]);
		pInstructions = (PPOWER_PROTECTER_INSTRUCTION)&(pRecord->Instructions[i]);
		iEncryptInstCount = pRecord->iInstructionCount[i];
		pCurrEncryptProcedure = PowerProtectThisProcedure(i, pMem, pProcedure, pKeyProcedure, pInstructions, iEncryptInstCount, pCurrEncryptProcedure);
	}
}

/*
 * 参数:
 *	pRecord:要设置的参数结构
 *	addrProcedure:函数的内存地址
 *	iSize:函数的长度
 *	addrKeyProcedure:密钥函数的内存地址
 *	iKeySize:密钥函数的长度
 *	pInstruction:要加密指令的描述结构
 *	iInstCount:指令的计数
 *
 * 介绍:
 *	设置要保护的函数的详细描述
 */
__integer __API__ PowerProtectAthSelectProcedure(PPOWER_PROTECTER_PROCEDURE pRecord, __address addrProcedure, __integer iSize, __address addrKeyProcedure, __integer iKeySize, PPOWER_PROTECTER_INSTRUCTION pInstruction, __integer iInstCount) {
	__integer iCount = 0;
	iCount = pRecord->iCount;
	pRecord->Procedure[iCount].addrMemAddress = addrProcedure;
	pRecord->Procedure[iCount].iSize = iSize;
	pRecord->KeyProcedure[iCount].addrMemAddress = addrKeyProcedure;
	pRecord->KeyProcedure[iCount].iSize = iKeySize;
	if (iInstCount > __POWER_PROTECT_MAX_INSTRUCTION__)//不能超过最大保护数量
		iInstCount = __POWER_PROTECT_MAX_INSTRUCTION__;
	__logic_memcpy__((__memory)&(pRecord->Instructions[iCount]), (__memory)pInstruction, sizeof(POWER_PROTECTER_INSTRUCTION) * iInstCount);
	pRecord->iInstructionCount[iCount] = iInstCount;

	(pRecord->iCount)++;
	return pRecord->iCount;
}

/*
 * 参数:
 *	pConfigure:配置结构
 *
 * 介绍:
 *	设置配置参数
 */
__void __API__ PowerProtecterAthSetArguments(PPOWER_PROTECTER_ATTACH_CONFIGURE pConfigure) {
	__logic_memcpy__(&g_PowerProtecterAttachConfigure, pConfigure, sizeof(POWER_PROTECTER_ATTACH_CONFIGURE));
}
