#if !defined(__XDETOURS_H__)
#define __XDETOURS_H__

// 一个服务库可以支持无限数量的HOOK函数
// 可以HOOK API,也可以对指定的地址进行HOOK
// 对目标HOOK可以无限

#define __CONFIGURE_FILE_NAME__							_T("xd_config.cfg")
#define __XDETOURS_CONFIGURE_FILE_KEY__					0x99
#define __MAX_DETOURS_LIB__								0x08							//可以提供服务的库最大数量
#define __MAX_DETOURS_LIB_NAME_SIZE__					0x20							//函数名称的最大数量
#define __MAX_DETOURS_PROC__							0x10							//每个提供服务的库可以HOOK函数的总数
#define __MAX_DETOURS_PROC_NAME_SIZE__					0x20							//函数名称的最大数量
#define __MAX_DETOURS_TRAMPOLINE_NAME_SIZE__			__MAX_DETOURS_PROC_NAME_SIZE__	//保存trampoline数组的名称

typedef struct _XDETOURS_CONFIGURE {
	DWORD dwLibCount;
	TCHAR LibNames[__MAX_DETOURS_LIB__][__MAX_DETOURS_LIB_NAME_SIZE__];
} XDETOURS_CONFIGURE, *PXDETOURS_CONFIGURE;

typedef struct _XDETOURS_TARGET_API {
	TCHAR LibName[__MAX_DETOURS_LIB_NAME_SIZE__];
	CHAR ProcName[__MAX_DETOURS_PROC_NAME_SIZE__];
} XDETOURS_TARGET_API, *PXDETOURS_TARGET_API;

typedef struct _XDETOURS_TARGET_PROC {
	DWORD dwAddress;
} XDETOURS_TARGET_PROC, *PXDETOURS_TARGET_PROC;

#define __TYEP_HOOK_API__				1
#define __TYEP_HOOK_PROC__				2
typedef struct _XDETOURS_TARGET {
	DWORD dwType;
	XDETOURS_TARGET_API Api;
	XDETOURS_TARGET_PROC Procedure;
} XDETOURS_TARGET, *PXDETOURS_TARGET;

typedef struct _XDETOURS_LIB_CONFIGURE {
	DWORD dwProcCount;
	CHAR ProcNames[__MAX_DETOURS_PROC__][__MAX_DETOURS_PROC_NAME_SIZE__];
	XDETOURS_TARGET Targets[__MAX_DETOURS_PROC__];
	DWORD dwProcArgCount[__MAX_DETOURS_PROC__];
	
	CHAR TrampolineName[__MAX_DETOURS_TRAMPOLINE_NAME_SIZE__];
} XDETOURS_LIB_CONFIGURE, *PXDETOURS_LIB_CONFIGURE;

// 配置文件结构
typedef struct _XDETOURS_CONFIGURE_FILE {
	XDETOURS_CONFIGURE Names;															//服务库路径
	XDETOURS_LIB_CONFIGURE Info[__MAX_DETOURS_LIB__];									//服务库信息
	BOOL bHookAllImportTable;															//HOOK所有引入表的函数
} XDETOURS_CONFIGURE_FILE, *PXDETOURS_CONFIGURE_FILE;

#endif
