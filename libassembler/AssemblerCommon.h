#if !defined(__ASSEMBLER_COMMON_H__)
#define __ASSEMBLER_COMMON_H__

#include "Common.h"
#include "y.tab.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define ASMER_TYPE YYSTYPE

//// 操作数格式
//typedef enum _OPT_FORM
//{
//	OF_NONE = 0,
//
//	/* op */ 
//	OF_OP, 
//	
//	/* op imm */
//	OF_I8,
//	OF_I16, 
//	OF_I32,
//
//	/* op mem */
//	OF_M8,
//	OF_M16, 
//	OF_M32,
//
//	/* op reg */
//	OF_R8,
//	OF_R16, 
//	OF_R32,
//
//	/* op reg, imm */
//	OF_R8_I8,
//	OF_R16_I8, 
//	OF_R16_I16,
//	OF_R32_I8,
//	OF_R32_I16, 
//	OF_R32_I32,
//	
//	/* op reg, mem */
//	OF_R8_M8,
//	OF_R16_M8,
//	OF_R16_M16,
//	OF_R32_M8,
//	OF_R32_M16,
//	OF_R32_M32,
//	OF_R32_M64,/* 应该是错误的 */
//	OF_R64_M64,
//	OF_R64_M128,
//	OF_R128_M64,
//	OF_R128_M128,
//
//	/* op reg, reg */
//	OF_R8_R8,
//	OF_R16_R8,
//	OF_R16_R16,
//	OF_R32_R8,
//	OF_R32_R16, 
//	OF_R32_R32,
//	OF_R64_R64,
//	OF_R128_R128,
//
//	/* op mem, imm */
//	OF_M8_I8,
//	OF_M16_I8, 
//	OF_M16_I16,
//	OF_M32_I8,
//	OF_M32_I16, 
//	OF_M32_I32,
//
//	/* op mem, reg */
//	OF_M8_R8,
//	OF_M8_R16,
//	OF_M16_R16,
//	OF_M32_R16,
//	OF_M32_R32,
//
//	/* op imm:imm */
//	OF_I16_I8,
//	OF_I16_I16,
//	OF_I16_I32,
//
//	/* opt reg, mem, imm */
//	OF_R8_M8_I8,
//	OF_R16_M16_I8,
//	OF_R16_M16_I16, 
//	OF_R32_M32_I8,
//	OF_R32_M32_I16, 
//	OF_R32_M32_I32,
//	OF_R128_M128_8,
//
//	/* opt reg, reg, imm */
//	OF_R8_R8_I8,
//	OF_R16_R16_I8,
//	OF_R16_R16_I16, 
//	OF_R32_R32_I8,
//	OF_R32_R32_I16,
//	OF_R32_R32_I32,
//	OF_R128_R128_8
//} OPT_FORM;
	
typedef enum _ASMER_BIT {
	ASMER_0_BITS = 0,
	ASMER_8_BITS = 8,
	ASMER_16_BITS = 16,
	ASMER_32_BITS = 32,
	ASMER_64_BITS = 64,
	ASMER_80_BITS = 80,
	ASMER_128_BITS = 128
} ASMER_BIT;

#define __MAX_SYMBOL_SIZE__	128
typedef struct _ASM_SOURCE {
	__char *pText;//汇编源代码
	__integer iTokenListMaxCount;//标记的最大个数
	__integer iImmediateMaxSize;//立即数内存最大个数
	__integer iSymbolNameLength;//符号名最大长度
	__integer iSymbolMaxCount;//符号表符号的个数
} ASM_SOURCE, *PASM_SOURCE;

typedef struct _MODRM_TYPE {
	__byte RM:3;
	__byte RO:3;
	__byte Mod:2;
} MODRM_TYPE;

typedef struct _SIB_TYPE {
	__byte Base:3;
	__byte Index:3;
	__byte SS:2;
} SIB_TYPE;

typedef enum _ASMER_SYMBOL_TYPE {
	AST_ADDR_NONE = 0,
	AST_ADDR_LAB
} ASMER_SYMBOL_TYPE;

// 标记转符号类型
#define __AsmerTokenToSymbolType__(AsmerToken, AsmerSymbolType)\
	switch ((AsmerToken){\
	case ADDR_LAB:(AsmerSymbolType) = AST_ADDR_LAB;break;\
	default: (AsmerSymbolType) = AST_ADDR_NONE;}

// OBJ中的符号表
typedef struct _ASMER_SYMBOL_NODE {
	ASMER_SYMBOL_TYPE Type;//类型
	__offset ofOffset;//到代码块开始的偏移
} ASMER_SYMBOL_NODE, *PASMER_SYMBOL_NODE;

#define __CreateSymbolNode__(SymbolNode, SymbolType, OffsetFromStart)\
	(SymbolNode) = (PASMER_SYMBOL_NODE)__logic_new__(ASMER_SYMBOL_NODE, 1);\
	__logic_memset__((SymbolNode), 0, sizeof(ASMER_SYMBOL_NODE));\
	(SymbolNode)->Type = (SymbolType);(SymbolNode)->ofOffset = OffsetFromStart;

#define __DestorySymbolNode__(SymbolNode)			__logic_delete__((SymbolNode));(SymbolNode) = NULL;

// 汇编操作符
typedef struct _ASMER_OPERAND {
	__bool bAddrLabel;//这个节点使用了地址标号
	__bool bIsImmediate;//操作数是立即数
	__bool bIsRegister;//操作数是寄存器
	__bool bIsMem;//操作数是内存
	ASMER_TYPE Type;//寄存器, 内存, 立即数
	ASMER_BIT Bit;//当前操作的位数
	ASMER_TYPE Base;//基
	ASMER_TYPE Index;//索引
	__byte Scale;//刻度	
	ASMER_BIT ValBit;//值所占的位
	union {
		__char sByte;
		__byte uByte;
		__sword sWord;
		__word uWord;
		__sdword sDword;
		__dword uDword;
	} Val;//值
	
	__offset ofRelocationFixOffset;//重定位修订偏移
	//__char *pAddrLabelSymbolName;//地址标号名称指针
	//PASMER_SYMBOL_NODE pSymbolNode;//符号节点,操作数不需要所以删除此项
} ASMER_OPERAND, *PASMER_OPERAND;

// 指令类型
typedef enum _INST_CLASS {
	IC_NONE = 0,
	IC_X86,
	IC_FPU,
	IC_SIMD,
	IC_VMX
} INST_CLASS;

// 汇编OBJ结构
typedef struct _ASM_OBJ {
	struct _ASM_OBJ *pNext;//下一个节点
	__bool bAddrLabel;//这是一个标号节点
	INST_CLASS InstClass;//指令类型
	ASMER_TYPE Inst;//指令
	__byte bOpcodes[4];//操作码队列
	__byte bOpcodesCount;//操作码计数
	ASMER_OPERAND Operand[3];//操作对象
	__byte bOperandCount;//操作数数量
	__bool bUseOpEx;//使用OP扩展
	__byte bOpEx;//操作码扩展
	__offset ofOffset;//偏移
	__byte bInstLength;//当前指令的长度
	__bool bUsePrefix;//使用了前缀
	__byte bPrefixCount;//前缀计数
	__byte bPrefix[4];//前缀
	__bool bUseModRM;//使用了ModRM
	__bool bUseSIB;//是否有SIB位
	__bool bUseDisplacement;//这条指令拥有偏移
	__byte bDisplacementOwn;//偏移所属哪个操作对象
	MODRM_TYPE ModRM;
	SIB_TYPE SIB;
	__char *pAddrLabelSymbolName;//地址标号的名字指针
	PASMER_SYMBOL_NODE pSymbolNode;//符号节点
} ASM_OBJ, *PASM_OBJ;

// 获取寄存器索引
__integer __INTERNAL_FUNC__ GetRegisterIndex(ASMER_TYPE Reg);
__void __INTERNAL_FUNC__ SetOperand(PASMER_OPERAND pOperand, __bool bAddressLabel, ASMER_TYPE OptType, ASMER_BIT OptBit, ASMER_TYPE RegBase, \
									ASMER_TYPE RegIndex, __byte MemScale, ASMER_BIT ValueBit, __dword OptValue, __char *pAddressLabelSymbolName, \
									__offset RelocationFixOffset, PASMER_SYMBOL_NODE pCurrSymbolNode);
__void __INTERNAL_FUNC__ SetOperandWithoutVal(PASMER_OPERAND pOperand, ASMER_TYPE OptType, ASMER_BIT OptBit, ASMER_TYPE RegBase, ASMER_TYPE RegIndex);
__void __INTERNAL_FUNC__ SetAsmObj(PASM_OBJ pAsmObj, INST_CLASS InstructionClass, ASMER_TYPE Instruction, __void *pOpcodes, __byte bNumberOfOpcodes, __byte bOpcodeEx);

#if defined(_DEBUG)
#define __PRINT_DBG_INFO__
#endif

__void __INTERNAL_FUNC__ AssemblerPrintAsmObj(PASM_OBJ pAsmObj);

#if defined(__cplusplus)
}
#endif

#endif
