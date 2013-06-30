#if !defined(__CHAOSVM_H__)
#define __CHAOSVM_H__

#include "Common.h"
#include "logic.h"
#include "ChaosVmp.h"
#include "ChaosVmCpu.h"
#include "Support.h"
#include "ChaosVmByteCodeFile.h"
#include "PowerProtecter.h"

#if defined(__cplusplus)
extern "C"
{
#endif

//#define __CHAOSVM_INTERNAL_DEBUG__						0x01
#define __CHAOSVM_XFILE_DNA__								0xFBAC837E//用此值来唯一标识

// 运行模式
typedef enum _CHAOSVM_RUN_MODE {
	CRM_INFECT = 0,
	CRM_EMULATION,
	CRM_EMULATION_SYS,
	CRM_NETWORK
} CHAOSVM_RUN_MODE;

// 文件类型
typedef enum _CHAOSVM_FILETYPE {
	CFT_NONE = 0,
	CFT_EXE,
	CFT_DLL,
	CFT_SYS
} CHAOSVM_FILETYPE;

/*
 * 混乱虚拟机配置结构
 * 此结构目前只用于感染模式
 */
typedef struct _CHAOSVM_CONFIGURE {
	CHAOSVM_FILETYPE FileType;//要保护的文件类型
	__bool bUseByteCodeFile;//使用字节码文件
	__tchar szChaosVmByteCodeFileName[0x20];//字节码文件的名称
	__dword dwTmp;

	//////////////////////////////////////////////////////////////////////////
	// 力量保护器配置结构
	POWER_PROTECTER_CONFIGURE PowerProtecterConfigure;//此版本没啥作用

	//////////////////////////////////////////////////////////////////////////
	// 提示框选项,当cbc文件确实时调用
	__tchar szMessageBoxTitle[0x40];
	__tchar szMessageBoxContext[0x100];
	__dword dwMessageStyle;//消息框风格
} CHAOSVM_CONFIGURE, *PCHAOSVM_CONFIGURE;

// 混乱虚拟机运行时
#define __CHAOSVM_DECRYPT_OPCODE_TABLE_KEY_INFECT_MODE__							0xBD7115AB
#define __CHAOSVM_DECRYPT_OPCODE_TABLE_KEY_EMULATION_MODE__							0xACFC7763
typedef struct _CHAOSVM_RUNTIME {
	CHAOSVM_CPU Cpu;//CPU
	__memory pStack;//执行堆栈
	__integer iStackSize;//堆栈长度
	CPU_BASIC_REGISTERS LastCheckPoint;//最后一次调用寄存器的值
	CHAOSVMP_PROCEDURE Procedure;//指向函数记录结构
	__integer iIndex;//函数的Index
	__integer iInstIndex;//指令的Index
	__dword dwKey;//用于解码
	__address addrPrevProcedureAddress;//上一个函数的地址
	__integer iPrevProcedureSize;//上一个函数的长度

	__integer iDispSize;//当前指令Mod位的偏移大小

	/*
	 * 记录了当前的编码规则
	 * 在感染模式下这篇内存被加密了,在感染模式下与在仿真机模式下的密钥不一样
	 */
	__byte Opcode1Tbl[0x100];
	__byte Opcode2Tbl[0x100];
} CHAOSVM_RUNTIME, *PCHAOSVM_RUNTIME;

#define __GetRunTime__(pCPU)								((PCHAOSVM_RUNTIME)((pCPU)->pUserContext))
#define __GetKey__(pCPU)									(__GetRunTime__(pCPU)->dwKey)
#define __GetInitKey__(pCPU)								((__GetRunTime__(pCPU)->Procedure).dwKey)

// 函数指针声明
#if defined(__CHAOSVM_MODE_EMULATION__)
typedef __void (__API__ *FPChaosVmEmulationEntry)(PCHAOSVM_EMULATION_CONFIGURE pConfigure, PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile, PCHAOSVM_RUNTIME pRuntime);
#else
typedef __void (__API__ *FPChaosVmEntry)();
typedef __void (__API__ *FPChaosVmInit)();
#endif

#if defined(__cplusplus)
}
#endif

#endif
