#if !defined(__DIS_KERNEL_H__)
#define __DIS_KERNEL_H__

#include "Support.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 所需结构定义
 */
// DIS的配置结构
typedef struct _DIS_CONFIGURE {
	//////////////////////////////////////////////////////////////////////////
	// 全局变量
	__offset ofOrigEntryRVA;//原始入口点的RVA
	__address addrOrigImageBase;//原始映射基地址
	__integer iOrigSizeOfImage;//原始映射长度
	__integer iNowSizeOfImage;//当前映射的长度

	IMPORT_PROTECT DISImportProtect;//DIS的引入表保护结构
	IMPORT_PROTECT TargetImportProtect;//目标文件的引入表保护结构

	__address addrDISNewImportTable[__MAX_JMP_ADDRESS_TABLE_COUNT__];//DIS新的引入地址表数据
	__address addrTargetNewImportTable[__MAX_JMP_ADDRESS_TABLE_COUNT__];//目标文件新的引入地址表数据

	//////////////////////////////////////////////////////////////////////////
	// 配置选项
	__bool bFirstRun;//第一次运行
	__bool bProtectMyIAT;//解密自身的引入表
	__bool bProtectTargetIAT;//解密目标程序的引入表

} DIS_CONFIGURE, *PDIS_CONFIGURE;

/*
 * 使用时需要引出变量
 */
__NEED_EXPORT__ __EXTERN__ DIS_CONFIGURE g_DISConfigure;																	//DIS的配置结构

/*
 * 只做声明的函数
 */
__memory __INTERNAL_FUNC__ DISAddThunkCodeStub(__address addrNowApiAddress);

/*
 * 调用接口
 */
//适用于EXE程序
__bool __API__ DISEntry();
__bool __API__ DISEntryInDll(__dword hModule, __dword ul_reason_for_call, __void *lpReserved);


// DNA设定
#include "DISDNA.h"

// 外部流程函数声明
#include "DISSteps.h"

#if defined(__cplusplus)
}
#endif

#endif
