/*
 * 壳使用的小型x86汇编器
 */
#if !defined(__ASSEMBLER_H__)
#define __ASSEMBLER_H__

// 使用的位
typedef enum _ASMER_BIT
{
	ASMER_0_BITS = 0,
	ASMER_8_BITS = 8,
	ASMER_16_BITS = 16,
	ASMER_32_BITS = 32
} ASMER_BIT;

// 可以进行汇编的指令
typedef enum _ASMER_INST
{
	ASMER_NOP, 
	ASMER_ADD, 
	ASMER_SUB, 
	ASMER_MUL, 
	ASMER_IMUL, 
	ASMER_DIV, 
	ASMER_IDIV, 
	ASMER_NOT, 
	ASMER_AND, 
	ASMER_OR, 
	ASMER_XOR, 
	ASMER_SHL,
	ASMER_SHR, 
	ASMER_ROL, 
	ASMER_ROR, 
	ASMER_MOV, 
	ASMER_LEA, 
	ASMER_STOSB, 
	ASMER_STOSW, 
	ASMER_STOSD,
	ASMER_LODSB, 
	ASMER_LODSW, 
	ASMER_LODSD, 
	ASMER_MOVSB, 
	ASMER_MOVSW, 
	ASMER_MOVSD,
	ASMER_CLD,
	ASMER_STD,
	ASMER_PUSH,
	ASMER_POP, 
	ASMER_PUSHAD, 
	ASMER_POPAD, 
	ASMER_PUSHFD, 
	ASMER_POPFD, 
	ASMER_RET, 
	ASMER_RETN, 
	ASMER_JMP, 
	ASMER_CALL,
	ASMER_LOOP, 
	ASMER_JZ, 
	ASMER_JNZ, 
	ASMER_JA, 
	ASMER_JB, 
	ASMER_JAE, 
	ASMER_JBE, 
	ASMER_CMP, 
	ASMER_TEST,

	/* 以下是伪指令 */
	ASMER_PSEUDO_ADDR_LAB,
	ASMER_PSEUDO_ADDR_VALUE_LAB
} ASMER_INST;

// 汇编器类型
typedef enum _ASMER_TYPE
{
	ASMER_NONE = 0,

	/* 8Bits 寄存器 */
	ASMER_REG_AL, ASMER_REG_AH, ASMER_REG_CL, ASMER_REG_CH,
	ASMER_REG_DL, ASMER_REG_DH, ASMER_REG_BL, ASMER_REG_BH,

	/* 16Bits 寄存器 */
	ASMER_REG_AX, ASMER_REG_CX, ASMER_REG_DX, ASMER_REG_BX,
	ASMER_REG_SP, ASMER_REG_BP, ASMER_REG_SI, ASMER_REG_DI,

	/* 32Bits 寄存器 */
	ASMER_REG_EAX, ASMER_REG_ECX, ASMER_REG_EDX, ASMER_REG_EBX,
	ASMER_REG_ESP, ASMER_REG_EBP, ASMER_REG_ESI, ASMER_REG_EDI,

	/* 操作符类型 */
	ASMER_OP_REG, ASMER_OP_MEM, ASMER_OP_IMM
} ASMER_TYPE;

// 获取寄存器索引
#define __GetRegisterIndex__(Index, Reg)\
	switch ((Reg)){\
	case ASMER_REG_AL:\
	case ASMER_REG_AX:\
	case ASMER_REG_EAX: (Index) = 0; break;\
	case ASMER_REG_CL:\
	case ASMER_REG_CX:\
	case ASMER_REG_ECX: (Index) = 1; break;\
	case ASMER_REG_DL:\
	case ASMER_REG_DX:\
	case ASMER_REG_EDX: (Index) = 2; break;\
	case ASMER_REG_BL:\
	case ASMER_REG_BX:\
	case ASMER_REG_EBX: (Index) = 3; break;\
	case ASMER_REG_AH:\
	case ASMER_REG_SP:\
	case ASMER_REG_ESP: (Index) = 4; break;\
	case ASMER_REG_CH:\
	case ASMER_REG_BP:\
	case ASMER_REG_EBP: (Index) = 5; break;\
	case ASMER_REG_DH:\
	case ASMER_REG_SI:\
	case ASMER_REG_ESI: (Index) = 6; break;\
	case ASMER_REG_BH:\
	case ASMER_REG_DI:\
	case ASMER_REG_EDI: (Index) = 7; break;\
	default: (Index) = 0;}

// 汇编标记
typedef enum _ASM_TOKEN
{
	ASMER_TK_ERROR,

	/* 指令 */
	ASMER_TK_INST_NOP, 
	ASMER_TK_INST_ADD, 
	ASMER_TK_INST_SUB, 
	ASMER_TK_INST_MUL, 
	ASMER_TK_INST_IMUL, 
	ASMER_TK_INST_DIV, 
	ASMER_TK_INST_IDIV, 
	ASMER_TK_INST_NOT, 
	ASMER_TK_INST_AND, 
	ASMER_TK_INST_OR, 
	ASMER_TK_INST_XOR, 
	ASMER_TK_INST_SHL,
	ASMER_TK_INST_SHR, 
	ASMER_TK_INST_ROL, 
	ASMER_TK_INST_ROR, 
	ASMER_TK_INST_MOV, 
	ASMER_TK_INST_LEA, 
	ASMER_TK_INST_STOSB, 
	ASMER_TK_INST_STOSW, 
	ASMER_TK_INST_STOSD,
	ASMER_TK_INST_LODSB, 
	ASMER_TK_INST_LODSW, 
	ASMER_TK_INST_LODSD, 
	ASMER_TK_INST_MOVSB, 
	ASMER_TK_INST_MOVSW, 
	ASMER_TK_INST_MOVSD,
	ASMER_TK_INST_CLD,
	ASMER_TK_INST_STD,
	ASMER_TK_INST_PUSH,
	ASMER_TK_INST_POP, 
	ASMER_TK_INST_PUSHAD, 
	ASMER_TK_INST_POPAD, 
	ASMER_TK_INST_PUSHFD, 
	ASMER_TK_INST_POPFD, 
	ASMER_TK_INST_RET, 
	ASMER_TK_INST_RETN, 
	ASMER_TK_INST_JMP, 
	ASMER_TK_INST_CALL,
	ASMER_TK_INST_LOOP, 
	ASMER_TK_INST_JZ, 
	ASMER_TK_INST_JNZ, 
	ASMER_TK_INST_JA, 
	ASMER_TK_INST_JB, 
	ASMER_TK_INST_JAE, 
	ASMER_TK_INST_JBE, 
	ASMER_TK_INST_CMP, 
	ASMER_TK_INST_TEST,

	/* 寄存器 */
	/* 8Bits 寄存器 */
	ASMER_TK_REG_AL, ASMER_TK_REG_AH, ASMER_TK_REG_CL, ASMER_TK_REG_CH,
	ASMER_TK_REG_DL, ASMER_TK_REG_DH, ASMER_TK_REG_BL, ASMER_TK_REG_BH,

	/* 16Bits 寄存器 */
	ASMER_TK_REG_AX, ASMER_TK_REG_CX, ASMER_TK_REG_DX, ASMER_TK_REG_BX,
	ASMER_TK_REG_SP, ASMER_TK_REG_BP, ASMER_TK_REG_SI, ASMER_TK_REG_DI,

	/* 32Bits 寄存器 */
	ASMER_TK_REG_EAX, ASMER_TK_REG_ECX, ASMER_TK_REG_EDX, ASMER_TK_REG_EBX,
	ASMER_TK_REG_ESP, ASMER_TK_REG_EBP, ASMER_TK_REG_ESI, ASMER_TK_REG_EDI,

	/* 关键字 */
	ASMER_TK_KW_BYTE_PTR, ASMER_TK_KW_WORD_PTR, ASMER_TK_KW_DWORD_PTR,
	ASMER_TK_KW_SCALE_1, ASMER_TK_KW_SCALE_2, ASMER_TK_KW_SCALE_4, ASMER_TK_KW_SCALE_8, 
	ASMER_TK_KW_ADD, ASMER_TK_KW_SUB,/* 减号在编译的过程中换算为加号 */
	ASMER_TK_KW_ADDR_LAB, ASMER_TK_KW_ADDR_VALUE_LAB,
	ASMER_TK_KW_DISPLACEMENT8, ASMER_TK_KW_DISPLACEMENT32,
	ASMER_TK_KW_IMMEDIATE8, ASMER_TK_KW_IMMEDIATE16, ASMER_TK_KW_IMMEDIATE32,
	ASMER_TK_KW_MEMEND, ASMER_TK_KW_LINEND,

	/* 结束符 */
	ASMER_TK_END
} ASM_TOKEN, *PASM_TOKEN;

// 寄存器标记转换寄存器标志
#define __RegTokenToReg__(Reg, RegToken)\
	if ((RegToken) == ASMER_TK_REG_AL) (Reg) = ASMER_REG_AL;\
	else if ((RegToken) == ASMER_TK_REG_AH) (Reg) = ASMER_REG_AH;\
	else if ((RegToken) == ASMER_TK_REG_CL) (Reg) = ASMER_REG_CL;\
	else if ((RegToken) == ASMER_TK_REG_CH) (Reg) = ASMER_REG_CH;\
	else if ((RegToken) == ASMER_TK_REG_DL) (Reg) = ASMER_REG_DL;\
	else if ((RegToken) == ASMER_TK_REG_DH) (Reg) = ASMER_REG_DH;\
	else if ((RegToken) == ASMER_TK_REG_BL) (Reg) = ASMER_REG_BL;\
	else if ((RegToken) == ASMER_TK_REG_BH) (Reg) = ASMER_REG_BH;\
	else if ((RegToken) == ASMER_TK_REG_AX) (Reg) = ASMER_REG_AX;\
	else if ((RegToken) == ASMER_TK_REG_CX) (Reg) = ASMER_REG_CX;\
	else if ((RegToken) == ASMER_TK_REG_DX) (Reg) = ASMER_REG_DX;\
	else if ((RegToken) == ASMER_TK_REG_BX) (Reg) = ASMER_REG_BX;\
	else if ((RegToken) == ASMER_TK_REG_SP) (Reg) = ASMER_REG_SP;\
	else if ((RegToken) == ASMER_TK_REG_BP) (Reg) = ASMER_REG_BP;\
	else if ((RegToken) == ASMER_TK_REG_SI) (Reg) = ASMER_REG_SI;\
	else if ((RegToken) == ASMER_TK_REG_DI) (Reg) = ASMER_REG_DI;\
	else if ((RegToken) == ASMER_TK_REG_EAX) (Reg) = ASMER_REG_EAX;\
	else if ((RegToken) == ASMER_TK_REG_ECX) (Reg) = ASMER_REG_ECX;\
	else if ((RegToken) == ASMER_TK_REG_EDX) (Reg) = ASMER_REG_EDX;\
	else if ((RegToken) == ASMER_TK_REG_EBX) (Reg) = ASMER_REG_EBX;\
	else if ((RegToken) == ASMER_TK_REG_ESP) (Reg) = ASMER_REG_ESP;\
	else if ((RegToken) == ASMER_TK_REG_EBP) (Reg) = ASMER_REG_EBP;\
	else if ((RegToken) == ASMER_TK_REG_ESI) (Reg) = ASMER_REG_ESI;\
	else if ((RegToken) == ASMER_TK_REG_EDI) (Reg) = ASMER_REG_EDI;

// 汇编源代码结构
typedef struct _ASM_SOURCE
{
	PASM_TOKEN pAsmTokenList;//汇编语法标记
	DWORD dwTokenMaxCount;//标记缓冲最大计数
	DWORD *pConstList;//常数队列
	DWORD dwConstMaxCount;//常数队列最大计数
	CHAR **pSymbolList;//符号指针
	DWORD dwSymbolMaxCount;//符号表最大计数
} ASM_SOURCE, *PASM_SOURCE;

typedef struct _MODRM_TYPE
{
	BYTE RM:3;
	BYTE RO:3;
	BYTE Mod:2;
} MODRM_TYPE;

typedef struct _SIB_TYPE
{
	BYTE Base:3;
	BYTE Index:3;
	BYTE SS:2;
} SIB_TYPE;

typedef enum _ASMER_SCALE
{
	AS_NONE = 0,
	AS_1 = 1,
	AS_2 = 2,
	AS_4 = 3,
	AS_8 = 4,
} ASMER_SCALE;

#define __SetScale__(SetToScale, ScaleType)			if ((ScaleType) != AS_NONE) (SetToScale) = ((ScaleType) - 1)

// 符号类型
typedef enum _ASMER_SYMBOL_TYPE
{
	AST_ADDR_NONE = 0,
	AST_ADDR_LAB,
	AST_ADDR_VALUE_LAB
} ASMER_SYMBOL_TYPE;

// 标记转符号类型
#define __AsmerTokenToSymbolType__(AsmerToken, AsmerSymbolType)\
	switch ((AsmerToken){\
	case ASMER_TK_KW_ADDR_LAB:(AsmerSymbolType) = AST_ADDR_LAB;break;\
	case ASMER_TK_KW_ADDR_VALUE_LAB:(AsmerSymbolType) = AST_ADDR_VALUE_LAB;break;\
	default: (AsmerSymbolType) = AST_ADDR_NONE;}

// OBJ中的符号表
typedef struct _ASMER_SYMBOL_NODE
{
	ASMER_SYMBOL_TYPE Type;//类型
	DWORD dwOffset;//到代码块开始的偏移
} ASMER_SYMBOL_NODE, *PASMER_SYMBOL_NODE;

#define __CreateSymbolNode__(SymbolNode, SymbolType, OffsetFromStart)\
	(SymbolNode) = __new__(ASMER_SYMBOL_NODE, 1);memset((SymbolNode), 0, sizeof(ASMER_SYMBOL_NODE));\
	(SymbolNode)->Type = (SymbolType);(SymbolNode)->dwOffset = OffsetFromStart;

#define __DestorySymbolNode__(SymbolNode)			__delete__((SymbolNode));(SymbolNode) = NULL;

// 汇编操作符
typedef struct _ASMER_OPERAND
{
	ASMER_TYPE Type;//类型
	ASMER_BIT Bit;//当前操作的位数
	ASMER_TYPE Base;//基
	ASMER_TYPE Index;//索引
	ASMER_BIT OffsetBit;//偏移所占用的位
	ASMER_SCALE Scale;//刻度
	union 
	{
		CHAR sByte;
		BYTE uByte;
		SHORT sWord;
		WORD uWord;
		LONG sDword;
		DWORD uDword;
	} Val;//值


	// 以下结构用于编译时内部使用 
	struct 
	{
		PASMER_SYMBOL_NODE pSymbolNode;//符号节点
		DWORD dwRelocationPoint;//重定位的位置
	} CompilingInternal;
} ASMER_OPERAND, *PASMER_OPERAND;

// 汇编OBJ结构
typedef struct _ASM_OBJ
{
	struct _ASM_OBJ *pNext;//下一个节点

	ASMER_INST Inst;//指令
	BYTE bOperandCount;//操作数数量
	ASMER_OPERAND Operand[3];//操作对象
	DWORD dwOffset;//偏移
	BYTE bInstLength;//当前指令的长度

	// 以下结构用于编译时内部使用
	struct
	{
		BOOL bRefAddrLabel;//此条指令引用了标号
		BOOL bUseModRM;//使用了ModRM
		MODRM_TYPE ModRM;
		BOOL bHasSIB;//是否有SIB位
		SIB_TYPE SIB;
		PASMER_SYMBOL_NODE pSymbolNode;//当前的OBJ节点是符号节点,不为空则表示这是一个标号节点
	} CompilingInternal;
} ASM_OBJ, *PASM_OBJ;

#endif
