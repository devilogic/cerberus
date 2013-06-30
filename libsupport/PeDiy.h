/*
 * 剖析PE文件辅助函数
 */
#if !defined(__PEDIY__H__)
#define __PEDIY__H__

#include "Common.h"
#include <Windows.h>
#include "winternl.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * 宏函数
 */
// 获取PEB
#if (MSVC_VER <= 8)
__inline struct _TEB * GetNtCurrentTeb( void ) { __asm mov eax, fs:[0x18] }
#else
#define GetNtCurrentTeb			NtCurrentTeb
#endif
#define __NtCurrentPeb__()		(GetNtCurrentTeb()->Peb)
// 获取当前的基地址
#define __GetNowImageBase__()	(GetNtCurrentTeb()->Peb->ImageBaseAddress)
// 获取DOS头
#define __GetDosHeader__(x)		((PIMAGE_DOS_HEADER)(x))
// 获取NT头
#define __GetNtHeader__(x)		((PIMAGE_NT_HEADERS)((__dword)__GetDosHeader__(x)->e_lfanew + (__dword)(x)))
// 获取首节节表
#define __GetSectionHeader__(x)	IMAGE_FIRST_SECTION(x)
// RVA换VA
#define __RvaToVa__(base,offset) ((__void *)((__dword)(base) + (__dword)(offset)))
// VA换RVA
#define __VaToRva__(base,offset) ((__void *)((__dword)(offset) - (__dword)(base)))
// 默认的新节属性
#define __DEF_NEWSECTION_CHARACTERISTICS__ IMAGE_SCN_CNT_CODE | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE

// 编译器宏定义
#if (MSVC_VER <= 8)
#define IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE				0x0040
#define IMAGE_DLLCHARACTERISTICS_NX_COMPAT					0x0100
#endif


/*
 * 函数申明
 */
// 获取NT头
PIMAGE_NT_HEADERS __API__ GetNtHeader(__memory pMem);
// 获取头节表从内存映射文件
PIMAGE_SECTION_HEADER __API__ GetFirstSection(__memory pMem);
// 获取头节表从NT头
PIMAGE_SECTION_HEADER __API__ GetFirstSectionByNtHeader(PIMAGE_NT_HEADERS pNtH);
// 获取末尾节
PIMAGE_SECTION_HEADER __API__ GetTailSection(__memory pMem);
// 获取节索引
__integer __API__ GetSectionIndex(__memory pMem, __char *pSectionName);
// 获取入口点节索引
__integer __API__ GetEntrySectionIndex(__memory pMem);
// 预估新节的节表
__bool __API__ PredictNewSectionHeader(__memory pMem, __dword dwVirtualSize, PIMAGE_SECTION_HEADER pNewSectionHeader);
// 获取入口点节
PIMAGE_SECTION_HEADER __API__ GetEntryPointSection(__memory pMem);
// 获取入口点内存地址
__address __API__ GetEntryPointMemoryAddress(__memory pMem);
// 获取节表从指定节名
PIMAGE_SECTION_HEADER __API__ GetSection(__memory pMem, __char *lpSectionName);
// 获取节表从节索引
PIMAGE_SECTION_HEADER __API__ GetSectionByIndex(__memory pMem, __integer iIndex);
// 检测某个数据目录项是否存在
PIMAGE_DATA_DIRECTORY __API__ ExistDataDirectory(__memory pMem, __integer iIndex);
// 随机所有节名
__void __API__ RandomAllSectionName(__memory pMem);
// 确定是有效的PE格式文件
__bool __API__ IsValidPE32(__memory pMem);
// 确定是否是一个SYS文件
__bool __API__ IsDriverFile(__memory pMem);
// 确定是否是一个DLL文件
__bool __API__ IsDllFile(__memory pMem);
// 获取正确的SizeOfImage
__integer __API__ CorrectImageSize(__memory pMem);
// 确定这个节是否有实际内容
__bool __API__ IsRawSection(PIMAGE_SECTION_HEADER pSectH);
// 获取时间戳
__dword __API__ GetTimeDateStamp(__memory pMem);
// 获取节的数量
__word __API__ GetNumberOfSections(__memory pMem);
// 是否存在于这个节内
__bool __API__ InThisSection(PIMAGE_SECTION_HEADER pSectH, __offset ofOffset, __bool bRva);
// 是否存在于这个节内,通过地址比较
__bool __API__ InThisSectionByAddress(PIMAGE_SECTION_HEADER pSectH, __address addrImageBase, __address addrAddress);
// 通过RVA获取节表
PIMAGE_SECTION_HEADER __API__ Rva2Section(__memory pMem, __offset ofRva);
// 通过RAW获取节表
PIMAGE_SECTION_HEADER __API__ Raw2Section(__memory pMem, __offset ofRaw);
// RVA 转换 RAW
__offset __API__ Rva2Raw(__memory pMem, __offset ofRva);
// RAW 转换 RVA
__offset __API__ Raw2Rva(__memory pMem, __offset ofRaw);
// 计算对齐
__integer __API__ Alig(__integer n, __integer iFactor, __bool bUp);
// 计算按照基地址对齐
#define __IMAGE_BASE_ALIGN__	0x1000//PAGE_SIZE = 40960
__address __API__ AligImageBase(__address n);
// 复制引出表
__void __API__ CopyExportTableTo(PIMAGE_EXPORT_DIRECTORY pExportDir, __offset ofNewRva, __offset ofOldRva);
// 复制引入表
__void __API__ CopyImportTableTo(PIMAGE_IMPORT_DESCRIPTOR pImportDesc, __offset ofNewRva, __offset ofOldRva);
// 复制资源节
__void __API__ CopyResourceTo(PIMAGE_RESOURCE_DIRECTORY pRootResDir, __offset ofNewRva, __offset ofOldRva);
// 复制基址重定位表
__void __API__ CopyBaseRelocationTo(PIMAGE_BASE_RELOCATION pBaseRelocation, __offset ofNewRva, __offset ofOldRva, __integer iSize);
// 寻找资源通过类型
PIMAGE_RESOURCE_DATA_ENTRY __API__ FindResourceInfo(__memory pMem, __integer iType);
typedef struct _RESOURCE_INFO {
	PIMAGE_RESOURCE_DATA_ENTRY pDataEntry;//入口
	__byte *pPoint;//数据指针
	__integer iPointSize;//数据长度
} RESOURCE_INFO, *PRESOURCE_INFO;
// 获取资源manifest数据
PRESOURCE_INFO __API__ GetManifestResourceInfo(__memory pMem);
// 获取资源桌面ICON数据
PRESOURCE_INFO __API__ GetIconResourceInfo(__memory pMem);
// 删除数据目录项
__bool __API__ DeleteDataDirectoryObject(__memory pMem, __integer iObject);
__bool __API__ DeleteDataDirectoryObjectOnMemMap(__memory pMem, __integer iObject);
// 添加新节
PIMAGE_SECTION_HEADER __API__ AddSection(__memory pMem, __char *Name, __dword Characteristics, __dword VirtualSize, __memory pData, __bool bForce);
// 覆盖末尾节通过内存
PIMAGE_SECTION_HEADER __API__ CoverTailSectionFromImage(__memory pMem, __memory *pNewMemPoint, __integer iMemSize, __integer iNewSize, __memory pData, __integer iDataSize, __integer *piNewMemSize);
// 覆盖末尾节
PIMAGE_SECTION_HEADER __API__ CoverTailSection(__tchar *pFilePath, __memory *pMemPoint, __integer iNewSize, __memory pData, __integer iDataSize, __integer *piNewMemSize);
// 删除节
__bool __API__ DelSectionBySectionIndex(__memory pMem, __integer n);
__bool __API__ DelSectionBySectionName(__memory pMem, __char *pName);
__bool __API__ DelSectionBySectionHeader(__memory pMem, PIMAGE_SECTION_HEADER pSectH);
__bool __API__ DelSectionBySectionIndexOnMemMap(__memory pMem, __integer n);
__bool __API__ DelSectionBySectionNameOnMemMap(__memory pMem, __char *pName);
__bool __API__ DelSectionBySectionHeaderOnMemMap(__memory pMem, PIMAGE_SECTION_HEADER pSectH);
// 获取文件
__integer __API__ GetFilePhySize(__tchar *lpszFile);
// 映射文件
__memory __API__ MappingFile(__tchar *lpszFile, __integer *piFileSize, __bool bWrite, __integer iMaximumSizeHigh, __integer iMaximumSizeLow);
// 重新映射文件加上新的长度
__memory __API__ MappingFilePlusNewSize(__tchar *lpszFile, __memory pMap, __integer iOldSize, __integer iNewPlusSize, __bool bWrite);
// 解除映射文件
__bool __API__ UnMappingFile(__memory pBaseAddress);
// 获取真实的文件长度
__integer __API__ GetRealPeFileSize(__memory pMem);
// 获取末尾数据指针
__memory __API__ GetTailDataPoint(__memory pMem, __integer iFileSize);
// 获取末尾数据长度
__integer __API__ GetTailDataSize(__memory pMem, __integer iFileSize);
// 重新设置文件末尾
__integer __API__ ResetFileTail(__tchar *lpszFile, __integer iNewTail);
// 计算重新映射增加的长度,当要添加新节时
__integer __API__ GetAddSectionMapSize(__memory pMem, __integer iNewMap);
// 拷贝一个PE文件映射到另一片内存,2012.2.7新增
__bool __API__ CopyMemToMem(__memory pFromMemory, __memory pToMemory, __integer iSizeOfImage);
// 拷贝一个PE文件映射到另一片内存并使用内存对齐
__bool __API__ CopyMemToMemBySecAlign(__memory pFromMemory, __memory pToMemory, __integer iSizeOfImage);
// 设置内存保护
__bool __API__ ProtectImage(__memory pImageBase, __bool bWriteAll);
// 按照节设置节的内存属性
__bool __API__ SetSectionCharacteristics(__memory pImageBase);
// 设置当前映射所有节的某个属性
__void __API__ SetAllSectionCharacteristics(__memory pMem, __dword dwCharacteristics);
// 修复绑定输入表
__bool __API__ RefixBoundIAT(__memory pImageBase);
// 修复引入表
__bool __API__ RefixIAT(__memory pImageBase);
// 加解密引入表
typedef enum _CRYPTIAT_TYPE {
	LIB_NAME = 0,
	PROC_NAME = 1
} CRYPTIAT_TYPE;
typedef __void (__INTERNAL_FUNC__ *FPCryptIAT)(__integer iIndex, CRYPTIAT_TYPE Type, __memory pData, __integer iDataSize, __bool bOrd, __dword dwFirstThunk, __memory pArgs);
// 加密引入表
__bool __API__ EncryptIAT(PIMAGE_IMPORT_DESCRIPTOR pImportDescryptor, __address addrImageBase, FPCryptIAT pEncryptIAT, __void *pEncryptFuncArgs, __bool bOnFile);
// 解密引入表
__bool __API__ DecryptIAT(PIMAGE_IMPORT_DESCRIPTOR pImportDescryptor, __address addrImageBase, FPCryptIAT pDecryptIAT, __void *pEncryptFuncArgs);
// 遍历引入表
#define FPShowImportDetail FPCryptIAT
__bool __API__ ShowIAT(PIMAGE_IMPORT_DESCRIPTOR pImportDescryptor, __address addrImageBase, FPShowImportDetail pShowIAT, __void *pShowFuncArgs, __bool bOnFile);
// 统计引入表库的个数
__integer __API__ CountLibraryInImportTable(__memory pMem, __bool bOnFile);
// 统计引入表数据的长度
__integer __API__ CountImportTableDataSize(__memory pMem, __bool bOnFile);
// 构建一个输入表
PIMAGE_IMPORT_DESCRIPTOR __API__ MakeImportDescriptor(__memory pMem, __integer iLibCount, __integer iHowManyProcInEachLib, __integer *iSize);
// 修复TLS节
__bool __API__ RefixTLS(__memory pImageBase, __bool bDetach);
// 重定位程序
__bool __API__ BaseRelocation(__memory pMem, __address addrOldImageBase, __address addrNewImageBase, __bool bIsInFile);
// 重定位程序,重定位到一个基地址,写入时是写到另外一个基地址
__bool __API__ BaseRelocationAssignImageBaseWriteToOtherImageBase(__address addrWriteTo, __address addrOldImageBase, __address addrNewImageBase, __bool bIsInFile);
// 使用重定位节修复直接作用于文件
__bool __API__ BaseRelocationOnFile(__memory pMem, __address addrNewImageBase);
// 重定位程序,重定位到一个基地址,写入时是写到另外一个基地址 写入地址为文件中
__bool __API__ BaseRelocationAssignImageBaseWriteToOtherImageBaseOnFile(__memory pMem, __address addrNewImageBase);
// HOOK引出表
FARPROC __API__ HookExportProcAddress(HMODULE hModule, __char *lpProcName, FARPROC fpAddr);
// 从引出表中获取函数地址通过文件
FARPROC __API__ xGetProcAddressImmediately(HMODULE hDll, __char *pFuncName);
FARPROC __API__ xGetProcAddress(HMODULE hDll, __char *pFuncName);
FARPROC __API__ xGetAddressFromOnFile(__memory pMem, __char *pFuncName, __offset *pofFuncRva);
typedef __integer (__INTERNAL_FUNC__ *FPHashFunc)(__memory pTarget, __integer iTargetSize, __memory pHashValue);
FARPROC __API__ xGetProcAddressByHash(HMODULE hDll, __memory pHashPoint, __integer iHashSize, FPHashFunc pHashFunc);
FARPROC __API__ xGetProcAddressImmediatelyByHash(HMODULE hDll, __memory pHashPoint, __integer iHashSize, FPHashFunc pHashFunc);
FARPROC __API__ xGetProcAddressEx(HMODULE hDll, __memory pHashPoint, __integer iHashSize, FPHashFunc pHashFunc, FARPROC fpLoadLibraryA);
// PE加载器
typedef __bool (__INTERNAL_FUNC__ *FPRefixIAT)(__void *pArg);//修复引入表函数原型
typedef __void (__INTERNAL_FUNC__ *FPEntryFunction)();//入口点原型
FPEntryFunction __API__ PeLoader(__memory pLoadCode, __memory pOutMemory, __integer iOutMemorySize, __bool bRefixIAT, FPRefixIAT pRefixIAT, __void *pRefixIATArg);

// 重新整理映像
__bool __API__ PrepareImage(__memory pMemoryImage, __integer iImageSize, __bool bRefFixTls, __bool bRefixIAT, FPRefixIAT pRefixIAT, __void *pRefixIATArg);
// 加载DLL
__void __API__ InitDllManager();
__void __API__ DestoryDllManager();
typedef __bool (__API__ *FPDllMain)(HMODULE hinstDLL, __dword fdwReason, __void *lpvReserved);
HMODULE __API__ xLoadLibraryFromMemoryEx(__memory pDllCode, __memory pOutMemory, __dword dwFlags);
HMODULE __API__ xLoadLibraryFromMemory(__memory pDllCode, __tchar *svMappingName, __dword dwFlags);
HMODULE __API__ xLoadLibrary(__tchar *pLibName);
HMODULE __API__ xGetModuleHandle(__tchar *pLibName);
// 释放DLL
__bool __API__ xFreeLibrary(HMODULE hLibModule);
// 替换应用程序ICON
__void __API__ ChangedExeIcon(__tchar *lpExeName, __tchar *lpIconFile);
// 获取kernel32的基地址
HMODULE __API__ GetKernel32BaseAddress();
// 获取ntdll的基地址
HMODULE __API__ GetNtdllBaseAddress();
// 获取LoadLibraryA的地址
FARPROC __API__ GetLoadLibraryAAddress();

// 操作资源
#include "OptResource.h"

// 定义数据
#define __CRC32_LOADLIBRARYA_STR__						0x3FC1BD8D
#define __CRC32_SETUNHANDLEDEXCEPTIONFILTER_STR__		0xCB841A54
#define __CRC32_VIRTUALALLOC_STR__						0x09CE0D4A
typedef HMODULE (WINAPI *FPLoadLibraryA)(__char *lpFileName);
typedef LPVOID (WINAPI *FPVirtualAlloc)(__void *lpAddress, __integer iSize, __dword flAllocationType, __dword flProtect);
typedef LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI *FPSetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);

/*
 * 内嵌代码
 */
#include "udis86.h"
#include "hde32/hde32.h"
#include "logic.h"
// 重映射DLL
__memory __API__ RemapDll(__memory pOrigMap, FPVirtualAlloc pVirtualAlloc, __bool bRunDllMain);
// 函数重定位修复相关
#include "ProcedureRelocation.h"
// 保护引入表
#include "ImpTblProtecter.h"


//////////////////////////////////////////////////////////////////////////
// 2011年3月30日以后追加
// 设置所有节可写
__void __API__ SetAllSectionCanWrite(__memory pMem);

// ApiSetMap结构
typedef struct _API_SET_MAP_HEADER {
	__dword dwVersionNumber;
	__dword dwNumberOfApiSetModules;
} API_SET_MAP_HEADER, *PAPI_SET_MAP_HEADER;

typedef struct _API_SET_MAP_ENTRY {
	__dword dwNameOfApiSetModuleRVA;
	__dword dwSizeOfName;
	__dword dwHostModulesRVA;
} API_SET_MAP_ENTRY, *PAPI_SET_MAP_ENTRY;

typedef struct _API_SET_MAP_HOST_HEADER {
	__dword dwNumberOfHosts;
} API_SET_MAP_HOST_HEADER, *PAPI_SET_MAP_HOST_HEADER;

typedef struct _API_SET_MAP_HOST_ENTRY {
	__dword dwNameOfImportModuleRVA;
	__dword dwSizeOfImportModuleName;
	__dword dwNameOfHostRVA;
	__dword dwSizeOfHostName;
} API_SET_MAP_HOST_ENTRY, *PAPI_SET_MAP_HOST_ENTRY;
// 获取APISETMAP的头结构
PAPI_SET_MAP_HEADER __API__ GetApiSetMapHeader();
// 从当前的模块链中找出指定的模块
PLDR_MODULE __API__ GetExistModuleInLoadModuleList(__memory pBaseAddress);
// 计算当前加载模块链中存在的模块数量
__integer __API__ GetLoadModuleCount();

#if defined(__cplusplus)
}
#endif

#endif
