/*
 * 将混乱虚拟机的DLL直接在文件中使用内存粒度展开并将此作为新节附加到要保护的程序上
 *
 * 分割符号:
 * '-':表示目标文件的分隔符
 * '*':表示NT新节的分隔符
 * '*-'表示在一个NT节内,只不过是划分空间明显的标记
 * 'x':表示X节的分隔符
 * '#':表示混乱虚拟机区域分隔符
 *
 * 混乱虚拟机在目标文件中的内存布局
 * --------------------
 * |                  |
 * |   原始目标文件   | 
 * |                  |
 * ********************
 * |   末尾数据
 * *-*-*-*-*-*-*-*-*-*-*
 * |   XFILE_HEADER   |
 * xxxxxxxxxxxxxxxxxxxx
 * |   XFILE_SECTION_HEADER(0)  |
 * |   XFILE_SECTION_HEADER(1)  |
 * |             .              |
 * |             .              |
 * |             .              |
 * |   XFILE_SECTION_HEADER(n)  |
 * xxxxxxxxxxxxxxxxxxxx
 * |   其余X节的节段    |
 * xxxxxxxxxxxxxxxxxxxx
 * |   混乱虚拟机(已经通过内存对齐展开)   |
 * ####################
 * |   混乱虚拟机数据区域   |
 * ####################
 * |   混乱虚拟机运行环境时队列结构   |
 * xxxxxxxxxxxxxxxxxxxx
 * |   其余X节的节段  |
 * ********************
 * |   其余NT节的节段 |
 * --------------------
 */

#if !defined(__CHAOSVMATH_H__)
#define __CHAOSVMATH_H__

#include "Common.h"
#include "ChaosVm.h"
#include "ChaosVmLdr.h"
#include "ChaosVmp.h"
#include "DISAth.h"
#include "PowerProtecterAth.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __CHAOSVMP_SECTION_NAME__				"CHAOSVMP"
#define __CHAOSATH_MAX_SECTION_NUMBER__			5
#define __CHAOSATH_XFILE_SECTION_PLUS_SIZE		0x1000

typedef __memory (__API__ *FPGenChaosVmInvokeThunkCode)(__integer iSize);

// 被保护的函数结构
typedef struct _CHAOSVMATH_PROCEDURE {
	__memory pAddress;//函数的文件地址
	__address addrMemoryAddress;//函数的内存地址
	__integer iSize;//函数的长度

	__memory pKeyAddress;//Key函数的文件地址
	__address addrKeyMemoryAddress;//Key函数的内存地址
	__integer iKeySize;//Key的函数长度
} CHAOSVMATH_PROCEDURE, *PCHAOSVMATH_PROCEDURE;

// 此结构用于配置混乱虚拟机保护的保护选项
typedef struct _CHAOSVMATH_CONFIGURE {
	//////////////////////////////////////////////////////////////////////////
	// 通用的选项
	CHAOSVM_RUN_MODE Mode;//采用什么模式

	// 所需的数据
	CHAOSVMATH_PROCEDURE ProceduceList[__MAX_VMP_PROCEDURE__];//要保护的函数队列
	__integer iProcedureCount;//函数队列的计数

	// 自定义花指令生成
	FPGenChaosVmInvokeThunkCode pGenChaosVmInvokeThunkCode;//产生混乱虚拟机调用头花指令的函数指针

	// 字节码文件的名称
	__tchar szChaosVmByteCodeFileName[0x20];

	//////////////////////////////////////////////////////////////////////////
	// 感染模式下的特殊选项
	__bool bUseByteCodeFile;//使用字节码文件

	//////////////////////////////////////////////////////////////////////////
	// 仿真模式下的特殊选项
	__bool bUseChaosVmEmulationInResource;//使用资源中的混乱虚拟机仿真器
	__tchar szChaosVmEmulationFileName[0x20];

	//////////////////////////////////////////////////////////////////////////
	// 力量保护配置
	POWER_PROTECTER_ATTACH_CONFIGURE PowerProtecterAttachConfigure;

	//////////////////////////////////////////////////////////////////////////
	// 提示框选项
	__tchar szMessageBoxTitle[0x40];
	__tchar szMessageBoxOnByteCodeFileNotExist[0x100];
	__tchar szMessageBoxOnEmulationFileNotExist[0x100];
	__dword dwMessageStyle;//消息框风格

	//////////////////////////////////////////////////////////////////////////
	// 调试虚拟机选项
	// 2012.2.9 新增
	CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE DebugConfigure;
} CHAOSVMATH_CONFIGURE, *PCHAOSVMATH_CONFIGURE;

// 文件类型
typedef CHAOSVM_FILETYPE	CHAOSVMATH_FILETYPE;

/*
 * 混乱虚拟机附加器结构
 * 此结构用于记录用户对于混乱虚拟机的配置操作以及配置结构
 */
typedef struct _CHAOSVMATH {
	//////////////////////////////////////////////////////////////////////////
	// 基本信息
	PCHAOSVMATH_CONFIGURE pConfigure;//配置结构
	CHAOSVMATH_FILETYPE FileType;//文件类型
	PXFILE_ATTACH_INFO pXFileAttachInfo;//X文件附加器信息结构
	XFILE_SECTION_HEADER ChaosVmXSectionHeader;//混乱虚拟机所在的X节的复制
	PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile;//混乱虚拟机仿真器的字节码文件

	__memory pChaosVm;//混乱虚拟机的内存映射
	__memory pOrigChaosVm;//原始的混乱虚拟机的内存映射
	__memory pChaosVmInTarget;//混乱虚拟机在目标文件中的映射
	__integer iChaosVmSize;//混乱虚拟机文件大小
	__integer iChaosVmSizeOfImage;//混乱虚拟机映射大小

	__offset ofChaosVmInTargetOffsetByXSectionBody;//在目标文件中的混乱虚拟机离当前X节头的偏移

	__offset ofChaosVmInTargetRVA;//混乱虚拟机在目标文件中的RVA
	__offset ofChaosVmInTargetOffset;//混乱虚拟机在目标文件中的文件偏移

	__offset ofChaosVmDataRvaByTarget;//混乱虚拟机数据区域离目标文件头的RVA
	__offset ofChaosVmDataOffsetByTarget;//混乱虚拟机数据区域离目标文件头的偏移

	__offset ofChaosVmRuntimeRvaByTarget;//混乱虚拟机运行时队列离目标文件头的RVA
	__offset ofChaosVmRuntimeOffsetByTarget;//混乱虚拟机运行时队列离目标文件头的偏移

	__offset ofPowerProtecterEncryptProceduresRvaByTarget;//力量保护器加密函数结构离目标文件头的偏移
	__offset ofPowerProtecterEncryptProceduresOffsetByTarget;//力量保护器加密函数结构离目标文件头的偏移

	__integer iChaosVmSectionSize;//混乱虚拟机节的总大小
	__integer iChaosVmDataSize;//混乱虚拟机数据区的大小
	__integer iChaosVmRuntimeSize;//混乱虚拟机运行时结构队列的大小
	__integer iPowerProtecterEncryptProceduresSize;//力量保护加密函数结构的总长度

	__address addrTargetImageBase;//目标文件的原始映射基地址
	__address addrChaosVmOrigImageBase;//混乱虚拟机原本的映射基地址
	__address addrChaosVmImageBaseInTarget;//混乱虚拟机在目标文件中的映射基地址 = addrTargetImageBase + ofChaosVmInTargetRVA

	__memory pProcedureWriteTo;//当前函数要写入目标程序的数据指针
	__dword dwKey;//加密函数的Key

	//////////////////////////////////////////////////////////////////////////
	// 保护后函数的存放地点
	PCHAOSVMP_PROCEDURE pChaosVmpProcedure[__MAX_VMP_PROCEDURE__];

	//////////////////////////////////////////////////////////////////////////
	// 一些用户自定义的函数接口
	FPOpcodeExchange pOpcodeExchange;//OP转换自定义函数
	FPModRmSibExchage pModRmSibExchange;//MODRM/SIB位转换自定义函数
	FPVmHash pVmHash;//自定义哈希函数
	FPVmEncrypt pVmEncrypt;//自定义加密函数
	FPVmInstRemainEncrypt pVmInstRemainEncrypt;//自定义指令剩余数据加密函数

	//////////////////////////////////////////////////////////////////////////
	// 混乱虚拟机或者混乱虚拟机加载器引出的函数指针与全局变量
	FPChaosVmEntry pChaosVmEntry;//混乱虚拟机入口
	FPChaosVmInit pChaosVmInit;//混乱虚拟机初始化函数
	PCHAOSVM_RUNTIME pChaosVmRuntimeList;//混乱运行环境时队列
	__integer *piVmpProcedureCount;//指向保护了多少个函数计数的指针
	union {
		PCHAOSVM_CONFIGURE pChaosVmConfigure;//混乱虚拟机配置结构
		PCHAOSVM_LOADER_CONFIGURE pChaosVmLdrConfigure;//混乱虚拟机加载器配置结构
	};

	__integer *piPowerProtecterEncryptProceduresCount;//力量保护器加密函数结构的计数
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pPowerProtecterEncryptProcedures;//力量保护器加密函数


	// 以下定义了各种指令编码所使用的分派函数表
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_FF;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_FE;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_C6;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_C7;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_F6;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_F7;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_80;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_81;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_83;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_8F;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_C0;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_C1;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_D0;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_D1;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_D2;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForOne_D3;
	PPARGS_DISPATCH_TABLE_ENTRY pOpcodeExtensionTableForTwo_0FBA;
	PONE_OPCODE_TABLE_ENTRY pOneByteOpcodeTable;
	PTWO_BYTE_OPCODE_TABLE_ENTRY pTwoByteOpcodeTable;
	PEFLAG_CONDITION_TABLE_ENTRY pEFlagContionTable;
	PMODRM_BYTE_ANALYSE_ROUTINE_TABLE_ENTRY pModRMAnalyseRoutineTable;

	// 以下定义了各种功能函数的离代码段首的偏移量
	__offset ofChaosVmEntry;
	__offset ofChaosVmInit;
	__offset ofChaosVmRuntimeList;
	__offset ofVmpProcedureCount;
	union {
		__offset ofChaosVmConfigure;
		__offset ofChaosVmLdrConfigure;
	};

	__offset ofPowerProtecterEncryptProceduresCount;//力量保护器加密函数结构计数偏移
	__offset ofPowerProtecterEncryptProcedures;//力量保护加密函数指针的偏移

	// 以下定义了各种分派表离代码段首的偏移量
	__offset ofOpcodeExtensionTableForOne_FF;
	__offset ofOpcodeExtensioTableForOne_FE;
	__offset ofOpcodeExtensionTableForOne_C6;
	__offset ofOpcodeExtensionTableForOne_C7;
	__offset ofOpcodeExtensionTableForOne_F6;
	__offset ofOpcodeExtensionTableForOne_F7;
	__offset ofOpcodeExtensionTableForOne_80;
	__offset ofOpcodeExtensionTableForOne_81;
	__offset ofOpcodeExtensionTableForOne_83;
	__offset ofOpcodeExtensionTableForOne_8F;
	__offset ofOpcodeExtensionTableForOne_C0;
	__offset ofOpcodeExtensionTableForOne_C1;
	__offset ofOpcodeExtensionTableForOne_D0;
	__offset ofOpcodeExtensionTableForOne_D1;
	__offset ofOpcodeExtensionTableForOne_D2;
	__offset ofOpcodeExtensionTableForOne_D3;
	__offset ofOpcodeExtensionTableForTwo_0FBA;
	__offset ofOneByteOpcodeTable;
	__offset ofTwoByteOpcodeTable;
	__offset ofEFlagContionTable;
	__offset ofModRMAnalyseRoutineTable;

} CHAOSVMATH, *PCHAOSVMATH;

// 目标结构返回信息
typedef struct _CHAOSVMATH_RET_INFO {
	__integer iTargetCodeSectionIndex;//原目标代码节索引
} CHAOSVMATH_RET_INFO, *PCHAOSVMATH_RET_INFO;

// 获取目标文件的类型
CHAOSVMATH_FILETYPE __API__ ChaosVmAthGetFileType(__tchar *pTargetFilePath);
// 初始化混乱虚拟机配置结构
__void __API__ ChaosVmAthInitConfigure(PCHAOSVMATH_CONFIGURE pConfigure);
// 选定一个要保护的函数
__void __API__ ChaosVmAthSelectProcedure(PCHAOSVMATH_CONFIGURE pConfigure, __address addrMemoryAddress, __integer iSize, __address addrKeyMemoryAddress, __integer iKeySize);
// 混乱虚拟机附加器(文件)
__dword __API__ ChaosVmAthAttach(PDISATH_CONFIGURE pConfigure);

#if defined(__cplusplus)
}
#endif

#endif
