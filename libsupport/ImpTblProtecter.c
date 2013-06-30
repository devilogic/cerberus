/*
 * 介绍:
 *	确定一个CRC32是否在列表内
 *
 * 参数:
 *	dwTargetCrc32:目标的CRC32值
 *	pCrc32List:CRC32的值列表
 *	iCrc32ListCount:CRC32的计数
 */
__INLINE__ __bool __INTERNAL_FUNC__ ThisValueIsInList(__dword dwTargetCrc32, __dword *pCrc32List, __integer iCrc32ListCount) {
	__integer i;
	for (i = 0; i < iCrc32ListCount; i++) {
		if (dwTargetCrc32 == pCrc32List[i])
			return TRUE;
	}
	return FALSE;
}

/*
 * 介绍:
 *	初始化引入表保护器
 */
__void __API__ InitImportProtecter() {
	__dword dwCrc32 = 0;
	HMODULE hKernel32 = NULL;

	__PrintDbgInfo_OutputDbgString__("Entry InitImportProtecter");

	// 获取kernel32的基地址
	__PrintDbgInfo_OutputDbgString__("Get kernel32 base address");
	hKernel32 = GetKernel32BaseAddress();

	// 获取pVirtualAlloc的地址
	__PrintDbgInfo_OutputDbgString__("Get VirtualAlloc address");
	dwCrc32 = __CRC32_VIRTUALALLOC_STR__;
	g_pVirtualAlloc = (FPVirtualAlloc)xGetProcAddressImmediatelyByHash(hKernel32, (__memory)(&dwCrc32), sizeof(__dword), GetApiAddress_Crc32HashFunc);

	// 重映射kernel32.dll
	__PrintDbgInfo_OutputDbgString__("Remap kernel32 map");
	hKernel32 = (HMODULE)RemapDll((__memory)hKernel32, g_pVirtualAlloc, FALSE);//这里也是唯一可以被断点进攻的地方

	//////////////////////////////////////////////////////////////////////////
	// 获取所需的支持API地址
	__PrintDbgInfo_OutputDbgString__("Reget VirtualAlloc address");
	dwCrc32 = __CRC32_VIRTUALALLOC_STR__;
	g_pVirtualAlloc = (FPVirtualAlloc)xGetProcAddressImmediatelyByHash(hKernel32, (__memory)(&dwCrc32), sizeof(__dword), GetApiAddress_Crc32HashFunc);

	__PrintDbgInfo_OutputDbgString__("Get LoadLibraryA address");
	dwCrc32 = __CRC32_LOADLIBRARYA_STR__;
	g_pLoadLibraryA = (FPLoadLibraryA)xGetProcAddressImmediatelyByHash(hKernel32, (__memory)(&dwCrc32), sizeof(__dword), GetApiAddress_Crc32HashFunc);


	// 退出
	__PrintDbgInfo_OutputDbgString__("Exit InitImportProtecter");
}

//////////////////////////////////////////////////////////////////////////
// 以下为加解密引入表保护器的相关实现
// 加密密钥,使用简单的异或算法
__INLINE__ __void __INTERNAL_FUNC__ XorKey4Bytes(__memory pKey, __byte bXor) {
	__integer i = 0;
	for (i = 0; i < 4; i++)
		pKey[i] = pKey[i] ^ bXor;
}

/*
 * 介绍:
 *	加密引入表的回调函数
 *
 * 参数:
 *	iIndex:要加密函数的的ID号
 *	Type:加密的类型,表明当前是动态库,还是API
 *	pData:要加密的数据,根据Type不同而不同
 *	iDataSize:数据的长度
 *	bOrd:如果Type = PROC_NAME,如果此字段为FALSE,则表示是一个以索引引出的函数
 *	dwFirstThunk:引入表中的FirstThunk值
 *	pArgs:自定义的数据指针
 */
__void __INTERNAL_FUNC__ EncryptIATCallBack(__integer iIndex, CRYPTIAT_TYPE Type, __memory pData, __integer iDataSize, __bool bOrd, __dword dwFirstThunk, __void *pArgs) {
	PIMPORT_PROTECT pImportProtect = (PIMPORT_PROTECT)pArgs;

	if (Type == LIB_NAME) {
		__char szLibName[128] = {0};
		__memory pKey = NULL;
		__dword dwKey = GenerateRandomNumber();//随机获取一个KEY
		pImportProtect->iLibraryNameLengthList[iIndex] = iDataSize;

		// 转换库名为小写
		__logic_strcpy__(szLibName, pData);
		__logic_str2lower__(szLibName);
		XorArray(dwKey, (__memory)szLibName, (__memory)pImportProtect->LibraryNameList[iIndex], iDataSize);//加密
		pKey = (__memory)&dwKey;//加密密钥
		XorKey4Bytes(pKey, pImportProtect->bXor);
		pImportProtect->dwLibraryKeyList[iIndex] = dwKey;
		(pImportProtect->iLibraryKeyCount)++;
	} else if (Type == PROC_NAME) {
		pImportProtect->bIsOrdList[iIndex] = bOrd;
		if (bOrd == FALSE) {
			__dword dwCrc32 = crc32(pData, iDataSize);
			__memory pCrc32 = (__memory)&dwCrc32;
			pImportProtect->dwApiNameCrc32List[iIndex] = dwCrc32;
		} else {
			pImportProtect->dwApiNameCrc32List[iIndex] = *(__dword *)pData;
			pImportProtect->dwApiNameCrc32List[iIndex] &= 0xFFFF;// 设置高2字节为0
		}
		pImportProtect->dwFirstThunkList[iIndex] = dwFirstThunk;//记录FirstThunk的值
		(pImportProtect->iApiNameCrc32Count)++;
	}/* end else */
}

// 解密器所需的哈希函数
__dword __INTERNAL_FUNC__ DecrypterHashFunc(__memory pTarget, __integer iTargetSize, __memory pHashValue) {
	__memory pDecryptData = NULL;
	__dword dwDecryptSize = 0;
	__dword dwCrc32 = crc32(pTarget, iTargetSize);
	__logic_memcpy__(pHashValue, &dwCrc32, sizeof(__dword));
	return sizeof(__dword);
}

// 解密引入表
__void __INTERNAL_FUNC__ DecryptIATCallBack(__integer iIndex, CRYPTIAT_TYPE Type, __memory pData, __integer iDataSize, __bool bOrd, __dword dwFirstThunk, __void *pArgs) {
	PIMPORT_PROTECT pImportProtect = (PIMPORT_PROTECT)pArgs;
	__dword dwLibNameCrc32 = 0;
	__bool bDllIsProtect = FALSE;

	if (Type == LIB_NAME) {
		__integer iLength = 0;
		__char pLibName[64] = {0};
		__dword dwKey = pImportProtect->dwLibraryKeyList[iIndex];//解密密钥
		__memory pKey = (__memory)&dwKey;
		HMODULE hDll;
		XorKey4Bytes(pKey, pImportProtect->bXor);
		iLength = pImportProtect->iLibraryNameLengthList[iIndex];
		__logic_memcpy__(pLibName, pData, iLength);
		XorArray(dwKey, (__memory)pLibName, (__memory)pLibName, iLength);//解密
		hDll = g_pLoadLibraryA(pLibName);

		dwLibNameCrc32 = crc32((__memory)pLibName, iLength);

		// 重映射DLL
		if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCrc32List, pImportProtect->iProtectDllCrc32Count)) {
			// 查看是否是排除在执行DllMain的库
			if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCallDllMainCrc32List, pImportProtect->iProtectDllCallDllMainCrc32Count))
				hDll = (HMODULE)RemapDll((__memory)hDll, g_pVirtualAlloc, TRUE);
			else
				hDll = (HMODULE)RemapDll((__memory)hDll, g_pVirtualAlloc, FALSE);

			// 设置此DLL经过保护
			bDllIsProtect = TRUE;
		} else {
			// 设置此DLL未经过保护
			bDllIsProtect = FALSE;
		}

		// 设置为当前DLL
		pImportProtect->hDll = hDll;
	} else if (Type == PROC_NAME) {
		__memory pHashData = (__memory)&(pImportProtect->dwApiNameCrc32List[iIndex]);
		__address addrImageBase = pImportProtect->addrImageBase;
		__address *paddrOut = (__address *)(addrImageBase + (__address)dwFirstThunk);
		if (pImportProtect->bIsOrdList[iIndex]) {
			__dword dwOrd = pImportProtect->dwApiNameCrc32List[iIndex];
			*paddrOut = (__address)xGetProcAddressByHash(pImportProtect->hDll, (__memory)&dwOrd, 2, DecrypterHashFunc);
		} else
			*paddrOut = (__address)xGetProcAddressByHash(pImportProtect->hDll, pHashData, sizeof(__address), DecrypterHashFunc);
	}/* end else */
}

/*
 * 介绍:
 *	解密引入表
 *
 * 参数:
 *	pImageBase:基地址
 *	pImportProtect:引入表保护结构指针
 *	bOnFile:是否在一个文件上做这个操作
 *	pOutImportTable:输出新的引入表
 */
__bool __API__ EncryptImportTable(__memory pImageBase, PIMPORT_PROTECT pImportProtect, __bool bOnFile, __memory pOutImportTable) {
	__byte bXor = 0;
	__integer iProcCount = 0, iLibCount = 0, iIndex = 0;
	__address addrImageBase = 0;
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_DATA_DIRECTORY pImageImportDataDirectory = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = NULL;
	__integer iImportTableSize = 0;
	__dword dwFirstThunk = 0;
	__memory pMem = pImageBase;//设置内存基地址

	// 初始化数据
	pImageImportDataDirectory = ExistDataDirectory(pImageBase, IMAGE_DIRECTORY_ENTRY_IMPORT);
	if (!pImageImportDataDirectory)
		return NULL;

	pNtHdr = GetNtHeader(pImageBase);
	if (bOnFile)
		addrImageBase = (__address)(pNtHdr->OptionalHeader.ImageBase);
	else
		addrImageBase = (__address)pMem;

	if (bOnFile)
		pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(pMem + Rva2Raw(pMem, pImageImportDataDirectory->VirtualAddress));
	else
		pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)__RvaToVa__(addrImageBase, pImageImportDataDirectory->VirtualAddress);

	// 设置IMAGE_PROTECT
	bXor = (__byte)GenerateRandomNumber();//随机生成出一个KEY
	pImportProtect->bXor = bXor;

	// 将引入表信息存入IMPORT_PROTECT结构
	// 有些程序只适用FirstThunk
	while (pImageImportDescriptor->FirstThunk) {
		__address addrCurrAddress = 0;
		__dword dwCurrRva = 0;
		__char *svDllName = NULL;
		PIMAGE_THUNK_DATA pTdIn = NULL;
		PIMAGE_THUNK_DATA pTdOut = NULL;
		if (bOnFile)
			svDllName = (__char *)(pMem + Rva2Raw((__void *)pMem, pImageImportDescriptor->Name));
		else
			svDllName = (__char *)__RvaToVa__(addrImageBase, pImageImportDescriptor->Name);

		EncryptIATCallBack(iLibCount, LIB_NAME, (__memory)svDllName, __logic_strlen__(svDllName), FALSE, 0, (__void *)pImportProtect);

		// 填充引入表地址
		if (bOnFile) {
			pTdIn = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw((__void *)pMem, pImageImportDescriptor->OriginalFirstThunk));
			pTdOut = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw((__void *)pMem, pImageImportDescriptor->FirstThunk));
			// 没有OriginalFirstThunk的情况
			if ((__memory)pTdIn == pMem)
				pTdIn = pTdOut;
		} else {
			pTdIn = (PIMAGE_THUNK_DATA)__RvaToVa__(addrImageBase, pImageImportDescriptor->OriginalFirstThunk);
			pTdOut = (PIMAGE_THUNK_DATA)__RvaToVa__(addrImageBase, pImageImportDescriptor->FirstThunk);
			// 没有OriginalFirstThunk的情况
			if ((__address)pTdIn == addrImageBase)
				pTdIn = pTdOut;
		}

		iProcCount = 0;
		// 加密函数
		while (pTdIn->u1.Function) {

			dwFirstThunk = (__dword)((__address)pTdOut - addrImageBase);

			// 以序号引出还是以函数名引出
			if (pTdIn->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
				__word wOrd = pTdIn->u1.Ordinal;
				EncryptIATCallBack(iIndex, PROC_NAME, (__memory)&wOrd, 2, TRUE, dwFirstThunk, (__void *)pImportProtect);
			} else {
				__char *szProcName = NULL;
				PIMAGE_IMPORT_BY_NAME pIbn = NULL;
				if (bOnFile)
					pIbn = (PIMAGE_IMPORT_BY_NAME)(pMem + Rva2Raw((__memory)pMem, pTdIn->u1.AddressOfData));
				else
					pIbn = (PIMAGE_IMPORT_BY_NAME)__RvaToVa__(addrImageBase, pTdIn->u1.AddressOfData);
				szProcName = (__char *)(pIbn->Name);
				EncryptIATCallBack(iIndex, PROC_NAME, (__memory)szProcName, __logic_strlen__(szProcName), FALSE, dwFirstThunk, (__void *)pImportProtect);
			}
			// 下一个函数
			addrCurrAddress += sizeof(__address);
			iProcCount++;//函数计数增加
			iIndex++;//API索引计数增加
			pTdIn++;
			pTdOut++;
		}/* end while */

		// 在下一个DLL之前,记录当前库所有的API数量
		pImportProtect->iApiNumberInThisLibrary[iLibCount] = iProcCount;
		// 下一个DLL
		pImageImportDescriptor++;
		iLibCount++;
	}/* end while */

	// 检查加密函数的个数是否统一
	if (iIndex != pImportProtect->iApiNameCrc32Count)
		return FALSE;

	// 复制引入表
	iImportTableSize = pImageImportDataDirectory->Size;//引入表长度
	if (pOutImportTable) {
		__logic_memcpy__(pOutImportTable, (__memory)pImageImportDescriptor, iImportTableSize);
	}

	__logic_memset__((__memory)pImageImportDescriptor, 0, iImportTableSize);//清除原先的引入表
	return TRUE;
}

/*
 * 介绍:
 *	清除重映射DLL后的不安全的信息
 */
__INLINE__ __void __INTERNAL_FUNC__ ClearRemapDllUnSafeInfo(__memory pDll) {
	PIMAGE_DOS_HEADER pDosHdr = NULL;
	PIMAGE_NT_HEADERS pNtHdr = NULL;

	// 获取PE头
	pDosHdr = (PIMAGE_DOS_HEADER)pDll;
	pNtHdr = GetNtHeader(pDll);
	
	// 清除映射的引出表, 引入表, 调试表, 重定位表, 与PE头
	DeleteDataDirectoryObjectOnMemMap(pDll, IMAGE_DIRECTORY_ENTRY_EXPORT);
	DeleteDataDirectoryObjectOnMemMap(pDll, IMAGE_DIRECTORY_ENTRY_IMPORT);
	//DeleteDataDirectoryObjectOnMemMap(pDll, IMAGE_DIRECTORY_ENTRY_DEBUG);
	//DeleteDataDirectoryObjectOnMemMap(pDll, IMAGE_DIRECTORY_ENTRY_BASERELOC);
	// 清楚DOS头,PE头
	__logic_memset__((__memory)pDosHdr, 0, sizeof(IMAGE_DOS_HEADER));
	__logic_memset__((__memory)pNtHdr, 0, sizeof(IMAGE_NT_HEADERS));
}

/*
 * 介绍:
 *	解密引入表
 *
 * 参数:
 *	pImportProtect:引入表保护结构
 */
__bool __API__ DecryptImportTable(PIMPORT_PROTECT pImportProtect) {
	__byte bXor = 0;
	HMODULE hDll = 0, hCurrDll = 0;
	__integer i = 0, j = 0, iIndex = 0;
	__integer iLength = 0;
	__char *pLibName = NULL;
	__char LibName[64] = {0};
	__dword dwLibNameCrc32 = 0;
	__bool bDllIsProtect = FALSE;

	__PrintDbgInfo_OutputDbgString__("Entry DecryptImportTable");

	bXor = pImportProtect->bXor;//获取密钥的解密密码
	for (i = 0; i < pImportProtect->iLibraryKeyCount; i++) {
		__dword dwKey = pImportProtect->dwLibraryKeyList[i];//解密密钥
		__memory pKey = (__memory)&dwKey;
		XorKey4Bytes(pKey, bXor);
		iLength = pImportProtect->iLibraryNameLengthList[i];
		__logic_memset__(LibName, 0, 64);
		pLibName = pImportProtect->LibraryNameList[i];
		XorArray(dwKey, (__memory)pLibName, (__memory)LibName, iLength);//解密
		hCurrDll = g_pLoadLibraryA(LibName);

		// 重映射DLL
		dwLibNameCrc32 = crc32((__memory)pLibName, iLength);

		// 重映射DLL
		if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCrc32List, pImportProtect->iProtectDllCrc32Count)) {
			// 查看是否是排除在执行DllMain的库
			if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCallDllMainCrc32List, pImportProtect->iProtectDllCallDllMainCrc32Count))
				hDll = (HMODULE)RemapDll((__memory)hCurrDll, g_pVirtualAlloc, TRUE);
			else
				hDll = (HMODULE)RemapDll((__memory)hCurrDll, g_pVirtualAlloc, FALSE);

			// 设置此DLL经过保护
			bDllIsProtect = TRUE;
		} else {
			hDll = hCurrDll;

			// 设置此DLL未经过保护
			bDllIsProtect = FALSE;
		}

		// 获取API地址
		for (j = 0; j < pImportProtect->iApiNumberInThisLibrary[i]; j++) {
			__memory pHashData = (__memory)&(pImportProtect->dwApiNameCrc32List[iIndex]);
			__address addrImageBase = pImportProtect->addrImageBase;
			__dword dwFirstThunk = pImportProtect->dwFirstThunkList[iIndex];
			__address *paddrOut = (__address *)(addrImageBase + (__address)dwFirstThunk);
			if (pImportProtect->bIsOrdList[iIndex]) {
				__dword dwOrd = pImportProtect->dwApiNameCrc32List[iIndex];
				*paddrOut = (__address)xGetProcAddressByHash(hDll, (__memory)&dwOrd, 2, DecrypterHashFunc);
			} else
				*paddrOut = (__address)xGetProcAddressByHash(hDll, pHashData, sizeof(__address), DecrypterHashFunc);

			// 增加索引计数
			iIndex++;
		}/* end for */

		// 检验
		if (iIndex != pImportProtect->iApiNameCrc32Count)
			return FALSE;

		// 如果是被保护的则清除这个DLL的无用信息
		if (bDllIsProtect) {
			__PrintDbgInfo_OutputDbgString__("Already go to ClearRemapDllUnSafeInfo");
			ClearRemapDllUnSafeInfo((__memory)hDll);
		}
	}

	// 退出
	__PrintDbgInfo_OutputDbgString__("Exit DecryptImportTable");
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 以下组件与模块是力量引入表保护器独有的

/*
 * 介绍:
 *	我们要在内存中建立一个自己的引入表,类似真实编译器编译的跳转表
 *	jmp dword ptr [xxx]
 *	jmp dword ptr [yyy]
 *	jmp dword ptr [zzz]
 *	这个函数的作用就是传入一个布尔队列
 *
 * 参数:
 *	pJmpAddressTableMakeSure:
 */
__INLINE__ __integer __INTERNAL_FUNC__ RandJmpAddress(__bool *pJmpAddressTableMakeSure) {
	__integer iIndex = 0;
	
	do {
		iIndex = GenerateRandomNumber() % __MAX_JMP_ADDRESS_TABLE_COUNT__;
	} while (pJmpAddressTableMakeSure[iIndex]);
	pJmpAddressTableMakeSure[iIndex] = TRUE;
	return iIndex;
}

/*
 * 介绍:
 *	确定一个被引用的地址是否是引入表的函数
 *
 * 参数:
 *	addrTargetAddress:要跳转的目标地址
 *	pJmpAddressTable:引入地址表的指针
 *	iJmpAddressTableCount:引入地址表的计数
 */
__INLINE__ __bool __INTERNAL_FUNC__ IsInJmpAddressTable(__address addrTargetAddress, __address *pJmpAddressTable, __integer iJmpAddressTableCount) {
	__integer i = 0;
	for (i = 0; i < iJmpAddressTableCount; i++) {
		if (addrTargetAddress == pJmpAddressTable[i])
			return TRUE;
	}
	return FALSE;
}

typedef struct _JMPTABLE_TO_ADDRESS {
	__dword dwNewRva;
	__address addrAddress;
} JMPTABLE_TO_ADDRESS, *PJMPTABLE_TO_ADDRESS;

/*
 * 介绍:
 *	查看一个目标地址是否已经存在地址引入地址表中
 *
 * 参数:
 *	addrTargetAddress:目标地址
 *	pJmpTableToAddressList:跳转地址表
 *	iJmpAddressTableCount:跳转地址表的计数
 */
#define __NOT_IN_JMPADDRESSTABLE__		0xFFFFFFFF
__INLINE__ __dword __INTERNAL_FUNC__ GetNewRvaFromJmpAddressTable(__address addrTargetAddress, PJMPTABLE_TO_ADDRESS pJmpTableToAddressList, __integer iJmpAddressTableCount) {
	__integer i = 0;
	for (i = 0; i < iJmpAddressTableCount; i++) {
		if (addrTargetAddress == pJmpTableToAddressList[i].addrAddress)
			return pJmpTableToAddressList[i].dwNewRva;
	}
	return __NOT_IN_JMPADDRESSTABLE__;
}

/*
 * 介绍:
 *	计算引入地址链表的个数
 */
__integer __API__ CountReleaseReferenceImportTable(PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceImportTableAddress) {
	__integer i =0;

	while (pReferenceImportTableAddress) {
		i++;
		pReferenceImportTableAddress = pReferenceImportTableAddress->pNext;
	}

	return i;
}

/*
 * 介绍:
 *	释放引用引入地址表的内存
 */
__void __API__ ReleaseReferenceImportTableAddress(PREFERENCE_IMPORT_TABLE_ADDRESS *pReferenceImportTableAddressPoint) {
	PREFERENCE_IMPORT_TABLE_ADDRESS pCurrReferenceImportTableAddress = *pReferenceImportTableAddressPoint;
	PREFERENCE_IMPORT_TABLE_ADDRESS pTmp = NULL;
	while (pCurrReferenceImportTableAddress) {
		pTmp = pCurrReferenceImportTableAddress->pNext;
		__logic_delete__(pCurrReferenceImportTableAddress);
		pCurrReferenceImportTableAddress = pTmp;
	}
	*pReferenceImportTableAddressPoint = NULL;
}

/*
 * 介绍:
 *	力量解密引入表
 * 
 * 参数:
 *	pMem:要保护函数的映射
 *	addrOrigImageBase:要保护函数原先的基地址
 *	pImportProtect:引入表保护结构指针
 *	bOnFile:是否是文件
 *	ofJmpTableRva:新的引入跳转表的RVA
 */
PREFERENCE_IMPORT_TABLE_ADDRESS __API__ PowerEncryptImportTable(__memory pMem, __address addrOrigImageBase, PIMPORT_PROTECT pImportProtect, __bool bOnFile, __offset ofJmpTableRva) {
	__byte bXor = 0;
	__memory pCodeStart = NULL;
	__integer iCodeSize = 0;
	__integer iProcCount = 0, iLibCount = 0, iIndex = 0;
	__address addrImageBase = 0;
	__address addrCurrOrigImageBase = 0;
	__address OrigJmpAddressTable[__MAX_JMP_ADDRESS_TABLE_COUNT__] = {0};
	__bool JmpAddressTableMakeSure[__MAX_JMP_ADDRESS_TABLE_COUNT__] = {0};//用于确认当前位置是否被占用
	JMPTABLE_TO_ADDRESS JmpTableToAddressList[__MAX_JMP_ADDRESS_TABLE_COUNT__] = {0};
	__integer iJmpAddressTableCount = 0;
	__dword *pJmpAddressTableRva = NULL;
	__address addrNowAddress = 0;
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_DATA_DIRECTORY pImageImportDataDirectory = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = NULL;
	ud_t ud_obj = {0};
	PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceImportTableAddres = NULL;
	PREFERENCE_IMPORT_TABLE_ADDRESS *pCurrReferenceImportTableAddresPoint = &pReferenceImportTableAddres;

	// 初始化数据
	pImageImportDataDirectory = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_IMPORT);
	if (!pImageImportDataDirectory)
		return NULL;

	/*
	 * 获取目标映射的基地址
	 * 要修复的基地址可以通过函数的参数addrOrigImageBase指定,如果addrOrigImageBase == 0xFFFFFFFF则使用
	 * addrImageBase,如果addrOrigImageBase != 0xFFFFFFFF,则使用addrOrigImageBase
	 */
	pNtHdr = GetNtHeader(pMem);
	addrImageBase = pImportProtect->addrImageBase;

	// 获取目标文件代码段的地址与长度
	if (bOnFile) {
		//addrImageBase = (__address)(pNtHdr->OptionalHeader.ImageBase);
		pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(pMem + Rva2Raw(pMem, pImageImportDataDirectory->VirtualAddress));
		pCodeStart = pMem + GetEntryPointSection(pMem)->PointerToRawData;
	} else {
		//addrImageBase = (__address)pMem;
		pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)__RvaToVa__(pMem, pImageImportDataDirectory->VirtualAddress);
		pCodeStart = pMem + GetEntryPointSection(pMem)->VirtualAddress;
	}
	iCodeSize = GetEntryPointSection(pMem)->Misc.VirtualSize;
	__logic_memset__(JmpAddressTableMakeSure, FALSE, __MAX_JMP_ADDRESS_TABLE_COUNT__);

	// 设置IMAGE_PROTECT
	bXor = (__byte)GenerateRandomNumber();//随机生成出一个KEY
	pImportProtect->bXor = bXor;

	// 将引入表信息存入IMPORT_PROTECT结构
	// 有些程序只适用FirstThunk
	while (pImageImportDescriptor->FirstThunk) {
		__address addrCurrAddress = 0;
		__dword dwCurrRva = 0;
		__char *svDllName = NULL;
		PIMAGE_THUNK_DATA pTdIn = NULL;
		PIMAGE_THUNK_DATA pTdOut = NULL;
		if (bOnFile)
			svDllName = (__char *)(pMem + Rva2Raw(pMem, pImageImportDescriptor->Name));
		else
			svDllName = (__char *)__RvaToVa__(pMem, pImageImportDescriptor->Name);

		EncryptIATCallBack(iLibCount, LIB_NAME, (__memory)svDllName, __logic_strlen__(svDllName), FALSE, 0, (__void *)pImportProtect);

		// 填充引入表地址
		if (bOnFile) {
			pTdIn = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw(pMem, pImageImportDescriptor->OriginalFirstThunk));
			pTdOut = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw(pMem, pImageImportDescriptor->FirstThunk));
			// 没有OriginalFirstThunk的情况
			if ((__memory)pTdIn == pMem)
				pTdIn = pTdOut;
		} else {
			pTdIn = (PIMAGE_THUNK_DATA)__RvaToVa__(pMem, pImageImportDescriptor->OriginalFirstThunk);
			pTdOut = (PIMAGE_THUNK_DATA)__RvaToVa__(pMem, pImageImportDescriptor->FirstThunk);
			// 没有OriginalFirstThunk的情况
			if ((__memory)pTdIn == pMem)
				pTdIn = pTdOut;
		}
		
		iProcCount = 0;
		if (addrOrigImageBase == __USE_DEF_IMAGEBASE_AS_ORIG__)
			addrCurrOrigImageBase = addrImageBase;
		else
			addrCurrOrigImageBase = addrOrigImageBase;
		addrCurrAddress = __RvaToVa__(addrCurrOrigImageBase, pImageImportDescriptor->FirstThunk);

		// 加密函数
		while (pTdIn->u1.Function) {
			// 随机取出一个要放入的位置
			__integer iOffsetTableIndex = RandJmpAddress(&JmpAddressTableMakeSure);

			// 获取新的FirstThunk
			__dword dwNewFirstThunk = (__dword)(ofJmpTableRva + iOffsetTableIndex * sizeof(__address));
			OrigJmpAddressTable[iJmpAddressTableCount] = addrCurrAddress;
			JmpTableToAddressList[iJmpAddressTableCount].addrAddress = addrCurrAddress;
			// 合成新的引入地址表偏移
			JmpTableToAddressList[iJmpAddressTableCount].dwNewRva = dwNewFirstThunk;
			iJmpAddressTableCount++;//跳入表计数

			// 以序号引出还是以函数名引出
			if (pTdIn->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
				__word wOrd = pTdIn->u1.Ordinal;
				EncryptIATCallBack(iIndex, PROC_NAME, (__memory)&wOrd, 2, TRUE, dwNewFirstThunk, (__void *)pImportProtect);
			} else {
				__char *szProcName = NULL;
				PIMAGE_IMPORT_BY_NAME pIbn = NULL;
				if (bOnFile)
					pIbn = (PIMAGE_IMPORT_BY_NAME)(pMem + Rva2Raw(pMem, pTdIn->u1.AddressOfData));
				else
					pIbn = (PIMAGE_IMPORT_BY_NAME)__RvaToVa__(pMem, pTdIn->u1.AddressOfData);
				szProcName = (__char *)(pIbn->Name);
				EncryptIATCallBack(iIndex, PROC_NAME, (__memory)szProcName, __logic_strlen__(szProcName), FALSE, dwNewFirstThunk, (__void *)pImportProtect);
			}
			// 下一个函数
			addrCurrAddress += sizeof(__address);
			iProcCount++;//函数计数增加
			iIndex++;//索引计数增加
			pTdIn++;
			pTdOut++;
		}/* end while */
		
		// 在下一个DLL之前,记录当前库所有的API数量
		pImportProtect->iApiNumberInThisLibrary[iLibCount] = iProcCount;
		// 下一个DLL
		pImageImportDescriptor++;
		iLibCount++;
	}/* end while */

	pJmpAddressTableRva = &(pImportProtect->dwFirstThunkList);

	// 验证
	if (iIndex != pImportProtect->iApiNameCrc32Count)
		return NULL;

	// 进行随机混淆
	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, pCodeStart, iCodeSize);//默认一个函数的最大长度为4096
	ud_set_mode(&ud_obj, 32);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	while (ud_disassemble(&ud_obj)) {
		__memory pFileSaveAddress = NULL;
		struct ud_operand *pCurrOperand = NULL;
		/*
		 * 找到拥有内存访问能力的指令,如果指令访问的内存地址在表中的话,则将其改写为新的内存
		 * 地址
		 */
		if (ud_obj.operand[0].type != UD_NONE) {
			// 如果拥有操作数
			__integer iOperandCount = 0;

			///*
			// * 这里仅处理MOV,CALL,JMP 三条指令
			// * 因为不同编译只有这三条指令会对引入表造成访问
			// */
			//if (ud_obj.mnemonic == UD_Imov) {
			//	if ((ud_obj.operand[1].type == UD_OP_MEM) && (ud_obj.operand[1].base == UD_NONE) && \
			//		(ud_obj.operand[1].index == UD_NONE) && (ud_obj.operand[1].size == 32)) {
			//			pCurrOperand = &(ud_obj.operand[1]);
			//			pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
			//	}
			//} else if ((ud_obj.mnemonic == UD_Icall) || (ud_obj.mnemonic == UD_Ijmp)) {
			//	if ((ud_obj.operand[0].type == UD_OP_MEM) && (ud_obj.operand[0].base == UD_NONE) && \
			//		(ud_obj.operand[0].index == UD_NONE) && (ud_obj.operand[0].offset) && (ud_obj.operand[0].size == 32)) {
			//			pCurrOperand = &(ud_obj.operand[0]);
			//			pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
			//	}
			//}

			//////////////////////////////////////////////////////////////////////////
			// 2012.2.10 修改为 所有指令只要有内存访问
			// 形如:xxx dword ptr [address]
			//      xxx dword ptr [address], reg
			//      xxx reg, dword ptr [address]
			if ((ud_obj.operand[0].type == UD_OP_MEM) && (ud_obj.operand[0].base == UD_NONE) && \
				(ud_obj.operand[0].index == UD_NONE) && (ud_obj.operand[0].offset) && (ud_obj.operand[0].size == 32)) {
					pCurrOperand = &(ud_obj.operand[0]);
					pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
			}
			else if ((ud_obj.operand[1].type == UD_OP_MEM) && (ud_obj.operand[1].base == UD_NONE) && \
				(ud_obj.operand[1].index == UD_NONE) && (ud_obj.operand[1].size == 32)) {
					pCurrOperand = &(ud_obj.operand[1]);
					pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
			}

			if (pFileSaveAddress) {
				__memory pCurrInstFileAddress = ud_obj.inp_buff - ud_obj.inp_ctr;
				/*
				 * 如果是内存访问操作
				 * 取出地址与跳转地址表中进行检索
				 */
				__address addrTargetAddress = (__address)(pCurrOperand->lval.sdword);
				__dword dwNowRva = GetNewRvaFromJmpAddressTable(addrTargetAddress, &JmpTableToAddressList, iJmpAddressTableCount);
				if (dwNowRva != __NOT_IN_JMPADDRESSTABLE__) {
					addrNowAddress = addrImageBase + dwNowRva;
					*(__address *)pFileSaveAddress = addrNowAddress;//重新设置

					// 设置一个引入表引用结构
					(*pCurrReferenceImportTableAddresPoint) = (PREFERENCE_IMPORT_TABLE_ADDRESS)__logic_new__(REFERENCE_IMPORT_TABLE_ADDRESS, 1);
					if (bOnFile) {
						(*pCurrReferenceImportTableAddresPoint)->ofReferenceRVA = Raw2Rva(pMem, (__integer)(pFileSaveAddress - pMem));
						(*pCurrReferenceImportTableAddresPoint)->addrReferenceMemAddress = addrImageBase + Raw2Rva(pMem, (__integer)(pCurrInstFileAddress - pMem));
					} else {
						(*pCurrReferenceImportTableAddresPoint)->ofReferenceRVA = (__integer)(pFileSaveAddress - pMem);
						(*pCurrReferenceImportTableAddresPoint)->addrReferenceMemAddress = addrImageBase + (__integer)(pCurrInstFileAddress - pMem);
					}
					(*pCurrReferenceImportTableAddresPoint)->pReferenceFileAddress = pCurrInstFileAddress;
					__logic_memcpy__(&((*pCurrReferenceImportTableAddresPoint)->ud_obj), &ud_obj, sizeof(ud_t));

					// 增加引用引入表内存指令RVA,如果大于最大的计数则加密引入表失败直接退出
					if (pImportProtect->iImportTableReferenceAddressCount >= __MAX_IMPORT_REFERENCE_COUNT__) {
						// 释放已经分配的内存
						ReleaseReferenceImportTableAddress(&pReferenceImportTableAddres);
						return NULL;
					}/* end if */
					pImportProtect->ofImportTableReferenceAddressRVA[pImportProtect->iImportTableReferenceAddressCount] = (*pCurrReferenceImportTableAddresPoint)->ofReferenceRVA;
					pImportProtect->ofAPINowRVA[pImportProtect->iImportTableReferenceAddressCount] = dwNowRva;
					(pImportProtect->iImportTableReferenceAddressCount)++;

					// 移动到下一个
					pCurrReferenceImportTableAddresPoint = &((*pCurrReferenceImportTableAddresPoint)->pNext);
				}
			}/* end if */
		}/* end if */
	}

	pImportProtect->ofJmpTableRva = ofJmpTableRva;//设置新跳转表的RVA
	// 销毁原先的引入表
	if (bOnFile)
		DeleteDataDirectoryObject(pMem, IMAGE_DIRECTORY_ENTRY_IMPORT);
	else
		DeleteDataDirectoryObjectOnMemMap(pMem, IMAGE_DIRECTORY_ENTRY_IMPORT);

	return pReferenceImportTableAddres;
}

/*
 * 介绍:
 *	解密引入地址表,此函数在目标文件中调用,用于修复
 *
 * 参数:
 *	pArg:力量解密引入表参数结构
 */
__bool __API__ PowerDecryptImportTable(PPOWERDECRYPTIMPORTTABLE_ARG pArg) {
	PIMPORT_PROTECT pImportProtect = NULL;
	FPAddThunkCodeStub pAddThunkCodeStub = NULL;
	__byte bXor = 0;
	HMODULE hDll = NULL, hCurrDll = NULL;
	__integer i = 0, j = 0, iIndex = 0;
	__integer iLength = 0;
	__char *pLibName = NULL;
	__char LibName[64] = {0};
	__dword dwLibNameCrc32 = 0;
	__bool bDllIsProtect = FALSE;

	__PrintDbgInfo_OutputDbgString__("Entry PowerDecryptImportTable");

	// 初始化数据
	pImportProtect = pArg->pImportProtect;
	pAddThunkCodeStub = pArg->pAddThunkCodeStub;
	bXor = pImportProtect->bXor;//获取密钥的解密密码

	for (i = 0; i < pImportProtect->iLibraryKeyCount; i++) {
		__dword dwKey = 0;
		__memory pKey = NULL;

		dwKey = pImportProtect->dwLibraryKeyList[i];//解密密钥
		pKey = (__memory)&dwKey;

		XorKey4Bytes(pKey, bXor);
		iLength = pImportProtect->iLibraryNameLengthList[i];
		__logic_memset__(LibName, 0, 64);
		pLibName = pImportProtect->LibraryNameList[i];
		XorArray(dwKey, (__memory)pLibName, (__memory)LibName, iLength);//解密

		// 获取库名的CRC32值
		dwLibNameCrc32 = crc32((__memory)LibName, iLength);

		// 加载并重映射DLL
		hCurrDll = g_pLoadLibraryA(LibName);

		// 如果是在保护内的库则重新映射
		if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCrc32List, pImportProtect->iProtectDllCrc32Count)) {
			// 查看是否是排除在执行DllMain的库
			if (ThisValueIsInList(dwLibNameCrc32, pImportProtect->dwProtectDllCallDllMainCrc32List, pImportProtect->iProtectDllCallDllMainCrc32Count))
				hDll = (HMODULE)RemapDll((__memory)hCurrDll, g_pVirtualAlloc, TRUE);
			else
				hDll = (HMODULE)RemapDll((__memory)hCurrDll, g_pVirtualAlloc, FALSE);

			// 设置此DLL经过保护
			bDllIsProtect = TRUE;
		} else {
			hDll = (HMODULE)hCurrDll;

			// 设置此DLL未经过保护
			bDllIsProtect = FALSE;
		}

		// 获取API地址
		for (j = 0; j < pImportProtect->iApiNumberInThisLibrary[i]; j++) {
			__memory pHashData = NULL;
			__address addrImageBase = 0;
			__dword dwFirstThunk = 0;
			__address *paddrOut = NULL;

			pHashData = (__memory)&(pImportProtect->dwApiNameCrc32List[iIndex]);
			addrImageBase = pImportProtect->addrImageBase;
			dwFirstThunk = pImportProtect->dwFirstThunkList[iIndex];
			paddrOut = (__address *)(addrImageBase + (__address)dwFirstThunk);

			if (pImportProtect->bIsOrdList[iIndex]) {
				__dword dwOrd = pImportProtect->dwApiNameCrc32List[iIndex] & 0xFFFF;//取低2字节
				__PrintDbgInfo_OutputDbgString__("Already goto xGetProcAddressByHash by API ord");
				*paddrOut = (__address)xGetProcAddressByHash(hDll, (__memory)dwOrd, 2, DecrypterHashFunc);
			} else {
				__PrintDbgInfo_OutputDbgString__("Already goto xGetProcAddressByHash by API name hash value");
				*paddrOut = (__address)xGetProcAddressByHash(hDll, pHashData, sizeof(__address), DecrypterHashFunc);
			}

			// 在需要抽取的API列表中找寻
			__PrintDbgInfo_OutputDbgString__("Already goto ThisApiIsInProtectList");
			if (ThisValueIsInList(pImportProtect->dwApiNameCrc32List[iIndex], &(pImportProtect->dwProtectApiCrc32List), pImportProtect->iProtectApiCrc32Count)) {
				__memory pNowAddress = NULL;
				__memory pNewAddress = NULL;
				__offset ofOffset = 0;
				//__integer iProcSize = 0;

				pNowAddress = (__memory)(*paddrOut);

				// 计算这个函数的长度
				//iProcSize = SimpleCalcThisProcedureLength(pNowAddress);

				if (pAddThunkCodeStub) {
					pNewAddress = pAddThunkCodeStub((__address)pNowAddress);
					if (!pNewAddress) goto _default_add_thunk_code_stub;//如果为空则直接转入默认处理
				} else {
					_default_add_thunk_code_stub:
					// 产生一个中间函数
					pNewAddress = __logic_new_size__(0x10);
					// 计算偏移
					ofOffset = CalcCurrOffsetFromAddress(32, (__address)pNowAddress, (__address)pNewAddress, 5);
					*(__byte *)pNewAddress = 0xE9;
					*(__offset *)(pNewAddress + 1) = ofOffset;
				}

				// 重新设定地址
				*paddrOut = (__address)pNewAddress;
			}

			// 增加索引计数
			iIndex++;
		}/* end for */

		// 如果在保护范围内则清除这个DLL的无用信息
		if (bDllIsProtect) {
			__PrintDbgInfo_OutputDbgString__("Already goto ClearRemapDllUnSafeInfo");
			ClearRemapDllUnSafeInfo(hDll);
		}/* end if */
	}

	// 检验
	if (iIndex != pImportProtect->iApiNameCrc32Count)
		return FALSE;

	// 这里开启一个非常重要就是修订目标代码节要引用的
	__PrintDbgInfo_OutputDbgString__("Fix target code reference API memory address");
	{
		__integer i = 0;
		__memory pMem = NULL;
		
		pMem = (__memory)(pImportProtect->addrImageBase);

		for (i = 0; i < pImportProtect->iImportTableReferenceAddressCount; i++) {
			__address *pReference = NULL;
			__address addrNowAddress = 0;

			// 获得引用的地址
			pReference = (__address *)(pMem + pImportProtect->ofImportTableReferenceAddressRVA[i]);
			addrNowAddress = (__address)(pMem + pImportProtect->ofAPINowRVA[i]);

			// 设置
			*pReference = addrNowAddress;
		}/* end for */
	}

	__PrintDbgInfo_OutputDbgString__("Exit PowerDecryptImportTable");
	return TRUE;
}
