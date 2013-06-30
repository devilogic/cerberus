#if !defined(__ASSEMBLERPARSE_H__)
#define __ASSEMBLERPARSE_H__

#include "AssemblerCommon.h"
#include "AssemblerRelocation.h"
#include "AssemblerEncoder.h"
#include "AssemblerImmediateMemory.h"
#include "AssemblerSymbolTable.h"
#include "AssemblerHook.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__EXTERN__ __integer *g_pAsmTokenList;
__EXTERN__ __integer g_iAsmTokenListIndex;
__EXTERN__ __integer g_iAsmTokenListMaxCount;
__EXTERN__ FPAssemblerHook g_pAssemblerHookFunc;
__EXTERN__ __bool g_bCompilingError;
__EXTERN__ __bool g_bLexAnalyzingError;
__EXTERN__ PASM_OBJ *g_pCurrAsmObjPoint;
__EXTERN__ PASM_OBJ g_pAsmObjList;//Assembler.c

#define __PreFetcherToken__() *(int *)(g_pAsmTokenList + 1)
#define __BackToken__() g_iAsmTokenIndex--

int yylex();
void yyerror(char const *pErrorMsg);
__memory __INTERNAL_FUNC__ OutputToBin(PASM_OBJ pAsmObjList, __integer *pBinSize);
	
#if defined(__cplusplus)
}
#endif

#endif
