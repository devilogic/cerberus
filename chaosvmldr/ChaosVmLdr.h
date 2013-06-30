#if !defined(__CHAOSVM_LDR_H__)
#define __CHAOSVM_LDR_H__

#include "Common.h"
#include "Support.h"
#include "ChaosVm.h"

#define __CHAOSVM_LOADER_XFILE_DNA__								0x7E83ACFB//用此值来唯一标识 

// 婚礼虚拟机加载器的信息结构
typedef struct _CHAOSVM_LOADER_DATA {
	__offset ofChaosVmRuntimeRVA;//混乱虚拟机运行环境时的RVA
} CHAOSVM_LOADER_DATA, *PCHAOSVM_LOADER_DATA;

// 混乱虚拟机加载器结构
typedef struct _CHAOSVM_LOADER_CONFIGURE {
	__bool bUseChaosVmEmulationInResource;//使用资源中的混乱虚拟机仿真器
	__tchar szByteCodeFileName[0x20];//字节码文件的名称
	__tchar szChaosVmEmulationFileName[0x20];//混乱虚拟机仿真器的名称
	CHAOSVM_EMULATION_CONFIGURE ChaosVmEmulationConfigure;//混乱虚拟机仿真器配置结构
	CHAOSVM_LOADER_DATA ChaosVmLoaderData;//混乱虚拟机加载器的数据

	//////////////////////////////////////////////////////////////////////////
	// 提示框选项,当cbc文件确实时调用
	__tchar szMessageBoxTitle[0x40];
	__tchar szMessageBoxContextOnByteCodeFileNotExist[0x100];
	__tchar szMessageBoxContextOnEmulationFileNotExist[0x100];
	__dword dwMessageStyle;//消息框风格

	//////////////////////////////////////////////////////////////////////////
	// 调试虚拟机选项
	// 2012.2.9 新增
	CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE DebugConfigure;
} CHAOSVM_LOADER_CONFIGURE, *PCHAOSVM_LOADER_CONFIGURE;

#endif
