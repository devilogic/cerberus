#include "AnalyzeBin.h"
#include <string.h>

/*
 * 全局变量
 */
FPRva2Raw AnalyzerRva2Raw = NULL;
FPRaw2Rva AnalyzerRaw2Rva = NULL;
FPGetCodeSectionHeader AnalyzerGetCodeSectionHeader = NULL;
FPGetNtHeader AnalyzerGetNtHeader = NULL;

/*
 * !注:以下顺序统一进行排列,顺序不能错乱
 */
#include "AnalyzerDebug.c"//调试函数
#include "CheckValidAddress.c"//检查地址的有效性
#include "ImportTableReference.c"//分析引入表引用
#include "AnalyzeInstruction.c"//分析指令
#include "AnalyzeProcedure.c"//分析函数

PPROGRAM __INTERNAL_FUNC__ InitProgram(PANALYZE_CONFIGURE pAnalyzeConfigure) {
	PPROGRAM pProgram = __logic_new__(PROGRAM, 1);
	if (!pProgram) return NULL;
	__logic_memset__(pProgram, 0, sizeof(PROGRAM));
	__logic_memcpy__(&(pProgram->AnalyzeConfigure), pAnalyzeConfigure, sizeof(ANALYZE_CONFIGURE));
	return pProgram;
}

__void __API__ ReleaseProgram(PPROGRAM *pProgramPoint) {
	PPROGRAM pProgram = NULL;

	pProgram = *pProgramPoint;
	ReleaseImportTableReference(&(pProgram->pImportTableReference));
	if (pProgram->pProcedureList)
		ReleaseProcedureList(&(pProgram->pProcedureList));
	__logic_delete__(*pProgramPoint);
	*pProgramPoint = NULL;
}

/*
 * 通过一个PE文件映射指针(pMem),得到一个PROGRAM结构的指针
 * 返回的结构指针的内存由本程序分配,使用完毕后通过
 * ReleaseProgram函数释放它
 */
PPROGRAM __API__ AnalyzeProgram(PANALYZE_CONFIGURE pAnalyzeConfigure, PANALYZE_BASIC_INFO pAnalyzeBasicInfo) {
	__integer iProcCount = 0;
	PPROCEDURE pCurrProcCount = NULL;
	PPROGRAM pProgram = InitProgram(pAnalyzeConfigure);
	if (!pProgram) return NULL;
	
	pProgram->pMem = pAnalyzeBasicInfo->pMem;
	pProgram->ImageBase = pAnalyzeBasicInfo->ImageBase;
	pProgram->pCodeSeg = pAnalyzeBasicInfo->pCodeSeg;
	pProgram->pTailData = pAnalyzeBasicInfo->pTailData;
	pProgram->addrCodeSegMemoryAddress = pAnalyzeBasicInfo->addrCodeSegMemoryAddress;
	pProgram->iBinSize = pAnalyzeBasicInfo->iBinSize;
	pProgram->iCodeSegSize = pAnalyzeBasicInfo->iCodeSegSize;
	pProgram->iTailDataSize = pAnalyzeBasicInfo->iTailDataSize;
	// 查看是否拥有指定的入口点,如果有指定入口点,则使用指定入口点分析
	if (pAnalyzeConfigure->addrFromHereStartAnalyze == 0)
		pProgram->iEntryRva = pAnalyzeBasicInfo->iEntryRva;
	else
		pProgram->iEntryRva = pAnalyzeConfigure->addrFromHereStartAnalyze - pAnalyzeBasicInfo->ImageBase;
	AnalyzerRva2Raw = pAnalyzeBasicInfo->pRva2Raw;
	AnalyzerRaw2Rva = pAnalyzeBasicInfo->pRaw2Rva;
	AnalyzerGetCodeSectionHeader = pAnalyzeBasicInfo->pGetCodeSectionHeader;
	AnalyzerGetNtHeader = pAnalyzeBasicInfo->pGetNtHeader;

	// 是否进行引入表分析
	if (pAnalyzeConfigure->bEnableImportTableReference)
		pProgram->pImportTableReference = GenerateImportTableReference(pProgram->pMem);
		
	// 进入第一次遍历分析,找出从入口点函数所有的交叉引用函数
	pProgram->pProcedureList = AnalyzeProcedurePass1(pProgram);
	pProgram->pEntryProcedure = FindEntryProcedure(pProgram->pProcedureList);

	// 计算函数的总数
	pCurrProcCount = pProgram->pProcedureList;
	pProgram->iProcCount = CountProcedureList(pCurrProcCount);
	pProgram->iAllBlockCount = CountAllBloackList(pCurrProcCount);

	return pProgram;
}

PX86INSTRUCTION __API__ FindInstructionByAddress(PPROGRAM pProgram, __address addrInstruction) {
	PX86INSTRUCTION pCurrInst = NULL;
	// 遍历函数链
	PPROCEDURE pCurrProc = pProgram->pProcedureList;
	while (pCurrProc) {
		if ((pCurrProc->addrMemoryStartAddress >= addrInstruction) && (addrInstruction < (pCurrProc->addrMemoryStartAddress + pCurrProc->iSize))) {
			// 遍历指令链
			pCurrInst = pCurrProc->pInstruction;
			while (pCurrInst) {
				if (pCurrInst->addrCurrMemoryAddress == addrInstruction)
					return pCurrInst;
				pCurrInst = pCurrInst->pNext;
			}
		}
		pCurrProc = pCurrProc->pNext;
	}
	return NULL;
}

PPROCEDURE __API__ FindProcedureByAddress(PPROGRAM pProgram, __address addrProcedure) {
	PPROCEDURE pCurrProc = pProgram->pProcedureList;
	while (pCurrProc) {
		if (pCurrProc->addrMemoryStartAddress == addrProcedure)
			return pCurrProc;
		pCurrProc = pCurrProc->pNext;
	}
	return NULL;
}

PPROCEDURE __API__ FindProcedureByInsideAddress(PPROGRAM pProgram, __address addrAddress) {
	PPROCEDURE pCurrProc = pProgram->pProcedureList;
	while (pCurrProc) {
		if ((pCurrProc->addrMemoryStartAddress >= addrAddress) && (addrAddress < (pCurrProc->addrMemoryStartAddress + pCurrProc->iSize)))
			return pCurrProc;
		pCurrProc = pCurrProc->pNext;
	}
	return NULL;
}
