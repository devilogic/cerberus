#include "Assembler.h"

#define ADC_Template(Inst, Label) {\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(R_AL);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_8_BITS);WriteInst(LINEND);\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(R_AX);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_16_BITS);WriteInst(LINEND);\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(R_EAX);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_32_BITS);WriteInst(LINEND);\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(R_BL);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_8_BITS);WriteInst(LINEND);\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(BYTE_PTR);WriteLabel((__char *)Label);WriteInst(MEMEND);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_8_BITS);WriteInst(LINEND);\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteInst(BYTE_PTR);WriteInst(R_EAX);WriteInst(MEMEND);WriteInst(COMMA);WriteImmediate((__memory)&iImm, ASMER_8_BITS);WriteInst(LINEND);\
}

#define JCC_Template(Inst, Label) {\
	WriteInst(LINESTART);WriteInst(## Inst ##);WriteLabel((__char *)Label);WriteInst(LINEND);\
}

int main() {
	__integer iBinSize = 0;
	__integer iImm = 0;
	ASM_SOURCE AsmSource;
	GenerateDefAsmSource(&AsmSource);
	InitAssembler(&AsmSource, NULL);
	WriteInst(LINESTART);WriteLabel((__char *)"Start");WriteInst(COLON);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(AAA);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(AAD);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(AAM);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(AAS);WriteInst(LINEND);
	ADC_Template(ADC, "Test1");
	ADC_Template(ADD, "Test2");
	JCC_Template(JO, "Test3");
	WriteInst(LINESTART);WriteInst(CALL);WriteLabel((__char *)"Start");WriteInst(LINEND);

	// Êý¾ÝÇøÓò
	WriteInst(LINESTART);WriteLabel((__char *)"Test1");WriteInst(COLON);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(NOP);WriteInst(LINEND);
	WriteInst(LINESTART);WriteLabel((__char *)"Test2");WriteInst(COLON);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(NOP);WriteInst(LINEND);
	WriteInst(LINESTART);WriteLabel((__char *)"Test3");WriteInst(COLON);WriteInst(LINEND);
	WriteInst(LINESTART);WriteInst(NOP);WriteInst(LINEND);
	WriteInst(LINESTART);WriteLabel((__char *)"Test4");WriteInst(COLON);WriteInst(LINEND);
	WriteInst(END);
	__memory pBin = Assembler(&AsmSource, &iBinSize, 0x00400000);

	return 0;
}
