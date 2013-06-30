#include "Assembler.h"

PASM_OBJ g_pAsmObjList = NULL;
__bool g_bAssemblerInited = FALSE;
__integer g_iCurrAsmTokenCount = 0;
__integer g_iCurrAsmSymbolCount = 0;
__integer g_iCurrAsmImmediateWritenSize = 0;

__INLINE__ __void __INTERNAL_FUNC__ ReleaseAsmObjList(PASM_OBJ *pAsmObjListPoint) {
	PASM_OBJ pCurr = *pAsmObjListPoint, pTmp = NULL;
	while (pCurr) {
		pTmp = pCurr->pNext;
		__logic_delete__(pCurr);
		pCurr = pTmp;
	}
	*pAsmObjListPoint = NULL;
}

__void __API__ InitAssembler(PASM_SOURCE pSource, FPAssemblerHook pAssemblerHookFunc) {
	if (g_bAssemblerInited) return;//如果已经初始化则立即退出

	/*
	 * 初始化符号表, 设置汇编符号
	 */
	g_pCurrAsmObjPoint = &g_pAsmObjList;
	g_iAsmTokenListMaxCount = pSource->iTokenListMaxCount;
	g_pAsmTokenList = (__integer *)__logic_new__(__integer, g_iAsmTokenListMaxCount);
	g_iAsmTokenListIndex = 0;
	g_pAssemblerHookFunc = pAssemblerHookFunc;
	InitImmediateMemory(pSource->iImmediateMaxSize);
	InitAsmerSymbolTable(pSource->iSymbolNameLength, pSource->iSymbolMaxCount);
	g_bAssemblerInited = TRUE;
	g_iCurrAsmTokenCount = 0;
	g_iCurrAsmSymbolCount = 0;
	g_iCurrAsmImmediateWritenSize = 0;
}

extern int yyparse (void);//y.tab.c
#define __AssemblerRunFailed__()\
	g_iAsmTokenListMaxCount = g_iAsmTokenListIndex = 0;\
	__logic_delete__(g_pAsmTokenList); g_pAsmTokenList = NULL;\
	DestoryAsmerSymbolTable();\
	FreeImmediateMemory();\
	ReleaseAsmObjList(&g_pAsmObjList);\
	g_pCurrAsmObjPoint = NULL;\
	*pBinSize = 0;\
	g_bAssemblerInited = FALSE;\
	g_iCurrAsmTokenCount = 0;\
	g_iCurrAsmSymbolCount = 0;\
	g_iCurrAsmImmediateWritenSize = 0;
#define __AssemblerRunExit__				__AssemblerRunFailed__
__memory __API__ Assembler(PASM_SOURCE pSource, __integer *pBinSize, __integer iLoadBase) {
	__memory pMemory = NULL;
	__integer iBinSize = 0, iParseRet = 0;

	/*
	 * 编译为ASM_OBJ链表
	 */
	iParseRet = yyparse();
	if (iParseRet < 0) {
		/* 出错 */ 
		__AssemblerRunFailed__();
		return NULL;
	}
	
	/*
	 * 输出为2进制
	 */ 
	pMemory = OutputToBin(g_pAsmObjList, &iBinSize);
	if (!pMemory) {
		__AssemblerRunFailed__();
		return NULL;
	}

	/*
	 * 重定位
	 */
	pMemory = Relocation(pMemory, g_pAsmObjList, iLoadBase);
	if (!pMemory) {
		__AssemblerRunFailed__();
		return NULL;
	}
	
	/*
	 * 退出
	 */
	__AssemblerRunExit__();
	*pBinSize = iBinSize;
	return pMemory;
}

#define __MAX_IMMEDIATE_SIZE__		4096
#define __MAX_SYMBOL_COUNT__		128
#define __MAX_SYMBOL_NAME_LENGTH__	64
#define __MAX_TOKEN_COUNT__			4096
__void __API__ GenerateDefAsmSource(PASM_SOURCE pSource) {
	pSource->iImmediateMaxSize = __MAX_IMMEDIATE_SIZE__;
	pSource->iSymbolMaxCount = __MAX_SYMBOL_COUNT__;
	pSource->iSymbolNameLength = __MAX_SYMBOL_NAME_LENGTH__;
	pSource->iTokenListMaxCount = __MAX_TOKEN_COUNT__;
	pSource->pText = NULL;
}

__bool __API__ WriteInst(ASMER_TYPE Inst) {
	if (g_iCurrAsmTokenCount >= g_iAsmTokenListMaxCount)
		return FALSE;

	g_pAsmTokenList[g_iCurrAsmTokenCount] = Inst;
	g_iCurrAsmTokenCount++;
}

__bool __API__ WriteLabel(__char *pSymbolName) {
	if (!WriteInst(ADDR_LAB)) return FALSE;
	if (g_iCurrAsmSymbolCount >= g_iSymbolNameMaxCount)
		return FALSE;
	__logic_strcpy__(g_pSymbolList[g_iCurrAsmSymbolCount], pSymbolName);
	g_iCurrAsmSymbolCount++;
}

__bool __API__ WriteImmediate(__memory pImmediate, ASMER_BIT Bits) {
	if (Bits == ASMER_8_BITS) {
		if (!WriteInst(IMMEDIATE8)) return FALSE;
		__logic_memcpy__(g_pImmediateMemory + g_iCurrAsmImmediateWritenSize, pImmediate, 1);
		g_iCurrAsmImmediateWritenSize += 1;
		return TRUE;
	} else if (Bits == ASMER_16_BITS) {
		if (!WriteInst(IMMEDIATE16)) return FALSE;
		__logic_memcpy__(g_pImmediateMemory + g_iCurrAsmImmediateWritenSize, pImmediate, 2);
		g_iCurrAsmImmediateWritenSize += 2;
		return TRUE;
	} else if (Bits == ASMER_32_BITS) {
		if (!WriteInst(IMMEDIATE32)) return FALSE;
		__logic_memcpy__(g_pImmediateMemory + g_iCurrAsmImmediateWritenSize, pImmediate, 4);
		g_iCurrAsmImmediateWritenSize += 4;
		return TRUE;
	}
	return FALSE;
}

__bool __API__ WriteDisplacement(__memory pImmediate, ASMER_BIT Bits) {
	if (Bits == ASMER_8_BITS) {
		if (!WriteInst(DISPLACEMENT8)) return FALSE;
		__logic_memcpy__(g_pImmediateMemory + g_iCurrAsmImmediateWritenSize, pImmediate, 1);
		g_iCurrAsmImmediateWritenSize += 1;
		return TRUE;
	} else if (Bits == ASMER_32_BITS) {
		if (!WriteInst(DISPLACEMENT32)) return FALSE;
		__logic_memcpy__(g_pImmediateMemory + g_iCurrAsmImmediateWritenSize, pImmediate, 4);
		g_iCurrAsmImmediateWritenSize += 4;
		return TRUE;
	}
	return FALSE;
}
