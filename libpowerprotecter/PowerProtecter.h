/*
 * 加密一个函数,在这个函数运行时开辟一片新的内存解密运行,函数返回时销毁这片内存
 * 函数的解密依靠另外一个未解密的函数P,P通过哈希运算得到一个KEY,这个KEY用于解密
 * 当前被保护的函数
 * 被保护函数的指令也受到加密保护,这里指令有两重保护,一重保护是将指令提取出来,存
 * 入记录结构,在原指令位置放置可以触发异常的指令,指令的加解密只通过一个简单的KEY做XOR
 * 运算。二是指令解密通过另外一片未被加密的内存区域,这片区域通过哈希运算得到一个KEY,
 * 这个KEY来解密当前指令
 */
#if !defined(__POWER_PROTECTER_H__)
#define __POWER_PROTECTER_H__

#include "Common.h"
#include "Support.h"

#if defined(__cplusplus)
extern "C"
{
#endif

// 力量加密函数的对齐粒度
#define __POWER_PROTECT_ENCRYPT_PROCEDURE_ALIGN__					sizeof(__integer)

// 力量保护的配置结构
typedef struct _POWER_PROTECTER_CONFIGURE {
	__integer iTmp;
} POWER_PROTECTER_CONFIGURE, *PPOWER_PROTECTER_CONFIGURE;

// 力量保护的信息结构
typedef struct _POWER_PROTECTER_INFO {
	__address addrOrigTargetImageBase;//原始的目标基地址
	__address addrNowTargetImageBase;//当前的目标基地址
	__address addrPowerProtecterOrigImageBase;//力量保护器的原始基地址
	__address addrPowerProtecterNowImageBase;//力量保护器的当前基地址
} POWER_PROTECTER_INFO, *PPOWER_PROTECTER_INFO;

/*
 * 此结构用来描述被保护函数或者指令或者监视内存的内存地址,文件地址,已经长度
 */
typedef struct _POWER_PROTECTER_PROCEDURE_RECORD {
	union {
		__address addrMemAddress;//内存地址
		__offset ofMemRVA;//内存偏移
	};
	__memory pFileAddress;//文件地址
	__integer iSize;//函数长度
} POWER_PROTECTER_PROCEDURE_RECORD, POWER_PROTECTER_WATCH_RECORD, POWER_PROTECTER_INSTRUCTION_RECORD, \
  *PPOWER_PROTECTER_PROCEDURE_RECORD, *PPOWER_PROTECTER_WATCH_RECORD, *PPOWER_PROTECTER_INSTRUCTION_RECORD;

// 要保护的指令
#define __POWER_PROTECT_IS_NOT_A_FLOW_INSTRUCTION__			0x80
typedef enum _POWER_PROTECTER_FLOW_TYPE {
	PPFT_NONE = __POWER_PROTECT_IS_NOT_A_FLOW_INSTRUCTION__,
	PPFT_JO = 1,
	PPFT_JNO = 2,
	PPFT_JB = 3,
	PPFT_JAE = 4,
	PPFT_JZ = 5,
	PPFT_JNZ = 6,
	PPFT_JBE = 7,
	PPFT_JA = 8,
	PPFT_JS = 9,
	PPFT_JNS = 10,
	PPFT_JP = 11,
	PPFT_JNP = 12,
	PPFT_JL = 13,
	PPFT_JGE = 14,
	PPFT_JLE = 15,
	PPFT_JG = 16,
	PPFT_JCXZ = 17,
	PPFT_JECXZ = 18,
	PPFT_JRCXZ = 19,
	PPFT_LOOPNE = 20,
	PPFT_LOOPE = 21,
	PPFT_LOOP = 22,
	PPFT_JMP = 23,
	PPFT_CALL = 24,
	PPFT_RET = 25
} POWER_PROTECTER_FLOW_TYPE;

/*
 * 此结构保存在目标程序体内,用来记录被保护指令的信息
 */
#define __POWER_PROTECTER_MAX_INSTRUCTION_BUFFER_SIZE__				0x20
typedef struct _POWER_PROTECTER_ENCRYPT_INSTRUCTION {
	__bool bOut;//是否向外进行跳转

	union {
		__address addMemAddress;//内存地址
		__offset ofMemRVA;//内存偏移
	};

	__byte InstBuf[__POWER_PROTECTER_MAX_INSTRUCTION_BUFFER_SIZE__];//指令 <- 使用展开后的
	POWER_PROTECTER_FLOW_TYPE JmpType;//是什么类型的跳转 <- 如果是0x80 则为非跳转
	__bool bIsWatched;//此条指令监视其他内存地址
	POWER_PROTECTER_WATCH_RECORD WatchRecord;//要监视的内存 <- 使用InstBuf的密文加密
	__dword dwKey;//如果要无要监视的内存,则使用指定的密钥进行加密

	/*
	 * 目标地址与RVA只在此条指令是流程指令才启用
	 */
	union {
		__address addrTargetMemAddress;//目标内存地址
		__offset ofTargetMemRVA;//目标内存的RVA
	};
	__integer iInstLen;//指令长度
	__integer iRetSize;//需要返回的参数长度
} POWER_PROTECTER_ENCRYPT_INSTRUCTION, *PPOWER_PROTECTER_ENCRYPT_INSTRUCTION;

// 加密函数必要信息结构
typedef struct _POWER_PROTECTER_DECRYPT_PROCEDURE {
	POWER_PROTECTER_PROCEDURE_RECORD KeyProcedure;//这里记录了解密这个函数对应的函数,这个结构使用加密后函数作为密钥进行解密
	//union {
	//	__address addrProcAddress;//函数原本的地址
	//	__offset ofProcRVA;//函数原本的RVA
	//};
} POWER_PROTECTER_DECRYPT_PROCEDURE, *PPOWER_PROTECTER_DECRYPT_PROCEDURE;

// 寄存器定义
typedef struct _POWER_PROTECTER_RUN_CONTEXT {
	__dword dwEFlag;//标志寄存器
	__dword EDI;
	__dword ESI;
	__dword EBP;
	__dword ESP;
	__dword EBX;
	__dword EDX;
	__dword ECX;
	__dword EAX;
} POWER_PROTECTER_RUN_CONTEXT, *PPOWER_PROTECTER_RUN_CONTEXT;

/*
 * 此结构放置在被保护程序目标体内,用来记录加密后函数的信息
 */
typedef struct _POWER_PROTECTER_ENCRYPT_PROCEDURE {
	POWER_PROTECTER_PROCEDURE_RECORD KeyProcedure;//这里记录了解密这个函数对应的函数,这个结构使用加密后函数作为密钥进行解密
	union {
		__address addrProcAddress;//函数原本的地址
		__offset ofProcRVA;//函数的RVA
	};
	__integer iTotalSize;//此结构 + 不定长度 对齐后的长度
	__integer iProcSize;//被保护函数的长度,后面的长度
	__integer iEncryptInstCount;//加密指令计数
	__bool bInit;//是否已经初始化
	CRITICAL_SECTION LocalCriticalSection;//当前线程的同步对象
	__integer iHandleCount;//句柄计数,当为0时就可以销毁掉开辟的内存了
	__memory pRunSpace;//运行空间
	PPOWER_PROTECTER_DECRYPT_PROCEDURE pDecryptProcedure;//解密结构
	//POWER_PROTECTER_RUN_CONTEXT Context;//记录函数开始时的上下文
	// 这里跟随加密后的函数
	// 这里跟随iEncryptInstCount个POWER_PROTECTER_ENCRYPT_INSTRUCTION结构 <- 使用函数的明文进行加密
} POWER_PROTECTER_ENCRYPT_PROCEDURE, *PPOWER_PROTECTER_ENCRYPT_PROCEDURE;

//#define __MAX_POWER_PROTECT_PROCEDURE_ARGC__				0x20
//#define __MAX_POWER_PROTECTER_STACK_SIZE__					0x2000//8KB
//#define __POWER_PROTECTER_ESP_POINT__						0x1000//4KB
//typedef struct _POWER_PROTECTER_PROCEDURE_RUN_FRAME {
//	__dword dwRetAddress;//返回地址
//	__dword dwArgs[__MAX_POWER_PROTECT_PROCEDURE_ARGC__];//参数个数
//} POWER_PROTECTER_PROCEDURE_RUN_FRAME, *PPOWER_PROTECTER_PROCEDURE_RUN_FRAME;

//#define __POWER_PROTECTER_DATA_SIGN_1__						0xFB11CA42
//#define __POWER_PROTECTER_DATA_SIGN_2__						0xED45AB33
//typedef struct _POWER_PROTECTER_PROCEDURE_DATA {
//	__dword dwSign[2];//标致
//	__dword dwOrigEsp;//原ESP的值
//	__dword dwNewStackAddress;//新堆栈的首地址,用于释放这个结构
//	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pCurrEncryptProcedure;//指向一个解密函数结构
//	__dword dwStartEsp;//新堆栈切栈后ESP的地址,此值最重要的目的是计算目标函数的参数个数,与ret指令和调用方式有关系
//} POWER_PROTECTER_PROCEDURE_DATA, *PPOWER_PROTECTER_PROCEDURE_DATA;
//
//typedef struct _POWER_PROTECTER_RUNTIME {					// <- 新堆栈起点
//	POWER_PROTECTER_PROCEDURE_RUN_FRAME RunFrame;//运行堆栈
//	POWER_PROTECTER_PROCEDURE_DATA Data;//必要的数据
//} POWER_PROTECTER_RUNTIME, *PPOWER_PROTECTER_RUNTIME;

// 初始化力量保护,在最初调用
__void __API__ PowerProtecterInit(PPOWER_PROTECTER_CONFIGURE pConfigure, PPOWER_PROTECTER_INFO pInfo);

#if defined(__cplusplus)
}
#endif

#endif
