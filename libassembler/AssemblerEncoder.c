#include "AssemblerEncoder.h"

__integer __INTERNAL_FUNC__ Encoder(__memory pInstBuf, PASM_OBJ pAsmObj, __offset ofCurrentOffset) {
	/*
	 * [Prefixes] [Opcode] [ModR/M] [SIB] [Displacement] [Immediate]
	 * 1.写入前缀(如果有的话)
	 * 2.写入操作码
	 * 3.写入ModRM | SIB(如果有的话)
	 * 4.写入偏移(如果有的话)
	 * 5.写入立即数(如果有的话)
	 * 6.写入地址标号偏移量的偏移地址(如果有的话)
	 * 7.返回指令长度
	 */
	__integer iInstLength = 0, i = 0;
	PASMER_OPERAND pOperand = (PASMER_OPERAND)&(pAsmObj->Operand);
	__logic_memcpy__(pInstBuf, pAsmObj->bPrefix, pAsmObj->bPrefixCount);
	iInstLength += pAsmObj->bPrefixCount;
	__logic_memcpy__(pInstBuf + iInstLength, pAsmObj->bOpcodes, pAsmObj->bOpcodesCount);
	iInstLength += pAsmObj->bOpcodesCount;
	if (pAsmObj->bUseModRM) {
		__logic_memcpy__(pInstBuf + iInstLength, (__memory)&(pAsmObj->ModRM), 1);
		iInstLength++;
	}
	if (pAsmObj->bUseSIB) {
		__logic_memcpy__(pInstBuf + iInstLength, (__memory)&(pAsmObj->bUseSIB), 1);
		iInstLength++;
	}
	// 遍历操作数
	for (i = 0; i < pAsmObj->bOperandCount; i++) {
		// 修订地址标号,如果不是地址标号,将是立即数
		if (pOperand[i].bAddrLabel)
			pOperand[i].ofRelocationFixOffset = ofCurrentOffset + iInstLength;

		// 写入值
		switch (pOperand[i].ValBit) {
		case ASMER_8_BITS:{
			__logic_memcpy__(pInstBuf + iInstLength, (__memory)&(pOperand[i].Val.uByte), sizeof(__byte));
			iInstLength += sizeof(__byte);
		}break;
		case ASMER_16_BITS:{
			__logic_memcpy__(pInstBuf + iInstLength, (__memory)&(pOperand[i].Val.uWord), sizeof(__word));
			iInstLength += sizeof(__word);
		}break;
		case ASMER_32_BITS:{
			__logic_memcpy__(pInstBuf + iInstLength, (__memory)&(pOperand[i].Val.uDword), sizeof(__dword));
			iInstLength += sizeof(__dword);
		}break;
		}/* end switch */
	}/* end for */
	pAsmObj->bInstLength = (__byte)iInstLength;
	return iInstLength;
}
