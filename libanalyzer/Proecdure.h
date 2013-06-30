// 引用函数链
typedef struct _PROCEDURE_REFFROM {
	struct _PROCEDURE_REFFROM *pNext;//下一个节点
	__void *pProcedure;//函数节点,PROCEDURE结构
} PROCEDURE_REFFROM, *PPROCEDURE_REFFROM;

typedef enum _ALLOC_STACK_TYPE {
	ALLOC_BY_NOT = 0,
	ALLOC_BY_ENTER,
	ALLOC_BY_SUB_ESP
} ALLOC_STACK_TYPE, *PALLOC_STACK_TYPE;
#define __INVALID_ALLOC_STACK_SIZE__			0xFFFFFFFF

// 函数结构
typedef struct _PROCEDURE {
	struct _PROCEDURE *pNext;//下一个函数

	__bool bBlock;//只是一个块
	__bool bEntry;//入口点函数
	__bool bInline;//是内联函数

	struct _PROCEDURE *pFatherProcedure;//如果是内联函数则它的父函数

	__integer iSize;//长度
	__integer iInstCount;//指令的数量
	__integer iInvalidOpcodeCount;//无效指令计数

	__address addrAllocStackMemoryAddress;//分配栈大小的内存地址
	__memory pAllocStackFileAddress;//分配栈大小的文件地址
	ALLOC_STACK_TYPE AllocStackType;//分配栈指令类型
	__integer iStackSize;//栈大小

	__address addrMemoryStartAddress;//函数在内存中起始的地址
	__memory pFileStartAddress;//函数在文件中起始的地址

	PPROCEDURE_REFFROM pProcedureRefForm;//哪个函数引用了这个函数,这个需要释放空间
	PINSTRUCTION_JMP pInstructionJmp;//跳转指令链
	PX86INSTRUCTION pInstruction;//指令链,这个需要释放空间
	__void *pParents;//父节点,指向PROGRAM结构
} PROCEDURE, *PPROCEDURE;
#define __GetProcedureRefFromHeader__(pProcedureRefFrom)	((PPROCEDURE)((pProcedureRefFrom)->pProcedure))

#define __MAX_PROCEDURE_LENGTH__		4096
