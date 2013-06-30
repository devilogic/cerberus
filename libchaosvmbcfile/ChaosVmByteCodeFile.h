#if !defined(__CHAOSVM_BYTECODE_FILE_H__)
#define __CHAOSVM_BYTECODE_FILE_H__

#include "Common.h"

#define __CHAOSVM_BYTECODE_SIGN__							0xDEADDAED//字节码文件的标识	
#define __IsChaosVmByteCodeFile__(x)						((x)->dwSign == __CHAOSVM_BYTECODE_SIGN__)//确定是否是混乱虚拟机的字节码文件

// 仿真机调试选项,2012.2.9 新增
typedef struct _CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE {
	__bool bDebugChaosVm;
	__bool bBreakPoint;
} CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE, *PCHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE;

// 仿真模式配置结构
typedef struct _CHAOSVM_EMULATION_CONFIGURE {
	__dword dwTargetOrigImageBase;//被保护程序原始的基地址
	__dword dwTargetOrigSizeOfImage;//被保护程序原始的映射长度
	__dword dwTargetNowImageBase;//被保护程序当前的基地址
	__dword dwTargetNowSizeOfImage;//被保护程序的当前映射长度

	//////////////////////////////////////////////////////////////////////////
	// 混乱虚拟机仿真机调试选项,2012.2.9 新增
	CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE DebugConfigure;
} CHAOSVM_EMULATION_CONFIGURE, *PCHAOSVM_EMULATION_CONFIGURE;

/*
 * ByteCode文件结构
 * CHAOSVM_EMULATION_BYTECODE_FILE
 * N个(CHAOSVM_EMULATION_BYTECODE_PROCEDURE + VmpProcedure)
 */
typedef struct _CHAOSVM_EMULATION_BYTECODE_PROCEDURE {
	__dword dwSize;//加上节头此节的长度
	__dword dwAttribute;//函数的属性
} CHAOSVM_EMULATION_BYTECODE_PROCEDURE, *PCHAOSVM_EMULATION_BYTECODE_PROCEDURE;

// 仿真环境的BYTECODE结构
typedef struct _CHAOSVM_EMULATION_BYTECODE_FILE {
	__dword dwSign;
	__dword dwSize;
	__dword dwProcedureCount;
	__dword dwCrc32;//整个字节码文件的CRC32值,除头部外
} CHAOSVM_EMULATION_BYTECODE_FILE, *PCHAOSVM_EMULATION_BYTECODE_FILE;

PCHAOSVM_EMULATION_BYTECODE_FILE __API__ ChaosVmByteCodeFileGenByteCodeFile();
__void __API__ ChaosVmByteCodeFileReleaseByteCodeFile(PCHAOSVM_EMULATION_BYTECODE_FILE *pFilePoint);
PCHAOSVM_EMULATION_BYTECODE_PROCEDURE __API__ ChaosVmByteCodeFileAddByteCodeProcedureToFile(PCHAOSVM_EMULATION_BYTECODE_FILE *pFilePoint, __memory pProcedure, __integer iProcSize);
__bool __API__ ChaosVmByteCodeFileOutputByteCodeFileToFile(__tchar *szFilePath, PCHAOSVM_EMULATION_BYTECODE_FILE pFile);
__bool __API__ ChaosVmByteCodeFileVerifySign(PCHAOSVM_EMULATION_BYTECODE_FILE pFile, __dword *pdwCrc32);
__integer __API__ ChaosVmByteCodeFileGetProcedureCount(PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile);
__memory __API__ ChaosVmByteCodeFileGetProcedureByteCode(__integer iIndex, PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile);

#endif