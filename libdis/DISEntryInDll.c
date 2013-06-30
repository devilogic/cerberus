// DIS保护DLL文件
__bool __API__ DISEntryInDllKernel(__dword dwEsp, __dword dwRet, __dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
	__memory pHostImageBase = NULL;
	__memory pTargetImageBase = NULL;
	__memory pDISImageBase = NULL;

	PXFILE_HEADER pXFileHeader = NULL;
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL;
	PXFILE_SECTION_HEADER pXFileFatherSectionHeader = NULL;
	PIMAGE_SECTION_HEADER pNtSectionHeader = NULL;

	POWERDECRYPTIMPORTTABLE_ARG PowerDecryptDISImportTableArg = {0};
	POWERDECRYPTIMPORTTABLE_ARG PowerDecryptTargetImportTableArg = {0};

	__address addrDISOrigImageBase = 0;
	__address addrOrigEntryAddress = 0;

	__dword dwStepRet = __DIS_ERROR_SUCCESS__;

	PDIS_CONFIGURE pDISConfigure = NULL;

	// 步骤0,所有流程自己实现
_call_back_0:
	DISStep0(hModule, ul_reason_for_call, lpReserved);

	// 找到目标文件的映射基地址
	pHostImageBase = (__memory)hModule;

_call_back_1:
	dwStepRet = DISStep1((__dword)pHostImageBase, ul_reason_for_call, lpReserved);
	__HandleDISStepReturnValue__(1, dwStepRet);

	// 移动到末尾节
	pNtSectionHeader = GetTailSection(pHostImageBase);

_call_back_2:
	dwStepRet = DISStep2((__dword)pHostImageBase, ul_reason_for_call, lpReserved, pNtSectionHeader);
	__HandleDISStepReturnValue__(2, dwStepRet);

	// 判断此是否是X文件
	pXFileHeader = (PXFILE_HEADER)(pHostImageBase + pNtSectionHeader->VirtualAddress);
	if (!__IS_XFILE__(pXFileHeader->dwSign))
		return FALSE;

_call_back_3:
	{
		__dword dwMyDNA = __DIS_KERNEL_DNA__;//默认的DNA值
		dwStepRet = DISStep3((__dword)pHostImageBase, ul_reason_for_call, lpReserved, pNtSectionHeader, pXFileHeader, &dwMyDNA);
		__HandleDISStepReturnValue__(3, dwStepRet);

		// 通过自身的DNA找到自己
		pXFileSectionHeader = XFileGetXFileSectionHeaderByDNA(pHostImageBase, pXFileHeader, dwMyDNA, FALSE, &pXFileFatherSectionHeader);
		if (!pXFileSectionHeader)
			return FALSE;
	}

_call_back_4:
	dwStepRet = DISStep4((__dword)pHostImageBase, ul_reason_for_call, lpReserved, pNtSectionHeader, pXFileHeader, pXFileSectionHeader, pXFileFatherSectionHeader);
	__HandleDISStepReturnValue__(4, dwStepRet);

	// 获取X节的扩展数据
	pDISConfigure = (PDIS_CONFIGURE)(pHostImageBase + pXFileSectionHeader->dwCustomDataRVA);

	// 确定是否是第一次运行
	if (!pDISConfigure->bFirstRun) {
		goto _call_back_11;
	}
	pDISConfigure->bFirstRun = FALSE;//设置标志为非第一次运行

_call_back_5:
	dwStepRet = DISStep5((__dword)pHostImageBase, ul_reason_for_call, lpReserved, pNtSectionHeader, pXFileHeader, pXFileSectionHeader, pXFileFatherSectionHeader, pDISConfigure);
	__HandleDISStepReturnValue__(5, dwStepRet);

	// 获取DIS自身的当前基地址
	pDISImageBase = pHostImageBase + pXFileSectionHeader->dwVirtualAddress;
	pDISImageBase = (__memory)AligImageBase((__address)pDISImageBase);
	addrDISOrigImageBase = GetNtHeader(pDISImageBase)->OptionalHeader.ImageBase;//原基地址

_call_back_6:
	dwStepRet = DISStep6((__dword)pHostImageBase, ul_reason_for_call, lpReserved, pNtSectionHeader, pXFileHeader, pXFileSectionHeader, pXFileFatherSectionHeader, pDISConfigure, pDISImageBase, addrDISOrigImageBase);
	__HandleDISStepReturnValue__(6, dwStepRet);

	// 重新定位自身
	if (!BaseRelocation(pDISImageBase, addrDISOrigImageBase, (__address)pDISImageBase, FALSE))
		return FALSE;

_call_back_7:
	dwStepRet = DISStep7(pDISConfigure, pDISImageBase, addrDISOrigImageBase);
	__HandleDISStepReturnValue__(7, dwStepRet);

	// 是否解密自己的引入表
	if (pDISConfigure->bProtectMyIAT) {
		// 初始化引入表保护器
		InitImportProtecter();

		// 重新修订DIS自身的基地址在引入保护结构中
		pDISConfigure->DISImportProtect.addrImageBase = (__address)pDISImageBase;

		// 修复自身的引入表
		PowerDecryptDISImportTableArg.pImportProtect = &(pDISConfigure->DISImportProtect);
		PowerDecryptDISImportTableArg.pAddThunkCodeStub = DISAddThunkCodeStub;
		if (!PowerDecryptImportTable(&PowerDecryptDISImportTableArg))
			return FALSE;
	}

_call_back_8:
	dwStepRet = DISStep8();
	__HandleDISStepReturnValue__(8, dwStepRet);

	// 此DIS是否保护了其他的DIS,获取他的保护对象的基地址
	if (pXFileFatherSectionHeader) {
		pTargetImageBase = pHostImageBase + pXFileFatherSectionHeader->dwVirtualAddress + pXFileFatherSectionHeader->ofMemImageBaseOffset;
	} else {
		pTargetImageBase = pHostImageBase;
	}

_call_back_9:
	dwStepRet = DISStep9(pTargetImageBase);
	__HandleDISStepReturnValue__(9, dwStepRet);

	// 是否解密目标程序的引入表
	if (pDISConfigure->bProtectTargetIAT) {
		// 初始化引入表保护器
		InitImportProtecter();

		// 重新修订DIS所保护的程序的引入表
		pDISConfigure->TargetImportProtect.addrImageBase = (__address)pTargetImageBase;

		// 修复目标程序的引入表
		PowerDecryptTargetImportTableArg.pImportProtect = &(pDISConfigure->TargetImportProtect);
		PowerDecryptTargetImportTableArg.pAddThunkCodeStub = DISAddThunkCodeStub;
		if (!PowerDecryptImportTable(&PowerDecryptTargetImportTableArg))
			return FALSE;
	}

_call_back_10:
	dwStepRet = DISStep10();
	__HandleDISStepReturnValue__(10, dwStepRet);

	// 进入原始入口点
_call_back_11:
	addrOrigEntryAddress = (__address)(pHostImageBase + pDISConfigure->ofOrigEntryRVA);
	dwStepRet = DISStep11(addrOrigEntryAddress);
	__HandleDISStepReturnValue__(11, dwStepRet);
	__asm {
		;;
		;; 调用原始的入口点
			;;
		mov eax, addrOrigEntryAddress			; eax = 原始入口点
		mov esp, dwEsp							; 恢复esp
		jmp eax									; 跳入到原始入口点
	}

	// 花指令

	return TRUE;
}

__NAKED__ __bool __API__ DISEntryInDll(__dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
#if defined(WIN32)
	__asm {
		;;
		;; 当前的堆栈环境
			;; --------------------
			;; ntdll.xxxxxxxx						<- esp
			;; hModule
			;; ul_reason_for_call
			;; lpReserved
			;; 
		;; 压入esp后的堆栈环境
			;; --------------------
			;; 未知值								<- esp
			;; esp的值
			;; ntdll.xxxxxxxx
			;; hModule
			;; ul_reason_for_call
			;; lpReserved
			push esp
			sub esp, 04h							; 减去4个字节,构建一个假的返回值
			;; 直接跳转到DISEntryInDllKernel
			jmp DISEntryInDllKernel
	}
#endif
}
