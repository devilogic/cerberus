#if !defined(__CHAOSVM_CPU_X86_INTERRUPT_H__)
#define __CHAOSVM_CPU_X86_INTERRUPT_H__

/*
 *中断号
 */
#define __CPU_INTERRUPT_DE__	0		/* #DE   Divide Error            DIV and IDIV instructions.          */
#define __CPU_INTERRUPT_DB__	1       /* #DB   Debug                   Any code or data reference.         */
#define __CPU_INTERRUPT_BP__	3		/* #BP   Breakpoint              INT 3 instruction.                  */
#define __CPU_INTERRUPT_OF__	4		/* #OF   Overflow                INTO instruction.                   */
#define __CPU_INTERRUPT_BR__	5       /* #BR   BOUND Range Exceeded    BOUND instruction.                  */
#define __CPU_INTERRUPT_UD__	6		/* #UD   Invalid Opcode          UD2 instruction or reserved opcode. */
										/*       (UndefinedOpcode)											 */
#define __CPU_INTERRUPT_NM__	7       /* #NM   Device Not Available    Floating-point or WAIT/FWAIT instruction.*/
										/*       (NoMath Coprocessor)                                             */
#define __CPU_INTERRUPT_DF__	8       /* #DF   Double Fault            Any instruction that can generate an exception, */
										/*                               an NMI, or an INTR.							 */
#define __CPU_INTERRUPT_GP__	13		/* #GP   General Protection      memory reference and other protection checks. */
#define __CPU_INTERRUPT_PF__	14      /* #PF   Page Fault              Any memory reference.                */
#define __CPU_INTERRUPT_MF__	16		/* #MF   x87 FPU Floating-Point  Fault No x87 FPU floating-point or WAIT/FWAIT instruction.*/
										/*       Error (Math Fault)																   */

/*
 * EFLAGS寄存器相关定义 
 */
// 各标志位在EFLAGS寄存器中的位置
#define __EFLAG_INDEX_CF__   0
#define __EFLAG_INDEX_PF__   2
#define __EFLAG_INDEX_AF__   4
#define __EFLAG_INDEX_ZF__   6
#define __EFLAG_INDEX_SF__   7
/*Trap (bit 8) — Set to enable single-step mode for debugging; clear to
disable single-step mode. In single-step mode, the processor generates a
debug exception after each instruction. This allows the execution state of a
program to be inspected after each instruction. If an application program
sets the TF flag using a POPF, POPFD, or IRET instruction, a debug exception
is generated after the instruction that follows the POPF, POPFD, or IRET.*/
#define __EFLAG_INDEX_TF__   8 
#define __EFLAG_INDEX_IF__   9
#define __EFLAG_INDEX_DF__   10
#define __EFLAG_INDEX_OF__   11

// 占2位，用于保护模式，只有当任务的现行特权级CPL高于或者等于IOPL时，才能执行IN/OUT/INS/OUTS/STI/CLI/LOCK,否则产生异常13 (GP)
#define __EFLAG_INDEX_IOPL__ 12
// 任务嵌入标志
#define __EFLAG_INDEX_NT__   14
// 恢复标志。用于与调试寄存器的代码断点结合使用，以保证不重复出处理断点
#define __EFLAG_INDEX_RF	 16
/* 
 * 虚拟8086模式标志VM。保护模式下，VM置1时，CPU工作与虚拟8086模式。
 * 该位仅能以以下2种方式设置：
 * 1)保护模式下，由0级的代码段的IRET设置
 * 2)由任务转换来设置
 */
#define __EFLAG_INDEX_VM__   17
/*
 * 对齐检查标志AC。仅对80486/Pentium有效，若AC位为1，且CR0的对齐标志位AM为1，则对
 * 字、双字、四字的边界对齐检查，否则不检查。未按边界对齐，发生异常17
 */
#define __EFLAG_INDEX_AC__   18
// 虚拟中断允许标志VIF
#define __EFLAG_INDEX_VIF__  19
// 虚拟中断挂起标志VIP
#define __EFLAG_INDEX_VIP__  20
// CPU标识标志ID。为1时，允许使用CPUID指令
#define __EFLAG_INDEX_ID__   21
// 用于设置EFLAGS寄存器中保留且恒为1的位
#define __EFLAG_OR_MASK__	0x2

// 普通32寄存器索引
#define __GR32_EAX__	    0
#define __GR32_ECX__	    1
#define __GR32_EDX__	    2
#define __GR32_EBX__	    3
#define __GR32_ESP__	    4
#define __GR32_EBP__	    5
#define __GR32_ESI__		6
#define __GR32_EDI__	    7

// 段寄存器索引
#define __SR_ES__		    0
#define __SR_CS__		    1
#define __SR_SS__		    2
#define __SR_DS__		    3
#define __SR_FS__		    4
#define __SR_GS__		    5

#endif

