#include "AssemblerParse.h"

/*
 * 全局变量
 */
__bool g_bCompilingError = FALSE;
__bool g_bLexAnalyzingError = FALSE;
__integer *g_pAsmTokenList = NULL;
__integer g_iAsmTokenListMaxCount = 0;
__integer g_iAsmTokenListIndex = 0;
FPAssemblerHook g_pAssemblerHookFunc = NULL;
PASM_OBJ *g_pCurrAsmObjPoint = NULL;
__byte g_bInstBuf[16];//指令临时内存, 一条指令最长15个字节

/*
 * 自定义的yylex函数
 * 非lex生成
 * 出错返回-1 
 * 成功结束返回0
 */
int yylex() {
	int iToken = *(int *)(g_pAsmTokenList + g_iAsmTokenListIndex);
	g_iAsmTokenListIndex++;
	if (iToken == END) return 0;
	else if (iToken == ERROR) {
		g_bLexAnalyzingError = TRUE;
		return -1;
	}
	return iToken;
}

void yyerror(char const *pErrorMsg) {
	/* 出错暂时什么也不做 */
	//fprintf(stderr, pErrorMsg);
}

__INLINE__ __integer __INTERNAL_FUNC__ OutputOneInst(PASM_OBJ pCurrAsmObj, __offset ofCurrentOffset) {
	__logic_memset__(g_bInstBuf, 0, 0x10);
	// 存在HOOK函数则调用
	if (g_pAssemblerHookFunc) return g_pAssemblerHookFunc(g_bInstBuf, pCurrAsmObj, ofCurrentOffset);
	return Encoder(g_bInstBuf, pCurrAsmObj, ofCurrentOffset);
}

__INLINE__ PASM_OBJ __INTERNAL_FUNC__ SkipAddrLabelInfo(PASM_OBJ pAsmObj) {
	while (pAsmObj) {
		if (pAsmObj->bAddrLabel)
			pAsmObj = pAsmObj->pNext;//返回下一个节点
		else
			break;
	}
	return pAsmObj;
}

#define __OutputToBinFailed__()\
	g_bCompilingError = TRUE;\
		if (pBin) __logic_delete__(pBin);\
	*pBinSize = 0;\
	return NULL;
__memory __INTERNAL_FUNC__ OutputToBin(PASM_OBJ pAsmObjList, __integer *pBinSize) {
	/*
	 * 初始化数据
	 */ 
	__memory pBin = NULL;
	__integer iInstLength = 0;
	__offset ofOffset = 0;
	PASM_OBJ pCurr = pAsmObjList;
	g_bCompilingError = FALSE;
	g_bLexAnalyzingError = FALSE;
	
	while (pCurr) {		
		/*
		 * 跳过地址标号
		 */
		pCurr = SkipAddrLabelInfo(pCurr);
		if (!pCurr) break;//防止最后一条指令是地址标号的情况
		pCurr->ofOffset = ofOffset;//当前指令偏移
		iInstLength = OutputOneInst(pCurr, ofOffset);
		
		/*
		 * 输出一条指令失败
		 */ 
		if (!iInstLength) {
			__OutputToBinFailed__();
		}
		/*
		 * 输出指令到内存
		 */ 
		InputValueToMemory(&pBin, (__integer)ofOffset, g_bInstBuf, iInstLength);
		ofOffset += (__offset)iInstLength;
		pCurr->bInstLength = (__byte)iInstLength;
		pCurr = pCurr->pNext;//下一个节点
	}

	/*
	 * 建立地址标号信息
	 */
	BuildAddrLabelInfo(pAsmObjList);

	*pBinSize = (__integer)ofOffset;
	return pBin;
}
