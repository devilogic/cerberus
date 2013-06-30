#if !defined(__MISC_H__)
#define __MISC_H__

#include "Common.h"
#include <Windows.h>
#include "xInject.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__bool __API__ Map2File(__tchar *pFilePath, __memory pMem, __integer iMemSize);
__bool __API__ AnsiToUnicode(__char *pSource, __word sLen, __wchar *pDestination, __word wLen);
__bool __API__ UnicodeToAnsi(__wchar *pSource, __word wLen, __char *pDestination, __word sLen);
__integer __API__ GetPidFromProcName(__tchar *lpszProcName);
__bool __API__ ExistFile(__tchar *lpszFilePath);
__bool __API__ CloseNX();//关闭DEP数据保护,在WIN2003与WIN XP SP2 下有效
typedef enum _WINDOWS_VERSION {
	WIN_NONE = 0,
	WIN_9X,
	WIN_2K,
	WIN_XP,
	WIN_2K3,
	WIN_VISTA,
	WIN_7
} WINDOWS_VERSION;
WINDOWS_VERSION __API__ GetWindowsVersion();

PIMAGE_NT_HEADERS __API__ LogicCheckSumMappedFile(__void *pBaseAddress, __integer iFileLength, __dword *pdwHeaderSum, __dword *pdwCheckSum);
__dword __API__ RefixCheckSum(__memory pMem, __integer iNewSize);
__tchar * __API__ GetLocalPath(HMODULE hMod, __tchar *szPath);
__bool __API__ FindProcessModules(__dword dwPID, __tchar *pModuleName);
__bool __API__ InsertRemoteThread(__tchar *szTargetProcess, __tchar *szDllPath);

#if defined(__cplusplus)
}
#endif

#endif
