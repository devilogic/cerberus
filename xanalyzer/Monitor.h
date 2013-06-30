#if !defined(__MONITOR_H__)
#define __MONITOR_H__

#include "Common.h"
#include "Support.h"

typedef struct _IAT_MONITOR_ITEM {
	struct _IAT_MONITOR_ITEM *pNext;
	__char szName[0x20];//函数名
} IAT_MONITOR_ITEM, *PIAT_MONITOR_ITEM;

typedef struct _PROC_MONITOR_ITEM {
	struct _PROC_MONITOR_ITEM *pNext;
	__address addrAddress;//要HOOK的内存地址
} PROC_MONITOR_ITEM, *PPROC_MONITOR_ITEM;

typedef struct _MONITOR_CONFIGURE {
	__integer iIatMonitorCount;//引入表监视个数
	PIAT_MONITOR_ITEM pIatMonitorItems;

	__integer iProcMonitorCount;//函数的个数
	PPROC_MONITOR_ITEM pProcMonitorItems;

	__bool bAllCall;//监视所有的CALL指令

	__tchar szProgramName[MAX_PATH];//要分析程序的名称
	__tchar szAnalyzeFileName[MAX_PATH];//分析文件结果名称
} MONITOR_CONFIGURE, *PMONITOR_CONFIGURE;

__bool __INTERNAL_FUNC__ Monitor(__tchar *pResultFilePath, PMONITOR_CONFIGURE pConfigure);

#endif