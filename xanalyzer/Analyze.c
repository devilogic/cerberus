#include "Analyze.h"
#include "Support.h"

// 产生流程图路径
__bool g_bGenProcedureFlowChart;

__bool __INTERNAL_FUNC__ FillAnalyzeBasicInfo(PXFILE_ATTACH_INFO pTarget, PANALYZE_BASIC_INFO pAnalyzeBasicInfo) {
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_SECTION_HEADER pCodeSecHdr = NULL;

	// 获取节头信息
	pNtHdr = GetNtHeader(pTarget->pMem);
	pCodeSecHdr = GetEntryPointSection(pTarget->pMem);

	// 填充基本信息结构
	pAnalyzeBasicInfo->pMem = pTarget->pMem;
	pAnalyzeBasicInfo->pCodeSeg = pTarget->pMem + pCodeSecHdr->PointerToRawData;
	pAnalyzeBasicInfo->pTailData = pTarget->pTailData;

	pAnalyzeBasicInfo->ImageBase = pNtHdr->OptionalHeader.ImageBase;
	pAnalyzeBasicInfo->addrCodeSegMemoryAddress = pNtHdr->OptionalHeader.ImageBase + pCodeSecHdr->VirtualAddress;

	pAnalyzeBasicInfo->iBinSize = pTarget->iOrigFileSize;
	pAnalyzeBasicInfo->iCodeSegSize = pCodeSecHdr->SizeOfRawData;
	pAnalyzeBasicInfo->iTailDataSize = pTarget->iTailDataSize;
	pAnalyzeBasicInfo->iEntryRva = pNtHdr->OptionalHeader.AddressOfEntryPoint;
	if (pAnalyzeBasicInfo->iEntryRva == 0)
		return FALSE;

	pAnalyzeBasicInfo->pRaw2Rva = (FPRaw2Rva)Raw2Rva;
	pAnalyzeBasicInfo->pRva2Raw = (FPRva2Raw)Rva2Raw;
	pAnalyzeBasicInfo->pGetCodeSectionHeader = (FPGetCodeSectionHeader)GetEntryPointSection;
	pAnalyzeBasicInfo->pGetNtHeader = (FPGetNtHeader)GetNtHeader;

	return TRUE;
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_AllocStackType(FILE *fp, ALLOC_STACK_TYPE AllocStackType) {
	if (AllocStackType == ALLOC_BY_NOT) {
		fprintf(fp, "<AllocStackType>ALLOC_BY_NOT</AllocStackType>\n");
	} else if (AllocStackType == ALLOC_BY_ENTER) {
		fprintf(fp, "<AllocStackType>ALLOC_BY_ENTER</AllocStackType>\n");
	} else if (AllocStackType == ALLOC_BY_SUB_ESP) {
		fprintf(fp, "<AllocStackType>ALLOC_BY_SUB_ESP</AllocStackType>\n");
	} else {
		//
	}
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_Disasm(FILE *fp, __address addrProcedureMemoryAddress, __memory pProcedureFileAddress, __integer iProcSize) {
	ud_t ud_obj = {0};
	__offset ofOffset = 0;
	__address addrCurrMemoryAddress = 0;

	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, pProcedureFileAddress, iProcSize);
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	fprintf(fp, "<Assemble>\n");

	addrCurrMemoryAddress = addrProcedureMemoryAddress;
	while (ud_disassemble(&ud_obj)) {

		fprintf(fp, "<x%X>%s|%s</x%X>\n", addrCurrMemoryAddress, ud_obj.insn_hexcode, ud_obj.insn_buffer, addrCurrMemoryAddress);

		ofOffset += ud_obj.inp_ctr;
		addrCurrMemoryAddress += ofOffset;
	}
	fprintf(fp, "</Assemble>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_Hexcode(FILE *fp, __memory pProcedureFileAddress, __integer iProcSize) {
	__offset ofOffset = 0;
	__byte bByte = 0;
	__integer iCount = 0, iLine = 0, i = 0;

	iLine = iProcSize / 16 + (iProcSize % 16 ? 1 : 0);

	fprintf(fp, "<HexCode>\n");

	while (1) {
		// 判断末尾
		if ((iCount != 0) && (iCount % 0x10 == 0) || (iCount >= iProcSize)) {
			fprintf(fp, "</x%X>\n", ofOffset);

			// 是否是末尾
			if (iCount >= iProcSize)
				break;

			ofOffset += 0x10;
		}

		if ((iCount == 0) || ((iCount != 0) && (iCount % 0x10 == 0)))
			fprintf(fp, "<x%X>", ofOffset);

		// 获取字节
		bByte = *((__byte *)pProcedureFileAddress + iCount);
		if (bByte == 0)
			fprintf(fp, "00 ");
		else if (bByte < 0x0F)
			fprintf(fp, "0%X ", bByte);
		else
			fprintf(fp, "%2X ", bByte);

		iCount++;
	}
	fprintf(fp, "</HexCode>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_ProcedureRefForm(FILE *fp, PPROCEDURE_REFFROM pProcedureRefForm) {
	PPROCEDURE_REFFROM pCurrProcedureRefForm = NULL;
	PPROGRAM pProgram = NULL;
	PPROCEDURE pProcedure = NULL;
	__integer i = 0;
	__memory pMem = NULL;

	if (!pProcedureRefForm)
		return;

	pCurrProcedureRefForm = pProcedureRefForm;
	fprintf(fp, "<ProcedureRefForm>\n");

	while (pCurrProcedureRefForm) {

		pProcedure = __GetProcedureRefFromHeader__(pCurrProcedureRefForm);
		pProgram = __GetProcedureParents__(pProcedure);
		pMem = pProgram->pMem;

		fprintf(fp, "<ProcRefForm Index=\"%d\">\n", i);
		fprintf(fp, "<addrMemoryStartAddress>0x%X</addrMemoryStartAddress>\n", pProcedure->addrMemoryStartAddress);
		fprintf(fp, "<ofFileStartOffset>0x%X</ofFileStartOffset>\n", pProcedure->pFileStartAddress - pMem);
		fprintf(fp, "</ProcRefForm>\n");

		pCurrProcedureRefForm = pCurrProcedureRefForm->pNext;
		i++;
	}

	fprintf(fp, "</ProcedureRefForm>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_JmpWay(FILE *fp, JMPWAY JmpWay) {
	if (JmpWay == JMP_WAY_UNKNOW)
		fprintf(fp, "<JmpWay>JMP_WAY_UNKNOW</JmpWay>\n");
	else if (JmpWay == JMP_WAY_UP)
		fprintf(fp, "<JmpWay>JMP_WAY_UP</JmpWay>\n");
	else if (JmpWay == JMP_WAY_DOWN)
		fprintf(fp, "<JmpWay>JMP_WAY_DOWN</JmpWay>\n");
	else
		fprintf(fp, "<JmpWay>JMP_WAY_UNKNOW</JmpWay>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_JmpBit(FILE *fp, JMPBIT JmpBit) {
	fprintf(fp, "<JmpBit>%d</JmpBit>\n", JmpBit);
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_JmpType(FILE *fp, JMPTYPE JmpType) {
	if (JmpType == JMP_TYPE_NOT_FIX)
		fprintf(fp, "<JmpWay>JMP_TYPE_NOT_FIX</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_OFFSET)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_OFFSET</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_OFFSET)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_OFFSET</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JCC_OFFSET)
		fprintf(fp, "<JmpWay>JMP_TYPE_JCC_OFFSET</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_IMEM)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_IMEM</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_MOV_ADDR_REG)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_MOV_ADDR_REG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_MOV_ADDR_MREG)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_MOV_ADDR_MREG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_MOV_MEM_REG)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_MOV_MEM_REG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_JMP_MOV_MEM_MREG)
		fprintf(fp, "<JmpWay>JMP_TYPE_JMP_MOV_MEM_MREG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_IMEM)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_IMEM</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_MOV_ADDR_REG)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_MOV_ADDR_REG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_MOV_ADDR_MREG)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_MOV_ADDR_MREG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_MOV_MEM_REG)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_MOV_MEM_REG</JmpWay>\n");
	else if (JmpType == JMP_TYPE_CALL_MOV_MEM_MREG)
		fprintf(fp, "<JmpWay>JMP_TYPE_CALL_MOV_MEM_MREG</JmpWay>\n");
	else {;}
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_InstructionJmp(FILE *fp, PINSTRUCTION_JMP pInstructionJmp) {
	__memory pMem = NULL;
	PX86INSTRUCTION pInstruction = NULL;
	PPROCEDURE pProcedure = NULL;
	PPROGRAM pProgram = NULL;

	if (!pInstructionJmp)
		return;

	pInstruction = __GetInstructionJmpParents__(pInstructionJmp);
	pProcedure = __GetInstructionParents__(pInstruction);
	pProgram = __GetProcedureParents__(pProcedure);
	pMem = pProgram->pMem;

	fprintf(fp, "<InstructionJmp bTargetAddressIsInvalid=\"%d\" bJmpOut=\"%d\" bIndirectJmp=\"%d\">\n", \
		pInstructionJmp->bTargetAddressIsInvalid, \
		pInstructionJmp->bJmpOut, \
		pInstructionJmp->bIndirectJmp);

	Output2XML_JmpWay(fp, pInstructionJmp->JmpWay);
	Output2XML_JmpBit(fp, pInstructionJmp->JmpBit);
	Output2XML_JmpType(fp, pInstructionJmp->JmpType);

	if (pInstructionJmp->bIndirectJmp) {
		fprintf(fp, "<addrIndirectMemoryAddress>0x%4X</addrIndirectMemoryAddress>\n", pInstructionJmp->addrIndirectMemoryAddress);
		fprintf(fp, "<ofIndirectFileOffset>0x%4X</ofIndirectFileOffset>\n", pInstructionJmp->pIndirectFileAddress - pMem);
	} else {
		fprintf(fp, "<addrTargetMemoryAddress>0x%4X</addrTargetMemoryAddress>\n", pInstructionJmp->addrTargetMemoryAddress);
		fprintf(fp, "<ofTargetFileOffset>0x%4X</ofTargetFileOffset>\n", pInstructionJmp->pTargetFileAddress - pMem);
	}

	if (pInstructionJmp->JmpBit != JMP_NONE) {
		if (pInstructionJmp->JmpBit == JMP_BIT8)
			fprintf(fp, "<Offset>0x%X</Offset>\n", pInstructionJmp->Offset.bVal);
		else if (pInstructionJmp->JmpBit == JMP_BIT16)
			fprintf(fp, "<Offset>0x%X</Offset>\n", pInstructionJmp->Offset.wVal);
		else if (pInstructionJmp->JmpBit == JMP_BIT32)
			fprintf(fp, "<Offset>0x%X</Offset>\n", pInstructionJmp->Offset.dwVal);
	}

	fprintf(fp, "</InstructionJmp>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_HookSuccessLevel(FILE *fp, HOOK_SUCCESS_LEVEL HookSuccessLevel) {
	if (HookSuccessLevel == HOOK_LEVEL_NOT) {
		fprintf(fp, "<HookSuccessLevel>HOOK_LEVEL_NOT</HookSuccessLevel>\n");
	} else if (HookSuccessLevel == HOOK_LEVEL_MAYBE) {
		fprintf(fp, "<HookSuccessLevel>HOOK_LEVEL_MAYBE</HookSuccessLevel>\n");
	} else if (HookSuccessLevel == HOOK_LEVEL_OK) {
		fprintf(fp, "<HookSuccessLevel>HOOK_LEVEL_OK</HookSuccessLevel>\n");
	} else {
		//
	}
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_ReferenceData(FILE *fp, PREFERENCE_DATA pReferenceData, __memory pMem) {
	if (!pReferenceData)
		return;

	fprintf(fp, "<ReferenceData>\n");
	fprintf(fp, "<bSet>%d</bSet>\n", pReferenceData->bSet);
	fprintf(fp, "<bMaybeCrash>%d</bMaybeCrash>\n", pReferenceData->bMaybeCrash);
	fprintf(fp, "<addrMemoryAddress>0x%X</addrMemoryAddress>\n", pReferenceData->addrMemoryAddress);
	fprintf(fp, "<ofFileOffset>0x%X</ofFileOffset>\n", pReferenceData->pFileAddress - pMem);

	if (pReferenceData->pImportTableReference) {
		PIMPORT_TABLE_REFERENCE pCurr = NULL;

		pCurr = pReferenceData->pImportTableReference;
		fprintf(fp, "<ImportTableReference>\n");
		fprintf(fp, "<LibName>%s</LibName>\n", pCurr->szLibName);

		if (pCurr->bOrdinal)
			fprintf(fp, "<Ord>0x%X</Ord>\n", pCurr->wOrdinal);
		else
			fprintf(fp, "<Name>%s</Name>\n", pCurr->szProcName);

		fprintf(fp, "<addrFirstThunk>0x%X</addrFirstThunk>\n", pCurr->addrFirstThunk);
		fprintf(fp, "<ofFirstThunk>0x%X</ofFirstThunk>\n", pCurr->ofFirstThunk);
		fprintf(fp, "<ofFirstThunkFileOffset>0x%X</ofFirstThunkFileOffset>\n", pCurr->ofFirstThunkFileOffset);

		fprintf(fp, "<addrReferenceMemAddress>0x%X</addrReferenceMemAddress>\n", pCurr->addrReferenceMemAddress);
		fprintf(fp, "<ofReferenceRVA>0x%X</ofReferenceRVA>\n", pCurr->ofReferenceRVA);
		fprintf(fp, "<ofReferenceFileOffset>0x%X</ofReferenceFileOffset>\n", pCurr->ofReferenceFileOffset);

		fprintf(fp, "<addrAddressReferenceMemAddress>0x%X</addrAddressReferenceMemAddress>\n", pCurr->addrAddressReferenceMemAddress);
		fprintf(fp, "<ofAddressReferenceRVA>0x%X</ofAddressReferenceRVA>\n", pCurr->ofAddressReferenceRVA);
		fprintf(fp, "<ofAddressReferenceFileOffset>0x%X</ofAddressReferenceFileOffset>\n", pCurr->ofAddressReferenceFileOffset);

		fprintf(fp, "</ImportTableReference>\n");
	}

	fprintf(fp, "</ReferenceData>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_EffectRegister(FILE *fp, __bool *pEffectRegister) {
	__integer i = 0;
	fprintf(fp, "<EffectRegister>\n");

	for (i = 0; i < 8; i ++) {
		if (pEffectRegister[i] == TRUE) {
			if (i == 0)
				fprintf(fp, "<EAX>Effect</EAX>\n");
			else if (i == 1)
				fprintf(fp, "<ECX>Effect</ECX>\n");
			else if (i == 2)
				fprintf(fp, "<EDX>Effect</EDX>\n");
			else if (i == 3)
				fprintf(fp, "<EBX>Effect</EBX>\n");
			else if (i == 4)
				fprintf(fp, "<ESP>Effect</ESP>\n");
			else if (i == 5)
				fprintf(fp, "<EBP>Effect</EBP>\n");
			else if (i == 6)
				fprintf(fp, "<ESI>Effect</ESI>\n");
			else if (i == 7)
				fprintf(fp, "<EDI>Effect</EDI>\n");
		}
	}/* end for */
	fprintf(fp, "</EffectRegister>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_EffectEFlag(FILE *fp, __bool *pEffectEFlag) {
	fprintf(fp, "<EffectEFlag>\n");

	if (pEffectEFlag[X86EFLAG_CF] == TRUE)
		fprintf(fp, "<CF>Effect</CF>\n");
	if (pEffectEFlag[X86EFLAG_PF] == TRUE)
		fprintf(fp, "<PF>Effect</PF>\n");
	if (pEffectEFlag[X86EFLAG_AF] == TRUE)
		fprintf(fp, "<AF>Effect</AF>\n");
	if (pEffectEFlag[X86EFLAG_ZF] == TRUE)
		fprintf(fp, "<ZF>Effect</ZF>\n");
	if (pEffectEFlag[X86EFLAG_SF] == TRUE)
		fprintf(fp, "<SF>Effect</SF>\n");
	if (pEffectEFlag[X86EFLAG_TF] == TRUE)
		fprintf(fp, "<TF>Effect</TF>\n");
	if (pEffectEFlag[X86EFLAG_IF] == TRUE)
		fprintf(fp, "<IF>Effect</IF>\n");
	if (pEffectEFlag[X86EFLAG_DF] == TRUE)
		fprintf(fp, "<DF>Effect</DF>\n");
	if (pEffectEFlag[X86EFLAG_OF] == TRUE)
		fprintf(fp, "<OF>Effect</OF>\n");
	if (pEffectEFlag[X86EFLAG_IOPL] == TRUE)
		fprintf(fp, "<IOPL>Effect</IOPL>\n");
	if (pEffectEFlag[X86EFLAG_NT] == TRUE)
		fprintf(fp, "<NT>Effect</NT>\n");
	if (pEffectEFlag[X86EFLAG_RF] == TRUE)
		fprintf(fp, "<RF>Effect</RF>\n");
	if (pEffectEFlag[X86EFLAG_VM] == TRUE)
		fprintf(fp, "<VM>Effect</VM>\n");
	if (pEffectEFlag[X86EFLAG_AC] == TRUE)
		fprintf(fp, "<AC>Effect</AC>\n");
	if (pEffectEFlag[X86EFLAG_VIF] == TRUE)
		fprintf(fp, "<VIF>Effect</VIF>\n");
	if (pEffectEFlag[X86EFLAG_VIP] == TRUE)
		fprintf(fp, "<VIP>Effect</VIP>\n");
	if (pEffectEFlag[X86EFLAG_ID] == TRUE)
		fprintf(fp, "<ID>Effect</ID>\n");

	fprintf(fp, "</EffectEFlag>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_ConditionEFlag(FILE *fp, __bool *pConditionEFlag) {
	fprintf(fp, "<ConditionEFlag>\n");

	if (pConditionEFlag[X86EFLAG_CF] == TRUE)
		fprintf(fp, "<CF>Effect</CF>\n");
	if (pConditionEFlag[X86EFLAG_PF] == TRUE)
		fprintf(fp, "<PF>Effect</PF>\n");
	if (pConditionEFlag[X86EFLAG_AF] == TRUE)
		fprintf(fp, "<AF>Effect</AF>\n");
	if (pConditionEFlag[X86EFLAG_ZF] == TRUE)
		fprintf(fp, "<ZF>Effect</ZF>\n");
	if (pConditionEFlag[X86EFLAG_SF] == TRUE)
		fprintf(fp, "<SF>Effect</SF>\n");
	if (pConditionEFlag[X86EFLAG_TF] == TRUE)
		fprintf(fp, "<TF>Effect</TF>\n");
	if (pConditionEFlag[X86EFLAG_IF] == TRUE)
		fprintf(fp, "<IF>Effect</IF>\n");
	if (pConditionEFlag[X86EFLAG_DF] == TRUE)
		fprintf(fp, "<DF>Effect</DF>\n");
	if (pConditionEFlag[X86EFLAG_OF] == TRUE)
		fprintf(fp, "<OF>Effect</OF>\n");
	if (pConditionEFlag[X86EFLAG_IOPL] == TRUE)
		fprintf(fp, "<IOPL>Effect</IOPL>\n");
	if (pConditionEFlag[X86EFLAG_NT] == TRUE)
		fprintf(fp, "<NT>Effect</NT>\n");
	if (pConditionEFlag[X86EFLAG_RF] == TRUE)
		fprintf(fp, "<RF>Effect</RF>\n");
	if (pConditionEFlag[X86EFLAG_VM] == TRUE)
		fprintf(fp, "<VM>Effect</VM>\n");
	if (pConditionEFlag[X86EFLAG_AC] == TRUE)
		fprintf(fp, "<AC>Effect</AC>\n");
	if (pConditionEFlag[X86EFLAG_VIF] == TRUE)
		fprintf(fp, "<VIF>Effect</VIF>\n");
	if (pConditionEFlag[X86EFLAG_VIP] == TRUE)
		fprintf(fp, "<VIP>Effect</VIP>\n");
	if (pConditionEFlag[X86EFLAG_ID] == TRUE)
		fprintf(fp, "<ID>Effect</ID>\n");

	fprintf(fp, "</ConditionEFlag>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_Instruction(FILE *fp, PX86INSTRUCTION pInstruction) {
	__memory pMem = NULL;
	PX86INSTRUCTION pCurrInstruction = NULL;
	PPROCEDURE pProcedure = NULL;
	PPROGRAM pProgram = NULL;
	__integer i = 0;

	if (!pInstruction)
		return;

	pCurrInstruction = pInstruction;
	pProcedure = __GetInstructionParents__(pInstruction);
	pProgram = __GetProcedureParents__(pProcedure);
	pMem = pProgram->pMem;

	fprintf(fp, "<InstructsDetail>\n");
	while (pCurrInstruction) {
		if (pCurrInstruction->bInvalid) {//无效指令
			fprintf(fp, "<x%X Invalid=\"%d\" FileOffset=\"0x%X\">\n", \
				pCurrInstruction->addrCurrMemoryAddress, \
				pCurrInstruction->bInvalid, \
				pCurrInstruction->pCurrFileAddress - pMem);
			fprintf(fp, "<HexCode>%s</HexCode>\n", pCurrInstruction->ud_obj.insn_hexcode);
		} else {
			fprintf(fp, "<x%X FileOffset=\"x%X\" IsJmp=\"%d\" IsReferenceData=\"%d\" IsExchange=\"%d\">\n", \
				pCurrInstruction->addrCurrMemoryAddress, \
				pCurrInstruction->pCurrFileAddress - pMem, \
				pCurrInstruction->bJmp, \
				pCurrInstruction->bReferenceData, \
				pCurrInstruction->bExchange);
			fprintf(fp, "<Asm Length=\"%d\">%s|%s</Asm>\n", pCurrInstruction->ud_obj.inp_ctr, pCurrInstruction->ud_obj.insn_hexcode, pCurrInstruction->ud_obj.insn_buffer);
			Output2XML_HookSuccessLevel(fp, pCurrInstruction->HookSuccessLevel);
			if (pCurrInstruction->HookSuccessLevel > HOOK_LEVEL_NOT)
				fprintf(fp, "<HookSaveAddressFileOffset>0x%X</HookSaveAddressFileOffset>\n", pCurrInstruction->pHookSaveAddress - pMem);

			// 是否引用了数据
			if (pCurrInstruction->bReferenceData) {
				Output2XML_ReferenceData(fp, &(pCurrInstruction->ReferenceData), pMem);
			}

			// 打印几个寄存器
			Output2XML_EffectRegister(fp, pCurrInstruction->EffectRegister);
			Output2XML_EffectEFlag(fp, pCurrInstruction->EffectEFlag);
			Output2XML_ConditionEFlag(fp, pCurrInstruction->ConditionEFlag);
		}

		fprintf(fp, "<ofOffsetByProcedureStart>0x%X</ofOffsetByProcedureStart>\n", pCurrInstruction->ofOffsetByProcedureStart);
		fprintf(fp, "<ofOffsetByImageBase>0x%X</ofOffsetByImageBase>\n", pCurrInstruction->ofOffsetByImageBase);

		// 结束标志
		fprintf(fp, "</x%X>\n", pCurrInstruction->addrCurrMemoryAddress);

		// 下一个指令
		pCurrInstruction = pCurrInstruction->pNext;
	}

	fprintf(fp, "</InstructsDetail>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ Output2XML_ShowImportTableReference(FILE *fp, PIMPORT_TABLE_REFERENCE pImportTableReference) {
	PIMPORT_TABLE_REFERENCE pCurr = NULL;

	fprintf(fp, "<ImportTableReference>\n");

	pCurr = pImportTableReference;
	while (pCurr) {
		fprintf(fp, "<Item HexCode=\"%s\" Inst=\"%s\">\n", ud_insn_hex(&(pCurr->ud_obj)), ud_insn_asm(&(pCurr->ud_obj)));

		fprintf(fp, "<LibName>%s</LibName>\n", pCurr->szLibName);

		if (pCurr->bOrdinal)
			fprintf(fp, "<Ord>0x%X</Ord>\n", pCurr->wOrdinal);
		else
			fprintf(fp, "<Name>%s</Name>\n", pCurr->szProcName);

		fprintf(fp, "<addrFirstThunk>0x%X</addrFirstThunk>\n", pCurr->addrFirstThunk);
		fprintf(fp, "<ofFirstThunk>0x%X</ofFirstThunk>\n", pCurr->ofFirstThunk);
		fprintf(fp, "<ofFirstThunkFileOffset>0x%X</ofFirstThunkFileOffset>\n", pCurr->ofFirstThunkFileOffset);

		fprintf(fp, "<addrReferenceMemAddress>0x%X</addrReferenceMemAddress>\n", pCurr->addrReferenceMemAddress);
		fprintf(fp, "<ofReferenceRVA>0x%X</ofReferenceRVA>\n", pCurr->ofReferenceRVA);
		fprintf(fp, "<ofReferenceFileOffset>0x%X</ofReferenceFileOffset>\n", pCurr->ofReferenceFileOffset);

		fprintf(fp, "<addrAddressReferenceMemAddress>0x%X</addrAddressReferenceMemAddress>\n", pCurr->addrAddressReferenceMemAddress);
		fprintf(fp, "<ofAddressReferenceRVA>0x%X</ofAddressReferenceRVA>\n", pCurr->ofAddressReferenceRVA);
		fprintf(fp, "<ofAddressReferenceFileOffset>0x%X</ofAddressReferenceFileOffset>\n", pCurr->ofAddressReferenceFileOffset);

		fprintf(fp, "</Item>\n");
		pCurr = pCurr->pNext;
	}

	fprintf(fp, "</ImportTableReference>\n");
	return;
}

__bool __INTERNAL_FUNC__ Output2XML(PPROGRAM pProgram, __tchar *pResultFilePath) {
	FILE *fp = NULL;
	__char buf[1024] = {0};

	UnicodeToAnsi(pResultFilePath, MAX_PATH, buf, 1024);
	fp = fopen(buf, "w");
	if (!fp) return FALSE;

	// 输出信息头
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(fp, "<Program>\n");

	fprintf(fp, "<Info>\n");
	fprintf(fp, "<Imagebase>0x%X</Imagebase>\n", pProgram->ImageBase);
	fprintf(fp, "<addrCodeSegMemoryAddress>0x%X</addrCodeSegMemoryAddress>\n", pProgram->addrCodeSegMemoryAddress);
	fprintf(fp, "<iBinSize>%d</iBinSize>\n", pProgram->iBinSize);
	fprintf(fp, "<iCodeSegSize>%d</iCodeSegSize>\n", pProgram->iCodeSegSize);
	fprintf(fp, "<iTailDataSize>%d</iTailDataSize>\n", pProgram->iTailDataSize);
	fprintf(fp, "<iEntryRva>0x%X</iEntryRva>\n", pProgram->iEntryRva);
	//fprintf(fp, "<ProcedureCount>%d</ProcedureCount>\n", pProgram->iProcCount);
	fprintf(fp, "</Info>\n");

	//PPROCEDURE_REFFROM pProcedureRefForm;//哪个函数引用了这个函数,这个需要释放空间
	//PINSTRUCTION_JMP pInstructionJmp;//跳转指令链
	//PX86INSTRUCTION pInstruction;//指令链,这个需要释放空间

	// 引入表引用
	Output2XML_ShowImportTableReference(fp, pProgram->pImportTableReference);

	// 函数
	fprintf(fp, "<Procedures CodeBlockCount=\"%d\" DataBlockCount=\"%d\">\n", pProgram->iProcCount, pProgram->iAllBlockCount - pProgram->iProcCount);
	{
		__integer i = 0;
		PPROCEDURE pProcedure = NULL;

		pProcedure = pProgram->pProcedureList;
		for (i = 0; i < pProgram->iAllBlockCount; i++, pProcedure = pProcedure->pNext) {
			if (pProcedure->bEntry)
				fprintf(fp, "<Procedure Entry=\"%d\" Size=\"%d\">\n", pProcedure->bEntry, pProcedure->iSize);
			else
				fprintf(fp, "<Procedure Size=\"%d\">\n", pProcedure->iSize);

			fprintf(fp, "<IsBlock>%d</IsBlock>\n", pProcedure->bBlock);
			fprintf(fp, "<addrMemoryStartAddress>0x%X</addrMemoryStartAddress>\n", pProcedure->addrMemoryStartAddress);
			fprintf(fp, "<ofFileOffset>0x%X</ofFileOffset>\n", pProcedure->pFileStartAddress - pProgram->pMem);

			if (pProcedure->bInline) {
				fprintf(fp, "<IsInline>%d</IsInline>\n", pProcedure->bInline);
				fprintf(fp, "<FatherProcedure Size=\"0x%X\">0x%X</FatherProcedure>\n", pProcedure->pFatherProcedure->iSize, pProcedure->pFatherProcedure->addrMemoryStartAddress);
			}

			if (pProcedure->bBlock) {
				Output2XML_Hexcode(fp, pProcedure->pFileStartAddress, pProcedure->iSize);
			} else {
				fprintf(fp, "<addrAllocStackMemoryAddress>0x%X</addrAllocStackMemoryAddress>\n", pProcedure->addrAllocStackMemoryAddress);
				fprintf(fp, "<ofAllocStackFileOffset>0x%X</ofAllocStackFileOffset>\n", pProcedure->pAllocStackFileAddress - pProgram->pMem);
				fprintf(fp, "<StackSize>%d</StackSize>\n", pProcedure->iStackSize);
				Output2XML_AllocStackType(fp, pProcedure->AllocStackType);
				fprintf(fp, "<InstCount>%d</InstCount>\n", pProcedure->iInstCount);
				fprintf(fp, "<InvalidOpcodeCount>%d</InvalidOpcodeCount>\n", pProcedure->iInvalidOpcodeCount);
				Output2XML_Disasm(fp, pProcedure->addrMemoryStartAddress, pProcedure->pFileStartAddress, pProcedure->iSize);
				Output2XML_ProcedureRefForm(fp, pProcedure->pProcedureRefForm);
				Output2XML_InstructionJmp(fp, pProcedure->pInstructionJmp);
				Output2XML_Instruction(fp, pProcedure->pInstruction);
			}

			fprintf(fp, "</Procedure>\n");
		}/* end for */
	}
	fprintf(fp, "</Procedures>\n");

	fprintf(fp, "</Program>\n");
	fclose(fp);
	return TRUE;
}

#define __PROCEDURE_FLOWCHART_DOT__		"flowchart.dot"
#define __PROCEDURE_FLOWCHART_PIC__		"flowchart.png"
__bool __INTERNAL_FUNC__ Output2FlowChart(PPROGRAM pProgram, __tchar *pResultDir) {
	FILE *fp = NULL;
	PPROCEDURE pProcedure = NULL;
	__char DotFile[1024] = {0};
	__char PngFile[1024] = {0};
	__char CommandFile[1024] = {0};

	UnicodeToAnsi(pResultDir, MAX_PATH, DotFile, 1024);
	strcat(DotFile, __PROCEDURE_FLOWCHART_DOT__);

	UnicodeToAnsi(pResultDir, MAX_PATH, PngFile, 1024);
	strcat(PngFile, __PROCEDURE_FLOWCHART_PIC__);

	fp = fopen(DotFile, "w");
	if (!fp) return FALSE;

	fprintf(fp, "digraph ProcedureFlowChart {\n");

	// 定义节点
	pProcedure = pProgram->pProcedureList;
	while (pProcedure) {
		__char szNode[0x100] = {0};

		if (pProcedure->bEntry) {
			sprintf(szNode, "NodeWithSize%x[shape=ellipse,label=\"0x%x size=%d\"];\n", pProcedure->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress, pProcedure->iSize);
			//sprintf(szNode, "Node%x[shape=ellipse,label=\"0x%x\"];\n", pProcedure->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress);
		} else {
			sprintf(szNode, "NodeWithSize%x[shape=box,label=\"0x%x size=%d\"];\n", pProcedure->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress, pProcedure->iSize);
			//sprintf(szNode, "Node%x[shape=box,label=\"0x%x\"];\n", pProcedure->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress);
		}
		fprintf(fp, szNode);
		pProcedure = pProcedure->pNext;
	}

	// 链接节点
	pProcedure = pProgram->pProcedureList;
	while (pProcedure) {
		PPROCEDURE_REFFROM pProcedureRefFrom = NULL;
		PPROCEDURE pRef = NULL;
		
		pProcedureRefFrom = pProcedure->pProcedureRefForm;
		while (pProcedureRefFrom) {
			__char szNode[0x100] = {0};

			pRef = pProcedureRefFrom->pProcedure;			
			//sprintf(szNode, "Node%x -> Node%x;\n", pRef->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress);
			sprintf(szNode, "NodeWithSize%x -> NodeWithSize%x;\n", pRef->addrMemoryStartAddress, pProcedure->addrMemoryStartAddress);
			fprintf(fp, szNode);
			pProcedureRefFrom = pProcedureRefFrom->pNext;
		}

		pProcedure = pProcedure->pNext;
	}

	fprintf(fp, "}\r\n");
	fclose(fp);

	// 合成命令行
	UnicodeToAnsi(g_szGraphvizPath, __logic_tcslen__(g_szGraphvizPath), CommandFile, 1024);
	sprintf(CommandFile, "%s -Tpng %s -o %s", CommandFile, DotFile, PngFile);

	// 执行命令
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );


		if (!CreateProcessA( NULL, CommandFile, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			__dword dwLastErr = GetLastError();
			return FALSE;
		}

		// 等待执行完毕
		WaitForSingleObject( pi.hProcess, INFINITE ); 
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}

	return TRUE;
}

ANALYZE_BASIC_INFO g_AnalyzeBasicInfo = {0};
__bool __INTERNAL_FUNC__ Analyze(PXFILE_ATTACH_INFO pTarget, __tchar *pResultDir, __tchar *pResultFilePath, PANALYZE_CONFIGURE pConfigure) {
	PPROGRAM pProgram = NULL;

	// 填充基本信息结构
	if (FillAnalyzeBasicInfo(pTarget, &g_AnalyzeBasicInfo) == FALSE) {
		return FALSE;
	}

	// 分析
	pConfigure->bCodeMixSize = 6;//默认代码最小长度等于6
	pProgram = AnalyzeProgram(pConfigure, &g_AnalyzeBasicInfo);
	if (!pProgram) {
		// 分析程序失败
		return FALSE;
	}

	// 输出到XML文件
	if (!Output2XML(pProgram, pResultFilePath)) {
		// 输出文件失败
		return FALSE;
	}

	// 输出函数流程图
	if (g_bGenProcedureFlowChart) {
		if (!Output2FlowChart(pProgram, pResultDir)) {
			return FALSE;
		}
	}

	ReleaseProgram(&pProgram);
	return TRUE;
}
