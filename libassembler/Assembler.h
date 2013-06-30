#if !defined(__ASSEMBLER_H__)
#define __ASSEMBLER_H__

#include "AssemblerParse.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__void __API__ InitAssembler(PASM_SOURCE pSource, FPAssemblerHook pAssemblerHookFunc);
__memory __API__ Assembler(PASM_SOURCE pSource, __integer *pBinSize, __integer iLoadBase);
__void __API__ GenerateDefAsmSource(PASM_SOURCE pSource);
__bool __API__ WriteInst(ASMER_TYPE Inst);
__bool __API__ WriteLabel(__char *pSymbolName);
__bool __API__ WriteImmediate(__memory pImmediate, ASMER_BIT Bits);
__bool __API__ WriteDisplacement(__memory pImmediate, ASMER_BIT Bits);

#if defined(__cplusplus)
}
#endif

#endif
