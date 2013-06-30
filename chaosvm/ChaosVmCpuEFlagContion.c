/*
 * 0x70 & 0xF;		0x0F80 & 0xF;	Jcc;		O;           OF=1
 * 0x71 & 0xF;		0x0F81 & 0xF;	Jcc;		NO;          OF=0
 * 0x72 & 0xF;		0x0F82 & 0xF;	Jcc;		B/NAE/C;     CF=1
 * 0x73 & 0xF;		0x0F83 & 0xF;	Jcc;		NB/AE/NC;    CF=0
 * 0x74 & 0xF;		0x0F84 & 0xF;	Jcc;		Z/E;         ZF=1
 * 0x75 & 0xF;		0x0F85 & 0xF;	Jcc;		NZ/NE;       ZF=0
 * 0x76 & 0xF;		0x0F86 & 0xF;	Jcc;		BE/NA;       CF=1 or  ZF=1
 * 0x77 & 0xF;		0x0F87 & 0xF;	Jcc;		NBE/A;       CF=0 and ZF=0
 * 0x78 & 0xF;		0x0F88 & 0xF;	Jcc;		S;           SF=1
 * 0x79 & 0xF;		0x0F89 & 0xF;	Jcc;		NS;          SF=0
 * 0x7A & 0xF;		0x0F8A & 0xF;	Jcc;		P/PE;        PF=1
 * 0x7B & 0xF;		0x0F8B & 0xF;	Jcc;		NP/PO;       PF=0
 * 0x7C & 0xF;		0x0F8C & 0xF;	Jcc;		L/NGE;       SF != OF
 * 0x7D & 0xF;		0x0F8D & 0xF;	Jcc;		NL/GE;       SF =  OF
 * 0x7E & 0xF;		0x0F8E & 0xF;	Jcc;		LE/NG;       ZF=1 or  SF != OF
 * 0x7F & 0xF;		0x0F8F & 0xF;	Jcc;		NLE/G;       ZF=0 and SF =  OF
 */

/*
 * struct
 * {
 * __byte FlagA;
 * __byte FlagB;
 * __byte FlagC;
 * __byte FlagD;
 * __byte XorCode;
 * };
 * (FlagA==0 && FlagB==0 && (FlagC == FlagD)) ^ XorCode
 */


__byte __INTERNAL_FUNC__ Test_00(PCHAOSVM_CPU pCPU) {
	/* O */
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bOF == __EFLAG_SET__) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_01(PCHAOSVM_CPU pCPU) {
	/* NO */
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bOF == __EFLAG_SET__) ? 0 : 1);
}

__byte __INTERNAL_FUNC__ Test_02(PCHAOSVM_CPU pCPU) {
	/* C */
	__byte bCF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF);
	return ((bCF == __EFLAG_SET__) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_03(PCHAOSVM_CPU pCPU) {
	/* NC */
	__byte bCF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF);
	return ((bCF == __EFLAG_SET__) ? 0 : 1);
}

__byte __INTERNAL_FUNC__ Test_04(PCHAOSVM_CPU pCPU) {
	/* Z */
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	return ((bZF == __EFLAG_SET__) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_05(PCHAOSVM_CPU pCPU) {
	/* NZ */
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	return ((bZF == __EFLAG_SET__) ? 0 : 1);
}

__byte __INTERNAL_FUNC__ Test_06(PCHAOSVM_CPU pCPU) {
	/* BE/NA */
	__byte bCF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF);
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	return (((bCF == __EFLAG_SET__) || (bZF == __EFLAG_SET__)) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_07(PCHAOSVM_CPU pCPU) {
	/* NBE/A */
	__byte bCF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_CF);
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	return (((bCF == __EFLAG_RESET__) && (bZF == __EFLAG_RESET__)) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_08(PCHAOSVM_CPU pCPU) {
	/* S */
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	return (bSF ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_09(PCHAOSVM_CPU pCPU) {
	/* NS */
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	return (bSF ? 0 : 1);
}

__byte __INTERNAL_FUNC__ Test_0A(PCHAOSVM_CPU pCPU) {
	/* P */
	__byte bPF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_PF);
	return (bPF ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_0B(PCHAOSVM_CPU pCPU) {
	/* NP */
	__byte bPF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_PF);
	return (bPF ? 0 : 1);
}

__byte __INTERNAL_FUNC__ Test_0C(PCHAOSVM_CPU pCPU) {
	/* L/NGE */
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bSF != bOF) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_0D(PCHAOSVM_CPU pCPU) {
	/*NL/GE */
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bSF == bOF) ? 1 : 0);
}

__byte __INTERNAL_FUNC__ Test_0E(PCHAOSVM_CPU pCPU) {
	/* LE/NG */
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bZF == __EFLAG_SET__) || ((bSF != bOF) ? 1 : 0));
}

__byte __INTERNAL_FUNC__ Test_0F(PCHAOSVM_CPU pCPU) {
	/*NL/GE */
	__byte bZF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_ZF);
	__byte bSF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF);
	__byte bOF = __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_OF);
	return ((bZF == __EFLAG_RESET__) && ((bSF == bOF) ? 1 : 0));
}
