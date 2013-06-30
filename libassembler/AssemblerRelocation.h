#if !defined(__ASSEMBLERRELOCATION_H__)
#define __ASSEMBLERRELOCATION_H__

#if defined(__cplusplus)
extern "C"
{
#endif
	
#include "AssemblerCommon.h"
#include "AssemblerSymbolTable.h"	

__void __INTERNAL_FUNC__ BuildAddrLabelInfo(PASM_OBJ pAsmObjList);
__memory __INTERNAL_FUNC__ Relocation(__memory pBin, PASM_OBJ pAsmObjList, __integer iLoadBase);
	
#if defined(__cplusplus)
}
#endif

#endif
