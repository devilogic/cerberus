#include "AssemblerCommon.h"

// 获取寄存器索引
__integer __INTERNAL_FUNC__ GetRegisterIndex(ASMER_TYPE Reg) {
	__integer iIndex;
	switch (Reg){
	case R_AL: case R_AX: case R_EAX: case SEG_ES:
	case R_CR0: case R_DR0: case R_MM0: case R_ST0:
	case R_XMM0: iIndex = 0; break;
	case R_CL: case R_CX: case R_ECX: case SEG_CS:
	case R_CR1: case R_DR1: case R_MM1: case R_ST1:
	case R_XMM1: iIndex = 1; break;
	case R_DL: case R_DX: case R_EDX: case SEG_SS:
	case R_CR2: case R_DR2: case R_MM2: case R_ST2:
	case R_XMM2: iIndex = 2; break;
	case R_BL: case R_BX: case R_EBX: case SEG_DS:
	case R_CR3: case R_DR3: case R_MM3: case R_ST3:
	case R_XMM3: iIndex = 3; break;
	case R_AH: case R_SP: case R_ESP: case SEG_FS:
	case R_CR4: case R_DR4: case R_MM4: case R_ST4:
	case R_XMM4: iIndex = 4; break;
	case R_CH: case R_BP: case R_EBP: case SEG_GS:
	case R_CR5: case R_DR5: case R_MM5: case R_ST5:
	case R_XMM5: iIndex = 5; break;
	case R_DH: case R_SI: case R_ESI: case R_CR6:
	case R_DR6: case R_MM6: case R_ST6:
	case R_XMM6: iIndex = 6; break;
	case R_BH: case R_DI: case R_EDI: case R_CR7:
	case R_DR7: case R_MM7: case R_ST7:
	case R_XMM7: iIndex = 7; break;
	default: iIndex = 0;}
	return iIndex;
}

__void __INTERNAL_FUNC__ SetOperand(PASMER_OPERAND pOperand, __bool bAddressLabel, ASMER_TYPE OptType, ASMER_BIT OptBit, ASMER_TYPE RegBase, \
									ASMER_TYPE RegIndex, __byte MemScale, ASMER_BIT ValueBit, __dword OptValue, __char *pAddressLabelSymbolName, \
									__offset RelocationFixOffset, PASMER_SYMBOL_NODE pCurrSymbolNode) {
	pOperand->bAddrLabel = bAddressLabel;
	pOperand->Type = OptType;
	pOperand->Bit = OptBit;
	pOperand->Base = RegBase;
	pOperand->Index = RegIndex;
	pOperand->Scale = MemScale;
	pOperand->ValBit = ValueBit;
	pOperand->Val.uDword = (__dword)OptValue;
	pOperand->ofRelocationFixOffset = RelocationFixOffset;
	//pOperand->pAddrLabelSymbolName = pAddressLabelSymbolName;//因为每条指令只允许地址出现一次,所以直接在ASM_OBJ中查询
	//pOperand->pSymbolNode = pCurrSymbolNode;//不需要此项
}

__void __INTERNAL_FUNC__ SetOperandWithoutVal(PASMER_OPERAND pOperand, ASMER_TYPE OptType, ASMER_BIT OptBit, ASMER_TYPE RegBase, ASMER_TYPE RegIndex) {
	pOperand->Type = OptType;
	if (OptType == OP_REG) pOperand->bIsRegister = TRUE;
	else if (OptType == OP_IMM) pOperand->bIsImmediate = TRUE;
	else if (OptType == OP_MEM) pOperand->bIsMem = TRUE;
	pOperand->Bit = OptBit;
	pOperand->Base = RegBase;
	pOperand->Index = RegIndex;
}

__void __INTERNAL_FUNC__ SetAsmObj(PASM_OBJ pAsmObj, INST_CLASS InstructionClass, ASMER_TYPE Instruction, __void *pOpcodes, __byte bNumberOfOpcodes, __byte bOpcodeEx) {
	pAsmObj->InstClass = InstructionClass;
	pAsmObj->Inst = Instruction;
	__logic_memcpy__(pAsmObj->bOpcodes, pOpcodes, bNumberOfOpcodes);
	pAsmObj->bOpcodesCount = bNumberOfOpcodes;
	if (bOpcodeEx <= 7) pAsmObj->bUseOpEx = TRUE;
	else pAsmObj->bUseOpEx = FALSE;
	pAsmObj->bOpEx = bOpcodeEx;
}

__void __INTERNAL_FUNC__ AssemblerPrintAsmObj(PASM_OBJ pAsmObj) {
	__PrintDbgInfo__("Print Asm Object:");
	__PrintDbgInfo_DumpMemory__("Opcode:", (__memory)&(pAsmObj->bOpcodes), pAsmObj->bOpcodesCount);
}
