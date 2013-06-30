/*
 * 此文件专门为调试分析器所用
 * 使用VS自定义宏_DEBUG进行开启或者关闭
 */
#if defined(_DEBUG)
#include <stdio.h>
__void __INTERNAL_FUNC__ PrintProcedureListCount(PPROCEDURE pProcedureList) {
	PPROCEDURE pCurr = pProcedureList;
	__integer iCount = 0;
	while (pCurr) {
		iCount++;
		pCurr = pCurr->pNext;
	}
	__PrintDbgInfo__("Total of procedure:%d\n", iCount);
}

__void __INTERNAL_FUNC__ PrintProcedure(PPROCEDURE pProcedure) {
	__PrintDbgInfo__("Block:");
	if (pProcedure->bBlock) {
		__PrintDbgInfo__("TRUE");
	} else {
		__PrintDbgInfo__("FALSE");
	}
	__PrintDbgInfo__("\n");
	__PrintDbgInfo__("File start address:0x%4X\n", (__integer)pProcedure->pFileStartAddress);
	__PrintDbgInfo__("Memory start address:0x%4X\n", (__integer)pProcedure->addrMemoryStartAddress);
	__PrintDbgInfo__("Procedure size(bytes):%d\n", (__integer)pProcedure->iSize);
}

__void __INTERNAL_FUNC__ PrintProcedureList(PPROCEDURE pProcedureList) {
	PPROCEDURE pCurr = pProcedureList;
	__integer iCount = 0;
	while (pCurr) {
		__PrintDbgInfo__("%d----------\n", iCount);
		PrintProcedure(pCurr);
		iCount++;
		pCurr = pCurr->pNext;
	}
}

__void __INTERNAL_FUNC__ CheckSameAddressProcedure(PPROCEDURE pProcedureList) {
	PPROCEDURE pCurr1 = pProcedureList, pCurr2 = pProcedureList;
	__integer iCount = 0;
	while (pCurr1) {
		pCurr2 = pProcedureList;
		while (pCurr2) {
			if ((pCurr1->addrMemoryStartAddress == pCurr2->addrMemoryStartAddress) && (pCurr1 != pCurr2)) {
				__PrintDbgInfo__("Check address = 0x%4X\n", pCurr1->addrMemoryStartAddress);
				__PrintDbgInfo__("Check Procedure = 0x%4X, Same Procedure = 0x%4X\n", (__integer)pCurr1, (__integer)pCurr2);
				iCount++;
			}
			pCurr2 = pCurr2->pNext;
		}/* end while */
		pCurr1 = pCurr1->pNext;
	}
	__PrintDbgInfo__("Total of procedure struct point to same address = %d\n", iCount);
}

__void __INTERNAL_FUNC__ CheckInstructionsParents(PPROCEDURE pProcedureList) {
	PPROCEDURE pCheckProcedure = pProcedureList;
	while (pCheckProcedure) {
		if (pCheckProcedure->pInstruction) {
			if (pCheckProcedure != pCheckProcedure->pInstruction->pParents) {
				__PrintDbgInfo__("Procedure struct = 0x%4X\n", pCheckProcedure);
				__PrintDbgInfo__("Procedure MemoryAddress = 0x%4X\n", pCheckProcedure->addrMemoryStartAddress);
				__PrintDbgInfo__("Instruct struct = 0x%4X\n", pCheckProcedure->pInstruction);
				__PrintDbgInfo__("Instruct struct's parents = 0x%4X\n", pCheckProcedure->pInstruction->pParents);
				__PrintDbgInfo__("----------\n");
			}
		}
		pCheckProcedure = pCheckProcedure->pNext;
	}
}

__void __INTERNAL_FUNC__ CheckProcedureList1(PPROCEDURE pProcedureList) {
	PPROCEDURE pCheckProcedure = pProcedureList;
	while (pCheckProcedure) {
		if (pCheckProcedure->pNext) {
			if (pCheckProcedure->addrMemoryStartAddress + pCheckProcedure->iSize != pCheckProcedure->pNext->addrMemoryStartAddress) {
				__PrintDbgInfo__("Curr + Size != Next\n");
				__PrintDbgInfo__("Curr procedure = 0x%4X\n", pCheckProcedure->addrMemoryStartAddress);
				__PrintDbgInfo__("Next procedure = 0x%4X\n", pCheckProcedure->pNext->addrMemoryStartAddress);
				__PrintDbgInfo__("----------\n");
			}
		}
		pCheckProcedure = pCheckProcedure->pNext;
	}
}

__void __INTERNAL_FUNC__ CheckProcedureList2(PPROCEDURE pProcedureList) {
	PPROCEDURE pCheckProcedure = pProcedureList;
	while (pCheckProcedure) {
		if (pCheckProcedure->pNext) {
			if (pCheckProcedure->addrMemoryStartAddress + pCheckProcedure->iSize > pCheckProcedure->pNext->addrMemoryStartAddress) {
				__PrintDbgInfo__("Curr + Size > Next\n");
				__PrintDbgInfo__("Curr procedure = 0x%4X,Size = 0x%X\n", pCheckProcedure->addrMemoryStartAddress, pCheckProcedure->iSize);
				__PrintDbgInfo__("Curr procedure + Size = 0x%X\n", pCheckProcedure->addrMemoryStartAddress + pCheckProcedure->iSize);
				__PrintDbgInfo__("Next procedure = 0x%4X,Size = 0x%X\n", pCheckProcedure->pNext->addrMemoryStartAddress, pCheckProcedure->pNext->iSize);
				__PrintDbgInfo__("----------\n");
			}
		}
		pCheckProcedure = pCheckProcedure->pNext;
	}
}

__void __INTERNAL_FUNC__ CheckSortProcedureList(PPROCEDURE pProcedureList) {
	PPROCEDURE pCurr1 = pProcedureList;

	while (pCurr1) {
		if (pCurr1->pNext) {
			if (pCurr1->addrMemoryStartAddress > pCurr1->pNext->addrMemoryStartAddress) {
				__PrintDbgInfo__("Check address = 0x%4X\n", pCurr1->addrMemoryStartAddress);
				__PrintDbgInfo__("Next address = 0x%4X\n", pCurr1->pNext->addrMemoryStartAddress);
			}
		}
		pCurr1 = pCurr1->pNext;
	}/* end while */
}

#define __PrintProcedure__(pProcedure)					PrintProcedure(pProcedure)
#define __PrintProcedureList__(pProcedureList)			PrintProcedureList(pProcedureList)
#define __PrintProcedureListCount__(pProcedureList)		PrintProcedureListCount(pProcedureList)
#define __CheckSameAddressProcedure__(pProcedureList)	CheckSameAddressProcedure(pProcedureList)
#define __CheckInstructionsParents__(pProcedureList)	CheckInstructionsParents(pProcedureList)
#define __CheckProcedureList1__(pProcedureList)			CheckProcedureList1(pProcedureList)
#define __CheckProcedureList2__(pProcedureList)			CheckProcedureList2(pProcedureList)
#define __CheckSortProcedureList__(pProcedureList)		CheckSortProcedureList(pProcedureList)

#else
#define __PrintProcedure__(pProcedure)
#define __PrintProcedureList__(pProcedureList)
#define __PrintProcedureListCount__(pProcedureList)
#define __CheckSameAddressProcedure__(pProcedureList)
#define __CheckInstructionsParents__(pProcedureList)
#define __CheckProcedureList1__(pProcedureList)
#define __CheckProcedureList2__(pProcedureList)
#define __CheckSortProcedureList__(pProcedureList)

#endif
