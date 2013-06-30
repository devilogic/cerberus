#include "PeDiy.h"
#include "Misc.h"
#include "xRand.h"
#include "XFileFormat.h"

// 默认XFILE节对齐粒度
#define __XFILE_ALIGNMENT__					0x100
// 默认X文件节名
#define __XFILE_SECTION_NAME__				"XFILE"
// 默认X节名
#define __XFILE_X_SECTION_NAME__			"XSECTION"
// 基础DNA
#define __XFILE_BASE_DNA__					0xF6E5D4C3

// 这个函数是为了添加新的X节
__INLINE__ PXFILE_SECTION_HEADER __INTERNAL_FUNC__ XFileGetCurrentSectionHeader(__memory pMem, PXFILE_SECTION_HEADER pCurrSectionHeader) {
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL;
	__memory pLocal = NULL;

	// 检验是否存在XFile节
	pXFileNtSectionHeader = XFileExistXFileInPEFile(pMem);
	if (!pXFileNtSectionHeader) return NULL;

	// 获取X文件
	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);

	// 获取当前的末尾节
	pXFileSectionHeader = XFileGetTailSectionInPEFile(pMem);
	if (pXFileSectionHeader) {
		pCurrSectionHeader->dwPointerToRawData = pXFileSectionHeader->dwPointerToRawData + pXFileSectionHeader->dwSizeOfSection;
		pCurrSectionHeader->dwVirtualAddress = pXFileSectionHeader->dwVirtualAddress + pXFileSectionHeader->dwSizeOfSection;
		pCurrSectionHeader->dwOffsetByXFile = pXFileSectionHeader->dwOffsetByXFile + pXFileSectionHeader->dwSizeOfSection;
		pLocal = pMem + pCurrSectionHeader->dwPointerToRawData;
	} else {
		pCurrSectionHeader->dwPointerToRawData = pXFileNtSectionHeader->PointerToRawData + pXFileHeader->dwSizeOfAllHeaders;
		pCurrSectionHeader->dwVirtualAddress = pXFileNtSectionHeader->VirtualAddress + pXFileHeader->dwSizeOfAllHeaders;
		pCurrSectionHeader->dwOffsetByXFile = pXFileHeader->dwSizeOfAllHeaders;
		pLocal = (__memory)pMem + pCurrSectionHeader->dwPointerToRawData;
	}

	return pCurrSectionHeader;
}

#define __XFILE_PREDICT_DEF_SECTION_NAME__				"XTMPSEC"
__bool __API__ XFilePredictNewSectionHeader(__memory pMem, PXFILE_SECTION_HEADER pNewSectionHeader) {
	XFILE_SECTION_HEADER CurrXFileSectionHeader = {0};

	// 检验是否存在XFile节
	if (!XFileExistXFileInPEFile(pMem)) return FALSE;

	// 获取正确的节
	XFileGetCurrentSectionHeader(pMem, &CurrXFileSectionHeader);

	// 产生新的节
	__logic_strcpy__(pNewSectionHeader->szSectionName, __XFILE_PREDICT_DEF_SECTION_NAME__);
	pNewSectionHeader->dwDNA = 0;
	pNewSectionHeader->dwPointerToRawData = CurrXFileSectionHeader.dwPointerToRawData;
	pNewSectionHeader->dwVirtualAddress = CurrXFileSectionHeader.dwVirtualAddress;
	pNewSectionHeader->dwOffsetByXFile = CurrXFileSectionHeader.dwOffsetByXFile;
	pNewSectionHeader->dwSizeOfSection = 0;
	pNewSectionHeader->dwCharacteristics = __XFILE_SECTION_CHARACTERISTICS_USED__;

	return TRUE;
}

PXFILE_SECTION_HEADER __API__ XFileGetFirstSectionInPEFile(__memory pMem) {
	PXFILE_HEADER pXFileHeader = NULL;
	PXFILE_SECTION_HEADER pXFileSectionHeadr = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;

	// 是否存在一个X文件
	pXFileNtSectionHeader = XFileExistXFileInPEFile(pMem);
	if (!pXFileNtSectionHeader) return NULL;

	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);

	// 检验是否存在节
	if (pXFileHeader->dwSectionNumber == 0)
		return NULL;

	pXFileSectionHeadr = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER));

	return pXFileSectionHeadr;
}

PXFILE_SECTION_HEADER __API__ XFileGetTailSectionInPEFile(__memory pMem) {
	PXFILE_HEADER pXFileHeader = NULL;
	PXFILE_SECTION_HEADER pXFileSectionHeadr = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;

	// 是否存在一个X文件
	pXFileNtSectionHeader = XFileExistXFileInPEFile(pMem);
	if (!pXFileNtSectionHeader) return NULL;

	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);

	// 检验是否存在节
	if (pXFileHeader->dwSectionNumber == 0)
		return NULL;

	pXFileSectionHeadr = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * (pXFileHeader->dwSectionNumber - 1)));

	return pXFileSectionHeadr;
}

PIMAGE_SECTION_HEADER __API__ XFileExistXFileInPEFile(__memory pMem) {
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	__integer i = 0;
	__integer j = 0;

	pXFileNtSectionHeader = GetFirstSection(pMem);
	j = GetNumberOfSections(pMem);
	for (i = 0; i < j; i++, pXFileNtSectionHeader++) {
		pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);
		if (__IS_XFILE__(pXFileHeader->dwSign)) 
			return pXFileNtSectionHeader;
	}

	return NULL;
}

__integer __API__ XFileCalcXFileHeaderSize(__dword dwMaxSectionNumber) {
	__integer iAllSectionSize = 0;

	iAllSectionSize = (dwMaxSectionNumber * sizeof(XFILE_SECTION_HEADER)) + sizeof(XFILE_HEADER);
	iAllSectionSize = Alig(iAllSectionSize, __XFILE_ALIGNMENT__, TRUE);

	return iAllSectionSize;
}

__bool __API__ XFileAttachInfoInit(PXFILE_ATTACH_INFO pXFileAttachInfo) {
	__tchar *pTargetFilePath = NULL;
	__tchar *pTargetResourceType = NULL;
	__integer iTargetFileSize = 0;
	__memory pMem = NULL;
	__bool bIsResource = FALSE;
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	//__logic_memset__(pXFileAttachInfo, 0, sizeof(XFILE_ATTACH_INFO));
	pTargetFilePath = pXFileAttachInfo->szTargetFilePath;
	pTargetResourceType = pXFileAttachInfo->szResourceType;
	
	// 设置一些默认值
	if (!pXFileAttachInfo->szResourceType) pXFileAttachInfo->szResourceType = (__tchar *)_T("BIN");
	if (!pXFileAttachInfo->szSectionName) pXFileAttachInfo->szSectionName = (__char *)__XFILE_SECTION_NAME__;
	if (!pXFileAttachInfo->szXSectionName) pXFileAttachInfo->szXSectionName = (__char *)__XFILE_X_SECTION_NAME__;
	if (pXFileAttachInfo->dwDNA == 0) pXFileAttachInfo->dwDNA = __XFILE_BASE_DNA__ + GetRandDword();

	/*
	 * 如果高16位为0则认为是以资源ID打开
	 * 映射文件
	 */
	if (__HiWord__(pTargetFilePath) == 0) {
		__dword dwKey = 0;
		dwKey = pXFileAttachInfo->dwResourceDecodeKey;
		pMem = MapResourceDataEx(NULL, (__word)pTargetFilePath, pTargetResourceType, &iTargetFileSize, dwKey);
		bIsResource = TRUE;
	} else {
		pMem = MappingFile(pTargetFilePath, &iTargetFileSize, TRUE, 0, 0);
		bIsResource = FALSE;
	}
	if (!pMem)
		return FALSE;

	// 判断目标是否是PE文件
	if (!IsValidPE32(pMem)) {
		UnMappingFile(pMem);
		return FALSE;
	}

	pXFileAttachInfo->iFileSize = iTargetFileSize;
	pXFileAttachInfo->iOrigFileSize = iTargetFileSize;
	pXFileAttachInfo->pMem = pMem;
	pXFileAttachInfo->szTargetFilePath = pTargetFilePath;
	pXFileAttachInfo->bUsed = TRUE;
	pXFileAttachInfo->bImageBaseRelocate = (IsDllFile(pMem) || IsDriverFile(pMem));

	{
		// 取得末尾数据
		__integer iTargetTailDataSize = 0;
		__memory pTargetTailData = NULL;
		__memory pTailData = NULL;
		__offset ofTailDataRawOffset = 0;
		PIMAGE_DATA_DIRECTORY pSecurityDataDirectory = NULL;
		__bool bTailDataIsSecurityDataDirectory = FALSE;
		__offset ofSecurityDataDirectoryRawOffsetByTailData = 0;

		iTargetTailDataSize = GetTailDataSize(pMem, iTargetFileSize);
		if (iTargetTailDataSize != 0) {
			pTargetTailData = (__memory)__logic_new_size__(iTargetTailDataSize);
			pTailData = GetTailDataPoint(pMem, iTargetFileSize);
			ofTailDataRawOffset = (__offset)(pTailData - pMem);//末尾数据的文件偏移
			__logic_memcpy__(pTargetTailData, pTailData, iTargetTailDataSize);

			// 确定是否存在证书节
			pSecurityDataDirectory = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_SECURITY);
			if (pSecurityDataDirectory) {
				if (pSecurityDataDirectory->VirtualAddress == ofTailDataRawOffset) {
					bTailDataIsSecurityDataDirectory = TRUE;
					ofSecurityDataDirectoryRawOffsetByTailData = 0;
				} else if (pSecurityDataDirectory->VirtualAddress > ofTailDataRawOffset) {
					bTailDataIsSecurityDataDirectory = TRUE;
					ofSecurityDataDirectoryRawOffsetByTailData = pSecurityDataDirectory->VirtualAddress - ofTailDataRawOffset;
				} else {
					bTailDataIsSecurityDataDirectory = FALSE;
					ofSecurityDataDirectoryRawOffsetByTailData = 0;
				}/* end else */
			}

			// 关闭映射,以没有末尾数据的长度重新映射目标
			if (bIsResource)
				UnMapResourceData(pMem);
			else
				UnMappingFile(pMem);
			iTargetFileSize -= iTargetTailDataSize;

			// 重新设置文件末尾
			ResetFileTail(pTargetFilePath, iTargetFileSize);

			// 重新打开映射
			if (bIsResource) {
				pMem = MapResourceDataSubNewSize(pMem, pXFileAttachInfo->iOrigFileSize, iTargetTailDataSize);
			} else
				pMem = MappingFile(pTargetFilePath, NULL, TRUE, 0, iTargetFileSize);

			// 设置新的X文件附加结构
			if (!pMem) {
				__logic_memset__(pXFileAttachInfo, 0, sizeof(XFILE_ATTACH_INFO));
				return FALSE;
			} else {
				pXFileAttachInfo->pMem = pMem;
				pXFileAttachInfo->iFileSize = iTargetFileSize;
				pXFileAttachInfo->pTailData = pTargetTailData;
				pXFileAttachInfo->iTailDataSize = iTargetTailDataSize;
				pXFileAttachInfo->ofOrigTailDataRawOffset = ofTailDataRawOffset;
				pXFileAttachInfo->bTailDataIsSecurityDataDirectory = bTailDataIsSecurityDataDirectory;//末尾数据是否是证书节
				pXFileAttachInfo->ofSecurityDataDirectoryRawOffsetByTailData = ofSecurityDataDirectoryRawOffsetByTailData;
			}
		}/* end if */
	}

	// 备份原始的PE头
	pNtHdr = GetNtHeader(pXFileAttachInfo->pMem);
	__logic_memcpy__(&(pXFileAttachInfo->OrigTargetNtHeader), pNtHdr, sizeof(IMAGE_NT_HEADERS));

	// 备份原始的引入表
	{
		PIMAGE_DATA_DIRECTORY pImportDataDirectory = ExistDataDirectory(pXFileAttachInfo->pMem, IMAGE_DIRECTORY_ENTRY_IMPORT);
		if (!pImportDataDirectory) {
			// 如果引入表不存在
			pXFileAttachInfo->pOrigImportDescriptor = NULL;
		} else {
			pXFileAttachInfo->pOrigImportDescriptor = (__memory)__logic_new_size__(pImportDataDirectory->Size);
			if (pXFileAttachInfo->pOrigImportDescriptor) {
				__memory pImportData = pXFileAttachInfo->pMem + Rva2Raw(pXFileAttachInfo->pMem, pImportDataDirectory->VirtualAddress);
				__logic_memcpy__(pXFileAttachInfo->pOrigImportDescriptor, pImportData, pImportDataDirectory->Size);
			} else {
				pXFileAttachInfo->pOrigImportDescriptor = NULL;
			}
		}/* end else */
	}

	//// 创建一个傀儡引入表
	//{
	//	__integer iLibCount = CountLibraryInImportTable(pXFileAttachInfo->pMem, TRUE);
	//	PIMAGE_IMPORT_DESCRIPTOR pDummyImportDescriptor = MakeImportDescriptor(pXFileAttachInfo->pMem, iLibCount, 1);

	//}
	

	return TRUE;
}

/*
 * 介绍:
 *	这里的X文件的长度是按照PE文件的对齐粒度对齐的
 */
PIMAGE_SECTION_HEADER __API__ XFileAddXFileToPEFile(PXFILE_ATTACH_INFO pXFileAttachInfo, __integer iSectionSize, __dword dwMaxSectionNumber) {
	__memory pMem = NULL;
	__tchar *szTargetFilePath = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;
	__integer iTargetFileSize = 0;
	__integer iXFileNtSectionSize = 0, iAllSectionSize = 0, iNewTargetFileSize = 0;
	__char *pSectionName = pXFileAttachInfo->szSectionName;

	// 检查参数
	if (dwMaxSectionNumber <= 0) return NULL;
	if (!pXFileAttachInfo->bUsed) return NULL;

	// 获取变量值
	szTargetFilePath = pXFileAttachInfo->szTargetFilePath;
	pMem = pXFileAttachInfo->pMem;
	iTargetFileSize = pXFileAttachInfo->iFileSize;
	
	// 遍历这个PE文件的节,查看是否已经存在X文件
	if (XFileExistXFileInPEFile(pMem))
		return NULL;

	// 计算XFile节总共的大小
	iAllSectionSize = (dwMaxSectionNumber * sizeof(XFILE_SECTION_HEADER)) + sizeof(XFILE_HEADER);
	iAllSectionSize = Alig(iAllSectionSize, __XFILE_ALIGNMENT__, TRUE);
	iXFileNtSectionSize = iAllSectionSize + iSectionSize;
	iXFileNtSectionSize = GetAddSectionMapSize(pMem, iXFileNtSectionSize);

	// 新的映射大小
	iNewTargetFileSize = iTargetFileSize + iXFileNtSectionSize;
	pXFileAttachInfo->iFileSize = iNewTargetFileSize;

	// 重新映射
	UnMappingFile(pMem);
	pMem = (LPBYTE)MappingFile(szTargetFilePath, NULL, TRUE, 0, iNewTargetFileSize);
	if (!pMem) {
		pXFileAttachInfo->bUsed = FALSE;//设定为没有使用
		return NULL;
	}
	pXFileAttachInfo->pMem = pMem;

	// 添加这个新节
	pXFileNtSectionHeader = AddSection(pMem, pSectionName, __DEF_NEWSECTION_CHARACTERISTICS__, iXFileNtSectionSize, NULL, FALSE);
	if (!pXFileNtSectionHeader)
		return NULL;
	
	// 初始化XFILE格式头
	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);
	__logic_memset__(pXFileHeader, 0, iXFileNtSectionSize);
	pXFileHeader->dwSign = __XFILE_SIGN__;
	pXFileHeader->dwVersion = __XFILE_VERSION__;
	pXFileHeader->dwSectionNumber = 0;
	pXFileHeader->dwMaxSectionNumber = dwMaxSectionNumber;
	pXFileHeader->dwXFileSize = iXFileNtSectionSize;
	pXFileHeader->dwAlignment = __XFILE_ALIGNMENT__;
	pXFileHeader->dwXFileNtSectionHdrFileOffset = pXFileNtSectionHeader->PointerToRawData;
	pXFileHeader->dwXFileNtSectionHdrMemoryOffset = pXFileNtSectionHeader->VirtualAddress;
	pXFileHeader->dwSizeOfAllHeaders = iAllSectionSize;

	return pXFileNtSectionHeader;
}

/*
 * 介绍:
 *	在调用AddXFileSectionByXFileHeader之后,使用它的返回值进行调用
 *	这里的X文件的长度是按照X文件内部对齐粒度进行对齐的
 */
PXFILE_HEADER __API__ XFileAddXFileToXFileSection(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_SECTION_HEADER pXFileSectionHeader, __integer iSectionSize, __dword dwMaxSectionNumber) {
	PXFILE_HEADER pXFileHeader = NULL;
	__integer iXFileSectionSize = 0, iAllSectionSize = 0;
	__memory pMem = pXFileAttachInfo->pMem;
	__char *pSectionName = pXFileAttachInfo->szSectionName;

	// 计算XFile节总共的大小
	iAllSectionSize = (dwMaxSectionNumber * sizeof(XFILE_SECTION_HEADER)) + sizeof(XFILE_HEADER);
	iAllSectionSize = Alig(iAllSectionSize, __XFILE_ALIGNMENT__, TRUE);
	iXFileSectionSize = iAllSectionSize + iSectionSize;
	iXFileSectionSize = Alig(iXFileSectionSize, __XFILE_ALIGNMENT__, TRUE);

	// 初始化XFILE格式头
	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileSectionHeader->dwPointerToRawData);
	pXFileHeader->dwSign = __XFILE_SUB_SIGN__;
	pXFileHeader->dwVersion = __XFILE_VERSION__;
	pXFileHeader->dwSectionNumber = 0;
	pXFileHeader->dwMaxSectionNumber = dwMaxSectionNumber;
	pXFileHeader->dwXFileSize = iXFileSectionSize;
	pXFileHeader->dwAlignment = __XFILE_ALIGNMENT__;
	pXFileHeader->dwXFileSectionHdrFileOffset = pXFileSectionHeader->dwPointerToRawData;
	pXFileHeader->dwXFileSectionHdrMemoryOffset = pXFileSectionHeader->dwVirtualAddress;
	pXFileHeader->dwSizeOfAllHeaders = iAllSectionSize;

	return pXFileHeader;
}

PXFILE_SECTION_HEADER __API__ XFileAddXFileSectionByNtSectionHeader(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_SECTION_HEADER pXFileNtSectionHeader, __integer iSectionSize, __dword dwCharacteristics, __dword dwEx1, __dword dwEx2) {
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL, pXFileLastSectionHeader = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	__memory pLocal = NULL;
	__dword dwSectionSize = 0;
	__memory pMem = NULL;
	__tchar *szTargetFilePath = NULL;
	__integer iTargetFileSize = 0;
	__offset ofRvaLocal = 0;
	XFILE_SECTION_HEADER CurrXFileSectionHeader = {0};
	__char *pSectionName = NULL;
	__dword dwDNA = 0;

	// 默认设定为内存足够
	__bool bEnoughMemory = TRUE;

	// 检查
	if (!pXFileAttachInfo->bUsed)
		return NULL;
	pMem = pXFileAttachInfo->pMem;
	szTargetFilePath = pXFileAttachInfo->szTargetFilePath;
	iTargetFileSize = pXFileAttachInfo->iFileSize;
	pSectionName = pXFileAttachInfo->szXSectionName;
	dwDNA = pXFileAttachInfo->dwDNA;

	// 获取X文件
	pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);

	// 判断是否是X标志
	if (!__IS_XFILE__(pXFileHeader->dwSign))
		return NULL;

	// 检查是否已经到了最大的节数目
	if (pXFileHeader->dwSectionNumber >= pXFileHeader->dwMaxSectionNumber)
		return NULL;

	// 计算节以对齐粒度的长度
	dwSectionSize = Alig(iSectionSize, pXFileHeader->dwAlignment, TRUE);

	// 获取新节头位置
	pXFileSectionHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * pXFileHeader->dwSectionNumber));

	// 计算当前节
	XFileGetCurrentSectionHeader(pMem, &CurrXFileSectionHeader);

	if (pXFileHeader->dwSectionNumber != 0) {
		pXFileLastSectionHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * (pXFileHeader->dwSectionNumber - 1)));
	} else {
		pXFileLastSectionHeader = NULL;
	}

	// 判断当前映射是否有足够的长度容纳新节
	//bEnoughMemory = TRUE;//默认为TRUE
	if (pXFileLastSectionHeader) {
		if ((pXFileLastSectionHeader->dwOffsetByXFile + pXFileLastSectionHeader->dwSizeOfSection + dwSectionSize)  > pXFileHeader->dwXFileSize)
			bEnoughMemory = FALSE;
	} else if ((pXFileHeader->dwSizeOfAllHeaders + dwSectionSize) > pXFileHeader->dwXFileSize) {
		bEnoughMemory = FALSE;
	}

	// 如果没有足够的内存
	if (!bEnoughMemory) {
		__integer iNewSectionSize = 0;

		// 核算新末尾节的长度
		//iNewSectionSize = pXFileLastSectionHeader->dwOffsetByXFile + pXFileLastSectionHeader->dwSizeOfSection + dwSectionSize;
		iNewSectionSize = CurrXFileSectionHeader.dwOffsetByXFile + dwSectionSize;

		// 扩展末尾节
		pXFileNtSectionHeader = CoverTailSection(szTargetFilePath, &pMem, iNewSectionSize, NULL, 0, &iTargetFileSize);
		if (!pXFileNtSectionHeader)
			return NULL;

		// 重新设定附加信息
		pXFileAttachInfo->bUsed = TRUE;
		pXFileAttachInfo->pMem = pMem;
		pXFileAttachInfo->iFileSize = iTargetFileSize;
		pXFileAttachInfo->szTargetFilePath = szTargetFilePath;

		// 重新定位到X文件,并重新设定尺寸
		pXFileHeader = (PXFILE_HEADER)(pMem + pXFileNtSectionHeader->PointerToRawData);
		pXFileHeader->dwXFileSize = pXFileNtSectionHeader->SizeOfRawData;

		// 计算新的X当前要添加的节以及新的X末尾节位置
		pXFileSectionHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * pXFileHeader->dwSectionNumber));
		pXFileLastSectionHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * (pXFileHeader->dwSectionNumber - 1)));
	}/* end if */

	// 填充节头信息
	__logic_strcpy__(pXFileSectionHeader->szSectionName, pSectionName);
	pXFileSectionHeader->dwDNA = dwDNA;
	pXFileSectionHeader->dwPointerToRawData = CurrXFileSectionHeader.dwPointerToRawData;
	pXFileSectionHeader->dwVirtualAddress = CurrXFileSectionHeader.dwVirtualAddress;
	pXFileSectionHeader->dwOffsetByXFile = CurrXFileSectionHeader.dwOffsetByXFile;
	pXFileSectionHeader->dwSizeOfSection = dwSectionSize;
	pXFileSectionHeader->dwCharacteristics = dwCharacteristics | __XFILE_SECTION_CHARACTERISTICS_USED__;

	// 如果是PE文件切是通过内存对齐的
	if ((dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE__) && (!(dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE_FILE_ALIGN__)))
	{
		pXFileSectionHeader->ofMemImageBaseOffset = (__offset)dwEx1;
		// 计算出自定义数据区域离目标文件的RVA
		{
			__dword delta = 0;
			// 得到自身PE映射的基地址
			delta = pXFileSectionHeader->dwVirtualAddress + pXFileSectionHeader->ofMemImageBaseOffset;
			pXFileSectionHeader->dwCustomDataRVA = dwEx2 + delta;
		}
	}

	// 增加XFILE节数量
	(pXFileHeader->dwSectionNumber)++;

	return pXFileSectionHeader;
}

/*
 * 介绍:
 *	通过一个X文件增加一个X节,与通过NT节头添加X节不同,后者是添加主X节,可以使用扩展末尾节的方式自动扩展节的大小
 *	而这个函数则不行,因为X文件本身是固定的
 */
PXFILE_SECTION_HEADER __API__ XFileAddXFileSectionByXFileHeader(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_HEADER pXFileHeader, __integer iSectionSize, __dword dwCharacteristics, __dword dwEx1, __dword dwEx2) {
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL;
	__memory pLocal = NULL;
	__dword dwSectionSize = 0;
	__offset ofRvaLocal = 0;
	XFILE_SECTION_HEADER CurrXFileSectionHeader = {0};
	__memory pMem = pXFileAttachInfo->pMem;
	__char *pSectionName = pXFileAttachInfo->szXSectionName;
	__dword dwDNA = pXFileAttachInfo->dwDNA;

	// 判断是否是X标志
	if (!__IS_XFILE__(pXFileHeader->dwSign))
		return NULL;

	// 检查是否已经到了最大的节数目
	if (pXFileHeader->dwSectionNumber >= pXFileHeader->dwMaxSectionNumber)
		return NULL;

	// 计算节以对齐粒度的长度
	dwSectionSize = Alig(iSectionSize, pXFileHeader->dwAlignment, TRUE);

	// 计算当前节
	XFileGetCurrentSectionHeader(pMem, &CurrXFileSectionHeader);

	// 判断当前映射是否有足够的长度容纳新节
	//bEnoughMemory = TRUE;//默认为TRUE
	if (CurrXFileSectionHeader.dwOffsetByXFile + dwSectionSize > pXFileHeader->dwXFileSize)
		return NULL;

	// 获取新节头位置
	pXFileSectionHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER) + (sizeof(XFILE_SECTION_HEADER) * pXFileHeader->dwSectionNumber));

	// 填充节头信息
	__logic_strcpy__(pXFileSectionHeader->szSectionName, pSectionName);
	pXFileSectionHeader->dwDNA = dwDNA;
	pXFileSectionHeader->dwPointerToRawData = CurrXFileSectionHeader.dwPointerToRawData;
	pXFileSectionHeader->dwVirtualAddress = CurrXFileSectionHeader.dwVirtualAddress;
	pXFileSectionHeader->dwOffsetByXFile = CurrXFileSectionHeader.dwOffsetByXFile;
	pXFileSectionHeader->dwSizeOfSection = dwSectionSize;
	pXFileSectionHeader->dwCharacteristics = dwCharacteristics | __XFILE_SECTION_CHARACTERISTICS_USED__;

	// 如果是PE文件切是通过内存对齐的
	if ((dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE__) && (!(dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE_FILE_ALIGN__)))
	{
		pXFileSectionHeader->ofMemImageBaseOffset = (__offset)dwEx1;
		// 计算出自定义数据区域离目标文件的RVA
		{
			__dword delta = 0;
			// 得到自身PE映射的基地址
			delta = pXFileSectionHeader->dwVirtualAddress + pXFileSectionHeader->ofMemImageBaseOffset;
			pXFileSectionHeader->dwCustomDataRVA = dwEx2 + delta;
		}
	}

	// 增加XFILE节数量
	(pXFileHeader->dwSectionNumber)++;

	return pXFileSectionHeader;
}

__void __API__ XFileReleaseXFileAttach(PXFILE_ATTACH_INFO pData) {
	__bool bResource = FALSE;
	PIMAGE_NT_HEADERS pNtHdr = NULL;

	if (!pData->bUsed)
		return;

	if (HIWORD(pData->szTargetFilePath) == 0)
		bResource = TRUE;
	else
		bResource = FALSE;

	// 复制末尾数据
	if (pData->bKeepTailData) {
		if (pData->iTailDataSize != 0) {
			// 关闭映射,并以新的长度打开映射
			if (bResource)
				UnMapResourceData(pData->pMem);
			else
				UnMappingFile(pData->pMem);

			// 重新打开映射
			if (bResource) {
				pData->pMem = MapResourceDataPlusNewSize(pData->pMem, pData->iFileSize, pData->iTailDataSize);
			} else {
				pData->pMem = MappingFile(pData->szTargetFilePath, NULL, TRUE, 0, pData->iFileSize + pData->iTailDataSize);
			}
			if (!pData->pMem) {
				return;
			}
			__logic_memcpy__(pData->pMem + pData->iFileSize, pData->pTailData, pData->iTailDataSize);
			pData->iFileSize += pData->iTailDataSize;

			// 设置证书节相关
			if (pData->bTailDataIsSecurityDataDirectory) {
				PIMAGE_DATA_DIRECTORY pSecurityDataDirectory = NULL;

				// 安全证书节是否存在
				pSecurityDataDirectory = ExistDataDirectory(pData->pMem, IMAGE_DIRECTORY_ENTRY_SECURITY);
				if (pSecurityDataDirectory) {
					__memory pTailData = NULL;

					pTailData = GetTailDataPoint(pData->pMem, pData->iFileSize);
					pSecurityDataDirectory->VirtualAddress = pTailData - pData->pMem + pData->ofSecurityDataDirectoryRawOffsetByTailData;//偏移的修订
				}
			}/* end if */
		}/* end if */
	}

	// 获取NT头
	pNtHdr = GetNtHeader(pData->pMem);

	// 检查是否需要关闭DEP兼容
	if (pData->bCloseNX)
		pNtHdr->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_NX_COMPAT;

	// 检查是否需要关闭随机地址化映射,如果是DLL则忽略此设置
	if ((pData->bCloseRandAddressMap) && (!pData->bImageBaseRelocate))
		pNtHdr->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;

	// 设置所有节为可写
	if (pData->bSetAllSectionCanWrite)
		SetAllSectionCanWrite(pData->pMem);

	// 随机所有节名
	if (pData->bRandomAllSectionName)
		RandomAllSectionName(pData->pMem);

	// 删除指定的数据目录
	{
		__integer n = 0;
		for (n = 0; n < 0x10; n++)
			if (pData->bWillDelDataDirectoryIndexs[n]) DeleteDataDirectoryObject(pData->pMem, n);
	}

	// 是否重新计算目标的校验和
	if (pData->bResetCheckSum)
		RefixCheckSum(pData->pMem, pData->iFileSize);
	else 
		RefixCheckSum(pData->pMem, 0);

	// 提高兼容性附加
	if (pData->bCompatibility) {
		// 删除绑定引入表
		DeleteDataDirectoryObject(pData->pMem, IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT);
		// 删除引入地址表
		DeleteDataDirectoryObject(pData->pMem, IMAGE_DIRECTORY_ENTRY_IAT);
	}

	// 保留引入表中的一些数据提高兼容性
	if (pData->bKeepSameOrigImpLib) {
		if (pData->pOrigImportDescriptor) {

		}/* end if */
	}

	// 关闭映射
	if (bResource) {
		UnMapResourceData(pData->pMem);
	} else {
		UnMappingFile(pData->pMem);
	}

	// 释放末尾数据的内存
	if (pData->pTailData) __logic_delete__(pData->pTailData);
	
	// 释放备份的引入表数据
	if (pData->pOrigImportDescriptor) __logic_delete__(pData->pOrigImportDescriptor);

	// 清空X文件附加结构
	__logic_memset__(pData, 0, sizeof(XFILE_ATTACH_INFO));
}

__bool __API__ XFileInThisXFileSection(PXFILE_SECTION_HEADER pSectH, __offset ofOffset, __bool bRva) {
	return (bRva ? (ofOffset >= (__offset)(pSectH->dwVirtualAddress)) && (ofOffset < (__offset)(pSectH->dwVirtualAddress + pSectH->dwSizeOfSection)) :
		(ofOffset >= (__offset)(pSectH->dwPointerToRawData)) && (ofOffset < (__offset)(pSectH->dwPointerToRawData + pSectH->dwSizeOfSection)));

}

PXFILE_SECTION_HEADER __API__ XFileGetXFileSectionHeaderByOffset(PXFILE_HEADER pXFileHeader, __offset ofOffset, __bool bRva) {
	PXFILE_SECTION_HEADER pHeader = NULL, pRet = NULL;
	__integer i = 0;

	pHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER));
	for (i = 0; i < pXFileHeader->dwSectionNumber; pHeader++, i++) {
		if (XFileInThisXFileSection(pHeader, ofOffset, bRva)) {
			pRet = pHeader;
			break;
		}
	}

	return pRet;
}

PXFILE_SECTION_HEADER __API__ XFileGetXFileSectionHeaderByDNA(__memory pMem, PXFILE_HEADER pXFileHeader, __dword dwDNA, __bool bFile, PXFILE_SECTION_HEADER *pXFatherSectionHdrPoint) {
	PXFILE_SECTION_HEADER pHeader = NULL, pRet = NULL;
	__integer i = 0;

	// 遍历当前映射的XFILE节
	// 如果pRet不为空则表示已经找到
	pHeader = (PXFILE_SECTION_HEADER)((__memory)pXFileHeader + sizeof(XFILE_HEADER));
	for (i = 0; i < (pXFileHeader->dwSectionNumber && !pRet); pHeader++, i++) {
		if (pHeader->dwDNA == dwDNA) {
			// 如果匹配到DNA直接返回
			return pHeader;
		} else if (pHeader->dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_X__ == __XFILE_SECTION_CHARACTERISTICS_X__) {
			// 如果是XFILE节,则直接进行递归
			PXFILE_HEADER pSubXFileHeader = NULL;

			// 获取子X文件头节
			pSubXFileHeader = (PXFILE_HEADER)((bFile) ? pMem + pHeader->dwPointerToRawData : pMem + pHeader->dwVirtualAddress);
			
			// 递归进入查找
			pRet = XFileGetXFileSectionHeaderByDNA(pMem, pSubXFileHeader, dwDNA, bFile, pXFatherSectionHdrPoint);
			if (pRet) return pRet;
		} else if (pHeader->dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE__ == __XFILE_SECTION_CHARACTERISTICS_PE__) {
			// 如果此XFILE节是PE文件则进去此PE文件内部进行遍历节操作
			__memory pImage = NULL;
			PIMAGE_NT_HEADERS pNtHdr = NULL;
			PIMAGE_SECTION_HEADER pSecHdr = NULL;
			__integer j = 0;

			// 获取当前PE文件的映射,如果是PE文件是使用内存对齐,则这里进行基地址对齐操作
			pImage = (bFile) ? pMem + pHeader->dwPointerToRawData : pMem + pHeader->dwVirtualAddress + pHeader->ofMemImageBaseOffset;

			// 获取NT头
			pNtHdr = GetNtHeader(pImage);

			// 找到这个PE文件的XFILE节
			pSecHdr = GetFirstSection(pImage);
			for (j = 0; (j < (pNtHdr->FileHeader).NumberOfSections && !pRet) ; pSecHdr++, j++) {
				__memory pSec = NULL;
				PXFILE_HEADER pXSec  = NULL;
				__bool bOnFileAlign = FALSE;

				// 判断此PE是否是文件对齐还是内存对齐
				if (pHeader->dwCharacteristics & __XFILE_SECTION_CHARACTERISTICS_PE_FILE_ALIGN__ == __XFILE_SECTION_CHARACTERISTICS_PE_FILE_ALIGN__) {
					pSec = pImage + pSecHdr->PointerToRawData + pHeader->ofMemImageBaseOffset;
					bOnFileAlign = TRUE;
				} else {
					pSec = pImage + pSecHdr->VirtualAddress + pHeader->ofMemImageBaseOffset;
					bOnFileAlign = FALSE;
				}

				pXSec = (PXFILE_HEADER)pSec;
				// 判断此节是否是XFILE节
				if (__IS_XFILE__(pXSec->dwSign)) {
					// 进行递归操作
					*pXFatherSectionHdrPoint = pHeader;//设置父X节
					pRet = XFileGetXFileSectionHeaderByDNA(pImage, pXSec, dwDNA, bOnFileAlign, pXFatherSectionHdrPoint);
					if (pRet) return pRet;
				}/* end if */
			}/* end for */
		}/* end else if */

		// ...
	}

	return NULL;
}
