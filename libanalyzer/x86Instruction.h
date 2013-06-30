// 跳转指令结构
typedef enum _JMPBIT {
	JMP_NONE = 0x00,
	JMP_BIT8 = 0x08,
	JMP_BIT16 = 0x10,
	JMP_BIT32 = 0x20
} JMPBIT;

typedef enum _MOVTYPE {
	MOV_NONE = 0,
	MOV_REG_IMM,
	MOV_REG_MEM,
	LEA_REG_MEM
} MOVTYPE, *PMOVTYPE;

typedef enum _JMPTYPE {
	JMP_TYPE_NOT_FIX = 0,
	JMP_TYPE_JMP_OFFSET,
	JMP_TYPE_CALL_OFFSET,
	JMP_TYPE_JCC_OFFSET,
	JMP_TYPE_JMP_IMEM,
	JMP_TYPE_JMP_MOV_ADDR_REG,
	JMP_TYPE_JMP_MOV_ADDR_MREG,
	JMP_TYPE_JMP_MOV_MEM_REG,
	JMP_TYPE_JMP_MOV_MEM_MREG,
	JMP_TYPE_CALL_IMEM,
	JMP_TYPE_CALL_MOV_ADDR_REG,
	JMP_TYPE_CALL_MOV_ADDR_MREG,
	JMP_TYPE_CALL_MOV_MEM_REG,
	JMP_TYPE_CALL_MOV_MEM_MREG
} JMPTYPE;

typedef enum _JMPWAY {
	JMP_WAY_UNKNOW = 0,
	JMP_WAY_UP,
	JMP_WAY_DOWN
} JMPWAY;

typedef struct _INSTRUCTION_JMP {
	struct _INSTRUCTION_JMP *pNext;//下一个节点

	__bool bTargetAddressIsInvalid;//跳转目标地址是否无效
	__bool bJmpOut;//是否跳出到另外的函数中
	__bool bIndirectJmp;//是否是间接跳转

	JMPWAY JmpWay;//跳转方向
	JMPBIT JmpBit;//跳转的位数
	JMPTYPE JmpType;//跳转的类型

	union {
		__address addrTargetMemoryAddress;//跳转后的内存地址
		__address addrIndirectMemoryAddress;//间接的内存地址
	};

	union {
		__memory pTargetFileAddress;//跳转后的文件地址
		__memory pIndirectFileAddress;//间接的内存地址
	};

	union {
		__byte bVal;
		__word wVal;
		__dword dwVal;
	} Offset;//偏移

	__void *pParents;//父节点,指向X86INSTRUCTION结构
} INSTRUCTION_JMP, *PINSTRUCTION_JMP;

// 引用的数据
typedef struct _REFERENCE_DATA {
	__bool bSet;//是设置操作,否则为获取操作
	__bool bMaybeCrash;//可能不是地址,引起程序崩溃

	__address addrMemoryAddress;//数据的内存地址
	__memory pFileAddress;//数据的文件地址

	PIMPORT_TABLE_REFERENCE pImportTableReference;//引入表引用
} REFERENCE_DATA, *PREFERENCE_DATA;

// 指令结构
typedef enum _HOOK_SUCCESS_LEVEL {
	HOOK_LEVEL_NOT = 0,
	HOOK_LEVEL_MAYBE,
	HOOK_LEVEL_OK
} HOOK_SUCCESS_LEVEL;

// 指令结构
typedef struct _X86INSTRUCTION {
	struct _X86INSTRUCTION *pPrev;//上一个节点
	struct _X86INSTRUCTION *pNext;//下一个节点


	/* 这里用作指令信息 */
	__bool bInvalid;//是无效的指令
	__bool bJmp;//是否是跳转
	__bool bReferenceData;//是否引用变量
	__bool bExchange;//是否可以进行交换,大于等于5字节并非跳转指令的指令

	HOOK_SUCCESS_LEVEL HookSuccessLevel;//HOOK成功的级别
	__memory pHookSaveAddress;//保存HOOK地址的文件地址

	REFERENCE_DATA ReferenceData;//引用的数据
	INSTRUCTION_JMP InstructionJmp;//跳转指令
	ud_t ud_obj;//反汇编结构
	__address addrCurrMemoryAddress;//当前指令内存地址
	__memory pCurrFileAddress;//当前指令文件地址
	__offset ofOffsetByProcedureStart;//离函数头的偏移
	__offset ofOffsetByImageBase;//离基址的偏移

	__bool EffectRegister[8];//受影响的寄存器
	__bool EffectEFlag[32];//受影响的标志寄存器
	__bool ConditionEFlag[32];//条件标志寄存器

	__void *pParents;//父节点,指向PROCEDURE结构


	/* 这里用作错误逻辑指令分析 */
	__bool bErrorLogicInstruction;//错误逻辑的指令
	__memory pMem;//pMem的指针
	__address addrMemoryBlockStart;//所属区域开始的指针
	__integer iBlockSize;//所属区域的长度

} X86INSTRUCTION, *PX86INSTRUCTION;
#define __ThisInstIsJmp__(pInstruction)			((pInstruction)->bJmp)
#define __ThisInstNotHook__(pInstruction)		((pInstruction)->HookSuccessLevel == HOOK_LEVEL_NOT)
#define __ThisInstMayHook__(pInstruction)		((pInstruction)->HookSuccessLevel == HOOK_LEVEL_MAYBE)
#define __ThisInstCanHook__(pInstruction)		((pInstruction)->HookSuccessLevel == HOOK_LEVEL_OK)
#define __ThisInstCanExchange__(pInstruction)	((pInstruction)->bExchange)

#define __GetInstructionJmpFromHeader__(pInstructionJmpFrom)			((PX86INSTRUCTION)((pInstructionJmpFrom)->pInstruction))

