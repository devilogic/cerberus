#if !defined(__PRINTDBGINFO_H__)
#define __PRINTDBGINFO_H__

#include "Configure.h"
#include "TypeDef.h"
#include "LogicCrt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

//#define __PRINT_DBG_INFO__ 1

#define __PRINTDBGINFO_TITLE__		"<DbgInfo>"

#if defined(__PRINT_DBG_INFO__)
#if (MSVC_VER > 8)
#define __PrintDbgInfo__(...)													printf(__PRINTDBGINFO_TITLE__);printf(__VA_ARGS__);printf("\n")
#else
#define __PrintDbgInfo__()
#endif
#define __PrintDbgInfo_DumpMemory__(pInfo, pMemory, iLength)					PrintDbgInfo_DumpMemory(pInfo, pMemory, iLength)
#define __PrintDbgInfo_DumpMemoryToFile__(pInfo, pFileName, pMemory, iLength)	PrintDbgInfo_DumpMemoryToFile(pInfo, pFileName, pMemory, iLength)
#define __PrintDbgInfo_OutputDbgString__(pString)								PrintDbgInfo_OutputDbgString(pString)
#define __PrintDbgInfo_OutputDbgInteger__(iInteger)								PrintDbgInfo_OutputDbgInteger(iInteger)
#define __PrintDbgInfo_OutputDbgDumpMemory__(pInfo, pMemory, iSize)				PrintDbgInfo_OutputDbgDumpMemory(pInfo, pMemory, iSize)
#define __PrintDbgInfo_RecordToFileInit__(pFilePath)							PrintDbgInfo_RecordToFileInit(pFilePath)
#define __PrintDbgInfo_RecordStringToFile__(hHandle, pInfo)						PrintDbgInfo_RecordStringToFile(hHandle, pInfo)
#define __PrintDbgInfo_RecordIntegerToFile__(hHandle, iInteger)					PrintDbgInfo_RecordIntegerToFile(hHandle, iInteger)
#define __PrintDbgInfo_RecordDumpMemoryToFile__(hHandle, pInfo, pMemory, iSize)	PrintDbgInfo_RecordDumpMemoryToFile(hHandle, pInfo, pMemory, iSize)
#define __PrintDbgInfo_RecordToFileClose__(hHandle)								PrintDbgInfo_RecordToFileClose(hHandle)
#define __PrintDbgInfo_DebugBreak__(pName)										PrintDbgInfo_DebugBreak(pName)
#define __PrintDbgInfo_DebugerInit__(pDebuger)									PrintDbgInfo_DebugerInit(pDebuger)
#define __PrintDbgInfo_DebugerWrite__(pInfo)									PrintDbgInfo_DebugerWrite(pInfo)
#define __PrintDbgInfo_DebugerWriteLine__(pInfo)								PrintDbgInfo_DebugerWriteLine(pInfo)
#define __PrintDbgInfo_DebugerWriteInteger__(iInteger)							PrintDbgInfo_DebugerWriteInteger(iInteger)
#define __PrintDbgInfo_DebugerWriteFormatStringInteger__(pInfo, iInteger)		PrintDbgInfo_DebugerWriteFormatStringInteger(pInfo, (__integer)iInteger)
#define __PrintDbgInfo_DebugerReadLine__(pOutBuffer, iMaxSize)					PrintDbgInfo_DebugerReadLine(pOutBuffer, iMaxSize)
#define __PrintDbgInfo_DebugerBreakPoint__(pInfo, pParam)						PrintDbgInfo_DebugerBreakPoint(pInfo, (__void *)pParam)
#define __PrintDbgInfo_DebugerRelease__()										PrintDbgInfo_DebugerRelease()
#else
#if (MSVC_VER > 8)
#define __PrintDbgInfo__(...)
#else
#define __PrintDbgInfo__()
#endif
#define __PrintDbgInfo_DumpMemory__(pInfo, pMemory, iLength)
#define __PrintDbgInfo_DumpMemoryToFile__(pInfo, pFileName, pMemory, iLength)
#define __PrintDbgInfo_OutputDbgString__(pString)
#define __PrintDbgInfo_OutputDbgInteger__(iInteger)
#define __PrintDbgInfo_OutputDbgDumpMemory__(pInfo, pMemory, iSize)
#define __PrintDbgInfo_RecordToFileInit__(pFilePath)
#define __PrintDbgInfo_RecordStringToFile__(hHandle, pInfo)
#define __PrintDbgInfo_RecordIntegerToFile__(hHandle, iInteger)
#define __PrintDbgInfo_RecordDumpMemoryToFile__(hHandle, pInfo, pMemory, iSize)
#define __PrintDbgInfo_RecordToFileClose__(hHandle)
#define __PrintDbgInfo_DebugBreak__(pName)
#define __PrintDbgInfo_DebugerInit__(pDebuger)
#define __PrintDbgInfo_DebugerWrite__(pInfo)
#define __PrintDbgInfo_DebugerWriteLine__(pInfo)
#define __PrintDbgInfo_DebugerWriteInteger__(iInteger)
#define __PrintDbgInfo_DebugerWriteFormatStringInteger__(pInfo, iInteger)
#define __PrintDbgInfo_DebugerReadLine__(pOutBuffer, iMaxSize)
#define __PrintDbgInfo_DebugerBreakPoint__(pInfo, pParam)
#define __PrintDbgInfo_DebugerRelease__()
#endif

__void __INTERNAL_FUNC__ PrintDbgInfo_DumpMemory(__char *pInfo, __memory pMemory, __integer iLength);
__void __INTERNAL_FUNC__ PrintDbgInfo_DumpMemoryToFile(__char *pInfo, __char *pFileName, __memory pMemory, __integer iLength);
__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgString(__char *pString);
__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgInteger(__integer iInteger);
__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgDumpMemory(__char *pInfo, __memory pMemory, __integer iSize);
__dword __INTERNAL_FUNC__ PrintDbgInfo_RecordToFileInit(__char *pFilePath);
__void __INTERNAL_FUNC__ PrintDbgInfo_RecordStringToFile(__dword hHandle, __char *pInfo);
__void __INTERNAL_FUNC__ PrintDbgInfo_RecordIntegerToFile(__dword hHandle, __integer iInteger);
__void __INTERNAL_FUNC__ PrintDbgInfo_RecordDumpMemoryToFile(__dword hHandle, __char *pInfo, __memory pMemory, __integer iSize);
__void __INTERNAL_FUNC__ PrintDbgInfo_RecordToFileClose(__dword hHandle);
__void __INTERNAL_FUNC__ PrintDbgInfo_DebugBreak(__char *pName);
typedef __bool (__INTERNAL_FUNC__ *FPCustomDebuger)(__char *pCommand, __void *pParam);
__bool __INTERNAL_FUNC__ PrintDbgInfo_DebugerInit(FPCustomDebuger pDebuger);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWrite(__char *pInfo);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteLine(__char *pInfo);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteInteger(__integer iInteger);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteFormatStringInteger(__char *pInfo, __integer iInteger);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerReadLine(__memory pOutBuffer, __integer iMaxSize);
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerBreakPoint(__char *pInfo, __void *pParam);
__void __INTERNAL_FUNC__ PrintDbgInfo_DebugerRelease();

#if defined(__cplusplus)
}
#endif

#endif
