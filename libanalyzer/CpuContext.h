// 标志寄存器
typedef enum _EFLAG_FLAG_INDEX {
	X86EFLAG_CF = 0,
	X86EFLAG_PF = 2,
	X86EFLAG_AF = 4,
	X86EFLAG_ZF = 6,
	X86EFLAG_SF = 7,
	X86EFLAG_TF = 8,
	X86EFLAG_IF = 9,
	X86EFLAG_DF = 10,
	X86EFLAG_OF = 11,
	X86EFLAG_IOPL = 12,
	X86EFLAG_IOPL_HIGH = 13,
	X86EFLAG_NT = 14,
	X86EFLAG_RF = 16,
	X86EFLAG_VM = 17,
	X86EFLAG_AC = 18,
	X86EFLAG_VIF = 19,
	X86EFLAG_VIP = 20,
	X86EFLAG_ID = 21
} EFLAG_FLAG_INDEX;

typedef struct _EFLAG_FLAG {
	__dword CF:1;//0
	__dword :1;//1
	__dword PF:1;//2
	__dword :1;//3
	__dword AF:1;//4
	__dword :1;//5
	__dword ZF:1;//6
	__dword SF:1;//7
	__dword TF:1;//8
	__dword IF:1;//9
	__dword DF:1;//10
	__dword OF:1;//11
	__dword IOPL:2;//12,13
	__dword NT:1;//14
	__dword :1;//15
	__dword RF:1;//16
	__dword VM:1;//17
	__dword AC:1;//18
	__dword VIF:1;//19
	__dword VIP:1;//20
	__dword ID:1;//21
	__dword :1;//22
	__dword :1;//23
	__dword :1;//24
	__dword :1;//25
	__dword :1;//26
	__dword :1;//27
	__dword :1;//28
	__dword :1;//29
	__dword :1;//30
	__dword :1;//31
} EFLAG_FLAG, *PEFLAG_FLAG;

// 通用寄存器标识
typedef enum _X86REGISTER_INDEX {
	X86REG_EAX = 0,
	X86REG_ECX,
	X86REG_EDX,
	X86REG_EBX,
	X86REG_ESP,
	X86REG_EBP,
	X86REG_ESI,
	X86REG_EDI
} X86REGISTER_INDEX;

// 通用寄存器结构
typedef struct _X86REGISTER {
	union {
		struct {
			struct {
				__byte Low8;
				__byte High8;
			} Low16;
			__word High16;
		} Detail;
		__dword dwValue;
	};
} X86REGISTER, *PX86REGISTER;

// CPU上下文结构
typedef struct _CPU_CONTEXT {
	X86REGISTER Register;//寄存器的值
	EFLAG_FLAG EFlag;//标志寄存器
} CPU_CONTEXT, *PCPU_CONTEXT;