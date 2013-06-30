#include "DISAth.h"

/*
 * 宏函数
 */
// 处理步骤函数返回值
#define __HandleDISAthStepReturnValue__(n, x)				{\
	if (!(__DISATH_SUCCESS__(x))) return x;\
	else if ((x & __DISATH_ERROR_SUCCESS_GOTO__) == __DISATH_ERROR_SUCCESS_GOTO__) {\
		if ((x == __DISATH_ERROR_SUCCESS_GOTO_0__) && (n != 0)) goto _call_back_0;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_1__) && (n != 1)) goto _call_back_1;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_2__) && (n != 2)) goto _call_back_2;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_3__) && (n != 3)) goto _call_back_3;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_4__) && (n != 4)) goto _call_back_4;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_5__) && (n != 5)) goto _call_back_5;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_6__) && (n != 6)) goto _call_back_6;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_7__) && (n != 7)) goto _call_back_7;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_8__) && (n != 8)) goto _call_back_8;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_9__) && (n != 9)) goto _call_back_9;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_A__) && (n != 10)) goto _call_back_10;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_B__) && (n != 11)) goto _call_back_11;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_C__) && (n != 12)) goto _call_back_12;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_D__) && (n != 13)) goto _call_back_13;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_E__) && (n != 14)) goto _call_back_14;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_F__) && (n != 15)) goto _call_back_15;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_10__) && (n != 16)) goto _call_back_16;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_11__) && (n != 17)) goto _call_back_17;\
		else if ((x == __DISATH_ERROR_SUCCESS_GOTO_12__) && (n != 18)) goto _call_back_18;\
	}\
}

__dword __API__ DISAthAttach(PDISATH_CONFIGURE pConfigure) {
	PXFILE_ATTACH_INFO pXFileAttachInfo = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;
	__integer iXSectionSize = 0;
	PIMAGE_NT_HEADERS pTargetNtHeader = NULL;
	PIMAGE_NT_HEADERS pDISNtHeader = NULL;
	__memory pDIS = NULL;
	__integer iDISSize = 0;
	PXFILE_SECTION_HEADER pXSection = NULL;
	PDIS_CONFIGURE pDISConfigure = NULL;
	__bool bDISFromResource = FALSE;
	__dword dwStepReturn = __DISATH_ERROR_SUCCESS__;

	// 初始化变量
	pXFileAttachInfo = &(pConfigure->XFileAttachInfo);

	// 执行0号步骤
_call_back_0:
	dwStepReturn = DISAthStep0(pConfigure);
	__HandleDISAthStepReturnValue__(0, dwStepReturn);

	// 打开映射
	if (!XFileAttachInfoInit(pXFileAttachInfo)) {
		return __DISATH_ERROR_MAPPING_FILE_FAILED__;
	}

	// 执行1号步骤
_call_back_1:
	dwStepReturn = DISAthStep1(pXFileAttachInfo, pConfigure);
	__HandleDISAthStepReturnValue__(1, dwStepReturn);
	
	// 添加X文件
	pXFileNtSectionHeader = XFileAddXFileToPEFile(pXFileAttachInfo, 0x1000, 5);
	if (!pXFileNtSectionHeader) {
		if (pConfigure->bIfXFileExistFailed)
			return __DISATH_ERROR_ADD_XFILE_FAILED__;
		else {
			// 获取X文件
			pXFileNtSectionHeader = XFileExistXFileInPEFile(pXFileAttachInfo->pMem);
			if (!pXFileNtSectionHeader)
				return __DISATH_ERROR_ADD_XFILE_FAILED__;
		}/* end else */
	}

	// 执行2号步骤
_call_back_2:
	dwStepReturn = DISAthStep2(pXFileAttachInfo, pXFileNtSectionHeader);
	__HandleDISAthStepReturnValue__(2, dwStepReturn);

	// 获取目标文件的基本信息
	pTargetNtHeader = GetNtHeader(pXFileAttachInfo->pMem);

	// 执行3号步骤
_call_back_3:
	dwStepReturn = DISAthStep3(pXFileAttachInfo, pTargetNtHeader);
	__HandleDISAthStepReturnValue__(3, dwStepReturn);

	// 开始进入关键的流程
	{
		XFILE_SECTION_HEADER NewXFileSection = {0};
		__address addrDISImageBaseInTarget = 0;
		__offset ofDISOffsetByXSectionBody = 0;
		__integer iDISSizeOfImage = 0;
		__memory pDISInTarget = NULL;
		__offset ofDISConfigureRVA = 0;

		// 预先计算新的X节
		if (!XFilePredictNewSectionHeader(pXFileAttachInfo->pMem, &NewXFileSection)) {
			return __DISATH_ERROR_PREDICT_NEW_XSECTION_FAILED__;
		}

		// 执行4号步骤
_call_back_4:
		dwStepReturn = DISAthStep4(pXFileAttachInfo, &NewXFileSection);
		__HandleDISAthStepReturnValue__(4, dwStepReturn);

		// 获取DIS在目标文件中的基地址
		addrDISImageBaseInTarget = pTargetNtHeader->OptionalHeader.ImageBase + NewXFileSection.dwVirtualAddress;
		addrDISImageBaseInTarget = AligImageBase(addrDISImageBaseInTarget);
		ofDISOffsetByXSectionBody = addrDISImageBaseInTarget - (pTargetNtHeader->OptionalHeader.ImageBase + NewXFileSection.dwVirtualAddress);

		// 执行5号步骤
_call_back_5:
		dwStepReturn = DISAthStep5(pXFileAttachInfo, addrDISImageBaseInTarget, ofDISOffsetByXSectionBody);
		__HandleDISAthStepReturnValue__(5, dwStepReturn);

		// 映射DIS
		bDISFromResource = (__HiWord__(pConfigure->szDISFilePath) == 0);
		if (bDISFromResource) {
			pDIS = MapResourceDataEx(NULL, pConfigure->wResourceID, pConfigure->szResourceType, &iDISSize, pConfigure->dwDISResourceKey);
			if (!pDIS) {
				return __DISATH_ERROR_MAP_DIS_FROM_RESOURCE_FAILED__;
			}
		} else {
			__memory t = NULL;
			pDIS = MappingFile(pConfigure->szDISFilePath, &iDISSize, FALSE, 0, 0);
			if (!pDIS) {
				return __DISATH_ERROR_MAP_DIS_FROM_FILE_FAILED__;
			}
			t = (__memory)__logic_new_size__(iDISSize);
			__logic_memcpy__(t, pDIS, iDISSize);
			UnMappingFile(pDIS);
			pDIS = t;
		}

		// 执行6号步骤
_call_back_6:
		dwStepReturn = DISAthStep6(pXFileAttachInfo, pDIS, iDISSize);
		__HandleDISAthStepReturnValue__(6, dwStepReturn);

		// 计算出新X节的长度
		pDISNtHeader = GetNtHeader(pDIS);
		iDISSizeOfImage = pDISNtHeader->OptionalHeader.SizeOfImage;
		iXSectionSize = iDISSizeOfImage + ofDISOffsetByXSectionBody;

		// 执行7号步骤
_call_back_7:
		dwStepReturn = DISAthStep7(pXFileAttachInfo, pDIS, iDISSize, iDISSizeOfImage, ofDISOffsetByXSectionBody, &iXSectionSize);
		__HandleDISAthStepReturnValue__(7, dwStepReturn);

		// 计算DIS公共数据区的内存偏移(RVA)
		{
			__memory x = NULL;
			__memory y = NULL;

			x = (__memory)__logic_new_size__(iDISSizeOfImage);
			CopyMemToMemBySecAlign(pDIS, x, iDISSizeOfImage);
			y = (__memory)xGetProcAddressImmediately((HMODULE)x, "g_DISConfigure");
			if (!y) {
				return __DISATH_ERROR_GET_DISCONFIGURE_FAILED__;
			}
			ofDISConfigureRVA = (__offset)(y - x);
			__logic_delete__(x);
		}

		// 添加一个新X节
		pXSection = XFileAddXFileSectionByNtSectionHeader(pXFileAttachInfo, pXFileNtSectionHeader, iXSectionSize, __XFILE_SECTION_CHARACTERISTICS_PE__, (__dword)ofDISOffsetByXSectionBody, ofDISConfigureRVA);
		if (!pXSection) {
			return __DISATH_ERROR_ADD_XSECTION_FAILED__;
		}

		// 执行8号步骤
_call_back_8:
		dwStepReturn = DISAthStep8(pXFileAttachInfo, pDIS, iDISSize, pXFileNtSectionHeader, pXSection, pXSection->dwDNA, ofDISConfigureRVA);
		__HandleDISAthStepReturnValue__(8, dwStepReturn);

		// 重新获取目标文件的NT头
		pTargetNtHeader = GetNtHeader(pXFileAttachInfo->pMem);

		// 执行9号步骤
_call_back_9:
		dwStepReturn = DISAthStep9(pXFileAttachInfo, pTargetNtHeader);
		__HandleDISAthStepReturnValue__(9, dwStepReturn);

		// DIS在目标文件中的位置
		pDISInTarget = pXFileAttachInfo->pMem + pXSection->dwPointerToRawData + ofDISOffsetByXSectionBody;

		// 以内存映射复制yImportTable
		CopyMemToMemBySecAlign(pDIS, pDISInTarget, iDISSizeOfImage);

		// 执行10号步骤
_call_back_10:
		dwStepReturn = DISAthStep10(pXFileAttachInfo, pDIS, pDISInTarget, iDISSizeOfImage);
		__HandleDISAthStepReturnValue__(10, dwStepReturn);

		// 释放DIS
		if (bDISFromResource)
			UnMapResourceData(pDIS);
		else
			__logic_delete__(pDIS);
		
		// 获取DIS的配置结构
		pDISConfigure = (PDIS_CONFIGURE)xGetProcAddressImmediately((HMODULE)pDISInTarget, "g_DISConfigure");
		if (!pDISConfigure)
			return __DISATH_ERROR_GET_DISCONFIGURE_FAILED__;

		// 配置DIS
		__logic_memset__(pDISConfigure, 0, sizeof(DIS_CONFIGURE));
		pDISConfigure->ofOrigEntryRVA = pXFileAttachInfo->OrigTargetNtHeader.OptionalHeader.AddressOfEntryPoint;
		pDISConfigure->addrOrigImageBase = pXFileAttachInfo->OrigTargetNtHeader.OptionalHeader.ImageBase;
		pDISConfigure->iOrigSizeOfImage = pXFileAttachInfo->OrigTargetNtHeader.OptionalHeader.SizeOfImage;
		pDISConfigure->iNowSizeOfImage = pTargetNtHeader->OptionalHeader.SizeOfImage;
		pDISConfigure->bFirstRun = TRUE;
		pDISConfigure->bProtectMyIAT = pConfigure->bProtectMyIAT;
		pDISConfigure->bProtectTargetIAT = pConfigure->bProtectTargetIAT;

		// 设置DIS自己的引入表保护结构
		pDISConfigure->DISImportProtect.addrImageBase = addrDISImageBaseInTarget;//设置DIS在目标中的基地址,如果是DLL那么这个基地址是变动的

		pDISConfigure->DISImportProtect.iProtectDllCrc32Count = pConfigure->iDISProtectDllCrc32Count;
		__logic_memcpy__(&(pDISConfigure->DISImportProtect.dwProtectDllCrc32List), &(pConfigure->dwDISProtectDllCrc32List), sizeof(__dword) * pDISConfigure->DISImportProtect.iProtectDllCrc32Count);

		pDISConfigure->DISImportProtect.iProtectApiCrc32Count = pConfigure->iDISProtectApiCrc32Count;
		__logic_memcpy__(&(pDISConfigure->DISImportProtect.dwProtectApiCrc32List), &(pConfigure->dwDISProtectApiCrc32List), sizeof(__dword) * pDISConfigure->DISImportProtect.iProtectApiCrc32Count);

		pDISConfigure->DISImportProtect.iProtectDllCallDllMainCrc32Count = pConfigure->iDISProtectDllCallDllMainCrc32Count;
		__logic_memcpy__(&(pDISConfigure->DISImportProtect.dwProtectDllCallDllMainCrc32List), &(pConfigure->dwDISProtectDllCallDllMainCrc32List), sizeof(__dword) * pDISConfigure->DISImportProtect.iProtectDllCallDllMainCrc32Count);

		// 设置目标文件的引入表保护结构
		pDISConfigure->TargetImportProtect.addrImageBase = pTargetNtHeader->OptionalHeader.ImageBase;//设置目标文件的基地址,如果目标文件是DLL或者开启随机地址化映射,那么这个值是变动的

		pDISConfigure->TargetImportProtect.iProtectDllCrc32Count = pConfigure->iTargetProtectDllCrc32Count;
		__logic_memcpy__(&(pDISConfigure->TargetImportProtect.dwProtectDllCrc32List), &(pConfigure->dwTargetProtectDllCrc32List), sizeof(__dword) * pDISConfigure->TargetImportProtect.iProtectDllCrc32Count);

		pDISConfigure->TargetImportProtect.iProtectApiCrc32Count = pConfigure->iTargetProtectApiCrc32Count;
		__logic_memcpy__(&(pDISConfigure->TargetImportProtect.dwProtectApiCrc32List), &(pConfigure->dwTargetProtectApiCrc32List), sizeof(__dword) * pDISConfigure->TargetImportProtect.iProtectApiCrc32Count);

		pDISConfigure->TargetImportProtect.iProtectDllCallDllMainCrc32Count = pConfigure->iTargetProtectDllCallDllMainCrc32Count;
		__logic_memcpy__(&(pDISConfigure->TargetImportProtect.dwProtectDllCallDllMainCrc32List), &(pConfigure->dwTargetProtectDllCallDllMainCrc32List), sizeof(__dword) * pDISConfigure->TargetImportProtect.iProtectDllCallDllMainCrc32Count);

		// 加密DIS的引入表
		{
			PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceDISImportTableAddress = NULL;
			__offset ofDISNewAddressTableRva = 0;
			__offset ofDISNewAddressTableRvaByDIS = 0;
			__memory pDISNewImportTable = NULL;

			// 获取DIS新引入地址表在目标中的位置
			pDISNewImportTable = (__memory)&(pDISConfigure->addrDISNewImportTable);
			// 随机向新引入地址表填充随机值
			{
				__integer i = 0;
				__address *pAddrDISNewImportTable = NULL;

				for (i = 0; i < __MAX_JMP_ADDRESS_TABLE_COUNT__ / sizeof(__address); i++) {
					pAddrDISNewImportTable = (__address *)((__memory)pDISNewImportTable + i * sizeof(__address));
					*pAddrDISNewImportTable = (__address)GenerateRandomNumber();
				}
			}

			// 获取DIS新的引入地址表在目标地址中的偏移

			/*
			 * 以下计算出来的是新的引入地址表离目标程序基地址的RVA,而解密引入表的时候是以在DIS的RVA偏移计算的,所以以下语句出错
			 * 这个调试了半天,特此标记,不过还是计算出来提供给回调函数使用
			 * ofDISNewAddressTableRva = pXSection->dwVirtualAddress + ofDISOffsetByXSectionBody + (pDISNewImportTable - pDISInTarget);
			 */
			ofDISNewAddressTableRva = pXSection->dwVirtualAddress + ofDISOffsetByXSectionBody + (pDISNewImportTable - pDISInTarget);
			ofDISNewAddressTableRvaByDIS = (__offset)(pDISNewImportTable - pDISInTarget);

			// 执行11号步骤
_call_back_11:
			dwStepReturn = DISAthStep11(pXFileAttachInfo, pDISInTarget, pDISConfigure, ofDISNewAddressTableRva);
			__HandleDISAthStepReturnValue__(11, dwStepReturn);

			if (pDISConfigure->bProtectMyIAT) {
				// 重新获取DIS的基地址
				pDISNtHeader = GetNtHeader(pDISInTarget);
				// 不使用__USE_DEF_IMAGEBASE_AS_ORIG__,直接使用指定的基地址
				pReferenceDISImportTableAddress = PowerEncryptImportTable(pDISInTarget, pDISNtHeader->OptionalHeader.ImageBase, &(pDISConfigure->DISImportProtect), FALSE, ofDISNewAddressTableRvaByDIS);
				if (!pReferenceDISImportTableAddress) {
					return __DISATH_ERROR_ENCRYPT_DIS_IMPORT_TABLE_FAILED__;
				}/* end if */
			}

			// 执行12号步骤
_call_back_12:
			dwStepReturn = DISAthStep12(pXFileAttachInfo, pDISInTarget, pDISConfigure, pReferenceDISImportTableAddress);
			__HandleDISAthStepReturnValue__(12, dwStepReturn);

			ReleaseReferenceImportTableAddress(&pReferenceDISImportTableAddress);
		}

		// 保护目标文件的引入表
		{
			PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceTargetImportTableAddress = NULL;
			__offset ofTargetNewAddressTableRva = 0;
			__memory pTargetNewImportTable = NULL;

			// 获取新引入地址表在目标中的位置
			pTargetNewImportTable = (__memory)&(pDISConfigure->addrTargetNewImportTable);
			// 随机向新引入地址表填充随机值
			{
				__integer i = 0;
				__address *pAddrTargetNewImportTable = NULL;

				for (i = 0; i < __MAX_JMP_ADDRESS_TABLE_COUNT__ / sizeof(__address); i++) {
					pAddrTargetNewImportTable = (__address *)((__memory)pTargetNewImportTable + i * sizeof(__address));
					*pAddrTargetNewImportTable = (__address)GenerateRandomNumber();
				}
			}

			// 获取新的引入地址表在目标地址中的偏移
			/*
			 * 因为新的引入地址表是在DIS体内所以,这里这样计算是正确的
			 */
			ofTargetNewAddressTableRva = pXSection->dwVirtualAddress + ofDISOffsetByXSectionBody + (pTargetNewImportTable - pDISInTarget);

			// 执行13号步骤
_call_back_13:
			dwStepReturn = DISAthStep13(pXFileAttachInfo, pDISInTarget, pDISConfigure, ofTargetNewAddressTableRva);
			__HandleDISAthStepReturnValue__(13, dwStepReturn);

			if (pDISConfigure->bProtectTargetIAT) {
				pReferenceTargetImportTableAddress = PowerEncryptImportTable(pXFileAttachInfo->pMem, __USE_DEF_IMAGEBASE_AS_ORIG__, &(pDISConfigure->TargetImportProtect), TRUE, ofTargetNewAddressTableRva);
				if (!pReferenceTargetImportTableAddress) {
					return __DISATH_ERROR_ENCRYPT_TARGET_IMPORT_TABLE_FAILED__;
				}
			}

			// 执行14号步骤
_call_back_14:
			dwStepReturn = DISAthStep14(pXFileAttachInfo, pDISInTarget, pDISConfigure, pReferenceTargetImportTableAddress);
			__HandleDISAthStepReturnValue__(14, dwStepReturn);

			ReleaseReferenceImportTableAddress(&pReferenceTargetImportTableAddress);
		}

		// 执行15号步骤
_call_back_15:
		dwStepReturn = DISAthStep15(pXFileAttachInfo, pDISInTarget, pDISConfigure);
		__HandleDISAthStepReturnValue__(15, dwStepReturn);

		// 修改目标函数的入口点
		{
			__memory pDISEntryProc = NULL;

			if (pXFileAttachInfo->bImageBaseRelocate)
				pDISEntryProc = (__memory)xGetProcAddressImmediately((HMODULE)pDISInTarget, "DISEntryInDll");
			else
				pDISEntryProc = (__memory)xGetProcAddressImmediately((HMODULE)pDISInTarget, "DISEntry");

			// 修改
			pTargetNtHeader->OptionalHeader.AddressOfEntryPoint = pXSection->dwVirtualAddress + ofDISOffsetByXSectionBody + (pDISEntryProc - pDISInTarget);

			// 执行16号步骤
_call_back_16:
			dwStepReturn = DISAthStep16(pXFileAttachInfo, pTargetNtHeader);
			__HandleDISAthStepReturnValue__(16, dwStepReturn);
		}

		// 执行17号步骤
_call_back_17:
		dwStepReturn = DISAthStep17(pXFileAttachInfo, pDISInTarget, pDISConfigure);
		__HandleDISAthStepReturnValue__(17, dwStepReturn);

	}

	// 关闭文件映射
	XFileReleaseXFileAttach(pXFileAttachInfo);

	// 执行18号步骤
_call_back_18:
	dwStepReturn = DISAthStep18(pConfigure);
	__HandleDISAthStepReturnValue__(18, dwStepReturn);

	return __DISATH_ERROR_SUCCESS__;
}

