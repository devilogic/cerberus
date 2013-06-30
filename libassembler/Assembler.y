%{
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

%}

%token LOCK
%token REP
%token REPE
%token REPZ
%token REPNE
%token REPNZ

%token AAA
%token AAD
%token AAM
%token AAS
%token ADC
%token ADD
%token ADDPD
%token ADDPS
%token ADDSD
%token ADDSS
%token ADDSUBPD
%token ADDSUBPS
%token AESDEC
%token AESDECLAST
%token AESENC
%token AESENCLAST
%token AESIMC
%token AESKEYGENASSIST
%token AND
%token ANDPD
%token ANDPS
%token ANDNPD
%token ANDNPS
%token ARPL
%token BLENDPD
%token BLENDPS
%token BLENDVPD
%token BLENDVPS
%token BOUND
%token BSF
%token BSR
%token BSWAP
%token BT
%token BTC
%token BTR
%token BTS
%token CALL
%token CBW
%token CWDE
%token CDQE
%token CLC
%token CLD
%token CLFLUSH
%token CLI
%token CLTS
%token CMC
%token CMOVA
%token CMOVAE
%token CMOVB
%token CMOVBE
%token CMOVC
%token CMOVE
%token CMOVG
%token CMOVGE
%token CMOVL
%token CMOVLE
%token CMOVNA
%token CMOVNAE
%token CMOVNB
%token CMOVNBE
%token CMOVNC
%token CMOVNE
%token CMOVNG
%token CMOVNGE
%token CMOVNL
%token CMOVNLE
%token CMOVNO
%token CMOVNP
%token CMOVNS
%token CMOVNZ
%token CMOVO
%token CMOVP
%token CMOVPE
%token CMOVPO
%token CMOVS
%token CMOVZ
%token CMP
%token CMPPD
%token CMPPS
%token CMPSB
%token CMPSW
%token CMPSD
%token CMPSQ
%token CMPSDx
%token CMPSS
%token CMPXCHG
%token CMPXCHG8B
%token COMISD
%token COMISS
%token CPUID
%token CRC32
%token CVTDQ2PD
%token CVTDQ2PS
%token CVTPD2DQ
%token CVTPD2PI
%token CVTPD2PS
%token CVTPI2PD
%token CVTPI2PS
%token CVTPS2DQ
%token CVTPS2PD
%token CVTPS2PI
%token CVTSD2SI
%token CVTSD2SS
%token CVTSI2SD
%token CVTSI2SS
%token CVTSS2SD
%token CVTSS2SI
%token CVTTPD2DQ
%token CVTTPD2PI
%token CVTTPS2DQ
%token CVTTPS2PI
%token CVTTSD2SI
%token CVTTSS2SI
%token CWD
%token CDQ
%token CQO
%token DAA
%token DAS
%token DEC
%token DIV
%token DIVPD
%token DIVPS
%token DIVSD
%token DIVSS
%token DPPD
%token DPPS
%token EMMS
%token ENTER
%token EXTRACTPS
%token F2XM1
%token FABS
%token FADD
%token FADDP
%token FIADD
%token FBLD
%token FBSTP
%token FCHS
%token FCLEX
%token FNCLEX
%token FCMOVB
%token FCMOVE
%token FCMOVBE
%token FCMOVU
%token FCMOVNB
%token FCMOVNE
%token FCMOVNBE
%token FCMOVNU
%token FCOMI
%token FCOMIP
%token FCOS
%token FDECSTP
%token FDIV
%token FDIVP
%token FIDIV
%token FDIVR
%token FDIVRP
%token FIDIVR
%token FFREE
%token FICOM
%token FICOMP
%token FILD
%token FINCSTP
%token FINIT
%token FNINIT
%token FIST
%token FISTP
%token FISTTP
%token FLD
%token FLD1
%token FLDL2T
%token FLDL2E
%token FLDPI
%token FLDLG2
%token FLDLN2
%token FLDZ
%token FLDCW
%token FLDENV
%token FMUL
%token FMULP
%token FIMUL
%token FNOP
%token FPATAN
%token FPREM
%token FPREM1
%token FPTAN
%token FRNDINT
%token FRSTOR
%token FSAVE
%token FNSAVE
%token FSCALE
%token FSIN
%token FSINCOS
%token FSQRT
%token FST
%token FSTP
%token FSTCW
%token FNSTCW
%token FSTENV
%token FNSTENV
%token FSTSW
%token FNSTSW
%token FSUB
%token FSUBP
%token FISUB
%token FSUBR
%token FSUBRP
%token FISUBR
%token FTST
%token FUCOM
%token FUCOMP
%token FUCOMPP
%token FXAM
%token FXCH
%token FXRSTOR
%token FXSAVE
%token FXTRACT
%token FYL2X
%token FYL2XP1
%token HADDPD
%token HADDPS
%token HLT
%token HSUBPD
%token HSUBPS
%token IDIV
%token IMUL
%token IN
%token INC
%token INS
%token INSB
%token INSW
%token INSD
%token INSERTPS
%token INT
%token INT3
%token INTO
%token INVD
%token INVLPG
%token IRET
%token IRETD
%token JA
%token JAE
%token JB
%token JBE
%token JC
%token JCXZ
%token JECXZ
%token JRCXZ
%token JE
%token JG
%token JGE
%token JL
%token JLE
%token JNA
%token JNAE
%token JNB
%token JNBE
%token JNC
%token JNE
%token JNG
%token JNGE
%token JNL
%token JNLE
%token JNO
%token JNP
%token JNS
%token JNZ
%token JO
%token JP
%token JPE
%token JPO
%token JS
%token JZ
%token JMP
%token LAHF
%token LAR
%token LDDQU
%token LDMXCSR
%token LDS
%token LES
%token LFS
%token LGS
%token LSS
%token LEA
%token LEAVE
%token LFENCE
%token LGDT
%token LIDT
%token LLDT
%token LMSW
%token LODSB
%token LODSW
%token LODSD
%token LODSQ
%token LOOP
%token LOOPE
%token LOOPNE
%token LSL
%token LTR
%token MASKMOVDQU
%token MASKMOVQ
%token MAXPD
%token MAXPS
%token MAXSD
%token MAXSS
%token MFENCE
%token MINPD
%token MINPS
%token MINSD
%token MINSS
%token MONITOR
%token MOV
%token MOVAPD
%token MOVAPS
%token MOVBE
%token MOVD
%token MOVQ
%token MOVDDUP
%token MOVDQA
%token MOVDQU
%token MOVDQ2Q
%token MOVHLPS
%token MOVHPD
%token MOVHPS
%token MOVLHPS
%token MOVLPD
%token MOVLPS
%token MOVMSKPD
%token MOVMSKPS
%token MOVNTDQA
%token MOVNTDQ
%token MOVNTI
%token MOVNTPD
%token MOVNTPS
%token MOVNTQ
%token MOVQx
%token MOVQ2DQ
%token MOVSB
%token MOVSW
%token MOVSD
%token MOVSQ
%token MOVSDx
%token MOVSHDUP
%token MOVSLDUP
%token MOVSS
%token MOVSX
%token MOVSXD
%token MOVUPD
%token MOVUPS
%token MOVZX
%token MPSADBW
%token MUL
%token MULPD
%token MULPS
%token MULSD
%token MULSS
%token MWAIT
%token NEG
%token NOP
%token NOT
%token OR
%token ORPD
%token ORPS
%token OUT
%token OUTS
%token OUTSB
%token OUTSW
%token OUTSD
%token PABSB
%token PABSW
%token PABSD
%token PACKSSWB
%token PACKSSDW
%token PACKUSDW
%token PACKUSWB
%token PADDB
%token PADDW
%token PADDD
%token PADDQ
%token PADDSB
%token PADDSW
%token PADDUSB
%token PADDUSW
%token PALIGNR
%token PAND
%token PANDN
%token PAUSE
%token PAVGB
%token PAVGW
%token PBLENDVB
%token PBLENDW
%token PCLMULQDQ
%token PCMPEQB
%token PCMPEQW
%token PCMPEQD
%token PCMPEQQ
%token PCMPESTRI
%token PCMPESTRM
%token PCMPGTB
%token PCMPGTW
%token PCMPGTD
%token PCMPGTQ
%token PCMPISTRI
%token PCMPISTRM
%token PEXTRB
%token PEXTRD
%token PEXTRQ
%token PEXTRW
%token PHADDW
%token PHADDD
%token PHADDSW
%token PHMINPOSUW
%token PHSUBW
%token PHSUBD
%token PHSUBSW
%token PINSRB
%token PINSRD
%token PINSRQ
%token PINSRW
%token PMADDUBSW
%token PMADDWD
%token PMAXSB
%token PMAXSD
%token PMAXSW
%token PMAXUB
%token PMAXUD
%token PMAXUW
%token PMINSB
%token PMINSD
%token PMINSW
%token PMINUB
%token PMINUD
%token PMINUW
%token PMOVMSKB
%token PMOVSX
%token PMOVZX
%token PMULDQ
%token PMULHRSW
%token PMULHUW
%token PMULHW
%token PMULLD
%token PMULLW
%token PMULUDQ
%token POP
%token POPA
%token POPAD
%token POPCNT
%token POPF
%token POPFD
%token POPFQ
%token POR
%token PREFETCHT0
%token PREFETCHT1
%token PREFETCHT2
%token PREFETCHNTA
%token PSADBW
%token PSHUFB
%token PSHUFD
%token PSHUFHW
%token PSHUFLW
%token PSHUFW
%token PSIGNB
%token PSIGNW
%token PSIGND
%token PSLLDQ
%token PSLLW
%token PSLLD
%token PSLLQ
%token PSRAW
%token PSRAD
%token PSRLDQ
%token PSRLW
%token PSRLD
%token PSRLQ
%token PSUBB
%token PSUBW
%token PSUBD
%token PSUBQ
%token PSUBSB
%token PSUBSW
%token PSUBUSB
%token PSUBUSW
%token PTEST
%token PUNPCKHBW
%token PUNPCKHWD
%token PUNPCKHDQ
%token PUNPCKHQDQ
%token PUNPCKLBW
%token PUNPCKLWD
%token PUNPCKLDQ
%token PUNPCKLQDQ
%token PUSH
%token PUSHA
%token PUSHAD
%token PUSHF
%token PUSHFD
%token PXOR
%token RCL
%token RCR
%token ROL
%token ROR
%token RCPPS
%token RCPSS
%token RDMSR
%token RDPMC
%token RDTSC
%token RDTSCP
%token RET
%token RETN
%token ROUNDPD
%token ROUNDPS
%token ROUNDSD
%token ROUNDSS
%token RSM
%token RSQRTPS
%token RSQRTSS
%token SAHF
%token SAL
%token SAR
%token SHL
%token SHR
%token SBB
%token SCASB
%token SCASW
%token SCASD
%token SETA
%token SETAE
%token SETB
%token SETBE
%token SETC
%token SETE
%token SETG
%token SETGE
%token SETL
%token SETLE
%token SETNA
%token SETNAE
%token SETNB
%token SETNBE
%token SETNC
%token SETNE
%token SETNG
%token SETNGE
%token SETNL
%token SETNLE
%token SETNO
%token SETNP
%token SETNS
%token SETNZ
%token SETO
%token SETP
%token SETPE
%token SETPO
%token SETS
%token SETZ
%token SFENCE
%token SGDT
%token SHLD
%token SHRD
%token SHUFPD
%token SHUFPS
%token SIDT
%token SLDT
%token SMSW
%token SQRTPS
%token SQRTSD
%token SQRTSS
%token STC
%token STD
%token STI
%token STMXCSR
%token STOSB
%token STOSW
%token STOSD
%token STOSQ
%token STR
%token SUB
%token SUBPD
%token SUBPS
%token SUBSD
%token SUBSS
%token SWAPGS
%token SYSCALL
%token SYSENTER
%token SYSEXIT
%token SYSRET
%token TEST
%token UCOMISD
%token UCOMISS
%token UD2
%token UNPCKHPD
%token UNPCKHPS
%token UNPCKLPD
%token UNPCKLPS
%token VERR
%token VERW
%token WAIT
%token FWAIT
%token WBINVD
%token WRMSR
%token XADD
%token XCHG
%token XGETBV
%token XLAT
%token XLATB
%token XOR
%token XORPD
%token XORPS
%token XRSTOR
%token XSAVE
%token XSETBV
%token INVEPT
%token INVVPID
%token VMCALL
%token VMCLEAR
%token VMLAUNCH
%token VMPTRLD
%token VMPTRST
%token VMREAD
%token VMRESUME
%token VMWRITE
%token VMXOFF
%token VMXON

%token R_AL R_CL R_DL R_BL
%token R_AH R_CH R_DH R_BH

%token R_AX R_CX R_DX R_BX
%token R_SP	R_BP R_SI R_DI

%token R_EAX R_ECX R_EDX R_EBX
%token R_ESP R_EBP R_ESI R_EDI

%token R_CR0 R_CR1 R_CR2 R_CR3
%token R_CR4 R_CR5 R_CR6 R_CR7

%token R_DR0 R_DR1 R_DR2 R_DR3
%token R_DR4 R_DR5 R_DR6 R_DR7

%token R_MM0 R_MM1 R_MM2 R_MM3
%token R_MM4 R_MM5 R_MM6 R_MM7

%token R_ST0 R_ST1 R_ST2 R_ST3
%token R_ST4 R_ST5 R_ST6 R_ST7

%token R_XMM0 R_XMM1 R_XMM2 R_XMM3
%token R_XMM4 R_XMM5 R_XMM6 R_XMM7

%token SEG_ES SEG_CS SEG_SS SEG_DS SEG_FS SEG_GS

%token OP_REG OP_MEM OP_IMM

%token BYTE_PTR WORD_PTR DWORD_PTR QWORD_PTR TWORD_PTR
%token SCALE_1 SCALE_2 SCALE_4 SCALE_8
%token PLUSSIGN SUBSIGN
%token ADDR_LAB
%token DISPLACEMENT8 DISPLACEMENT32
%token IMMEDIATE8 IMMEDIATE16 IMMEDIATE32
%token LINESTART COLON COMMA MEMEND LINEND ERROR END NONE

%%
asm_line:		instruction_line
	|			asm_line instruction_line
	;
	
instruction_line:	prefix instruction linend
	;

instruction:	 x86_instruction 
	|			 fpu_instruction
	|			 simd_instruction
	|			 vm_instruction
	|			 ADDR_LAB cn
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
	;

x86_instruction:    aaa_instruction
    |				aad_instruction
    |				aam_instruction
	|				aas_instruction
	|				adc_instruction
	|				add_instruction
	|				and_instruction
	|				arpl_instruction
	|				bound_instruction
	|				bsf_instruction
	|				bsr_instruction
	|				bswap_instruction
	|				bt_instruction
	|				btc_instruction
	|				btr_instruction
	|				bts_instruction
	|				call_instruction
	|				cbw_instruction
	|				cwde_instruction
	|				clc_instruction
	|				cld_instruction
	|				clflush_instruction
	|				cli_instruction
	|				clts_instruction
	|				cmc_instruction
	|				cmovcc_instruction
	|				cmp_instruction
	|				cmpsb_instruction
	|				cmpsw_instruction
	|				cmpsd_instruction
	|				cmpxchg_instruction
	|				cmpxchg8b_instruction
	|				cpuid_instruction
	|				crc32_instruction
	|				cwd_instruction
	|				cdq_instruction
	|				daa_instruction
	|				das_instruction
	|				dec_instruction
	|				div_instruction
	|				enter_instruction
	|				hlt_instruction
	|				idiv_instruction
	|				imul_instruction
	|				in_instruction
	|				inc_instruction
	|				ins_instruction
	|				insb_instruction
	|				insw_instruction
	|				insd_instruction
	|				int_instruction
	|				int3_instruction
	|				into_instruction
	|				invd_instruction
	|				invlpg_instruction
	|				iret_instruction
	|				jcc_instruction
	|				jmp_instruction
	|				lahf_instruction
	|				lar_instruction
	|				lds_instruction
	|				lss_instruction
	|				les_instruction
	|				lfs_instruction
	|				lgs_instruction
	|				lea_instruction
	|				leave_instruction
	|				lfence_instruction
	|				lgdt_instruction
	|				lidt_instruction
	|				lldt_instruction
	|				lmsw_instruction
	|				lodsb_instruction
	|				lodsw_instruction
	|				lodsd_instruction
	|				loop_instruction
	|				loope_instruction
	|				loopne_instruction
	|				lsl_instruction
	|				ltr_instruction
	|				mfence_instruction
	|				monitor_instruction
	|				mov_instruction
	|				movbe_instruction
	|				movsb_instruction
	|				movsw_instruction
	|				movsd_instruction
	|				movsx_instruction
	|				movzx_instruction
	|				mul_instruction
	|				mwait_instruction
	|				neg_instruction
	|				nop_instruction
	|				not_instruction
	|				or_instruction
	|				out_instruction
	|				outs_instruction
	|				outsb_instruction
	|				outsw_instruction
	|				outsd_instruction
	|				pause_instruction
	|				pop_instruction
	|				popa_instruction
	|				popad_instruction
	|				popcnt_instruction
	|				popf_instruction
	|				popfd_instruction
	|				prefetcht0_instruction
	|				prefetcht1_instruction
	|				prefetcht2_instruction
	|				prefetchnta_instruction
	|				push_instruction
	|				pusha_instruction
	|				pushad_instruction
	|				pushf_instruction
	|				pushfd_instruction
	|				rcl_instruction
	|				rcr_instruction
	|				rol_instruction
	|				ror_instruction
	|				rdmsr_instruction
	|				rdpmc_instruction
	|				rdtsc_instruction
	|				rdtscp_instruction
	|				ret_instruction
	|				retn_instruction
	|				rsm_instruction
	|				sahf_instruction
	|				sal_instruction
	|				sar_instruction
	|				shl_instruction
	|				shr_instruction
	|				sbb_instruction
	|				scasb_instruction
	|				scasw_instruction
	|				scasd_instruction
	|				setcc_instruction
	|				sfence_instruction
	|				sgdt_instruction
	|				shld_instruction
	|				shrd_instruction
	|				sidt_instruction
	|				sldt_instruction
	|				smsw_instruction
	|				stc_instruction
	|				std_instruction
	|				sti_instruction
	|				stmxcsr_instruction
	|				stosb_instruction
	|				stosw_instruction
	|				stosd_instruction
	|				str_instruction
	|				sub_instruction
	|				swapgs_instruction
	|				syscall_instruction
	|				sysenter_instruction
	|				sysexit_instruction
	|				sysret_instruction
	|				test_instruction
	|				ud2_instruction
	|				verr_instruction
	|				verw_instruction
	|				wait_instruction
	|				fwait_instruction
	|				wbinvd_instruction
	|				wrmsr_instruction
	|				xadd_instruction
	|				xchg_instruction
	|				xgetbv_instruction
	|				xlat_instruction
	|				xlatb_instruction
	|				xor_instruction
	|				xrstor_instruction
	|				xsave_instruction
	|				xsetbv_instruction
	;

fpu_instruction:
	;
	
simd_instruction:
	;
	
vm_instruction:
	;

aaa_instruction:    AAA
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAA, "\x37", 1, 0xFF);
					}
	;

aad_instruction:    AAD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAD, "\xD5\x0A", 2, 0xFF);
					}
	|				AAD immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAD, "\xD5", 1, 0xFF);
					}
	;

aam_instruction:    AAM
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAM, "\xD4\x0A", 2, 0xFF);
					}
	|				AAM immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAM, "\xD4", 1, 0xFF);
					}
	;

aas_instruction:    AAS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, AAS, "\x3F", 1, 0xFF);
					}
	;

adc_instruction:	ADC register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x14", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x80", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				ADC ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x80", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x15", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				ADC ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x15", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 2;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				ADC ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x81", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				ADC register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x83", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
    |				ADC register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x10", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADC ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x10", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADC register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADC ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADC register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADC ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x11", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADC register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x12", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				ADC register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x13", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				ADC register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADC, "\x13", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
	
add_instruction:	ADD register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x04", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x80", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				ADD ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x80", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x05", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				ADD ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x05", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				ADD ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x81", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				ADD register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x83", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				ADD register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x00", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADD ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x00", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADD register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADD ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADD register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				ADD ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x01", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				ADD register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x02", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				ADD register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x03", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				ADD register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ADD, "\x03", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
								
and_instruction:	AND register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x24", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x80", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				AND ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x80", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x24", 1, 0xFF);		   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				AND ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x25", 1, 0xFF);  
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 4;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				AND ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x81", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				AND register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x83", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				AND register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x20", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				AND ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x20", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				AND register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				AND ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				AND register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				AND ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x21", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				AND register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x22", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				AND register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x23", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				AND register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, AND, "\x23", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
	
arpl_instruction:	ARPL register_16bits ca register_16bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ANDNPS, "\x63", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ARPL ptr_16bits mem ca register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, ARPL, "\x63", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	;

bound_instruction:	BOUND register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BOUND, "\x62", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				BOUND register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, BOUND, "\x62", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

bsf_instruction:	BSF register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				BSF register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				BSF register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);				
					}
	|				BSF register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, BSF, "\x0F\xBC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);	
					}
	;
					
bsr_instruction:	BSR register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				BSR register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				BSR register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				BSR register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, BSR, "\x0F\xBD", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

bswap_instruction:	BSWAP register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, BSWAP, "\x0F\xC8", 2, 0xFF);
					}
	;
	
bt_instruction:		BT register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BT register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BT ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BT ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xA3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BT register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BT register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BT ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				BT ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BT, "\x0F\xBA", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	;
	
btc_instruction:	BTC register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTC register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTC ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTC ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTC register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTC register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTC ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				BTC ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTC, "\x0F\xBA", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	;

btr_instruction:	BTR register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTR register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTR ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTR ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xB3", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTR register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);						
					}
	|				BTR register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTR ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				BTR ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTR, "\x0F\xBA", 2, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	;

bts_instruction:	BTS register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTS register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTS ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTS ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xAB", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				BTS register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTS register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				BTS ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				BTS ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, BTS, "\x0F\xBA", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	;

call_instruction:	CALL label
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
	|				CALL immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
	|				CALL immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xE8", 1, 0xFF);
					}
	|				CALL register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				CALL register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				CALL ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);			    
					    pCurrAsmObj->ModRM.RO = 2;
					}
	|				CALL ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CALL, "\xFF", 1, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
	;

cbw_instruction:	CBW
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CBW, "\x98", 1, 0xFF);
					}
	;
	
cwde_instruction:	CWDE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CWDE, "\x98", 1, 0xFF);
					}
	;
	
clc_instruction:	CLC
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CLC, "\xF8", 1, 0xFF);	
					}
	;
	
cld_instruction:	CLD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CLD, "\xFC", 1, 0xFF);
					}
	;
	
clflush_instruction:CLFLUSH ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CLFLUSH, "\x0F\xAE", 2, 7);
					    pCurrAsmObj->ModRM.RO = 7;
					}
	;

cli_instruction:	CLI
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CLI, "\xFA", 1, 0xFF);
					}
	;
	
clts_instruction:	CLTS
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CLTS, "\x0F\x06", 2, 0xFF);
					}
	;

cmc_instruction:	CMC
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMC, "\xF5", 1, 0xFF);
					}
	;
	
cmovcc_instruction:	cmova_instruction { $$ = CMOVA; }
	|				cmovae_instruction { $$ = CMOVAE; }
	|				cmovb_instruction { $$ = CMOVB; }
	|				cmovbe_instruction { $$ = CMOVBE; }
	|				cmovc_instruction { $$ = CMOVC; }
	|				cmove_instruction { $$ = CMOVE; }
	|				cmovg_instruction { $$ = CMOVG; }
	|				cmovge_instruction { $$ = CMOVGE; }
	|				cmovl_instruction { $$ = CMOVL; }
	|				cmovle_instruction { $$ = CMOVLE; }
	|				cmovna_instruction { $$ = CMOVNA; }
	|				cmovnae_instruction { $$ = CMOVNAE; }
	|				cmovnb_instruction { $$ = CMOVNB; }
	|				cmovnbe_instruction { $$ = CMOVNBE; }
	|				cmovnc_instruction { $$ = CMOVNC; }
	|				cmovne_instruction { $$ = CMOVNE; }
	|				cmovng_instruction { $$ = CMOVNG; }
	|				cmovnge_instruction { $$ = CMOVGE; }
	|				cmovnl_instruction { $$ = CMOVNL; }
	|				cmovnle_instruction { $$ = CMOVNLE; }
	|				cmovno_instruction { $$ = CMOVNO; }
	|				cmovnp_instruction { $$ = CMOVNP; }
	|				cmovns_instruction { $$ = CMOVNS; }
	|				cmovnz_instruction { $$ = CMOVNZ; }
	|				cmovo_instruction { $$ = CMOVO; }
	|				cmovp_instruction { $$ = CMOVP; }
	|				cmovpe_instruction { $$ = CMOVPE; }
	|				cmovpo_instruction { $$ = CMOVPO; }
	|				cmovs_instruction { $$ = CMOVS; }
	|				cmovz_instruction { $$ = CMOVZ; }
	;
	
cmova_instruction:	CMOVA register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVA register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVA register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVA register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVA, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovae_instruction:	CMOVAE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVAE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVAE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVAE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVAE, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovb_instruction:	CMOVB register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVB register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVB register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVB register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVB, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);				
					}
	;

cmovbe_instruction: CMOVBE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVBE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVBE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVBE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVBE, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovc_instruction:	CMOVC register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVC register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVC register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVC register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVC, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmove_instruction:  CMOVE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVE, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovg_instruction:	CMOVG register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVG register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVG register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVG register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVG, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovge_instruction:	CMOVGE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVGE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVGE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVGE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVGE, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovl_instruction:	CMOVL register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVL register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVL register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVL register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVL, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovle_instruction:	CMOVLE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVLE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVLE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVLE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVLE, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovna_instruction:	CMOVNA register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNA register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNA register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNA register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNA, "\x0F\x46", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnae_instruction:CMOVNAE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNAE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNAE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNAE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNAE, "\x0F\x42", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnb_instruction:	CMOVNB register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNB register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNB register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNB register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNB, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnbe_instruction:CMOVNBE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNBE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNBE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNBE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNBE, "\x0F\x47", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnc_instruction:	CMOVNC register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNC register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNC register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNC register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNC, "\x0F\x43", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;
	
cmovne_instruction:	CMOVNE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNE, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovng_instruction:	CMOVNG register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNG register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNG register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNG register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNG, "\x0F\x4E", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnge_instruction:CMOVNGE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNGE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNGE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNGE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNGE, "\x0F\x4C", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnl_instruction:	CMOVNL register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNL register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNL register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNL register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNL, "\x0F\x4D", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnle_instruction:CMOVNLE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNLE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNLE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNLE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNLE, "\x0F\x4F", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovno_instruction:	CMOVNO register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNO register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNO register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNO register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNO, "\x0F\x41", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnp_instruction:	CMOVNP register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNP register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNP register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNP register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNP, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovns_instruction:	CMOVNS register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNS register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNS, "\x0F\x49", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovnz_instruction:	CMOVNZ register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNZ register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVNZ register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVNZ register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVNZ, "\x0F\x45", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovo_instruction:	CMOVO register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVO register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVO register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVO register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVO, "\x0F\x40", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovp_instruction:	CMOVP register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVP register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVP register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVP register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVP, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovpe_instruction:	CMOVPE register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVPE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVPE register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVPE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPE, "\x0F\x4A", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovpo_instruction:	CMOVPO register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVPO register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVPO register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVPO register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVPO, "\x0F\x4B", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;


cmovs_instruction:	CMOVS register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVS register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVS, "\x0F\x48", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmovz_instruction:	CMOVZ register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVZ register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMOVZ register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CMOVZ register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMOVZ, "\x0F\x44", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cmp_instruction:	CMP register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x80", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				CMP ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x80", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    |				CMP register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				CMP ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
						pCurrAsmObj->ModRM.RO = 4;
					}
    |				CMP register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 7;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				CMP ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x81", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				CMP register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    |				CMP ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    |				CMP register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    |				CMP ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x83", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
    |				CMP register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x38", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				CMP ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x38", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				CMP register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				CMP ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				CMP register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				CMP ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x39", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				CMP register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CMP register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				CMP register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, CMP, "\x3B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
		
cmpsb_instruction:	CMPSB
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSB, "\xA6", 1, 0xFF);
					}
	;

cmpsw_instruction:	CMPSW
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSW, "\xA7", 1, 0xFF);
					}
	;

cmpsd_instruction:	CMPSD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPSD, "\xA7", 1, 0xFF);
					}
	;
	
cmpxchg_instruction:CMPXCHG register_8bits ca register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB0", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				CMPXCHG ptr_8bits mem ca register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB0", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				CMPXCHG register_16bits ca register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				CMPXCHG register_32bits ca register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				CMPXCHG ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				CMPXCHG ptr_32bits mem ca register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG, "\x0F\xB1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	;

cmpxchg8b_instruction:CMPXCHG8B
					  {
							SetAsmObj(pCurrAsmObj, IC_X86, CMPXCHG8B, "\x0F\C7", 2, 1);
							pCurrAsmObj->ModRM.RO = 1;
					  }
	;

cpuid_instruction:	CPUID
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CPUID, "\x0F\xA2", 2, 0xFF);
					}
	;

crc32_instruction:	CRC32 register_32bits ca register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF0", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CRC32 register_32bits ca ptr_8bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF0", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CRC32 register_32bits ca register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CRC32 register_32bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				CRC32 register_32bits ca register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				CRC32 register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CRC32, "\xF2\x0F\x38\xF1", 4, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);					
					}
	;

cwd_instruction:	CWD
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, CWD, "\x99", 1, 0xFF);
					}
	;

cdq_instruction:	CDQ
					{
						SetAsmObj(pCurrAsmObj, IC_X86, CDQ, "\x99", 1, 0xFF);
					}
	;

daa_instruction:	DAA
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DAA, "\x27", 1, 0xFF);
					}
	;

das_instruction:	DAS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DAS, "\x2F", 1, 0xFF);
					}
	;

dec_instruction:	DEC register_8bits
					{
						__byte bOpCode = '\xFE' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				DEC ptr_8bits mem
					{
						__byte bOpCode = '\xFE' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				DEC register_16bits
					{
						__byte bOpCode = '\x48' + GetRegisterIndex($2);
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 0xFF);
					}
	|				DEC ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, "\xFF", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				DEC register_32bits
					{
						__byte bOpCode = '\x48' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, &bOpCode, 1, 0xFF);
					}
	|				DEC ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DEC, "\xFF", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}					
	;

div_instruction:	DIV register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF6", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				DIV ptr_8bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF6", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				DIV register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				DIV ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				DIV register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				DIV ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, DIV, "\xF7", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}					
	;

enter_instruction:	ENTER register_16bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ENTER, "\xC8", 1, 0xFF);
					}
	;

hlt_instruction:	HLT
					{
						SetAsmObj(pCurrAsmObj, IC_X86, HLT, "\xF4", 1, 0xFF);
					}
	;

idiv_instruction:	IDIV register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF6", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				IDIV ptr_8bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF6", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				IDIV register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				IDIV ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				IDIV register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				IDIV ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IDIV, "\xF7", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}					
	;

imul_instruction:	IMUL register_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF6", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;	
					}
	|				IMUL ptr_8bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF6", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				IMUL register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				IMUL ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				IMUL register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				IMUL ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\xF7", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				IMUL register_16bits ca register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
					}
	|				IMUL register_32bits ca register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x0F\xAF", 2, 0xFF);
					}
	|				IMUL register_16bits ca register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_16bits ca ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
					}
	|				IMUL register_32bits ca register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_32bits ca ptr_32bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x6B", 1, 0xFF);					
					}
	|				IMUL register_16bits ca register_16bits ca immediate_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_16bits ca ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
					}
	|				IMUL register_32bits ca register_32bits ca immediate_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				IMUL register_32bits ca ptr_32bits mem ca immediate_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IMUL, "\x69", 1, 0xFF);
					}
	;

in_instruction:		IN R_AL ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE4", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				IN R_AX ca immediate_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE5", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				IN R_EAX ca immediate_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xE5", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				IN R_AL ca R_DX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xEC", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				IN R_AX ca R_DX
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xED", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				IN R_EAX ca R_DX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IN, "\xED", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);						
						pCurrAsmObj->bOperandCount = 2;
					}
	;

inc_instruction:	INC register_8bits
					{
						__byte bOpCode = '\xFE' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				INC ptr_8bits mem
					{
						__byte bOpCode = '\xFE' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				INC register_16bits
					{
						__byte bOpCode = '\x40' + GetRegisterIndex($2);
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0xFF);
					}
	|				INC ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INC, "\xFF", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				INC register_32bits
					{
						__byte bOpCode = '\x40' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, INC, &bOpCode, 1, 0xFF);
					}
	|				INC ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INC, "\xFF", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}					
	;

ins_instruction:	INS ptr_8bits mem ca R_DX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6C", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				INS ptr_16bits mem ca R_DX
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6D", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;				
						pCurrAsmObj->bOperandCount = 2;									
					}
	|				INS ptr_32bits mem ca R_DX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INS, "\x6D", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;				
						pCurrAsmObj->bOperandCount = 2;
					}
	;
	
insb_instruction:	INSB
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INSB, "\x6C", 1, 0xFF);
					}
	;

insw_instruction:	INSW
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, INSW, "\x6D", 1, 0xFF);					
					}
	;
	
insd_instruction:	INSD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INSD, "\x6D", 1, 0xFF);
					}
	;

int3_instruction:	INT3
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INT3, "\xCC", 1, 0xFF);						
					}
	;

into_instruction:	INTO
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INTO, "\xCE", 1, 0xFF);	
					}
	;
	
int_instruction:	INT immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INT, "\xCD", 1, 0xFF);
					}
	;	

invd_instruction:	INVD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INVD, "\x0F\x08", 2, 0xFF);	
					}
	;

invlpg_instruction:	INVLPG ptr_8bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, INVLPG, "\x0F\x01", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	;

iret_instruction:	IRET
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, IRET, "\xCF", 1, 0xFF);
					}
	|				IRETD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, IRETD, "\xCF", 1, 0xFF);					
					}
	;

jcc_instruction:	JCXZ label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JCXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;						
					}
	|				JECXZ label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JECXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
	|				JRCXZ label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JECXZ, "\xE3", 1, 0xFF);
						pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
	|				JA label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JA, "\x0F\x87", 2, 0xFF);	
					}
	|				JAE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JAE, "\x0F\x83", 2, 0xFF);
					}
	|				JB label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JB, "\x0F\x82", 2, 0xFF);
					}
	|				JBE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JB, "\x0F\x86", 2, 0xFF);					
					}
	|				JC label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JC, "\x0F\x82", 2, 0xFF);	
					}
	|				JE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JE, "\x0F\x84", 2, 0xFF);
					}
	|				JZ label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JZ, "\x0F\x84", 2, 0xFF);
					}
	|				JG label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JG, "\x0F\x8F", 2, 0xFF);
					}
	|				JGE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JGE, "\x0F\x8D", 2, 0xFF);
					}
	|				JL label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JL, "\x0F\x8C", 2, 0xFF);
					}
	|				JLE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JLE, "\x0F\x8E", 2, 0xFF);
					}
	|				JNA label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNA, "\x0F\x86", 2, 0xFF);
					}
	|				JNAE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNAE, "\x0F\x82", 2, 0xFF);					
					}
	|				JNB label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNB, "\x0F\x83", 2, 0xFF);
					}
	|				JNBE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNBE, "\x0F\x87", 2, 0xFF);
					}
	|				JNC label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNC, "\x0F\x83", 2, 0xFF);
					}
	|				JNE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNE, "\x0F\x85", 2, 0xFF);					
					}
	|				JNG label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNG, "\x0F\x8E", 2, 0xFF);	
					}
	|				JNGE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNGE, "\x0F\x8C", 2, 0xFF);
					}
	|				JNL label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNL, "\x0F\x8D", 2, 0xFF);
					}
	|				JNLE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNLE, "\x0F\x8F", 2, 0xFF);
					}
	|				JNO label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNO, "\x0F\x81", 2, 0xFF);
					}
	|				JNP label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNP, "\x0F\x8B", 2, 0xFF);
					}
	|				JNS label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNS, "\x0F\x89", 2, 0xFF);
					}
	|				JNZ label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JNZ, "\x0F\x85", 2, 0xFF);
					}
	|				JO label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JO, "\x0F\x80", 2, 0xFF);
					}
	|				JP label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JP, "\x0F\x8A", 2, 0xFF);
					}
	|				JPE label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JPE, "\x0F\x8A", 2, 0xFF);
					}
	|				JPO label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JPO, "\x0F\x8B", 2, 0xFF);
					}
	|				JS label
					{
						SetAsmObj(pCurrAsmObj, IC_X86, JS, "\x0F\x88", 2, 0xFF);
					}												
	;


jmp_instruction:	JMP label
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
	|				JMP immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xEB", 1, 0xFF);
					}					
	|				JMP immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
	|				JMP immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xE9", 1, 0xFF);
					}
	|				JMP register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 4;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				JMP register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 4;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				JMP ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);			    
					    pCurrAsmObj->ModRM.RO = 4;
					}
	|				JMP ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, JMP, "\xFF", 1, 4);			    
					    pCurrAsmObj->ModRM.RO = 4;
					}
	;

lahf_instruction:	LAHF
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LAHF, "\x9F", 1, 0xFF);
					}
	;

lar_instruction:	LAR register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				LAR register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LAR register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				LAR register_32bits ca ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LAR, "\x0F\x02", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}					
	;

lds_instruction:	LDS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LDS, "\xC5", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LDS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LDS, "\xC5", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

lss_instruction:	LSS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSS, "\x0F\xB2", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LSS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LSS, "\x0F\xB2", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

les_instruction:	LES register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LES, "\xC4", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LES register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LES, "\xC4", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

lfs_instruction:	LFS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LFS, "\x0F\xB4", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LFS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LFS, "\x0F\xB4", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
	
lgs_instruction:	LGS register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LGS, "\x0F\xB5", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LGS register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LGS, "\x0F\xB5", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

lea_instruction:	LEA register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LEA, "\x8D", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LEA register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LEA, "\x8D", 1, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

leave_instruction:	LEAVE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LEAVE, "\xC9", 1, 0xFF);
					}
	;

lfence_instruction:	LFENCE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LFENCE, "\x0F\xAE", 2, 5);
					    pCurrAsmObj->ModRM.RO = 5;
					}
	;

lgdt_instruction:	LGDT ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LGDT, "\x0F\x01", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
	|				LGDT ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LGDT, "\x0F\x01", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
	;

lidt_instruction:	LIDT ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LIDT, "\x0F\x01", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
	|				LIDT ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LIDT, "\x0F\x01", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
	;

lldt_instruction:	LLDT register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LLDT, "\x0F\x00", 2, 2);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 2;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				LLDT ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LLDT, "\x0F\x00", 2, 2);
					    pCurrAsmObj->ModRM.RO = 2;
					}
	;

lmsw_instruction:	LMSW register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LMSW, "\x0F\x01", 2, 6);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = 6;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				LMSW ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LMSW, "\x0F\x01", 2, 6);
					    pCurrAsmObj->ModRM.RO = 6;
					}
	;

lodsb_instruction:	LODSB
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSB, "\xAC", 1, 0xFF);
					}
	;
	
lodsw_instruction:	LODSW
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSW, "\xAD", 1, 0xFF);
					}
	;
	
lodsd_instruction:	LODSD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LODSD, "\xAD", 1, 0xFF);
					}
	;

loop_instruction:	LOOP label
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOP, "\xE2", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
	;
	
loope_instruction:	LOOPE label
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOPE, "\xE1", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
	;
	
loopne_instruction: LOOPNE label
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LOOPNE, "\xE0", 1, 0xFF);
					    pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
					}
	;

lsl_instruction:	LSL register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				LSL register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				LSL register_32bits ca register_32bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.Mod = 3;
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				LSL register_32bits ca ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x03", 2, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

ltr_instruction:	LTR register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x00", 2, 3);
					    pCurrAsmObj->bUseModRM = TRUE;
					    pCurrAsmObj->ModRM.RO = 3;
					    pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				LTR ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, LSL, "\x0F\x00", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
	;

mfence_instruction:	MFENCE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MFENCE, "\x0F\xAE", 2, 6);
					    pCurrAsmObj->ModRM.RO = 6;
					}
	;

monitor_instruction:MONITOR
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MONITOR, "\x0F\x01\xC8", 3, 0xFF);						
					}
	;

mov_instruction:	MOV register_8bits ca immediate_8bits
					{
						__byte bOpcode = '\xB0' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
	|				MOV ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC6", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				MOV register_16bits ca immediate_16bits
					{
						__byte bOpcode = '\xB8' + GetRegisterIndex($2);
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
    |				MOV ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				MOV register_32bits ca immediate_32bits
					{
						__byte bOpcode = '\xB8' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, MOV, &bOpcode, 1, 0xFF);
					}
    |				MOV ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\xC7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				MOV register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x88", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				MOV ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x88", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				MOV register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				MOV ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				MOV register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				MOV ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x89", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				MOV register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOV register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				MOV register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				MOV register_16bits ca register_seg
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8C", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}	
    |				MOV ptr_16bits mem ca register_seg
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8C", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
					
    |				MOV register_seg ca register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8E", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}	
    |				MOV register_seg ca ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x8E", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}					
							
	|				MOV register_32bits ca register_ctl
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x20", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);	
					}
	|				MOV register_ctl ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x22", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOV register_32bits ca register_dbg
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x21", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOV register_dbg ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOV, "\x0F\x23", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	;

movbe_instruction:	MOVBE register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF0", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVBE ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF1", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVBE register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF0", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVBE ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVBE, "\x0F\x38\xF1", 3, 0xFF);
					    pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

movsb_instruction:	MOVSB
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSB, "\xA4", 1, 0xFF);
					}
	;
	
movsw_instruction:	MOVSW
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSW, "\xA5", 1, 0xFF);
					}
	;
	
movsd_instruction:	MOVSD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSD, "\xA5", 1, 0xFF);
					}
	;
	
movsx_instruction:	MOVSX register_16bits ca register_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVSX register_16bits ca ptr_8bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVSX register_32bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVSX register_32bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBE", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVSX register_32bits ca register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBF", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVSX register_32bits ca ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVSX, "\x0F\xBF", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

movzx_instruction:	MOVZX register_16bits ca register_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVZX register_16bits ca ptr_8bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVZX register_32bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVZX register_32bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB6", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				MOVZX register_32bits ca register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB7", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				MOVZX register_32bits ca ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MOVZX, "\x0F\xB7", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;
	
mul_instruction:	MUL register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF6", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				MUL ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF6", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				MUL register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				MUL ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				MUL register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				MUL ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MUL, "\xF7", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	;

mwait_instruction:	MWAIT
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, MWAIT, "\x0F\x01\xC9", 3, 0xFF);
					}
	;

neg_instruction:	NEG register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF6", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NEG ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF6", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				NEG register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NEG ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				NEG register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NEG ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NEG, "\xF7", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	;

nop_instruction:	NOP
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x90", 1, 0xFF);
					}
	|				NOP register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NOP ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				NOP register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NOP ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOP, "\x0F\x1F", 2, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	;

not_instruction:	NOT register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF6", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NOT ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF6", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				NOT register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NOT ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				NOT register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				NOT ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, NOT, "\xF7", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	;

or_instruction:		OR register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x80", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				OR ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x80", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				OR ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 1;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				OR ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x81", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				OR register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x83", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
    |				OR register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x08", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				OR ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x08", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				OR register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				OR ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				OR register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				OR ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x09", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				OR register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				OR register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				OR register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, OR, "\x0B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;


out_instruction:	OUT immediate_8bits ca R_AL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE6", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUT immediate_8bits ca R_AX
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE7", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUT immediate_8bits ca R_EAX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xE7", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUT R_DX ca R_AL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEE", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_AL, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUT R_DX ca R_AX
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEF", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_16_BITS, R_AX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUT R_DX ca R_EAX
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUT, "\xEF", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
						pCurrAsmObj->bOperandCount = 2;
					}
	;

outs_instruction:	OUTS R_DX ca ptr_8bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUTS R_DX ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				OUTS R_DX ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUTS, "\x6F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, R_DX, NONE);
						pCurrAsmObj->ModRM.RO = R_DX;
						pCurrAsmObj->bOperandCount = 2;
					}
	;
	
outsb_instruction:	OUTSB
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSB, "\x6E", 1, 0xFF);					
					}
	;

outsw_instruction:	OUTSW
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSW, "\x6F", 1, 0xFF);
					}
	;
	
outsd_instruction:	OUTSD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, OUTSD, "\x6F", 1, 0xFF);
					}
	;

	
pause_instruction:	PAUSE
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PAUSE, "\xF3\x90", 2, 0xFF);
					}
	;

pop_instruction:	POP register_16bits
					{
						__byte bOpcode = '\x58' + GetRegisterIndex($2);
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POP, &bOpcode, 1, 0xFF);	
					}
	|				POP ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x8F", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				POP register_32bits
					{
						__byte bOpcode = '\x58' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, POP, &bOpcode, 1, 0xFF);
					}
	|				POP ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x8F", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				POP SEG_DS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x1F", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_DS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				POP SEG_ES
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x07", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_ES, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				POP SEG_SS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x17", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_SS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				POP SEG_FS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x0F\xA1", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_FS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				POP SEG_GS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POP, "\x0F\xA9", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_GS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	;

popa_instruction:	POPA
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPA, "\x61", 1, 0xFF);
					}
	;
	
popad_instruction:	POPAD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POPAD, "\x61", 1, 0xFF);
					}
	;

popcnt_instruction:	POPCNT register_16bits ca register_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				POPCNT register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				POPCNT register_32bits ca register_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
					}
	|				POPCNT register_32bits ca ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POPCNT, "\xF3\x0F\xB8", 3, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

popf_instruction:	POPF
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, POPF, "\x9D", 1, 0xFF);
					}
	;
	
popfd_instruction:	POPFD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, POPFD, "\x9D", 1, 0xFF);
					}
	;

prefetcht0_instruction:	PREFETCHT0 ptr_8bits mem
						{
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT0, "\x0F\x18", 2, 1);
							pCurrAsmObj->ModRM.RO = 1;
						}
	;

prefetcht1_instruction:	PREFETCHT1 ptr_8bits mem
						{
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT1, "\x0F\x18", 2, 2);
							pCurrAsmObj->ModRM.RO = 2;
						}
	;

prefetcht2_instruction:	PREFETCHT2 ptr_8bits mem
						{
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHT2, "\x0F\x18", 2, 3);
							pCurrAsmObj->ModRM.RO = 3;
						}
	;

prefetchnta_instruction:PREFETCHNTA ptr_8bits mem
						{
							SetAsmObj(pCurrAsmObj, IC_X86, PREFETCHNTA, "\x0F\x18", 2, 0);
							pCurrAsmObj->ModRM.RO = 0;
						}
	;

push_instruction:	PUSH register_16bits
					{
						__byte bOpcode = '\x50' + GetRegisterIndex($2);
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, &bOpcode, 1, 0xFF);	
					}
	|				PUSH ptr_16bits mem
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\xFF", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				PUSH register_32bits
					{
						__byte bOpcode = '\x50' + GetRegisterIndex($2);
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, &bOpcode, 1, 0xFF);	
					}
	|				PUSH ptr_32bits mem
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\xFF", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				PUSH immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x6A", 1, 0xFF);
					}
	|				PUSH immediate_16bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x68", 1, 0xFF);
					}
	|				PUSH immediate_32bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x68", 1, 0xFF);
					}
	|				PUSH SEG_CS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_CS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				PUSH SEG_DS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x1E", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_DS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				PUSH SEG_ES
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x06", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_ES, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				PUSH SEG_SS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x16", 1, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_16_BITS, SEG_SS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				PUSH SEG_FS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0F\xA0", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_FS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	|				PUSH SEG_GS
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSH, "\x0F\xA8", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[0]), OP_REG, ASMER_32_BITS, SEG_GS, NONE);
						pCurrAsmObj->bOperandCount = 1;
					}
	;

pusha_instruction:	PUSHA
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHA, "\x60", 1, 0xFF);
					}
	;
	
pushad_instruction:	PUSHAD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHAD, "\x60", 1, 0xFF);
					}
	;

pushf_instruction:	PUSHF
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHF, "\x9C", 1, 0xFF);
					}
	;
	
pushfd_instruction:	PUSHFD
					{
						SetAsmObj(pCurrAsmObj, IC_X86, PUSHFD, "\x9C", 1, 0xFF);
					}
	;

rcl_instruction:	RCL register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC0", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCL register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCL register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCL ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC0", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				RCL ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				RCL ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xC1", 1, 2);
						pCurrAsmObj->ModRM.RO = 2;
					}
	|				RCL register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD2", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCL register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCL register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCL ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD2", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCL ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCL ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCL, "\xD3", 1, 2);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 2;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

rcr_instruction:	RCR register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC0", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCR register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCR register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				RCR ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC0", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				RCR ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				RCR ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xC1", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				RCR register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD2", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCR register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCR register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCR ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD2", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCR ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				RCR ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RCR, "\xD3", 1, 3);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 3;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

rol_instruction:	ROL register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC0", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROL register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROL register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROL ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC0", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				ROL ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				ROL ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xC1", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
	|				ROL register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD2", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROL register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROL register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROL ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD2", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROL ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROL ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROL, "\xD3", 1, 0);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

ror_instruction:	ROR register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC0", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROR register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROR register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				ROR ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC0", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				ROR ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				ROR ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xC1", 1, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	|				ROR register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD2", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROR register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROR register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROR ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD2", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROR ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				ROR ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, ROR, "\xD3", 1, 1);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

rdmsr_instruction:	RDMSR
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RDMSR, "\x0F\x32", 2, 0xFF);
					}
	;

rdpmc_instruction:	RDPMC
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RDPMC, "\x0F\x33", 2, 0xFF);
					}
	;

rdtsc_instruction:	RDTSC
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RDTSC, "\x0F\x31", 2, 0xFF);
					}
	;

rdtscp_instruction:	RDTSCP
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RDTSCP, "\x0F\x01\xF9", 3, 0xFF);
					}
	;

ret_instruction:	RET
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RET, "\xC3", 1, 0xFF);
					}
	;

retn_instruction:	RETN immediate_16bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RETN, "\xC2", 1, 0xFF);
					}
	;

rsm_instruction:	RSM
					{
						SetAsmObj(pCurrAsmObj, IC_X86, RSM, "\x0F\xAA", 2, 0xFF);
					}
	;

sahf_instruction:	SAHF
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAHF, "\x9E", 1, 0xFF);
					}
	;

sal_instruction:	SAL register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC0", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAL register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAL register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAL ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC0", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SAL ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SAL ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SAL register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAL register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAL register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAL ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAL ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAL ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

sar_instruction:	SAR register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC0", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAR register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAR register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SAR ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC0", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				SAR ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				SAR ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xC1", 1, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	|				SAR register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD2", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAR register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAR register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAR ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD2", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAR ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SAR ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SAR, "\xD3", 1, 7);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 7;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

shl_instruction:	SHL register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC0", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHL register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHL register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHL ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC0", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SHL ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SHL ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xC1", 1, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	|				SHL register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHL register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHL register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHL ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD2", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHL ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHL ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHL, "\xD3", 1, 4);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

shr_instruction:	SHR register_8bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC0", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHR register_16bits ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHR register_32bits ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHR ptr_8bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC0", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				SHR ptr_16bits mem ca immediate_8bits
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				SHR ptr_32bits mem ca immediate_8bits
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xC1", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				SHR register_8bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD2", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHR register_16bits ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHR register_32bits ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHR ptr_8bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD2", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHR ptr_16bits mem ca R_CL
					{
						SetPrefix66();
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
	|				SHR ptr_32bits mem ca R_CL
					{
						SetAsmObj(pCurrAsmObj, IC_X86, SHR, "\xD3", 1, 5);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[1]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->bOperandCount = 2;
					}
	;

sbb_instruction:	SBB register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x80", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				SBB ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x80", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				SBB ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 3;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				SBB ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x81", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
	|				SBB register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x83", 1, 3);
						pCurrAsmObj->ModRM.RO = 3;
					}
    |				SBB register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x18", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SBB ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x18", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SBB register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SBB ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SBB register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SBB ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x19", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SBB register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				SBB register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				SBB register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SBB, "\x1B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

scasb_instruction:	SCASB
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASB, "\xAE", 1, 0xFF);
					}
	;

scasw_instruction:	SCASW
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASW, "\xAF", 1, 0xFF);
					}
	;

scasd_instruction:	SCASD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SCASD, "\xAF", 1, 0xFF);
					}
	;

setcc_instruction:	seta_instruction { $$ = SETA; }
	|				setae_instruction { $$ = SETAE; }
	|				setb_instruction { $$ = SETB; }
	|				setbe_instruction { $$ = SETBE; }
	|				setc_instruction { $$ = SETC; }
	|				sete_instruction { $$ = SETE; }
	|				setg_instruction { $$ = SETG; }
	|				setge_instruction { $$ = SETGE; }
	|				setl_instruction { $$ = SETL; }
	|				setle_instruction { $$ = SETLE; }
	|				setna_instruction { $$ = SETNA; }
	|				setnae_instruction { $$ = SETNAE; }
	|				setnb_instruction { $$ = SETNB; }
	|				setnbe_instruction { $$ = SETNBE; }
	|				setnc_instruction { $$ = SETNC; }
	|				setne_instruction { $$ = SETNE; }
	|				setng_instruction { $$ = SETNG; }
	|				setnge_instruction { $$ = SETNGE; }
	|				setnl_instruction { $$ = SETNL; }
	|				setnle_instruction { $$ = SETNLE; }
	|				setno_instruction { $$ = SETNO; }
	|				setnp_instruction { $$ = SETNP; }
	|				setns_instruction { $$ = SETNS; }
	|				setnz_instruction { $$ = SETNZ; }
	|				seto_instruction { $$ = SETO; }
	|				setp_instruction { $$ = SETP; }
	|				setpe_instruction { $$ = SETPE; }
	|				setpo_instruction { $$ = SETPO; }
	|				sets_instruction { $$ = SETS; }
	|				setz_instruction { $$ = SETZ; }
	;
					

seta_instruction:	SETA register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETA, "\x0F\x97", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETA ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETA, "\x0F\x97", 2, 0xFF);
					}
	;

setae_instruction:	SETAE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETAE, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETAE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETAE, "\x0F\x93", 2, 0xFF);
					}
	;

setb_instruction:	SETB register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETB, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETB ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETB, "\x0F\x92", 2, 0xFF);
					}
	;

setbe_instruction:	SETBE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETBE, "\x0F\x96", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETBE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETBE, "\x0F\x96", 2, 0xFF);
					}
	;

setc_instruction:	SETC register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETC ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x92", 2, 0xFF);
					}
	;

sete_instruction:	SETE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x94", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETC, "\x0F\x94", 2, 0xFF);
					}
	;

setg_instruction:	SETG register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETG, "\x0F\x9F", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETG ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETG, "\x0F\x9F", 2, 0xFF);
					}
	;

setge_instruction:	SETGE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETGE, "\x0F\x9D", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETGE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETGE, "\x0F\x9D", 2, 0xFF);
					}
	;

setl_instruction:	SETL register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9C", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETL ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9C", 2, 0xFF);
					}
	;

setle_instruction:	SETLE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9E", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETLE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETL, "\x0F\x9E", 2, 0xFF);
					}
	;

setna_instruction:	SETNA register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNA, "\x0F\x96", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNA ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNA, "\x0F\x96", 2, 0xFF);
					}
	;

setnae_instruction:	SETNAE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNAE, "\x0F\x92", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNAE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNAE, "\x0F\x92", 2, 0xFF);
					}
	;

setnb_instruction:	SETNB register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNB, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNB ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNB, "\x0F\x93", 2, 0xFF);
					}
	;

setnbe_instruction:	SETNBE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNBE, "\x0F\x97", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNBE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNBE, "\x0F\x97", 2, 0xFF);
					}
	;

setnc_instruction:	SETNC register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNC, "\x0F\x93", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNC ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNC, "\x0F\x93", 2, 0xFF);
					}
	;

setne_instruction:	SETNE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNE, "\x0F\x95", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNE, "\x0F\x95", 2, 0xFF);
					}
	;

setng_instruction:	SETNG register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNG, "\x0F\x9E", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNG ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNG, "\x0F\x9E", 2, 0xFF);
					}
	;

setnge_instruction:	SETNGE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNGE, "\x0F\x9C", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNGE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNGE, "\x0F\x9C", 2, 0xFF);
					}
	;

setnl_instruction:	SETNL register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNL, "\x0F\x9D", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNL ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNL, "\x0F\x9D", 2, 0xFF);
					}
	;

setnle_instruction:	SETNLE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNLE, "\x0F\x9F", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNLE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNLE, "\x0F\x9F", 2, 0xFF);
					}
	;

setno_instruction:	SETNO register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNO, "\x0F\x91", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNO ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNO, "\x0F\x91", 2, 0xFF);
					}
	;

setnp_instruction:	SETNP register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNP, "\x0F\x9B", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNP ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNP, "\x0F\x9B", 2, 0xFF);
					}
	;

setns_instruction:	SETNS register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNS, "\x0F\x99", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNS ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNS, "\x0F\x99", 2, 0xFF);
					}
	;

setnz_instruction:	SETNZ register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNZ, "\x0F\x95", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETNZ ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETNZ, "\x0F\x95", 2, 0xFF);
					}
	;

seto_instruction:	SETO register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETO, "\x0F\x90", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETO ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETO, "\x0F\x90", 2, 0xFF);
					}
	;

setp_instruction:	SETP register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETP, "\x0F\x9A", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETP ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETP, "\x0F\x9A", 2, 0xFF);
					}
	;

setpe_instruction:	SETPE register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPE, "\x0F\x9A", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETPE ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPE, "\x0F\x9A", 2, 0xFF);
					}
	;

setpo_instruction:	SETPO register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPO, "\x0F\x9B", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETPO ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETPO, "\x0F\x9B", 2, 0xFF);
					}
	;

sets_instruction:	SETS register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETS, "\x0F\x98", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETS ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETS, "\x0F\x98", 2, 0xFF);
					}
	;

setz_instruction:	SETZ register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETZ, "\x0F\x94", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SETZ ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SETZ, "\x0F\x94", 2, 0xFF);
					}
	;

sfence_instruction:	SFENCE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SFENCE, "\x0F\xAE", 2, 7);
					    pCurrAsmObj->ModRM.RO = 7;
					}
	;

sgdt_instruction:	SGDT ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SGDT, "\x0F\x01", 2, 0);
					    pCurrAsmObj->ModRM.RO = 0;
					}
	;

shld_instruction:	SHLD register_16bits ca register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHLD ptr_16bits mem ca register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
					}
	|				SHLD register_16bits ca register_16bits ca R_CL
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHLD ptr_16bits mem ca register_16bits ca R_CL
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHLD register_32bits ca register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHLD ptr_32bits mem ca register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA4", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
					}
	|				SHLD register_32bits ca register_32bits ca R_CL
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHLD ptr_32bits mem ca register_32bits ca R_CL
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHLD, "\x0F\xA5", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->bOperandCount = 3;
					}
	;

shrd_instruction:	SHRD register_16bits ca register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHRD ptr_16bits mem ca register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
					}
	|				SHRD register_16bits ca register_16bits ca R_CL
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHRD ptr_16bits mem ca register_16bits ca R_CL
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHRD register_32bits ca register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SHRD ptr_32bits mem ca register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAC", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
					}
	|				SHRD register_32bits ca register_32bits ca R_CL
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						pCurrAsmObj->bOperandCount = 3;
					}
	|				SHRD ptr_32bits mem ca register_32bits ca R_CL
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SHRD, "\x0F\xAD", 2, 0xFF);
						SetOperandWithoutVal(&(pCurrAsmObj->Operand[2]), OP_REG, ASMER_8_BITS, R_CL, NONE);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->bOperandCount = 3;
					}			
	;

sidt_instruction:	SIDT ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SIDT, "\x0F\x01", 2, 1);
					    pCurrAsmObj->ModRM.RO = 1;
					}
	;

sldt_instruction:	SLDT ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SLDT, "\x0F\x00", 2, 0);
					    pCurrAsmObj->ModRM.RO = 0;
					}
	|				SLDT register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SLDT, "\x0F\x00", 2, 0);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 0;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	;

smsw_instruction:	SMSW register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				SMSW ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->ModRM.RO = 4;
					}
	|				SMSW register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SMSW, "\x0F\x01", 2, 4);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	;

stc_instruction:	STC
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STC, "\xF9", 1, 0xFF);	
					}
	;

std_instruction:	STD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STD, "\xFD", 1, 0xFF);
					}
	;

sti_instruction:	STI
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STI, "\xFB", 1, 0xFF);
					}
	;

stmxcsr_instruction:STMXCSR ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STMXCSR, "\x0F\xAE", 2, 3);
					    pCurrAsmObj->ModRM.RO = 3;
					}
	;

stosb_instruction:	STOSB
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSB, "\xAA", 1, 0xFF);
					}
	;

stosw_instruction:	STOSW
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSW, "\xAB", 1, 0xFF);
					}
	;

stosd_instruction:	STOSD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STOSW, "\xAB", 1, 0xFF);
					}
	;

str_instruction:	STR register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STR, "\x0F\x00", 2, 1);
					    pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 1;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				STR ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, STR, "\x0F\x00", 2, 1);
						pCurrAsmObj->ModRM.RO = 1;
					}
	;

sub_instruction:	SUB register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2C", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x80", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				SUB ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x80", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				SUB ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2D", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 5;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				SUB ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x81", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	|				SUB register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x83", 1, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
    |				SUB register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x28", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SUB ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x28", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SUB register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SUB ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SUB register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				SUB ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x29", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				SUB register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2A", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				SUB register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				SUB register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SUB, "\x2B", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

swapgs_instruction:	SWAPGS
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SWAPGS, "\x0F\x01", 2, 7);
						pCurrAsmObj->ModRM.RO = 7;
					}
	;

syscall_instruction:SYSCALL
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSCALL, "\x0F\x05", 2, 0xFF);
					}
	;

sysenter_instruction:SYSENTER
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSENTER, "\x0F\x34", 2, 0xFF);
					}
	;

sysexit_instruction:SYSEXIT
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSEXIT, "\x0F\x35", 2, 0xFF);
					}
	;

sysret_instruction:	SYSRET
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, SYSRET, "\x0F\x07", 2, 0xFF);
					}
	;

test_instruction:	TEST register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA8", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF6", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				TEST ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF6", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				TEST register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA9", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				TEST ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				TEST register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xA9", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 0;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				TEST ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\xF7", 1, 0);
						pCurrAsmObj->ModRM.RO = 0;
					}
    |				TEST register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x84", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				TEST ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x84", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				TEST register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				TEST ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				TEST register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				TEST ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, TEST, "\x85", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	;

ud2_instruction:	UD2
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, UD2, "\x0F\x0B", 2, 0xFF);
					}
	;

verr_instruction:	VERR register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 4);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 4;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				VERR ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	;

verw_instruction:	VERW register_16bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 5);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = 5;
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				VERW ptr_16bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, VERR, "\x0F\x00", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	;

wait_instruction:	WAIT
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, WAIT, "\x9B", 1, 0xFF);
					}
	;

fwait_instruction:	FWAIT
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, FWAIT, "\x9B", 1, 0xFF);
					}
	;

wbinvd_instruction:	WBINVD
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, WBINVD, "\x0F\x09", 2, 0xFF);
					}
	;

wrmsr_instruction:	WRMSR
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, WRMSR, "\x0F\x30", 2, 0xFF);
					}
	;

xadd_instruction:	XADD register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC0", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				XADD ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC0", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				XADD register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				XADD ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				XADD register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				XADD ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XADD, "\x0F\xC1", 2, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	;

xchg_instruction:	XCHG register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
	|				XCHG ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				XCHG register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x86", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				XCHG register_16bits ca register_16bits
					{
						__byte bOpcode = 0;
						SetPrefix66();
						
						if ($2 == R_AX) {
							bOpcode = '\x90' + GetRegisterIndex($2);
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else if ($4 == R_AX) {
							bOpcode = '\x90' + GetRegisterIndex($4);
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else {
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				XCHG ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
	|				XCHG register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				XCHG register_32bits ca register_32bits
					{
						__byte bOpcode = 0;
						
						if ($2 == R_EAX) {
							bOpcode = '\x90' + GetRegisterIndex($4);
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else if ($4 == R_EAX) {
							bOpcode = '\x90' + GetRegisterIndex($2);
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, &bOpcode, 1, 0xFF);
						}
						else {
							SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($4);
						}
					}
	|				XCHG ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				XCHG register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XCHG, "\x87", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

xgetbv_instruction:	XGETBV
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XGETBV, "\x0F\x01\xD0", 3, 0xFF);
					}
	;

xlat_instruction:	XLAT ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XLAT, "\xD7", 1, 0xFF);
					}
	;

xlatb_instruction:	XLATB
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XLAT, "\xD7", 1, 0xFF);
					}
	;

xor_instruction:	XOR register_8bits ca immediate_8bits
					{
						if ($2 == R_AL) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x34", 1, 0xFF);
						} else {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x80", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
	|				XOR ptr_8bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x80", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR register_16bits ca immediate_16bits
					{
						SetPrefix66();
						if ($2 == R_AX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x35", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				XOR ptr_16bits mem ca immediate_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR register_32bits ca immediate_32bits
					{
						if ($2 == R_EAX) {
						    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x35", 1, 0xFF);	   
						} else {
							SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
							pCurrAsmObj->bUseModRM = TRUE;
							pCurrAsmObj->ModRM.Mod = 3;
							pCurrAsmObj->ModRM.RO = 6;
							pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
						}
					}
    |				XOR ptr_32bits mem ca immediate_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x81", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
	|				XOR register_16bits ca immediate_8bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR ptr_16bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR register_32bits ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR ptr_32bits mem ca immediate_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x83", 1, 6);
						pCurrAsmObj->ModRM.RO = 6;
					}
    |				XOR register_8bits ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x30", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				XOR ptr_8bits mem ca register_8bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x30", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				XOR register_16bits ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				XOR ptr_16bits mem ca register_16bits
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				XOR register_32bits ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->bUseModRM = TRUE;
						pCurrAsmObj->ModRM.Mod = 3;
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($4);
						pCurrAsmObj->ModRM.RM = GetRegisterIndex($2);
					}
    |				XOR ptr_32bits mem ca register_32bits
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x31", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($5);
					}
    |				XOR register_8bits ca ptr_8bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x32", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	|				XOR register_16bits ca ptr_16bits mem
					{
						SetPrefix66();
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x33", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
    |				XOR register_32bits ca ptr_32bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XOR, "\x33", 1, 0xFF);
						pCurrAsmObj->ModRM.RO = GetRegisterIndex($2);
					}
	;

xrstor_instruction:	XRSTOR ptr_64bits mem
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XRSTOR, "\x0F\xAE", 2, 5);
						pCurrAsmObj->ModRM.RO = 5;
					}
	;
	
xsave_instruction:	XSAVE
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XSAVE, "\x0F\xAE", 2, 4);
						pCurrAsmObj->ModRM.RO = 4;
					}
	;

xsetbv_instruction:	XSETBV
					{
					    SetAsmObj(pCurrAsmObj, IC_X86, XSETBV, "\x0F\x01\xD1", 3, 0xFF);
					}
	;

label:           ADDR_LAB
				 { 
					$$ = ADDR_LAB;
					pCurrAsmObj->Operand[g_iCurrOperand].bAddrLabel = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].bIsImmediate = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].Type = OP_IMM;
					pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
					pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = 0;//先设置为0				    
					pCurrAsmObj->pAddrLabelSymbolName = NextSymbol();//记录到所引用的地址标号
					(pCurrAsmObj->bOperandCount)++;
				 }
    ;

mem:			 register_seg mem_no_seg MEMEND
				 {
					pCurrAsmObj->bUsePrefix = TRUE;
				    pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = $1;
					(pCurrAsmObj->bPrefixCount)++;
				 }
    |            mem_no_seg MEMEND
				 {
				    pCurrAsmObj->bUseModRM = TRUE;
				    pCurrAsmObj->Operand[g_iCurrOperand].bIsMem = TRUE;
					pCurrAsmObj->Operand[g_iCurrOperand].Type = OP_MEM;
				    (pCurrAsmObj->bOperandCount)++;
				 }
	;

mem_no_seg:		 ADDR_LAB
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
	|			 displacement_32bits
				 {
				     pCurrAsmObj->ModRM.Mod = 0;
					 pCurrAsmObj->ModRM.RM = 5;
				 }
	|			 register_32bits_mem
				 {
				 	 pCurrAsmObj->ModRM.Mod = 0;
					 if ($1 == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex($1);
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $1;
				 }
	|			 register_32bits_mem sign displacement_8bits
				 {
				     pCurrAsmObj->ModRM.Mod = 1;
					 if ($1 == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex($1);
					 	 if ($2 == SUBSIGN) {
					         __byte bDisplacement8 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte;
						 	 bDisplacement8 = ~bDisplacement8 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
					 	 }
				     }
				     pCurrAsmObj->Operand[g_iCurrOperand].Base = $1;
				 }
	|			 register_32bits_mem sign displacement_32bits
				 {
				     pCurrAsmObj->ModRM.Mod = 2;
					 if ($1 == R_ESP) {
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->SIB.SS = 0;
						 pCurrAsmObj->SIB.Index = 4;
						 pCurrAsmObj->SIB.Base = 4;
                         pCurrAsmObj->bUseSIB = TRUE;
					 } else {
					     pCurrAsmObj->ModRM.RM = GetRegisterIndex($1);
					 	 if ($2 == SUBSIGN) {
					     	 __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $1;
				 }
	|			 scale register_32bits_mem
				 {
				     if ($2 == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
				         pCurrAsmObj->ModRM.Mod = 0;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 pCurrAsmObj->SIB.Base = 5;
						 /* Mod == 0, [scale index] + disp32 */
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = 0;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
					 }
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $2;
				 }
	|			 scale register_32bits_mem sign displacement_32bits
				 {
				     if ($2 == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
				         pCurrAsmObj->ModRM.Mod = 0;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 pCurrAsmObj->SIB.Base = 5;
					
						 if ($3 == SUBSIGN) {
					         __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $2;
				 }
	|			 scale register_32bits_mem PLUSSIGN register_32bits_mem
				 {
				     if ($2 == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
						 /*
                          * 如果Base寄存器为ebp, 那么还需要遵从
                          * Mod == 1, [scale index] + disp8的约定
                          */
						 if ($4 == R_EBP) {
				             pCurrAsmObj->ModRM.Mod = 1;
						 	 pCurrAsmObj->ModRM.RM = 4;
					     	 pCurrAsmObj->bUseSIB = TRUE;
					     	 pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 	 pCurrAsmObj->SIB.Base = 5;

						 	 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = 0;
						 	 pCurrAsmObj->bUseDisplacement = TRUE;
						 	 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
						 } else {
				             pCurrAsmObj->ModRM.Mod = 0;
						 	 pCurrAsmObj->ModRM.RM = 4;
					     	 pCurrAsmObj->bUseSIB = TRUE;
					     	 pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 	 pCurrAsmObj->SIB.Base = GetRegisterIndex($4);
						 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $2;
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = $4;
				 }
	|			 scale register_32bits_mem PLUSSIGN register_32bits_mem sign displacement_8bits
				 {
				     if ($2 == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
					     pCurrAsmObj->ModRM.Mod = 1;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 pCurrAsmObj->SIB.Base = GetRegisterIndex($4);

						 if ($5 == SUBSIGN) {
					         __byte bDisplacement8 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte;
						 	 bDisplacement8 = ~bDisplacement8 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $2;
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = $4;
				 }
	|			 scale register_32bits_mem PLUSSIGN register_32bits_mem sign displacement_32bits
				 {
				     if ($2 == R_ESP) {
					 	 /* 出错, Index寄存器不能为esp */
					 	 return -1;
					 } else {
					     pCurrAsmObj->ModRM.Mod = 1;
						 pCurrAsmObj->ModRM.RM = 4;
					     pCurrAsmObj->bUseSIB = TRUE;
					     pCurrAsmObj->SIB.Index = GetRegisterIndex($2);
						 pCurrAsmObj->SIB.Base = GetRegisterIndex($4);

						 if ($5 == SUBSIGN) {
					         __dword dwDisplacement32 = pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword;
						 	 dwDisplacement32 = ~dwDisplacement32 + 1;
						 	 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
					 	 }
					 }/* end else */
					 pCurrAsmObj->Operand[g_iCurrOperand].Base = $2;
					 pCurrAsmObj->Operand[g_iCurrOperand].Index = $4;
				 }
	;

prefix:          LOCK
				 {
				     $$ = LOCK;
					 pCurrAsmObj->bUsePrefix = TRUE;
					 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF0;
					 (pCurrAsmObj->bPrefixCount)++;
                 }
    |            repz_prefix
				 {
				     /* 鉴别是否是串指令, 如果不是则返回错误 */
					 int iNextToken = __PreFetcherToken__();
					 switch (iNextToken) {
					 case LODSB: case LODSW: case LODSD: case STOSB:
					 case STOSW: case STOSD: case CMPSB: case CMPSW:
					 case CMPSD: case SCASB: case SCASW: case SCASD: {
					     $$ = REPZ;
					 	 pCurrAsmObj->bUsePrefix = TRUE;
					 	 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF3;
					 	 (pCurrAsmObj->bPrefixCount)++;
					 } break;
					 default:
					     return -1;
					 }/* end switch */
				 }
	|			 repnz_prefix
				 {
				     /* 鉴别是否是串指令, 如果不是则返回错误 */
					 int iNextToken = __PreFetcherToken__();
					 switch (iNextToken) {
					 case LODSB: case LODSW: case LODSD: case STOSB:
					 case STOSW: case STOSD: case CMPSB: case CMPSW:
					 case CMPSD: case SCASB: case SCASW: case SCASD: {
					     $$ = REPNZ;
					 	 pCurrAsmObj->bUsePrefix = TRUE;
					 	 pCurrAsmObj->bPrefix[pCurrAsmObj->bPrefixCount] = 0xF2;
					 	 (pCurrAsmObj->bPrefixCount)++;
					 } break;
					 default:
					     return -1;
					 }/* end switch */
				 }
	|			 LINESTART
				 {
					/* 新的指令开始 */
					CreateNewAsmObj();
				 }
	;

repz_prefix:	 REP        { $$ = REP; }
    |			 REPE	    { $$ = REPE; }
	|			 REPZ	    { $$ = REPZ; }
	;

repnz_prefix:	 REPNE      { $$ = REPNE; }
    |			 REPNZ		{ $$ = REPNZ; }
	;

register_8bits: R_AL        
				{ 
					$$ = R_AL;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_AL, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    |			R_CL
				{
					$$ = R_CL;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_CL, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_DL		 
				{
					$$ = R_DL; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_DL, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_BL		 
				{ 
					$$ = R_BL; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_BL, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_AH		 
				{
					$$ = R_AH; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_AH, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|           R_CH
				{
					$$ = R_CH; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_CH, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_DH
				{
					$$ = R_DH;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_DH, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_BH		 
				{
					$$ = R_BH;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_8_BITS, R_BH, NONE); 
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_16bits:R_AX        
				{ 
					$$ = R_AX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_AX, NONE); 
					(pCurrAsmObj->bOperandCount)++; 
				}
    |			R_CX		 
				{ 
					$$ = R_CX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_CX, NONE); 
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_DX
				{
					$$ = R_DX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_DX, NONE); 
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_BX		 
				{
					$$ = R_BX; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_BX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_SP		
				{
					$$ = R_SP; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_SP, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_BP
				{
					$$ = R_BP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_BP, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_SI
				{
					$$ = R_SI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_SI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_DI
				{
					$$ = R_DI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_16_BITS, R_DI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_32bits:R_EAX
				{
					$$ = R_EAX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EAX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    |			R_ECX 
				{
					$$ = R_ECX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ECX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_EDX
				{
					$$ = R_EDX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EDX, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_EBX
				{
					$$ = R_EBX;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EBX, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ESP
				{
					$$ = R_ESP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ESP, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_EBP 		 
				{ 
					$$ = R_EBP;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EBP, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_ESI 		 
				{
					$$ = R_ESI; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_ESI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_EDI		 
				{
					$$ = R_EDI;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_EDI, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_ctl:	R_CR0       
				{
					$$ = R_CR0; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR0, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    |			R_CR1 		 
				{
					$$ = R_CR1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR1, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_CR2
				{
					$$ = R_CR2;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_CR3		 
				{
					$$ = R_CR3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR3, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_CR4 		 
				{
					$$ = R_CR4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR4, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_CR5
				{
					$$ = R_CR5; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_CR6
				{
					$$ = R_CR6;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_CR7
				{
					$$ = R_CR7; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_CR7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_dbg:	R_DR0       
				{ 
					$$ = R_DR0; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR0, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    |			R_DR1 		 
				{ 
					$$ = R_DR1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR1, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_DR2
				{
					$$ = R_DR2;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_DR3
				{
					$$ = R_DR3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR3, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_DR4 
				{
					$$ = R_DR4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR4, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_DR5 		 
				{
					$$ = R_DR5;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_DR6
				{
					$$ = R_DR6;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_DR7
				{
					$$ = R_DR7;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_32_BITS, R_DR7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_mmx:   R_MM0
				{
					$$ = R_MM0;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM0, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    |			R_MM1 		 
				{ 
					$$ = R_MM1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM1, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_MM2 		 
				{ 
					$$ = R_MM2; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM2, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_MM3		 
				{ 
					$$ = R_MM3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM3, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_MM4 		 
				{ 
					$$ = R_MM4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM4, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_MM5 	 	 
				{ 
					$$ = R_MM5; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM5, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_MM6 		 
				{ 
					$$ = R_MM6; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM6, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	|			R_MM7		 
				{ 
					$$ = R_MM7; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_64_BITS, R_MM7, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
	;

register_fpu:   R_ST0		 
				{ 
					$$ = R_ST0;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST0, NONE);
					(pCurrAsmObj->bOperandCount)++; 
				}
    |			R_ST1 		 
				{
					$$ = R_ST1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST1, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}  
	|			R_ST2 		 
				{
					$$ = R_ST2; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ST3		 
				{
					$$ = R_ST3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST3, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ST4 		 
				{
					$$ = R_ST4;
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST4, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ST5 
				{
					$$ = R_ST5; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ST6 
				{
					$$ = R_ST6; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_ST7
				{ 
					$$ = R_ST7; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_80_BITS, R_ST7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_xmm:   R_XMM0     
				{
					$$ = R_XMM0; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM0, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
    |			R_XMM1 	 
				{ 
					$$ = R_XMM1; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM1, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM2 	 
				{
					$$ = R_XMM2; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM2, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM3
				{
					$$ = R_XMM3; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM3, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM4
				{
					$$ = R_XMM4; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM4, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM5 	 
				{
					$$ = R_XMM5; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM5, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM6
				{
					$$ = R_XMM6; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM6, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	|			R_XMM7
				{
					$$ = R_XMM7; 
					SetOperandWithoutVal(&(pCurrAsmObj->Operand[g_iCurrOperand]), OP_REG, ASMER_128_BITS, R_XMM7, NONE);
					(pCurrAsmObj->bOperandCount)++;
				}
	;

register_32bits_mem: R_EAX       { $$ = R_EAX; }
    |				 R_ECX 		 { $$ = R_ECX; }
	|				 R_EDX 		 { $$ = R_EDX; }
	|				 R_EBX		 { $$ = R_EBX; }
	|				 R_ESP 		 { $$ = R_ESP; }
	|				 R_EBP 		 { $$ = R_EBP; }
	|				 R_ESI 		 { $$ = R_ESI; }
	|				 R_EDI		 { $$ = R_EDI; }
	;

register_seg:    SEG_ES      { $$ = 0x26; }
    |			 SEG_CS 	 { $$ = 0x2E; }
	|			 SEG_SS 	 { $$ = 0x36; }
	|			 SEG_DS 	 { $$ = 0x3E; }
	|			 SEG_FS 	 { $$ = 0x64; }
	|			 SEG_GS		 { $$ = 0x65; }
	;

scale:           SCALE_1     { $$ = 0; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 0; pCurrAsmObj->SIB.SS = 0; }
    |			 SCALE_2 	 { $$ = 1; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 1; pCurrAsmObj->SIB.SS = 1; }
	|			 SCALE_4 	 { $$ = 2; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 2; pCurrAsmObj->SIB.SS = 2; }
	|			 SCALE_8	 { $$ = 3; pCurrAsmObj->Operand[g_iCurrOperand].Scale = 3; pCurrAsmObj->SIB.SS = 3; }
	;

sign:            PLUSSIGN	 { $$ = PLUSSIGN; }
    |			 SUBSIGN     { $$ = SUBSIGN; }
	;

ptr_8bits:		 BYTE_PTR    { $$ = BYTE_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_8_BITS; }
    ;

ptr_16bits:		 WORD_PTR    { $$ = WORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_16_BITS; }
    ;

ptr_32bits:		 DWORD_PTR   { $$ = DWORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_32_BITS; }
    ;

ptr_64bits:	     QWORD_PTR	 { $$ = QWORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_64_BITS; }
	;
	
ptr_128bits:	 TWORD_PTR   { $$ = TWORD_PTR; pCurrAsmObj->Operand[g_iCurrOperand].Bit = ASMER_128_BITS; }
	;  		 

immediate_8bits:      IMMEDIATE8
				 	  {
					      __byte bImmediate8 = *(__byte *)GetImmediate(1);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
										NONE, 0xFF, ASMER_8_BITS, bImmediate8, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    ;

immediate_16bits:     IMMEDIATE16
				 	  {
					      __word wImmediate16 = *(__word *)GetImmediate(2);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
									    NONE, 0xFF, ASMER_16_BITS, wImmediate16, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    ;

immediate_32bits:     IMMEDIATE32
				 	  {
					      __dword dwImmediate32 = *(__dword *)GetImmediate(4);
					      SetOperand(&(pCurrAsmObj->Operand[g_iCurrOperand]), FALSE, OP_IMM, ASMER_0_BITS, NONE,\
									    NONE, 0xFF, ASMER_32_BITS, dwImmediate32, NULL, 0, NULL);
						  (pCurrAsmObj->bOperandCount)++;
				 	  }
    ;

displacement_8bits:	 DISPLACEMENT8
				 	 {
					     __byte bDisplacement8 = *(__byte *)GetImmediate(1);
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_8_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uByte = bDisplacement8;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
				 	 }
    ;

displacement_32bits: DISPLACEMENT32
				 	 {
					     __dword dwDisplacement32 = *(__dword *)GetImmediate(4);
						 pCurrAsmObj->Operand[g_iCurrOperand].ValBit = ASMER_32_BITS;
						 pCurrAsmObj->Operand[g_iCurrOperand].Val.uDword = dwDisplacement32;
						 pCurrAsmObj->bUseDisplacement = TRUE;
						 pCurrAsmObj->bDisplacementOwn = g_iCurrOperand;
				 	 }
    ;

cn:				 COLON		 { $$ = COLON; }

ca:              COMMA       { $$ = COMMA; g_iCurrOperand++; }

linend:          LINEND
				 {
					$$ = LINEND;
					g_pCurrAsmObjPoint = &((*g_pCurrAsmObjPoint)->pNext);
					g_iCurrOperand = 0;
				 }
    ;

%%
