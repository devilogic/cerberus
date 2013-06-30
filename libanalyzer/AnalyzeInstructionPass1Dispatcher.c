#define __SetConditionEFlag__(EFlag) pInstruction->ConditionEFlag[X86EFLAG_##EFlag] = TRUE;
#define __SetEffectEFlag__(EFlag) pInstruction->EffectEFlag[X86EFLAG_##EFlag] = TRUE;
#define __SetEffectRegister__(Register) pInstruction->EffectRegister[X86REG_##Register] = TRUE;
#define __SetEffectRegisterFromUDFormat__(Register)\
	switch ((Register)){\
		case UD_R_AL:case UD_R_AH:case UD_R_EAX:\
			pInstruction->EffectRegister[X86REG_EAX] = TRUE;\
		break;\
		case UD_R_CL:case UD_R_CH:case UD_R_ECX:\
			pInstruction->EffectRegister[X86REG_ECX] = TRUE;\
		break;\
		case UD_R_DL:case UD_R_DH:case UD_R_EDX:\
			pInstruction->EffectRegister[X86REG_EDX] = TRUE;\
		break;\
		case UD_R_BL:case UD_R_BH:case UD_R_EBX:\
			pInstruction->EffectRegister[X86REG_EBX] = TRUE;\
		break;\
		case UD_R_SP:case UD_R_ESP:\
			pInstruction->EffectRegister[X86REG_ESP] = TRUE;\
		break;\
		case UD_R_BP:case UD_R_EBP:\
			pInstruction->EffectRegister[X86REG_EBP] = TRUE;\
		break;\
		case UD_R_SI:case UD_R_ESI:\
			pInstruction->EffectRegister[X86REG_ESI] = TRUE;\
		break;\
		case UD_R_DI:case UD_R_EDI:\
			pInstruction->EffectRegister[X86REG_EDI] = TRUE;\
		break;\
	}

#define __SetReferenceData__(IsSet, IsMaybeCrash, Value)\
	__address __addrAddress__ = (__address)(Value);\
	__integer iValue = GetValueByAddressReference(pInstruction, __addrAddress__);\
	__memory __pMem__ = __GetProgramFromInstruction__(pInstruction)->pMem;\
	__address __ImageBase__ = __GetProgramFromInstruction__(pInstruction)->ImageBase;\
	pInstruction->bReferenceData = TRUE;\
	pInstruction->ReferenceData.bSet = (IsSet);\
	pInstruction->ReferenceData.bMaybeCrash = (IsMaybeCrash);\
	pInstruction->ReferenceData.addrMemoryAddress = __addrAddress__;\
	pInstruction->ReferenceData.pFileAddress = __pMem__ + AnalyzerRva2Raw(__pMem__, __addrAddress__ - __ImageBase__);

#define __JmpUpOffset__(Offset, InstLen) ((~(Offset) + 1) - (InstLen))
#define __JmpDownOffset__(Offset, InstLen) ((Offset) + (InstLen))

#define __CalculateFileAddressByRefAddressInJmp__(pFileBase, addrMemAddr, pFileAddr, ImageBase){\
	VALID_ADDR __ValidAddr__ = CheckValidAddress((pFileBase), (addrMemAddr), CHK_IN_SEC_MEM);\
	if (__IsValidAddressLevel__(__ValidAddr__, CHK_IN_SEC_MEM)){\
		__integer __iRva__ = (__integer)((addrMemAddr) - (ImageBase));\
		(pFileAddr) = pFileBase + AnalyzerRva2Raw((pFileBase), __iRva__);\
	} else if (__IsValidAddressLevel__(__ValidAddr__, CHK_IN_IMAGE_MEM)){\
		__integer __iRaw__ = (__integer)((addrMemAddr) - (ImageBase));\
		(pFileAddr) = (pFileBase) + __iRaw__;\
	} else (pFileAddr) = NULL;}

#define __SetJmpFileAddress__(pFileBase, addrMemAddr, pFileAddr, ImageBase) __CalculateFileAddressByRefAddressInJmp__((pFileBase), (addrMemAddr), (pFileAddr), (ImageBase))

// 8位
#define __JmpBit8Up__()\
	pInstructionJmp->JmpWay = JMP_WAY_UP;\
	bOffset = __JmpUpOffset__(bOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.bVal = bOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress - bOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase);\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;
	

#define __JmpBit8Down__()\
	pInstructionJmp->JmpWay = JMP_WAY_DOWN;\
	bOffset = __JmpDownOffset__(bOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.bVal = bOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress + bOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase);\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;

// 16位
#define __JmpBit16Up__()\
	pInstructionJmp->JmpWay = JMP_WAY_UP;\
	wOffset = __JmpUpOffset__(wOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.wVal = wOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress - wOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase)\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;

#define __JmpBit16Down__()\
	pInstructionJmp->JmpWay = JMP_WAY_DOWN;\
	wOffset = __JmpDownOffset__(wOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.wVal = wOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress + wOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase)\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;

// 32位
#define __JmpBit32Up__()\
	pInstructionJmp->JmpWay = JMP_WAY_UP;\
	dwOffset = __JmpUpOffset__(dwOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.dwVal = dwOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress - dwOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase)\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;

#define __JmpBit32Down__()\
	pInstructionJmp->JmpWay = JMP_WAY_DOWN;\
	dwOffset = __JmpDownOffset__(dwOffset, pud_obj->inp_ctr);\
	pInstructionJmp->Offset.dwVal = dwOffset;\
	pInstructionJmp->addrTargetMemoryAddress = (__address)(pInstruction->addrCurrMemoryAddress + dwOffset);\
	__SetJmpFileAddress__(pMem, pInstructionJmp->addrTargetMemoryAddress, pInstructionJmp->pTargetFileAddress, ImageBase);\
	if (!(pInstructionJmp->pTargetFileAddress)) pInstructionJmp->bTargetAddressIsInvalid = TRUE;

__INLINE__ __dword __INTERNAL_FUNC__ GetValueByAddressReference(PX86INSTRUCTION pInstruction, __address addrAddress) {
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
	__integer iSize = __GetProgramFromInstruction__(pInstruction)->iBinSize;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	__memory pFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(addrAddress - ImageBase));
	if ((pFileAddress >= pMem + iSize) || (pFileAddress < pMem))
		return 0;
	else
		return *(__dword *)pFileAddress;
}

__INLINE__ __void __INTERNAL_FUNC__ SetJcc(PX86INSTRUCTION pInstruction) {
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	ud_t *pud_obj = &(pInstruction->ud_obj);
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	pInstruction->bJmp = TRUE;
	pInstructionJmp->JmpType = JMP_TYPE_JCC_OFFSET;

	if (pud_obj->operand[0].size == 8) {//8位
		__byte bOffset = pud_obj->operand[0].lval.ubyte;
		pInstructionJmp->JmpBit = JMP_BIT8;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
		if (__IsNegative8__(bOffset)) {
			__JmpBit8Up__();
		} else {
			__JmpBit8Down__();
		}
	} else if (pud_obj->operand[0].size == 16) {//16位
		__word wOffset = pud_obj->operand[0].lval.uword;
		pInstructionJmp->JmpBit = JMP_BIT16;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 3;//prefix 0x0f opcode
		if (__IsNegative16__(wOffset)) {
			__JmpBit16Up__();
		} else {
			__JmpBit16Down__();
		}
	} else if (pud_obj->operand[0].size == 32) {//32位
		__dword dwOffset = pud_obj->operand[0].lval.udword;
		pInstructionJmp->JmpBit = JMP_BIT32;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 2;//0x0f opcode
		if (__IsNegative32__(dwOffset)) {
			__JmpBit32Up__();
		} else {
			__JmpBit32Down__();
		}
	}
}

/*
 * 指令处理
 */
__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_I3dnow(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaaa(PX86INSTRUCTION pInstruction)
{
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(CF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaad(PX86INSTRUCTION pInstruction)
{
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(PF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaam(PX86INSTRUCTION pInstruction)
{
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(PF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaas(PX86INSTRUCTION pInstruction)
{
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(CF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iadc(PX86INSTRUCTION pInstruction)
{
	__SetConditionEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(PF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iadd(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(PF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddsubpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iaddsubps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iand(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(PF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iandpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iandps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iandnpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iandnps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iarpl(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsxd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibound(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibsf(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibsr(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibswap(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibt(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if (pInstruction->ud_obj.operand[1].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibtc(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if (pInstruction->ud_obj.operand[1].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibtr(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if (pInstruction->ud_obj.operand[1].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ibts(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if (pInstruction->ud_obj.operand[1].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icall(PX86INSTRUCTION pInstruction) {
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	ud_t *pud_obj = &(pInstruction->ud_obj);
	pInstruction->bJmp = TRUE;

	if (pud_obj->operand[0].type == UD_OP_JIMM) {
		pInstructionJmp->JmpType = JMP_TYPE_CALL_OFFSET;
		if (pud_obj->operand[0].size == 16) {
			// 16位
			__word wOffset = pud_obj->operand[0].lval.uword;
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
			pInstruction->pHookSaveAddress = pCurrFileAddress + 2;//prefix opcode
			if (__IsNegative16__(wOffset)) {
				__JmpBit16Up__();
			} else {
				__JmpBit16Down__();
			}/* end else */
		} else {
			// 32位
			__dword dwOffset = pud_obj->operand[0].lval.udword;
			pInstructionJmp->JmpBit = JMP_BIT32;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
			pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
			if (__IsNegative32__(dwOffset)) {
				__JmpBit32Up__();
			} else {
				__JmpBit32Down__();	
			}
		}/* end else */
	} else if (pud_obj->operand[0].type == UD_OP_REG) {
		// call $reg
		if (pud_obj->pfx_opr == 0x66) {
			// 16位
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
			pInstruction->pHookSaveAddress = NULL;
		} else {
			// 32位
			// 进行反馈分析
			__address addrTargetMemoryAddress = 0;
			__memory pHookSaveFileAddress = NULL;
			__bool bIndirect = FALSE;
			PX86INSTRUCTION pPrevInstruction = pInstruction->pPrev;
			enum ud_type OpRegister = pInstruction->ud_obj.operand[0].base;
			MOVTYPE MovType = FeedbackAnalyzeInstruction(pPrevInstruction, OpRegister, &addrTargetMemoryAddress, &pHookSaveFileAddress, &bIndirect);
			if (MovType != MOV_NONE) {
				pInstructionJmp->JmpBit = JMP_BIT32;
				if ((MovType == MOV_REG_IMM) || (MovType == LEA_REG_MEM))
					pInstructionJmp->JmpType = JMP_TYPE_CALL_MOV_ADDR_REG;
				else
					pInstructionJmp->JmpType = JMP_TYPE_CALL_MOV_MEM_REG;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
				pInstruction->pHookSaveAddress = pHookSaveFileAddress;
				pInstructionJmp->addrTargetMemoryAddress = addrTargetMemoryAddress;
				pInstructionJmp->bIndirectJmp = bIndirect;
				pInstructionJmp->pTargetFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(addrTargetMemoryAddress - ImageBase));
				if (pInstructionJmp->JmpType == JMP_TYPE_CALL_MOV_ADDR_REG) {
					if (addrTargetMemoryAddress >= pInstruction->addrCurrMemoryAddress)
						pInstructionJmp->JmpWay = JMP_WAY_DOWN;
					else
						pInstructionJmp->JmpWay = JMP_WAY_UP;
				} else
					pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
			} else {
				// 不能进行HOOK
				pInstructionJmp->JmpBit = JMP_BIT32;
				pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
				pInstruction->pHookSaveAddress = NULL;
			}
		}
	} else if (pud_obj->operand[0].type == UD_OP_MEM) {
		// call dword ptr [address]
		// call dword ptr [$reg]
		pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
		if (pud_obj->pfx_adr == 0x67) {
			// 16位
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
			pInstruction->pHookSaveAddress = NULL;
		} else {
			// 32
			// call dword ptr [address]
			if ((pInstruction->ud_obj.operand[0].base == UD_NONE) && (pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
				__dword dwImm = pInstruction->ud_obj.operand[0].lval.udword;
				__SetReferenceData__(FALSE, FALSE, dwImm);
				pInstructionJmp->JmpBit = JMP_BIT32;
				pInstructionJmp->JmpType = JMP_TYPE_CALL_IMEM;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
				pInstruction->pHookSaveAddress = pInstruction->pCurrFileAddress + 2;//opcode modrm
				pInstructionJmp->bIndirectJmp = TRUE;
				pInstructionJmp->addrIndirectMemoryAddress = (__address)dwImm;
				pInstructionJmp->pIndirectFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(dwImm - ImageBase));
			} else if ((pInstruction->ud_obj.operand[0].base != UD_NONE) && (pInstruction->ud_obj.operand[0].index == UD_NONE) && \
				(!(pInstruction->ud_obj.operand[0].offset))) {
				// call dword ptr [$reg]
				// 进行反馈分析
				__address addrTargetMemoryAddress = 0;
				__memory pHookSaveFileAddress = NULL;
				__bool bIndirect = FALSE;
				PX86INSTRUCTION pPrevInstruction = pInstruction->pPrev;
				enum ud_type OpRegister = pInstruction->ud_obj.operand[0].base;
				MOVTYPE MovType = FeedbackAnalyzeInstruction(pPrevInstruction, OpRegister, &addrTargetMemoryAddress, &pHookSaveFileAddress, &bIndirect);
				if (MovType != MOV_NONE) {
					pInstructionJmp->JmpBit = JMP_BIT32;
					if ((MovType == MOV_REG_IMM) || (MovType == LEA_REG_MEM))
						pInstructionJmp->JmpType = JMP_TYPE_CALL_MOV_ADDR_MREG;
					else
						pInstructionJmp->JmpType = JMP_TYPE_CALL_MOV_MEM_MREG;
					pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
					pInstruction->pHookSaveAddress = pHookSaveFileAddress;
					pInstructionJmp->bIndirectJmp = bIndirect;
					pInstructionJmp->addrTargetMemoryAddress = addrTargetMemoryAddress;
					pInstructionJmp->pTargetFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(addrTargetMemoryAddress - ImageBase));
				} else {
					// 不能进行HOOK
					pInstructionJmp->JmpBit = JMP_BIT32;
					pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
					pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
					pInstruction->pHookSaveAddress = NULL;
				}
			}
		}
	} else if (pud_obj->operand[0].type == UD_OP_PTR) {
		if (pud_obj->pfx_adr == 0x67)
			pInstructionJmp->JmpBit = JMP_BIT16;
		else
			pInstructionJmp->JmpBit = JMP_BIT32;
		pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
		pInstruction->pHookSaveAddress = NULL;
		pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icbw(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icwde(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icdqe(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iclc(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icld(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(DF);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iclflush(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iclgi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icli(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iclts(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmc(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovo(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovno(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovb(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovae(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovnz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovbe(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmova(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovs(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovns(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) &&
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovnp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovl(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovge(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovle(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmovg(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(OF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(AF);
	__SetConditionEFlag__(PF);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	} else if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmppd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpsb(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(ESI);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpsw(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(ESI);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpsd(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(ESI);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpsq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpxchg(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(OF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(AF);
	__SetConditionEFlag__(PF);
	__SetEffectEFlag__(ZF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if (pInstruction->ud_obj.operand[1].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icmpxchg8b(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icomisd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icomiss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icpuid(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtdq2pd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtdq2ps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtpd2dq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtpd2pi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtpd2ps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtpi2ps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtpi2pd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtps2dq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtps2pi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtps2pd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtsd2si(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtsd2ss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtsi2ss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtss2si(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtss2sd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttpd2pi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttpd2dq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttps2dq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttps2pi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttsd2si(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvtsi2sd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icvttss2si(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icwd(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icdq(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Icqo(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idaa(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(ZF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idas(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(ZF);
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idec(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idiv(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(EDX);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idivpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idivps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idivsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idivss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iemms(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ienter(PX86INSTRUCTION pInstruction) {
	PPROCEDURE pProcedure = __GetInstructionParents__(pInstruction);
	pProcedure->AllocStackType = ALLOC_BY_ENTER;
	pProcedure->addrAllocStackMemoryAddress = pInstruction->addrCurrMemoryAddress;
	pProcedure->pAllocStackFileAddress = pInstruction->pCurrFileAddress;
	pProcedure->iStackSize = (__integer)(pInstruction->ud_obj.operand[0].lval.uword);

	__SetEffectRegister__(ESP);
	__SetEffectRegister__(EBP);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_If2xm1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifabs(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifadd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifaddp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifbld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifbstp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifchs(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifclex(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmove(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovbe(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovu(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovnb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovne(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovnbe(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcmovnu(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifucomi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcom(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcom2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcomp3(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcomi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifucomip(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcomip(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcomp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcomp5(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcompp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifcos(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifdecstp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifdiv(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifdivp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifdivr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifdivrp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifemms(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iffree(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iffreep(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ificom(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ificomp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifild(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifncstp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifninit(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifiadd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifidivr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifidiv(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifisub(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifisubr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifist(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifistp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifisttp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifld1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldl2t(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldl2e(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldlpi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldlg2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldln2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldz(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldcw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifldenv(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifmul(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifmulp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifimul(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifnop(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifpatan(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifprem(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifprem1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifptan(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifrndint(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifrstor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifnsave(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifscale(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsin(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsincos(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsqrt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifstp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifstp1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifstp8(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifstp9(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifst(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifnstcw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifnstenv(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifnstsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsub(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsubp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsubr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifsubrp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iftst(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifucom(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifucomp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifucompp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxam(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxch(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxch4(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxch7(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxrstor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifxsave(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifpxtract(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifyl2x(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ifyl2xp1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ihaddpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ihaddps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ihlt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ihsubpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ihsubps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iidiv(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(EDX);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iin(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iimul(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinc(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(PF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinsb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iint1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iint3(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iint(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinto(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinvd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinvlpg(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinvlpga(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iiretw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iiretd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iiretq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijo(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijno(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijb(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijae(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijnz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijbe(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(CF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ija(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(CF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijs(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijns(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijnp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijl(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijge(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijle(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijg(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijcxz(PX86INSTRUCTION pInstruction) {
	// 受寄存器cx的影响
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijecxz(PX86INSTRUCTION pInstruction) {
	// 受寄存器ecx的影响
	SetJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijrcxz(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ijmp(PX86INSTRUCTION pInstruction) {
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	ud_t *pud_obj = &(pInstruction->ud_obj);
	pInstruction->bJmp = TRUE;

	if (pud_obj->operand[0].type == UD_OP_JIMM) {
		pInstructionJmp->JmpType = JMP_TYPE_JMP_OFFSET;
		if (pud_obj->operand[0].size == 8) {
			// 8位
			__byte bOffset = pud_obj->operand[0].lval.ubyte;
			pInstructionJmp->JmpBit = JMP_BIT8;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
			pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
			if (__IsNegative8__(bOffset)) {
				__JmpBit8Up__();
			} else {
				__JmpBit8Down__();
			}
		} else if (pud_obj->operand[0].size == 16) {
			// 16位
			__word wOffset = pud_obj->operand[0].lval.uword;
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
			pInstruction->pHookSaveAddress = pCurrFileAddress + 2;//prefix opcode
			if (__IsNegative16__(wOffset)) {
				__JmpBit16Up__();
			} else {
				__JmpBit16Down__();
			}/* end else */
		} else if (pud_obj->operand[0].size == 32) {
			// 32位
			__dword dwOffset = pud_obj->operand[0].lval.udword;
			pInstructionJmp->JmpBit = JMP_BIT32;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
			pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
			if (__IsNegative32__(dwOffset)) {
				__JmpBit32Up__();
			} else {
				__JmpBit32Down__();	
			}
		}/* end else */
	} else if (pud_obj->operand[0].type == UD_OP_REG) {
		// jmp $reg
		if (pud_obj->pfx_opr == 0x66) {
			// 16位
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
			pInstruction->pHookSaveAddress = NULL;
		} else {
			// 32位
			// 进行反馈分析
			__address addrTargetMemoryAddress = 0;
			__memory pHookSaveFileAddress = NULL;
			__bool bIndirect = FALSE;
			PX86INSTRUCTION pPrevInstruction = pInstruction->pPrev;
			enum ud_type OpRegister = pInstruction->ud_obj.operand[0].base;
			MOVTYPE MovType = FeedbackAnalyzeInstruction(pPrevInstruction, OpRegister, &addrTargetMemoryAddress, &pHookSaveFileAddress, &bIndirect);
			if (MovType != MOV_NONE) {
				pInstructionJmp->JmpBit = JMP_BIT32;
				if ((MovType == MOV_REG_IMM) || (MovType == LEA_REG_MEM))
					pInstructionJmp->JmpType = JMP_TYPE_JMP_MOV_ADDR_REG;
				else
					pInstructionJmp->JmpType = JMP_TYPE_JMP_MOV_MEM_REG;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
				pInstruction->pHookSaveAddress = pHookSaveFileAddress;
				pInstructionJmp->addrTargetMemoryAddress = addrTargetMemoryAddress;
				pInstructionJmp->bIndirectJmp = bIndirect;
				pInstructionJmp->pTargetFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(addrTargetMemoryAddress - ImageBase));
				if (pInstructionJmp->JmpType == JMP_TYPE_JMP_MOV_ADDR_REG) {
					if (addrTargetMemoryAddress >= pInstruction->addrCurrMemoryAddress)
						pInstructionJmp->JmpWay = JMP_WAY_DOWN;
					else
						pInstructionJmp->JmpWay = JMP_WAY_UP;
				} else
					pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
			} else {
				// 不能进行HOOK
				pInstructionJmp->JmpBit = JMP_BIT32;
				pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
				pInstruction->pHookSaveAddress = NULL;
			}
		}
	} else if (pud_obj->operand[0].type == UD_OP_MEM) {
		// jmp dword ptr [address]
		// jmp dword ptr [$reg]
		pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
		if (pud_obj->pfx_adr == 0x67) {
			// 16位
			pInstructionJmp->JmpBit = JMP_BIT16;
			pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
			pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
			pInstruction->pHookSaveAddress = NULL;
		} else {
			// 32
			// jmp dword ptr [address]
			if ((pInstruction->ud_obj.operand[0].base == UD_NONE) && (pInstruction->ud_obj.operand[0].index == UD_NONE) && \
				(pInstruction->ud_obj.operand[0].offset)) {
				__dword dwImm = pInstruction->ud_obj.operand[0].lval.udword;
				__SetReferenceData__(FALSE, FALSE, dwImm);
				pInstructionJmp->JmpBit = JMP_BIT32;
				pInstructionJmp->JmpType = JMP_TYPE_JMP_IMEM;
				pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
				pInstruction->pHookSaveAddress = pInstruction->pCurrFileAddress + 2;//opcode modrm
				pInstructionJmp->bIndirectJmp = TRUE;
				pInstructionJmp->addrIndirectMemoryAddress = (__address)dwImm;
				pInstructionJmp->pIndirectFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(dwImm - ImageBase));
			} else if ((pInstruction->ud_obj.operand[0].base != UD_NONE) && (pInstruction->ud_obj.operand[0].index == UD_NONE) && \
				(!(pInstruction->ud_obj.operand[0].offset))) {
				// jmp dword ptr [$reg]
				// 进行反馈分析
				__address addrTargetMemoryAddress = 0;
				__memory pHookSaveFileAddress = NULL;
				__bool bIndirect = FALSE;
				PX86INSTRUCTION pPrevInstruction = pInstruction->pPrev;
				enum ud_type OpRegister = pInstruction->ud_obj.operand[0].base;
				MOVTYPE MovType = FeedbackAnalyzeInstruction(pPrevInstruction, OpRegister, &addrTargetMemoryAddress, &pHookSaveFileAddress, &bIndirect);
				if (MovType != MOV_NONE) {
					pInstructionJmp->JmpBit = JMP_BIT32;
					if ((MovType == MOV_REG_IMM) || (MovType == LEA_REG_MEM))
						pInstructionJmp->JmpType = JMP_TYPE_JMP_MOV_ADDR_MREG;
					else
						pInstructionJmp->JmpType = JMP_TYPE_JMP_MOV_MEM_MREG;
					pInstruction->HookSuccessLevel = HOOK_LEVEL_OK;
					pInstruction->pHookSaveAddress = pHookSaveFileAddress;
					pInstructionJmp->bIndirectJmp = bIndirect;
					pInstructionJmp->addrTargetMemoryAddress = addrTargetMemoryAddress;
					pInstructionJmp->pTargetFileAddress = pMem + AnalyzerRva2Raw(pMem, (__integer)(addrTargetMemoryAddress - ImageBase));
				} else {
					// 不能进行HOOK
					pInstructionJmp->JmpBit = JMP_BIT32;
					pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
					pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
					pInstruction->pHookSaveAddress = NULL;
				}
			}
		}
	} else if (pud_obj->operand[0].type == UD_OP_PTR) {
		if (pud_obj->pfx_adr == 0x67)
			pInstructionJmp->JmpBit = JMP_BIT16;
		else
			pInstructionJmp->JmpBit = JMP_BIT32;
		pInstructionJmp->JmpType = JMP_TYPE_NOT_FIX;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_NOT;
		pInstruction->pHookSaveAddress = NULL;
		pInstructionJmp->JmpWay = JMP_WAY_UNKNOW;
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilahf(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilar(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(ZF);
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilddqu(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ildmxcsr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilds(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilea(PX86INSTRUCTION pInstruction) {
	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iles(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilfs(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilgs(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilidt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ileave(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(ESP);
	__SetEffectRegister__(EBP);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilfence(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilgdt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Illdt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilmsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilock(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilodsb(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(ESI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilodsw(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(ESI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilodsd(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(ESI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilodsq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iloopnz(PX86INSTRUCTION pInstruction) {
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	ud_t *pud_obj = &(pInstruction->ud_obj);
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;

	__SetConditionEFlag__(ZF);
	pInstructionJmp->JmpType = JMP_TYPE_JCC_OFFSET;
	// 8位
	if (pud_obj->operand[0].offset == 8) {
		__byte bOffset = pud_obj->operand[0].lval.ubyte;
		pInstructionJmp->JmpBit = JMP_BIT8;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
		if (bOffset >= 0x80) {
			__JmpBit8Up__();
		} else {
			__JmpBit8Down__();
		}
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iloope(PX86INSTRUCTION pInstruction) {
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	ud_t *pud_obj = &(pInstruction->ud_obj);
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;

	__SetConditionEFlag__(ZF);
	pInstructionJmp->JmpType = JMP_TYPE_JCC_OFFSET;
	// 8位
	if (pud_obj->operand[0].offset == 8) {
		__byte bOffset = pud_obj->operand[0].lval.ubyte;
		pInstructionJmp->JmpBit = JMP_BIT8;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
		if (bOffset >= 0x80) {
			__JmpBit8Up__();
		} else {
			__JmpBit8Down__();
		}
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iloop(PX86INSTRUCTION pInstruction) {
	// 根据ECX的值
	PINSTRUCTION_JMP pInstructionJmp = &(pInstruction->InstructionJmp);
	ud_t *pud_obj = &(pInstruction->ud_obj);
	__memory pCurrFileAddress = pInstruction->pCurrFileAddress;
	__address addrCurrentMemoryAddress = pInstruction->addrCurrMemoryAddress;
	__address ImageBase = __GetProgramFromInstruction__(pInstruction)->ImageBase;
	__memory pMem = __GetProgramFromInstruction__(pInstruction)->pMem;

	pInstructionJmp->JmpType = JMP_TYPE_JCC_OFFSET;
	// 8位
	if (pud_obj->operand[0].offset == 8) {
		__byte bOffset = pud_obj->operand[0].lval.ubyte;
		pInstructionJmp->JmpBit = JMP_BIT8;
		pInstruction->HookSuccessLevel = HOOK_LEVEL_MAYBE;
		pInstruction->pHookSaveAddress = pCurrFileAddress + 1;//opcode
		if (bOffset >= 0x80) {
			__JmpBit8Up__();
		} else {
			__JmpBit8Down__();
		}
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ilsl(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iltr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imaskmovq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imaxpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imaxps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imaxsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imaxss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imfence(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iminpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iminps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iminsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iminss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imonitor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imov(PX86INSTRUCTION pInstruction) {
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	}
	else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovapd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovaps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovddup(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovdqa(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovdqu(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovdq2q(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovhpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovhps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovlhps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovlpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovlps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovhlps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovmskpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovmskps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovntdq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovnti(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovntpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovntps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovntq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovqa(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovq2dq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsb(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsw(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsd(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsldup(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovshdup(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovsx(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovupd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovups(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imovzx(PX86INSTRUCTION pInstruction) {
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imul(PX86INSTRUCTION pInstruction)
{
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectRegister__(EAX);
	__SetEffectRegister__(EDX);
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imulpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imulps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imulsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imulss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Imwait(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ineg(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(AF);
	__SetEffectEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Inop(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Inot(PX86INSTRUCTION pInstruction) {
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ior(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iorpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iorps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iout(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ioutsb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ioutsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ioutsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ioutsq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipacksswb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipackssdw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipackuswb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddsb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddusb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipaddusw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipand(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipandn(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipause(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipavgb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipavgw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpeqb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpeqw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpeqd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpgtb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpgtw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipcmpgtd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipextrw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipinsrw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmaddwd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmaxsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmaxub(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipminsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipminub(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmovmskb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmulhuw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmulhw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmullw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmuludq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipop(PX86INSTRUCTION pInstruction) {
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipopa(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipopad(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipopfw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipopfd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipopfq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iprefetch(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iprefetchnta(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iprefetcht0(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iprefetcht1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iprefetcht2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsadbw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipshufd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipshufhw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipshuflw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipshufw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipslldq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsllw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipslld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsllq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsraw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsrad(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsrlw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsrld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsrlq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsrldq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubsb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubusb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipsubusw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpckhbw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpckhwd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpckhdq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpckhqdq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpcklbw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpcklwd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpckldq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipunpcklqdq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipi2fw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipi2fd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipf2iw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipf2id(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfnacc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfpnacc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfcmpge(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfmin(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfrcp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfrsqrt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfsub(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfadd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfcmpgt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfmax(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfrcpit1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfrspit1(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfsubr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfacc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfcmpeq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfmul(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipfrcpit2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipmulhrw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipswapd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipavgusb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipush(PX86INSTRUCTION pInstruction) {
	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipusha(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipushad(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipushfw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipushfd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipushfq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ipxor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ircl(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ircr(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irol(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iror(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ircpps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ircpss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irdmsr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irdpmc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irdtsc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irdtscp(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irepne(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irep(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iret(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(ESP);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iretf(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irsm(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irsqrtps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Irsqrtss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isahf(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isal(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isalc(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isar(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishl(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishr(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isbb(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(AF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	else if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iscasb(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(AF);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iscasw(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(AF);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iscasd(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(AF);
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iscasq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iseto(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetno(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetb(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetnb(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetnz(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetbe(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iseta(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(CF);
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isets(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetns(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetnp(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(PF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetl(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetge(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetle(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isetg(PX86INSTRUCTION pInstruction) {
	__SetConditionEFlag__(SF);
	__SetConditionEFlag__(OF);
	__SetConditionEFlag__(ZF);
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
			(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isfence(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isgdt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishrd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishufpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ishufps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isidt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isldt(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ismsw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isqrtps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isqrtpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isqrtsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isqrtss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istc(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istd(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(DF);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istgi(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isti(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iskinit(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istmxcsr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istosb(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istosw(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istosd(PX86INSTRUCTION pInstruction) {
	__SetEffectRegister__(EDI);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istosq(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Istr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isub(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(AF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
		// 记录堆栈
		if (pInstruction->ud_obj.operand[0].base == UD_R_ESP) {
			PPROCEDURE pProcedure = __GetInstructionParents__(pInstruction);
			pProcedure->AllocStackType = ALLOC_BY_SUB_ESP;
			pProcedure->addrAllocStackMemoryAddress = pInstruction->addrCurrMemoryAddress;
			pProcedure->pAllocStackFileAddress = pInstruction->pCurrFileAddress;
			if (pInstruction->ud_obj.operand[1].type == UD_OP_IMM)
				pProcedure->iStackSize = (__integer)(pInstruction->ud_obj.operand[1].lval.udword);
			else
				pProcedure->iStackSize = __INVALID_ALLOC_STACK_SIZE__;
		}
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isubpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isubps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isubsd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isubss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iswapgs(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isyscall(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isysenter(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isysexit(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Isysret(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Itest(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);

	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(FALSE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iucomisd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iucomiss(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iud2(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iunpckhpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iunpckhps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iunpcklps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iunpcklpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iverr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iverw(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmcall(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmclear(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmxon(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmptrld(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmptrst(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmresume(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmxoff(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmrun(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmmcall(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmload(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ivmsave(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iwait(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iwbinvd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iwrmsr(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixadd(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);
	__SetEffectEFlag__(AF);

	if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[1].base);
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixchg(PX86INSTRUCTION pInstruction) {
	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixlatb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixor(PX86INSTRUCTION pInstruction) {
	__SetEffectEFlag__(CF);
	__SetEffectEFlag__(OF);
	__SetEffectEFlag__(ZF);
	__SetEffectEFlag__(SF);
	__SetEffectEFlag__(PF);

	if (pInstruction->ud_obj.operand[0].type == UD_OP_REG) {
		__SetEffectRegisterFromUDFormat__(pInstruction->ud_obj.operand[0].base);
	} else if ((pInstruction->ud_obj.operand[0].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[0].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[0].index == UD_NONE) && (pInstruction->ud_obj.operand[0].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[0].lval.udword);
	}

	if ((pInstruction->ud_obj.operand[1].type == UD_OP_MEM) && (pInstruction->ud_obj.operand[1].base == UD_NONE) && \
		(pInstruction->ud_obj.operand[1].index == UD_NONE) && (pInstruction->ud_obj.operand[1].offset)) {
		__SetReferenceData__(TRUE, FALSE, pInstruction->ud_obj.operand[1].lval.udword);
	}
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixorpd(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ixorps(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Idb(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Iinvalid(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Id3vil(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Ina(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_reg(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_rm(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_vendor(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_x87(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_mode(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_osize(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_asize(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Igrp_mod(PX86INSTRUCTION pInstruction)
{
}

__void __INTERNAL_FUNC__ AnalyzeInstructionPass1Dispatcher_Inone(PX86INSTRUCTION pInstruction)
{
}
