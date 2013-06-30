#include "PeView.h"
#include "Support.h"

__void __INTERNAL_FUNC__ PrintPEHeader(FILE *fp, __memory pMem) {
	PIMAGE_NT_HEADERS pNtHdr = NULL;

	// 获取NT头
	pNtHdr = GetNtHeader(pMem);
	
	fprintf(fp, "<PeHeader Size=\"%d\">\n", sizeof(IMAGE_NT_HEADERS));

	fprintf(fp, "<Signature>0x%X</Signature>\n", pNtHdr->Signature);

	fprintf(fp, "<FileHeader Size=\"%d\">\n", sizeof(IMAGE_FILE_HEADER));
	fprintf(fp, "<Machine>0x%X</Machine>\n", pNtHdr->FileHeader.Machine);
	fprintf(fp, "<NumberOfSections>0x%X</NumberOfSections>\n", pNtHdr->FileHeader.NumberOfSections);
	fprintf(fp, "<TimeDateStamp>0x%X</TimeDateStamp>\n", pNtHdr->FileHeader.TimeDateStamp);
	fprintf(fp, "<PointerToSymbolTable>0x%X</PointerToSymbolTable>\n", pNtHdr->FileHeader.PointerToSymbolTable);
	fprintf(fp, "<NumberOfSymbols>0x%X</NumberOfSymbols>\n", pNtHdr->FileHeader.NumberOfSymbols);
	fprintf(fp, "<SizeOfOptionalHeader>0x%X</SizeOfOptionalHeader>\n", pNtHdr->FileHeader.SizeOfOptionalHeader);
	fprintf(fp, "<Characteristics>0x%X</Characteristics>\n", pNtHdr->FileHeader.Characteristics);
	fprintf(fp, "</FileHeader>\n");

	fprintf(fp, "<OptionalHeader Size=\"%d\">\n", sizeof(IMAGE_OPTIONAL_HEADER));
	fprintf(fp, "<Magic>0x%X</Magic>\n", pNtHdr->OptionalHeader.Magic);
	fprintf(fp, "<MajorLinkerVersion>0x%X</MajorLinkerVersion>\n", pNtHdr->OptionalHeader.MajorLinkerVersion);
	fprintf(fp, "<MinorLinkerVersion>0x%X</MinorLinkerVersion>\n", pNtHdr->OptionalHeader.MinorLinkerVersion);
	fprintf(fp, "<SizeOfCode>0x%X</SizeOfCode>\n", pNtHdr->OptionalHeader.SizeOfCode);
	fprintf(fp, "<SizeOfInitializedData>0x%X</SizeOfInitializedData>\n", pNtHdr->OptionalHeader.SizeOfInitializedData);
	fprintf(fp, "<SizeOfUninitializedData>0x%X</SizeOfUninitializedData>\n", pNtHdr->OptionalHeader.SizeOfUninitializedData);
	fprintf(fp, "<AddressOfEntryPoint>0x%X</AddressOfEntryPoint>\n", pNtHdr->OptionalHeader.AddressOfEntryPoint);
	fprintf(fp, "<BaseOfCode>0x%X</BaseOfCode>\n", pNtHdr->OptionalHeader.BaseOfCode);
	fprintf(fp, "<BaseOfData>0x%X</BaseOfData>\n", pNtHdr->OptionalHeader.BaseOfData);
	//
	// NT additional fields.
	//
	fprintf(fp, "<ImageBase>0x%X</ImageBase>\n", pNtHdr->OptionalHeader.ImageBase);
	fprintf(fp, "<SectionAlignment>0x%X</SectionAlignment>\n", pNtHdr->OptionalHeader.SectionAlignment);
	fprintf(fp, "<FileAlignment>0x%X</FileAlignment>\n", pNtHdr->OptionalHeader.FileAlignment);
	fprintf(fp, "<MajorOperatingSystemVersion>0x%X</MajorOperatingSystemVersion>\n", pNtHdr->OptionalHeader.MajorOperatingSystemVersion);
	fprintf(fp, "<MinorOperatingSystemVersion>0x%X</MinorOperatingSystemVersion>\n", pNtHdr->OptionalHeader.MinorOperatingSystemVersion);
	fprintf(fp, "<MajorImageVersion>0x%X</MajorImageVersion>\n", pNtHdr->OptionalHeader.MajorImageVersion);
	fprintf(fp, "<MinorImageVersion>0x%X</MinorImageVersion>\n", pNtHdr->OptionalHeader.MinorImageVersion);
	fprintf(fp, "<MajorSubsystemVersion>0x%X</MajorSubsystemVersion>\n", pNtHdr->OptionalHeader.MajorSubsystemVersion);
	fprintf(fp, "<MinorSubsystemVersion>0x%X</MinorSubsystemVersion>\n", pNtHdr->OptionalHeader.MinorSubsystemVersion);
	fprintf(fp, "<Win32VersionValue>0x%X</Win32VersionValue>\n", pNtHdr->OptionalHeader.Win32VersionValue);
	fprintf(fp, "<SizeOfImage>0x%X</SizeOfImage>\n", pNtHdr->OptionalHeader.SizeOfImage);
	fprintf(fp, "<SizeOfHeaders>0x%X</SizeOfHeaders>\n", pNtHdr->OptionalHeader.SizeOfHeaders);
	fprintf(fp, "<CheckSum>0x%X</CheckSum>\n", pNtHdr->OptionalHeader.CheckSum);
	fprintf(fp, "<Subsystem>0x%X</Subsystem>\n", pNtHdr->OptionalHeader.Subsystem);
	fprintf(fp, "<DllCharacteristics>0x%X</DllCharacteristics>\n", pNtHdr->OptionalHeader.DllCharacteristics);
	fprintf(fp, "<SizeOfStackReserve>0x%X</SizeOfStackReserve>\n", pNtHdr->OptionalHeader.SizeOfStackReserve);
	fprintf(fp, "<SizeOfStackCommit>0x%X</SizeOfStackCommit>\n", pNtHdr->OptionalHeader.SizeOfStackCommit);
	fprintf(fp, "<SizeOfHeapReserve>0x%X</SizeOfHeapReserve>\n", pNtHdr->OptionalHeader.SizeOfHeapReserve);
	fprintf(fp, "<SizeOfHeapCommit>0x%X</SizeOfHeapCommit>\n", pNtHdr->OptionalHeader.SizeOfHeapCommit);
	fprintf(fp, "<LoaderFlags>0x%X</LoaderFlags>\n", pNtHdr->OptionalHeader.LoaderFlags);
	fprintf(fp, "<NumberOfRvaAndSizes>0x%X</NumberOfRvaAndSizes>\n", pNtHdr->OptionalHeader.NumberOfRvaAndSizes);
	fprintf(fp, "</OptionalHeader>\n");

	fprintf(fp, "</PeHeader>\n");
	return;
}

__void __INTERNAL_FUNC__ PrintSectionHeaders(FILE *fp, __memory pMem) {
	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_SECTION_HEADER pSectionHdrs = NULL;
	__integer i = 0, NumberOfSections = 0;

	// 获取NT头
	pNtHdr = GetNtHeader(pMem);
	NumberOfSections = pNtHdr->FileHeader.NumberOfSections;
	fprintf(fp, "<SectionHeaders Numbers=\"%d\">\n", pNtHdr->FileHeader.NumberOfSections);
	pSectionHdrs = GetFirstSection(pMem);
	for (i = 0; i < NumberOfSections; i++, pSectionHdrs++) {
		fprintf(fp, "<Section>\n");
		fprintf(fp, "<Name>%s</Name>\n", pSectionHdrs->Name);
		fprintf(fp, "<VirtualSize>0x%X</VirtualSize>\n", pSectionHdrs->Misc.VirtualSize);
		fprintf(fp, "<VirtualAddress>0x%X</VirtualAddress>\n", pSectionHdrs->VirtualAddress);
		fprintf(fp, "<SizeOfRawData>0x%X</SizeOfRawData>\n", pSectionHdrs->SizeOfRawData);
		fprintf(fp, "<PointerToRawData>0x%X</PointerToRawData>\n", pSectionHdrs->PointerToRawData);
		fprintf(fp, "<PointerToRelocations>0x%X</PointerToRelocations>\n", pSectionHdrs->PointerToRelocations);
		fprintf(fp, "<PointerToLinenumbers>0x%X</PointerToLinenumbers>\n", pSectionHdrs->PointerToLinenumbers);
		fprintf(fp, "<NumberOfRelocations>0x%X</NumberOfRelocations>\n", pSectionHdrs->NumberOfRelocations);
		fprintf(fp, "<NumberOfLinenumbers>0x%X</NumberOfLinenumbers>\n", pSectionHdrs->NumberOfLinenumbers);
		fprintf(fp, "<Characteristics>0x%X</Characteristics>\n", pSectionHdrs->Characteristics);
		fprintf(fp, "</Section>\n");
	}
	fprintf(fp, "</SectionHeaders>\n");
	return;
}

__void __INTERNAL_FUNC__ PrintExportTable(FILE *fp, __memory pMem) {
	__offset ofOffset = 0;
	__word wOrdinal = 0;
	__integer iDirCount = 0;
	__address *pAddrTable = NULL;
	__address addrAddr = 0;
	__offset ofRVA = 0;
	__integer iExpDataSize = 0;
	PIMAGE_EXPORT_DIRECTORY pEd = NULL;
	PIMAGE_NT_HEADERS pNt = NULL;
	PIMAGE_DATA_DIRECTORY pExportDataDirectory = NULL;

	pNt = GetNtHeader(pMem);
	pExportDataDirectory = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_EXPORT);
	if(!pExportDataDirectory) {
		return;
	}

	ofOffset = Rva2Raw(pMem, pExportDataDirectory->VirtualAddress);
	iExpDataSize = pExportDataDirectory->Size;

	fprintf(fp, "<ExportTable Rva=\"0x%X\" Offset=\"0x%X\" Size=\"%d\">\n", pExportDataDirectory->VirtualAddress, ofOffset, iExpDataSize);

	// 从引出表获取函数地址
	pEd = (PIMAGE_EXPORT_DIRECTORY)(pMem + Rva2Raw(pMem, pExportDataDirectory->VirtualAddress));	
	{
		__integer i, iCount;
		__dword *pdwNamePtr;
		__word *pwOrdinalPtr;

		iCount = (__integer)(pEd->NumberOfNames);
		pdwNamePtr = (__dword *)(pMem + Rva2Raw(pMem, pEd->AddressOfNames));
		pwOrdinalPtr = (__word *)(pMem + Rva2Raw(pMem, pEd->AddressOfNameOrdinals));

		fprintf(fp, "<IMAGE_EXPORT_DIRECTORY>\n");
		fprintf(fp, "<Characteristics>0x%X</Characteristics>\n", pEd->Characteristics);
		fprintf(fp, "<TimeDateStamp>0x%X</TimeDateStamp>\n", pEd->TimeDateStamp);
		fprintf(fp, "<MajorVersion>0x%X</MajorVersion>\n", pEd->MajorVersion);
		fprintf(fp, "<MinorVersion>0x%X</MinorVersion>\n", pEd->MinorVersion);
		fprintf(fp, "<Name>0x%X</Name>\n", pEd->Name);
		fprintf(fp, "<Base>0x%X</Base>\n", pEd->Base);
		fprintf(fp, "<NumberOfFunctions>0x%X</NumberOfFunctions>\n", pEd->NumberOfFunctions);
		fprintf(fp, "<NumberOfNames>0x%X</NumberOfNames>\n", pEd->NumberOfNames);
		fprintf(fp, "<AddressOfFunctions>0x%X</AddressOfFunctions>\n", pEd->AddressOfFunctions);
		fprintf(fp, "<AddressOfNames>0x%X</AddressOfNames>\n", pEd->AddressOfNames);
		fprintf(fp, "<AddressOfNameOrdinals>0x%X</AddressOfNameOrdinals>\n", pEd->AddressOfNameOrdinals);
		fprintf(fp, "</IMAGE_EXPORT_DIRECTORY>\n");

		for(i = 0; i < iCount; i++) {
			__char *svName = NULL;

			svName = (__char *)(pMem + Rva2Raw(pMem, *pdwNamePtr));
			fprintf(fp, "<Procedure Index=\"%d\">\n", i);

			pAddrTable=(__address *)(pMem + Rva2Raw(pMem, pEd->AddressOfFunctions));
			ofRVA = pAddrTable[wOrdinal];
			addrAddr = (__address)(pMem + Rva2Raw(pMem, ofRVA));

			fprintf(fp, "<Name>%s</Name>\n", svName);
			fprintf(fp, "<Rva>0x%X</Rva>\n", ofRVA);

			// 是否是中间跳转
			if (((__address)addrAddr >= (__address)pEd) && ((__address)addrAddr < (__address)pEd + (__address)iExpDataSize)) {
				fprintf(fp, "<Address>%s</Address>\n", (__char *)addrAddr);
			} else {
				__address addrProcAddress = pNt->OptionalHeader.ImageBase + ofRVA;
				fprintf(fp, "<Address>0x%X</Address>\n", addrProcAddress);
			}

			fprintf(fp, "</Procedure>\n");
			pdwNamePtr++;
			pwOrdinalPtr++;
		}
	}

	fprintf(fp, "</ExportTable>\n");
	return;
}

__void __INTERNAL_FUNC__ PrintImportTable(FILE *fp, __memory pMem) {
	__offset ofOffset = 0;
	__integer iSize = 0;
	__integer iLibIndex = 0, iProcIndex = 0;
	PIMAGE_IMPORT_DESCRIPTOR pImportDes = NULL;
	PIMAGE_DATA_DIRECTORY pData = NULL;
	PIMAGE_NT_HEADERS pNtHdr = NULL;

	pData = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_IMPORT);
	if (!pData) {
		return;
	}

	pNtHdr = GetNtHeader(pMem);
	pImportDes = (PIMAGE_IMPORT_DESCRIPTOR)(pMem + Rva2Raw(pMem, pData->VirtualAddress));
	ofOffset = Rva2Raw(pMem, pData->VirtualAddress);
	iSize = pData->Size;

	fprintf(fp, "<ImportTable Rva=\"0x%X\" Offset=\"0x%X\" Size=\"%d\">\n", pData->VirtualAddress, ofOffset, iSize);

	// 有些程序只适用FirstThunk
	while ((pImportDes->OriginalFirstThunk) || (pImportDes->FirstThunk)) {
		__char *svDllName = NULL;
		PIMAGE_THUNK_DATA pTdIn = NULL;
		PIMAGE_THUNK_DATA pTdOut = NULL;
		__dword dwFirstThunk = 0;

		// 输出引入表描述符结构
		fprintf(fp, "<IMAGE_IMPORT_DESCRIPTOR>\n");
		fprintf(fp, "<dwFirstThunk>0x%X</dwFirstThunk>\n", pImportDes->Characteristics);
		fprintf(fp, "<TimeDateStamp>0x%X</TimeDateStamp>\n", pImportDes->TimeDateStamp);
		fprintf(fp, "<ForwarderChain>0x%X</ForwarderChain>\n", pImportDes->ForwarderChain);
		fprintf(fp, "<Name>0x%X</Name>\n", pImportDes->Name);
		fprintf(fp, "<FirstThunk>0x%X</FirstThunk>\n", pImportDes->FirstThunk);
		fprintf(fp, "</IMAGE_IMPORT_DESCRIPTOR>\n");

		svDllName = (__char *)(pMem + Rva2Raw((__void *)pMem, pImportDes->Name));
		
		// 显示函数名
		fprintf(fp, "<Library Index=\"%d\" Name=\"%s\">\n", iLibIndex, svDllName);
		iLibIndex++;

		// 填充引入表地址
		if (pImportDes->OriginalFirstThunk == 0) {//如果此字段为0,则使用FirstThunk
			pTdIn = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw((__void *)pMem, pImportDes->FirstThunk));
			pTdOut = pTdIn;
		} else {
			pTdIn = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw((__void *)pMem, pImportDes->OriginalFirstThunk));
			pTdOut = (PIMAGE_THUNK_DATA)(pMem + Rva2Raw((__void *)pMem, pImportDes->FirstThunk));
		}

		iProcIndex = 0;
		// 加密函数
		while (pTdIn->u1.Function) {
			// 以序号引出还是以函数名引出
			if (pTdIn->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
				__word wOrd = pTdIn->u1.Ordinal;
				fprintf(fp, "<Procedure Index=\"%d\">0x%X</Procedure>\n", wOrd);
			} else {
				__char *szProcName = NULL;
				PIMAGE_IMPORT_BY_NAME pIbn = NULL;
				
				pIbn = (PIMAGE_IMPORT_BY_NAME)(pMem + Rva2Raw((__memory)pMem, pTdIn->u1.AddressOfData));
				szProcName = (__char *)(pIbn->Name);
				fprintf(fp, "<Procedure Index=\"%d\">%s</Procedure>\n", iProcIndex, szProcName);
			}
			iProcIndex++;//下一个函数
			pTdIn++;
			pTdOut++;
		}/* end while */
		fprintf(fp, "</Library>\n");
		pImportDes++;//下一个DLL
	}/* end while */

	fprintf(fp, "</ImportTable>\n");
}

__INLINE__ __void __INTERNAL_FUNC__ PrintResourceTableDumpData(FILE *fp, __memory pMem, PIMAGE_RESOURCE_DATA_ENTRY pDataEntry) {
	__memory pData = NULL;
	__offset ofOffset = 0;
	__byte bByte = 0;
	__integer iCount = 0, i = 0, iDataSize = 0;;

	fprintf(fp, "<Resource OffsetToData=\"0x%X\" Size=\"0x%X\" CodePage=\"0x%X\">\n", pDataEntry->OffsetToData, pDataEntry->Size, pDataEntry->CodePage);

	pData = (__memory)pMem + Rva2Raw((__memory)pMem, pDataEntry->OffsetToData);
	iDataSize = pDataEntry->Size;

	while (1) {
		// 判断末尾
		if ((iCount != 0) && (iCount % 0x10 == 0) || (iCount >= iDataSize)) {
			fprintf(fp, "</x%X>\n", ofOffset);

			// 是否是末尾
			if (iCount >= iDataSize)
				break;

			ofOffset += 0x10;
		}

		if ((iCount == 0) || ((iCount != 0) && (iCount % 0x10 == 0)))
			fprintf(fp, "<x%X>", ofOffset);

		// 获取字节
		bByte = *((__byte *)pData + iCount);
		if (bByte == 0)
			fprintf(fp, "00 ");
		else if (bByte < 0x0F)
			fprintf(fp, "0%X ", bByte);
		else
			fprintf(fp, "%2X ", bByte);

		iCount++;
	}

	fprintf(fp, "</Resource>\n");
}

__INLINE__ PIMAGE_RESOURCE_DATA_ENTRY __INTERNAL_FUNC__ _PrintResourceTable(PIMAGE_RESOURCE_DIRECTORY pDir, PIMAGE_RESOURCE_DIRECTORY pRoot) {
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((__integer)pDir + sizeof(IMAGE_RESOURCE_DIRECTORY));
	__integer iNumberEntries = (__integer)(pDir->NumberOfNamedEntries + pDir->NumberOfIdEntries);
	__integer i = 0;
	for (i = 0; i < iNumberEntries; i++, pEntry++) {
		if (pEntry->DataIsDirectory) {//如果是目录
			PIMAGE_RESOURCE_DIRECTORY pDir = (PIMAGE_RESOURCE_DIRECTORY)((__integer)pRoot + pEntry->OffsetToDirectory);
			return _PrintResourceTable(pDir, pRoot);
		} else {
			PIMAGE_RESOURCE_DATA_ENTRY pDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)((__integer)pRoot + pEntry->OffsetToDirectory);
			return pDataEntry;
		}/* end else */
	}/* end for */
	return NULL;
}

__void __INTERNAL_FUNC__ PrintResourceTable(FILE *fp, __memory pMem) {
	PIMAGE_DATA_DIRECTORY pDataDir = NULL;
	__offset ofOffset = 0;
	__integer iSize = 0;
	PIMAGE_RESOURCE_DIRECTORY pResRoot = NULL;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pEntry = NULL;
	__integer iNumberEntries = 0, i = 0;
	PIMAGE_NT_HEADERS pNtHdr = GetNtHeader(pMem);//检验资源节是否存在

	pDataDir = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_RESOURCE);
	if (!pDataDir) {
		return;
	}

	ofOffset = Rva2Raw(pMem, pDataDir->VirtualAddress);
	iSize = pDataDir->Size;

	// 获取ROOT节点
	pResRoot = (PIMAGE_RESOURCE_DIRECTORY)((__integer)pMem + Rva2Raw(pMem, pDataDir->VirtualAddress));

	fprintf(fp, "<ResourceTable Rva=\"0x%X\" Offset=\"0x%X\" Size=\"%d\">\n", pDataDir->VirtualAddress, ofOffset, iSize);

	//fprintf(fp, "<IMAGE_RESOURCE_DIRECTORY>\n");
	//fprintf(fp, "<Characteristics>0x%X</Characteristics>\n", pResRoot->Characteristics);
	//fprintf(fp, "<TimeDateStamp>0x%X</TimeDateStamp>\n", pResRoot->TimeDateStamp);
	//fprintf(fp, "<MajorVersion>0x%X</MajorVersion>\n", pResRoot->MajorVersion);
	//fprintf(fp, "<MinorVersion>0x%X</MinorVersion>\n", pResRoot->MinorVersion);
	//fprintf(fp, "<NumberOfNamedEntries>0x%X</NumberOfNamedEntries>\n", pResRoot->NumberOfNamedEntries);
	//fprintf(fp, "<NumberOfIdEntries>0x%X</NumberOfIdEntries>\n", pResRoot->NumberOfIdEntries);
	//fprintf(fp, "</IMAGE_RESOURCE_DIRECTORY>\n");

	pEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((__integer)pResRoot + sizeof(IMAGE_RESOURCE_DIRECTORY));
	iNumberEntries = pResRoot->NumberOfNamedEntries + pResRoot->NumberOfIdEntries;
	for (i = 0; i < iNumberEntries; i++, pEntry++) {
		if (pEntry->DataIsDirectory) {//如果是目录
			PIMAGE_RESOURCE_DIRECTORY pDir = NULL;
			PIMAGE_RESOURCE_DATA_ENTRY pRet = NULL;

			pDir = (PIMAGE_RESOURCE_DIRECTORY)((__integer)pResRoot + pEntry->OffsetToDirectory);
			pRet = _PrintResourceTable(pDir, pResRoot);
			if (pRet) {
				PrintResourceTableDumpData(fp, pMem, pRet);
			}
		}/* end if */
	}

	fprintf(fp, "</ResourceTable>\n");
}

__void __INTERNAL_FUNC__ PrintDebugTable(FILE *fp, __memory pMem) {

}

// 重定位所需结构
#pragma pack(push,1)
// 修复入口
typedef struct _IMAGE_FIXUP_ENTRY {
	__word offset:12;
	__word type:4;
} IMAGE_FIXUP_ENTRY, *PIMAGE_FIXUP_ENTRY;
// 重定位块
typedef struct _IMAGE_FIXUP_BLOCK {
	__dword dwPageRVA;
	__dword dwBlockSize;
} IMAGE_FIXUP_BLOCK, *PIMAGE_FIXUP_BLOCK;
#pragma pack(pop)
__void __INTERNAL_FUNC__ PrintRelocateTable(FILE *fp, __memory pMem) {
	__offset ofOffset = 0;
	__integer *pFixAddRhi = NULL;
	__bool bHaveFixAddRhi = FALSE;
	__integer iRelocSize = 0;

	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_DATA_DIRECTORY pDataDir = NULL;

	pNtHdr = GetNtHeader(pMem);

	pDataDir = ExistDataDirectory(pMem, IMAGE_DIRECTORY_ENTRY_BASERELOC);
	if (!pDataDir) {
		return;
	}

	ofOffset = Rva2Raw(pMem, pDataDir->VirtualAddress);
	iRelocSize = pDataDir->Size;

	fprintf(fp, "<RelocateTable Rva=\"0x%X\" Offset=\"0x%X\" Size=\"%d\">\n", pDataDir->VirtualAddress, ofOffset, iRelocSize);

	if (iRelocSize) {
		PIMAGE_FIXUP_BLOCK pStartFB = NULL;
		PIMAGE_FIXUP_BLOCK pIBR = NULL;
		__integer iRelocRaw = Rva2Raw(pMem, pDataDir->VirtualAddress);

		pIBR = (PIMAGE_FIXUP_BLOCK)(pMem + iRelocRaw);
		pStartFB = pIBR;

		// 遍历每个重定位块
		while ((__integer)(pIBR - pStartFB) < iRelocSize) {
			PIMAGE_FIXUP_ENTRY pFE;
			__integer i, iCount = 0;
			if (pIBR->dwBlockSize > 0) {
				iCount=(pIBR->dwBlockSize - sizeof(IMAGE_FIXUP_BLOCK)) / sizeof(IMAGE_FIXUP_ENTRY);
				pFE = (PIMAGE_FIXUP_ENTRY)(((__memory)pIBR) + sizeof(IMAGE_FIXUP_BLOCK));
			} else {
				//pIBR = (PIMAGE_FIXUP_BLOCK)(((__memory)pIBR) + sizeof(IMAGE_FIXUP_BLOCK));		
				//continue;
				break;
			}

			ofOffset = Rva2Raw(pMem, pIBR->dwPageRVA);
			fprintf(fp, "<Page Rva=\"0x%X\" Offset=\"0x%X\" Size=\"%d\">\n", pIBR->dwPageRVA, ofOffset, pIBR->dwBlockSize);

			// 修复每个入口
			for (i = 0; i < iCount; i++) {
				__memory pFixAddr = NULL;
				__offset ofRva = pIBR->dwPageRVA + pFE->offset;
				__offset ofRaw = Rva2Raw(pMem, ofRva);
				pFixAddr = pMem + ofRaw;
				// 进行重定位
#if defined(_X86_)
				fprintf(fp, "<Item>\n");
				fprintf(fp, "<Type>0x%X</Type>\n", pFE->type);
				fprintf(fp, "<Rva>0x%X</Rva>\n", ofRva);
				fprintf(fp, "<Offset>0x%X</Offset>\n", ofRaw);
				fprintf(fp, "<OrigValue>0x%X</OrigValue>\n", *(__integer *)pFixAddr);
				fprintf(fp, "</Item>\n");
				if (pFE->type == IMAGE_REL_BASED_HIGHADJ) {// This one's really fucked up.
					pFE++;
				}
#endif
				// 下一个要修复的块
				pFE++;
			}/* end for */

			fprintf(fp, "</Page>\n");
			pIBR = (PIMAGE_FIXUP_BLOCK)((__memory)pIBR + pIBR->dwBlockSize);
		}/* end while */
	}

	fprintf(fp, "</RelocateTable>\n");
	return;
}

__bool __INTERNAL_FUNC__ PeView(__memory pMem, __tchar *pResultFilePath, PPEVIEW_CONFIGURE pConfigure) {
	FILE *fp = NULL;
	__char buf[1024] = {0};

	UnicodeToAnsi(pResultFilePath, MAX_PATH, buf, 1024);
	fp = fopen(buf, "w");
	if (!fp) return FALSE;

	// 输出信息头
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(fp, "<PeView>\n");

	if (pConfigure->bPrintPEHeader) {
		PrintPEHeader(fp, pMem);
	}

	if (pConfigure->bPrintSectionHeaders) {
		PrintSectionHeaders(fp, pMem);
	}

	if (pConfigure->bPrintImportTable) {
		PrintImportTable(fp, pMem);
	}

	if (pConfigure->bPrintExportTable) {
		PrintExportTable(fp, pMem);
	}

	if (pConfigure->bPrintDebugTable) {
		PrintDebugTable(fp, pMem);
	}

	if (pConfigure->bPrintRelocateTable) {
		PrintRelocateTable(fp, pMem);
	}

	if (pConfigure->bPrintResourceTable) {
		PrintResourceTable(fp, pMem);
	}

	fprintf(fp, "</PeView>\n");
	fclose(fp);
	return TRUE;
}