
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"

/*
 * CMPSDx MOVQx MOVSDx 是为了避免x86指令符号冲突而为SIMD指令
 * 专门设定
 * 这里处理地址标号的算法如下:
 * 如果是定义标号,则加入符号表,并且预留下标号的偏移信息
 * 如果是以内存地址偏移引用地址标号,则预留下标号的偏移信息
 * 如果是以立即数的形式引用地址标号,如跳转指令,则预留下标号的偏移信息
 * 标号的偏移信息为ASMER_OPERAND类型的ofRelocationFixOffset字段
 * 填充ofRelocationFixOffset字段在AssemblerEncoder.c中的Encoder中实现
 *
 * CALL
 * JMP
 * MOV 不对A0 - A3操作码进行编码
 *
 * 编码顺序:Mod Ro Rm
 */
#include "AssemblerParse.h"

#define pCurrAsmObj (*g_pCurrAsmObjPoint)
__byte g_iCurrOperand = 0;

/*
 * 创建一个汇编对象
 */
__void __INTERNAL_FUNC__ CreateNewAsmObj() {
    pCurrAsmObj = (PASM_OBJ)__logic_new__(ASM_OBJ, 1);
	__logic_memset__(pCurrAsmObj, 0, sizeof(ASM_OBJ));
}

/*
 * 设置66前缀
 */
__void __INTERNAL_FUNC__ SetPrefix66() {
    pCurrAsmObj->bUsePrefix = TRUE;
	pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0x66;
	(pCurrAsmObj->bPrefixCount)++;
}



/* Line 189 of yacc.c  */
#line 115 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LOCK = 258,
     REP = 259,
     REPE = 260,
     REPZ = 261,
     REPNE = 262,
     REPNZ = 263,
     AAA = 264,
     AAD = 265,
     AAM = 266,
     AAS = 267,
     ADC = 268,
     ADD = 269,
     ADDPD = 270,
     ADDPS = 271,
     ADDSD = 272,
     ADDSS = 273,
     ADDSUBPD = 274,
     ADDSUBPS = 275,
     AESDEC = 276,
     AESDECLAST = 277,
     AESENC = 278,
     AESENCLAST = 279,
     AESIMC = 280,
     AESKEYGENASSIST = 281,
     AND = 282,
     ANDPD = 283,
     ANDPS = 284,
     ANDNPD = 285,
     ANDNPS = 286,
     ARPL = 287,
     BLENDPD = 288,
     BLENDPS = 289,
     BLENDVPD = 290,
     BLENDVPS = 291,
     BOUND = 292,
     BSF = 293,
     BSR = 294,
     BSWAP = 295,
     BT = 296,
     BTC = 297,
     BTR = 298,
     BTS = 299,
     CALL = 300,
     CBW = 301,
     CWDE = 302,
     CDQE = 303,
     CLC = 304,
     CLD = 305,
     CLFLUSH = 306,
     CLI = 307,
     CLTS = 308,
     CMC = 309,
     CMOVA = 310,
     CMOVAE = 311,
     CMOVB = 312,
     CMOVBE = 313,
     CMOVC = 314,
     CMOVE = 315,
     CMOVG = 316,
     CMOVGE = 317,
     CMOVL = 318,
     CMOVLE = 319,
     CMOVNA = 320,
     CMOVNAE = 321,
     CMOVNB = 322,
     CMOVNBE = 323,
     CMOVNC = 324,
     CMOVNE = 325,
     CMOVNG = 326,
     CMOVNGE = 327,
     CMOVNL = 328,
     CMOVNLE = 329,
     CMOVNO = 330,
     CMOVNP = 331,
     CMOVNS = 332,
     CMOVNZ = 333,
     CMOVO = 334,
     CMOVP = 335,
     CMOVPE = 336,
     CMOVPO = 337,
     CMOVS = 338,
     CMOVZ = 339,
     CMP = 340,
     CMPPD = 341,
     CMPPS = 342,
     CMPSB = 343,
     CMPSW = 344,
     CMPSD = 345,
     CMPSQ = 346,
     CMPSDx = 347,
     CMPSS = 348,
     CMPXCHG = 349,
     CMPXCHG8B = 350,
     COMISD = 351,
     COMISS = 352,
     CPUID = 353,
     CRC32 = 354,
     CVTDQ2PD = 355,
     CVTDQ2PS = 356,
     CVTPD2DQ = 357,
     CVTPD2PI = 358,
     CVTPD2PS = 359,
     CVTPI2PD = 360,
     CVTPI2PS = 361,
     CVTPS2DQ = 362,
     CVTPS2PD = 363,
     CVTPS2PI = 364,
     CVTSD2SI = 365,
     CVTSD2SS = 366,
     CVTSI2SD = 367,
     CVTSI2SS = 368,
     CVTSS2SD = 369,
     CVTSS2SI = 370,
     CVTTPD2DQ = 371,
     CVTTPD2PI = 372,
     CVTTPS2DQ = 373,
     CVTTPS2PI = 374,
     CVTTSD2SI = 375,
     CVTTSS2SI = 376,
     CWD = 377,
     CDQ = 378,
     CQO = 379,
     DAA = 380,
     DAS = 381,
     DEC = 382,
     DIV = 383,
     DIVPD = 384,
     DIVPS = 385,
     DIVSD = 386,
     DIVSS = 387,
     DPPD = 388,
     DPPS = 389,
     EMMS = 390,
     ENTER = 391,
     EXTRACTPS = 392,
     F2XM1 = 393,
     FABS = 394,
     FADD = 395,
     FADDP = 396,
     FIADD = 397,
     FBLD = 398,
     FBSTP = 399,
     FCHS = 400,
     FCLEX = 401,
     FNCLEX = 402,
     FCMOVB = 403,
     FCMOVE = 404,
     FCMOVBE = 405,
     FCMOVU = 406,
     FCMOVNB = 407,
     FCMOVNE = 408,
     FCMOVNBE = 409,
     FCMOVNU = 410,
     FCOMI = 411,
     FCOMIP = 412,
     FCOS = 413,
     FDECSTP = 414,
     FDIV = 415,
     FDIVP = 416,
     FIDIV = 417,
     FDIVR = 418,
     FDIVRP = 419,
     FIDIVR = 420,
     FFREE = 421,
     FICOM = 422,
     FICOMP = 423,
     FILD = 424,
     FINCSTP = 425,
     FINIT = 426,
     FNINIT = 427,
     FIST = 428,
     FISTP = 429,
     FISTTP = 430,
     FLD = 431,
     FLD1 = 432,
     FLDL2T = 433,
     FLDL2E = 434,
     FLDPI = 435,
     FLDLG2 = 436,
     FLDLN2 = 437,
     FLDZ = 438,
     FLDCW = 439,
     FLDENV = 440,
     FMUL = 441,
     FMULP = 442,
     FIMUL = 443,
     FNOP = 444,
     FPATAN = 445,
     FPREM = 446,
     FPREM1 = 447,
     FPTAN = 448,
     FRNDINT = 449,
     FRSTOR = 450,
     FSAVE = 451,
     FNSAVE = 452,
     FSCALE = 453,
     FSIN = 454,
     FSINCOS = 455,
     FSQRT = 456,
     FST = 457,
     FSTP = 458,
     FSTCW = 459,
     FNSTCW = 460,
     FSTENV = 461,
     FNSTENV = 462,
     FSTSW = 463,
     FNSTSW = 464,
     FSUB = 465,
     FSUBP = 466,
     FISUB = 467,
     FSUBR = 468,
     FSUBRP = 469,
     FISUBR = 470,
     FTST = 471,
     FUCOM = 472,
     FUCOMP = 473,
     FUCOMPP = 474,
     FXAM = 475,
     FXCH = 476,
     FXRSTOR = 477,
     FXSAVE = 478,
     FXTRACT = 479,
     FYL2X = 480,
     FYL2XP1 = 481,
     HADDPD = 482,
     HADDPS = 483,
     HLT = 484,
     HSUBPD = 485,
     HSUBPS = 486,
     IDIV = 487,
     IMUL = 488,
     IN = 489,
     INC = 490,
     INS = 491,
     INSB = 492,
     INSW = 493,
     INSD = 494,
     INSERTPS = 495,
     INT = 496,
     INT3 = 497,
     INTO = 498,
     INVD = 499,
     INVLPG = 500,
     IRET = 501,
     IRETD = 502,
     JA = 503,
     JAE = 504,
     JB = 505,
     JBE = 506,
     JC = 507,
     JCXZ = 508,
     JECXZ = 509,
     JRCXZ = 510,
     JE = 511,
     JG = 512,
     JGE = 513,
     JL = 514,
     JLE = 515,
     JNA = 516,
     JNAE = 517,
     JNB = 518,
     JNBE = 519,
     JNC = 520,
     JNE = 521,
     JNG = 522,
     JNGE = 523,
     JNL = 524,
     JNLE = 525,
     JNO = 526,
     JNP = 527,
     JNS = 528,
     JNZ = 529,
     JO = 530,
     JP = 531,
     JPE = 532,
     JPO = 533,
     JS = 534,
     JZ = 535,
     JMP = 536,
     LAHF = 537,
     LAR = 538,
     LDDQU = 539,
     LDMXCSR = 540,
     LDS = 541,
     LES = 542,
     LFS = 543,
     LGS = 544,
     LSS = 545,
     LEA = 546,
     LEAVE = 547,
     LFENCE = 548,
     LGDT = 549,
     LIDT = 550,
     LLDT = 551,
     LMSW = 552,
     LODSB = 553,
     LODSW = 554,
     LODSD = 555,
     LODSQ = 556,
     LOOP = 557,
     LOOPE = 558,
     LOOPNE = 559,
     LSL = 560,
     LTR = 561,
     MASKMOVDQU = 562,
     MASKMOVQ = 563,
     MAXPD = 564,
     MAXPS = 565,
     MAXSD = 566,
     MAXSS = 567,
     MFENCE = 568,
     MINPD = 569,
     MINPS = 570,
     MINSD = 571,
     MINSS = 572,
     MONITOR = 573,
     MOV = 574,
     MOVAPD = 575,
     MOVAPS = 576,
     MOVBE = 577,
     MOVD = 578,
     MOVQ = 579,
     MOVDDUP = 580,
     MOVDQA = 581,
     MOVDQU = 582,
     MOVDQ2Q = 583,
     MOVHLPS = 584,
     MOVHPD = 585,
     MOVHPS = 586,
     MOVLHPS = 587,
     MOVLPD = 588,
     MOVLPS = 589,
     MOVMSKPD = 590,
     MOVMSKPS = 591,
     MOVNTDQA = 592,
     MOVNTDQ = 593,
     MOVNTI = 594,
     MOVNTPD = 595,
     MOVNTPS = 596,
     MOVNTQ = 597,
     MOVQx = 598,
     MOVQ2DQ = 599,
     MOVSB = 600,
     MOVSW = 601,
     MOVSD = 602,
     MOVSQ = 603,
     MOVSDx = 604,
     MOVSHDUP = 605,
     MOVSLDUP = 606,
     MOVSS = 607,
     MOVSX = 608,
     MOVSXD = 609,
     MOVUPD = 610,
     MOVUPS = 611,
     MOVZX = 612,
     MPSADBW = 613,
     MUL = 614,
     MULPD = 615,
     MULPS = 616,
     MULSD = 617,
     MULSS = 618,
     MWAIT = 619,
     NEG = 620,
     NOP = 621,
     NOT = 622,
     OR = 623,
     ORPD = 624,
     ORPS = 625,
     OUT = 626,
     OUTS = 627,
     OUTSB = 628,
     OUTSW = 629,
     OUTSD = 630,
     PABSB = 631,
     PABSW = 632,
     PABSD = 633,
     PACKSSWB = 634,
     PACKSSDW = 635,
     PACKUSDW = 636,
     PACKUSWB = 637,
     PADDB = 638,
     PADDW = 639,
     PADDD = 640,
     PADDQ = 641,
     PADDSB = 642,
     PADDSW = 643,
     PADDUSB = 644,
     PADDUSW = 645,
     PALIGNR = 646,
     PAND = 647,
     PANDN = 648,
     PAUSE = 649,
     PAVGB = 650,
     PAVGW = 651,
     PBLENDVB = 652,
     PBLENDW = 653,
     PCLMULQDQ = 654,
     PCMPEQB = 655,
     PCMPEQW = 656,
     PCMPEQD = 657,
     PCMPEQQ = 658,
     PCMPESTRI = 659,
     PCMPESTRM = 660,
     PCMPGTB = 661,
     PCMPGTW = 662,
     PCMPGTD = 663,
     PCMPGTQ = 664,
     PCMPISTRI = 665,
     PCMPISTRM = 666,
     PEXTRB = 667,
     PEXTRD = 668,
     PEXTRQ = 669,
     PEXTRW = 670,
     PHADDW = 671,
     PHADDD = 672,
     PHADDSW = 673,
     PHMINPOSUW = 674,
     PHSUBW = 675,
     PHSUBD = 676,
     PHSUBSW = 677,
     PINSRB = 678,
     PINSRD = 679,
     PINSRQ = 680,
     PINSRW = 681,
     PMADDUBSW = 682,
     PMADDWD = 683,
     PMAXSB = 684,
     PMAXSD = 685,
     PMAXSW = 686,
     PMAXUB = 687,
     PMAXUD = 688,
     PMAXUW = 689,
     PMINSB = 690,
     PMINSD = 691,
     PMINSW = 692,
     PMINUB = 693,
     PMINUD = 694,
     PMINUW = 695,
     PMOVMSKB = 696,
     PMOVSX = 697,
     PMOVZX = 698,
     PMULDQ = 699,
     PMULHRSW = 700,
     PMULHUW = 701,
     PMULHW = 702,
     PMULLD = 703,
     PMULLW = 704,
     PMULUDQ = 705,
     POP = 706,
     POPA = 707,
     POPAD = 708,
     POPCNT = 709,
     POPF = 710,
     POPFD = 711,
     POPFQ = 712,
     POR = 713,
     PREFETCHT0 = 714,
     PREFETCHT1 = 715,
     PREFETCHT2 = 716,
     PREFETCHNTA = 717,
     PSADBW = 718,
     PSHUFB = 719,
     PSHUFD = 720,
     PSHUFHW = 721,
     PSHUFLW = 722,
     PSHUFW = 723,
     PSIGNB = 724,
     PSIGNW = 725,
     PSIGND = 726,
     PSLLDQ = 727,
     PSLLW = 728,
     PSLLD = 729,
     PSLLQ = 730,
     PSRAW = 731,
     PSRAD = 732,
     PSRLDQ = 733,
     PSRLW = 734,
     PSRLD = 735,
     PSRLQ = 736,
     PSUBB = 737,
     PSUBW = 738,
     PSUBD = 739,
     PSUBQ = 740,
     PSUBSB = 741,
     PSUBSW = 742,
     PSUBUSB = 743,
     PSUBUSW = 744,
     PTEST = 745,
     PUNPCKHBW = 746,
     PUNPCKHWD = 747,
     PUNPCKHDQ = 748,
     PUNPCKHQDQ = 749,
     PUNPCKLBW = 750,
     PUNPCKLWD = 751,
     PUNPCKLDQ = 752,
     PUNPCKLQDQ = 753,
     PUSH = 754,
     PUSHA = 755,
     PUSHAD = 756,
     PUSHF = 757,
     PUSHFD = 758,
     PXOR = 759,
     RCL = 760,
     RCR = 761,
     ROL = 762,
     ROR = 763,
     RCPPS = 764,
     RCPSS = 765,
     RDMSR = 766,
     RDPMC = 767,
     RDTSC = 768,
     RDTSCP = 769,
     RET = 770,
     RETN = 771,
     ROUNDPD = 772,
     ROUNDPS = 773,
     ROUNDSD = 774,
     ROUNDSS = 775,
     RSM = 776,
     RSQRTPS = 777,
     RSQRTSS = 778,
     SAHF = 779,
     SAL = 780,
     SAR = 781,
     SHL = 782,
     SHR = 783,
     SBB = 784,
     SCASB = 785,
     SCASW = 786,
     SCASD = 787,
     SETA = 788,
     SETAE = 789,
     SETB = 790,
     SETBE = 791,
     SETC = 792,
     SETE = 793,
     SETG = 794,
     SETGE = 795,
     SETL = 796,
     SETLE = 797,
     SETNA = 798,
     SETNAE = 799,
     SETNB = 800,
     SETNBE = 801,
     SETNC = 802,
     SETNE = 803,
     SETNG = 804,
     SETNGE = 805,
     SETNL = 806,
     SETNLE = 807,
     SETNO = 808,
     SETNP = 809,
     SETNS = 810,
     SETNZ = 811,
     SETO = 812,
     SETP = 813,
     SETPE = 814,
     SETPO = 815,
     SETS = 816,
     SETZ = 817,
     SFENCE = 818,
     SGDT = 819,
     SHLD = 820,
     SHRD = 821,
     SHUFPD = 822,
     SHUFPS = 823,
     SIDT = 824,
     SLDT = 825,
     SMSW = 826,
     SQRTPS = 827,
     SQRTSD = 828,
     SQRTSS = 829,
     STC = 830,
     STD = 831,
     STI = 832,
     STMXCSR = 833,
     STOSB = 834,
     STOSW = 835,
     STOSD = 836,
     STOSQ = 837,
     STR = 838,
     SUB = 839,
     SUBPD = 840,
     SUBPS = 841,
     SUBSD = 842,
     SUBSS = 843,
     SWAPGS = 844,
     SYSCALL = 845,
     SYSENTER = 846,
     SYSEXIT = 847,
     SYSRET = 848,
     TEST = 849,
     UCOMISD = 850,
     UCOMISS = 851,
     UD2 = 852,
     UNPCKHPD = 853,
     UNPCKHPS = 854,
     UNPCKLPD = 855,
     UNPCKLPS = 856,
     VERR = 857,
     VERW = 858,
     WAIT = 859,
     FWAIT = 860,
     WBINVD = 861,
     WRMSR = 862,
     XADD = 863,
     XCHG = 864,
     XGETBV = 865,
     XLAT = 866,
     XLATB = 867,
     XOR = 868,
     XORPD = 869,
     XORPS = 870,
     XRSTOR = 871,
     XSAVE = 872,
     XSETBV = 873,
     INVEPT = 874,
     INVVPID = 875,
     VMCALL = 876,
     VMCLEAR = 877,
     VMLAUNCH = 878,
     VMPTRLD = 879,
     VMPTRST = 880,
     VMREAD = 881,
     VMRESUME = 882,
     VMWRITE = 883,
     VMXOFF = 884,
     VMXON = 885,
     R_AL = 886,
     R_CL = 887,
     R_DL = 888,
     R_BL = 889,
     R_AH = 890,
     R_CH = 891,
     R_DH = 892,
     R_BH = 893,
     R_AX = 894,
     R_CX = 895,
     R_DX = 896,
     R_BX = 897,
     R_SP = 898,
     R_BP = 899,
     R_SI = 900,
     R_DI = 901,
     R_EAX = 902,
     R_ECX = 903,
     R_EDX = 904,
     R_EBX = 905,
     R_ESP = 906,
     R_EBP = 907,
     R_ESI = 908,
     R_EDI = 909,
     R_CR0 = 910,
     R_CR1 = 911,
     R_CR2 = 912,
     R_CR3 = 913,
     R_CR4 = 914,
     R_CR5 = 915,
     R_CR6 = 916,
     R_CR7 = 917,
     R_DR0 = 918,
     R_DR1 = 919,
     R_DR2 = 920,
     R_DR3 = 921,
     R_DR4 = 922,
     R_DR5 = 923,
     R_DR6 = 924,
     R_DR7 = 925,
     R_MM0 = 926,
     R_MM1 = 927,
     R_MM2 = 928,
     R_MM3 = 929,
     R_MM4 = 930,
     R_MM5 = 931,
     R_MM6 = 932,
     R_MM7 = 933,
     R_ST0 = 934,
     R_ST1 = 935,
     R_ST2 = 936,
     R_ST3 = 937,
     R_ST4 = 938,
     R_ST5 = 939,
     R_ST6 = 940,
     R_ST7 = 941,
     R_XMM0 = 942,
     R_XMM1 = 943,
     R_XMM2 = 944,
     R_XMM3 = 945,
     R_XMM4 = 946,
     R_XMM5 = 947,
     R_XMM6 = 948,
     R_XMM7 = 949,
     SEG_ES = 950,
     SEG_CS = 951,
     SEG_SS = 952,
     SEG_DS = 953,
     SEG_FS = 954,
     SEG_GS = 955,
     OP_REG = 956,
     OP_MEM = 957,
     OP_IMM = 958,
     BYTE_PTR = 959,
     WORD_PTR = 960,
     DWORD_PTR = 961,
     QWORD_PTR = 962,
     TWORD_PTR = 963,
     SCALE_1 = 964,
     SCALE_2 = 965,
     SCALE_4 = 966,
     SCALE_8 = 967,
     PLUSSIGN = 968,
     SUBSIGN = 969,
     ADDR_LAB = 970,
     DISPLACEMENT8 = 971,
     DISPLACEMENT32 = 972,
     IMMEDIATE8 = 973,
     IMMEDIATE16 = 974,
     IMMEDIATE32 = 975,
     LINESTART = 976,
     COLON = 977,
     COMMA = 978,
     MEMEND = 979,
     LINEND = 980,
     ERROR = 981,
     END = 982,
     NONE = 983
   };
#endif
/* Tokens.  */
#define LOCK 258
#define REP 259
#define REPE 260
#define REPZ 261
#define REPNE 262
#define REPNZ 263
#define AAA 264
#define AAD 265
#define AAM 266
#define AAS 267
#define ADC 268
#define ADD 269
#define ADDPD 270
#define ADDPS 271
#define ADDSD 272
#define ADDSS 273
#define ADDSUBPD 274
#define ADDSUBPS 275
#define AESDEC 276
#define AESDECLAST 277
#define AESENC 278
#define AESENCLAST 279
#define AESIMC 280
#define AESKEYGENASSIST 281
#define AND 282
#define ANDPD 283
#define ANDPS 284
#define ANDNPD 285
#define ANDNPS 286
#define ARPL 287
#define BLENDPD 288
#define BLENDPS 289
#define BLENDVPD 290
#define BLENDVPS 291
#define BOUND 292
#define BSF 293
#define BSR 294
#define BSWAP 295
#define BT 296
#define BTC 297
#define BTR 298
#define BTS 299
#define CALL 300
#define CBW 301
#define CWDE 302
#define CDQE 303
#define CLC 304
#define CLD 305
#define CLFLUSH 306
#define CLI 307
#define CLTS 308
#define CMC 309
#define CMOVA 310
#define CMOVAE 311
#define CMOVB 312
#define CMOVBE 313
#define CMOVC 314
#define CMOVE 315
#define CMOVG 316
#define CMOVGE 317
#define CMOVL 318
#define CMOVLE 319
#define CMOVNA 320
#define CMOVNAE 321
#define CMOVNB 322
#define CMOVNBE 323
#define CMOVNC 324
#define CMOVNE 325
#define CMOVNG 326
#define CMOVNGE 327
#define CMOVNL 328
#define CMOVNLE 329
#define CMOVNO 330
#define CMOVNP 331
#define CMOVNS 332
#define CMOVNZ 333
#define CMOVO 334
#define CMOVP 335
#define CMOVPE 336
#define CMOVPO 337
#define CMOVS 338
#define CMOVZ 339
#define CMP 340
#define CMPPD 341
#define CMPPS 342
#define CMPSB 343
#define CMPSW 344
#define CMPSD 345
#define CMPSQ 346
#define CMPSDx 347
#define CMPSS 348
#define CMPXCHG 349
#define CMPXCHG8B 350
#define COMISD 351
#define COMISS 352
#define CPUID 353
#define CRC32 354
#define CVTDQ2PD 355
#define CVTDQ2PS 356
#define CVTPD2DQ 357
#define CVTPD2PI 358
#define CVTPD2PS 359
#define CVTPI2PD 360
#define CVTPI2PS 361
#define CVTPS2DQ 362
#define CVTPS2PD 363
#define CVTPS2PI 364
#define CVTSD2SI 365
#define CVTSD2SS 366
#define CVTSI2SD 367
#define CVTSI2SS 368
#define CVTSS2SD 369
#define CVTSS2SI 370
#define CVTTPD2DQ 371
#define CVTTPD2PI 372
#define CVTTPS2DQ 373
#define CVTTPS2PI 374
#define CVTTSD2SI 375
#define CVTTSS2SI 376
#define CWD 377
#define CDQ 378
#define CQO 379
#define DAA 380
#define DAS 381
#define DEC 382
#define DIV 383
#define DIVPD 384
#define DIVPS 385
#define DIVSD 386
#define DIVSS 387
#define DPPD 388
#define DPPS 389
#define EMMS 390
#define ENTER 391
#define EXTRACTPS 392
#define F2XM1 393
#define FABS 394
#define FADD 395
#define FADDP 396
#define FIADD 397
#define FBLD 398
#define FBSTP 399
#define FCHS 400
#define FCLEX 401
#define FNCLEX 402
#define FCMOVB 403
#define FCMOVE 404
#define FCMOVBE 405
#define FCMOVU 406
#define FCMOVNB 407
#define FCMOVNE 408
#define FCMOVNBE 409
#define FCMOVNU 410
#define FCOMI 411
#define FCOMIP 412
#define FCOS 413
#define FDECSTP 414
#define FDIV 415
#define FDIVP 416
#define FIDIV 417
#define FDIVR 418
#define FDIVRP 419
#define FIDIVR 420
#define FFREE 421
#define FICOM 422
#define FICOMP 423
#define FILD 424
#define FINCSTP 425
#define FINIT 426
#define FNINIT 427
#define FIST 428
#define FISTP 429
#define FISTTP 430
#define FLD 431
#define FLD1 432
#define FLDL2T 433
#define FLDL2E 434
#define FLDPI 435
#define FLDLG2 436
#define FLDLN2 437
#define FLDZ 438
#define FLDCW 439
#define FLDENV 440
#define FMUL 441
#define FMULP 442
#define FIMUL 443
#define FNOP 444
#define FPATAN 445
#define FPREM 446
#define FPREM1 447
#define FPTAN 448
#define FRNDINT 449
#define FRSTOR 450
#define FSAVE 451
#define FNSAVE 452
#define FSCALE 453
#define FSIN 454
#define FSINCOS 455
#define FSQRT 456
#define FST 457
#define FSTP 458
#define FSTCW 459
#define FNSTCW 460
#define FSTENV 461
#define FNSTENV 462
#define FSTSW 463
#define FNSTSW 464
#define FSUB 465
#define FSUBP 466
#define FISUB 467
#define FSUBR 468
#define FSUBRP 469
#define FISUBR 470
#define FTST 471
#define FUCOM 472
#define FUCOMP 473
#define FUCOMPP 474
#define FXAM 475
#define FXCH 476
#define FXRSTOR 477
#define FXSAVE 478
#define FXTRACT 479
#define FYL2X 480
#define FYL2XP1 481
#define HADDPD 482
#define HADDPS 483
#define HLT 484
#define HSUBPD 485
#define HSUBPS 486
#define IDIV 487
#define IMUL 488
#define IN 489
#define INC 490
#define INS 491
#define INSB 492
#define INSW 493
#define INSD 494
#define INSERTPS 495
#define INT 496
#define INT3 497
#define INTO 498
#define INVD 499
#define INVLPG 500
#define IRET 501
#define IRETD 502
#define JA 503
#define JAE 504
#define JB 505
#define JBE 506
#define JC 507
#define JCXZ 508
#define JECXZ 509
#define JRCXZ 510
#define JE 511
#define JG 512
#define JGE 513
#define JL 514
#define JLE 515
#define JNA 516
#define JNAE 517
#define JNB 518
#define JNBE 519
#define JNC 520
#define JNE 521
#define JNG 522
#define JNGE 523
#define JNL 524
#define JNLE 525
#define JNO 526
#define JNP 527
#define JNS 528
#define JNZ 529
#define JO 530
#define JP 531
#define JPE 532
#define JPO 533
#define JS 534
#define JZ 535
#define JMP 536
#define LAHF 537
#define LAR 538
#define LDDQU 539
#define LDMXCSR 540
#define LDS 541
#define LES 542
#define LFS 543
#define LGS 544
#define LSS 545
#define LEA 546
#define LEAVE 547
#define LFENCE 548
#define LGDT 549
#define LIDT 550
#define LLDT 551
#define LMSW 552
#define LODSB 553
#define LODSW 554
#define LODSD 555
#define LODSQ 556
#define LOOP 557
#define LOOPE 558
#define LOOPNE 559
#define LSL 560
#define LTR 561
#define MASKMOVDQU 562
#define MASKMOVQ 563
#define MAXPD 564
#define MAXPS 565
#define MAXSD 566
#define MAXSS 567
#define MFENCE 568
#define MINPD 569
#define MINPS 570
#define MINSD 571
#define MINSS 572
#define MONITOR 573
#define MOV 574
#define MOVAPD 575
#define MOVAPS 576
#define MOVBE 577
#define MOVD 578
#define MOVQ 579
#define MOVDDUP 580
#define MOVDQA 581
#define MOVDQU 582
#define MOVDQ2Q 583
#define MOVHLPS 584
#define MOVHPD 585
#define MOVHPS 586
#define MOVLHPS 587
#define MOVLPD 588
#define MOVLPS 589
#define MOVMSKPD 590
#define MOVMSKPS 591
#define MOVNTDQA 592
#define MOVNTDQ 593
#define MOVNTI 594
#define MOVNTPD 595
#define MOVNTPS 596
#define MOVNTQ 597
#define MOVQx 598
#define MOVQ2DQ 599
#define MOVSB 600
#define MOVSW 601
#define MOVSD 602
#define MOVSQ 603
#define MOVSDx 604
#define MOVSHDUP 605
#define MOVSLDUP 606
#define MOVSS 607
#define MOVSX 608
#define MOVSXD 609
#define MOVUPD 610
#define MOVUPS 611
#define MOVZX 612
#define MPSADBW 613
#define MUL 614
#define MULPD 615
#define MULPS 616
#define MULSD 617
#define MULSS 618
#define MWAIT 619
#define NEG 620
#define NOP 621
#define NOT 622
#define OR 623
#define ORPD 624
#define ORPS 625
#define OUT 626
#define OUTS 627
#define OUTSB 628
#define OUTSW 629
#define OUTSD 630
#define PABSB 631
#define PABSW 632
#define PABSD 633
#define PACKSSWB 634
#define PACKSSDW 635
#define PACKUSDW 636
#define PACKUSWB 637
#define PADDB 638
#define PADDW 639
#define PADDD 640
#define PADDQ 641
#define PADDSB 642
#define PADDSW 643
#define PADDUSB 644
#define PADDUSW 645
#define PALIGNR 646
#define PAND 647
#define PANDN 648
#define PAUSE 649
#define PAVGB 650
#define PAVGW 651
#define PBLENDVB 652
#define PBLENDW 653
#define PCLMULQDQ 654
#define PCMPEQB 655
#define PCMPEQW 656
#define PCMPEQD 657
#define PCMPEQQ 658
#define PCMPESTRI 659
#define PCMPESTRM 660
#define PCMPGTB 661
#define PCMPGTW 662
#define PCMPGTD 663
#define PCMPGTQ 664
#define PCMPISTRI 665
#define PCMPISTRM 666
#define PEXTRB 667
#define PEXTRD 668
#define PEXTRQ 669
#define PEXTRW 670
#define PHADDW 671
#define PHADDD 672
#define PHADDSW 673
#define PHMINPOSUW 674
#define PHSUBW 675
#define PHSUBD 676
#define PHSUBSW 677
#define PINSRB 678
#define PINSRD 679
#define PINSRQ 680
#define PINSRW 681
#define PMADDUBSW 682
#define PMADDWD 683
#define PMAXSB 684
#define PMAXSD 685
#define PMAXSW 686
#define PMAXUB 687
#define PMAXUD 688
#define PMAXUW 689
#define PMINSB 690
#define PMINSD 691
#define PMINSW 692
#define PMINUB 693
#define PMINUD 694
#define PMINUW 695
#define PMOVMSKB 696
#define PMOVSX 697
#define PMOVZX 698
#define PMULDQ 699
#define PMULHRSW 700
#define PMULHUW 701
#define PMULHW 702
#define PMULLD 703
#define PMULLW 704
#define PMULUDQ 705
#define POP 706
#define POPA 707
#define POPAD 708
#define POPCNT 709
#define POPF 710
#define POPFD 711
#define POPFQ 712
#define POR 713
#define PREFETCHT0 714
#define PREFETCHT1 715
#define PREFETCHT2 716
#define PREFETCHNTA 717
#define PSADBW 718
#define PSHUFB 719
#define PSHUFD 720
#define PSHUFHW 721
#define PSHUFLW 722
#define PSHUFW 723
#define PSIGNB 724
#define PSIGNW 725
#define PSIGND 726
#define PSLLDQ 727
#define PSLLW 728
#define PSLLD 729
#define PSLLQ 730
#define PSRAW 731
#define PSRAD 732
#define PSRLDQ 733
#define PSRLW 734
#define PSRLD 735
#define PSRLQ 736
#define PSUBB 737
#define PSUBW 738
#define PSUBD 739
#define PSUBQ 740
#define PSUBSB 741
#define PSUBSW 742
#define PSUBUSB 743
#define PSUBUSW 744
#define PTEST 745
#define PUNPCKHBW 746
#define PUNPCKHWD 747
#define PUNPCKHDQ 748
#define PUNPCKHQDQ 749
#define PUNPCKLBW 750
#define PUNPCKLWD 751
#define PUNPCKLDQ 752
#define PUNPCKLQDQ 753
#define PUSH 754
#define PUSHA 755
#define PUSHAD 756
#define PUSHF 757
#define PUSHFD 758
#define PXOR 759
#define RCL 760
#define RCR 761
#define ROL 762
#define ROR 763
#define RCPPS 764
#define RCPSS 765
#define RDMSR 766
#define RDPMC 767
#define RDTSC 768
#define RDTSCP 769
#define RET 770
#define RETN 771
#define ROUNDPD 772
#define ROUNDPS 773
#define ROUNDSD 774
#define ROUNDSS 775
#define RSM 776
#define RSQRTPS 777
#define RSQRTSS 778
#define SAHF 779
#define SAL 780
#define SAR 781
#define SHL 782
#define SHR 783
#define SBB 784
#define SCASB 785
#define SCASW 786
#define SCASD 787
#define SETA 788
#define SETAE 789
#define SETB 790
#define SETBE 791
#define SETC 792
#define SETE 793
#define SETG 794
#define SETGE 795
#define SETL 796
#define SETLE 797
#define SETNA 798
#define SETNAE 799
#define SETNB 800
#define SETNBE 801
#define SETNC 802
#define SETNE 803
#define SETNG 804
#define SETNGE 805
#define SETNL 806
#define SETNLE 807
#define SETNO 808
#define SETNP 809
#define SETNS 810
#define SETNZ 811
#define SETO 812
#define SETP 813
#define SETPE 814
#define SETPO 815
#define SETS 816
#define SETZ 817
#define SFENCE 818
#define SGDT 819
#define SHLD 820
#define SHRD 821
#define SHUFPD 822
#define SHUFPS 823
#define SIDT 824
#define SLDT 825
#define SMSW 826
#define SQRTPS 827
#define SQRTSD 828
#define SQRTSS 829
#define STC 830
#define STD 831
#define STI 832
#define STMXCSR 833
#define STOSB 834
#define STOSW 835
#define STOSD 836
#define STOSQ 837
#define STR 838
#define SUB 839
#define SUBPD 840
#define SUBPS 841
#define SUBSD 842
#define SUBSS 843
#define SWAPGS 844
#define SYSCALL 845
#define SYSENTER 846
#define SYSEXIT 847
#define SYSRET 848
#define TEST 849
#define UCOMISD 850
#define UCOMISS 851
#define UD2 852
#define UNPCKHPD 853
#define UNPCKHPS 854
#define UNPCKLPD 855
#define UNPCKLPS 856
#define VERR 857
#define VERW 858
#define WAIT 859
#define FWAIT 860
#define WBINVD 861
#define WRMSR 862
#define XADD 863
#define XCHG 864
#define XGETBV 865
#define XLAT 866
#define XLATB 867
#define XOR 868
#define XORPD 869
#define XORPS 870
#define XRSTOR 871
#define XSAVE 872
#define XSETBV 873
#define INVEPT 874
#define INVVPID 875
#define VMCALL 876
#define VMCLEAR 877
#define VMLAUNCH 878
#define VMPTRLD 879
#define VMPTRST 880
#define VMREAD 881
#define VMRESUME 882
#define VMWRITE 883
#define VMXOFF 884
#define VMXON 885
#define R_AL 886
#define R_CL 887
#define R_DL 888
#define R_BL 889
#define R_AH 890
#define R_CH 891
#define R_DH 892
#define R_BH 893
#define R_AX 894
#define R_CX 895
#define R_DX 896
#define R_BX 897
#define R_SP 898
#define R_BP 899
#define R_SI 900
#define R_DI 901
#define R_EAX 902
#define R_ECX 903
#define R_EDX 904
#define R_EBX 905
#define R_ESP 906
#define R_EBP 907
#define R_ESI 908
#define R_EDI 909
#define R_CR0 910
#define R_CR1 911
#define R_CR2 912
#define R_CR3 913
#define R_CR4 914
#define R_CR5 915
#define R_CR6 916
#define R_CR7 917
#define R_DR0 918
#define R_DR1 919
#define R_DR2 920
#define R_DR3 921
#define R_DR4 922
#define R_DR5 923
#define R_DR6 924
#define R_DR7 925
#define R_MM0 926
#define R_MM1 927
#define R_MM2 928
#define R_MM3 929
#define R_MM4 930
#define R_MM5 931
#define R_MM6 932
#define R_MM7 933
#define R_ST0 934
#define R_ST1 935
#define R_ST2 936
#define R_ST3 937
#define R_ST4 938
#define R_ST5 939
#define R_ST6 940
#define R_ST7 941
#define R_XMM0 942
#define R_XMM1 943
#define R_XMM2 944
#define R_XMM3 945
#define R_XMM4 946
#define R_XMM5 947
#define R_XMM6 948
#define R_XMM7 949
#define SEG_ES 950
#define SEG_CS 951
#define SEG_SS 952
#define SEG_DS 953
#define SEG_FS 954
#define SEG_GS 955
#define OP_REG 956
#define OP_MEM 957
#define OP_IMM 958
#define BYTE_PTR 959
#define WORD_PTR 960
#define DWORD_PTR 961
#define QWORD_PTR 962
#define TWORD_PTR 963
#define SCALE_1 964
#define SCALE_2 965
#define SCALE_4 966
#define SCALE_8 967
#define PLUSSIGN 968
#define SUBSIGN 969
#define ADDR_LAB 970
#define DISPLACEMENT8 971
#define DISPLACEMENT32 972
#define IMMEDIATE8 973
#define IMMEDIATE16 974
#define IMMEDIATE32 975
#define LINESTART 976
#define COLON 977
#define COMMA 978
#define MEMEND 979
#define LINEND 980
#define ERROR 981
#define END 982
#define NONE 983




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1613 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  729
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  270
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1209
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2237

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   983

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   728
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    14,    16,    18,    20,
      23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    47,    49,    51,    53,    55,    57,    59,    61,
      63,    65,    67,    69,    71,    73,    75,    77,    79,    81,
      83,    85,    87,    89,    91,    93,    95,    97,    99,   101,
     103,   105,   107,   109,   111,   113,   115,   117,   119,   121,
     123,   125,   127,   129,   131,   133,   135,   137,   139,   141,
     143,   145,   147,   149,   151,   153,   155,   157,   159,   161,
     163,   165,   167,   169,   171,   173,   175,   177,   179,   181,
     183,   185,   187,   189,   191,   193,   195,   197,   199,   201,
     203,   205,   207,   209,   211,   213,   215,   217,   219,   221,
     223,   225,   227,   229,   231,   233,   235,   237,   239,   241,
     243,   245,   247,   249,   251,   253,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   355,   357,   359,   361,
     363,   365,   367,   369,   371,   373,   374,   375,   376,   378,
     380,   383,   385,   388,   390,   395,   401,   406,   412,   417,
     423,   428,   434,   439,   445,   450,   456,   461,   467,   472,
     478,   484,   490,   496,   501,   507,   512,   518,   523,   529,
     534,   540,   545,   551,   556,   562,   567,   573,   578,   584,
     590,   596,   602,   607,   613,   618,   624,   629,   635,   640,
     646,   651,   657,   662,   668,   673,   679,   684,   690,   696,
     702,   708,   713,   719,   725,   731,   736,   742,   747,   753,
     758,   764,   769,   775,   778,   783,   788,   794,   800,   805,
     810,   816,   822,   827,   832,   838,   844,   849,   854,   860,
     866,   871,   876,   882,   888,   893,   898,   904,   910,   915,
     920,   926,   932,   937,   942,   948,   954,   957,   960,   963,
     966,   969,   973,   977,   979,   981,   983,   985,   989,   991,
     993,   995,   997,   999,  1001,  1003,  1005,  1007,  1009,  1011,
    1013,  1015,  1017,  1019,  1021,  1023,  1025,  1027,  1029,  1031,
    1033,  1035,  1037,  1039,  1041,  1043,  1045,  1047,  1049,  1051,
    1053,  1055,  1060,  1066,  1071,  1077,  1082,  1088,  1093,  1099,
    1104,  1110,  1115,  1121,  1126,  1132,  1137,  1143,  1148,  1154,
    1159,  1165,  1170,  1176,  1181,  1187,  1192,  1198,  1203,  1209,
    1214,  1220,  1225,  1231,  1236,  1242,  1247,  1253,  1258,  1264,
    1269,  1275,  1280,  1286,  1291,  1297,  1302,  1308,  1313,  1319,
    1324,  1330,  1335,  1341,  1346,  1352,  1357,  1363,  1368,  1374,
    1379,  1385,  1390,  1396,  1401,  1407,  1412,  1418,  1423,  1429,
    1434,  1440,  1445,  1451,  1456,  1462,  1467,  1473,  1478,  1484,
    1489,  1495,  1500,  1506,  1511,  1517,  1522,  1528,  1533,  1539,
    1544,  1550,  1555,  1561,  1566,  1572,  1577,  1583,  1588,  1594,
    1599,  1605,  1610,  1616,  1621,  1627,  1632,  1638,  1643,  1649,
    1654,  1660,  1665,  1671,  1676,  1682,  1687,  1693,  1698,  1704,
    1709,  1715,  1720,  1726,  1731,  1737,  1742,  1748,  1753,  1759,
    1764,  1770,  1775,  1781,  1786,  1792,  1797,  1803,  1809,  1815,
    1821,  1823,  1825,  1827,  1832,  1838,  1843,  1848,  1854,  1860,
    1862,  1864,  1869,  1875,  1880,  1886,  1891,  1897,  1899,  1901,
    1903,  1905,  1908,  1912,  1915,  1919,  1922,  1926,  1929,  1933,
    1936,  1940,  1943,  1947,  1952,  1954,  1957,  1961,  1964,  1968,
    1971,  1975,  1978,  1982,  1985,  1989,  1992,  1996,  2001,  2007,
    2012,  2018,  2025,  2033,  2040,  2048,  2055,  2063,  2070,  2078,
    2083,  2088,  2093,  2098,  2103,  2108,  2111,  2115,  2118,  2122,
    2125,  2129,  2135,  2141,  2147,  2149,  2151,  2153,  2155,  2157,
    2160,  2162,  2166,  2168,  2170,  2173,  2176,  2179,  2182,  2185,
    2188,  2191,  2194,  2197,  2200,  2203,  2206,  2209,  2212,  2215,
    2218,  2221,  2224,  2227,  2230,  2233,  2236,  2239,  2242,  2245,
    2248,  2251,  2254,  2257,  2260,  2263,  2266,  2269,  2272,  2275,
    2278,  2281,  2284,  2287,  2291,  2295,  2297,  2302,  2308,  2313,
    2319,  2325,  2331,  2337,  2343,  2349,  2355,  2361,  2367,  2373,
    2379,  2385,  2391,  2393,  2395,  2399,  2403,  2407,  2411,  2414,
    2418,  2421,  2425,  2427,  2429,  2431,  2434,  2437,  2440,  2445,
    2451,  2456,  2462,  2465,  2469,  2471,  2473,  2478,  2484,  2489,
    2495,  2500,  2506,  2511,  2517,  2522,  2528,  2533,  2539,  2545,
    2551,  2557,  2562,  2568,  2573,  2579,  2584,  2589,  2594,  2599,
    2605,  2611,  2617,  2623,  2625,  2627,  2629,  2634,  2640,  2645,
    2651,  2656,  2662,  2667,  2673,  2678,  2684,  2689,  2695,  2698,
    2702,  2705,  2709,  2712,  2716,  2718,  2721,  2725,  2728,  2732,
    2735,  2739,  2741,  2744,  2748,  2751,  2755,  2758,  2762,  2765,
    2769,  2772,  2776,  2781,  2787,  2792,  2798,  2803,  2809,  2814,
    2820,  2825,  2831,  2836,  2842,  2847,  2853,  2858,  2864,  2870,
    2876,  2882,  2887,  2892,  2897,  2902,  2907,  2912,  2918,  2924,
    2930,  2932,  2934,  2936,  2938,  2941,  2945,  2948,  2952,  2955,
    2958,  2961,  2964,  2967,  2969,  2971,  2976,  2982,  2987,  2993,
    2995,  2997,  3001,  3005,  3009,  3013,  3016,  3020,  3023,  3027,
    3030,  3033,  3036,  3039,  3042,  3045,  3048,  3051,  3054,  3056,
    3058,  3060,  3062,  3067,  3072,  3077,  3083,  3089,  3095,  3100,
    3105,  3110,  3116,  3122,  3128,  3133,  3138,  3143,  3149,  3155,
    3161,  3166,  3171,  3176,  3182,  3188,  3194,  3199,  3204,  3209,
    3215,  3221,  3227,  3232,  3237,  3242,  3248,  3254,  3260,  3265,
    3270,  3275,  3281,  3287,  3293,  3298,  3303,  3308,  3314,  3320,
    3326,  3328,  3330,  3332,  3334,  3336,  3339,  3341,  3343,  3348,
    3353,  3358,  3364,  3370,  3376,  3381,  3386,  3391,  3397,  3403,
    3409,  3414,  3419,  3424,  3430,  3436,  3442,  3447,  3452,  3457,
    3463,  3469,  3475,  3480,  3485,  3490,  3496,  3502,  3508,  3513,
    3518,  3523,  3529,  3535,  3541,  3546,  3551,  3556,  3562,  3568,
    3574,  3579,  3584,  3589,  3595,  3601,  3607,  3612,  3618,  3623,
    3629,  3634,  3640,  3645,  3651,  3656,  3662,  3667,  3673,  3678,
    3684,  3689,  3695,  3701,  3707,  3713,  3715,  3717,  3719,  3721,
    3723,  3725,  3727,  3729,  3731,  3733,  3735,  3737,  3739,  3741,
    3743,  3745,  3747,  3749,  3751,  3753,  3755,  3757,  3759,  3761,
    3763,  3765,  3767,  3769,  3771,  3773,  3775,  3777,  3779,  3782,
    3786,  3789,  3793,  3796,  3800,  3803,  3807,  3810,  3814,  3817,
    3821,  3824,  3828,  3831,  3835,  3838,  3842,  3845,  3849,  3852,
    3856,  3859,  3863,  3866,  3870,  3873,  3877,  3880,  3884,  3887,
    3891,  3894,  3898,  3901,  3905,  3908,  3912,  3915,  3919,  3922,
    3926,  3929,  3933,  3936,  3940,  3943,  3947,  3950,  3954,  3957,
    3961,  3964,  3968,  3971,  3975,  3978,  3982,  3985,  3989,  3991,
    3995,  4002,  4010,  4017,  4025,  4032,  4040,  4047,  4055,  4062,
    4070,  4077,  4085,  4092,  4100,  4107,  4115,  4119,  4123,  4126,
    4129,  4133,  4136,  4138,  4140,  4142,  4146,  4148,  4150,  4152,
    4155,  4159,  4164,  4170,  4175,  4181,  4186,  4192,  4197,  4203,
    4208,  4214,  4219,  4225,  4230,  4236,  4241,  4247,  4253,  4259,
    4265,  4267,  4269,  4271,  4273,  4275,  4280,  4286,  4291,  4297,
    4302,  4308,  4313,  4319,  4324,  4330,  4335,  4341,  4343,  4346,
    4350,  4353,  4357,  4359,  4361,  4363,  4365,  4370,  4376,  4381,
    4387,  4392,  4398,  4403,  4409,  4415,  4420,  4426,  4432,  4437,
    4443,  4449,  4451,  4455,  4457,  4462,  4468,  4473,  4479,  4484,
    4490,  4495,  4501,  4506,  4512,  4517,  4523,  4528,  4534,  4539,
    4545,  4551,  4557,  4563,  4567,  4569,  4571,  4573,  4577,  4580,
    4582,  4584,  4586,  4590,  4594,  4597,  4602,  4607,  4614,  4621,
    4623,  4625,  4627,  4629,  4631,  4633,  4635,  4637,  4639,  4641,
    4643,  4645,  4647,  4649,  4651,  4653,  4655,  4657,  4659,  4661,
    4663,  4665,  4667,  4669,  4671,  4673,  4675,  4677,  4679,  4681,
    4683,  4685,  4687,  4689,  4691,  4693,  4695,  4697,  4699,  4701,
    4703,  4705,  4707,  4709,  4711,  4713,  4715,  4717,  4719,  4721,
    4723,  4725,  4727,  4729,  4731,  4733,  4735,  4737,  4739,  4741,
    4743,  4745,  4747,  4749,  4751,  4753,  4755,  4757,  4759,  4761,
    4763,  4765,  4767,  4769,  4771,  4773,  4775,  4777,  4779,  4781
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     730,     0,    -1,   731,    -1,   730,   731,    -1,   975,   732,
     998,    -1,   733,    -1,   734,    -1,   735,    -1,   736,    -1,
     715,   996,    -1,   737,    -1,   738,    -1,   739,    -1,   740,
      -1,   741,    -1,   742,    -1,   743,    -1,   744,    -1,   745,
      -1,   746,    -1,   747,    -1,   748,    -1,   749,    -1,   750,
      -1,   751,    -1,   752,    -1,   753,    -1,   754,    -1,   755,
      -1,   756,    -1,   757,    -1,   758,    -1,   759,    -1,   760,
      -1,   761,    -1,   762,    -1,   793,    -1,   794,    -1,   795,
      -1,   796,    -1,   797,    -1,   798,    -1,   799,    -1,   800,
      -1,   801,    -1,   802,    -1,   803,    -1,   804,    -1,   805,
      -1,   806,    -1,   807,    -1,   808,    -1,   809,    -1,   810,
      -1,   811,    -1,   812,    -1,   813,    -1,   814,    -1,   815,
      -1,   816,    -1,   819,    -1,   817,    -1,   818,    -1,   820,
      -1,   821,    -1,   822,    -1,   823,    -1,   824,    -1,   825,
      -1,   826,    -1,   827,    -1,   828,    -1,   829,    -1,   830,
      -1,   831,    -1,   832,    -1,   833,    -1,   834,    -1,   835,
      -1,   836,    -1,   837,    -1,   838,    -1,   839,    -1,   840,
      -1,   841,    -1,   842,    -1,   843,    -1,   844,    -1,   845,
      -1,   846,    -1,   847,    -1,   848,    -1,   849,    -1,   850,
      -1,   851,    -1,   852,    -1,   853,    -1,   854,    -1,   855,
      -1,   856,    -1,   857,    -1,   858,    -1,   859,    -1,   860,
      -1,   861,    -1,   862,    -1,   863,    -1,   864,    -1,   865,
      -1,   866,    -1,   867,    -1,   868,    -1,   869,    -1,   870,
      -1,   871,    -1,   872,    -1,   873,    -1,   874,    -1,   875,
      -1,   876,    -1,   877,    -1,   878,    -1,   879,    -1,   880,
      -1,   881,    -1,   882,    -1,   883,    -1,   884,    -1,   885,
      -1,   886,    -1,   887,    -1,   888,    -1,   889,    -1,   890,
      -1,   891,    -1,   892,    -1,   893,    -1,   894,    -1,   895,
      -1,   896,    -1,   897,    -1,   898,    -1,   899,    -1,   900,
      -1,   901,    -1,   902,    -1,   903,    -1,   934,    -1,   935,
      -1,   936,    -1,   937,    -1,   938,    -1,   939,    -1,   940,
      -1,   941,    -1,   942,    -1,   943,    -1,   944,    -1,   945,
      -1,   946,    -1,   947,    -1,   948,    -1,   949,    -1,   950,
      -1,   951,    -1,   952,    -1,   953,    -1,   954,    -1,   955,
      -1,   956,    -1,   957,    -1,   958,    -1,   959,    -1,   960,
      -1,   961,    -1,   962,    -1,   963,    -1,   964,    -1,   965,
      -1,   966,    -1,   967,    -1,   968,    -1,   969,    -1,   970,
      -1,   971,    -1,    -1,    -1,    -1,     9,    -1,    10,    -1,
      10,   991,    -1,    11,    -1,    11,   991,    -1,    12,    -1,
      13,   978,   997,   991,    -1,    13,   987,   973,   997,   991,
      -1,    13,   979,   997,   992,    -1,    13,   988,   973,   997,
     992,    -1,    13,   980,   997,   993,    -1,    13,   989,   973,
     997,   993,    -1,    13,   979,   997,   991,    -1,    13,   988,
     973,   997,   991,    -1,    13,   980,   997,   991,    -1,    13,
     989,   973,   997,   991,    -1,    13,   978,   997,   978,    -1,
      13,   987,   973,   997,   978,    -1,    13,   979,   997,   979,
      -1,    13,   988,   973,   997,   979,    -1,    13,   980,   997,
     980,    -1,    13,   989,   973,   997,   980,    -1,    13,   978,
     997,   987,   973,    -1,    13,   979,   997,   988,   973,    -1,
      13,   980,   997,   989,   973,    -1,    14,   978,   997,   991,
      -1,    14,   987,   973,   997,   991,    -1,    14,   979,   997,
     992,    -1,    14,   988,   973,   997,   992,    -1,    14,   980,
     997,   993,    -1,    14,   989,   973,   997,   993,    -1,    14,
     979,   997,   991,    -1,    14,   988,   973,   997,   991,    -1,
      14,   980,   997,   991,    -1,    14,   989,   973,   997,   991,
      -1,    14,   978,   997,   978,    -1,    14,   987,   973,   997,
     978,    -1,    14,   979,   997,   979,    -1,    14,   988,   973,
     997,   979,    -1,    14,   980,   997,   980,    -1,    14,   989,
     973,   997,   980,    -1,    14,   978,   997,   987,   973,    -1,
      14,   979,   997,   988,   973,    -1,    14,   980,   997,   989,
     973,    -1,    27,   978,   997,   991,    -1,    27,   987,   973,
     997,   991,    -1,    27,   979,   997,   992,    -1,    27,   988,
     973,   997,   992,    -1,    27,   980,   997,   993,    -1,    27,
     989,   973,   997,   993,    -1,    27,   979,   997,   991,    -1,
      27,   988,   973,   997,   991,    -1,    27,   980,   997,   991,
      -1,    27,   989,   973,   997,   991,    -1,    27,   978,   997,
     978,    -1,    27,   987,   973,   997,   978,    -1,    27,   979,
     997,   979,    -1,    27,   988,   973,   997,   979,    -1,    27,
     980,   997,   980,    -1,    27,   989,   973,   997,   980,    -1,
      27,   978,   997,   987,   973,    -1,    27,   979,   997,   988,
     973,    -1,    27,   980,   997,   989,   973,    -1,    32,   979,
     997,   979,    -1,    32,   988,   973,   997,   979,    -1,    37,
     979,   997,   988,   973,    -1,    37,   980,   997,   989,   973,
      -1,    38,   979,   997,   979,    -1,    38,   979,   997,   988,
     973,    -1,    38,   980,   997,   980,    -1,    38,   980,   997,
     989,   973,    -1,    39,   979,   997,   979,    -1,    39,   979,
     997,   988,   973,    -1,    39,   980,   997,   980,    -1,    39,
     980,   997,   989,   973,    -1,    40,   980,    -1,    41,   979,
     997,   979,    -1,    41,   980,   997,   980,    -1,    41,   988,
     973,   997,   979,    -1,    41,   989,   973,   997,   980,    -1,
      41,   979,   997,   991,    -1,    41,   980,   997,   991,    -1,
      41,   988,   973,   997,   991,    -1,    41,   989,   973,   997,
     991,    -1,    42,   979,   997,   979,    -1,    42,   980,   997,
     980,    -1,    42,   988,   973,   997,   979,    -1,    42,   989,
     973,   997,   980,    -1,    42,   979,   997,   991,    -1,    42,
     980,   997,   991,    -1,    42,   988,   973,   997,   991,    -1,
      42,   989,   973,   997,   991,    -1,    43,   979,   997,   979,
      -1,    43,   980,   997,   980,    -1,    43,   988,   973,   997,
     979,    -1,    43,   989,   973,   997,   980,    -1,    43,   979,
     997,   991,    -1,    43,   980,   997,   991,    -1,    43,   988,
     973,   997,   991,    -1,    43,   989,   973,   997,   991,    -1,
      44,   979,   997,   979,    -1,    44,   980,   997,   980,    -1,
      44,   988,   973,   997,   979,    -1,    44,   989,   973,   997,
     980,    -1,    44,   979,   997,   991,    -1,    44,   980,   997,
     991,    -1,    44,   988,   973,   997,   991,    -1,    44,   989,
     973,   997,   991,    -1,    45,   972,    -1,    45,   992,    -1,
      45,   993,    -1,    45,   979,    -1,    45,   980,    -1,    45,
     988,   973,    -1,    45,   989,   973,    -1,    46,    -1,    47,
      -1,    49,    -1,    50,    -1,    51,   987,   973,    -1,    52,
      -1,    53,    -1,    54,    -1,   763,    -1,   764,    -1,   765,
      -1,   766,    -1,   767,    -1,   768,    -1,   769,    -1,   770,
      -1,   771,    -1,   772,    -1,   773,    -1,   774,    -1,   775,
      -1,   776,    -1,   777,    -1,   778,    -1,   779,    -1,   780,
      -1,   781,    -1,   782,    -1,   783,    -1,   784,    -1,   785,
      -1,   786,    -1,   787,    -1,   788,    -1,   789,    -1,   790,
      -1,   791,    -1,   792,    -1,    55,   979,   997,   979,    -1,
      55,   979,   997,   988,   973,    -1,    55,   980,   997,   980,
      -1,    55,   980,   997,   989,   973,    -1,    56,   979,   997,
     979,    -1,    56,   979,   997,   988,   973,    -1,    56,   980,
     997,   980,    -1,    56,   980,   997,   989,   973,    -1,    57,
     979,   997,   979,    -1,    57,   979,   997,   988,   973,    -1,
      57,   980,   997,   980,    -1,    57,   980,   997,   989,   973,
      -1,    58,   979,   997,   979,    -1,    58,   979,   997,   988,
     973,    -1,    58,   980,   997,   980,    -1,    58,   980,   997,
     989,   973,    -1,    59,   979,   997,   979,    -1,    59,   979,
     997,   988,   973,    -1,    59,   980,   997,   980,    -1,    59,
     980,   997,   989,   973,    -1,    60,   979,   997,   979,    -1,
      60,   979,   997,   988,   973,    -1,    60,   980,   997,   980,
      -1,    60,   980,   997,   989,   973,    -1,    61,   979,   997,
     979,    -1,    61,   979,   997,   988,   973,    -1,    61,   980,
     997,   980,    -1,    61,   980,   997,   989,   973,    -1,    62,
     979,   997,   979,    -1,    62,   979,   997,   988,   973,    -1,
      62,   980,   997,   980,    -1,    62,   980,   997,   989,   973,
      -1,    63,   979,   997,   979,    -1,    63,   979,   997,   988,
     973,    -1,    63,   980,   997,   980,    -1,    63,   980,   997,
     989,   973,    -1,    64,   979,   997,   979,    -1,    64,   979,
     997,   988,   973,    -1,    64,   980,   997,   980,    -1,    64,
     980,   997,   989,   973,    -1,    65,   979,   997,   979,    -1,
      65,   979,   997,   988,   973,    -1,    65,   980,   997,   980,
      -1,    65,   980,   997,   989,   973,    -1,    66,   979,   997,
     979,    -1,    66,   979,   997,   988,   973,    -1,    66,   980,
     997,   980,    -1,    66,   980,   997,   989,   973,    -1,    67,
     979,   997,   979,    -1,    67,   979,   997,   988,   973,    -1,
      67,   980,   997,   980,    -1,    67,   980,   997,   989,   973,
      -1,    68,   979,   997,   979,    -1,    68,   979,   997,   988,
     973,    -1,    68,   980,   997,   980,    -1,    68,   980,   997,
     989,   973,    -1,    69,   979,   997,   979,    -1,    69,   979,
     997,   988,   973,    -1,    69,   980,   997,   980,    -1,    69,
     980,   997,   989,   973,    -1,    70,   979,   997,   979,    -1,
      70,   979,   997,   988,   973,    -1,    70,   980,   997,   980,
      -1,    70,   980,   997,   989,   973,    -1,    71,   979,   997,
     979,    -1,    71,   979,   997,   988,   973,    -1,    71,   980,
     997,   980,    -1,    71,   980,   997,   989,   973,    -1,    72,
     979,   997,   979,    -1,    72,   979,   997,   988,   973,    -1,
      72,   980,   997,   980,    -1,    72,   980,   997,   989,   973,
      -1,    73,   979,   997,   979,    -1,    73,   979,   997,   988,
     973,    -1,    73,   980,   997,   980,    -1,    73,   980,   997,
     989,   973,    -1,    74,   979,   997,   979,    -1,    74,   979,
     997,   988,   973,    -1,    74,   980,   997,   980,    -1,    74,
     980,   997,   989,   973,    -1,    75,   979,   997,   979,    -1,
      75,   979,   997,   988,   973,    -1,    75,   980,   997,   980,
      -1,    75,   980,   997,   989,   973,    -1,    76,   979,   997,
     979,    -1,    76,   979,   997,   988,   973,    -1,    76,   980,
     997,   980,    -1,    76,   980,   997,   989,   973,    -1,    77,
     979,   997,   979,    -1,    77,   979,   997,   988,   973,    -1,
      77,   980,   997,   980,    -1,    77,   980,   997,   989,   973,
      -1,    78,   979,   997,   979,    -1,    78,   979,   997,   988,
     973,    -1,    78,   980,   997,   980,    -1,    78,   980,   997,
     989,   973,    -1,    79,   979,   997,   979,    -1,    79,   979,
     997,   988,   973,    -1,    79,   980,   997,   980,    -1,    79,
     980,   997,   989,   973,    -1,    80,   979,   997,   979,    -1,
      80,   979,   997,   988,   973,    -1,    80,   980,   997,   980,
      -1,    80,   980,   997,   989,   973,    -1,    81,   979,   997,
     979,    -1,    81,   979,   997,   988,   973,    -1,    81,   980,
     997,   980,    -1,    81,   980,   997,   989,   973,    -1,    82,
     979,   997,   979,    -1,    82,   979,   997,   988,   973,    -1,
      82,   980,   997,   980,    -1,    82,   980,   997,   989,   973,
      -1,    83,   979,   997,   979,    -1,    83,   979,   997,   988,
     973,    -1,    83,   980,   997,   980,    -1,    83,   980,   997,
     989,   973,    -1,    84,   979,   997,   979,    -1,    84,   979,
     997,   988,   973,    -1,    84,   980,   997,   980,    -1,    84,
     980,   997,   989,   973,    -1,    85,   978,   997,   991,    -1,
      85,   987,   973,   997,   991,    -1,    85,   979,   997,   992,
      -1,    85,   988,   973,   997,   992,    -1,    85,   980,   997,
     993,    -1,    85,   989,   973,   997,   993,    -1,    85,   979,
     997,   991,    -1,    85,   988,   973,   997,   991,    -1,    85,
     980,   997,   991,    -1,    85,   989,   973,   997,   991,    -1,
      85,   978,   997,   978,    -1,    85,   987,   973,   997,   978,
      -1,    85,   979,   997,   979,    -1,    85,   988,   973,   997,
     979,    -1,    85,   980,   997,   980,    -1,    85,   989,   973,
     997,   980,    -1,    85,   978,   997,   987,   973,    -1,    85,
     979,   997,   988,   973,    -1,    85,   980,   997,   989,   973,
      -1,    88,    -1,    89,    -1,    90,    -1,    94,   978,   997,
     978,    -1,    94,   987,   973,   997,   978,    -1,    94,   979,
     997,   979,    -1,    94,   980,   997,   980,    -1,    94,   988,
     973,   997,   979,    -1,    94,   989,   973,   997,   980,    -1,
      95,    -1,    98,    -1,    99,   980,   997,   978,    -1,    99,
     980,   997,   987,   973,    -1,    99,   980,   997,   979,    -1,
      99,   980,   997,   988,   973,    -1,    99,   980,   997,   980,
      -1,    99,   980,   997,   989,   973,    -1,   122,    -1,   123,
      -1,   125,    -1,   126,    -1,   127,   978,    -1,   127,   987,
     973,    -1,   127,   979,    -1,   127,   988,   973,    -1,   127,
     980,    -1,   127,   989,   973,    -1,   128,   978,    -1,   128,
     987,   973,    -1,   128,   979,    -1,   128,   988,   973,    -1,
     128,   980,    -1,   128,   989,   973,    -1,   136,   979,   997,
     991,    -1,   229,    -1,   232,   978,    -1,   232,   987,   973,
      -1,   232,   979,    -1,   232,   988,   973,    -1,   232,   980,
      -1,   232,   989,   973,    -1,   233,   978,    -1,   233,   987,
     973,    -1,   233,   979,    -1,   233,   988,   973,    -1,   233,
     980,    -1,   233,   989,   973,    -1,   233,   979,   997,   979,
      -1,   233,   979,   997,   988,   973,    -1,   233,   980,   997,
     980,    -1,   233,   980,   997,   989,   973,    -1,   233,   979,
     997,   979,   997,   991,    -1,   233,   979,   997,   988,   973,
     997,   991,    -1,   233,   980,   997,   980,   997,   991,    -1,
     233,   980,   997,   989,   973,   997,   991,    -1,   233,   979,
     997,   979,   997,   992,    -1,   233,   979,   997,   988,   973,
     997,   992,    -1,   233,   980,   997,   980,   997,   993,    -1,
     233,   980,   997,   989,   973,   997,   993,    -1,   234,   631,
     997,   991,    -1,   234,   639,   997,   992,    -1,   234,   647,
     997,   993,    -1,   234,   631,   997,   641,    -1,   234,   639,
     997,   641,    -1,   234,   647,   997,   641,    -1,   235,   978,
      -1,   235,   987,   973,    -1,   235,   979,    -1,   235,   988,
     973,    -1,   235,   980,    -1,   235,   989,   973,    -1,   236,
     987,   973,   997,   641,    -1,   236,   988,   973,   997,   641,
      -1,   236,   989,   973,   997,   641,    -1,   237,    -1,   238,
      -1,   239,    -1,   242,    -1,   243,    -1,   241,   991,    -1,
     244,    -1,   245,   987,   973,    -1,   246,    -1,   247,    -1,
     253,   972,    -1,   254,   972,    -1,   255,   972,    -1,   248,
     972,    -1,   249,   972,    -1,   250,   972,    -1,   251,   972,
      -1,   252,   972,    -1,   256,   972,    -1,   280,   972,    -1,
     257,   972,    -1,   258,   972,    -1,   259,   972,    -1,   260,
     972,    -1,   261,   972,    -1,   262,   972,    -1,   263,   972,
      -1,   264,   972,    -1,   265,   972,    -1,   266,   972,    -1,
     267,   972,    -1,   268,   972,    -1,   269,   972,    -1,   270,
     972,    -1,   271,   972,    -1,   272,   972,    -1,   273,   972,
      -1,   274,   972,    -1,   275,   972,    -1,   276,   972,    -1,
     277,   972,    -1,   278,   972,    -1,   279,   972,    -1,   281,
     972,    -1,   281,   991,    -1,   281,   992,    -1,   281,   993,
      -1,   281,   979,    -1,   281,   980,    -1,   281,   988,   973,
      -1,   281,   989,   973,    -1,   282,    -1,   283,   979,   997,
     979,    -1,   283,   979,   997,   988,   973,    -1,   283,   980,
     997,   980,    -1,   283,   980,   997,   988,   973,    -1,   286,
     979,   997,   988,   973,    -1,   286,   980,   997,   989,   973,
      -1,   290,   979,   997,   988,   973,    -1,   290,   980,   997,
     989,   973,    -1,   287,   979,   997,   988,   973,    -1,   287,
     980,   997,   989,   973,    -1,   288,   979,   997,   988,   973,
      -1,   288,   980,   997,   989,   973,    -1,   289,   979,   997,
     988,   973,    -1,   289,   980,   997,   989,   973,    -1,   291,
     979,   997,   988,   973,    -1,   291,   980,   997,   989,   973,
      -1,   292,    -1,   293,    -1,   294,   988,   973,    -1,   294,
     989,   973,    -1,   295,   988,   973,    -1,   295,   989,   973,
      -1,   296,   979,    -1,   296,   988,   973,    -1,   297,   979,
      -1,   297,   988,   973,    -1,   298,    -1,   299,    -1,   300,
      -1,   302,   972,    -1,   303,   972,    -1,   304,   972,    -1,
     305,   979,   997,   979,    -1,   305,   979,   997,   988,   973,
      -1,   305,   980,   997,   980,    -1,   305,   980,   997,   988,
     973,    -1,   306,   979,    -1,   306,   988,   973,    -1,   313,
      -1,   318,    -1,   319,   978,   997,   991,    -1,   319,   987,
     973,   997,   991,    -1,   319,   979,   997,   992,    -1,   319,
     988,   973,   997,   992,    -1,   319,   980,   997,   993,    -1,
     319,   989,   973,   997,   993,    -1,   319,   978,   997,   978,
      -1,   319,   987,   973,   997,   978,    -1,   319,   979,   997,
     979,    -1,   319,   988,   973,   997,   979,    -1,   319,   980,
     997,   980,    -1,   319,   989,   973,   997,   980,    -1,   319,
     978,   997,   987,   973,    -1,   319,   979,   997,   988,   973,
      -1,   319,   980,   997,   989,   973,    -1,   319,   979,   997,
     984,    -1,   319,   988,   973,   997,   984,    -1,   319,   984,
     997,   979,    -1,   319,   984,   997,   988,   973,    -1,   319,
     980,   997,   981,    -1,   319,   981,   997,   980,    -1,   319,
     980,   997,   982,    -1,   319,   982,   997,   980,    -1,   322,
     979,   997,   988,   973,    -1,   322,   988,   973,   997,   979,
      -1,   322,   980,   997,   989,   973,    -1,   322,   989,   973,
     997,   980,    -1,   345,    -1,   346,    -1,   347,    -1,   353,
     979,   997,   978,    -1,   353,   979,   997,   987,   973,    -1,
     353,   980,   997,   978,    -1,   353,   980,   997,   987,   973,
      -1,   353,   980,   997,   979,    -1,   353,   980,   997,   988,
     973,    -1,   357,   979,   997,   978,    -1,   357,   979,   997,
     987,   973,    -1,   357,   980,   997,   978,    -1,   357,   980,
     997,   987,   973,    -1,   357,   980,   997,   979,    -1,   357,
     980,   997,   988,   973,    -1,   359,   978,    -1,   359,   987,
     973,    -1,   359,   979,    -1,   359,   988,   973,    -1,   359,
     980,    -1,   359,   989,   973,    -1,   364,    -1,   365,   978,
      -1,   365,   987,   973,    -1,   365,   979,    -1,   365,   988,
     973,    -1,   365,   980,    -1,   365,   989,   973,    -1,   366,
      -1,   366,   979,    -1,   366,   988,   973,    -1,   366,   980,
      -1,   366,   989,   973,    -1,   367,   978,    -1,   367,   987,
     973,    -1,   367,   979,    -1,   367,   988,   973,    -1,   367,
     980,    -1,   367,   989,   973,    -1,   368,   978,   997,   991,
      -1,   368,   987,   973,   997,   991,    -1,   368,   979,   997,
     992,    -1,   368,   988,   973,   997,   992,    -1,   368,   980,
     997,   993,    -1,   368,   989,   973,   997,   993,    -1,   368,
     979,   997,   991,    -1,   368,   988,   973,   997,   991,    -1,
     368,   980,   997,   991,    -1,   368,   989,   973,   997,   991,
      -1,   368,   978,   997,   978,    -1,   368,   987,   973,   997,
     978,    -1,   368,   979,   997,   979,    -1,   368,   988,   973,
     997,   979,    -1,   368,   980,   997,   980,    -1,   368,   989,
     973,   997,   980,    -1,   368,   978,   997,   987,   973,    -1,
     368,   979,   997,   988,   973,    -1,   368,   980,   997,   989,
     973,    -1,   371,   991,   997,   631,    -1,   371,   991,   997,
     639,    -1,   371,   991,   997,   647,    -1,   371,   641,   997,
     631,    -1,   371,   641,   997,   639,    -1,   371,   641,   997,
     647,    -1,   372,   641,   997,   987,   973,    -1,   372,   641,
     997,   988,   973,    -1,   372,   641,   997,   989,   973,    -1,
     373,    -1,   374,    -1,   375,    -1,   394,    -1,   451,   979,
      -1,   451,   988,   973,    -1,   451,   980,    -1,   451,   989,
     973,    -1,   451,   698,    -1,   451,   695,    -1,   451,   697,
      -1,   451,   699,    -1,   451,   700,    -1,   452,    -1,   453,
      -1,   454,   979,   997,   979,    -1,   454,   979,   997,   988,
     973,    -1,   454,   980,   997,   980,    -1,   454,   980,   997,
     989,   973,    -1,   455,    -1,   456,    -1,   459,   987,   973,
      -1,   460,   987,   973,    -1,   461,   987,   973,    -1,   462,
     987,   973,    -1,   499,   979,    -1,   499,   988,   973,    -1,
     499,   980,    -1,   499,   989,   973,    -1,   499,   991,    -1,
     499,   992,    -1,   499,   993,    -1,   499,   696,    -1,   499,
     698,    -1,   499,   695,    -1,   499,   697,    -1,   499,   699,
      -1,   499,   700,    -1,   500,    -1,   501,    -1,   502,    -1,
     503,    -1,   505,   978,   997,   991,    -1,   505,   979,   997,
     991,    -1,   505,   980,   997,   991,    -1,   505,   987,   973,
     997,   991,    -1,   505,   988,   973,   997,   991,    -1,   505,
     989,   973,   997,   991,    -1,   505,   978,   997,   632,    -1,
     505,   979,   997,   632,    -1,   505,   980,   997,   632,    -1,
     505,   987,   973,   997,   632,    -1,   505,   988,   973,   997,
     632,    -1,   505,   989,   973,   997,   632,    -1,   506,   978,
     997,   991,    -1,   506,   979,   997,   991,    -1,   506,   980,
     997,   991,    -1,   506,   987,   973,   997,   991,    -1,   506,
     988,   973,   997,   991,    -1,   506,   989,   973,   997,   991,
      -1,   506,   978,   997,   632,    -1,   506,   979,   997,   632,
      -1,   506,   980,   997,   632,    -1,   506,   987,   973,   997,
     632,    -1,   506,   988,   973,   997,   632,    -1,   506,   989,
     973,   997,   632,    -1,   507,   978,   997,   991,    -1,   507,
     979,   997,   991,    -1,   507,   980,   997,   991,    -1,   507,
     987,   973,   997,   991,    -1,   507,   988,   973,   997,   991,
      -1,   507,   989,   973,   997,   991,    -1,   507,   978,   997,
     632,    -1,   507,   979,   997,   632,    -1,   507,   980,   997,
     632,    -1,   507,   987,   973,   997,   632,    -1,   507,   988,
     973,   997,   632,    -1,   507,   989,   973,   997,   632,    -1,
     508,   978,   997,   991,    -1,   508,   979,   997,   991,    -1,
     508,   980,   997,   991,    -1,   508,   987,   973,   997,   991,
      -1,   508,   988,   973,   997,   991,    -1,   508,   989,   973,
     997,   991,    -1,   508,   978,   997,   632,    -1,   508,   979,
     997,   632,    -1,   508,   980,   997,   632,    -1,   508,   987,
     973,   997,   632,    -1,   508,   988,   973,   997,   632,    -1,
     508,   989,   973,   997,   632,    -1,   511,    -1,   512,    -1,
     513,    -1,   514,    -1,   515,    -1,   516,   992,    -1,   521,
      -1,   524,    -1,   525,   978,   997,   991,    -1,   525,   979,
     997,   991,    -1,   525,   980,   997,   991,    -1,   525,   987,
     973,   997,   991,    -1,   525,   988,   973,   997,   991,    -1,
     525,   989,   973,   997,   991,    -1,   525,   978,   997,   632,
      -1,   525,   979,   997,   632,    -1,   525,   980,   997,   632,
      -1,   525,   987,   973,   997,   632,    -1,   525,   988,   973,
     997,   632,    -1,   525,   989,   973,   997,   632,    -1,   526,
     978,   997,   991,    -1,   526,   979,   997,   991,    -1,   526,
     980,   997,   991,    -1,   526,   987,   973,   997,   991,    -1,
     526,   988,   973,   997,   991,    -1,   526,   989,   973,   997,
     991,    -1,   526,   978,   997,   632,    -1,   526,   979,   997,
     632,    -1,   526,   980,   997,   632,    -1,   526,   987,   973,
     997,   632,    -1,   526,   988,   973,   997,   632,    -1,   526,
     989,   973,   997,   632,    -1,   527,   978,   997,   991,    -1,
     527,   979,   997,   991,    -1,   527,   980,   997,   991,    -1,
     527,   987,   973,   997,   991,    -1,   527,   988,   973,   997,
     991,    -1,   527,   989,   973,   997,   991,    -1,   527,   978,
     997,   632,    -1,   527,   979,   997,   632,    -1,   527,   980,
     997,   632,    -1,   527,   987,   973,   997,   632,    -1,   527,
     988,   973,   997,   632,    -1,   527,   989,   973,   997,   632,
      -1,   528,   978,   997,   991,    -1,   528,   979,   997,   991,
      -1,   528,   980,   997,   991,    -1,   528,   987,   973,   997,
     991,    -1,   528,   988,   973,   997,   991,    -1,   528,   989,
     973,   997,   991,    -1,   528,   978,   997,   632,    -1,   528,
     979,   997,   632,    -1,   528,   980,   997,   632,    -1,   528,
     987,   973,   997,   632,    -1,   528,   988,   973,   997,   632,
      -1,   528,   989,   973,   997,   632,    -1,   529,   978,   997,
     991,    -1,   529,   987,   973,   997,   991,    -1,   529,   979,
     997,   992,    -1,   529,   988,   973,   997,   992,    -1,   529,
     980,   997,   993,    -1,   529,   989,   973,   997,   993,    -1,
     529,   979,   997,   991,    -1,   529,   988,   973,   997,   991,
      -1,   529,   980,   997,   991,    -1,   529,   989,   973,   997,
     991,    -1,   529,   978,   997,   978,    -1,   529,   987,   973,
     997,   978,    -1,   529,   979,   997,   979,    -1,   529,   988,
     973,   997,   979,    -1,   529,   980,   997,   980,    -1,   529,
     989,   973,   997,   980,    -1,   529,   978,   997,   987,   973,
      -1,   529,   979,   997,   988,   973,    -1,   529,   980,   997,
     989,   973,    -1,   530,    -1,   531,    -1,   532,    -1,   904,
      -1,   905,    -1,   906,    -1,   907,    -1,   908,    -1,   909,
      -1,   910,    -1,   911,    -1,   912,    -1,   913,    -1,   914,
      -1,   915,    -1,   916,    -1,   917,    -1,   918,    -1,   919,
      -1,   920,    -1,   921,    -1,   922,    -1,   923,    -1,   924,
      -1,   925,    -1,   926,    -1,   927,    -1,   928,    -1,   929,
      -1,   930,    -1,   931,    -1,   932,    -1,   933,    -1,   533,
     978,    -1,   533,   987,   973,    -1,   534,   978,    -1,   534,
     987,   973,    -1,   535,   978,    -1,   535,   987,   973,    -1,
     536,   978,    -1,   536,   987,   973,    -1,   537,   978,    -1,
     537,   987,   973,    -1,   538,   978,    -1,   538,   987,   973,
      -1,   539,   978,    -1,   539,   987,   973,    -1,   540,   978,
      -1,   540,   987,   973,    -1,   541,   978,    -1,   541,   987,
     973,    -1,   542,   978,    -1,   542,   987,   973,    -1,   543,
     978,    -1,   543,   987,   973,    -1,   544,   978,    -1,   544,
     987,   973,    -1,   545,   978,    -1,   545,   987,   973,    -1,
     546,   978,    -1,   546,   987,   973,    -1,   547,   978,    -1,
     547,   987,   973,    -1,   548,   978,    -1,   548,   987,   973,
      -1,   549,   978,    -1,   549,   987,   973,    -1,   550,   978,
      -1,   550,   987,   973,    -1,   551,   978,    -1,   551,   987,
     973,    -1,   552,   978,    -1,   552,   987,   973,    -1,   553,
     978,    -1,   553,   987,   973,    -1,   554,   978,    -1,   554,
     987,   973,    -1,   555,   978,    -1,   555,   987,   973,    -1,
     556,   978,    -1,   556,   987,   973,    -1,   557,   978,    -1,
     557,   987,   973,    -1,   558,   978,    -1,   558,   987,   973,
      -1,   559,   978,    -1,   559,   987,   973,    -1,   560,   978,
      -1,   560,   987,   973,    -1,   561,   978,    -1,   561,   987,
     973,    -1,   562,   978,    -1,   562,   987,   973,    -1,   563,
      -1,   564,   989,   973,    -1,   565,   979,   997,   979,   997,
     991,    -1,   565,   988,   973,   997,   979,   997,   991,    -1,
     565,   979,   997,   979,   997,   632,    -1,   565,   988,   973,
     997,   979,   997,   632,    -1,   565,   980,   997,   980,   997,
     991,    -1,   565,   989,   973,   997,   980,   997,   991,    -1,
     565,   980,   997,   980,   997,   632,    -1,   565,   989,   973,
     997,   980,   997,   632,    -1,   566,   979,   997,   979,   997,
     991,    -1,   566,   988,   973,   997,   979,   997,   991,    -1,
     566,   979,   997,   979,   997,   632,    -1,   566,   988,   973,
     997,   979,   997,   632,    -1,   566,   980,   997,   980,   997,
     991,    -1,   566,   989,   973,   997,   980,   997,   991,    -1,
     566,   980,   997,   980,   997,   632,    -1,   566,   989,   973,
     997,   980,   997,   632,    -1,   569,   989,   973,    -1,   570,
     988,   973,    -1,   570,   979,    -1,   571,   979,    -1,   571,
     988,   973,    -1,   571,   980,    -1,   575,    -1,   576,    -1,
     577,    -1,   578,   989,   973,    -1,   579,    -1,   580,    -1,
     581,    -1,   583,   979,    -1,   583,   988,   973,    -1,   584,
     978,   997,   991,    -1,   584,   987,   973,   997,   991,    -1,
     584,   979,   997,   992,    -1,   584,   988,   973,   997,   992,
      -1,   584,   980,   997,   993,    -1,   584,   989,   973,   997,
     993,    -1,   584,   979,   997,   991,    -1,   584,   988,   973,
     997,   991,    -1,   584,   980,   997,   991,    -1,   584,   989,
     973,   997,   991,    -1,   584,   978,   997,   978,    -1,   584,
     987,   973,   997,   978,    -1,   584,   979,   997,   979,    -1,
     584,   988,   973,   997,   979,    -1,   584,   980,   997,   980,
      -1,   584,   989,   973,   997,   980,    -1,   584,   978,   997,
     987,   973,    -1,   584,   979,   997,   988,   973,    -1,   584,
     980,   997,   989,   973,    -1,   589,    -1,   590,    -1,   591,
      -1,   592,    -1,   593,    -1,   594,   978,   997,   991,    -1,
     594,   987,   973,   997,   991,    -1,   594,   979,   997,   992,
      -1,   594,   988,   973,   997,   992,    -1,   594,   980,   997,
     993,    -1,   594,   989,   973,   997,   993,    -1,   594,   978,
     997,   978,    -1,   594,   987,   973,   997,   978,    -1,   594,
     979,   997,   979,    -1,   594,   988,   973,   997,   979,    -1,
     594,   980,   997,   980,    -1,   594,   989,   973,   997,   980,
      -1,   597,    -1,   602,   979,    -1,   602,   988,   973,    -1,
     603,   979,    -1,   603,   988,   973,    -1,   604,    -1,   605,
      -1,   606,    -1,   607,    -1,   608,   978,   997,   978,    -1,
     608,   987,   973,   997,   978,    -1,   608,   979,   997,   979,
      -1,   608,   988,   973,   997,   979,    -1,   608,   980,   997,
     980,    -1,   608,   989,   973,   997,   980,    -1,   609,   978,
     997,   978,    -1,   609,   987,   973,   997,   978,    -1,   609,
     978,   997,   987,   973,    -1,   609,   979,   997,   979,    -1,
     609,   988,   973,   997,   979,    -1,   609,   979,   997,   988,
     973,    -1,   609,   980,   997,   980,    -1,   609,   989,   973,
     997,   980,    -1,   609,   980,   997,   989,   973,    -1,   610,
      -1,   611,   987,   973,    -1,   612,    -1,   613,   978,   997,
     991,    -1,   613,   987,   973,   997,   991,    -1,   613,   979,
     997,   992,    -1,   613,   988,   973,   997,   992,    -1,   613,
     980,   997,   993,    -1,   613,   989,   973,   997,   993,    -1,
     613,   979,   997,   991,    -1,   613,   988,   973,   997,   991,
      -1,   613,   980,   997,   991,    -1,   613,   989,   973,   997,
     991,    -1,   613,   978,   997,   978,    -1,   613,   987,   973,
     997,   978,    -1,   613,   979,   997,   979,    -1,   613,   988,
     973,   997,   979,    -1,   613,   980,   997,   980,    -1,   613,
     989,   973,   997,   980,    -1,   613,   978,   997,   987,   973,
      -1,   613,   979,   997,   988,   973,    -1,   613,   980,   997,
     989,   973,    -1,   616,   990,   973,    -1,   617,    -1,   618,
      -1,   715,    -1,   984,   974,   724,    -1,   974,   724,    -1,
     715,    -1,   995,    -1,   983,    -1,   983,   986,   994,    -1,
     983,   986,   995,    -1,   985,   983,    -1,   985,   983,   986,
     995,    -1,   985,   983,   713,   983,    -1,   985,   983,   713,
     983,   986,   994,    -1,   985,   983,   713,   983,   986,   995,
      -1,     3,    -1,   976,    -1,   977,    -1,   721,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,   631,
      -1,   632,    -1,   633,    -1,   634,    -1,   635,    -1,   636,
      -1,   637,    -1,   638,    -1,   639,    -1,   640,    -1,   641,
      -1,   642,    -1,   643,    -1,   644,    -1,   645,    -1,   646,
      -1,   647,    -1,   648,    -1,   649,    -1,   650,    -1,   651,
      -1,   652,    -1,   653,    -1,   654,    -1,   655,    -1,   656,
      -1,   657,    -1,   658,    -1,   659,    -1,   660,    -1,   661,
      -1,   662,    -1,   663,    -1,   664,    -1,   665,    -1,   666,
      -1,   667,    -1,   668,    -1,   669,    -1,   670,    -1,   647,
      -1,   648,    -1,   649,    -1,   650,    -1,   651,    -1,   652,
      -1,   653,    -1,   654,    -1,   695,    -1,   696,    -1,   697,
      -1,   698,    -1,   699,    -1,   700,    -1,   709,    -1,   710,
      -1,   711,    -1,   712,    -1,   713,    -1,   714,    -1,   704,
      -1,   705,    -1,   706,    -1,   707,    -1,   718,    -1,   719,
      -1,   720,    -1,   716,    -1,   717,    -1,   722,    -1,   723,
      -1,   725,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   709,   709,   710,   713,   716,   717,   718,   719,   720,
     733,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   750,   751,   752,
     753,   754,   755,   756,   757,   758,   759,   760,   761,   762,
     763,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   804,   805,   806,   807,   808,   809,   810,   811,   812,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
     843,   844,   845,   846,   847,   848,   849,   850,   851,   852,
     853,   854,   855,   856,   857,   858,   859,   860,   861,   862,
     863,   864,   865,   866,   867,   868,   869,   870,   871,   872,
     873,   874,   875,   876,   877,   878,   879,   880,   881,   882,
     883,   884,   885,   886,   887,   888,   889,   890,   891,   892,
     893,   894,   895,   896,   897,   898,   899,   900,   901,   902,
     903,   904,   905,   906,   907,   910,   913,   916,   919,   925,
     929,   935,   939,   945,   951,   963,   968,   981,   987,   999,
    1004,  1010,  1015,  1020,  1025,  1033,  1038,  1047,  1053,  1061,
    1066,  1071,  1077,  1084,  1096,  1101,  1114,  1120,  1132,  1137,
    1143,  1148,  1153,  1158,  1166,  1171,  1180,  1186,  1194,  1199,
    1204,  1210,  1217,  1229,  1234,  1247,  1253,  1265,  1270,  1276,
    1281,  1286,  1291,  1299,  1304,  1313,  1319,  1327,  1332,  1337,
    1343,  1350,  1358,  1365,  1371,  1378,  1387,  1393,  1401,  1408,
    1417,  1423,  1431,  1438,  1444,  1453,  1461,  1467,  1472,  1481,
    1489,  1495,  1502,  1511,  1519,  1525,  1530,  1539,  1547,  1553,
    1560,  1569,  1577,  1583,  1588,  1597,  1605,  1611,  1618,  1627,
    1635,  1641,  1646,  1655,  1663,  1669,  1676,  1680,  1685,  1689,
    1698,  1706,  1712,  1719,  1726,  1732,  1738,  1744,  1751,  1757,
    1763,  1769,  1770,  1771,  1772,  1773,  1774,  1775,  1776,  1777,
    1778,  1779,  1780,  1781,  1782,  1783,  1784,  1785,  1786,  1787,
    1788,  1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,
    1798,  1801,  1810,  1816,  1824,  1831,  1840,  1846,  1854,  1861,
    1870,  1876,  1884,  1891,  1900,  1906,  1914,  1921,  1930,  1936,
    1944,  1951,  1960,  1966,  1974,  1981,  1990,  1996,  2004,  2011,
    2020,  2026,  2034,  2041,  2050,  2056,  2064,  2071,  2080,  2086,
    2094,  2101,  2110,  2116,  2124,  2131,  2140,  2146,  2154,  2161,
    2170,  2176,  2184,  2191,  2200,  2206,  2214,  2221,  2230,  2236,
    2244,  2251,  2260,  2266,  2274,  2281,  2290,  2296,  2304,  2311,
    2320,  2326,  2334,  2341,  2350,  2356,  2364,  2371,  2380,  2386,
    2394,  2401,  2410,  2416,  2424,  2431,  2440,  2446,  2454,  2461,
    2470,  2476,  2484,  2491,  2500,  2506,  2514,  2521,  2530,  2536,
    2544,  2551,  2560,  2566,  2574,  2581,  2590,  2596,  2604,  2611,
    2620,  2626,  2634,  2642,  2651,  2657,  2665,  2672,  2681,  2687,
    2695,  2702,  2714,  2719,  2732,  2738,  2750,  2755,  2761,  2766,
    2771,  2776,  2784,  2789,  2798,  2804,  2812,  2817,  2822,  2828,
    2835,  2841,  2847,  2853,  2861,  2866,  2875,  2883,  2889,  2896,
    2903,  2909,  2917,  2922,  2931,  2937,  2945,  2952,  2959,  2965,
    2971,  2977,  2985,  2993,  2999,  3005,  3010,  3017,  3024,  3029,
    3037,  3043,  3050,  3057,  3063,  3069,  3076,  3081,  3089,  3095,
    3102,  3109,  3116,  3122,  3130,  3136,  3143,  3148,  3157,  3162,
    3170,  3174,  3183,  3188,  3196,  3201,  3210,  3215,  3223,  3229,
    3235,  3242,  3248,  3255,  3263,  3272,  3280,  3288,  3294,  3300,
    3305,  3312,  3319,  3327,  3336,  3342,  3349,  3355,  3361,  3367,
    3373,  3379,  3386,  3391,  3397,  3402,  3407,  3412,  3416,  3420,
    3424,  3428,  3432,  3436,  3440,  3444,  3448,  3452,  3456,  3460,
    3464,  3468,  3472,  3476,  3480,  3484,  3488,  3492,  3496,  3500,
    3504,  3508,  3512,  3516,  3520,  3524,  3528,  3535,  3539,  3543,
    3548,  3552,  3561,  3569,  3575,  3582,  3588,  3597,  3603,  3611,
    3618,  3624,  3631,  3637,  3644,  3650,  3657,  3663,  3670,  3676,
    3683,  3689,  3696,  3702,  3709,  3715,  3722,  3728,  3735,  3743,
    3750,  3758,  3765,  3771,  3778,  3784,  3791,  3798,  3805,  3814,
    3820,  3829,  3836,  3843,  3850,  3857,  3863,  3868,  3873,  3879,
    3885,  3890,  3895,  3903,  3908,  3917,  3923,  3931,  3936,  3941,
    3947,  3952,  3960,  3966,  3974,  3980,  3988,  3996,  4004,  4014,
    4020,  4026,  4031,  4038,  4044,  4051,  4057,  4066,  4072,  4080,
    4085,  4093,  4100,  4109,  4115,  4123,  4128,  4136,  4143,  4151,
    4156,  4165,  4171,  4179,  4186,  4192,  4200,  4205,  4214,  4220,
    4228,  4235,  4239,  4248,  4254,  4262,  4269,  4277,  4282,  4291,
    4297,  4305,  4312,  4324,  4329,  4342,  4348,  4360,  4365,  4371,
    4376,  4381,  4386,  4394,  4399,  4408,  4414,  4422,  4427,  4432,
    4438,  4446,  4452,  4459,  4465,  4472,  4480,  4489,  4496,  4504,
    4513,  4519,  4526,  4533,  4539,  4545,  4551,  4556,  4561,  4567,
    4573,  4579,  4585,  4593,  4600,  4606,  4615,  4621,  4629,  4636,
    4643,  4649,  4656,  4663,  4670,  4677,  4683,  4689,  4694,  4699,
    4703,  4708,  4712,  4718,  4724,  4730,  4736,  4742,  4750,  4757,
    4763,  4770,  4776,  4784,  4793,  4801,  4806,  4812,  4817,  4827,
    4838,  4848,  4855,  4863,  4872,  4880,  4889,  4897,  4902,  4908,
    4913,  4923,  4934,  4944,  4951,  4959,  4968,  4976,  4985,  4993,
    4998,  5004,  5009,  5019,  5030,  5040,  5047,  5055,  5064,  5072,
    5081,  5089,  5094,  5100,  5105,  5115,  5126,  5136,  5143,  5151,
    5160,  5166,  5172,  5178,  5184,  5190,  5196,  5202,  5208,  5216,
    5225,  5233,  5238,  5244,  5249,  5259,  5270,  5280,  5287,  5295,
    5304,  5312,  5321,  5329,  5334,  5340,  5345,  5355,  5366,  5376,
    5383,  5391,  5400,  5408,  5417,  5425,  5430,  5436,  5441,  5451,
    5462,  5472,  5479,  5487,  5496,  5504,  5513,  5521,  5526,  5532,
    5537,  5547,  5558,  5568,  5575,  5583,  5592,  5604,  5609,  5622,
    5628,  5640,  5645,  5651,  5656,  5661,  5666,  5674,  5679,  5688,
    5694,  5702,  5707,  5712,  5718,  5725,  5731,  5738,  5744,  5745,
    5746,  5747,  5748,  5749,  5750,  5751,  5752,  5753,  5754,  5755,
    5756,  5757,  5758,  5759,  5760,  5761,  5762,  5763,  5764,  5765,
    5766,  5767,  5768,  5769,  5770,  5771,  5772,  5773,  5777,  5784,
    5790,  5797,  5803,  5810,  5816,  5823,  5829,  5836,  5842,  5849,
    5855,  5862,  5868,  5875,  5881,  5888,  5894,  5901,  5907,  5914,
    5920,  5927,  5933,  5940,  5946,  5953,  5959,  5966,  5972,  5979,
    5985,  5992,  5998,  6005,  6011,  6018,  6024,  6031,  6037,  6044,
    6050,  6057,  6063,  6070,  6076,  6083,  6089,  6096,  6102,  6109,
    6115,  6122,  6128,  6135,  6141,  6148,  6154,  6161,  6167,  6174,
    6181,  6190,  6196,  6207,  6215,  6223,  6228,  6238,  6247,  6256,
    6262,  6273,  6281,  6289,  6294,  6304,  6313,  6320,  6325,  6335,
    6344,  6349,  6359,  6365,  6371,  6377,  6384,  6390,  6397,  6403,
    6411,  6418,  6430,  6435,  6448,  6454,  6466,  6471,  6477,  6482,
    6487,  6492,  6500,  6505,  6514,  6520,  6528,  6533,  6538,  6544,
    6551,  6558,  6564,  6570,  6576,  6582,  6594,  6599,  6612,  6618,
    6630,  6635,  6643,  6648,  6657,  6663,  6671,  6678,  6684,  6692,
    6699,  6707,  6714,  6720,  6726,  6732,  6738,  6746,  6751,  6760,
    6766,  6774,  6781,  6789,  6794,  6799,  6820,  6826,  6832,  6852,
    6857,  6864,  6870,  6876,  6882,  6894,  6899,  6912,  6918,  6930,
    6935,  6941,  6946,  6951,  6956,  6964,  6969,  6978,  6984,  6992,
    6997,  7002,  7008,  7015,  7022,  7029,  7035,  7048,  7054,  7063,
    7075,  7080,  7094,  7113,  7132,  7151,  7171,  7203,  7224,  7247,
    7254,  7271,  7288,  7295,  7296,  7297,  7300,  7301,  7304,  7310,
    7316,  7322,  7328,  7334,  7340,  7346,  7354,  7360,  7366,  7372,
    7378,  7384,  7390,  7396,  7404,  7410,  7416,  7422,  7428,  7434,
    7440,  7446,  7454,  7460,  7466,  7472,  7478,  7484,  7490,  7496,
    7504,  7510,  7516,  7522,  7528,  7534,  7540,  7546,  7704,  7705,
    7706,  7707,  7708,  7709,  7710,  7711,  7714,  7715,  7716,  7717,
    7718,  7719,  7722,  7723,  7724,  7725,  7728,  7729,  7732,  7735,
    7738,  7741,  7747,  7756,  7765,  7774,  7784,  7794,  7796,  7798
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOCK", "REP", "REPE", "REPZ", "REPNE",
  "REPNZ", "AAA", "AAD", "AAM", "AAS", "ADC", "ADD", "ADDPD", "ADDPS",
  "ADDSD", "ADDSS", "ADDSUBPD", "ADDSUBPS", "AESDEC", "AESDECLAST",
  "AESENC", "AESENCLAST", "AESIMC", "AESKEYGENASSIST", "AND", "ANDPD",
  "ANDPS", "ANDNPD", "ANDNPS", "ARPL", "BLENDPD", "BLENDPS", "BLENDVPD",
  "BLENDVPS", "BOUND", "BSF", "BSR", "BSWAP", "BT", "BTC", "BTR", "BTS",
  "CALL", "CBW", "CWDE", "CDQE", "CLC", "CLD", "CLFLUSH", "CLI", "CLTS",
  "CMC", "CMOVA", "CMOVAE", "CMOVB", "CMOVBE", "CMOVC", "CMOVE", "CMOVG",
  "CMOVGE", "CMOVL", "CMOVLE", "CMOVNA", "CMOVNAE", "CMOVNB", "CMOVNBE",
  "CMOVNC", "CMOVNE", "CMOVNG", "CMOVNGE", "CMOVNL", "CMOVNLE", "CMOVNO",
  "CMOVNP", "CMOVNS", "CMOVNZ", "CMOVO", "CMOVP", "CMOVPE", "CMOVPO",
  "CMOVS", "CMOVZ", "CMP", "CMPPD", "CMPPS", "CMPSB", "CMPSW", "CMPSD",
  "CMPSQ", "CMPSDx", "CMPSS", "CMPXCHG", "CMPXCHG8B", "COMISD", "COMISS",
  "CPUID", "CRC32", "CVTDQ2PD", "CVTDQ2PS", "CVTPD2DQ", "CVTPD2PI",
  "CVTPD2PS", "CVTPI2PD", "CVTPI2PS", "CVTPS2DQ", "CVTPS2PD", "CVTPS2PI",
  "CVTSD2SI", "CVTSD2SS", "CVTSI2SD", "CVTSI2SS", "CVTSS2SD", "CVTSS2SI",
  "CVTTPD2DQ", "CVTTPD2PI", "CVTTPS2DQ", "CVTTPS2PI", "CVTTSD2SI",
  "CVTTSS2SI", "CWD", "CDQ", "CQO", "DAA", "DAS", "DEC", "DIV", "DIVPD",
  "DIVPS", "DIVSD", "DIVSS", "DPPD", "DPPS", "EMMS", "ENTER", "EXTRACTPS",
  "F2XM1", "FABS", "FADD", "FADDP", "FIADD", "FBLD", "FBSTP", "FCHS",
  "FCLEX", "FNCLEX", "FCMOVB", "FCMOVE", "FCMOVBE", "FCMOVU", "FCMOVNB",
  "FCMOVNE", "FCMOVNBE", "FCMOVNU", "FCOMI", "FCOMIP", "FCOS", "FDECSTP",
  "FDIV", "FDIVP", "FIDIV", "FDIVR", "FDIVRP", "FIDIVR", "FFREE", "FICOM",
  "FICOMP", "FILD", "FINCSTP", "FINIT", "FNINIT", "FIST", "FISTP",
  "FISTTP", "FLD", "FLD1", "FLDL2T", "FLDL2E", "FLDPI", "FLDLG2", "FLDLN2",
  "FLDZ", "FLDCW", "FLDENV", "FMUL", "FMULP", "FIMUL", "FNOP", "FPATAN",
  "FPREM", "FPREM1", "FPTAN", "FRNDINT", "FRSTOR", "FSAVE", "FNSAVE",
  "FSCALE", "FSIN", "FSINCOS", "FSQRT", "FST", "FSTP", "FSTCW", "FNSTCW",
  "FSTENV", "FNSTENV", "FSTSW", "FNSTSW", "FSUB", "FSUBP", "FISUB",
  "FSUBR", "FSUBRP", "FISUBR", "FTST", "FUCOM", "FUCOMP", "FUCOMPP",
  "FXAM", "FXCH", "FXRSTOR", "FXSAVE", "FXTRACT", "FYL2X", "FYL2XP1",
  "HADDPD", "HADDPS", "HLT", "HSUBPD", "HSUBPS", "IDIV", "IMUL", "IN",
  "INC", "INS", "INSB", "INSW", "INSD", "INSERTPS", "INT", "INT3", "INTO",
  "INVD", "INVLPG", "IRET", "IRETD", "JA", "JAE", "JB", "JBE", "JC",
  "JCXZ", "JECXZ", "JRCXZ", "JE", "JG", "JGE", "JL", "JLE", "JNA", "JNAE",
  "JNB", "JNBE", "JNC", "JNE", "JNG", "JNGE", "JNL", "JNLE", "JNO", "JNP",
  "JNS", "JNZ", "JO", "JP", "JPE", "JPO", "JS", "JZ", "JMP", "LAHF", "LAR",
  "LDDQU", "LDMXCSR", "LDS", "LES", "LFS", "LGS", "LSS", "LEA", "LEAVE",
  "LFENCE", "LGDT", "LIDT", "LLDT", "LMSW", "LODSB", "LODSW", "LODSD",
  "LODSQ", "LOOP", "LOOPE", "LOOPNE", "LSL", "LTR", "MASKMOVDQU",
  "MASKMOVQ", "MAXPD", "MAXPS", "MAXSD", "MAXSS", "MFENCE", "MINPD",
  "MINPS", "MINSD", "MINSS", "MONITOR", "MOV", "MOVAPD", "MOVAPS", "MOVBE",
  "MOVD", "MOVQ", "MOVDDUP", "MOVDQA", "MOVDQU", "MOVDQ2Q", "MOVHLPS",
  "MOVHPD", "MOVHPS", "MOVLHPS", "MOVLPD", "MOVLPS", "MOVMSKPD",
  "MOVMSKPS", "MOVNTDQA", "MOVNTDQ", "MOVNTI", "MOVNTPD", "MOVNTPS",
  "MOVNTQ", "MOVQx", "MOVQ2DQ", "MOVSB", "MOVSW", "MOVSD", "MOVSQ",
  "MOVSDx", "MOVSHDUP", "MOVSLDUP", "MOVSS", "MOVSX", "MOVSXD", "MOVUPD",
  "MOVUPS", "MOVZX", "MPSADBW", "MUL", "MULPD", "MULPS", "MULSD", "MULSS",
  "MWAIT", "NEG", "NOP", "NOT", "OR", "ORPD", "ORPS", "OUT", "OUTS",
  "OUTSB", "OUTSW", "OUTSD", "PABSB", "PABSW", "PABSD", "PACKSSWB",
  "PACKSSDW", "PACKUSDW", "PACKUSWB", "PADDB", "PADDW", "PADDD", "PADDQ",
  "PADDSB", "PADDSW", "PADDUSB", "PADDUSW", "PALIGNR", "PAND", "PANDN",
  "PAUSE", "PAVGB", "PAVGW", "PBLENDVB", "PBLENDW", "PCLMULQDQ", "PCMPEQB",
  "PCMPEQW", "PCMPEQD", "PCMPEQQ", "PCMPESTRI", "PCMPESTRM", "PCMPGTB",
  "PCMPGTW", "PCMPGTD", "PCMPGTQ", "PCMPISTRI", "PCMPISTRM", "PEXTRB",
  "PEXTRD", "PEXTRQ", "PEXTRW", "PHADDW", "PHADDD", "PHADDSW",
  "PHMINPOSUW", "PHSUBW", "PHSUBD", "PHSUBSW", "PINSRB", "PINSRD",
  "PINSRQ", "PINSRW", "PMADDUBSW", "PMADDWD", "PMAXSB", "PMAXSD", "PMAXSW",
  "PMAXUB", "PMAXUD", "PMAXUW", "PMINSB", "PMINSD", "PMINSW", "PMINUB",
  "PMINUD", "PMINUW", "PMOVMSKB", "PMOVSX", "PMOVZX", "PMULDQ", "PMULHRSW",
  "PMULHUW", "PMULHW", "PMULLD", "PMULLW", "PMULUDQ", "POP", "POPA",
  "POPAD", "POPCNT", "POPF", "POPFD", "POPFQ", "POR", "PREFETCHT0",
  "PREFETCHT1", "PREFETCHT2", "PREFETCHNTA", "PSADBW", "PSHUFB", "PSHUFD",
  "PSHUFHW", "PSHUFLW", "PSHUFW", "PSIGNB", "PSIGNW", "PSIGND", "PSLLDQ",
  "PSLLW", "PSLLD", "PSLLQ", "PSRAW", "PSRAD", "PSRLDQ", "PSRLW", "PSRLD",
  "PSRLQ", "PSUBB", "PSUBW", "PSUBD", "PSUBQ", "PSUBSB", "PSUBSW",
  "PSUBUSB", "PSUBUSW", "PTEST", "PUNPCKHBW", "PUNPCKHWD", "PUNPCKHDQ",
  "PUNPCKHQDQ", "PUNPCKLBW", "PUNPCKLWD", "PUNPCKLDQ", "PUNPCKLQDQ",
  "PUSH", "PUSHA", "PUSHAD", "PUSHF", "PUSHFD", "PXOR", "RCL", "RCR",
  "ROL", "ROR", "RCPPS", "RCPSS", "RDMSR", "RDPMC", "RDTSC", "RDTSCP",
  "RET", "RETN", "ROUNDPD", "ROUNDPS", "ROUNDSD", "ROUNDSS", "RSM",
  "RSQRTPS", "RSQRTSS", "SAHF", "SAL", "SAR", "SHL", "SHR", "SBB", "SCASB",
  "SCASW", "SCASD", "SETA", "SETAE", "SETB", "SETBE", "SETC", "SETE",
  "SETG", "SETGE", "SETL", "SETLE", "SETNA", "SETNAE", "SETNB", "SETNBE",
  "SETNC", "SETNE", "SETNG", "SETNGE", "SETNL", "SETNLE", "SETNO", "SETNP",
  "SETNS", "SETNZ", "SETO", "SETP", "SETPE", "SETPO", "SETS", "SETZ",
  "SFENCE", "SGDT", "SHLD", "SHRD", "SHUFPD", "SHUFPS", "SIDT", "SLDT",
  "SMSW", "SQRTPS", "SQRTSD", "SQRTSS", "STC", "STD", "STI", "STMXCSR",
  "STOSB", "STOSW", "STOSD", "STOSQ", "STR", "SUB", "SUBPD", "SUBPS",
  "SUBSD", "SUBSS", "SWAPGS", "SYSCALL", "SYSENTER", "SYSEXIT", "SYSRET",
  "TEST", "UCOMISD", "UCOMISS", "UD2", "UNPCKHPD", "UNPCKHPS", "UNPCKLPD",
  "UNPCKLPS", "VERR", "VERW", "WAIT", "FWAIT", "WBINVD", "WRMSR", "XADD",
  "XCHG", "XGETBV", "XLAT", "XLATB", "XOR", "XORPD", "XORPS", "XRSTOR",
  "XSAVE", "XSETBV", "INVEPT", "INVVPID", "VMCALL", "VMCLEAR", "VMLAUNCH",
  "VMPTRLD", "VMPTRST", "VMREAD", "VMRESUME", "VMWRITE", "VMXOFF", "VMXON",
  "R_AL", "R_CL", "R_DL", "R_BL", "R_AH", "R_CH", "R_DH", "R_BH", "R_AX",
  "R_CX", "R_DX", "R_BX", "R_SP", "R_BP", "R_SI", "R_DI", "R_EAX", "R_ECX",
  "R_EDX", "R_EBX", "R_ESP", "R_EBP", "R_ESI", "R_EDI", "R_CR0", "R_CR1",
  "R_CR2", "R_CR3", "R_CR4", "R_CR5", "R_CR6", "R_CR7", "R_DR0", "R_DR1",
  "R_DR2", "R_DR3", "R_DR4", "R_DR5", "R_DR6", "R_DR7", "R_MM0", "R_MM1",
  "R_MM2", "R_MM3", "R_MM4", "R_MM5", "R_MM6", "R_MM7", "R_ST0", "R_ST1",
  "R_ST2", "R_ST3", "R_ST4", "R_ST5", "R_ST6", "R_ST7", "R_XMM0", "R_XMM1",
  "R_XMM2", "R_XMM3", "R_XMM4", "R_XMM5", "R_XMM6", "R_XMM7", "SEG_ES",
  "SEG_CS", "SEG_SS", "SEG_DS", "SEG_FS", "SEG_GS", "OP_REG", "OP_MEM",
  "OP_IMM", "BYTE_PTR", "WORD_PTR", "DWORD_PTR", "QWORD_PTR", "TWORD_PTR",
  "SCALE_1", "SCALE_2", "SCALE_4", "SCALE_8", "PLUSSIGN", "SUBSIGN",
  "ADDR_LAB", "DISPLACEMENT8", "DISPLACEMENT32", "IMMEDIATE8",
  "IMMEDIATE16", "IMMEDIATE32", "LINESTART", "COLON", "COMMA", "MEMEND",
  "LINEND", "ERROR", "END", "NONE", "$accept", "asm_line",
  "instruction_line", "instruction", "x86_instruction", "fpu_instruction",
  "simd_instruction", "vm_instruction", "aaa_instruction",
  "aad_instruction", "aam_instruction", "aas_instruction",
  "adc_instruction", "add_instruction", "and_instruction",
  "arpl_instruction", "bound_instruction", "bsf_instruction",
  "bsr_instruction", "bswap_instruction", "bt_instruction",
  "btc_instruction", "btr_instruction", "bts_instruction",
  "call_instruction", "cbw_instruction", "cwde_instruction",
  "clc_instruction", "cld_instruction", "clflush_instruction",
  "cli_instruction", "clts_instruction", "cmc_instruction",
  "cmovcc_instruction", "cmova_instruction", "cmovae_instruction",
  "cmovb_instruction", "cmovbe_instruction", "cmovc_instruction",
  "cmove_instruction", "cmovg_instruction", "cmovge_instruction",
  "cmovl_instruction", "cmovle_instruction", "cmovna_instruction",
  "cmovnae_instruction", "cmovnb_instruction", "cmovnbe_instruction",
  "cmovnc_instruction", "cmovne_instruction", "cmovng_instruction",
  "cmovnge_instruction", "cmovnl_instruction", "cmovnle_instruction",
  "cmovno_instruction", "cmovnp_instruction", "cmovns_instruction",
  "cmovnz_instruction", "cmovo_instruction", "cmovp_instruction",
  "cmovpe_instruction", "cmovpo_instruction", "cmovs_instruction",
  "cmovz_instruction", "cmp_instruction", "cmpsb_instruction",
  "cmpsw_instruction", "cmpsd_instruction", "cmpxchg_instruction",
  "cmpxchg8b_instruction", "cpuid_instruction", "crc32_instruction",
  "cwd_instruction", "cdq_instruction", "daa_instruction",
  "das_instruction", "dec_instruction", "div_instruction",
  "enter_instruction", "hlt_instruction", "idiv_instruction",
  "imul_instruction", "in_instruction", "inc_instruction",
  "ins_instruction", "insb_instruction", "insw_instruction",
  "insd_instruction", "int3_instruction", "into_instruction",
  "int_instruction", "invd_instruction", "invlpg_instruction",
  "iret_instruction", "jcc_instruction", "jmp_instruction",
  "lahf_instruction", "lar_instruction", "lds_instruction",
  "lss_instruction", "les_instruction", "lfs_instruction",
  "lgs_instruction", "lea_instruction", "leave_instruction",
  "lfence_instruction", "lgdt_instruction", "lidt_instruction",
  "lldt_instruction", "lmsw_instruction", "lodsb_instruction",
  "lodsw_instruction", "lodsd_instruction", "loop_instruction",
  "loope_instruction", "loopne_instruction", "lsl_instruction",
  "ltr_instruction", "mfence_instruction", "monitor_instruction",
  "mov_instruction", "movbe_instruction", "movsb_instruction",
  "movsw_instruction", "movsd_instruction", "movsx_instruction",
  "movzx_instruction", "mul_instruction", "mwait_instruction",
  "neg_instruction", "nop_instruction", "not_instruction",
  "or_instruction", "out_instruction", "outs_instruction",
  "outsb_instruction", "outsw_instruction", "outsd_instruction",
  "pause_instruction", "pop_instruction", "popa_instruction",
  "popad_instruction", "popcnt_instruction", "popf_instruction",
  "popfd_instruction", "prefetcht0_instruction", "prefetcht1_instruction",
  "prefetcht2_instruction", "prefetchnta_instruction", "push_instruction",
  "pusha_instruction", "pushad_instruction", "pushf_instruction",
  "pushfd_instruction", "rcl_instruction", "rcr_instruction",
  "rol_instruction", "ror_instruction", "rdmsr_instruction",
  "rdpmc_instruction", "rdtsc_instruction", "rdtscp_instruction",
  "ret_instruction", "retn_instruction", "rsm_instruction",
  "sahf_instruction", "sal_instruction", "sar_instruction",
  "shl_instruction", "shr_instruction", "sbb_instruction",
  "scasb_instruction", "scasw_instruction", "scasd_instruction",
  "setcc_instruction", "seta_instruction", "setae_instruction",
  "setb_instruction", "setbe_instruction", "setc_instruction",
  "sete_instruction", "setg_instruction", "setge_instruction",
  "setl_instruction", "setle_instruction", "setna_instruction",
  "setnae_instruction", "setnb_instruction", "setnbe_instruction",
  "setnc_instruction", "setne_instruction", "setng_instruction",
  "setnge_instruction", "setnl_instruction", "setnle_instruction",
  "setno_instruction", "setnp_instruction", "setns_instruction",
  "setnz_instruction", "seto_instruction", "setp_instruction",
  "setpe_instruction", "setpo_instruction", "sets_instruction",
  "setz_instruction", "sfence_instruction", "sgdt_instruction",
  "shld_instruction", "shrd_instruction", "sidt_instruction",
  "sldt_instruction", "smsw_instruction", "stc_instruction",
  "std_instruction", "sti_instruction", "stmxcsr_instruction",
  "stosb_instruction", "stosw_instruction", "stosd_instruction",
  "str_instruction", "sub_instruction", "swapgs_instruction",
  "syscall_instruction", "sysenter_instruction", "sysexit_instruction",
  "sysret_instruction", "test_instruction", "ud2_instruction",
  "verr_instruction", "verw_instruction", "wait_instruction",
  "fwait_instruction", "wbinvd_instruction", "wrmsr_instruction",
  "xadd_instruction", "xchg_instruction", "xgetbv_instruction",
  "xlat_instruction", "xlatb_instruction", "xor_instruction",
  "xrstor_instruction", "xsave_instruction", "xsetbv_instruction", "label",
  "mem", "mem_no_seg", "prefix", "repz_prefix", "repnz_prefix",
  "register_8bits", "register_16bits", "register_32bits", "register_ctl",
  "register_dbg", "register_32bits_mem", "register_seg", "scale", "sign",
  "ptr_8bits", "ptr_16bits", "ptr_32bits", "ptr_64bits", "immediate_8bits",
  "immediate_16bits", "immediate_32bits", "displacement_8bits",
  "displacement_32bits", "cn", "ca", "linend", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   708,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   750,   751,   752,   753,   754,
     755,   756,   757,   758,   759,   760,   761,   762,   763,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     775,   776,   777,   778,   779,   780,   781,   782,   783,   784,
     785,   786,   787,   788,   789,   790,   791,   792,   793,   794,
     795,   796,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,   807,   808,   809,   810,   811,   812,   813,   814,
     815,   816,   817,   818,   819,   820,   821,   822,   823,   824,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   850,   851,   852,   853,   854,
     855,   856,   857,   858,   859,   860,   861,   862,   863,   864,
     865,   866,   867,   868,   869,   870,   871,   872,   873,   874,
     875,   876,   877,   878,   879,   880,   881,   882,   883,   884,
     885,   886,   887,   888,   889,   890,   891,   892,   893,   894,
     895,   896,   897,   898,   899,   900,   901,   902,   903,   904,
     905,   906,   907,   908,   909,   910,   911,   912,   913,   914,
     915,   916,   917,   918,   919,   920,   921,   922,   923,   924,
     925,   926,   927,   928,   929,   930,   931,   932,   933,   934,
     935,   936,   937,   938,   939,   940,   941,   942,   943,   944,
     945,   946,   947,   948,   949,   950,   951,   952,   953,   954,
     955,   956,   957,   958,   959,   960,   961,   962,   963,   964,
     965,   966,   967,   968,   969,   970,   971,   972,   973,   974,
     975,   976,   977,   978,   979,   980,   981,   982,   983
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   729,   730,   730,   731,   732,   732,   732,   732,   732,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   733,   733,   733,   733,   733,
     733,   733,   733,   733,   733,   734,   735,   736,   737,   738,
     738,   739,   739,   740,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   741,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   742,   742,   742,   742,   742,   742,   742,   742,
     742,   742,   743,   743,   743,   743,   743,   743,   743,   743,
     743,   743,   743,   743,   743,   743,   743,   743,   743,   743,
     743,   744,   744,   745,   745,   746,   746,   746,   746,   747,
     747,   747,   747,   748,   749,   749,   749,   749,   749,   749,
     749,   749,   750,   750,   750,   750,   750,   750,   750,   750,
     751,   751,   751,   751,   751,   751,   751,   751,   752,   752,
     752,   752,   752,   752,   752,   752,   753,   753,   753,   753,
     753,   753,   753,   754,   755,   756,   757,   758,   759,   760,
     761,   762,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   762,   762,   762,   762,   762,   762,   762,   762,   762,
     762,   763,   763,   763,   763,   764,   764,   764,   764,   765,
     765,   765,   765,   766,   766,   766,   766,   767,   767,   767,
     767,   768,   768,   768,   768,   769,   769,   769,   769,   770,
     770,   770,   770,   771,   771,   771,   771,   772,   772,   772,
     772,   773,   773,   773,   773,   774,   774,   774,   774,   775,
     775,   775,   775,   776,   776,   776,   776,   777,   777,   777,
     777,   778,   778,   778,   778,   779,   779,   779,   779,   780,
     780,   780,   780,   781,   781,   781,   781,   782,   782,   782,
     782,   783,   783,   783,   783,   784,   784,   784,   784,   785,
     785,   785,   785,   786,   786,   786,   786,   787,   787,   787,
     787,   788,   788,   788,   788,   789,   789,   789,   789,   790,
     790,   790,   790,   791,   791,   791,   791,   792,   792,   792,
     792,   793,   793,   793,   793,   793,   793,   793,   793,   793,
     793,   793,   793,   793,   793,   793,   793,   793,   793,   793,
     794,   795,   796,   797,   797,   797,   797,   797,   797,   798,
     799,   800,   800,   800,   800,   800,   800,   801,   802,   803,
     804,   805,   805,   805,   805,   805,   805,   806,   806,   806,
     806,   806,   806,   807,   808,   809,   809,   809,   809,   809,
     809,   810,   810,   810,   810,   810,   810,   810,   810,   810,
     810,   810,   810,   810,   810,   810,   810,   810,   810,   811,
     811,   811,   811,   811,   811,   812,   812,   812,   812,   812,
     812,   813,   813,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   822,   823,   823,   823,   823,   823,   823,
     823,   823,   823,   823,   823,   823,   823,   823,   823,   823,
     823,   823,   823,   823,   823,   823,   823,   823,   823,   823,
     823,   823,   823,   823,   823,   823,   823,   824,   824,   824,
     824,   824,   824,   824,   824,   825,   826,   826,   826,   826,
     827,   827,   828,   828,   829,   829,   830,   830,   831,   831,
     832,   832,   833,   834,   835,   835,   836,   836,   837,   837,
     838,   838,   839,   840,   841,   842,   843,   844,   845,   845,
     845,   845,   846,   846,   847,   848,   849,   849,   849,   849,
     849,   849,   849,   849,   849,   849,   849,   849,   849,   849,
     849,   849,   849,   849,   849,   849,   849,   849,   849,   850,
     850,   850,   850,   851,   852,   853,   854,   854,   854,   854,
     854,   854,   855,   855,   855,   855,   855,   855,   856,   856,
     856,   856,   856,   856,   857,   858,   858,   858,   858,   858,
     858,   859,   859,   859,   859,   859,   860,   860,   860,   860,
     860,   860,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   862,   862,   862,   862,   862,   862,   863,   863,   863,
     864,   865,   866,   867,   868,   868,   868,   868,   868,   868,
     868,   868,   868,   869,   870,   871,   871,   871,   871,   872,
     873,   874,   875,   876,   877,   878,   878,   878,   878,   878,
     878,   878,   878,   878,   878,   878,   878,   878,   879,   880,
     881,   882,   883,   883,   883,   883,   883,   883,   883,   883,
     883,   883,   883,   883,   884,   884,   884,   884,   884,   884,
     884,   884,   884,   884,   884,   884,   885,   885,   885,   885,
     885,   885,   885,   885,   885,   885,   885,   885,   886,   886,
     886,   886,   886,   886,   886,   886,   886,   886,   886,   886,
     887,   888,   889,   890,   891,   892,   893,   894,   895,   895,
     895,   895,   895,   895,   895,   895,   895,   895,   895,   895,
     896,   896,   896,   896,   896,   896,   896,   896,   896,   896,
     896,   896,   897,   897,   897,   897,   897,   897,   897,   897,
     897,   897,   897,   897,   898,   898,   898,   898,   898,   898,
     898,   898,   898,   898,   898,   898,   899,   899,   899,   899,
     899,   899,   899,   899,   899,   899,   899,   899,   899,   899,
     899,   899,   899,   899,   899,   900,   901,   902,   903,   903,
     903,   903,   903,   903,   903,   903,   903,   903,   903,   903,
     903,   903,   903,   903,   903,   903,   903,   903,   903,   903,
     903,   903,   903,   903,   903,   903,   903,   903,   904,   904,
     905,   905,   906,   906,   907,   907,   908,   908,   909,   909,
     910,   910,   911,   911,   912,   912,   913,   913,   914,   914,
     915,   915,   916,   916,   917,   917,   918,   918,   919,   919,
     920,   920,   921,   921,   922,   922,   923,   923,   924,   924,
     925,   925,   926,   926,   927,   927,   928,   928,   929,   929,
     930,   930,   931,   931,   932,   932,   933,   933,   934,   935,
     936,   936,   936,   936,   936,   936,   936,   936,   937,   937,
     937,   937,   937,   937,   937,   937,   938,   939,   939,   940,
     940,   940,   941,   942,   943,   944,   945,   946,   947,   948,
     948,   949,   949,   949,   949,   949,   949,   949,   949,   949,
     949,   949,   949,   949,   949,   949,   949,   949,   949,   949,
     950,   951,   952,   953,   954,   955,   955,   955,   955,   955,
     955,   955,   955,   955,   955,   955,   955,   956,   957,   957,
     958,   958,   959,   960,   961,   962,   963,   963,   963,   963,
     963,   963,   964,   964,   964,   964,   964,   964,   964,   964,
     964,   965,   966,   967,   968,   968,   968,   968,   968,   968,
     968,   968,   968,   968,   968,   968,   968,   968,   968,   968,
     968,   968,   968,   969,   970,   971,   972,   973,   973,   974,
     974,   974,   974,   974,   974,   974,   974,   974,   974,   975,
     975,   975,   975,   976,   976,   976,   977,   977,   978,   978,
     978,   978,   978,   978,   978,   978,   979,   979,   979,   979,
     979,   979,   979,   979,   980,   980,   980,   980,   980,   980,
     980,   980,   981,   981,   981,   981,   981,   981,   981,   981,
     982,   982,   982,   982,   982,   982,   982,   982,   983,   983,
     983,   983,   983,   983,   983,   983,   984,   984,   984,   984,
     984,   984,   985,   985,   985,   985,   986,   986,   987,   988,
     989,   990,   991,   992,   993,   994,   995,   996,   997,   998
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     0,     1,     1,
       2,     1,     2,     1,     4,     5,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     4,     5,
       5,     5,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     5,
       5,     5,     4,     5,     4,     5,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     5,     5,
       5,     4,     5,     5,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     2,     4,     4,     5,     5,     4,     4,
       5,     5,     4,     4,     5,     5,     4,     4,     5,     5,
       4,     4,     5,     5,     4,     4,     5,     5,     4,     4,
       5,     5,     4,     4,     5,     5,     2,     2,     2,     2,
       2,     3,     3,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     5,     5,     5,
       1,     1,     1,     4,     5,     4,     4,     5,     5,     1,
       1,     4,     5,     4,     5,     4,     5,     1,     1,     1,
       1,     2,     3,     2,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     4,     1,     2,     3,     2,     3,     2,
       3,     2,     3,     2,     3,     2,     3,     4,     5,     4,
       5,     6,     7,     6,     7,     6,     7,     6,     7,     4,
       4,     4,     4,     4,     4,     2,     3,     2,     3,     2,
       3,     5,     5,     5,     1,     1,     1,     1,     1,     2,
       1,     3,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     1,     4,     5,     4,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     1,     1,     3,     3,     3,     3,     2,     3,
       2,     3,     1,     1,     1,     2,     2,     2,     4,     5,
       4,     5,     2,     3,     1,     1,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     5,     5,
       5,     4,     5,     4,     5,     4,     4,     4,     4,     5,
       5,     5,     5,     1,     1,     1,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     2,     3,
       2,     3,     2,     3,     1,     2,     3,     2,     3,     2,
       3,     1,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     4,     5,     4,     5,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     5,     5,
       5,     4,     4,     4,     4,     4,     4,     5,     5,     5,
       1,     1,     1,     1,     2,     3,     2,     3,     2,     2,
       2,     2,     2,     1,     1,     4,     5,     4,     5,     1,
       1,     3,     3,     3,     3,     2,     3,     2,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     4,     4,     4,     5,     5,     5,     4,     4,
       4,     5,     5,     5,     4,     4,     4,     5,     5,     5,
       4,     4,     4,     5,     5,     5,     4,     4,     4,     5,
       5,     5,     4,     4,     4,     5,     5,     5,     4,     4,
       4,     5,     5,     5,     4,     4,     4,     5,     5,     5,
       1,     1,     1,     1,     1,     2,     1,     1,     4,     4,
       4,     5,     5,     5,     4,     4,     4,     5,     5,     5,
       4,     4,     4,     5,     5,     5,     4,     4,     4,     5,
       5,     5,     4,     4,     4,     5,     5,     5,     4,     4,
       4,     5,     5,     5,     4,     4,     4,     5,     5,     5,
       4,     4,     4,     5,     5,     5,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     4,     5,
       4,     5,     5,     5,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     1,     3,
       6,     7,     6,     7,     6,     7,     6,     7,     6,     7,
       6,     7,     6,     7,     6,     7,     3,     3,     2,     2,
       3,     2,     1,     1,     1,     3,     1,     1,     1,     2,
       3,     4,     5,     4,     5,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     5,     5,     5,
       1,     1,     1,     1,     1,     4,     5,     4,     5,     4,
       5,     4,     5,     4,     5,     4,     5,     1,     2,     3,
       2,     3,     1,     1,     1,     1,     4,     5,     4,     5,
       4,     5,     4,     5,     5,     4,     5,     5,     4,     5,
       5,     1,     3,     1,     4,     5,     4,     5,     4,     5,
       4,     5,     4,     5,     4,     5,     4,     5,     4,     5,
       5,     5,     5,     3,     1,     1,     1,     3,     2,     1,
       1,     1,     3,     3,     2,     4,     4,     6,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,  1129,  1133,  1134,  1135,  1136,  1137,  1132,     0,     2,
     185,  1130,  1131,     1,     3,   188,   189,   191,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   303,   304,   305,   306,     0,   308,   309,   310,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   480,   481,   482,     0,   489,   490,     0,   497,   498,
     499,   500,     0,     0,     0,   514,     0,     0,     0,     0,
       0,   554,   555,   556,     0,   557,   558,   560,     0,   562,
     563,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   605,     0,     0,     0,     0,
       0,     0,     0,   622,   623,     0,     0,     0,     0,   632,
     633,   634,     0,     0,     0,     0,     0,   644,   645,     0,
       0,   673,   674,   675,     0,     0,     0,   694,     0,   701,
       0,     0,     0,     0,   740,   741,   742,   743,     0,   753,
     754,     0,   759,   760,     0,     0,     0,     0,     0,   778,
     779,   780,   781,     0,     0,     0,     0,   830,   831,   832,
     833,   834,     0,   836,   837,     0,     0,     0,     0,     0,
     905,   906,   907,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   998,     0,     0,     0,     0,     0,     0,
    1022,  1023,  1024,     0,  1026,  1027,  1028,     0,     0,  1050,
    1051,  1052,  1053,  1054,     0,  1067,     0,     0,  1072,  1073,
    1074,  1075,     0,     0,  1091,     0,  1093,     0,     0,  1114,
    1115,     0,     0,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    61,    62,    60,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   908,   909,   910,   911,   912,   913,
     914,   915,   916,   917,   918,   919,   920,   921,   922,   923,
     924,   925,   926,   927,   928,   929,   930,   931,   932,   933,
     934,   935,   936,   937,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,  1202,   190,   192,  1138,  1139,  1140,  1141,  1142,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1198,
    1199,  1200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   263,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1116,  1203,  1204,   296,   299,
     300,     0,     0,   297,   298,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
     503,   505,     0,     0,     0,   507,   509,   511,     0,     0,
       0,     0,   515,   517,   519,     0,     0,     0,   521,   523,
     525,     0,     0,     0,     0,     0,     0,   545,   547,   549,
       0,     0,     0,     0,     0,     0,   559,     0,   567,   568,
     569,   570,   571,   564,   565,   566,   572,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     587,   588,   589,   590,   591,   592,   593,   594,   595,   596,
     573,   597,   601,   602,     0,     0,   598,   599,   600,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   628,     0,   630,
       0,   635,   636,   637,     0,     0,   642,     0,  1162,  1163,
    1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,
    1174,  1175,  1176,  1177,  1186,  1187,  1188,  1189,  1190,  1191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   688,   690,   692,
       0,     0,     0,   695,   697,   699,     0,     0,     0,   702,
     704,     0,     0,   706,   708,   710,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   749,   750,
     748,   751,   752,   744,   746,     0,     0,     0,     0,     0,
       0,     0,     0,   774,   772,   775,   773,   776,   777,   765,
     767,     0,     0,   769,   770,   771,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     835,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   938,     0,   940,     0,   942,     0,   944,     0,   946,
       0,   948,     0,   950,     0,   952,     0,   954,     0,   956,
       0,   958,     0,   960,     0,   962,     0,   964,     0,   966,
       0,   968,     0,   970,     0,   972,     0,   974,     0,   976,
       0,   978,     0,   980,     0,   982,     0,   984,     0,   986,
       0,   988,     0,   990,     0,   992,     0,   994,     0,   996,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1018,     0,  1019,  1021,     0,     0,  1029,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1068,     0,  1070,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1201,     0,  1207,     9,  1209,     4,
    1208,     0,     0,     0,  1178,  1179,  1180,  1181,  1182,  1183,
    1184,  1185,  1192,  1193,  1194,  1195,  1119,  1206,     0,     0,
    1121,     0,     0,  1120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   301,   302,   307,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   502,   504,
     506,   508,   510,   512,     0,   516,   518,   520,     0,     0,
     522,   524,   526,     0,     0,     0,   546,   548,   550,     0,
       0,     0,   561,   603,   604,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   624,
     625,   626,   627,   629,   631,     0,     0,   643,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   689,   691,   693,   696,   698,
     700,   703,   705,   707,   709,   711,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   745,   747,     0,     0,   761,
     762,   763,   764,   766,   768,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   939,
     941,   943,   945,   947,   949,   951,   953,   955,   957,   959,
     961,   963,   965,   967,   969,   971,   973,   975,   977,   979,
     981,   983,   985,   987,   989,   991,   993,   995,   997,   999,
       0,     0,     0,     0,     0,     0,     0,     0,  1016,  1017,
    1020,  1025,  1030,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1069,  1071,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1092,
       0,     0,     0,     0,     0,     0,  1113,   204,     0,   194,
     206,     0,   200,   196,   208,     0,   202,   198,     0,  1118,
    1196,  1197,     0,     0,  1124,     0,     0,   223,     0,   213,
     225,     0,   219,   215,   227,     0,   221,   217,     0,     0,
       0,   242,     0,   232,   244,     0,   238,   234,   246,     0,
     240,   236,     0,     0,     0,   251,     0,     0,     0,   255,
       0,   257,     0,   259,     0,   261,     0,   264,   268,   265,
     269,     0,     0,   272,   276,   273,   277,     0,     0,   280,
     284,   281,   285,     0,     0,   288,   292,   289,   293,     0,
       0,   341,     0,   343,     0,   345,     0,   347,     0,   349,
       0,   351,     0,   353,     0,   355,     0,   357,     0,   359,
       0,   361,     0,   363,     0,   365,     0,   367,     0,   369,
       0,   371,     0,   373,     0,   375,     0,   377,     0,   379,
       0,   381,     0,   383,     0,   385,     0,   387,     0,   389,
       0,   391,     0,   393,     0,   395,     0,   397,     0,   399,
       0,   401,     0,   403,     0,   405,     0,   407,     0,   409,
       0,   411,     0,   413,     0,   415,     0,   417,     0,   419,
       0,   421,     0,   423,     0,   425,     0,   427,     0,   429,
       0,   431,     0,   433,     0,   435,     0,   437,     0,   439,
       0,   441,     0,   443,     0,   445,     0,   447,     0,   449,
       0,   451,     0,   453,     0,   455,     0,   457,     0,   459,
       0,   471,     0,   461,   473,     0,   467,   463,   475,     0,
     469,   465,     0,     0,     0,   483,   485,   486,     0,     0,
       0,   491,   493,   495,     0,     0,     0,   513,   527,     0,
     529,     0,   542,   539,   543,   540,   544,   541,     0,     0,
       0,   606,     0,   608,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   638,     0,   640,
       0,   652,     0,   646,   654,   661,     0,   648,   656,   665,
     667,     0,   650,   666,   668,   663,     0,     0,     0,     0,
       0,     0,     0,     0,   676,     0,   678,   680,     0,     0,
     682,     0,   684,   686,     0,     0,   722,     0,   712,   724,
       0,   718,   714,   726,     0,   720,   716,     0,     0,     0,
     734,   735,   736,   731,   732,   733,     0,     0,     0,   755,
       0,   757,     0,   788,   782,   789,   783,   790,   784,     0,
       0,     0,   800,   794,   801,   795,   802,   796,     0,     0,
       0,   812,   806,   813,   807,   814,   808,     0,     0,     0,
     824,   818,   825,   819,   826,   820,     0,     0,     0,   844,
     838,   845,   839,   846,   840,     0,     0,     0,   856,   850,
     857,   851,   858,   852,     0,     0,     0,   868,   862,   869,
     863,   870,   864,     0,     0,     0,   880,   874,   881,   875,
     882,   876,     0,     0,     0,   896,     0,   886,   898,     0,
     892,   888,   900,     0,   894,   890,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1041,     0,  1031,
    1043,     0,  1037,  1033,  1045,     0,  1039,  1035,     0,     0,
       0,  1061,  1055,  1063,  1057,  1065,  1059,     0,     0,     0,
    1076,  1078,  1080,     0,     0,     0,  1082,     0,  1085,     0,
    1088,     0,     0,     0,     0,  1104,     0,  1094,  1106,     0,
    1100,  1096,  1108,     0,  1102,  1098,     0,     0,     0,   210,
     211,   212,   205,   195,  1205,  1122,  1123,  1117,  1196,     0,
     207,   201,   197,   209,   203,   199,   229,   230,   231,   224,
     214,   226,   220,   216,   228,   222,   218,   248,   249,   250,
     243,   233,   245,   239,   235,   247,   241,   237,   252,   253,
     254,   256,   258,   260,   262,   266,   270,   267,   271,   274,
     278,   275,   279,   282,   286,   283,   287,   290,   294,   291,
     295,   342,   344,   346,   348,   350,   352,   354,   356,   358,
     360,   362,   364,   366,   368,   370,   372,   374,   376,   378,
     380,   382,   384,   386,   388,   390,   392,   394,   396,   398,
     400,   402,   404,   406,   408,   410,   412,   414,   416,   418,
     420,   422,   424,   426,   428,   430,   432,   434,   436,   438,
     440,   442,   444,   446,   448,   450,   452,   454,   456,   458,
     460,   477,   478,   479,   472,   462,   474,   468,   464,   476,
     470,   466,   484,   487,   488,   492,   494,   496,     0,   528,
       0,   530,   551,   552,   553,   607,   609,   610,   611,   614,
     615,   616,   617,   618,   619,   612,   613,   620,   621,   639,
     641,   658,   659,   660,   664,   653,   647,   655,   662,   649,
     657,   651,   669,   671,   670,   672,   677,   679,   681,   683,
     685,   687,   728,   729,   730,   723,   713,   725,   719,   715,
     727,   721,   717,   737,   738,   739,   756,   758,   791,   785,
     792,   786,   793,   787,   803,   797,   804,   798,   805,   799,
     815,   809,   816,   810,   817,   811,   827,   821,   828,   822,
     829,   823,   847,   841,   848,   842,   849,   843,   859,   853,
     860,   854,   861,   855,   871,   865,   872,   866,   873,   867,
     883,   877,   884,   878,   885,   879,   902,   903,   904,   897,
     887,   899,   893,   889,   901,   895,   891,     0,     0,     0,
       0,     0,     0,     0,     0,  1047,  1048,  1049,  1042,  1032,
    1044,  1038,  1034,  1046,  1040,  1036,  1062,  1056,  1064,  1058,
    1066,  1060,  1077,  1079,  1081,  1084,  1087,  1090,  1083,  1086,
    1089,  1110,  1111,  1112,  1105,  1095,  1107,  1101,  1097,  1109,
    1103,  1099,  1126,  1125,   531,   535,     0,   533,   537,     0,
    1002,  1000,  1006,  1004,     0,     0,  1010,  1008,  1014,  1012,
       0,     0,     0,   532,   536,   534,   538,  1003,  1001,  1007,
    1005,  1011,  1009,  1015,  1013,  1127,  1128
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,   453,   454,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   598,  1078,  1079,    10,    11,    12,   552,
     553,   554,   813,   814,  1080,  1081,  1082,  1442,   555,   556,
     557,  1055,   523,   603,   604,  1905,  1083,  1057,  1061,  1059
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1955
static const yytype_int16 yypact[] =
{
      12, -1955, -1955, -1955, -1955, -1955, -1955, -1955,     6, -1955,
    7440, -1955, -1955, -1955, -1955, -1955,  -656,  -656, -1955,   133,
     133,   133,   -43,   408,   408,   408,  -250,   307,   307,   307,
     307,   -95, -1955, -1955, -1955, -1955,  -619, -1955, -1955, -1955,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     133, -1955, -1955, -1955,   133, -1955, -1955,  -250, -1955, -1955,
   -1955, -1955,   133,   133,   -27, -1955,   133,   133,  -527,   133,
    -615, -1955, -1955, -1955,  -656, -1955, -1955, -1955,  -619, -1955,
   -1955,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,
    -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,
    -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,  -623,
    -623,  -623,  -623,  -623,  -111, -1955,   408,   408,   408,   408,
     408,   408,   408, -1955, -1955,  -639,  -639,   -43,   -43, -1955,
   -1955, -1955,  -623,  -623,  -623,   408,   -43, -1955, -1955,    39,
     307, -1955, -1955, -1955,   408,   408,   133, -1955,   133,   307,
     133,   133,  -586,  -515, -1955, -1955, -1955, -1955,   279, -1955,
   -1955,   408, -1955, -1955,  -619,  -619,  -619,  -619,  -346, -1955,
   -1955, -1955, -1955,   133,   133,   133,   133, -1955, -1955, -1955,
   -1955, -1955,  -591, -1955, -1955,   133,   133,   133,   133,   133,
   -1955, -1955, -1955,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242, -1955,  -601,   307,   307,  -601,   -43,   375,
   -1955, -1955, -1955,  -601, -1955, -1955, -1955,   -43,   133, -1955,
   -1955, -1955, -1955, -1955,   133, -1955,   -43,   -43, -1955, -1955,
   -1955, -1955,   133,   133, -1955,  -619, -1955,   133,  -580, -1955,
   -1955,  -568,  -486, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955,  -478,  -478,  -478,   174,   174,   174,  -478,  -478,
    -478,   174,   174,   174,  -478,  -478,  -478,   174,   174,   174,
    -478,   174,  -478,  -478,  -478,  -478,  -478,  -478, -1955,  -478,
    -478,   174,   174,  -478,  -478,   174,   174,  -478,  -478,   174,
     174,  -478,  -478,   174,   174, -1955, -1955, -1955, -1955, -1955,
   -1955,   174,   174, -1955, -1955,   174,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,   174,
     174,   174,  -478,  -478,  -478,   174,   174,   174,  -478, -1955,
   -1955, -1955,   174,   174,   174, -1955, -1955, -1955,   174,   174,
     174,  -478, -1955, -1955, -1955,   174,   174,   174, -1955,  -478,
    -478,   174,   174,   174,  -478,  -478,  -478, -1955, -1955, -1955,
     174,   174,   174,   174,   174,   174, -1955,   174, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955,   174,   174, -1955, -1955, -1955,  -478,
    -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,   174,   174,   174,   174, -1955,   174, -1955,
     174, -1955, -1955, -1955,  -478,  -478, -1955,   174, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
    -478,  -478,  -478,  -478,  -478,  -478,   174,   174,   174,  -478,
    -478,   174,   174,  -478,  -478,  -478,  -478, -1955, -1955, -1955,
     174,   174,   174, -1955, -1955, -1955,   174,   174,   174, -1955,
   -1955,   174,   174, -1955, -1955, -1955,   174,   174,   174,  -478,
    -478,  -478,   174,   174,   174,  -478,  -478,  -478, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955,   174,   174,  -478,  -478,   174,
     174,   174,   174, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955,   174,   174, -1955, -1955, -1955,  -478,  -478,  -478,   174,
     174,   174,  -478,  -478,  -478,   174,   174,   174,  -478,  -478,
    -478,   174,   174,   174,  -478,  -478,  -478,   174,   174,   174,
   -1955,  -478,  -478,  -478,   174,   174,   174,  -478,  -478,  -478,
     174,   174,   174,  -478,  -478,  -478,   174,   174,   174,  -478,
    -478,  -478,   174,   174,   174,  -478,  -478,  -478,   174,   174,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174,   174,  -478,  -478,   174,   174,  -478,  -478,   174,   174,
     174, -1955,   174, -1955, -1955,   174,   174, -1955,   174,  -478,
    -478,  -478,   174,   174,   174,  -478,  -478,  -478,   174,   174,
     174, -1955,   174, -1955,   174,  -478,  -478,  -478,   174,   174,
     174,  -478,  -478,  -478,   174,   174,   174,   174,  -478,  -478,
    -478,   174,   174,   174, -1955,   174, -1955, -1955, -1955, -1955,
   -1955,  -603,  -278,  -200, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,  -478,  -477,
    -592,   228,    63, -1955,  -478,  -478,  -603,  -278,  -200,  -478,
    -478,  -478,  -603,  -278,  -200,  -478,  -478,  -478,   -27,  -478,
    -567,  -601,   -43,   160,   -43,   160,  -408,   146,  -478,  -478,
    -408,   146,  -478,  -478,  -408,   146,  -478,  -478,  -408,   146,
    -478,  -478, -1955, -1955, -1955,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,   -43,   160,   -43,   160,   -43,
     160,   -43,   160,   -43,   160,  -603,  -278,  -200,  -478,  -478,
    -478,   332,   -27,  -250,  -478,  -478,  -478,   133, -1955, -1955,
   -1955, -1955, -1955, -1955,  -656, -1955, -1955, -1955,   -43,   160,
   -1955, -1955, -1955,  -400,  -590,  -472, -1955, -1955, -1955,  -478,
    -478,  -478, -1955, -1955, -1955,   -43,   257,  -567,  -601,  -567,
    -601,  -567,  -601,  -567,  -601,  -567,  -601,  -567,  -601, -1955,
   -1955, -1955, -1955, -1955, -1955,   -43,   257, -1955,  -603,   -69,
     193,  -250,  -250,   -43,  -478,  -478,  -478,  -567,  -601,  -478,
    -478,  -242,   115,  -242,   115, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955,  -603,  -278,  -200,  -478,
    -478,  -478,  -389,  -387,  -615, -1955, -1955,   -43,   160, -1955,
   -1955, -1955, -1955, -1955, -1955,  -625,  -624,  -611,  -478,  -478,
    -478,  -610,  -609,  -608,  -478,  -478,  -478,  -607,  -605,  -588,
    -478,  -478,  -478,  -587,  -585,  -584,  -478,  -478,  -478,  -583,
    -582,  -579,  -478,  -478,  -478,  -578,  -575,  -574,  -478,  -478,
    -478,  -573,  -572,  -571,  -478,  -478,  -478,  -569,  -562,  -560,
    -478,  -478,  -478,  -603,  -278,  -200,  -478,  -478,  -478, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
     -27,  -250,  -478,  -478,   -27,  -250,  -478,  -478, -1955, -1955,
   -1955, -1955, -1955,  -603,  -278,  -200,  -478,  -478,  -478,  -595,
    -141,     4,  -478,  -478,  -478, -1955, -1955,   332,   -27,  -250,
    -478,  -478,  -478,  -242,   -43,   160,  -478,  -478,  -478, -1955,
    -603,  -278,  -200,  -478,  -478,  -478, -1955, -1955,   174, -1955,
   -1955,   174, -1955, -1955, -1955,   174, -1955, -1955,  -595, -1955,
   -1955, -1955,  -614,  -473,  -589,  -258,   -86, -1955,   174, -1955,
   -1955,   174, -1955, -1955, -1955,   174, -1955, -1955,  -595,  -258,
     -86, -1955,   174, -1955, -1955,   174, -1955, -1955, -1955,   174,
   -1955, -1955,  -595,  -258,   -86, -1955,   -27,   174,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955, -1955, -1955,
   -1955,  -408,   146, -1955, -1955, -1955, -1955,  -408,   146, -1955,
   -1955, -1955, -1955,  -408,   146, -1955, -1955, -1955, -1955,  -408,
     146, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955,   174, -1955,   174, -1955,   174, -1955,
     174, -1955,   174, -1955, -1955,   174, -1955, -1955, -1955,   174,
   -1955, -1955,  -595,  -258,   -86, -1955, -1955, -1955,   332,   -27,
    -250, -1955, -1955, -1955,   174,   174,   174, -1955,  -478,   174,
    -478,   174, -1955, -1955, -1955, -1955, -1955, -1955,  -388,  -385,
    -384, -1955,   174, -1955,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174, -1955,   174, -1955,
     174, -1955,   174, -1955, -1955, -1955,   174, -1955, -1955, -1955,
   -1955,   174, -1955, -1955, -1955, -1955,   174,  -595,   -58,     4,
     174,   174,   -27,  -250, -1955,   174, -1955, -1955,   174,   174,
   -1955,   174, -1955, -1955,   174,   174, -1955,   174, -1955, -1955,
     174, -1955, -1955, -1955,   174, -1955, -1955,  -595,  -258,   -86,
   -1955, -1955, -1955, -1955, -1955, -1955,   174,   174,   174, -1955,
     174, -1955,   174, -1955, -1955, -1955, -1955, -1955, -1955,  -559,
    -558,  -557, -1955, -1955, -1955, -1955, -1955, -1955,  -556,  -554,
    -553, -1955, -1955, -1955, -1955, -1955, -1955,  -552,  -551,  -550,
   -1955, -1955, -1955, -1955, -1955, -1955,  -548,  -546,  -545, -1955,
   -1955, -1955, -1955, -1955, -1955,  -544,  -537,  -536, -1955, -1955,
   -1955, -1955, -1955, -1955,  -535,  -534,  -533, -1955, -1955, -1955,
   -1955, -1955, -1955,  -526,  -490,  -475, -1955, -1955, -1955, -1955,
   -1955, -1955,  -469,  -453,  -452, -1955,   174, -1955, -1955,   174,
   -1955, -1955, -1955,   174, -1955, -1955,  -595,  -258,   -86,  -478,
    -478,   -27,  -250,  -478,  -478,   -27,  -250, -1955,   174, -1955,
   -1955,   174, -1955, -1955, -1955,   174, -1955, -1955,  -595,  -258,
     -86, -1955, -1955, -1955, -1955, -1955, -1955,  -595,  -141,     4,
   -1955, -1955, -1955,   332,   -27,  -250, -1955,   174, -1955,   174,
   -1955,   174,   332,   -27,  -250, -1955,   174, -1955, -1955,   174,
   -1955, -1955, -1955,   174, -1955, -1955,  -595,  -258,   -86, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,    63,  -456,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,  -600,  -478,
    -604,  -478, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955,  -446,  -439,  -478,
    -478,  -438,  -407,  -478,  -478, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955,  -592, -1955, -1955, -1955,  -600, -1955, -1955,  -604,
   -1955, -1955, -1955, -1955,  -406,  -405, -1955, -1955, -1955, -1955,
    -403,  -402,  -614, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1955, -1955,   254, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955, -1955,
   -1955, -1955, -1955,  1456,  5582,  -818, -1955, -1955, -1955,   -18,
    2200,  1874,  -986,  -983, -1078,  -158, -1955, -1439,   250,  4853,
    4701, -1955,   -17,   -51,   -88, -1954, -1416, -1955,  3356, -1955
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     524,   815,   558,   564,  1444,  1909,    13,  1753,  1755,     1,
       2,     3,     4,     5,     6,     1,     2,     3,     4,     5,
       6,  1757,  1762,  1764,  1766,  1771,  1906,  1773,   525,   526,
     527,   528,   529,   530,   531,   532,   525,   526,   527,   528,
     529,   530,   531,   532,  1775,  1780,   758,  1782,  1784,  1789,
    1791,  1664,   666,  1793,  1798,   855,   672,  1800,  1802,  1807,
    1809,  1811,   522,  1816,   679,   685,   550,   551,   692,   698,
    1818,   707,  1820,  2098,  2100,  2102,  2104,   716,  2106,  2108,
    2110,  2112,  2114,   757,  2116,   549,  2118,  2120,  2122,   549,
     550,   551,   595,   522,   522,  2124,  2126,  2128,  2130,  2132,
     885,   549,  1904,  1077,   704,   551,  2134,   522,   522,   522,
     522,   522,   705,   522,   522,   522,   597,   756,   522,   596,
     706,  1440,  1441,   522,  1908,  1441,   857,  1054,   596,   596,
     522,   522,   522,   522,   522,   522,   522,   884,   550,   522,
     522,   810,  2136,   522,   522,   522,   522,   522,   827,   522,
     833,   910,   843,   849,  1056,   856,   522,  2138,   522,   522,
     522,   522,   522,  2140,   522,   522,   522,   522,   522,  1666,
     522,   883,   522,   522,   522,   886,   892,   898,   904,  2142,
    2144,   522,   522,   522,   522,   522,  2210,   911,   917,   923,
     929,   935,   522,  2212,  2216,   941,   943,   945,   947,   949,
     951,   953,   955,   957,   959,   961,   963,   965,   967,   969,
     971,   973,   975,   977,   979,   981,   983,   985,   987,   989,
     991,   993,   995,   997,   999,  2218,  2227,  2229,   522,  2231,
    2233,   533,   534,   535,   536,   537,   538,   539,   540,  1058,
    1019,  1662,  1740,   522,  1743,  1060,  1025,  1439,   597,   522,
    1741,  1907,  1744,  2042,  1035,  1041,  2043,  2044,  1742,  1048,
    1745,  1077,    14,  1443,  1699,   522,   522,  1700,  2235,     0,
     561,   567,   522,     0,     0,     0,     0,     0,     0,   522,
     522,     0,     0,     0,     0,     0,   605,     0,     0,     0,
       0,     0,     0,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,     0,
     522,   522,   522,   522,     0,   522,   522,     0,   522,     0,
     669,     0,     0,     0,   675,     0,     0,     0,     0,     0,
       0,     0,   682,   688,     0,     0,   695,   701,     0,   710,
     713,     0,     0,     0,     0,     0,     0,     0,   717,   873,
     874,   875,   876,   877,   878,     0,     0,     0,     0,   550,
     551,   533,   534,   535,   536,   537,   538,   539,   540,     0,
       0,     0,   522,   596,   597,     0,     0,     0,     0,     0,
       0,   533,   534,   535,   536,   537,   538,   539,   540,   525,
     526,   527,   528,   529,   530,   531,   532,   541,   542,   543,
     544,   545,   546,   547,   548,     0,     0,     0,     0,   816,
       0,     0,     0,     0,     0,     0,   830,     0,   836,     0,
     846,   852,     0,     0,     0,     0,     0,   550,     0,     0,
       0,     0,     0,     0,   869,   870,   871,   872,     0,     0,
     522,   596,     0,   889,   895,   901,   907,   541,   542,   543,
     544,   545,   546,   547,   548,   914,   920,   926,   932,   938,
     522,   596,   549,   942,   944,   946,   948,   950,   952,   954,
     956,   958,   960,   962,   964,   966,   968,   970,   972,   974,
     976,   978,   980,   982,   984,   986,   988,   990,   992,   994,
     996,   998,  1000,  2203,     0,     0,     0,     0,   533,   534,
     535,   536,   537,   538,   539,   540,   551,     0,  1022,     0,
       0,     0,     0,     0,  1028,     0,     0,     0,   522,     0,
     597,     0,  1038,  1044,     0,  1047,     0,  1051,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
       0,   541,   542,   543,   544,   545,   546,   547,   548,     0,
     533,   534,   535,   536,   537,   538,   539,   540,   596,     0,
       0,   533,   534,   535,   536,   537,   538,   539,   540,     0,
       0,     0,     0,     0,   550,   551,   533,   534,   535,   536,
     537,   538,   539,   540,   595,     0,     0,   522,   596,   597,
     550,   551,   533,   534,   535,   536,   537,   538,   539,   540,
     595,     0,     0,     0,   596,   597,   804,   805,   806,   807,
     808,   809,   522,     0,   597,     0,   550,   804,   805,   806,
     807,   808,   809,     0,     0,     0,     0,     0,     0,     0,
     596,   541,   542,   543,   544,   545,   546,   547,   548,     0,
       0,   596,   550,     0,     0,     0,     0,     0,     0,     0,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   788,   789,   790,   791,   792,   793,
     794,   795,   796,   797,   798,   799,   800,   801,   802,   803,
    1064,  1065,  1066,  1067,  1068,  1069,  1070,  1071,     0,     0,
       0,     0,     0,     0,   597,     0,     0,     7,     0,     0,
       0,     0,     0,     7,   804,   805,   806,   807,   808,   809,
       0,     0,     0,   549,   550,   551,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,     0,  2222,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,     0,     0,
       0,     0,     0,   541,   542,   543,   544,   545,   546,   547,
     548,     0,     0,     0,     0,     0,  2236,   541,   542,   543,
     544,   545,   546,   547,   548,     0,     0,     0,     0,   549,
     550,  1064,  1065,  1066,  1067,  1068,  1069,  1070,  1071,     0,
    2202,     0,     0,     0,     0,     0,     0,   549,   550,   551,
     541,   542,   543,   544,   545,   546,   547,   548,   788,   789,
     790,   791,   792,   793,   794,   795,   796,   797,   798,   799,
     800,   801,   802,   803,   522,     0,   551,     0,     0,   804,
     805,   806,   807,   808,   809,  1064,  1065,  1066,  1067,  1068,
    1069,  1070,  1071,  1072,  1073,  1074,  1075,     0,     0,  1076,
       0,  1077,     0,     0,     0,     0,     0,     0,     0,   551,
       0,     0,     0,     0,   541,   542,   543,   544,   545,   546,
     547,   548,     0,   597,     0,     0,     0,     0,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,     0,     0,     0,  1072,  1073,  1074,
    1075,     0,     0,  1076,     0,  1077,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   550,   525,   526,   527,   528,   529,   530,   531,
     532,     0,     0,     0,   858,  1437,   859,   860,   861,   862,
       0,     0,     0,     0,   550,   551,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1457,     0,     0,     0,     0,     0,  1471,     0,     0,     0,
       0,  1433,   550,   551,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
       0,     0,     0,     0,     0,     0,  1453,     0,     0,     0,
       0,     0,  1467,  1427,  1429,  1432,  1436,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,     0,     0,     0,     0,     0,  1447,  1449,
    1452,  1456,     0,     0,  1461,  1463,  1466,  1470,     0,     0,
     550,     0,     0,     0,     0,     0,     0,     0,     0,  1488,
    1490,  1695,     0,  1494,  1496,     0,     0,  1500,  1502,  1641,
       0,  1506,  1508,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1667,     0,     0,
       0,     0,     0,     0,     0,  1637,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1702,  1665,     0,     0,     0,  1631,  1633,  1636,
    1640,     0,     0,  1645,     0,     0,     0,     0,     0,  1651,
       0,     0,     0,     0,     0,     0,     0,  1657,     0,     0,
    1736,     0,     0,     0,     0,     0,  1663,     0,  1697,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1732,     0,     0,     0,
    1691,  1693,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1714,  1716,  1720,  1722,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1835,  1726,  1728,
    1731,  1735,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1754,  1756,
    1758,     0,     0,     0,  1763,  1765,  1767,     0,     0,     0,
    1772,  1774,  1776,  1831,     0,     0,  1781,  1783,  1785,     0,
       0,     0,  1790,  1792,  1794,     0,     0,  1857,  1799,  1801,
    1803,  1428,     0,  1866,  1808,  1810,  1812,     0,     0,     0,
    1817,  1819,  1821,     0,     0,  1825,  1827,  1830,  1834,     0,
       0,     0,     0,     0,  1895,     0,  1448,     0,     0,     0,
       0,     0,  1462,  1853,     0,     0,     0,     0,     0,  1864,
       0,     0,     0,     0,     0,     0,     0,     0,  1915,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1891,     0,  1926,     0,     0,  1847,  1849,  1852,  1856,     0,
       0,  1861,  1862,     0,     0,     0,  1937,     0,     0,  1870,
       0,     0,     0,     0,  1912,  1876,     0,     0,     0,     0,
       0,     0,  1885,  1887,  1890,  1894,     0,     0,  1923,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1902,  1903,  1934,     0,     0,     0,     0,     0,  1911,  1914,
       0,     0,     0,     0,     0,  1632,     0,     0,     0,     0,
    1919,  1920,  1922,  1925,     0,     0,     0,  1654,     0,     0,
       0,     0,     0,     0,  1930,  1931,  1933,  1936,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1946,  1948,     0,     0,     0,     0,
    1950,  1952,     0,     0,     0,     0,  1954,  1956,     0,     0,
       0,     0,  1958,  1960,     0,     0,     0,     0,  1692,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1715,  1718,  1721,  1724,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1727,     0,     0,     0,
       0,     0,     0,     0,  1746,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2068,     0,     0,     0,     0,     0,  2031,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   727,   728,   729,   730,
     731,   732,   733,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   747,   748,   749,   750,
     751,     0,  2028,  1826,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   781,   782,
     783,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2071,     0,     0,  2024,  2025,  2027,  2030,     0,     0,
    2032,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1848,     0,     0,     0,     0,     0,     0,
       0,  2092,     0,     0,     0,     0,     0,  2069,     0,     0,
       0,     0,     0,  1877,     0,     0,     0,     0,     0,     0,
    1886,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2089,     0,  2065,
    2066,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2085,
    2086,  2088,  2091,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2099,  2101,  2103,     0,     0,     0,     0,     0,
    2156,  2105,  2107,  2109,     0,     0,     0,     0,     0,     0,
    2111,  2113,  2115,     0,     0,     0,     0,     0,     0,  2117,
    2119,  2121,  2175,     0,     0,     0,     0,     0,  2123,  2125,
    2127,  2181,     0,     0,     0,     0,  2153,  2129,  2131,  2133,
       0,     0,     0,     0,     0,     0,  2135,  2137,  2139,     0,
       0,     0,     0,     0,     0,  2141,  2143,  2145,  2172,     0,
    2201,     0,     0,     0,     0,     0,     0,  2179,  2149,  2150,
    2152,  2155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2168,  2169,  2171,  2174,     0,     0,  2198,     0,     0,  2176,
    2177,     0,     0,     0,     0,  2182,     0,     0,     0,     0,
       0,     0,     0,     0,  2188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2194,  2195,
    2197,  2200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   560,   566,     0,   573,   575,   577,
     578,   580,   584,   588,   592,   600,     0,     0,     0,     0,
       0,     0,     0,     0,   607,   609,   611,   613,   615,   617,
     619,   621,   623,   625,   627,   629,   631,   633,   635,   637,
     639,   641,   643,   645,   647,   649,   651,   653,   655,   657,
     659,   661,   663,   665,   668,     0,     0,     0,   674,     0,
       0,   678,  2208,     0,     0,     0,   681,   687,     0,     0,
     694,   700,     0,   709,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   753,     0,
     760,   762,   764,   766,   768,   770,   772,     0,     0,     0,
       0,  2204,     0,  2207,     0,     0,     0,     0,     0,   785,
       0,     0,     0,   812,   820,     0,     0,     0,   824,   826,
     829,     0,   835,   840,   845,   851,     0,     0,     0,     0,
       0,     0,   864,     0,     0,   868,     0,     0,     0,     0,
       0,     0,   880,     0,     0,     0,     0,   888,   894,   900,
     906,     0,     0,     0,     0,     0,     0,     0,     0,   913,
     919,   925,   931,   937,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1003,
    1007,  2226,     0,  1014,     0,     0,     0,     0,     0,     0,
       0,     0,  1021,     0,     0,     0,     0,     0,  1027,     0,
    2211,  2213,     0,     0,  2217,  2219,  1037,  1043,     0,     0,
       0,  1050,     0,     0,     0,  2224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2223,
       0,     0,  2225,     0,     0,     0,     0,  2228,  2230,     0,
       0,     0,     0,  2232,  2234,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     559,   565,   570,   572,   574,   576,     0,   579,   583,   587,
     591,   599,     0,     0,     0,     0,     0,     0,     0,     0,
     606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
     626,   628,   630,   632,   634,   636,   638,   640,   642,   644,
     646,   648,   650,   652,   654,   656,   658,   660,   662,   664,
     667,     0,     0,     0,   673,     0,     0,     0,     0,     0,
       0,     0,   680,   686,   691,     0,   693,   699,     0,   708,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   752,     0,   759,   761,   763,   765,
     767,   769,   771,     0,     0,     0,     0,   777,   779,     0,
       0,     0,     0,     0,     0,   784,   786,     0,     0,   811,
     819,     0,     0,     0,   823,   825,   828,     0,   834,   839,
     844,   850,     0,     0,     0,     0,     0,     0,   863,     0,
       0,   867,     0,     0,     0,     0,     0,     0,   879,     0,
       0,     0,     0,   887,   893,   899,   905,     0,     0,     0,
       0,     0,     0,     0,     0,   912,   918,   924,   930,   936,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1002,  1006,     0,  1011,  1013,
       0,     0,     0,     0,     0,     0,     0,  1017,  1020,     0,
       0,     0,     0,     0,  1026,     0,  1031,  1033,     0,     0,
       0,     0,  1036,  1042,     0,     0,     0,  1049,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1434,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1454,     0,     0,     0,     0,     0,  1468,     0,
       0,     0,     0,     0,     0,     0,     0,  1481,     0,  1485,
       0,  1489,     0,     0,     0,  1495,     0,     0,     0,  1501,
       0,     0,     0,  1507,     0,     0,     0,     0,     0,     0,
    1513,     0,  1517,     0,  1521,     0,  1525,     0,  1529,     0,
    1533,     0,  1537,     0,  1541,     0,  1545,     0,  1549,     0,
    1553,     0,  1557,     0,  1561,     0,  1565,     0,  1569,     0,
    1573,     0,  1577,     0,  1581,     0,  1585,     0,  1589,     0,
    1593,     0,  1597,     0,  1601,     0,  1605,     0,  1609,     0,
    1613,     0,  1617,     0,  1621,     0,  1625,     0,  1629,     0,
       0,  1638,     0,     0,     0,     0,     0,  1647,     0,     0,
       0,  1653,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1660,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1673,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1689,     0,     0,     0,  1698,  1703,  1704,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1733,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1751,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1832,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1840,     0,     0,     0,  1844,
       0,     0,  1430,     0,     0,     0,     0,     0,     0,  1854,
       0,     0,     0,     0,     0,  1865,     0,     0,     0,     0,
       0,     0,     0,  1872,     0,     0,     0,  1450,     0,  1880,
       0,     0,     0,  1464,     0,     0,  1892,     0,  1475,     0,
       0,     0,  1479,     0,  1483,     0,  1487,     0,     0,     0,
    1493,     0,     0,     0,  1499,     0,     0,     0,  1505,     0,
    1913,     0,     0,     0,     0,  1511,     0,  1515,     0,  1519,
       0,  1523,     0,  1527,  1924,  1531,     0,  1535,     0,  1539,
       0,  1543,     0,  1547,     0,  1551,     0,  1555,  1935,  1559,
       0,  1563,     0,  1567,     0,  1571,     0,  1575,     0,  1579,
       0,  1583,     0,  1587,     0,  1591,  1947,  1595,     0,  1599,
       0,  1603,  1951,  1607,     0,  1611,     0,  1615,  1955,  1619,
       0,  1623,     0,  1627,  1959,     0,  1634,     0,     0,     0,
       0,     0,  1646,     0,     0,     0,     0,  1652,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1658,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1671,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1687,     0,     0,     0,  1694,
       0,     0,     0,  1705,     0,     0,     0,     0,     0,     0,
       0,     0,  1717,     0,  1723,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1729,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1749,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2029,     0,
       0,     0,     0,     0,  2034,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1828,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1839,     0,     0,  2070,  1843,     0,     0,  2075,     0,     0,
       0,     0,     0,     0,  1850,     0,     0,     0,     0,     0,
    1863,     0,     0,     0,     0,     0,     0,     0,  1871,     0,
       0,     0,     0,  2090,  1878,     0,     0,     0,     0,     0,
       0,  1888,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1910,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1921,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1932,     0,     0,  1938,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1945,     0,     0,     0,     0,     0,  1949,     0,     0,
       0,     0,     0,  1953,     0,     0,     0,     0,     0,  1957,
       0,     0,  2154,     0,     0,     0,  2160,     0,     0,     0,
    2164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2173,     0,     0,     0,     0,     0,
       0,     0,     0,  2180,     0,     0,     0,     0,     0,  2184,
       0,     0,     0,     0,     0,     0,     0,     0,  2190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2199,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2026,     0,     0,     0,     0,     0,  2033,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2067,  1062,
    1063,     0,  2074,     0,  1086,  1087,  1088,     0,     0,     0,
    1092,  1093,  1094,     0,     0,     0,  1098,     0,  1100,  1101,
    1102,  1103,  1104,  1105,     0,  1106,  1107,     0,  2087,  1110,
    1111,     0,     0,  1114,  1115,     0,     0,  1118,  1119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
    1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,
    1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,
    1183,  1184,  1185,  1186,  1187,     0,     0,     0,  1191,  1192,
    1193,     0,     0,     0,  1197,     0,     0,  2151,     0,     0,
       0,  2159,     0,     0,     0,  2163,     0,  1204,     0,     0,
       0,     0,     0,     0,     0,  1208,  1209,     0,     0,  2170,
    1213,  1214,  1215,     0,     0,     0,     0,     0,  2178,     0,
       0,     0,     0,     0,  2183,     0,     0,     0,     0,     0,
       0,     0,     0,  2189,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1225,  1226,  1227,  1228,  1229,
    1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1245,  1246,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1248,  1249,  1250,  1251,
    1252,  1253,     0,     0,     0,  1257,  1258,     0,     0,  1261,
    1262,  1263,  1264,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1276,  1277,  1278,     0,     0,
       0,  1282,  1283,  1284,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1287,  1288,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1295,  1296,  1297,     0,     0,     0,  1301,  1302,
    1303,     0,     0,     0,  1307,  1308,  1309,     0,     0,     0,
    1313,  1314,  1315,     0,     0,     0,     0,  1319,  1320,  1321,
       0,     0,     0,  1325,  1326,  1327,     0,     0,     0,  1331,
    1332,  1333,     0,     0,     0,  1337,  1338,  1339,     0,     0,
       0,  1343,  1344,  1345,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1380,  1381,
       0,     0,  1384,  1385,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1393,  1394,  1395,     0,     0,
       0,  1399,  1400,  1401,     0,     0,     0,     0,     0,     0,
       0,  1407,  1408,  1409,     0,     0,     0,  1413,  1414,  1415,
       0,     0,     0,     0,  1420,  1421,  1422,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1438,     0,     0,     0,     0,     0,
    1445,  1446,     0,     0,     0,  1458,  1459,  1460,     0,     0,
       0,  1472,  1473,  1474,     0,  1476,     0,     0,     0,     0,
       0,     0,     0,     0,  1491,  1492,     0,     0,  1497,  1498,
       0,     0,  1503,  1504,     0,     0,  1509,  1510,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1642,  1643,  1644,     0,     0,     0,
    1648,  1649,  1650,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1668,  1669,  1670,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1707,  1708,  1709,     0,     0,  1712,  1713,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1737,  1738,  1739,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1759,  1760,  1761,     0,     0,     0,
    1768,  1769,  1770,     0,     0,     0,  1777,  1778,  1779,     0,
       0,     0,  1786,  1787,  1788,     0,     0,     0,  1795,  1796,
    1797,     0,     0,     0,  1804,  1805,  1806,     0,     0,     0,
    1813,  1814,  1815,     0,     0,     0,  1822,  1823,  1824,     0,
       0,     0,  1836,  1837,  1838,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   563,   569,     0,     0,     0,     0,     0,   582,   586,
     590,   594,   602,     0,     0,     0,     0,     0,  1841,  1842,
       0,     0,  1845,  1846,     0,     0,     0,     0,     0,     0,
       0,     0,  1858,  1859,  1860,     0,     0,     0,  1867,  1868,
    1869,     0,     0,     0,     0,     0,  1873,  1874,  1875,     0,
       0,   671,  1882,  1883,  1884,   677,     0,     0,     0,  1896,
    1897,  1898,     0,   684,   690,     0,     0,   697,   703,     0,
     712,   715,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   755,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   774,   776,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     818,   822,     0,     0,     0,     0,     0,   832,     0,   838,
     842,   848,   854,   562,   568,   571,     0,     0,     0,   866,
     581,   585,   589,   593,   601,     0,     0,     0,     0,   882,
       0,     0,     0,     0,   891,   897,   903,   909,     0,     0,
       0,     0,     0,     0,     0,     0,   916,   922,   928,   934,
     940,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   670,     0,     0,     0,   676,     0,     0,
       0,     0,     0,     0,     0,   683,   689,     0,     0,   696,
     702,     0,   711,   714,     0,  1001,  1005,  1009,  1010,     0,
       0,     0,     0,     0,  1016,     0,     0,     0,     0,  1024,
       0,     0,     0,     0,     0,  1030,     0,     0,     0,     0,
       0,     0,     0,  1040,  1046,     0,     0,     0,  1053,     0,
       0,     0,     0,     0,     0,     0,     0,   754,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   773,   775,
     778,   780,     0,     0,     0,     0,     0,     0,     0,   787,
       0,     0,   817,   821,  2038,     0,  2040,     0,     0,   831,
       0,   837,   841,   847,   853,     0,     0,     0,     0,     0,
       0,   865,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   881,     0,     0,     0,     0,   890,   896,   902,   908,
       0,     0,     0,     0,     0,     0,     0,     0,   915,   921,
     927,   933,   939,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1004,  1008,
       0,  1012,  1015,     0,     0,     0,     0,     0,     0,     0,
    1018,  1023,     0,     0,     0,     0,     0,  1029,     0,  1032,
    1034,     0,     0,     0,     0,  1039,  1045,     0,     0,     0,
    1052,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2157,  2158,     0,     0,  2161,
    2162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2206,     0,  2209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2214,  2215,     0,     0,  2220,
    2221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1435,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1455,
       0,     0,     0,     0,     0,  1469,     0,     0,     0,     0,
       0,     0,  1478,     0,  1482,     0,  1486,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1514,     0,  1518,
       0,  1522,     0,  1526,     0,  1530,     0,  1534,     0,  1538,
       0,  1542,     0,  1546,     0,  1550,     0,  1554,     0,  1558,
       0,  1562,     0,  1566,     0,  1570,     0,  1574,     0,  1578,
       0,  1582,     0,  1586,     0,  1590,     0,  1594,     0,  1598,
       0,  1602,     0,  1606,     0,  1610,     0,  1614,     0,  1618,
       0,  1622,     0,  1626,     0,  1630,     0,     0,  1639,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1656,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1661,     0,     0,     0,     0,  1431,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1676,
       0,  1678,     0,  1680,     0,  1682,     0,  1684,     0,  1686,
    1451,     0,     0,     0,     0,     0,  1465,     0,     0,     0,
       0,  1701,     0,  1477,     0,  1480,     0,  1484,     0,  1711,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1512,  1734,
    1516,     0,  1520,     0,  1524,  1748,  1528,     0,  1532,  1752,
    1536,     0,  1540,     0,  1544,     0,  1548,     0,  1552,     0,
    1556,     0,  1560,     0,  1564,     0,  1568,     0,  1572,     0,
    1576,     0,  1580,     0,  1584,     0,  1588,     0,  1592,     0,
    1596,     0,  1600,     0,  1604,     0,  1608,     0,  1612,     0,
    1616,     0,  1620,     0,  1624,     0,  1628,     0,     0,  1635,
       0,     0,     0,     0,     0,     0,  1833,     0,     0,     0,
    1655,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1659,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1672,  1674,
    1675,     0,  1677,     0,  1679,     0,  1681,     0,  1683,     0,
    1685,     0,     0,     0,     0,     0,  1855,     0,  1688,  1690,
       0,     0,  1696,     0,     0,     0,  1706,     0,     0,     0,
    1710,     0,     0,     0,     0,  1719,  1881,  1725,     0,     0,
       0,     0,     0,  1893,     0,     0,     0,     0,     0,     0,
    1730,     0,     0,     0,     0,     0,     0,  1747,  1084,  1085,
    1750,     0,     0,  1089,  1090,  1091,     0,     0,     0,  1095,
    1096,  1097,     0,  1099,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1108,  1109,     0,     0,  1112,  1113,     0,
       0,  1116,  1117,     0,     0,  1120,  1121,     0,     0,     0,
       0,     0,     0,  1122,  1123,     0,     0,  1124,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1829,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1851,     0,     0,
       0,  1188,  1189,  1190,     0,     0,     0,  1194,  1195,  1196,
       0,     0,     0,     0,  1198,  1199,  1200,  1879,     0,     0,
    1201,  1202,  1203,     0,  1889,     0,     0,  1205,  1206,  1207,
       0,     0,     0,  1210,  1211,  1212,     0,     0,     0,     0,
       0,     0,  1216,  1217,  1218,  1219,  1220,  1221,     0,  1222,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1223,  1224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1239,  1240,  1241,  1242,     0,
    1243,     0,  1244,     0,     0,     0,     0,     0,     0,  1247,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1254,  1255,
    1256,     0,     0,  1259,  1260,     0,     0,     0,     0,     0,
       0,     0,  1265,  1266,  1267,     0,     0,     0,  1268,  1269,
    1270,     0,     0,  1271,  1272,     0,     0,     0,  1273,  1274,
    1275,     0,     0,     0,  1279,  1280,  1281,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1285,  1286,     0,
       0,  1289,  1290,  1291,  1292,     0,     0,     0,     0,     0,
       0,     0,     0,  1293,  1294,     0,     0,     0,     0,     0,
       0,  1298,  1299,  1300,     0,     0,     0,  1304,  1305,  1306,
       0,     0,     0,  1310,  1311,  1312,     0,     0,     0,  1316,
    1317,  1318,     0,     0,     0,     0,  1322,  1323,  1324,     0,
       0,     0,  1328,  1329,  1330,     0,     0,     0,  1334,  1335,
    1336,     0,     0,     0,  1340,  1341,  1342,     0,     0,     0,
    1346,  1347,  1348,     0,  1349,     0,  1350,     0,  1351,     0,
    1352,     0,  1353,     0,  1354,     0,  1355,     0,  1356,     0,
    1357,     0,  1358,     0,  1359,     0,  1360,     0,  1361,     0,
    1362,     0,  1363,     0,  1364,     0,  1365,     0,  1366,     0,
    1367,     0,  1368,     0,  1369,     0,  1370,     0,  1371,     0,
    1372,     0,  1373,     0,  1374,     0,  1375,     0,  1376,     0,
    1377,     0,  1378,  1379,     0,     0,  1382,  1383,     0,     0,
    1386,  1387,  1388,     0,  1389,     0,     0,  1390,  1391,     0,
    1392,     0,     0,     0,  1396,  1397,  1398,     0,     0,     0,
    1402,  1403,  1404,     0,  1405,     0,  1406,     0,     0,     0,
    1410,  1411,  1412,     0,     0,     0,  1416,  1417,  1418,  1419,
       0,     0,     0,  1423,  1424,  1425,     0,  1426,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1899,     0,     0,  1900,     0,     0,     0,  1901,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1916,     0,     0,  1917,     0,     0,     0,  1918,     0,     0,
       0,     0,     0,     0,  1927,     0,     0,  1928,     0,     0,
       0,  1929,     0,     0,     0,     0,     0,     0,     0,  1939,
    1940,     0,  1941,     0,  1942,     0,  1943,     0,  1944,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1961,     0,  1962,     0,  1963,     0,
    1964,     0,  1965,     0,  1966,     0,  1967,     0,  1968,     0,
    1969,     0,  1970,     0,  1971,     0,  1972,     0,  1973,     0,
    1974,     0,  1975,     0,  1976,     0,  1977,     0,  1978,     0,
    1979,     0,  1980,     0,  1981,     0,  1982,     0,  1983,     0,
    1984,     0,  1985,     0,  1986,     0,  1987,     0,  1988,     0,
    1989,     0,  1990,     0,  1991,     0,  1992,     0,  1993,     0,
    1994,     0,  1995,     0,  1996,     0,  1997,     0,  1998,     0,
    1999,     0,  2000,     0,  2001,     0,  2002,     0,  2003,     0,
    2004,     0,  2005,     0,  2006,     0,  2007,     0,  2008,     0,
    2009,     0,  2010,     0,  2011,     0,  2012,     0,  2013,     0,
    2014,     0,  2015,     0,  2016,     0,  2017,     0,  2018,     0,
    2019,     0,  2020,     0,  2021,     0,     0,  2022,     0,     0,
       0,  2023,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2035,  2036,  2037,     0,
       0,  2039,     0,  2041,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2045,     0,  2046,  2047,  2048,  2049,
    2050,  2051,  2052,  2053,  2054,  2055,  2056,  2057,  2058,     0,
    2059,     0,  2060,     0,  2061,     0,     0,     0,  2062,     0,
       0,     0,     0,  2063,     0,     0,     0,     0,  2064,     0,
       0,     0,  2072,  2073,     0,     0,     0,  2076,     0,     0,
    2077,  2078,     0,  2079,     0,     0,  2080,  2081,     0,  2082,
       0,     0,  2083,     0,     0,     0,  2084,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2093,  2094,
    2095,     0,  2096,     0,  2097,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2146,     0,
       0,  2147,     0,     0,     0,  2148,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2165,     0,     0,  2166,     0,     0,     0,  2167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,  2185,
       0,  2186,     0,  2187,     0,     0,     0,    21,  2191,     0,
       0,  2192,    22,     0,     0,  2193,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,     0,     0,    71,    72,
      73,     0,     0,     0,    74,    75,     0,     0,    76,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,    79,     0,    80,    81,    82,    83,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
       0,     0,    86,    87,    88,    89,    90,    91,    92,    93,
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,   157,     0,     0,     0,     0,   158,   159,
       0,     0,   160,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   161,   162,   163,     0,     0,
       0,     0,     0,   164,     0,     0,     0,   165,     0,   166,
       0,     0,     0,     0,   167,   168,   169,   170,   171,     0,
       0,   172,   173,   174,   175,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   179,   180,   181,   182,   183,     0,     0,   184,
     185,   186,   187,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
     189,   190,   191,   192,     0,   193,   194,   195,   196,     0,
       0,   197,   198,   199,   200,   201,   202,     0,     0,     0,
       0,   203,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,     0,     0,   247,
     248,   249,     0,     0,     0,   250,   251,   252,   253,   254,
     255,   256,     0,   257,   258,     0,     0,     0,     0,   259,
     260,   261,   262,   263,   264,     0,     0,   265,     0,     0,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,   278,   279,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   281
};

static const yytype_int16 yycheck[] =
{
      17,   159,    20,    21,  1082,  1444,     0,   632,   632,     3,
       4,     5,     6,     7,     8,     3,     4,     5,     6,     7,
       8,   632,   632,   632,   632,   632,  1442,   632,   631,   632,
     633,   634,   635,   636,   637,   638,   631,   632,   633,   634,
     635,   636,   637,   638,   632,   632,   134,   632,   632,   632,
     632,   641,    70,   632,   632,   641,    74,   632,   632,   632,
     632,   632,   718,   632,    82,    83,   705,   706,    86,    87,
     632,    89,   632,   632,   632,   632,   632,    94,   632,   632,
     632,   632,   632,   134,   632,   704,   632,   632,   632,   704,
     705,   706,   715,   718,   718,   632,   632,   632,   632,   632,
     188,   704,   716,   717,   631,   706,   632,   718,   718,   718,
     718,   718,   639,   718,   718,   718,   720,   134,   718,   719,
     647,   713,   714,   718,   713,   714,   641,   707,   719,   719,
     718,   718,   718,   718,   718,   718,   718,   188,   705,   718,
     718,   159,   632,   718,   718,   718,   718,   718,   166,   718,
     168,   202,   170,   171,   722,   172,   718,   632,   718,   718,
     718,   718,   718,   632,   718,   718,   718,   718,   718,   641,
     718,   188,   718,   718,   718,   193,   194,   195,   196,   632,
     632,   718,   718,   718,   718,   718,   632,   205,   206,   207,
     208,   209,   718,   632,   632,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   632,   632,   632,   718,   632,
     632,   639,   640,   641,   642,   643,   644,   645,   646,   725,
     258,   641,   631,   718,   631,   723,   264,   724,   720,   718,
     639,   724,   639,   641,   272,   273,   641,   641,   647,   277,
     647,   717,     8,  1081,  1250,   718,   718,  1250,  2222,    -1,
      20,    21,   718,    -1,    -1,    -1,    -1,    -1,    -1,   718,
     718,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   652,   653,   654,    -1,
     718,   718,   718,   718,    -1,   718,   718,    -1,   718,    -1,
      70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    83,    -1,    -1,    86,    87,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,   695,
     696,   697,   698,   699,   700,    -1,    -1,    -1,    -1,   705,
     706,   639,   640,   641,   642,   643,   644,   645,   646,    -1,
      -1,    -1,   718,   719,   720,    -1,    -1,    -1,    -1,    -1,
      -1,   639,   640,   641,   642,   643,   644,   645,   646,   631,
     632,   633,   634,   635,   636,   637,   638,   647,   648,   649,
     650,   651,   652,   653,   654,    -1,    -1,    -1,    -1,   159,
      -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,   168,    -1,
     170,   171,    -1,    -1,    -1,    -1,    -1,   705,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,   187,    -1,    -1,
     718,   719,    -1,   193,   194,   195,   196,   647,   648,   649,
     650,   651,   652,   653,   654,   205,   206,   207,   208,   209,
     718,   719,   704,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,  1909,    -1,    -1,    -1,    -1,   639,   640,
     641,   642,   643,   644,   645,   646,   706,    -1,   258,    -1,
      -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,   718,    -1,
     720,    -1,   272,   273,    -1,   275,    -1,   277,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
      -1,   647,   648,   649,   650,   651,   652,   653,   654,    -1,
     639,   640,   641,   642,   643,   644,   645,   646,   719,    -1,
      -1,   639,   640,   641,   642,   643,   644,   645,   646,    -1,
      -1,    -1,    -1,    -1,   705,   706,   639,   640,   641,   642,
     643,   644,   645,   646,   715,    -1,    -1,   718,   719,   720,
     705,   706,   639,   640,   641,   642,   643,   644,   645,   646,
     715,    -1,    -1,    -1,   719,   720,   695,   696,   697,   698,
     699,   700,   718,    -1,   720,    -1,   705,   695,   696,   697,
     698,   699,   700,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     719,   647,   648,   649,   650,   651,   652,   653,   654,    -1,
      -1,   719,   705,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     647,   648,   649,   650,   651,   652,   653,   654,    -1,    -1,
      -1,    -1,    -1,    -1,   720,    -1,    -1,   721,    -1,    -1,
      -1,    -1,    -1,   721,   695,   696,   697,   698,   699,   700,
      -1,    -1,    -1,   704,   705,   706,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   642,   643,   644,
     645,   646,    -1,  2202,   631,   632,   633,   634,   635,   636,
     637,   638,   639,   640,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,    -1,    -1,
      -1,    -1,    -1,   647,   648,   649,   650,   651,   652,   653,
     654,    -1,    -1,    -1,    -1,    -1,  2222,   647,   648,   649,
     650,   651,   652,   653,   654,    -1,    -1,    -1,    -1,   704,
     705,   647,   648,   649,   650,   651,   652,   653,   654,    -1,
    1908,    -1,    -1,    -1,    -1,    -1,    -1,   704,   705,   706,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   718,    -1,   706,    -1,    -1,   695,
     696,   697,   698,   699,   700,   647,   648,   649,   650,   651,
     652,   653,   654,   709,   710,   711,   712,    -1,    -1,   715,
      -1,   717,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   706,
      -1,    -1,    -1,    -1,   647,   648,   649,   650,   651,   652,
     653,   654,    -1,   720,    -1,    -1,    -1,    -1,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,    -1,    -1,    -1,   709,   710,   711,
     712,    -1,    -1,   715,    -1,   717,   639,   640,   641,   642,
     643,   644,   645,   646,   647,   648,   649,   650,   651,   652,
     653,   654,   705,   631,   632,   633,   634,   635,   636,   637,
     638,    -1,    -1,    -1,   695,  1063,   697,   698,   699,   700,
      -1,    -1,    -1,    -1,   705,   706,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1088,    -1,    -1,    -1,    -1,    -1,  1094,    -1,    -1,    -1,
      -1,  1062,   705,   706,   639,   640,   641,   642,   643,   644,
     645,   646,   647,   648,   649,   650,   651,   652,   653,   654,
      -1,    -1,    -1,    -1,    -1,    -1,  1087,    -1,    -1,    -1,
      -1,    -1,  1093,  1061,  1061,  1062,  1063,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,    -1,    -1,    -1,    -1,    -1,  1086,  1086,
    1087,  1088,    -1,    -1,  1092,  1092,  1093,  1094,    -1,    -1,
     705,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1106,
    1107,  1249,    -1,  1110,  1111,    -1,    -1,  1114,  1115,  1187,
      -1,  1118,  1119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1186,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1250,  1214,    -1,    -1,    -1,  1185,  1185,  1186,
    1187,    -1,    -1,  1191,    -1,    -1,    -1,    -1,    -1,  1197,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1204,    -1,    -1,
    1278,    -1,    -1,    -1,    -1,    -1,  1213,    -1,  1249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1277,    -1,    -1,    -1,
    1248,  1248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1261,  1262,  1263,  1264,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1345,  1276,  1276,
    1277,  1278,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1295,  1296,
    1297,    -1,    -1,    -1,  1301,  1302,  1303,    -1,    -1,    -1,
    1307,  1308,  1309,  1344,    -1,    -1,  1313,  1314,  1315,    -1,
      -1,    -1,  1319,  1320,  1321,    -1,    -1,  1395,  1325,  1326,
    1327,  1061,    -1,  1401,  1331,  1332,  1333,    -1,    -1,    -1,
    1337,  1338,  1339,    -1,    -1,  1343,  1343,  1344,  1345,    -1,
      -1,    -1,    -1,    -1,  1422,    -1,  1086,    -1,    -1,    -1,
      -1,    -1,  1092,  1394,    -1,    -1,    -1,    -1,    -1,  1400,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1446,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1421,    -1,  1460,    -1,    -1,  1393,  1393,  1394,  1395,    -1,
      -1,  1399,  1399,    -1,    -1,    -1,  1474,    -1,    -1,  1407,
      -1,    -1,    -1,    -1,  1445,  1413,    -1,    -1,    -1,    -1,
      -1,    -1,  1420,  1420,  1421,  1422,    -1,    -1,  1459,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1438,  1438,  1473,    -1,    -1,    -1,    -1,    -1,  1445,  1446,
      -1,    -1,    -1,    -1,    -1,  1185,    -1,    -1,    -1,    -1,
    1458,  1458,  1459,  1460,    -1,    -1,    -1,  1197,    -1,    -1,
      -1,    -1,    -1,    -1,  1472,  1472,  1473,  1474,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1491,  1492,    -1,    -1,    -1,    -1,
    1497,  1498,    -1,    -1,    -1,    -1,  1503,  1504,    -1,    -1,
      -1,    -1,  1509,  1510,    -1,    -1,    -1,    -1,  1248,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1261,  1262,  1263,  1264,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1276,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1284,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1708,    -1,    -1,    -1,    -1,    -1,  1644,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,  1643,  1343,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,   153,
     154,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1709,    -1,    -1,  1642,  1642,  1643,  1644,    -1,    -1,
    1648,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1393,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1739,    -1,    -1,    -1,    -1,    -1,  1708,    -1,    -1,
      -1,    -1,    -1,  1413,    -1,    -1,    -1,    -1,    -1,    -1,
    1420,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1738,    -1,  1707,
    1707,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1737,
    1737,  1738,  1739,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1759,  1760,  1761,    -1,    -1,    -1,    -1,    -1,
    1838,  1768,  1769,  1770,    -1,    -1,    -1,    -1,    -1,    -1,
    1777,  1778,  1779,    -1,    -1,    -1,    -1,    -1,    -1,  1786,
    1787,  1788,  1860,    -1,    -1,    -1,    -1,    -1,  1795,  1796,
    1797,  1869,    -1,    -1,    -1,    -1,  1837,  1804,  1805,  1806,
      -1,    -1,    -1,    -1,    -1,    -1,  1813,  1814,  1815,    -1,
      -1,    -1,    -1,    -1,    -1,  1822,  1823,  1824,  1859,    -1,
    1898,    -1,    -1,    -1,    -1,    -1,    -1,  1868,  1836,  1836,
    1837,  1838,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1858,  1858,  1859,  1860,    -1,    -1,  1897,    -1,    -1,  1867,
    1867,    -1,    -1,    -1,    -1,  1873,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1882,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1896,  1896,
    1897,  1898,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    74,    -1,
      -1,    77,  2040,    -1,    -1,    -1,    82,    83,    -1,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2038,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,
     136,   137,   138,   139,   140,   141,   142,    -1,    -1,    -1,
      -1,  2038,    -1,  2040,    -1,    -1,    -1,    -1,    -1,   155,
      -1,    -1,    -1,   159,   160,    -1,    -1,    -1,   164,   165,
     166,    -1,   168,   169,   170,   171,    -1,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,    -1,
      -1,    -1,   188,    -1,    -1,    -1,    -1,   193,   194,   195,
     196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   205,
     206,   207,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,
     246,  2209,    -1,   249,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   258,    -1,    -1,    -1,    -1,    -1,   264,    -1,
    2157,  2158,    -1,    -1,  2161,  2162,   272,   273,    -1,    -1,
      -1,   277,    -1,    -1,    -1,  2206,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2206,
      -1,    -1,  2209,    -1,    -1,    -1,    -1,  2214,  2215,    -1,
      -1,    -1,    -1,  2220,  2221,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    -1,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   134,    -1,   136,   137,   138,   139,
     140,   141,   142,    -1,    -1,    -1,    -1,   147,   148,    -1,
      -1,    -1,    -1,    -1,    -1,   155,   156,    -1,    -1,   159,
     160,    -1,    -1,    -1,   164,   165,   166,    -1,   168,   169,
     170,   171,    -1,    -1,    -1,    -1,    -1,    -1,   178,    -1,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,   188,    -1,
      -1,    -1,    -1,   193,   194,   195,   196,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   205,   206,   207,   208,   209,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   245,   246,    -1,   248,   249,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   257,   258,    -1,
      -1,    -1,    -1,    -1,   264,    -1,   266,   267,    -1,    -1,
      -1,    -1,   272,   273,    -1,    -1,    -1,   277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1063,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1088,    -1,    -1,    -1,    -1,    -1,  1094,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1103,    -1,  1105,
      -1,  1107,    -1,    -1,    -1,  1111,    -1,    -1,    -1,  1115,
      -1,    -1,    -1,  1119,    -1,    -1,    -1,    -1,    -1,    -1,
    1126,    -1,  1128,    -1,  1130,    -1,  1132,    -1,  1134,    -1,
    1136,    -1,  1138,    -1,  1140,    -1,  1142,    -1,  1144,    -1,
    1146,    -1,  1148,    -1,  1150,    -1,  1152,    -1,  1154,    -1,
    1156,    -1,  1158,    -1,  1160,    -1,  1162,    -1,  1164,    -1,
    1166,    -1,  1168,    -1,  1170,    -1,  1172,    -1,  1174,    -1,
    1176,    -1,  1178,    -1,  1180,    -1,  1182,    -1,  1184,    -1,
      -1,  1187,    -1,    -1,    -1,    -1,    -1,  1193,    -1,    -1,
      -1,  1197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1209,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1246,    -1,    -1,    -1,  1250,  1251,  1252,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1278,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1345,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1381,    -1,    -1,    -1,  1385,
      -1,    -1,  1062,    -1,    -1,    -1,    -1,    -1,    -1,  1395,
      -1,    -1,    -1,    -1,    -1,  1401,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1409,    -1,    -1,    -1,  1087,    -1,  1415,
      -1,    -1,    -1,  1093,    -1,    -1,  1422,    -1,  1098,    -1,
      -1,    -1,  1102,    -1,  1104,    -1,  1106,    -1,    -1,    -1,
    1110,    -1,    -1,    -1,  1114,    -1,    -1,    -1,  1118,    -1,
    1446,    -1,    -1,    -1,    -1,  1125,    -1,  1127,    -1,  1129,
      -1,  1131,    -1,  1133,  1460,  1135,    -1,  1137,    -1,  1139,
      -1,  1141,    -1,  1143,    -1,  1145,    -1,  1147,  1474,  1149,
      -1,  1151,    -1,  1153,    -1,  1155,    -1,  1157,    -1,  1159,
      -1,  1161,    -1,  1163,    -1,  1165,  1492,  1167,    -1,  1169,
      -1,  1171,  1498,  1173,    -1,  1175,    -1,  1177,  1504,  1179,
      -1,  1181,    -1,  1183,  1510,    -1,  1186,    -1,    -1,    -1,
      -1,    -1,  1192,    -1,    -1,    -1,    -1,  1197,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1208,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1225,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1245,    -1,    -1,    -1,  1249,
      -1,    -1,    -1,  1253,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1262,    -1,  1264,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1277,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1287,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1644,    -1,
      -1,    -1,    -1,    -1,  1650,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1344,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1380,    -1,    -1,  1709,  1384,    -1,    -1,  1713,    -1,    -1,
      -1,    -1,    -1,    -1,  1394,    -1,    -1,    -1,    -1,    -1,
    1400,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1408,    -1,
      -1,    -1,    -1,  1739,  1414,    -1,    -1,    -1,    -1,    -1,
      -1,  1421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1445,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1459,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1473,    -1,    -1,  1476,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1491,    -1,    -1,    -1,    -1,    -1,  1497,    -1,    -1,
      -1,    -1,    -1,  1503,    -1,    -1,    -1,    -1,    -1,  1509,
      -1,    -1,  1838,    -1,    -1,    -1,  1842,    -1,    -1,    -1,
    1846,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1860,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1869,    -1,    -1,    -1,    -1,    -1,  1875,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1884,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1898,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1643,    -1,    -1,    -1,    -1,    -1,  1649,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1708,   553,
     554,    -1,  1712,    -1,   558,   559,   560,    -1,    -1,    -1,
     564,   565,   566,    -1,    -1,    -1,   570,    -1,   572,   573,
     574,   575,   576,   577,    -1,   579,   580,    -1,  1738,   583,
     584,    -1,    -1,   587,   588,    -1,    -1,   591,   592,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,   619,   620,   621,   622,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   635,   636,   637,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   657,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,    -1,    -1,    -1,   672,   673,
     674,    -1,    -1,    -1,   678,    -1,    -1,  1837,    -1,    -1,
      -1,  1841,    -1,    -1,    -1,  1845,    -1,   691,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   699,   700,    -1,    -1,  1859,
     704,   705,   706,    -1,    -1,    -1,    -1,    -1,  1868,    -1,
      -1,    -1,    -1,    -1,  1874,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1883,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1897,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   769,   770,   771,   772,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     784,   785,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   810,   811,   812,   813,
     814,   815,    -1,    -1,    -1,   819,   820,    -1,    -1,   823,
     824,   825,   826,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   849,   850,   851,    -1,    -1,
      -1,   855,   856,   857,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   867,   868,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   886,   887,   888,    -1,    -1,    -1,   892,   893,
     894,    -1,    -1,    -1,   898,   899,   900,    -1,    -1,    -1,
     904,   905,   906,    -1,    -1,    -1,    -1,   911,   912,   913,
      -1,    -1,    -1,   917,   918,   919,    -1,    -1,    -1,   923,
     924,   925,    -1,    -1,    -1,   929,   930,   931,    -1,    -1,
      -1,   935,   936,   937,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1002,  1003,
      -1,    -1,  1006,  1007,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1019,  1020,  1021,    -1,    -1,
      -1,  1025,  1026,  1027,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1035,  1036,  1037,    -1,    -1,    -1,  1041,  1042,  1043,
      -1,    -1,    -1,    -1,  1048,  1049,  1050,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1078,    -1,    -1,    -1,    -1,    -1,
    1084,  1085,    -1,    -1,    -1,  1089,  1090,  1091,    -1,    -1,
      -1,  1095,  1096,  1097,    -1,  1099,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1108,  1109,    -1,    -1,  1112,  1113,
      -1,    -1,  1116,  1117,    -1,    -1,  1120,  1121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1188,  1189,  1190,    -1,    -1,    -1,
    1194,  1195,  1196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1219,  1220,  1221,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1254,  1255,  1256,    -1,    -1,  1259,  1260,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1279,  1280,  1281,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1298,  1299,  1300,    -1,    -1,    -1,
    1304,  1305,  1306,    -1,    -1,    -1,  1310,  1311,  1312,    -1,
      -1,    -1,  1316,  1317,  1318,    -1,    -1,    -1,  1322,  1323,
    1324,    -1,    -1,    -1,  1328,  1329,  1330,    -1,    -1,    -1,
    1334,  1335,  1336,    -1,    -1,    -1,  1340,  1341,  1342,    -1,
      -1,    -1,  1346,  1347,  1348,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,  1382,  1383,
      -1,    -1,  1386,  1387,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1396,  1397,  1398,    -1,    -1,    -1,  1402,  1403,
    1404,    -1,    -1,    -1,    -1,    -1,  1410,  1411,  1412,    -1,
      -1,    70,  1416,  1417,  1418,    74,    -1,    -1,    -1,  1423,
    1424,  1425,    -1,    82,    83,    -1,    -1,    86,    87,    -1,
      89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   145,   146,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     159,   160,    -1,    -1,    -1,    -1,    -1,   166,    -1,   168,
     169,   170,   171,    20,    21,    22,    -1,    -1,    -1,   178,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,   188,
      -1,    -1,    -1,    -1,   193,   194,   195,   196,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   205,   206,   207,   208,
     209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    83,    -1,    -1,    86,
      87,    -1,    89,    90,    -1,   244,   245,   246,   247,    -1,
      -1,    -1,    -1,    -1,   253,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   272,   273,    -1,    -1,    -1,   277,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,   146,
     147,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
      -1,    -1,   159,   160,  1658,    -1,  1660,    -1,    -1,   166,
      -1,   168,   169,   170,   171,    -1,    -1,    -1,    -1,    -1,
      -1,   178,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,    -1,    -1,    -1,    -1,   193,   194,   195,   196,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   205,   206,
     207,   208,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,   246,
      -1,   248,   249,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     257,   258,    -1,    -1,    -1,    -1,    -1,   264,    -1,   266,
     267,    -1,    -1,    -1,    -1,   272,   273,    -1,    -1,    -1,
     277,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1839,  1840,    -1,    -1,  1843,
    1844,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2039,    -1,  2041,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2159,  2160,    -1,    -1,  2163,
    2164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1063,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1088,
      -1,    -1,    -1,    -1,    -1,  1094,    -1,    -1,    -1,    -1,
      -1,    -1,  1101,    -1,  1103,    -1,  1105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1126,    -1,  1128,
      -1,  1130,    -1,  1132,    -1,  1134,    -1,  1136,    -1,  1138,
      -1,  1140,    -1,  1142,    -1,  1144,    -1,  1146,    -1,  1148,
      -1,  1150,    -1,  1152,    -1,  1154,    -1,  1156,    -1,  1158,
      -1,  1160,    -1,  1162,    -1,  1164,    -1,  1166,    -1,  1168,
      -1,  1170,    -1,  1172,    -1,  1174,    -1,  1176,    -1,  1178,
      -1,  1180,    -1,  1182,    -1,  1184,    -1,    -1,  1187,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1197,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1209,    -1,    -1,    -1,    -1,  1062,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1228,
      -1,  1230,    -1,  1232,    -1,  1234,    -1,  1236,    -1,  1238,
    1087,    -1,    -1,    -1,    -1,    -1,  1093,    -1,    -1,    -1,
      -1,  1250,    -1,  1100,    -1,  1102,    -1,  1104,    -1,  1258,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1125,  1278,
    1127,    -1,  1129,    -1,  1131,  1284,  1133,    -1,  1135,  1288,
    1137,    -1,  1139,    -1,  1141,    -1,  1143,    -1,  1145,    -1,
    1147,    -1,  1149,    -1,  1151,    -1,  1153,    -1,  1155,    -1,
    1157,    -1,  1159,    -1,  1161,    -1,  1163,    -1,  1165,    -1,
    1167,    -1,  1169,    -1,  1171,    -1,  1173,    -1,  1175,    -1,
    1177,    -1,  1179,    -1,  1181,    -1,  1183,    -1,    -1,  1186,
      -1,    -1,    -1,    -1,    -1,    -1,  1345,    -1,    -1,    -1,
    1197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1225,  1226,
    1227,    -1,  1229,    -1,  1231,    -1,  1233,    -1,  1235,    -1,
    1237,    -1,    -1,    -1,    -1,    -1,  1395,    -1,  1245,  1246,
      -1,    -1,  1249,    -1,    -1,    -1,  1253,    -1,    -1,    -1,
    1257,    -1,    -1,    -1,    -1,  1262,  1415,  1264,    -1,    -1,
      -1,    -1,    -1,  1422,    -1,    -1,    -1,    -1,    -1,    -1,
    1277,    -1,    -1,    -1,    -1,    -1,    -1,  1284,   556,   557,
    1287,    -1,    -1,   561,   562,   563,    -1,    -1,    -1,   567,
     568,   569,    -1,   571,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   581,   582,    -1,    -1,   585,   586,    -1,
      -1,   589,   590,    -1,    -1,   593,   594,    -1,    -1,    -1,
      -1,    -1,    -1,   601,   602,    -1,    -1,   605,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1344,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1394,    -1,    -1,
      -1,   669,   670,   671,    -1,    -1,    -1,   675,   676,   677,
      -1,    -1,    -1,    -1,   682,   683,   684,  1414,    -1,    -1,
     688,   689,   690,    -1,  1421,    -1,    -1,   695,   696,   697,
      -1,    -1,    -1,   701,   702,   703,    -1,    -1,    -1,    -1,
      -1,    -1,   710,   711,   712,   713,   714,   715,    -1,   717,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   754,   755,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   773,   774,   775,   776,    -1,
     778,    -1,   780,    -1,    -1,    -1,    -1,    -1,    -1,   787,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   816,   817,
     818,    -1,    -1,   821,   822,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   830,   831,   832,    -1,    -1,    -1,   836,   837,
     838,    -1,    -1,   841,   842,    -1,    -1,    -1,   846,   847,
     848,    -1,    -1,    -1,   852,   853,   854,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   865,   866,    -1,
      -1,   869,   870,   871,   872,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   881,   882,    -1,    -1,    -1,    -1,    -1,
      -1,   889,   890,   891,    -1,    -1,    -1,   895,   896,   897,
      -1,    -1,    -1,   901,   902,   903,    -1,    -1,    -1,   907,
     908,   909,    -1,    -1,    -1,    -1,   914,   915,   916,    -1,
      -1,    -1,   920,   921,   922,    -1,    -1,    -1,   926,   927,
     928,    -1,    -1,    -1,   932,   933,   934,    -1,    -1,    -1,
     938,   939,   940,    -1,   942,    -1,   944,    -1,   946,    -1,
     948,    -1,   950,    -1,   952,    -1,   954,    -1,   956,    -1,
     958,    -1,   960,    -1,   962,    -1,   964,    -1,   966,    -1,
     968,    -1,   970,    -1,   972,    -1,   974,    -1,   976,    -1,
     978,    -1,   980,    -1,   982,    -1,   984,    -1,   986,    -1,
     988,    -1,   990,    -1,   992,    -1,   994,    -1,   996,    -1,
     998,    -1,  1000,  1001,    -1,    -1,  1004,  1005,    -1,    -1,
    1008,  1009,  1010,    -1,  1012,    -1,    -1,  1015,  1016,    -1,
    1018,    -1,    -1,    -1,  1022,  1023,  1024,    -1,    -1,    -1,
    1028,  1029,  1030,    -1,  1032,    -1,  1034,    -1,    -1,    -1,
    1038,  1039,  1040,    -1,    -1,    -1,  1044,  1045,  1046,  1047,
      -1,    -1,    -1,  1051,  1052,  1053,    -1,  1055,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1428,    -1,    -1,  1431,    -1,    -1,    -1,  1435,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1448,    -1,    -1,  1451,    -1,    -1,    -1,  1455,    -1,    -1,
      -1,    -1,    -1,    -1,  1462,    -1,    -1,  1465,    -1,    -1,
      -1,  1469,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1477,
    1478,    -1,  1480,    -1,  1482,    -1,  1484,    -1,  1486,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1512,    -1,  1514,    -1,  1516,    -1,
    1518,    -1,  1520,    -1,  1522,    -1,  1524,    -1,  1526,    -1,
    1528,    -1,  1530,    -1,  1532,    -1,  1534,    -1,  1536,    -1,
    1538,    -1,  1540,    -1,  1542,    -1,  1544,    -1,  1546,    -1,
    1548,    -1,  1550,    -1,  1552,    -1,  1554,    -1,  1556,    -1,
    1558,    -1,  1560,    -1,  1562,    -1,  1564,    -1,  1566,    -1,
    1568,    -1,  1570,    -1,  1572,    -1,  1574,    -1,  1576,    -1,
    1578,    -1,  1580,    -1,  1582,    -1,  1584,    -1,  1586,    -1,
    1588,    -1,  1590,    -1,  1592,    -1,  1594,    -1,  1596,    -1,
    1598,    -1,  1600,    -1,  1602,    -1,  1604,    -1,  1606,    -1,
    1608,    -1,  1610,    -1,  1612,    -1,  1614,    -1,  1616,    -1,
    1618,    -1,  1620,    -1,  1622,    -1,  1624,    -1,  1626,    -1,
    1628,    -1,  1630,    -1,  1632,    -1,    -1,  1635,    -1,    -1,
      -1,  1639,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1654,  1655,  1656,    -1,
      -1,  1659,    -1,  1661,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1672,    -1,  1674,  1675,  1676,  1677,
    1678,  1679,  1680,  1681,  1682,  1683,  1684,  1685,  1686,    -1,
    1688,    -1,  1690,    -1,  1692,    -1,    -1,    -1,  1696,    -1,
      -1,    -1,    -1,  1701,    -1,    -1,    -1,    -1,  1706,    -1,
      -1,    -1,  1710,  1711,    -1,    -1,    -1,  1715,    -1,    -1,
    1718,  1719,    -1,  1721,    -1,    -1,  1724,  1725,    -1,  1727,
      -1,    -1,  1730,    -1,    -1,    -1,  1734,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1746,  1747,
    1748,    -1,  1750,    -1,  1752,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1826,    -1,
      -1,  1829,    -1,    -1,    -1,  1833,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1848,    -1,    -1,  1851,    -1,    -1,    -1,  1855,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,  1877,
      -1,  1879,    -1,  1881,    -1,    -1,    -1,    27,  1886,    -1,
      -1,  1889,    32,    -1,    -1,  1893,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    -1,    -1,    88,    89,
      90,    -1,    -1,    -1,    94,    95,    -1,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,   123,    -1,   125,   126,   127,   128,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   136,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   229,
      -1,    -1,   232,   233,   234,   235,   236,   237,   238,   239,
      -1,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,    -1,    -1,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,    -1,   302,   303,   304,   305,   306,    -1,    -1,    -1,
      -1,    -1,    -1,   313,    -1,    -1,    -1,    -1,   318,   319,
      -1,    -1,   322,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   345,   346,   347,    -1,    -1,
      -1,    -1,    -1,   353,    -1,    -1,    -1,   357,    -1,   359,
      -1,    -1,    -1,    -1,   364,   365,   366,   367,   368,    -1,
      -1,   371,   372,   373,   374,   375,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   394,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   451,   452,   453,   454,   455,   456,    -1,    -1,   459,
     460,   461,   462,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   499,
     500,   501,   502,   503,    -1,   505,   506,   507,   508,    -1,
      -1,   511,   512,   513,   514,   515,   516,    -1,    -1,    -1,
      -1,   521,    -1,    -1,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,    -1,    -1,   569,
     570,   571,    -1,    -1,    -1,   575,   576,   577,   578,   579,
     580,   581,    -1,   583,   584,    -1,    -1,    -1,    -1,   589,
     590,   591,   592,   593,   594,    -1,    -1,   597,    -1,    -1,
      -1,    -1,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,   612,   613,    -1,    -1,   616,   617,   618,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   715
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,   721,   730,   731,
     975,   976,   977,     0,   731,     9,    10,    11,    12,    13,
      14,    27,    32,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    88,    89,    90,    94,    95,    98,    99,   122,   123,
     125,   126,   127,   128,   136,   229,   232,   233,   234,   235,
     236,   237,   238,   239,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   302,   303,   304,   305,   306,   313,   318,   319,
     322,   345,   346,   347,   353,   357,   359,   364,   365,   366,
     367,   368,   371,   372,   373,   374,   375,   394,   451,   452,
     453,   454,   455,   456,   459,   460,   461,   462,   499,   500,
     501,   502,   503,   505,   506,   507,   508,   511,   512,   513,
     514,   515,   516,   521,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   564,   565,   566,   569,   570,   571,
     575,   576,   577,   578,   579,   580,   581,   583,   584,   589,
     590,   591,   592,   593,   594,   597,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   616,   617,
     618,   715,   732,   733,   734,   735,   736,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     750,   751,   752,   753,   754,   755,   756,   757,   758,   759,
     760,   761,   762,   763,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   793,   794,   795,   796,   797,   798,   799,
     800,   801,   802,   803,   804,   805,   806,   807,   808,   809,
     810,   811,   812,   813,   814,   815,   816,   817,   818,   819,
     820,   821,   822,   823,   824,   825,   826,   827,   828,   829,
     830,   831,   832,   833,   834,   835,   836,   837,   838,   839,
     840,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,   856,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   887,   888,   889,
     890,   891,   892,   893,   894,   895,   896,   897,   898,   899,
     900,   901,   902,   903,   904,   905,   906,   907,   908,   909,
     910,   911,   912,   913,   914,   915,   916,   917,   918,   919,
     920,   921,   922,   923,   924,   925,   926,   927,   928,   929,
     930,   931,   932,   933,   934,   935,   936,   937,   938,   939,
     940,   941,   942,   943,   944,   945,   946,   947,   948,   949,
     950,   951,   952,   953,   954,   955,   956,   957,   958,   959,
     960,   961,   962,   963,   964,   965,   966,   967,   968,   969,
     970,   971,   718,   991,   991,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   642,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   652,   653,   654,   704,
     705,   706,   978,   979,   980,   987,   988,   989,   978,   979,
     980,   987,   988,   989,   978,   979,   980,   987,   988,   989,
     979,   988,   979,   980,   979,   980,   979,   980,   980,   979,
     980,   988,   989,   979,   980,   988,   989,   979,   980,   988,
     989,   979,   980,   988,   989,   715,   719,   720,   972,   979,
     980,   988,   989,   992,   993,   987,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   979,   980,   979,   980,
     979,   980,   979,   980,   979,   980,   978,   979,   980,   987,
     988,   989,   978,   979,   980,   987,   988,   989,   980,   978,
     979,   980,   987,   988,   989,   978,   979,   980,   987,   988,
     989,   979,   978,   979,   980,   987,   988,   989,   978,   979,
     980,   987,   988,   989,   631,   639,   647,   978,   979,   980,
     987,   988,   989,   987,   988,   989,   991,   987,   972,   972,
     972,   972,   972,   972,   972,   972,   972,   972,   972,   972,
     972,   972,   972,   972,   972,   972,   972,   972,   972,   972,
     972,   972,   972,   972,   972,   972,   972,   972,   972,   972,
     972,   972,   979,   980,   988,   989,   991,   992,   993,   979,
     980,   979,   980,   979,   980,   979,   980,   979,   980,   979,
     980,   979,   980,   988,   989,   988,   989,   979,   988,   979,
     988,   972,   972,   972,   979,   980,   979,   988,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     667,   668,   669,   670,   695,   696,   697,   698,   699,   700,
     978,   979,   980,   981,   982,   984,   987,   988,   989,   979,
     980,   988,   989,   979,   980,   979,   980,   978,   979,   980,
     987,   988,   989,   978,   979,   980,   987,   988,   989,   979,
     980,   988,   989,   978,   979,   980,   987,   988,   989,   978,
     979,   980,   987,   988,   989,   641,   991,   641,   695,   697,
     698,   699,   700,   979,   980,   988,   989,   979,   980,   987,
     987,   987,   987,   695,   696,   697,   698,   699,   700,   979,
     980,   988,   989,   991,   992,   993,   978,   979,   980,   987,
     988,   989,   978,   979,   980,   987,   988,   989,   978,   979,
     980,   987,   988,   989,   978,   979,   980,   987,   988,   989,
     992,   978,   979,   980,   987,   988,   989,   978,   979,   980,
     987,   988,   989,   978,   979,   980,   987,   988,   989,   978,
     979,   980,   987,   988,   989,   978,   979,   980,   987,   988,
     989,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   978,   987,   978,   987,   978,   987,   978,   987,   978,
     987,   989,   979,   980,   988,   989,   979,   980,   988,   989,
     989,   979,   988,   979,   980,   988,   989,   979,   988,   978,
     979,   980,   987,   988,   989,   978,   979,   980,   987,   988,
     989,   979,   988,   979,   988,   978,   979,   980,   987,   988,
     989,   978,   979,   980,   987,   988,   989,   987,   978,   979,
     980,   987,   988,   989,   707,   990,   722,   996,   725,   998,
     723,   997,   997,   997,   647,   648,   649,   650,   651,   652,
     653,   654,   709,   710,   711,   712,   715,   717,   973,   974,
     983,   984,   985,   995,   973,   973,   997,   997,   997,   973,
     973,   973,   997,   997,   997,   973,   973,   973,   997,   973,
     997,   997,   997,   997,   997,   997,   997,   997,   973,   973,
     997,   997,   973,   973,   997,   997,   973,   973,   997,   997,
     973,   973,   973,   973,   973,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   973,   973,
     973,   997,   997,   997,   973,   973,   973,   997,   973,   973,
     973,   973,   973,   973,   997,   973,   973,   973,   997,   997,
     973,   973,   973,   997,   997,   997,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   997,   997,   997,   997,   997,
     997,   997,   997,   997,   997,   997,   997,   997,   997,   973,
     973,   973,   973,   973,   973,   997,   997,   973,   997,   997,
     997,   997,   997,   997,   973,   973,   973,   997,   997,   973,
     973,   997,   997,   997,   997,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   997,   997,   997,   973,
     973,   973,   997,   997,   997,   973,   973,   997,   997,   973,
     973,   973,   973,   973,   973,   997,   997,   997,   973,   973,
     973,   997,   997,   997,   973,   973,   973,   997,   997,   997,
     973,   973,   973,   997,   997,   997,   973,   973,   973,   997,
     997,   997,   973,   973,   973,   997,   997,   997,   973,   973,
     973,   997,   997,   997,   973,   973,   973,   997,   997,   997,
     973,   973,   973,   997,   997,   997,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     997,   997,   973,   973,   997,   997,   973,   973,   973,   973,
     973,   973,   973,   997,   997,   997,   973,   973,   973,   997,
     997,   997,   973,   973,   973,   973,   973,   997,   997,   997,
     973,   973,   973,   997,   997,   997,   973,   973,   973,   973,
     997,   997,   997,   973,   973,   973,   973,   978,   987,   991,
     979,   988,   991,   992,   980,   989,   991,   993,   997,   724,
     713,   714,   986,   974,   983,   997,   997,   978,   987,   991,
     979,   988,   991,   992,   980,   989,   991,   993,   997,   997,
     997,   978,   987,   991,   979,   988,   991,   992,   980,   989,
     991,   993,   997,   997,   997,   979,   997,   988,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   991,   980,
     991,   997,   997,   979,   991,   980,   991,   997,   997,   979,
     991,   980,   991,   997,   997,   979,   991,   980,   991,   997,
     997,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   979,   988,   980,   989,   979,   988,   980,   989,   979,
     988,   980,   989,   979,   988,   980,   989,   979,   988,   980,
     989,   978,   987,   991,   979,   988,   991,   992,   980,   989,
     991,   993,   997,   997,   997,   978,   979,   980,   997,   997,
     997,   978,   979,   980,   987,   988,   989,   991,   979,   988,
     980,   989,   641,   991,   641,   992,   641,   993,   997,   997,
     997,   979,   988,   980,   988,   988,   989,   988,   989,   988,
     989,   988,   989,   988,   989,   988,   989,   979,   988,   980,
     988,   978,   987,   991,   979,   984,   988,   992,   980,   981,
     982,   989,   993,   980,   980,   979,   988,   997,   997,   997,
     988,   989,   997,   997,   978,   987,   978,   979,   987,   988,
     978,   987,   978,   979,   987,   988,   978,   987,   991,   979,
     988,   991,   992,   980,   989,   991,   993,   997,   997,   997,
     631,   639,   647,   631,   639,   647,   987,   988,   989,   979,
     988,   980,   989,   632,   991,   632,   991,   632,   991,   997,
     997,   997,   632,   991,   632,   991,   632,   991,   997,   997,
     997,   632,   991,   632,   991,   632,   991,   997,   997,   997,
     632,   991,   632,   991,   632,   991,   997,   997,   997,   632,
     991,   632,   991,   632,   991,   997,   997,   997,   632,   991,
     632,   991,   632,   991,   997,   997,   997,   632,   991,   632,
     991,   632,   991,   997,   997,   997,   632,   991,   632,   991,
     632,   991,   997,   997,   997,   978,   987,   991,   979,   988,
     991,   992,   980,   989,   991,   993,   997,   997,   997,   979,
     980,   997,   997,   979,   980,   997,   997,   978,   987,   991,
     979,   988,   991,   992,   980,   989,   991,   993,   997,   997,
     997,   978,   991,   979,   992,   980,   993,   997,   997,   997,
     978,   979,   980,   997,   997,   997,   978,   987,   979,   988,
     980,   989,   997,   997,   997,   978,   987,   991,   979,   988,
     991,   992,   980,   989,   991,   993,   997,   997,   997,   973,
     973,   973,   978,   991,   716,   994,   995,   724,   713,   986,
     979,   991,   992,   980,   991,   993,   973,   973,   973,   978,
     991,   979,   991,   992,   980,   991,   993,   973,   973,   973,
     978,   991,   979,   991,   992,   980,   991,   993,   979,   973,
     973,   973,   973,   973,   973,   979,   991,   980,   991,   979,
     991,   980,   991,   979,   991,   980,   991,   979,   991,   980,
     991,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   978,   991,   979,   991,   992,   980,
     991,   993,   978,   979,   980,   973,   973,   973,   997,   973,
     997,   973,   641,   641,   641,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   978,   991,   979,   984,   992,
     980,   993,   973,   973,   979,   980,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   978,   991,   979,   991,   992,
     980,   991,   993,   973,   973,   973,   973,   973,   632,   991,
     632,   991,   632,   991,   632,   991,   632,   991,   632,   991,
     632,   991,   632,   991,   632,   991,   632,   991,   632,   991,
     632,   991,   632,   991,   632,   991,   632,   991,   632,   991,
     632,   991,   632,   991,   632,   991,   632,   991,   632,   991,
     632,   991,   632,   991,   632,   991,   973,   973,   973,   978,
     991,   979,   991,   992,   980,   991,   993,   997,   997,   979,
     980,   997,   997,   979,   980,   973,   973,   973,   978,   991,
     979,   991,   992,   980,   991,   993,   978,   991,   979,   992,
     980,   993,   978,   979,   980,   973,   973,   973,   978,   979,
     980,   973,   973,   973,   978,   991,   979,   991,   992,   980,
     991,   993,   983,   995,   991,   992,   997,   991,   993,   997,
     632,   991,   632,   991,   997,   997,   632,   991,   632,   991,
     997,   997,   986,   991,   992,   991,   993,   632,   991,   632,
     991,   632,   991,   632,   991,   994,   995
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:

/* Line 1455 of yacc.c  */
#line 721 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					/* 增加一个地址标号 */
				    __char *pNodeName = NextSymbol();
					PASMER_SYMBOL_NODE pNode = NULL;
				    pCurrAsmObj->bAddrLabel = TRUE;
					pNode = AddSymbolToTable(pNodeName, 0, AST_ADDR_LAB);
					if (!pNode) return -1;
					pCurrAsmObj->pAddrLabelSymbolName = pNodeName;
					pCurrAsmObj->pSymbolNode = pNode;
				 }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 920 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAA, "\x37", 1, 0xFF);
					}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 926 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAD, "\xD5\x0A", 2, 0xFF);
					}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 930 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAD, "\xD5", 1, 0xFF);
					}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 936 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAM, "\xD4\x0A", 2, 0xFF);
					}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 940 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAM, "\xD4", 1, 0xFF);
					}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 946 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, AAS, "\x3F", 1, 0xFF);
					}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 952 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x14", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x80", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 964 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x80", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 969 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x15", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 982 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 988 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x15", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1000 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1005 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1011 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1016 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1021 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1026 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x10", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1034 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x10", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1039 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1048 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1054 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1062 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1067 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x12", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1072 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x13", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1078 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x13", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1085 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x04", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x80", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1097 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x80", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1102 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x05", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1115 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1121 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x05", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1133 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1138 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1144 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1149 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1154 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1159 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x00", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1167 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x00", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1172 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1181 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1187 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1195 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1200 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x02", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1205 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x03", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1211 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x03", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1218 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x24", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x80", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1230 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x80", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1235 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x24", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1248 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1254 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x25", 1, 0xFF);  
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1266 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1271 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1277 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1282 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1287 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1292 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x20", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1300 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x20", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1305 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1314 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1320 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1328 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1333 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x22", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1338 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x23", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1344 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x23", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1351 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ANDNPS, "\x63", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1359 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, ARPL, "\x63", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1366 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BOUND, "\x62", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1372 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, BOUND, "\x62", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1379 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1388 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1394 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));				
					}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1402 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));	
					}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1409 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1418 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1424 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1432 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1439 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, BSWAP, "\x0F\xC8", 2, 0xFF);
					}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1445 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1454 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1462 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1468 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1473 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1482 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1490 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1496 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1503 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1512 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1520 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1526 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1531 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1540 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1548 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 1554 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 1561 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 1570 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 1578 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 1584 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 1589 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));						
					}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 1598 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 1606 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 1612 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 1619 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 1628 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 1636 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 1642 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 1647 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 1656 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 1664 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 1670 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 1677 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 1681 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 1686 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 1690 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 1699 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 1707 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);			    
					    pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 1713 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 1720 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CBW, "\x98", 1, 0xFF);
					}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 1727 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CWDE, "\x98", 1, 0xFF);
					}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 1733 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CLC, "\xF8", 1, 0xFF);	
					}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 1739 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CLD, "\xFC", 1, 0xFF);
					}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 1745 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CLFLUSH, "\x0F\xAE", 2, 7);
					    pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 1752 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CLI, "\xFA", 1, 0xFF);
					}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 1758 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CLTS, "\x0F\x06", 2, 0xFF);
					}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 1764 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMC, "\xF5", 1, 0xFF);
					}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 1769 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVA; }
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 1770 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVAE; }
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 1771 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVB; }
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 1772 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVBE; }
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 1773 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVC; }
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 1774 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVE; }
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 1775 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVG; }
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 1776 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVGE; }
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 1777 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVL; }
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 1778 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVLE; }
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 1779 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNA; }
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 1780 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNAE; }
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 1781 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNB; }
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 1782 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNBE; }
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 1783 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNC; }
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 1784 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNE; }
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 1785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNG; }
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 1786 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVGE; }
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 1787 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNL; }
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 1788 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNLE; }
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 1789 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNO; }
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 1790 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNP; }
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 1791 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNS; }
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 1792 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVNZ; }
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 1793 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVO; }
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 1794 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVP; }
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 1795 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVPE; }
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 1796 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVPO; }
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 1797 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVS; }
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 1798 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = CMOVZ; }
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 1802 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 1811 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 1817 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 1825 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 1832 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 1841 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 1847 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 1855 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 1862 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 1871 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 1877 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 1885 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));				
					}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 1892 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 1901 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 1907 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 1915 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 357:

/* Line 1455 of yacc.c  */
#line 1922 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 358:

/* Line 1455 of yacc.c  */
#line 1931 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 359:

/* Line 1455 of yacc.c  */
#line 1937 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 360:

/* Line 1455 of yacc.c  */
#line 1945 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 361:

/* Line 1455 of yacc.c  */
#line 1952 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 362:

/* Line 1455 of yacc.c  */
#line 1961 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 363:

/* Line 1455 of yacc.c  */
#line 1967 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 364:

/* Line 1455 of yacc.c  */
#line 1975 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 365:

/* Line 1455 of yacc.c  */
#line 1982 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 366:

/* Line 1455 of yacc.c  */
#line 1991 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 367:

/* Line 1455 of yacc.c  */
#line 1997 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 368:

/* Line 1455 of yacc.c  */
#line 2005 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 369:

/* Line 1455 of yacc.c  */
#line 2012 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 370:

/* Line 1455 of yacc.c  */
#line 2021 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 371:

/* Line 1455 of yacc.c  */
#line 2027 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 372:

/* Line 1455 of yacc.c  */
#line 2035 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 373:

/* Line 1455 of yacc.c  */
#line 2042 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 374:

/* Line 1455 of yacc.c  */
#line 2051 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 375:

/* Line 1455 of yacc.c  */
#line 2057 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 376:

/* Line 1455 of yacc.c  */
#line 2065 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 377:

/* Line 1455 of yacc.c  */
#line 2072 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 378:

/* Line 1455 of yacc.c  */
#line 2081 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 379:

/* Line 1455 of yacc.c  */
#line 2087 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 380:

/* Line 1455 of yacc.c  */
#line 2095 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 381:

/* Line 1455 of yacc.c  */
#line 2102 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 382:

/* Line 1455 of yacc.c  */
#line 2111 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 383:

/* Line 1455 of yacc.c  */
#line 2117 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 384:

/* Line 1455 of yacc.c  */
#line 2125 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 385:

/* Line 1455 of yacc.c  */
#line 2132 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 386:

/* Line 1455 of yacc.c  */
#line 2141 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 387:

/* Line 1455 of yacc.c  */
#line 2147 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 388:

/* Line 1455 of yacc.c  */
#line 2155 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 389:

/* Line 1455 of yacc.c  */
#line 2162 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 390:

/* Line 1455 of yacc.c  */
#line 2171 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 391:

/* Line 1455 of yacc.c  */
#line 2177 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 392:

/* Line 1455 of yacc.c  */
#line 2185 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 393:

/* Line 1455 of yacc.c  */
#line 2192 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 394:

/* Line 1455 of yacc.c  */
#line 2201 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 395:

/* Line 1455 of yacc.c  */
#line 2207 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 396:

/* Line 1455 of yacc.c  */
#line 2215 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 397:

/* Line 1455 of yacc.c  */
#line 2222 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 398:

/* Line 1455 of yacc.c  */
#line 2231 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 399:

/* Line 1455 of yacc.c  */
#line 2237 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 400:

/* Line 1455 of yacc.c  */
#line 2245 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 401:

/* Line 1455 of yacc.c  */
#line 2252 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 402:

/* Line 1455 of yacc.c  */
#line 2261 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 403:

/* Line 1455 of yacc.c  */
#line 2267 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 404:

/* Line 1455 of yacc.c  */
#line 2275 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 405:

/* Line 1455 of yacc.c  */
#line 2282 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 406:

/* Line 1455 of yacc.c  */
#line 2291 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 407:

/* Line 1455 of yacc.c  */
#line 2297 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 408:

/* Line 1455 of yacc.c  */
#line 2305 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 409:

/* Line 1455 of yacc.c  */
#line 2312 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 410:

/* Line 1455 of yacc.c  */
#line 2321 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 411:

/* Line 1455 of yacc.c  */
#line 2327 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 412:

/* Line 1455 of yacc.c  */
#line 2335 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 413:

/* Line 1455 of yacc.c  */
#line 2342 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 414:

/* Line 1455 of yacc.c  */
#line 2351 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 415:

/* Line 1455 of yacc.c  */
#line 2357 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 416:

/* Line 1455 of yacc.c  */
#line 2365 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 417:

/* Line 1455 of yacc.c  */
#line 2372 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 418:

/* Line 1455 of yacc.c  */
#line 2381 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 419:

/* Line 1455 of yacc.c  */
#line 2387 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 420:

/* Line 1455 of yacc.c  */
#line 2395 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 421:

/* Line 1455 of yacc.c  */
#line 2402 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 422:

/* Line 1455 of yacc.c  */
#line 2411 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 423:

/* Line 1455 of yacc.c  */
#line 2417 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 424:

/* Line 1455 of yacc.c  */
#line 2425 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 425:

/* Line 1455 of yacc.c  */
#line 2432 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 426:

/* Line 1455 of yacc.c  */
#line 2441 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 427:

/* Line 1455 of yacc.c  */
#line 2447 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 428:

/* Line 1455 of yacc.c  */
#line 2455 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 429:

/* Line 1455 of yacc.c  */
#line 2462 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 430:

/* Line 1455 of yacc.c  */
#line 2471 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 431:

/* Line 1455 of yacc.c  */
#line 2477 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 432:

/* Line 1455 of yacc.c  */
#line 2485 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 433:

/* Line 1455 of yacc.c  */
#line 2492 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 434:

/* Line 1455 of yacc.c  */
#line 2501 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 435:

/* Line 1455 of yacc.c  */
#line 2507 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 436:

/* Line 1455 of yacc.c  */
#line 2515 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 437:

/* Line 1455 of yacc.c  */
#line 2522 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 438:

/* Line 1455 of yacc.c  */
#line 2531 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 439:

/* Line 1455 of yacc.c  */
#line 2537 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 440:

/* Line 1455 of yacc.c  */
#line 2545 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 441:

/* Line 1455 of yacc.c  */
#line 2552 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 442:

/* Line 1455 of yacc.c  */
#line 2561 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 443:

/* Line 1455 of yacc.c  */
#line 2567 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 444:

/* Line 1455 of yacc.c  */
#line 2575 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 445:

/* Line 1455 of yacc.c  */
#line 2582 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 446:

/* Line 1455 of yacc.c  */
#line 2591 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 447:

/* Line 1455 of yacc.c  */
#line 2597 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 448:

/* Line 1455 of yacc.c  */
#line 2605 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 449:

/* Line 1455 of yacc.c  */
#line 2612 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 450:

/* Line 1455 of yacc.c  */
#line 2621 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 451:

/* Line 1455 of yacc.c  */
#line 2627 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 452:

/* Line 1455 of yacc.c  */
#line 2635 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 453:

/* Line 1455 of yacc.c  */
#line 2643 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 454:

/* Line 1455 of yacc.c  */
#line 2652 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 455:

/* Line 1455 of yacc.c  */
#line 2658 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 456:

/* Line 1455 of yacc.c  */
#line 2666 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 457:

/* Line 1455 of yacc.c  */
#line 2673 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 458:

/* Line 1455 of yacc.c  */
#line 2682 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 459:

/* Line 1455 of yacc.c  */
#line 2688 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 460:

/* Line 1455 of yacc.c  */
#line 2696 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 461:

/* Line 1455 of yacc.c  */
#line 2703 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x80", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 462:

/* Line 1455 of yacc.c  */
#line 2715 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x80", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 463:

/* Line 1455 of yacc.c  */
#line 2720 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 464:

/* Line 1455 of yacc.c  */
#line 2733 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 465:

/* Line 1455 of yacc.c  */
#line 2739 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 466:

/* Line 1455 of yacc.c  */
#line 2751 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 467:

/* Line 1455 of yacc.c  */
#line 2756 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 468:

/* Line 1455 of yacc.c  */
#line 2762 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 469:

/* Line 1455 of yacc.c  */
#line 2767 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 470:

/* Line 1455 of yacc.c  */
#line 2772 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 471:

/* Line 1455 of yacc.c  */
#line 2777 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x38", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 472:

/* Line 1455 of yacc.c  */
#line 2785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x38", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 473:

/* Line 1455 of yacc.c  */
#line 2790 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 474:

/* Line 1455 of yacc.c  */
#line 2799 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 475:

/* Line 1455 of yacc.c  */
#line 2805 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 476:

/* Line 1455 of yacc.c  */
#line 2813 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 477:

/* Line 1455 of yacc.c  */
#line 2818 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 478:

/* Line 1455 of yacc.c  */
#line 2823 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 479:

/* Line 1455 of yacc.c  */
#line 2829 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 480:

/* Line 1455 of yacc.c  */
#line 2836 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSB, "\xA6", 1, 0xFF);
					}
    break;

  case 481:

/* Line 1455 of yacc.c  */
#line 2842 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSW, "\xA7", 1, 0xFF);
					}
    break;

  case 482:

/* Line 1455 of yacc.c  */
#line 2848 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSD, "\xA7", 1, 0xFF);
					}
    break;

  case 483:

/* Line 1455 of yacc.c  */
#line 2854 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB0", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 484:

/* Line 1455 of yacc.c  */
#line 2862 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB0", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 485:

/* Line 1455 of yacc.c  */
#line 2867 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 486:

/* Line 1455 of yacc.c  */
#line 2876 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 487:

/* Line 1455 of yacc.c  */
#line 2884 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 488:

/* Line 1455 of yacc.c  */
#line 2890 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 489:

/* Line 1455 of yacc.c  */
#line 2897 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
							SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG8B, "\x0F\C7", 2, 1);
							pCurrAsmObj->ModRM.RO = 1;
					  }
    break;

  case 490:

/* Line 1455 of yacc.c  */
#line 2904 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CPUID, "\x0F\xA2", 2, 0xFF);
					}
    break;

  case 491:

/* Line 1455 of yacc.c  */
#line 2910 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF0", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 492:

/* Line 1455 of yacc.c  */
#line 2918 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF0", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 493:

/* Line 1455 of yacc.c  */
#line 2923 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 494:

/* Line 1455 of yacc.c  */
#line 2932 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 495:

/* Line 1455 of yacc.c  */
#line 2938 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 496:

/* Line 1455 of yacc.c  */
#line 2946 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));					
					}
    break;

  case 497:

/* Line 1455 of yacc.c  */
#line 2953 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CWD, "\x99", 1, 0xFF);
					}
    break;

  case 498:

/* Line 1455 of yacc.c  */
#line 2960 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, CDQ, "\x99", 1, 0xFF);
					}
    break;

  case 499:

/* Line 1455 of yacc.c  */
#line 2966 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DAA, "\x27", 1, 0xFF);
					}
    break;

  case 500:

/* Line 1455 of yacc.c  */
#line 2972 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DAS, "\x2F", 1, 0xFF);
					}
    break;

  case 501:

/* Line 1455 of yacc.c  */
#line 2978 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\xFE' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 502:

/* Line 1455 of yacc.c  */
#line 2986 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\xFE' + GetRegisterIndex((yyvsp[(2) - (3)]));
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 503:

/* Line 1455 of yacc.c  */
#line 2994 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\x48' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 0xFF);
					}
    break;

  case 504:

/* Line 1455 of yacc.c  */
#line 3000 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, "\xFF", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 505:

/* Line 1455 of yacc.c  */
#line 3006 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\x48' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 0xFF);
					}
    break;

  case 506:

/* Line 1455 of yacc.c  */
#line 3011 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, "\xFF", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 507:

/* Line 1455 of yacc.c  */
#line 3018 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF6", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 508:

/* Line 1455 of yacc.c  */
#line 3025 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF6", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 509:

/* Line 1455 of yacc.c  */
#line 3030 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 510:

/* Line 1455 of yacc.c  */
#line 3038 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 511:

/* Line 1455 of yacc.c  */
#line 3044 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 512:

/* Line 1455 of yacc.c  */
#line 3051 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 513:

/* Line 1455 of yacc.c  */
#line 3058 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ENTER, "\xC8", 1, 0xFF);
					}
    break;

  case 514:

/* Line 1455 of yacc.c  */
#line 3064 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, HLT, "\xF4", 1, 0xFF);
					}
    break;

  case 515:

/* Line 1455 of yacc.c  */
#line 3070 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF6", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 516:

/* Line 1455 of yacc.c  */
#line 3077 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF6", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 517:

/* Line 1455 of yacc.c  */
#line 3082 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 518:

/* Line 1455 of yacc.c  */
#line 3090 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 519:

/* Line 1455 of yacc.c  */
#line 3096 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 520:

/* Line 1455 of yacc.c  */
#line 3103 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 521:

/* Line 1455 of yacc.c  */
#line 3110 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF6", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;	
					}
    break;

  case 522:

/* Line 1455 of yacc.c  */
#line 3117 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF6", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 523:

/* Line 1455 of yacc.c  */
#line 3123 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 524:

/* Line 1455 of yacc.c  */
#line 3131 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 525:

/* Line 1455 of yacc.c  */
#line 3137 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 526:

/* Line 1455 of yacc.c  */
#line 3144 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 527:

/* Line 1455 of yacc.c  */
#line 3149 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 528:

/* Line 1455 of yacc.c  */
#line 3158 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
					}
    break;

  case 529:

/* Line 1455 of yacc.c  */
#line 3163 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 530:

/* Line 1455 of yacc.c  */
#line 3171 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
					}
    break;

  case 531:

/* Line 1455 of yacc.c  */
#line 3175 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (6)]));
					}
    break;

  case 532:

/* Line 1455 of yacc.c  */
#line 3184 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
					}
    break;

  case 533:

/* Line 1455 of yacc.c  */
#line 3189 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (6)]));
					}
    break;

  case 534:

/* Line 1455 of yacc.c  */
#line 3197 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);					
					}
    break;

  case 535:

/* Line 1455 of yacc.c  */
#line 3202 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (6)]));
					}
    break;

  case 536:

/* Line 1455 of yacc.c  */
#line 3211 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
					}
    break;

  case 537:

/* Line 1455 of yacc.c  */
#line 3216 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (6)]));
					}
    break;

  case 538:

/* Line 1455 of yacc.c  */
#line 3224 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
					}
    break;

  case 539:

/* Line 1455 of yacc.c  */
#line 3230 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE4", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 540:

/* Line 1455 of yacc.c  */
#line 3236 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE5", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 541:

/* Line 1455 of yacc.c  */
#line 3243 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE5", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 542:

/* Line 1455 of yacc.c  */
#line 3249 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xEC", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 543:

/* Line 1455 of yacc.c  */
#line 3256 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xED", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 544:

/* Line 1455 of yacc.c  */
#line 3264 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xED", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);						
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 545:

/* Line 1455 of yacc.c  */
#line 3273 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\xFE' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 546:

/* Line 1455 of yacc.c  */
#line 3281 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\xFE' + GetRegisterIndex((yyvsp[(2) - (3)]));
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 547:

/* Line 1455 of yacc.c  */
#line 3289 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\x40' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0xFF);
					}
    break;

  case 548:

/* Line 1455 of yacc.c  */
#line 3295 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INC, "\xFF", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 549:

/* Line 1455 of yacc.c  */
#line 3301 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpCode = '\x40' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0xFF);
					}
    break;

  case 550:

/* Line 1455 of yacc.c  */
#line 3306 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INC, "\xFF", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 551:

/* Line 1455 of yacc.c  */
#line 3313 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6C", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 552:

/* Line 1455 of yacc.c  */
#line 3320 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6D", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;				
						pCurrAsmObj->bOperandCount = 2;									
					}
    break;

  case 553:

/* Line 1455 of yacc.c  */
#line 3328 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6D", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;				
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 554:

/* Line 1455 of yacc.c  */
#line 3337 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INSB, "\x6C", 1, 0xFF);
					}
    break;

  case 555:

/* Line 1455 of yacc.c  */
#line 3343 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INSW, "\x6D", 1, 0xFF);					
					}
    break;

  case 556:

/* Line 1455 of yacc.c  */
#line 3350 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INSD, "\x6D", 1, 0xFF);
					}
    break;

  case 557:

/* Line 1455 of yacc.c  */
#line 3356 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INT3, "\xCC", 1, 0xFF);						
					}
    break;

  case 558:

/* Line 1455 of yacc.c  */
#line 3362 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INTO, "\xCE", 1, 0xFF);	
					}
    break;

  case 559:

/* Line 1455 of yacc.c  */
#line 3368 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INT, "\xCD", 1, 0xFF);
					}
    break;

  case 560:

/* Line 1455 of yacc.c  */
#line 3374 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INVD, "\x0F\x08", 2, 0xFF);	
					}
    break;

  case 561:

/* Line 1455 of yacc.c  */
#line 3380 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, INVLPG, "\x0F\x01", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 562:

/* Line 1455 of yacc.c  */
#line 3387 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IRET, "\xCF", 1, 0xFF);
					}
    break;

  case 563:

/* Line 1455 of yacc.c  */
#line 3392 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, IRETD, "\xCF", 1, 0xFF);					
					}
    break;

  case 564:

/* Line 1455 of yacc.c  */
#line 3398 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JCXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;						
					}
    break;

  case 565:

/* Line 1455 of yacc.c  */
#line 3403 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JECXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
    break;

  case 566:

/* Line 1455 of yacc.c  */
#line 3408 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JECXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
    break;

  case 567:

/* Line 1455 of yacc.c  */
#line 3413 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JA, "\x0F\x87", 2, 0xFF);	
					}
    break;

  case 568:

/* Line 1455 of yacc.c  */
#line 3417 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JAE, "\x0F\x83", 2, 0xFF);
					}
    break;

  case 569:

/* Line 1455 of yacc.c  */
#line 3421 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JB, "\x0F\x82", 2, 0xFF);
					}
    break;

  case 570:

/* Line 1455 of yacc.c  */
#line 3425 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JB, "\x0F\x86", 2, 0xFF);					
					}
    break;

  case 571:

/* Line 1455 of yacc.c  */
#line 3429 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JC, "\x0F\x82", 2, 0xFF);	
					}
    break;

  case 572:

/* Line 1455 of yacc.c  */
#line 3433 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JE, "\x0F\x84", 2, 0xFF);
					}
    break;

  case 573:

/* Line 1455 of yacc.c  */
#line 3437 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JZ, "\x0F\x84", 2, 0xFF);
					}
    break;

  case 574:

/* Line 1455 of yacc.c  */
#line 3441 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JG, "\x0F\x8F", 2, 0xFF);
					}
    break;

  case 575:

/* Line 1455 of yacc.c  */
#line 3445 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JGE, "\x0F\x8D", 2, 0xFF);
					}
    break;

  case 576:

/* Line 1455 of yacc.c  */
#line 3449 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JL, "\x0F\x8C", 2, 0xFF);
					}
    break;

  case 577:

/* Line 1455 of yacc.c  */
#line 3453 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JLE, "\x0F\x8E", 2, 0xFF);
					}
    break;

  case 578:

/* Line 1455 of yacc.c  */
#line 3457 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNA, "\x0F\x86", 2, 0xFF);
					}
    break;

  case 579:

/* Line 1455 of yacc.c  */
#line 3461 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNAE, "\x0F\x82", 2, 0xFF);					
					}
    break;

  case 580:

/* Line 1455 of yacc.c  */
#line 3465 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNB, "\x0F\x83", 2, 0xFF);
					}
    break;

  case 581:

/* Line 1455 of yacc.c  */
#line 3469 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNBE, "\x0F\x87", 2, 0xFF);
					}
    break;

  case 582:

/* Line 1455 of yacc.c  */
#line 3473 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNC, "\x0F\x83", 2, 0xFF);
					}
    break;

  case 583:

/* Line 1455 of yacc.c  */
#line 3477 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNE, "\x0F\x85", 2, 0xFF);					
					}
    break;

  case 584:

/* Line 1455 of yacc.c  */
#line 3481 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNG, "\x0F\x8E", 2, 0xFF);	
					}
    break;

  case 585:

/* Line 1455 of yacc.c  */
#line 3485 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNGE, "\x0F\x8C", 2, 0xFF);
					}
    break;

  case 586:

/* Line 1455 of yacc.c  */
#line 3489 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNL, "\x0F\x8D", 2, 0xFF);
					}
    break;

  case 587:

/* Line 1455 of yacc.c  */
#line 3493 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNLE, "\x0F\x8F", 2, 0xFF);
					}
    break;

  case 588:

/* Line 1455 of yacc.c  */
#line 3497 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNO, "\x0F\x81", 2, 0xFF);
					}
    break;

  case 589:

/* Line 1455 of yacc.c  */
#line 3501 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNP, "\x0F\x8B", 2, 0xFF);
					}
    break;

  case 590:

/* Line 1455 of yacc.c  */
#line 3505 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNS, "\x0F\x89", 2, 0xFF);
					}
    break;

  case 591:

/* Line 1455 of yacc.c  */
#line 3509 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JNZ, "\x0F\x85", 2, 0xFF);
					}
    break;

  case 592:

/* Line 1455 of yacc.c  */
#line 3513 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JO, "\x0F\x80", 2, 0xFF);
					}
    break;

  case 593:

/* Line 1455 of yacc.c  */
#line 3517 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JP, "\x0F\x8A", 2, 0xFF);
					}
    break;

  case 594:

/* Line 1455 of yacc.c  */
#line 3521 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JPE, "\x0F\x8A", 2, 0xFF);
					}
    break;

  case 595:

/* Line 1455 of yacc.c  */
#line 3525 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JPO, "\x0F\x8B", 2, 0xFF);
					}
    break;

  case 596:

/* Line 1455 of yacc.c  */
#line 3529 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, JS, "\x0F\x88", 2, 0xFF);
					}
    break;

  case 597:

/* Line 1455 of yacc.c  */
#line 3536 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
    break;

  case 598:

/* Line 1455 of yacc.c  */
#line 3540 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xEB", 1, 0xFF);
					}
    break;

  case 599:

/* Line 1455 of yacc.c  */
#line 3544 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
    break;

  case 600:

/* Line 1455 of yacc.c  */
#line 3549 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
    break;

  case 601:

/* Line 1455 of yacc.c  */
#line 3553 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 4;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 602:

/* Line 1455 of yacc.c  */
#line 3562 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 4;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 603:

/* Line 1455 of yacc.c  */
#line 3570 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);			    
					    pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 604:

/* Line 1455 of yacc.c  */
#line 3576 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);			    
					    pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 605:

/* Line 1455 of yacc.c  */
#line 3583 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LAHF, "\x9F", 1, 0xFF);
					}
    break;

  case 606:

/* Line 1455 of yacc.c  */
#line 3589 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 607:

/* Line 1455 of yacc.c  */
#line 3598 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 608:

/* Line 1455 of yacc.c  */
#line 3604 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 609:

/* Line 1455 of yacc.c  */
#line 3612 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 610:

/* Line 1455 of yacc.c  */
#line 3619 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LDS, "\xC5", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 611:

/* Line 1455 of yacc.c  */
#line 3625 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LDS, "\xC5", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 612:

/* Line 1455 of yacc.c  */
#line 3632 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSS, "\x0F\xB2", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 613:

/* Line 1455 of yacc.c  */
#line 3638 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LSS, "\x0F\xB2", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 614:

/* Line 1455 of yacc.c  */
#line 3645 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LES, "\xC4", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 615:

/* Line 1455 of yacc.c  */
#line 3651 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LES, "\xC4", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 616:

/* Line 1455 of yacc.c  */
#line 3658 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LFS, "\x0F\xB4", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 617:

/* Line 1455 of yacc.c  */
#line 3664 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LFS, "\x0F\xB4", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 618:

/* Line 1455 of yacc.c  */
#line 3671 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LGS, "\x0F\xB5", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 619:

/* Line 1455 of yacc.c  */
#line 3677 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LGS, "\x0F\xB5", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 620:

/* Line 1455 of yacc.c  */
#line 3684 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LEA, "\x8D", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 621:

/* Line 1455 of yacc.c  */
#line 3690 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LEA, "\x8D", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 622:

/* Line 1455 of yacc.c  */
#line 3697 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LEAVE, "\xC9", 1, 0xFF);
					}
    break;

  case 623:

/* Line 1455 of yacc.c  */
#line 3703 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LFENCE, "\x0F\xAE", 2, 5);
					    pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 624:

/* Line 1455 of yacc.c  */
#line 3710 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LGDT, "\x0F\x01", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 625:

/* Line 1455 of yacc.c  */
#line 3716 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LGDT, "\x0F\x01", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 626:

/* Line 1455 of yacc.c  */
#line 3723 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LIDT, "\x0F\x01", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 627:

/* Line 1455 of yacc.c  */
#line 3729 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LIDT, "\x0F\x01", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 628:

/* Line 1455 of yacc.c  */
#line 3736 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LLDT, "\x0F\x00", 2, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 629:

/* Line 1455 of yacc.c  */
#line 3744 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LLDT, "\x0F\x00", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 630:

/* Line 1455 of yacc.c  */
#line 3751 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LMSW, "\x0F\x01", 2, 6);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 6;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 631:

/* Line 1455 of yacc.c  */
#line 3759 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LMSW, "\x0F\x01", 2, 6);
					    pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 632:

/* Line 1455 of yacc.c  */
#line 3766 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSB, "\xAC", 1, 0xFF);
					}
    break;

  case 633:

/* Line 1455 of yacc.c  */
#line 3772 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSW, "\xAD", 1, 0xFF);
					}
    break;

  case 634:

/* Line 1455 of yacc.c  */
#line 3779 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSD, "\xAD", 1, 0xFF);
					}
    break;

  case 635:

/* Line 1455 of yacc.c  */
#line 3785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOP, "\xE2", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
    break;

  case 636:

/* Line 1455 of yacc.c  */
#line 3792 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOPE, "\xE1", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
    break;

  case 637:

/* Line 1455 of yacc.c  */
#line 3799 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOPNE, "\xE0", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
    break;

  case 638:

/* Line 1455 of yacc.c  */
#line 3806 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 639:

/* Line 1455 of yacc.c  */
#line 3815 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 640:

/* Line 1455 of yacc.c  */
#line 3821 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 641:

/* Line 1455 of yacc.c  */
#line 3830 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 642:

/* Line 1455 of yacc.c  */
#line 3837 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x00", 2, 3);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.RO = 3;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 643:

/* Line 1455 of yacc.c  */
#line 3844 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x00", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 644:

/* Line 1455 of yacc.c  */
#line 3851 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MFENCE, "\x0F\xAE", 2, 6);
					    pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 645:

/* Line 1455 of yacc.c  */
#line 3858 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MONITOR, "\x0F\x01\xC8", 3, 0xFF);						
					}
    break;

  case 646:

/* Line 1455 of yacc.c  */
#line 3864 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\xB0' + GetRegisterIndex((yyvsp[(2) - (4)]));
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
    break;

  case 647:

/* Line 1455 of yacc.c  */
#line 3869 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC6", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 648:

/* Line 1455 of yacc.c  */
#line 3874 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\xB8' + GetRegisterIndex((yyvsp[(2) - (4)]));
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
    break;

  case 649:

/* Line 1455 of yacc.c  */
#line 3880 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 650:

/* Line 1455 of yacc.c  */
#line 3886 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\xB8' + GetRegisterIndex((yyvsp[(2) - (4)]));
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
    break;

  case 651:

/* Line 1455 of yacc.c  */
#line 3891 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 652:

/* Line 1455 of yacc.c  */
#line 3896 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x88", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 653:

/* Line 1455 of yacc.c  */
#line 3904 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x88", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 654:

/* Line 1455 of yacc.c  */
#line 3909 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 655:

/* Line 1455 of yacc.c  */
#line 3918 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 656:

/* Line 1455 of yacc.c  */
#line 3924 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 657:

/* Line 1455 of yacc.c  */
#line 3932 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 658:

/* Line 1455 of yacc.c  */
#line 3937 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 659:

/* Line 1455 of yacc.c  */
#line 3942 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 660:

/* Line 1455 of yacc.c  */
#line 3948 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 661:

/* Line 1455 of yacc.c  */
#line 3953 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8C", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 662:

/* Line 1455 of yacc.c  */
#line 3961 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8C", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 663:

/* Line 1455 of yacc.c  */
#line 3967 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8E", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 664:

/* Line 1455 of yacc.c  */
#line 3975 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8E", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 665:

/* Line 1455 of yacc.c  */
#line 3981 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x20", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));	
					}
    break;

  case 666:

/* Line 1455 of yacc.c  */
#line 3989 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x22", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 667:

/* Line 1455 of yacc.c  */
#line 3997 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x21", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 668:

/* Line 1455 of yacc.c  */
#line 4005 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x23", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 669:

/* Line 1455 of yacc.c  */
#line 4015 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF0", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 670:

/* Line 1455 of yacc.c  */
#line 4021 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF1", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 671:

/* Line 1455 of yacc.c  */
#line 4027 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF0", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 672:

/* Line 1455 of yacc.c  */
#line 4032 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF1", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 673:

/* Line 1455 of yacc.c  */
#line 4039 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSB, "\xA4", 1, 0xFF);
					}
    break;

  case 674:

/* Line 1455 of yacc.c  */
#line 4045 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSW, "\xA5", 1, 0xFF);
					}
    break;

  case 675:

/* Line 1455 of yacc.c  */
#line 4052 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSD, "\xA5", 1, 0xFF);
					}
    break;

  case 676:

/* Line 1455 of yacc.c  */
#line 4058 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 677:

/* Line 1455 of yacc.c  */
#line 4067 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 678:

/* Line 1455 of yacc.c  */
#line 4073 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 679:

/* Line 1455 of yacc.c  */
#line 4081 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 680:

/* Line 1455 of yacc.c  */
#line 4086 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBF", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 681:

/* Line 1455 of yacc.c  */
#line 4094 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBF", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 682:

/* Line 1455 of yacc.c  */
#line 4101 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 683:

/* Line 1455 of yacc.c  */
#line 4110 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 684:

/* Line 1455 of yacc.c  */
#line 4116 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 685:

/* Line 1455 of yacc.c  */
#line 4124 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 686:

/* Line 1455 of yacc.c  */
#line 4129 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB7", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 687:

/* Line 1455 of yacc.c  */
#line 4137 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB7", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 688:

/* Line 1455 of yacc.c  */
#line 4144 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF6", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 689:

/* Line 1455 of yacc.c  */
#line 4152 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF6", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 690:

/* Line 1455 of yacc.c  */
#line 4157 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 691:

/* Line 1455 of yacc.c  */
#line 4166 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 692:

/* Line 1455 of yacc.c  */
#line 4172 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 693:

/* Line 1455 of yacc.c  */
#line 4180 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 694:

/* Line 1455 of yacc.c  */
#line 4187 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, MWAIT, "\x0F\x01\xC9", 3, 0xFF);
					}
    break;

  case 695:

/* Line 1455 of yacc.c  */
#line 4193 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF6", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 696:

/* Line 1455 of yacc.c  */
#line 4201 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF6", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 697:

/* Line 1455 of yacc.c  */
#line 4206 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 698:

/* Line 1455 of yacc.c  */
#line 4215 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 699:

/* Line 1455 of yacc.c  */
#line 4221 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 700:

/* Line 1455 of yacc.c  */
#line 4229 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 701:

/* Line 1455 of yacc.c  */
#line 4236 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x90", 1, 0xFF);
					}
    break;

  case 702:

/* Line 1455 of yacc.c  */
#line 4240 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 703:

/* Line 1455 of yacc.c  */
#line 4249 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 704:

/* Line 1455 of yacc.c  */
#line 4255 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 705:

/* Line 1455 of yacc.c  */
#line 4263 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 706:

/* Line 1455 of yacc.c  */
#line 4270 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF6", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 707:

/* Line 1455 of yacc.c  */
#line 4278 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF6", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 708:

/* Line 1455 of yacc.c  */
#line 4283 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 709:

/* Line 1455 of yacc.c  */
#line 4292 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 710:

/* Line 1455 of yacc.c  */
#line 4298 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 711:

/* Line 1455 of yacc.c  */
#line 4306 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 712:

/* Line 1455 of yacc.c  */
#line 4313 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x80", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 713:

/* Line 1455 of yacc.c  */
#line 4325 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x80", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 714:

/* Line 1455 of yacc.c  */
#line 4330 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 715:

/* Line 1455 of yacc.c  */
#line 4343 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 716:

/* Line 1455 of yacc.c  */
#line 4349 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 717:

/* Line 1455 of yacc.c  */
#line 4361 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 718:

/* Line 1455 of yacc.c  */
#line 4366 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 719:

/* Line 1455 of yacc.c  */
#line 4372 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 720:

/* Line 1455 of yacc.c  */
#line 4377 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 721:

/* Line 1455 of yacc.c  */
#line 4382 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 722:

/* Line 1455 of yacc.c  */
#line 4387 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x08", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 723:

/* Line 1455 of yacc.c  */
#line 4395 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x08", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 724:

/* Line 1455 of yacc.c  */
#line 4400 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 725:

/* Line 1455 of yacc.c  */
#line 4409 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 726:

/* Line 1455 of yacc.c  */
#line 4415 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 727:

/* Line 1455 of yacc.c  */
#line 4423 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 728:

/* Line 1455 of yacc.c  */
#line 4428 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 729:

/* Line 1455 of yacc.c  */
#line 4433 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 730:

/* Line 1455 of yacc.c  */
#line 4439 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 731:

/* Line 1455 of yacc.c  */
#line 4447 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE6", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 732:

/* Line 1455 of yacc.c  */
#line 4453 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE7", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 733:

/* Line 1455 of yacc.c  */
#line 4460 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE7", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 734:

/* Line 1455 of yacc.c  */
#line 4466 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEE", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 735:

/* Line 1455 of yacc.c  */
#line 4473 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEF", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 736:

/* Line 1455 of yacc.c  */
#line 4481 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEF", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 737:

/* Line 1455 of yacc.c  */
#line 4490 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 738:

/* Line 1455 of yacc.c  */
#line 4497 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 739:

/* Line 1455 of yacc.c  */
#line 4505 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 740:

/* Line 1455 of yacc.c  */
#line 4514 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSB, "\x6E", 1, 0xFF);					
					}
    break;

  case 741:

/* Line 1455 of yacc.c  */
#line 4520 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSW, "\x6F", 1, 0xFF);
					}
    break;

  case 742:

/* Line 1455 of yacc.c  */
#line 4527 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSD, "\x6F", 1, 0xFF);
					}
    break;

  case 743:

/* Line 1455 of yacc.c  */
#line 4534 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PAUSE, "\xF3\x90", 2, 0xFF);
					}
    break;

  case 744:

/* Line 1455 of yacc.c  */
#line 4540 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\x58' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POP, &bOpcode, 1, 0xFF);	
					}
    break;

  case 745:

/* Line 1455 of yacc.c  */
#line 4546 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x8F", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 746:

/* Line 1455 of yacc.c  */
#line 4552 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\x58' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, POP, &bOpcode, 1, 0xFF);
					}
    break;

  case 747:

/* Line 1455 of yacc.c  */
#line 4557 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x8F", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 748:

/* Line 1455 of yacc.c  */
#line 4562 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x1F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_DS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 749:

/* Line 1455 of yacc.c  */
#line 4568 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x07", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_ES, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 750:

/* Line 1455 of yacc.c  */
#line 4574 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x17", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_SS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 751:

/* Line 1455 of yacc.c  */
#line 4580 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x0F\xA1", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_FS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 752:

/* Line 1455 of yacc.c  */
#line 4586 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x0F\xA9", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_GS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 753:

/* Line 1455 of yacc.c  */
#line 4594 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPA, "\x61", 1, 0xFF);
					}
    break;

  case 754:

/* Line 1455 of yacc.c  */
#line 4601 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POPAD, "\x61", 1, 0xFF);
					}
    break;

  case 755:

/* Line 1455 of yacc.c  */
#line 4607 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 756:

/* Line 1455 of yacc.c  */
#line 4616 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 757:

/* Line 1455 of yacc.c  */
#line 4622 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
					}
    break;

  case 758:

/* Line 1455 of yacc.c  */
#line 4630 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 759:

/* Line 1455 of yacc.c  */
#line 4637 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPF, "\x9D", 1, 0xFF);
					}
    break;

  case 760:

/* Line 1455 of yacc.c  */
#line 4644 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, POPFD, "\x9D", 1, 0xFF);
					}
    break;

  case 761:

/* Line 1455 of yacc.c  */
#line 4650 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT0, "\x0F\x18", 2, 1);
							pCurrAsmObj->ModRM.RO = 1;
						}
    break;

  case 762:

/* Line 1455 of yacc.c  */
#line 4657 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT1, "\x0F\x18", 2, 2);
							pCurrAsmObj->ModRM.RO = 2;
						}
    break;

  case 763:

/* Line 1455 of yacc.c  */
#line 4664 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT2, "\x0F\x18", 2, 3);
							pCurrAsmObj->ModRM.RO = 3;
						}
    break;

  case 764:

/* Line 1455 of yacc.c  */
#line 4671 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHNTA, "\x0F\x18", 2, 0);
							pCurrAsmObj->ModRM.RO = 0;
						}
    break;

  case 765:

/* Line 1455 of yacc.c  */
#line 4678 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\x50' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, &bOpcode, 1, 0xFF);	
					}
    break;

  case 766:

/* Line 1455 of yacc.c  */
#line 4684 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\xFF", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 767:

/* Line 1455 of yacc.c  */
#line 4690 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = '\x50' + GetRegisterIndex((yyvsp[(2) - (2)]));
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, &bOpcode, 1, 0xFF);	
					}
    break;

  case 768:

/* Line 1455 of yacc.c  */
#line 4695 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\xFF", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 769:

/* Line 1455 of yacc.c  */
#line 4700 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x6A", 1, 0xFF);
					}
    break;

  case 770:

/* Line 1455 of yacc.c  */
#line 4704 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x68", 1, 0xFF);
					}
    break;

  case 771:

/* Line 1455 of yacc.c  */
#line 4709 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x68", 1, 0xFF);
					}
    break;

  case 772:

/* Line 1455 of yacc.c  */
#line 4713 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_CS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 773:

/* Line 1455 of yacc.c  */
#line 4719 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x1E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_DS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 774:

/* Line 1455 of yacc.c  */
#line 4725 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x06", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_ES, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 775:

/* Line 1455 of yacc.c  */
#line 4731 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x16", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_SS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 776:

/* Line 1455 of yacc.c  */
#line 4737 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0F\xA0", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_FS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 777:

/* Line 1455 of yacc.c  */
#line 4743 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0F\xA8", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_GS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
    break;

  case 778:

/* Line 1455 of yacc.c  */
#line 4751 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHA, "\x60", 1, 0xFF);
					}
    break;

  case 779:

/* Line 1455 of yacc.c  */
#line 4758 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHAD, "\x60", 1, 0xFF);
					}
    break;

  case 780:

/* Line 1455 of yacc.c  */
#line 4764 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHF, "\x9C", 1, 0xFF);
					}
    break;

  case 781:

/* Line 1455 of yacc.c  */
#line 4771 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHFD, "\x9C", 1, 0xFF);
					}
    break;

  case 782:

/* Line 1455 of yacc.c  */
#line 4777 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC0", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 783:

/* Line 1455 of yacc.c  */
#line 4785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 784:

/* Line 1455 of yacc.c  */
#line 4794 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 785:

/* Line 1455 of yacc.c  */
#line 4802 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC0", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 786:

/* Line 1455 of yacc.c  */
#line 4807 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 787:

/* Line 1455 of yacc.c  */
#line 4813 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    break;

  case 788:

/* Line 1455 of yacc.c  */
#line 4818 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD2", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 789:

/* Line 1455 of yacc.c  */
#line 4828 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 790:

/* Line 1455 of yacc.c  */
#line 4839 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 791:

/* Line 1455 of yacc.c  */
#line 4849 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD2", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 792:

/* Line 1455 of yacc.c  */
#line 4856 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 793:

/* Line 1455 of yacc.c  */
#line 4864 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 794:

/* Line 1455 of yacc.c  */
#line 4873 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC0", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 795:

/* Line 1455 of yacc.c  */
#line 4881 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 796:

/* Line 1455 of yacc.c  */
#line 4890 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 797:

/* Line 1455 of yacc.c  */
#line 4898 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC0", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 798:

/* Line 1455 of yacc.c  */
#line 4903 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 799:

/* Line 1455 of yacc.c  */
#line 4909 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 800:

/* Line 1455 of yacc.c  */
#line 4914 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD2", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 801:

/* Line 1455 of yacc.c  */
#line 4924 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 802:

/* Line 1455 of yacc.c  */
#line 4935 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 803:

/* Line 1455 of yacc.c  */
#line 4945 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD2", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 804:

/* Line 1455 of yacc.c  */
#line 4952 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 805:

/* Line 1455 of yacc.c  */
#line 4960 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 806:

/* Line 1455 of yacc.c  */
#line 4969 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC0", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 807:

/* Line 1455 of yacc.c  */
#line 4977 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 808:

/* Line 1455 of yacc.c  */
#line 4986 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 809:

/* Line 1455 of yacc.c  */
#line 4994 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC0", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 810:

/* Line 1455 of yacc.c  */
#line 4999 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 811:

/* Line 1455 of yacc.c  */
#line 5005 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 812:

/* Line 1455 of yacc.c  */
#line 5010 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD2", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 813:

/* Line 1455 of yacc.c  */
#line 5020 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 814:

/* Line 1455 of yacc.c  */
#line 5031 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 815:

/* Line 1455 of yacc.c  */
#line 5041 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD2", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 816:

/* Line 1455 of yacc.c  */
#line 5048 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 817:

/* Line 1455 of yacc.c  */
#line 5056 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 818:

/* Line 1455 of yacc.c  */
#line 5065 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC0", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 819:

/* Line 1455 of yacc.c  */
#line 5073 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 820:

/* Line 1455 of yacc.c  */
#line 5082 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 821:

/* Line 1455 of yacc.c  */
#line 5090 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC0", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 822:

/* Line 1455 of yacc.c  */
#line 5095 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 823:

/* Line 1455 of yacc.c  */
#line 5101 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 824:

/* Line 1455 of yacc.c  */
#line 5106 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD2", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 825:

/* Line 1455 of yacc.c  */
#line 5116 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 826:

/* Line 1455 of yacc.c  */
#line 5127 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 827:

/* Line 1455 of yacc.c  */
#line 5137 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD2", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 828:

/* Line 1455 of yacc.c  */
#line 5144 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 829:

/* Line 1455 of yacc.c  */
#line 5152 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 830:

/* Line 1455 of yacc.c  */
#line 5161 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RDMSR, "\x0F\x32", 2, 0xFF);
					}
    break;

  case 831:

/* Line 1455 of yacc.c  */
#line 5167 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RDPMC, "\x0F\x33", 2, 0xFF);
					}
    break;

  case 832:

/* Line 1455 of yacc.c  */
#line 5173 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RDTSC, "\x0F\x31", 2, 0xFF);
					}
    break;

  case 833:

/* Line 1455 of yacc.c  */
#line 5179 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RDTSCP, "\x0F\x01\xF9", 3, 0xFF);
					}
    break;

  case 834:

/* Line 1455 of yacc.c  */
#line 5185 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RET, "\xC3", 1, 0xFF);
					}
    break;

  case 835:

/* Line 1455 of yacc.c  */
#line 5191 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RETN, "\xC2", 1, 0xFF);
					}
    break;

  case 836:

/* Line 1455 of yacc.c  */
#line 5197 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, RSM, "\x0F\xAA", 2, 0xFF);
					}
    break;

  case 837:

/* Line 1455 of yacc.c  */
#line 5203 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAHF, "\x9E", 1, 0xFF);
					}
    break;

  case 838:

/* Line 1455 of yacc.c  */
#line 5209 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC0", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 839:

/* Line 1455 of yacc.c  */
#line 5217 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 840:

/* Line 1455 of yacc.c  */
#line 5226 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 841:

/* Line 1455 of yacc.c  */
#line 5234 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC0", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 842:

/* Line 1455 of yacc.c  */
#line 5239 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 843:

/* Line 1455 of yacc.c  */
#line 5245 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 844:

/* Line 1455 of yacc.c  */
#line 5250 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 845:

/* Line 1455 of yacc.c  */
#line 5260 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 846:

/* Line 1455 of yacc.c  */
#line 5271 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 847:

/* Line 1455 of yacc.c  */
#line 5281 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 848:

/* Line 1455 of yacc.c  */
#line 5288 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 849:

/* Line 1455 of yacc.c  */
#line 5296 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 850:

/* Line 1455 of yacc.c  */
#line 5305 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC0", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 851:

/* Line 1455 of yacc.c  */
#line 5313 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 852:

/* Line 1455 of yacc.c  */
#line 5322 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 853:

/* Line 1455 of yacc.c  */
#line 5330 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC0", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 854:

/* Line 1455 of yacc.c  */
#line 5335 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 855:

/* Line 1455 of yacc.c  */
#line 5341 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 856:

/* Line 1455 of yacc.c  */
#line 5346 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD2", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 857:

/* Line 1455 of yacc.c  */
#line 5356 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 858:

/* Line 1455 of yacc.c  */
#line 5367 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 859:

/* Line 1455 of yacc.c  */
#line 5377 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD2", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 860:

/* Line 1455 of yacc.c  */
#line 5384 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 861:

/* Line 1455 of yacc.c  */
#line 5392 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 862:

/* Line 1455 of yacc.c  */
#line 5401 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC0", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 863:

/* Line 1455 of yacc.c  */
#line 5409 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 864:

/* Line 1455 of yacc.c  */
#line 5418 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 865:

/* Line 1455 of yacc.c  */
#line 5426 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC0", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 866:

/* Line 1455 of yacc.c  */
#line 5431 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 867:

/* Line 1455 of yacc.c  */
#line 5437 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 868:

/* Line 1455 of yacc.c  */
#line 5442 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 869:

/* Line 1455 of yacc.c  */
#line 5452 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 870:

/* Line 1455 of yacc.c  */
#line 5463 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 871:

/* Line 1455 of yacc.c  */
#line 5473 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 872:

/* Line 1455 of yacc.c  */
#line 5480 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 873:

/* Line 1455 of yacc.c  */
#line 5488 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 874:

/* Line 1455 of yacc.c  */
#line 5497 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC0", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 875:

/* Line 1455 of yacc.c  */
#line 5505 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 876:

/* Line 1455 of yacc.c  */
#line 5514 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 877:

/* Line 1455 of yacc.c  */
#line 5522 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC0", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 878:

/* Line 1455 of yacc.c  */
#line 5527 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 879:

/* Line 1455 of yacc.c  */
#line 5533 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 880:

/* Line 1455 of yacc.c  */
#line 5538 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD2", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 881:

/* Line 1455 of yacc.c  */
#line 5548 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 882:

/* Line 1455 of yacc.c  */
#line 5559 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 883:

/* Line 1455 of yacc.c  */
#line 5569 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD2", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 884:

/* Line 1455 of yacc.c  */
#line 5576 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 885:

/* Line 1455 of yacc.c  */
#line 5584 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
    break;

  case 886:

/* Line 1455 of yacc.c  */
#line 5593 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x80", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 887:

/* Line 1455 of yacc.c  */
#line 5605 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x80", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 888:

/* Line 1455 of yacc.c  */
#line 5610 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 889:

/* Line 1455 of yacc.c  */
#line 5623 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 890:

/* Line 1455 of yacc.c  */
#line 5629 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 891:

/* Line 1455 of yacc.c  */
#line 5641 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 892:

/* Line 1455 of yacc.c  */
#line 5646 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 893:

/* Line 1455 of yacc.c  */
#line 5652 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 894:

/* Line 1455 of yacc.c  */
#line 5657 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 895:

/* Line 1455 of yacc.c  */
#line 5662 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 896:

/* Line 1455 of yacc.c  */
#line 5667 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x18", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 897:

/* Line 1455 of yacc.c  */
#line 5675 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x18", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 898:

/* Line 1455 of yacc.c  */
#line 5680 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 899:

/* Line 1455 of yacc.c  */
#line 5689 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 900:

/* Line 1455 of yacc.c  */
#line 5695 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 901:

/* Line 1455 of yacc.c  */
#line 5703 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 902:

/* Line 1455 of yacc.c  */
#line 5708 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 903:

/* Line 1455 of yacc.c  */
#line 5713 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 904:

/* Line 1455 of yacc.c  */
#line 5719 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 905:

/* Line 1455 of yacc.c  */
#line 5726 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASB, "\xAE", 1, 0xFF);
					}
    break;

  case 906:

/* Line 1455 of yacc.c  */
#line 5732 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASW, "\xAF", 1, 0xFF);
					}
    break;

  case 907:

/* Line 1455 of yacc.c  */
#line 5739 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASD, "\xAF", 1, 0xFF);
					}
    break;

  case 908:

/* Line 1455 of yacc.c  */
#line 5744 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETA; }
    break;

  case 909:

/* Line 1455 of yacc.c  */
#line 5745 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETAE; }
    break;

  case 910:

/* Line 1455 of yacc.c  */
#line 5746 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETB; }
    break;

  case 911:

/* Line 1455 of yacc.c  */
#line 5747 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETBE; }
    break;

  case 912:

/* Line 1455 of yacc.c  */
#line 5748 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETC; }
    break;

  case 913:

/* Line 1455 of yacc.c  */
#line 5749 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETE; }
    break;

  case 914:

/* Line 1455 of yacc.c  */
#line 5750 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETG; }
    break;

  case 915:

/* Line 1455 of yacc.c  */
#line 5751 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETGE; }
    break;

  case 916:

/* Line 1455 of yacc.c  */
#line 5752 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETL; }
    break;

  case 917:

/* Line 1455 of yacc.c  */
#line 5753 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETLE; }
    break;

  case 918:

/* Line 1455 of yacc.c  */
#line 5754 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNA; }
    break;

  case 919:

/* Line 1455 of yacc.c  */
#line 5755 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNAE; }
    break;

  case 920:

/* Line 1455 of yacc.c  */
#line 5756 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNB; }
    break;

  case 921:

/* Line 1455 of yacc.c  */
#line 5757 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNBE; }
    break;

  case 922:

/* Line 1455 of yacc.c  */
#line 5758 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNC; }
    break;

  case 923:

/* Line 1455 of yacc.c  */
#line 5759 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNE; }
    break;

  case 924:

/* Line 1455 of yacc.c  */
#line 5760 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNG; }
    break;

  case 925:

/* Line 1455 of yacc.c  */
#line 5761 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNGE; }
    break;

  case 926:

/* Line 1455 of yacc.c  */
#line 5762 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNL; }
    break;

  case 927:

/* Line 1455 of yacc.c  */
#line 5763 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNLE; }
    break;

  case 928:

/* Line 1455 of yacc.c  */
#line 5764 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNO; }
    break;

  case 929:

/* Line 1455 of yacc.c  */
#line 5765 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNP; }
    break;

  case 930:

/* Line 1455 of yacc.c  */
#line 5766 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNS; }
    break;

  case 931:

/* Line 1455 of yacc.c  */
#line 5767 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETNZ; }
    break;

  case 932:

/* Line 1455 of yacc.c  */
#line 5768 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETO; }
    break;

  case 933:

/* Line 1455 of yacc.c  */
#line 5769 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETP; }
    break;

  case 934:

/* Line 1455 of yacc.c  */
#line 5770 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETPE; }
    break;

  case 935:

/* Line 1455 of yacc.c  */
#line 5771 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETPO; }
    break;

  case 936:

/* Line 1455 of yacc.c  */
#line 5772 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETS; }
    break;

  case 937:

/* Line 1455 of yacc.c  */
#line 5773 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SETZ; }
    break;

  case 938:

/* Line 1455 of yacc.c  */
#line 5778 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETA, "\x0F\x97", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 939:

/* Line 1455 of yacc.c  */
#line 5785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETA, "\x0F\x97", 2, 0xFF);
					}
    break;

  case 940:

/* Line 1455 of yacc.c  */
#line 5791 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETAE, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 941:

/* Line 1455 of yacc.c  */
#line 5798 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETAE, "\x0F\x93", 2, 0xFF);
					}
    break;

  case 942:

/* Line 1455 of yacc.c  */
#line 5804 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETB, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 943:

/* Line 1455 of yacc.c  */
#line 5811 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETB, "\x0F\x92", 2, 0xFF);
					}
    break;

  case 944:

/* Line 1455 of yacc.c  */
#line 5817 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETBE, "\x0F\x96", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 945:

/* Line 1455 of yacc.c  */
#line 5824 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETBE, "\x0F\x96", 2, 0xFF);
					}
    break;

  case 946:

/* Line 1455 of yacc.c  */
#line 5830 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 947:

/* Line 1455 of yacc.c  */
#line 5837 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x92", 2, 0xFF);
					}
    break;

  case 948:

/* Line 1455 of yacc.c  */
#line 5843 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x94", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 949:

/* Line 1455 of yacc.c  */
#line 5850 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x94", 2, 0xFF);
					}
    break;

  case 950:

/* Line 1455 of yacc.c  */
#line 5856 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETG, "\x0F\x9F", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 951:

/* Line 1455 of yacc.c  */
#line 5863 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETG, "\x0F\x9F", 2, 0xFF);
					}
    break;

  case 952:

/* Line 1455 of yacc.c  */
#line 5869 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETGE, "\x0F\x9D", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 953:

/* Line 1455 of yacc.c  */
#line 5876 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETGE, "\x0F\x9D", 2, 0xFF);
					}
    break;

  case 954:

/* Line 1455 of yacc.c  */
#line 5882 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9C", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 955:

/* Line 1455 of yacc.c  */
#line 5889 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9C", 2, 0xFF);
					}
    break;

  case 956:

/* Line 1455 of yacc.c  */
#line 5895 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9E", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 957:

/* Line 1455 of yacc.c  */
#line 5902 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9E", 2, 0xFF);
					}
    break;

  case 958:

/* Line 1455 of yacc.c  */
#line 5908 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNA, "\x0F\x96", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 959:

/* Line 1455 of yacc.c  */
#line 5915 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNA, "\x0F\x96", 2, 0xFF);
					}
    break;

  case 960:

/* Line 1455 of yacc.c  */
#line 5921 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNAE, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 961:

/* Line 1455 of yacc.c  */
#line 5928 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNAE, "\x0F\x92", 2, 0xFF);
					}
    break;

  case 962:

/* Line 1455 of yacc.c  */
#line 5934 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNB, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 963:

/* Line 1455 of yacc.c  */
#line 5941 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNB, "\x0F\x93", 2, 0xFF);
					}
    break;

  case 964:

/* Line 1455 of yacc.c  */
#line 5947 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNBE, "\x0F\x97", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 965:

/* Line 1455 of yacc.c  */
#line 5954 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNBE, "\x0F\x97", 2, 0xFF);
					}
    break;

  case 966:

/* Line 1455 of yacc.c  */
#line 5960 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNC, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 967:

/* Line 1455 of yacc.c  */
#line 5967 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNC, "\x0F\x93", 2, 0xFF);
					}
    break;

  case 968:

/* Line 1455 of yacc.c  */
#line 5973 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNE, "\x0F\x95", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 969:

/* Line 1455 of yacc.c  */
#line 5980 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNE, "\x0F\x95", 2, 0xFF);
					}
    break;

  case 970:

/* Line 1455 of yacc.c  */
#line 5986 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNG, "\x0F\x9E", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 971:

/* Line 1455 of yacc.c  */
#line 5993 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNG, "\x0F\x9E", 2, 0xFF);
					}
    break;

  case 972:

/* Line 1455 of yacc.c  */
#line 5999 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNGE, "\x0F\x9C", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 973:

/* Line 1455 of yacc.c  */
#line 6006 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNGE, "\x0F\x9C", 2, 0xFF);
					}
    break;

  case 974:

/* Line 1455 of yacc.c  */
#line 6012 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNL, "\x0F\x9D", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 975:

/* Line 1455 of yacc.c  */
#line 6019 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNL, "\x0F\x9D", 2, 0xFF);
					}
    break;

  case 976:

/* Line 1455 of yacc.c  */
#line 6025 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNLE, "\x0F\x9F", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 977:

/* Line 1455 of yacc.c  */
#line 6032 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNLE, "\x0F\x9F", 2, 0xFF);
					}
    break;

  case 978:

/* Line 1455 of yacc.c  */
#line 6038 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNO, "\x0F\x91", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 979:

/* Line 1455 of yacc.c  */
#line 6045 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNO, "\x0F\x91", 2, 0xFF);
					}
    break;

  case 980:

/* Line 1455 of yacc.c  */
#line 6051 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNP, "\x0F\x9B", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 981:

/* Line 1455 of yacc.c  */
#line 6058 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNP, "\x0F\x9B", 2, 0xFF);
					}
    break;

  case 982:

/* Line 1455 of yacc.c  */
#line 6064 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNS, "\x0F\x99", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 983:

/* Line 1455 of yacc.c  */
#line 6071 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNS, "\x0F\x99", 2, 0xFF);
					}
    break;

  case 984:

/* Line 1455 of yacc.c  */
#line 6077 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNZ, "\x0F\x95", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 985:

/* Line 1455 of yacc.c  */
#line 6084 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNZ, "\x0F\x95", 2, 0xFF);
					}
    break;

  case 986:

/* Line 1455 of yacc.c  */
#line 6090 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETO, "\x0F\x90", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 987:

/* Line 1455 of yacc.c  */
#line 6097 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETO, "\x0F\x90", 2, 0xFF);
					}
    break;

  case 988:

/* Line 1455 of yacc.c  */
#line 6103 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETP, "\x0F\x9A", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 989:

/* Line 1455 of yacc.c  */
#line 6110 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETP, "\x0F\x9A", 2, 0xFF);
					}
    break;

  case 990:

/* Line 1455 of yacc.c  */
#line 6116 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPE, "\x0F\x9A", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 991:

/* Line 1455 of yacc.c  */
#line 6123 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPE, "\x0F\x9A", 2, 0xFF);
					}
    break;

  case 992:

/* Line 1455 of yacc.c  */
#line 6129 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPO, "\x0F\x9B", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 993:

/* Line 1455 of yacc.c  */
#line 6136 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPO, "\x0F\x9B", 2, 0xFF);
					}
    break;

  case 994:

/* Line 1455 of yacc.c  */
#line 6142 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETS, "\x0F\x98", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 995:

/* Line 1455 of yacc.c  */
#line 6149 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETS, "\x0F\x98", 2, 0xFF);
					}
    break;

  case 996:

/* Line 1455 of yacc.c  */
#line 6155 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETZ, "\x0F\x94", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 997:

/* Line 1455 of yacc.c  */
#line 6162 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SETZ, "\x0F\x94", 2, 0xFF);
					}
    break;

  case 998:

/* Line 1455 of yacc.c  */
#line 6168 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SFENCE, "\x0F\xAE", 2, 7);
					    pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 999:

/* Line 1455 of yacc.c  */
#line 6175 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SGDT, "\x0F\x01", 2, 0);
					    pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 1000:

/* Line 1455 of yacc.c  */
#line 6182 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
					}
    break;

  case 1001:

/* Line 1455 of yacc.c  */
#line 6191 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
					}
    break;

  case 1002:

/* Line 1455 of yacc.c  */
#line 6197 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1003:

/* Line 1455 of yacc.c  */
#line 6208 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1004:

/* Line 1455 of yacc.c  */
#line 6216 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
					}
    break;

  case 1005:

/* Line 1455 of yacc.c  */
#line 6224 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
					}
    break;

  case 1006:

/* Line 1455 of yacc.c  */
#line 6229 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1007:

/* Line 1455 of yacc.c  */
#line 6239 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1008:

/* Line 1455 of yacc.c  */
#line 6248 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
					}
    break;

  case 1009:

/* Line 1455 of yacc.c  */
#line 6257 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
					}
    break;

  case 1010:

/* Line 1455 of yacc.c  */
#line 6263 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1011:

/* Line 1455 of yacc.c  */
#line 6274 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1012:

/* Line 1455 of yacc.c  */
#line 6282 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
					}
    break;

  case 1013:

/* Line 1455 of yacc.c  */
#line 6290 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
					}
    break;

  case 1014:

/* Line 1455 of yacc.c  */
#line 6295 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (6)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (6)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1015:

/* Line 1455 of yacc.c  */
#line 6305 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (7)]));
						pCurrAsmObj->bOperandCount = 3;
					}
    break;

  case 1016:

/* Line 1455 of yacc.c  */
#line 6314 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SIDT, "\x0F\x01", 2, 1);
					    pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 1017:

/* Line 1455 of yacc.c  */
#line 6321 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SLDT, "\x0F\x00", 2, 0);
					    pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 1018:

/* Line 1455 of yacc.c  */
#line 6326 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SLDT, "\x0F\x00", 2, 0);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1019:

/* Line 1455 of yacc.c  */
#line 6336 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1020:

/* Line 1455 of yacc.c  */
#line 6345 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 1021:

/* Line 1455 of yacc.c  */
#line 6350 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1022:

/* Line 1455 of yacc.c  */
#line 6360 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STC, "\xF9", 1, 0xFF);	
					}
    break;

  case 1023:

/* Line 1455 of yacc.c  */
#line 6366 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STD, "\xFD", 1, 0xFF);
					}
    break;

  case 1024:

/* Line 1455 of yacc.c  */
#line 6372 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STI, "\xFB", 1, 0xFF);
					}
    break;

  case 1025:

/* Line 1455 of yacc.c  */
#line 6378 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STMXCSR, "\x0F\xAE", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
    break;

  case 1026:

/* Line 1455 of yacc.c  */
#line 6385 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSB, "\xAA", 1, 0xFF);
					}
    break;

  case 1027:

/* Line 1455 of yacc.c  */
#line 6391 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSW, "\xAB", 1, 0xFF);
					}
    break;

  case 1028:

/* Line 1455 of yacc.c  */
#line 6398 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSW, "\xAB", 1, 0xFF);
					}
    break;

  case 1029:

/* Line 1455 of yacc.c  */
#line 6404 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STR, "\x0F\x00", 2, 1);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1030:

/* Line 1455 of yacc.c  */
#line 6412 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, STR, "\x0F\x00", 2, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    break;

  case 1031:

/* Line 1455 of yacc.c  */
#line 6419 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x80", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1032:

/* Line 1455 of yacc.c  */
#line 6431 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x80", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1033:

/* Line 1455 of yacc.c  */
#line 6436 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1034:

/* Line 1455 of yacc.c  */
#line 6449 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1035:

/* Line 1455 of yacc.c  */
#line 6455 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1036:

/* Line 1455 of yacc.c  */
#line 6467 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1037:

/* Line 1455 of yacc.c  */
#line 6472 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1038:

/* Line 1455 of yacc.c  */
#line 6478 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1039:

/* Line 1455 of yacc.c  */
#line 6483 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1040:

/* Line 1455 of yacc.c  */
#line 6488 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1041:

/* Line 1455 of yacc.c  */
#line 6493 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x28", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1042:

/* Line 1455 of yacc.c  */
#line 6501 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x28", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1043:

/* Line 1455 of yacc.c  */
#line 6506 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1044:

/* Line 1455 of yacc.c  */
#line 6515 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1045:

/* Line 1455 of yacc.c  */
#line 6521 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1046:

/* Line 1455 of yacc.c  */
#line 6529 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1047:

/* Line 1455 of yacc.c  */
#line 6534 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1048:

/* Line 1455 of yacc.c  */
#line 6539 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1049:

/* Line 1455 of yacc.c  */
#line 6545 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1050:

/* Line 1455 of yacc.c  */
#line 6552 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SWAPGS, "\x0F\x01", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    break;

  case 1051:

/* Line 1455 of yacc.c  */
#line 6559 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSCALL, "\x0F\x05", 2, 0xFF);
					}
    break;

  case 1052:

/* Line 1455 of yacc.c  */
#line 6565 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSENTER, "\x0F\x34", 2, 0xFF);
					}
    break;

  case 1053:

/* Line 1455 of yacc.c  */
#line 6571 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSEXIT, "\x0F\x35", 2, 0xFF);
					}
    break;

  case 1054:

/* Line 1455 of yacc.c  */
#line 6577 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSRET, "\x0F\x07", 2, 0xFF);
					}
    break;

  case 1055:

/* Line 1455 of yacc.c  */
#line 6583 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA8", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF6", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1056:

/* Line 1455 of yacc.c  */
#line 6595 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF6", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 1057:

/* Line 1455 of yacc.c  */
#line 6600 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA9", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1058:

/* Line 1455 of yacc.c  */
#line 6613 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 1059:

/* Line 1455 of yacc.c  */
#line 6619 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA9", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1060:

/* Line 1455 of yacc.c  */
#line 6631 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    break;

  case 1061:

/* Line 1455 of yacc.c  */
#line 6636 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x84", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1062:

/* Line 1455 of yacc.c  */
#line 6644 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x84", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1063:

/* Line 1455 of yacc.c  */
#line 6649 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1064:

/* Line 1455 of yacc.c  */
#line 6658 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1065:

/* Line 1455 of yacc.c  */
#line 6664 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1066:

/* Line 1455 of yacc.c  */
#line 6672 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1067:

/* Line 1455 of yacc.c  */
#line 6679 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, UD2, "\x0F\x0B", 2, 0xFF);
					}
    break;

  case 1068:

/* Line 1455 of yacc.c  */
#line 6685 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1069:

/* Line 1455 of yacc.c  */
#line 6693 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 1070:

/* Line 1455 of yacc.c  */
#line 6700 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (2)]));
					}
    break;

  case 1071:

/* Line 1455 of yacc.c  */
#line 6708 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1072:

/* Line 1455 of yacc.c  */
#line 6715 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, WAIT, "\x9B", 1, 0xFF);
					}
    break;

  case 1073:

/* Line 1455 of yacc.c  */
#line 6721 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, FWAIT, "\x9B", 1, 0xFF);
					}
    break;

  case 1074:

/* Line 1455 of yacc.c  */
#line 6727 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, WBINVD, "\x0F\x09", 2, 0xFF);
					}
    break;

  case 1075:

/* Line 1455 of yacc.c  */
#line 6733 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, WRMSR, "\x0F\x30", 2, 0xFF);
					}
    break;

  case 1076:

/* Line 1455 of yacc.c  */
#line 6739 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC0", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1077:

/* Line 1455 of yacc.c  */
#line 6747 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC0", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1078:

/* Line 1455 of yacc.c  */
#line 6752 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1079:

/* Line 1455 of yacc.c  */
#line 6761 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1080:

/* Line 1455 of yacc.c  */
#line 6767 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1081:

/* Line 1455 of yacc.c  */
#line 6775 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1082:

/* Line 1455 of yacc.c  */
#line 6782 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1083:

/* Line 1455 of yacc.c  */
#line 6790 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1084:

/* Line 1455 of yacc.c  */
#line 6795 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1085:

/* Line 1455 of yacc.c  */
#line 6800 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = 0;
						SetPrefix66();
						
						if ((yyvsp[(2) - (4)]) == R_AX) {
							bOpcode = '\x90' + GetRegisterIndex((yyvsp[(2) - (4)]));
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else if ((yyvsp[(4) - (4)]) == R_AX) {
							bOpcode = '\x90' + GetRegisterIndex((yyvsp[(4) - (4)]));
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else {
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1086:

/* Line 1455 of yacc.c  */
#line 6821 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1087:

/* Line 1455 of yacc.c  */
#line 6827 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1088:

/* Line 1455 of yacc.c  */
#line 6833 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						__byte bOpcode = 0;
						
						if ((yyvsp[(2) - (4)]) == R_EAX) {
							bOpcode = '\x90' + GetRegisterIndex((yyvsp[(4) - (4)]));
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else if ((yyvsp[(4) - (4)]) == R_EAX) {
							bOpcode = '\x90' + GetRegisterIndex((yyvsp[(2) - (4)]));
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else {
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (4)]));
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(4) - (4)]));
						}
					}
    break;

  case 1089:

/* Line 1455 of yacc.c  */
#line 6853 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1090:

/* Line 1455 of yacc.c  */
#line 6858 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1091:

/* Line 1455 of yacc.c  */
#line 6865 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XGETBV, "\x0F\x01\xD0", 3, 0xFF);
					}
    break;

  case 1092:

/* Line 1455 of yacc.c  */
#line 6871 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XLAT, "\xD7", 1, 0xFF);
					}
    break;

  case 1093:

/* Line 1455 of yacc.c  */
#line 6877 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XLAT, "\xD7", 1, 0xFF);
					}
    break;

  case 1094:

/* Line 1455 of yacc.c  */
#line 6883 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x34", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x80", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1095:

/* Line 1455 of yacc.c  */
#line 6895 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x80", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1096:

/* Line 1455 of yacc.c  */
#line 6900 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
						if ((yyvsp[(2) - (4)]) == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x35", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1097:

/* Line 1455 of yacc.c  */
#line 6913 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1098:

/* Line 1455 of yacc.c  */
#line 6919 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						if ((yyvsp[(2) - (4)]) == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x35", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
						}
					}
    break;

  case 1099:

/* Line 1455 of yacc.c  */
#line 6931 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1100:

/* Line 1455 of yacc.c  */
#line 6936 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1101:

/* Line 1455 of yacc.c  */
#line 6942 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1102:

/* Line 1455 of yacc.c  */
#line 6947 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1103:

/* Line 1455 of yacc.c  */
#line 6952 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    break;

  case 1104:

/* Line 1455 of yacc.c  */
#line 6957 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x30", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1105:

/* Line 1455 of yacc.c  */
#line 6965 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x30", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1106:

/* Line 1455 of yacc.c  */
#line 6970 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1107:

/* Line 1455 of yacc.c  */
#line 6979 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1108:

/* Line 1455 of yacc.c  */
#line 6985 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(4) - (4)]));
						pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(2) - (4)]));
					}
    break;

  case 1109:

/* Line 1455 of yacc.c  */
#line 6993 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(5) - (5)]));
					}
    break;

  case 1110:

/* Line 1455 of yacc.c  */
#line 6998 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x32", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1111:

/* Line 1455 of yacc.c  */
#line 7003 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x33", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1112:

/* Line 1455 of yacc.c  */
#line 7009 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x33", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex((yyvsp[(2) - (5)]));
					}
    break;

  case 1113:

/* Line 1455 of yacc.c  */
#line 7016 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XRSTOR, "\x0F\xAE", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    break;

  case 1114:

/* Line 1455 of yacc.c  */
#line 7023 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XSAVE, "\x0F\xAE", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    break;

  case 1115:

/* Line 1455 of yacc.c  */
#line 7030 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					    SetAsmObj(pCurrAsmObj, IC_X86, XSETBV, "\x0F\x01\xD1", 3, 0xFF);
					}
    break;

  case 1116:

/* Line 1455 of yacc.c  */
#line 7036 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = ADDR_LAB;
					pCurrAsmObj->Operand[g_iCurrOperand].bAddrLabel = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].bIsImmediate = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].Type = OP_IMM;
					pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
					pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = 0;//先设置为0				    
					pCurrAsmObj->pAddrLabelSymbolName = NextSymbol();//记录到所引用的地址标号
					(pCurrAsmObj->bOperandCount)++;
				 }
    break;

  case 1117:

/* Line 1455 of yacc.c  */
#line 7049 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					pCurrAsmObj->bUsePrefix = TRUE;
				    pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = (yyvsp[(1) - (3)]);
					(pCurrAsmObj->bPrefixCount)++;
				 }
    break;

  case 1118:

/* Line 1455 of yacc.c  */
#line 7055 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				    pCurrAsmObj->bUseModRM = TRUE;
				    pCurrAsmObj->Operand[g_iCurrOperand].bIsMem = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].Type = OP_MEM;
				    (pCurrAsmObj->bOperandCount)++;
				 }
    break;

  case 1119:

/* Line 1455 of yacc.c  */
#line 7064 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					pCurrAsmObj->bUseDisplacement = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].bAddrLabel = TRUE;
					pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
					pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
					pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = 0;//先设置为0
					pCurrAsmObj->pAddrLabelSymbolName = NextSymbol();//记录到所引用的地址标号
					// 设置ModRM
					pCurrAsmObj->ModRM.Mod = 0;
					pCurrAsmObj->ModRM.RM = 5;
				 }
    break;

  case 1120:

/* Line 1455 of yacc.c  */
#line 7076 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     pCurrAsmObj->ModRM.Mod = 0;
					 pCurrAsmObj->ModRM.RM = 5;
				 }
    break;

  case 1121:

/* Line 1455 of yacc.c  */
#line 7081 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				 	 pCurrAsmObj->ModRM.Mod = 0;
					 if ((yyvsp[(1) - (1)]) == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(1) - (1)]));
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(1) - (1)]);
				 }
    break;

  case 1122:

/* Line 1455 of yacc.c  */
#line 7095 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     pCurrAsmObj->ModRM.Mod = 1;
					 if ((yyvsp[(1) - (3)]) == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(1) - (3)]));
					 	 if ((yyvsp[(2) - (3)]) == SUBSIGN) {
					         __byte bDisplacement8 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte;
						 	 bDisplacement8 = ~bDisplacement8 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
					 	 }
				     }
				     pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(1) - (3)]);
				 }
    break;

  case 1123:

/* Line 1455 of yacc.c  */
#line 7114 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     pCurrAsmObj->ModRM.Mod = 2;
					 if ((yyvsp[(1) - (3)]) == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex((yyvsp[(1) - (3)]));
					 	 if ((yyvsp[(2) - (3)]) == SUBSIGN) {
					     	 __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(1) - (3)]);
				 }
    break;

  case 1124:

/* Line 1455 of yacc.c  */
#line 7133 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     if ((yyvsp[(2) - (2)]) == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
				         pCurrAsmObj->ModRM.Mod = 0;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (2)]));
						 pCurrAsmObj->SIB.Base = 5;
						 /* Mod == 0, [scale index] + disp32 */
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = 0;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(2) - (2)]);
				 }
    break;

  case 1125:

/* Line 1455 of yacc.c  */
#line 7152 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     if ((yyvsp[(2) - (4)]) == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
				         pCurrAsmObj->ModRM.Mod = 0;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (4)]));
						 pCurrAsmObj->SIB.Base = 5;
					
						 if ((yyvsp[(3) - (4)]) == SUBSIGN) {
					         __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(2) - (4)]);
				 }
    break;

  case 1126:

/* Line 1455 of yacc.c  */
#line 7172 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     if ((yyvsp[(2) - (4)]) == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
						 /*
                          * 如果Base寄存器为ebp, 那么还需要遵从
                          * Mod == 1, [scale index] + disp8的约定
                          */
						 if ((yyvsp[(4) - (4)]) == R_EBP) {
				             pCurrAsmObj->ModRM.Mod = 1;
						 	 pCurrAsmObj->ModRM.RM = 4;
					     	 pCurrAsmObj->bUseSIB = TRUE;
					     	 pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (4)]));
						 	 pCurrAsmObj->SIB.Base = 5;

						 	 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = 0;
						 	 pCurrAsmObj->bUseDisplacement = TRUE;
						 	 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
						 } else {
				             pCurrAsmObj->ModRM.Mod = 0;
						 	 pCurrAsmObj->ModRM.RM = 4;
					     	 pCurrAsmObj->bUseSIB = TRUE;
					     	 pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (4)]));
						 	 pCurrAsmObj->SIB.Base = GetRegisterIndex((yyvsp[(4) - (4)]));
						 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(2) - (4)]);
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = (yyvsp[(4) - (4)]);
				 }
    break;

  case 1127:

/* Line 1455 of yacc.c  */
#line 7204 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     if ((yyvsp[(2) - (6)]) == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
					     pCurrAsmObj->ModRM.Mod = 1;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (6)]));
						 pCurrAsmObj->SIB.Base = GetRegisterIndex((yyvsp[(4) - (6)]));

						 if ((yyvsp[(5) - (6)]) == SUBSIGN) {
					         __byte bDisplacement8 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte;
						 	 bDisplacement8 = ~bDisplacement8 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(2) - (6)]);
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = (yyvsp[(4) - (6)]);
				 }
    break;

  case 1128:

/* Line 1455 of yacc.c  */
#line 7225 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     if ((yyvsp[(2) - (6)]) == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
					     pCurrAsmObj->ModRM.Mod = 1;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex((yyvsp[(2) - (6)]));
						 pCurrAsmObj->SIB.Base = GetRegisterIndex((yyvsp[(4) - (6)]));

						 if ((yyvsp[(5) - (6)]) == SUBSIGN) {
					         __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = (yyvsp[(2) - (6)]);
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = (yyvsp[(4) - (6)]);
				 }
    break;

  case 1129:

/* Line 1455 of yacc.c  */
#line 7248 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     (yyval) = LOCK;
					 pCurrAsmObj->bUsePrefix = TRUE;
					 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF0;
					 (pCurrAsmObj->bPrefixCount)++;
                 }
    break;

  case 1130:

/* Line 1455 of yacc.c  */
#line 7255 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     /* 鉴别是否是串指令, 如果不是则返回错误 */
					 int iNextToken = __PreFetcherToken__();
					 switch (iNextToken) {
					 case LODSB: case LODSW: case LODSD: case STOSB:
					 case STOSW: case STOSD: case CMPSB: case CMPSW:
					 case CMPSD: case SCASB: case SCASW: case SCASD: {
					     (yyval) = REPZ;
					 	 pCurrAsmObj->bUsePrefix = TRUE;
					 	 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF3;
					 	 (pCurrAsmObj->bPrefixCount)++;
					 } break;
					 default:
					     return -1;
					 }/* end switch */
				 }
    break;

  case 1131:

/* Line 1455 of yacc.c  */
#line 7272 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
				     /* 鉴别是否是串指令, 如果不是则返回错误 */
					 int iNextToken = __PreFetcherToken__();
					 switch (iNextToken) {
					 case LODSB: case LODSW: case LODSD: case STOSB:
					 case STOSW: case STOSD: case CMPSB: case CMPSW:
					 case CMPSD: case SCASB: case SCASW: case SCASD: {
					     (yyval) = REPNZ;
					 	 pCurrAsmObj->bUsePrefix = TRUE;
					 	 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF2;
					 	 (pCurrAsmObj->bPrefixCount)++;
					 } break;
					 default:
					     return -1;
					 }/* end switch */
				 }
    break;

  case 1132:

/* Line 1455 of yacc.c  */
#line 7289 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					/* 新的指令开始 */
					CreateNewAsmObj();
				 }
    break;

  case 1133:

/* Line 1455 of yacc.c  */
#line 7295 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = REP; }
    break;

  case 1134:

/* Line 1455 of yacc.c  */
#line 7296 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = REPE; }
    break;

  case 1135:

/* Line 1455 of yacc.c  */
#line 7297 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = REPZ; }
    break;

  case 1136:

/* Line 1455 of yacc.c  */
#line 7300 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = REPNE; }
    break;

  case 1137:

/* Line 1455 of yacc.c  */
#line 7301 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = REPNZ; }
    break;

  case 1138:

/* Line 1455 of yacc.c  */
#line 7305 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_AL;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_AL, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1139:

/* Line 1455 of yacc.c  */
#line 7311 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CL;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1140:

/* Line 1455 of yacc.c  */
#line 7317 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DL; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_DL, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1141:

/* Line 1455 of yacc.c  */
#line 7323 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_BL; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_BL, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1142:

/* Line 1455 of yacc.c  */
#line 7329 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_AH; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_AH, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1143:

/* Line 1455 of yacc.c  */
#line 7335 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CH; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_CH, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1144:

/* Line 1455 of yacc.c  */
#line 7341 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DH;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_DH, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1145:

/* Line 1455 of yacc.c  */
#line 7347 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_BH;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_BH, NONE); 
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1146:

/* Line 1455 of yacc.c  */
#line 7355 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_AX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_AX, NONE); 
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1147:

/* Line 1455 of yacc.c  */
#line 7361 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_CX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_CX, NONE); 
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1148:

/* Line 1455 of yacc.c  */
#line 7367 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_DX, NONE); 
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1149:

/* Line 1455 of yacc.c  */
#line 7373 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_BX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_BX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1150:

/* Line 1455 of yacc.c  */
#line 7379 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_SP; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_SP, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1151:

/* Line 1455 of yacc.c  */
#line 7385 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_BP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_BP, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1152:

/* Line 1455 of yacc.c  */
#line 7391 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_SI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_SI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1153:

/* Line 1455 of yacc.c  */
#line 7397 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_DI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1154:

/* Line 1455 of yacc.c  */
#line 7405 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_EAX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1155:

/* Line 1455 of yacc.c  */
#line 7411 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_ECX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ECX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1156:

/* Line 1455 of yacc.c  */
#line 7417 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_EDX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EDX, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1157:

/* Line 1455 of yacc.c  */
#line 7423 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_EBX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EBX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1158:

/* Line 1455 of yacc.c  */
#line 7429 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_ESP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ESP, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1159:

/* Line 1455 of yacc.c  */
#line 7435 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_EBP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EBP, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1160:

/* Line 1455 of yacc.c  */
#line 7441 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_ESI; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ESI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1161:

/* Line 1455 of yacc.c  */
#line 7447 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_EDI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EDI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1162:

/* Line 1455 of yacc.c  */
#line 7455 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR0; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR0, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1163:

/* Line 1455 of yacc.c  */
#line 7461 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR1, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1164:

/* Line 1455 of yacc.c  */
#line 7467 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR2;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1165:

/* Line 1455 of yacc.c  */
#line 7473 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR3, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1166:

/* Line 1455 of yacc.c  */
#line 7479 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR4, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1167:

/* Line 1455 of yacc.c  */
#line 7485 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR5; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1168:

/* Line 1455 of yacc.c  */
#line 7491 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR6;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1169:

/* Line 1455 of yacc.c  */
#line 7497 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_CR7; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1170:

/* Line 1455 of yacc.c  */
#line 7505 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_DR0; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR0, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1171:

/* Line 1455 of yacc.c  */
#line 7511 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { 
					(yyval) = R_DR1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR1, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1172:

/* Line 1455 of yacc.c  */
#line 7517 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR2;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1173:

/* Line 1455 of yacc.c  */
#line 7523 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR3, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1174:

/* Line 1455 of yacc.c  */
#line 7529 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR4, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    break;

  case 1175:

/* Line 1455 of yacc.c  */
#line 7535 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR5;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1176:

/* Line 1455 of yacc.c  */
#line 7541 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR6;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1177:

/* Line 1455 of yacc.c  */
#line 7547 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = R_DR7;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    break;

  case 1178:

/* Line 1455 of yacc.c  */
#line 7704 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_EAX; }
    break;

  case 1179:

/* Line 1455 of yacc.c  */
#line 7705 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_ECX; }
    break;

  case 1180:

/* Line 1455 of yacc.c  */
#line 7706 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_EDX; }
    break;

  case 1181:

/* Line 1455 of yacc.c  */
#line 7707 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_EBX; }
    break;

  case 1182:

/* Line 1455 of yacc.c  */
#line 7708 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_ESP; }
    break;

  case 1183:

/* Line 1455 of yacc.c  */
#line 7709 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_EBP; }
    break;

  case 1184:

/* Line 1455 of yacc.c  */
#line 7710 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_ESI; }
    break;

  case 1185:

/* Line 1455 of yacc.c  */
#line 7711 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = R_EDI; }
    break;

  case 1186:

/* Line 1455 of yacc.c  */
#line 7714 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x26; }
    break;

  case 1187:

/* Line 1455 of yacc.c  */
#line 7715 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x2E; }
    break;

  case 1188:

/* Line 1455 of yacc.c  */
#line 7716 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x36; }
    break;

  case 1189:

/* Line 1455 of yacc.c  */
#line 7717 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x3E; }
    break;

  case 1190:

/* Line 1455 of yacc.c  */
#line 7718 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x64; }
    break;

  case 1191:

/* Line 1455 of yacc.c  */
#line 7719 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0x65; }
    break;

  case 1192:

/* Line 1455 of yacc.c  */
#line 7722 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 0; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 0; pCurrAsmObj->SIB.SS = 0; }
    break;

  case 1193:

/* Line 1455 of yacc.c  */
#line 7723 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 1; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 1; pCurrAsmObj->SIB.SS = 1; }
    break;

  case 1194:

/* Line 1455 of yacc.c  */
#line 7724 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 2; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 2; pCurrAsmObj->SIB.SS = 2; }
    break;

  case 1195:

/* Line 1455 of yacc.c  */
#line 7725 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = 3; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 3; pCurrAsmObj->SIB.SS = 3; }
    break;

  case 1196:

/* Line 1455 of yacc.c  */
#line 7728 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = PLUSSIGN; }
    break;

  case 1197:

/* Line 1455 of yacc.c  */
#line 7729 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = SUBSIGN; }
    break;

  case 1198:

/* Line 1455 of yacc.c  */
#line 7732 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = BYTE_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_8_BITS; }
    break;

  case 1199:

/* Line 1455 of yacc.c  */
#line 7735 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = WORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_16_BITS; }
    break;

  case 1200:

/* Line 1455 of yacc.c  */
#line 7738 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = DWORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_32_BITS; }
    break;

  case 1201:

/* Line 1455 of yacc.c  */
#line 7741 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = QWORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_64_BITS; }
    break;

  case 1202:

/* Line 1455 of yacc.c  */
#line 7748 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					      __byte bImmediate8 = *(__byte *)GetImmediate(1);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
										NONE, 0xFF, ASMER_8_BITS, bImmediate8, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    break;

  case 1203:

/* Line 1455 of yacc.c  */
#line 7757 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					      __word wImmediate16 = *(__word *)GetImmediate(2);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
									    NONE, 0xFF, ASMER_16_BITS, wImmediate16, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    break;

  case 1204:

/* Line 1455 of yacc.c  */
#line 7766 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					      __dword dwImmediate32 = *(__dword *)GetImmediate(4);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
									    NONE, 0xFF, ASMER_32_BITS, dwImmediate32, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    break;

  case 1205:

/* Line 1455 of yacc.c  */
#line 7775 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					     __byte bDisplacement8 = *(__byte *)GetImmediate(1);
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
				 	 }
    break;

  case 1206:

/* Line 1455 of yacc.c  */
#line 7785 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					     __dword dwDisplacement32 = *(__dword *)GetImmediate(4);
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
				 	 }
    break;

  case 1207:

/* Line 1455 of yacc.c  */
#line 7794 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = COLON; }
    break;

  case 1208:

/* Line 1455 of yacc.c  */
#line 7796 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    { (yyval) = COMMA; g_iCurrOperand++; }
    break;

  case 1209:

/* Line 1455 of yacc.c  */
#line 7799 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"
    {
					(yyval) = LINEND;
					g_pCurrAsmObjPoint = &((*g_pCurrAsmObjPoint)->pNext);
					g_iCurrOperand = 0;
				 }
    break;



/* Line 1455 of yacc.c  */
#line 17849 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 7806 "e:\\logic\\projects\\codes\\libassembler\\Assembler.y"


