#include <Windows.h>

typedef struct _IMPORT_TABLE_ITEM {
	__char szLibName[0x20];//库名称

	__bool bOrdinal;//以序号引出
	union {
		__word wOrdinal;//序号
		__char szProcName[0x40];//函数名
	};

	__address addrFirstThunk;//用于保存地址的内存地址
	__memory pFirstThunk;//用于保存地址的文件地址
	__offset ofFirstThunk;//用于保存地址的RVA

	struct _IMPORT_TABLE_ITEM *pNext;//下一个节点
} IMPORT_TABLE_ITEM, *PIMPORT_TABLE_ITEM;

__INLINE__ PIMPORT_TABLE_ITEM __INTERNAL_FUNC__ FindItemFromImportTableItems(PIMPORT_TABLE_ITEM pImportTableItems, __address addrAddress) {
	PIMPORT_TABLE_ITEM pRet = NULL;

	pRet = pImportTableItems;
	while (pRet) {

		if (pRet->addrFirstThunk == addrAddress)
			return pRet;

		pRet = pRet->pNext;
	}

	return NULL;
}

__INLINE__ __void __INTERNAL_FUNC__ ReleaseImportTableItems(PIMPORT_TABLE_ITEM *pItemsPoint) {
	PIMPORT_TABLE_ITEM pCurrItem = NULL, pNext = NULL;

	pCurrItem = *pItemsPoint;
	while (pCurrItem) {
		pNext = pCurrItem->pNext;
		__logic_delete__(pCurrItem);
		pCurrItem = pNext;
	}

	*pItemsPoint = NULL;
	return;
}

PIMPORT_TABLE_REFERENCE __INTERNAL_FUNC__ FindImportTableReferenceByFirstThunkAddress(PIMPORT_TABLE_REFERENCE pReference, __address addrFirstThunkAddress) {
	PIMPORT_TABLE_REFERENCE pRet = NULL;

	if (!pReference)
		return NULL;

	pRet = pReference;
	while (pRet) {

		if (pRet->addrFirstThunk == addrFirstThunkAddress)
			return pRet;

		pRet = pRet->pNext;
	}

	return NULL;
}

PIMPORT_TABLE_REFERENCE __API__ GenerateImportTableReference(__memory pMem) {
	ud_t ud_obj = {0};

	PIMAGE_NT_HEADERS pNtHdr = NULL;
	PIMAGE_DATA_DIRECTORY pImageImportDataDirectory = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = NULL;
	PIMAGE_SECTION_HEADER pCodeSecHdr = NULL;

	PIMPORT_TABLE_ITEM pItem = NULL;
	PIMPORT_TABLE_ITEM *pCurrItem = NULL;

	PIMPORT_TABLE_REFERENCE pReferenceImportTableAddres = NULL;
	PIMPORT_TABLE_REFERENCE *pCurrReferenceImportTableAddresPoint = NULL;

	__address addrImageBase = 0;
	__memory pCode = NULL;
	__integer iCodeSize = 0;

	pCurrItem = &pItem;
	pCurrReferenceImportTableAddresPoint = &pReferenceImportTableAddres;

	pNtHdr = (PIMAGE_NT_HEADERS)AnalyzerGetNtHeader(pMem);

	pImageImportDataDirectory = &(pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]);
	if (pImageImportDataDirectory->VirtualAddress == 0)
		return NULL;

	pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(pMem + AnalyzerRva2Raw(pMem, pImageImportDataDirectory->VirtualAddress));
	addrImageBase = pNtHdr->OptionalHeader.ImageBase;

	pCodeSecHdr = (PIMAGE_SECTION_HEADER)AnalyzerGetCodeSectionHeader(pMem);
	pCode = pMem + pCodeSecHdr->PointerToRawData;
	iCodeSize = pCodeSecHdr->SizeOfRawData;

	// 遍历引入表
	while (pImageImportDescriptor->FirstThunk) {
		__address addrCurrAddress = 0;
		__integer iCurrRva = 0, iProcCount = 0, iLibCount = 0;
		__char *svDllName = NULL;
		PIMAGE_THUNK_DATA pTdIn = NULL;
		PIMAGE_THUNK_DATA pTdOut = NULL;
		
		// 获取库名
		svDllName = (__char *)(pMem + AnalyzerRva2Raw(pMem, pImageImportDescriptor->Name));

		// 记录库名

		// 填充引入表地址
		pTdIn = (PIMAGE_THUNK_DATA)(pMem + AnalyzerRva2Raw(pMem, pImageImportDescriptor->OriginalFirstThunk));
		pTdOut = (PIMAGE_THUNK_DATA)(pMem + AnalyzerRva2Raw(pMem, pImageImportDescriptor->FirstThunk));
		// 没有OriginalFirstThunk的情况
		if ((__memory)pTdIn == pMem)
			pTdIn = pTdOut;

		iLibCount = 0;
		iProcCount = 0;
		addrCurrAddress = addrImageBase + pImageImportDescriptor->FirstThunk;

		// 加密函数
		while (pTdIn->u1.Function) {
			// 申请内存
			(*pCurrItem) = (PIMPORT_TABLE_ITEM)__logic_new__(IMPORT_TABLE_ITEM, 1);
			__logic_strcpy__((*pCurrItem)->szLibName, svDllName);

			// 以序号引出还是以函数名引出
			if (pTdIn->u1.Ordinal & IMAGE_ORDINAL_FLAG32) {
				(*pCurrItem)->bOrdinal = TRUE;
				(*pCurrItem)->wOrdinal = pTdIn->u1.Ordinal;
			} else {
				__char *szProcName = NULL;
				PIMAGE_IMPORT_BY_NAME pIbn = NULL;

				pIbn = (PIMAGE_IMPORT_BY_NAME)(pMem + AnalyzerRva2Raw(pMem, pTdIn->u1.AddressOfData));
				szProcName = (__char *)(pIbn->Name);

				__logic_strcpy__((*pCurrItem)->szProcName, szProcName);
			}

			// 记录FirstThunk
			(*pCurrItem)->addrFirstThunk = addrCurrAddress;
			(*pCurrItem)->ofFirstThunk = (__offset)(addrCurrAddress - addrImageBase);
			(*pCurrItem)->pFirstThunk = (__memory)pTdOut;
			pCurrItem = &((*pCurrItem)->pNext);

			// 下一个函数
			addrCurrAddress += sizeof(__address);
			iProcCount++;//函数计数增加
			pTdIn++;
			pTdOut++;
		}/* end while */

		// 下一个DLL
		pImageImportDescriptor++;
		iLibCount++;
	}/* end while */

	// 找代码段中的引用
	ud_init(&ud_obj);
	ud_set_input_buffer(&ud_obj, pCode, iCodeSize);
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

			/*
			 * 这里仅处理MOV,CALL,JMP 三条指令
			 * 因为不同编译只有这三条指令会对引入表造成访问
			 */
			if (ud_obj.mnemonic == UD_Imov) {
				if ((ud_obj.operand[1].type == UD_OP_MEM) && (ud_obj.operand[1].base == UD_NONE) && \
					(ud_obj.operand[1].index == UD_NONE) && (ud_obj.operand[1].size == 32)) {
						pCurrOperand = &(ud_obj.operand[1]);
						pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
				}
			} else if ((ud_obj.mnemonic == UD_Icall) || (ud_obj.mnemonic == UD_Ijmp)) {
				if ((ud_obj.operand[0].type == UD_OP_MEM) && (ud_obj.operand[0].base == UD_NONE) && \
					(ud_obj.operand[0].index == UD_NONE) && (ud_obj.operand[0].offset) && (ud_obj.operand[0].size == 32)) {
						pCurrOperand = &(ud_obj.operand[0]);
						pFileSaveAddress = (__memory)(ud_obj.inp_buff) - sizeof(__dword);
				}
			}

			if (pFileSaveAddress) {
				PIMPORT_TABLE_ITEM pMyItem = NULL;
				__memory pCurrInstFileAddress = ud_obj.inp_buff - ud_obj.inp_ctr;
				/*
				 * 如果是内存访问操作
				 * 取出地址与跳转地址表中进行检索
				 */
				__address addrTargetAddress = (__address)(pCurrOperand->lval.sdword);

				// 寻找对应的引入地址表
				pMyItem = FindItemFromImportTableItems(pItem, addrTargetAddress);
				if (pMyItem) {
					// 设置一个引入表引用结构
					(*pCurrReferenceImportTableAddresPoint) = (PIMPORT_TABLE_REFERENCE)__logic_new__(IMPORT_TABLE_REFERENCE, 1);

					__logic_memcpy__(&((*pCurrReferenceImportTableAddresPoint)->ud_obj), &ud_obj, sizeof(ud_t));
					__logic_strcpy__((*pCurrReferenceImportTableAddresPoint)->szLibName, pMyItem->szLibName);
					__logic_strcpy__((*pCurrReferenceImportTableAddresPoint)->szProcName, pMyItem->szProcName);

					(*pCurrReferenceImportTableAddresPoint)->ofFirstThunk = pMyItem->ofFirstThunk;
					(*pCurrReferenceImportTableAddresPoint)->addrFirstThunk = pMyItem->addrFirstThunk;
					(*pCurrReferenceImportTableAddresPoint)->ofFirstThunkFileOffset = pMyItem->pFirstThunk - pMem;

					(*pCurrReferenceImportTableAddresPoint)->ofAddressReferenceRVA = AnalyzerRaw2Rva(pMem, (__integer)(pCurrInstFileAddress - pMem));
					(*pCurrReferenceImportTableAddresPoint)->addrAddressReferenceMemAddress = addrImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pCurrInstFileAddress - pMem));
					(*pCurrReferenceImportTableAddresPoint)->ofAddressReferenceFileOffset = pCurrInstFileAddress - pMem;

					(*pCurrReferenceImportTableAddresPoint)->ofReferenceRVA = AnalyzerRaw2Rva(pMem, (__integer)(pFileSaveAddress - pMem));
					(*pCurrReferenceImportTableAddresPoint)->addrReferenceMemAddress = addrImageBase + AnalyzerRaw2Rva(pMem, (__integer)(pFileSaveAddress - pMem));
					(*pCurrReferenceImportTableAddresPoint)->ofReferenceFileOffset = pFileSaveAddress - pMem;

					// 移动到下一个
					pCurrReferenceImportTableAddresPoint = &((*pCurrReferenceImportTableAddresPoint)->pNext);
				}
			}/* end if */
		}/* end if */
	}/* end while */

	// 释放引入表项
	ReleaseImportTableItems(&pItem);
	return pReferenceImportTableAddres;
}

__void __API__ ReleaseImportTableReference(PIMPORT_TABLE_REFERENCE *pImportTableReferencePoint) {
	PIMPORT_TABLE_REFERENCE pCurrItem = NULL, pNext = NULL;

	pCurrItem = *pImportTableReferencePoint;
	while (pCurrItem) {
		pNext = pCurrItem->pNext;
		__logic_delete__(pCurrItem);
		pCurrItem = pNext;
	}

	*pImportTableReferencePoint = NULL;
	return;
}