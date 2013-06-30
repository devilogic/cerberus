#include "x64Encoder.h"

// 前缀16位
#define PREFIX_66 0x66
#define PREFIX_67 0x67
#define REX_W 0x48

#define __SetPrefix66__(pInstBuf)	__MemPut8Bits__(pInstBuf, PREFIX_66)
#define __SetREX_W__(pInstBuf)      __MemPut8Bits__(pInstBuf, REX_W)

__INLINE__ __integer __INTERNAL_FUNC__ SetComplexCode(PASM_OBJ pAsmObj, __memory *pInstBufPoint, __memory pOpcodes, __integer iOpcodesCount, __byte bOpEx) {
	__integer iIndex = 0, iModRMSIB = 0;
	if (pAsmObj->bUseREX) {
		*(pInstBuf + iIndex) = GetREX(pAsmObj);
		iIndex++;
	}
	memcpy(pInstBuf + iIndex, pOpcodes, iOpcodesCount);
	iIndex += iOpcodesCount;
	iModeRMSIB = MakeCode(pAsmObj, bOpEx);
	if (iModeRMSIB == 1)
		*(pInstBuf + iIndex) = GetModRM(pAsmObj);
	else {
		*(pInstBuf + iIndex) = GetModRM(pAsmObj);
		*(pInstBuf + iIndex + 1) = GetSIB(pAsmObj);
	}
	iIndex += iModRMSIB;

	/*
	 * 设置偏移, 如果存在的话
	 */ 
	if (pAsmObj->bHasDisplacement) {
		__byte bIndex = pAsmObj->bDisplacementOwn;
		PASMER_OPERAND pCurrOpt = &(pAsmObj->Operand[bIndex]);
		if (pAsmObj->Operand[bIndex].OffsetBit == ASMER_8_BITS) {
			*(__byte *)(pInstBuf + iIndex) = pCurrOpt->Val.uByte;
			iIndex++;
		} else if (pAsmObj->Operand[bIndex].OffsetBit == ASMER_16_BITS) {
			*(__word *)(pInstBuf + iIndex) = pCurrOpt->Val.uWord;
			iIndex += 2;			
		} else if (pAsmObj->Operand[bIndex].offsetBit == ASMER_32_BITS) {
			*(__dword *)(pInstBuf + iIndex) = pCurrOpt->Val.uDword;
			iIndex += 4;
		}
	}
	
	(*pInstBufPoint) += iIndex;
	return iIndex;
}

/*
 * !注:以下文件不得变动
 */
#include "OptForm.c"
#include "x86.c"
#include "FPU.c"
#include "SIMD.c"
#include "VMX.c"

__integer __INTERNAL_FUNC__ Encoder(PASM_OBJ pAsmObj, __memory pInstBuf) {
	__integer iInstLength = 0;
	if (pAsmObj->InstClass == IC_X86)
		iInstLength = Asm_x86(pAsmObj, pInstBuf);
	else if (pAsmObj->InstClass == IC_FPU)
		iInstLength = Asm_FPU(pAsmObj, pInstBuf);
	else if (pAsmObj->InstClass == IC_SIMD)
		iInstLength = Asm_SIMD(pAsmObj, pInstBuf);
	else
		iInstLength = Asm_x86(pAsmObj, pInstBuf);
	
	return iInstLength;
}
