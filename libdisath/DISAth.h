#if !defined(__DIS_ATTACH_H__)
#define __DIS_ATTACH_H__

#include "DISKernel.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 结构定义
 */
typedef struct _DISATH_CONFIGURE {
	__bool bIfXFileExistFailed;//如果X文件存在则失败

	// DIS模块相关
	union {
		__word wResourceID;//资源ID
		__tchar *szDISFilePath;//DIS的路径
	};
	__dword dwDISResourceKey;//DIS作为资源时的Key
	__tchar *szResourceType;//DIS资源的类型

	__bool bProtectMyIAT;//保护自身的引入表
	__bool bProtectTargetIAT;//保护目标程序的引入表

	XFILE_ATTACH_INFO XFileAttachInfo;//X文件附加信息

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为要重映射DLL的所需的字段
	__dword dwDISProtectDllCrc32List[__MAX_LIBRARY_COUNT__];//需要进行重映射的DLL的CRC值
	__integer iDISProtectDllCrc32Count;//需要进行重映射的DLL的CRC值列表计数
	__dword dwDISProtectDllCallDllMainCrc32List[__MAX_LIBRARY_COUNT__];//执行DllMain的库
	__integer iDISProtectDllCallDllMainCrc32Count;//执行DllMain的库列表计数

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为进行API抽取所需字段
	__dword dwDISProtectApiCrc32List[__MAX_API_NAME_CRC_COUNT__];//需要进行API抽取的API, CRC32值
	__integer iDISProtectApiCrc32Count;//需要进行API抽取的API数量

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为要重映射DLL的所需的字段
	__dword dwTargetProtectDllCrc32List[__MAX_LIBRARY_COUNT__];//需要进行重映射的DLL的CRC值
	__integer iTargetProtectDllCrc32Count;//需要进行重映射的DLL的CRC值列表计数
	__dword dwTargetProtectDllCallDllMainCrc32List[__MAX_LIBRARY_COUNT__];//执行DllMain的库
	__integer iTargetProtectDllCallDllMainCrc32Count;//执行DllMain的库列表计数

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为进行API抽取所需字段
	__dword dwTargetProtectApiCrc32List[__MAX_API_NAME_CRC_COUNT__];//需要进行API抽取的API, CRC32值
	__integer iTargetProtectApiCrc32Count;//需要进行API抽取的API数量

	// 自定义数据
	__void *pUserData0;
	__void *pUserData1;
	__void *pUserData2;
	__void *pUserData3;
} DISATH_CONFIGURE, *PDISATH_CONFIGURE;

/*
 * 引出接口函数
 */
__dword __API__ DISAthAttach(PDISATH_CONFIGURE pConfigure);

// 外部流程函数
#include "DISAthSteps.h"

#if defined(__cplusplus)
}
#endif

#endif
