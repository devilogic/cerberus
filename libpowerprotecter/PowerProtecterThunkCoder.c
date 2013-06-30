// 引发异常的指令表
#define __MAX_EXCEPTIONINSTR_NUM__		18
__CONST__ __byte g_ExceptionInstrTable[__MAX_EXCEPTIONINSTR_NUM__] = {
	0x6C,	//insb							1
	0x6D,	//insw/insd						2
	0x6E,	//outsb							3
	0x6F,	//outsw/outsd					4
	0xCC,	//int3							5
	0xCF,	//iret							6
	0xE4,	//in	al, imm8				7
	0xE5,	//in	ax/eax, imm8			8	
	0xE6,	//out	imm8, al				9
	0xE7,	//out	imm8, ax/eax			10
	0xEC,	//in	al, dx					11
	0xED,	//in	ax/eax, dx				12
	0xEE,	//out	dx, al					13
	0xEF,	//out dx, ax/eax				14
	0xF1,	//int1							15
	0xF4,	//hlt							16
	0xFA,	//cli							17
	0xFB	//sti							18
};

__byte __INTERNAL_FUNC__ PowerProtecterRandGetExceptionInst() {
	__dword dwRand;
	dwRand = GenerateRandomNumber() % __MAX_EXCEPTIONINSTR_NUM__;
	return (__byte)(g_ExceptionInstrTable[dwRand]);
}

// 流程指令
#define __MAX_JMPINSTR_NUM__		17
__CONST__ __byte g_JmpCode[__MAX_JMPINSTR_NUM__] = {
	0x77,	//								1
	0x73,	//								2
	0x72,	//								3
	0x76,	//								4
	0xE3,	//								5
	0x74,	//								6
	0x7F,	//								7
	0x7D,	//								8
	0x7C,	//								9
	0x7E,	//								10
	0x75,	//								11
	0x71,	//								12
	0x7B,	//								13
	0x70,	//								14
	0x7A,	//								15
	0x78,	//								16
	0xEB	//								17
};
__INLINE__ __byte __INTERNAL_FUNC__ RandJmpCode() {
	__byte bCode = 0;
	__integer iIndex = 0;
	iIndex = GenerateRandomNumber() % __MAX_JMPINSTR_NUM__;
	bCode = g_JmpCode[iIndex];
	return bCode;
}

#define __MAX_ONE_BYTE_INSTRUCTION__		118
__CONST__ __byte g_OneByteInstruction[__MAX_ONE_BYTE_INSTRUCTION__] = {
	0x37,
	0x3F,
	0x14,
	0x15,
	0x04,
	0x05,
	0x24,
	0x25,
	0x63,
	0x62,
	0x98,
	0xF8,
	0xFC,
	0xFA,
	0xF5,
	0x3C,
	0x3D,
	0xA6,
	0xA7,
	0x99,
	0xFE,
	0xFF,
	0xF6,
	0xF7,
	0xC8,
	0xF4,
	0xE4,
	0xE5,
	0x6C,
	0x6D,
	0xCC,
	0xCD,
	0xCE,
	0xCF,
	0x9F,
	0x0F,
	0xAE,
	0xC5,
	0x8D,
	0xC4,
	0xF0,
	0xAC,
	0xAD,
	0xE1,
	0xE2,
	0x88,
	0x89,
	0x8A,
	0x8B,
	0x8C,
	0x8E,
	0xA0,
	0xA1,
	0xA2,
	0xA3,
	0xA4,
	0xA5,
	0xF6,
	0xF7,
	0x90,
	0x0C,
	0x0D,
	0x80,
	0x81,
	0x83,
	0x08,
	0x09,
	0x0A,
	0x0B,
	0xE6,
	0xE7,
	0x6E,
	0x6F,
	0x8F,
	0x1F,
	0x07,
	0x17,
	0x61,
	0x9D,
	0xFF,
	0x6A,
	0x68,
	0x0E,
	0x16,
	0x60,
	0x9C,
	0xF9,
	0xFD,
	0xFB,
	0xAA,
	0xAB,
	0x2C,
	0x2D,
	0x80,
	0x81,
	0x83,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0xA8,
	0xA9,
	0xF6,
	0xF7,
	0x85,
	0x84,
	0x9B,
	0x90,
	0x86,
	0x87,
	0x34,
	0x35,
	0x81,
	0x83,
	0x30,
	0x31,
	0x32,
	0x33
};
__INLINE__ __byte __INTERNAL_FUNC__ RandOneByteInst() {
	__byte bCode = 0;
	__integer iIndex = 0;
	iIndex = GenerateRandomNumber() % __MAX_ONE_BYTE_INSTRUCTION__;
	bCode = g_OneByteInstruction[iIndex];
	return bCode;
}

#define __MAX_TWO_BYTE_INSTRUCTION__			73
__CONST__ __word g_TwoByteInstruction[__MAX_TWO_BYTE_INSTRUCTION__] = {
	0xD50A,
	0xD40A,
	0x0FBC,
	0x0FBD,
	0x0FC8,
	0x0FA3,
	0x0FBB,
	0x0FAB,
	0x0FAB,
	0x0FBA,
	0x0FAE,
	0x0F06,
	0x0F40,
	0x0F41,
	0x0F42,
	0x0F43,
	0x0F44,
	0x0F45,
	0x0F46,
	0x0F47,
	0x0F48,
	0x0F49,
	0x0F4A,
	0x0F4B,
	0x0F4C,
	0x0F4D,
	0x0F4E,
	0x0F4F,
	0x0FB0,
	0x0FC7,
	0x0FA2,
	0x0F77,
	0x0FAF,
	0x0F08,
	0x0F01,
	0x0FB4,
	0x0FB5,
	0x0F00,
	0x0F01,
	0x0F03,
	0x0F00,
	0x0FAE,
	0x0FBE,
	0x0FB6,
	0x0F1F,
	0xF390,
	0x0FA1,
	0x0FA9,
	0x0F18,
	0x0FA0,
	0x0FA8,
	0x0F32,
	0x0F33,
	0x0F31,
	0xF2A7,
	0xF36C,
	0xF36D,
	0xF3A4,
	0xF3A5,
	0xF36E,
	0xF36F,
	0xF3AC,
	0xF3AD,
	0xF3AA,
	0xF3Ab,
	0x0FAE,
	0xFF00,
	0x0F05,
	0x0F34,
	0x0F35,
	0x0F07,
	0x0F00,
	0x0F02
};
__INLINE__ __word __INTERNAL_FUNC__ RandTwoByteInst() {
	__word wCode = 0;
	__integer iIndex = 0;
	iIndex = GenerateRandomNumber() % __MAX_TWO_BYTE_INSTRUCTION__;
	wCode = g_TwoByteInstruction[iIndex];
	return wCode;
}

__integer __INTERNAL_FUNC__ PowerProtecterGetJmpThunkCode(__memory pOutBuffer, __integer iThunkCodeSize) {
	__integer iSize = 0;
	switch (iThunkCodeSize) {
	case 1:{//JCC
		iSize = 1;
		*(__byte *)pOutBuffer = RandJmpCode();
		   }break;
	case 2:{//JCC OFFSET_8BITS
		iSize = 2;
		*(__byte *)pOutBuffer = RandJmpCode();
		*(__byte *)(pOutBuffer + 1) = (__byte)(GenerateRandomNumber() % 0x20);
		   }break;
	case 3:{//JCC OFFSET_8BITS; OneByteInst
		iSize = 3;
		*(__byte *)pOutBuffer = RandJmpCode();
		*(__byte *)(pOutBuffer + 1) = (__byte)(GenerateRandomNumber() % 0x20);
		*(__byte *)(pOutBuffer + 2) = RandOneByteInst();
		   }break;
	case 4:{//JCC OFFSET_8BITS; TwoByteInst
		iSize = 4;
		*(__byte *)pOutBuffer = RandJmpCode();
		*(__byte *)(pOutBuffer + 1) = (__byte)(GenerateRandomNumber() % 0x20);
		*(__word *)(pOutBuffer + 2) = RandTwoByteInst();
		   }break;
	case 5:{//JCC OFFSET_8BITS; TwoByteInst; JCC
		iSize = 5;
		*(__byte *)pOutBuffer = RandJmpCode();
		*(__byte *)(pOutBuffer + 1) = (__byte)(GenerateRandomNumber() % 0x20);
		*(__word *)(pOutBuffer + 2) = RandTwoByteInst();
		*(__byte *)(pOutBuffer + 4) = RandJmpCode();
		   }break;
	case 6:{//JCC OFFSET_8BITS; TwoByteInst; JCC OFFSET_8BITS
		iSize = 6;
		*(__byte *)pOutBuffer = RandJmpCode();
		*(__byte *)(pOutBuffer + 1) = (__byte)(GenerateRandomNumber() % 0x20);
		*(__word *)(pOutBuffer + 2) = RandTwoByteInst();
		*(__byte *)(pOutBuffer + 4) = RandJmpCode();
		*(__byte *)(pOutBuffer + 5) = (__byte)(GenerateRandomNumber() % 0x20);
		   }break;
	}
	return iSize;
}
