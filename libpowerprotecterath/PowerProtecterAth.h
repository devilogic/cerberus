#if !defined(__POWER_PROTECTER_ATTACH_H__)
#define __POWER_PROTECTER_ATTACH_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include "PowerProtecter.h"

#define __POWER_PROTECT_MAX_PROCEDURE__			1024
#define __POWER_PROTECT_MAX_INSTRUCTION__		1024

typedef __memory (__API__ *FPGenPowerProtecterInvokeThunkCode)(__integer iSize);

/*
 * 指令记录,记录了要保护的指令,要监视的地址
 * bWatched字段表明是否要监视其他内存
 */
typedef struct _POWER_PROTECTER_INSTRUCTION {
	POWER_PROTECTER_INSTRUCTION_RECORD Instruction;//要保护的指令
	POWER_PROTECTER_WATCH_RECORD WatchRecord;//要保护的地址
	__bool bWatched;//是否监视地址
} POWER_PROTECTER_INSTRUCTION, *PPOWER_PROTECTER_INSTRUCTION;

/*
 * 此结构由附加器使用,外部程序的命令行构成命令时,将要保护的详细信息输入到此
 */
typedef struct _POWER_PROTECTER_PROCEDURE {
	POWER_PROTECTER_PROCEDURE_RECORD Procedure[__POWER_PROTECT_MAX_PROCEDURE__];//要保护函数的信息
	POWER_PROTECTER_PROCEDURE_RECORD KeyProcedure[__POWER_PROTECT_MAX_PROCEDURE__];//对应的监视函数的信息
	POWER_PROTECTER_INSTRUCTION Instructions[__POWER_PROTECT_MAX_PROCEDURE__][__POWER_PROTECT_MAX_INSTRUCTION__];//要保护的指令
	__integer iInstructionCount[__POWER_PROTECT_MAX_PROCEDURE__];//每个函数保护指令的个数
	__integer iCount;//总共函数的计数
} POWER_PROTECTER_PROCEDURE, *PPOWER_PROTECTER_PROCEDURE;

// 力量保护器配置结构
typedef struct _POWER_PROTECTER_ATTACH_CONFIGURE {
	FPGenPowerProtecterInvokeThunkCode pGenPowerProtecterInvokeThunkCode;
	POWER_PROTECTER_PROCEDURE PowerProtecterProcedure;
} POWER_PROTECTER_ATTACH_CONFIGURE, *PPOWER_PROTECTER_ATTACH_CONFIGURE;

/*
 * 以下函数排列按照调用顺序
 */
__integer __API__ PowerProtectAthSelectProcedure(PPOWER_PROTECTER_PROCEDURE pRecord, __address addrProcedure, __integer iSize, __address addrKeyProcedure, __integer iKeySize, PPOWER_PROTECTER_INSTRUCTION pInstruction, __integer iInstCount);
__integer __API__ PowerProtecterAthCountAllEncryptProceduresSize(__memory pMem, PPOWER_PROTECTER_PROCEDURE pRecord);
__void __API__ PowerProtecterAthSetArguments(PPOWER_PROTECTER_ATTACH_CONFIGURE pConfigure);
__void __API__ PowerProtectAthGo(__memory pMem, PPOWER_PROTECTER_PROCEDURE pRecord, PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedures);

#if defined(__cplusplus)
}
#endif

#endif