#if !defined(__ASSEMBLERSYMBOLTABLE_H__)
#define __ASSEMBLERSYMBOLTABLE_H__

#include "AssemblerCommon.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__EXTERN__ __char **g_pSymbolList;
__EXTERN__ __integer g_iSymbolNameMaxCount;

__void __INTERNAL_FUNC__ BackSymbol();
__integer __INTERNAL_FUNC__ GetNowSymbolIndex();
__char * __INTERNAL_FUNC__ NextSymbol();
__void __INTERNAL_FUNC__ InitAsmerSymbolTable(__integer iSymbolNameLength, __integer iSymbolNameCount);
PASMER_SYMBOL_NODE __INTERNAL_FUNC__ QuerySymbolFromTable(__char *pName);
PASMER_SYMBOL_NODE __INTERNAL_FUNC__ AddSymbolToTable(__char *pName, __offset ofOffset, ASMER_SYMBOL_TYPE Type);
__void __INTERNAL_FUNC__ DestoryAsmerSymbolTable();

#if defined(__cplusplus)
}
#endif

#endif
