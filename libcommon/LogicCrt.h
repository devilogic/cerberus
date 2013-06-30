#if !defined(__LOGICCRT_H__)
#define __LOGICCRT_H__

#include "TypeDef.h"
#include "Configure.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__void * __INTERNAL_FUNC__ LogicMalloc(__char *szFileName, __integer iLine, __integer iSize);
__void __INTERNAL_FUNC__ LogicFree(__char *szFileName, __integer iLine, __void *pPoint);
__void * __INTERNAL_FUNC__ LogicMemcpy(__char *szFileName, __integer iLine, __void *pDest, __void *pSrc, __integer iCount);
__void * __INTERNAL_FUNC__ LogicMemset(__char *szFileName, __integer iLine, __void *pSrc, __byte bVal, __integer iCount);
__sinteger __INTERNAL_FUNC__ LogicMemcmp(__void *pS1, __void *pS2, __integer iCount);
__void * __INTERNAL_FUNC__ LogicMemmove(__char *szFileName, __integer iLine, __void *pDest, __void *pSrc, __integer iCount);

__char * __INTERNAL_FUNC__ LogicStr2Lower(__char *pStr);
__char * __INTERNAL_FUNC__ LogicStr2LowerN(__char *pStr, __integer iCount);
__integer __INTERNAL_FUNC__ LogicStrlen(__char *pStr);
__sinteger __INTERNAL_FUNC__ LogicStrcmp(__char *pStr1, __char *pStr2);
__sinteger __INTERNAL_FUNC__ LogicStrncmp(__char *pStr1, __char *pStr2, __integer iCount);
__char * __INTERNAL_FUNC__ LogicStrstr(__char *pStr, __char *pFind);
__char * __INTERNAL_FUNC__ LogicStrstrInMemory(__char *pStr, __char *pFind, __integer iMemLen);
__char * __INTERNAL_FUNC__ LogicStrcpy(__char *szFileName, __integer iLine, __char *pTo, __char* pFrom);
__char * __INTERNAL_FUNC__ LogicStrncpy(__char *szFileName, __integer iLine, __char *pDest, __char *pSrc, __integer iCount);
__char * __INTERNAL_FUNC__ LogicStrchr(__char *pSrc, __char c);
__char * __INTERNAL_FUNC__ LogicStrrchr(__char *pSrc, __char c);
__char * __INTERNAL_FUNC__ LogicStrcat(__char *pSrc, __char *pAppend);
__tchar * __INTERNAL_FUNC__ LogicStr2Tcs(__char *pStr, __tchar *pWStr);
__tchar * __INTERNAL_FUNC__ LogicStr2TcsN(__char *pStr, __tchar *pWStr, __integer iCount);

__tchar * __INTERNAL_FUNC__ LogicTcs2Lower(__tchar *pStr);
__tchar * __INTERNAL_FUNC__ LogicTcs2LowerN(__tchar *pStr, __integer iCount);
__integer __INTERNAL_FUNC__ LogicTcslen(__tchar *pStr);
__sinteger __INTERNAL_FUNC__ LogicTcscmp(__tchar *pStr1, __tchar *pStr2);
__sinteger __INTERNAL_FUNC__ LogicTcsncmp(__tchar *pStr1, __tchar *pStr2, __integer iCount);
__tchar * __INTERNAL_FUNC__ LogicTcscpy(__char *szFileName, __integer iLine, __tchar *pTo, __tchar* pFrom);
__tchar * __INTERNAL_FUNC__ LogicTcsncpy(__char *szFileName, __integer iLine, __tchar *pDest, __tchar *pSrc, __integer iCount);
__tchar * __INTERNAL_FUNC__ LogicTcschr(__tchar *pSrc, __tchar c);
__tchar * __INTERNAL_FUNC__ LogicTcsrchr(__tchar *pSrc, __tchar c);
__tchar * __INTERNAL_FUNC__ LogicTcscat(__tchar *pSrc, __tchar *pAppend);
__char * __INTERNAL_FUNC__ LogicTcs2Str(__tchar *pWStr, __char *pStr);
__char * __INTERNAL_FUNC__ LogicTcs2StrN(__tchar *pWStr, __char *pStr, __integer iCount);

__time __INTERNAL_FUNC__ LogicTime(__time* pTime);
__void __INTERNAL_FUNC__ LogicSrand(__integer iSeed);
__integer __INTERNAL_FUNC__ LogicRand();

__void __INTERNAL_FUNC__ LogicQsort(__void *pBase0, __integer n, __integer iSize, __sinteger (__INTERNAL_FUNC__ *pComparFunc)(__CONST__ __void *, __CONST__ __void *));

#define __logic_isalpha__(c) ((c & 0xc0) == 0x40 && (unsigned)((c & 0x1f) - 1) < 26)
#define __logic_toupper__(c) (c & ~0x20)
#define __logic_tolower__(c) (c | 0x20)

// 开启位置记录
//#define __LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__											1
#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_new__(Type, Count)											LogicMalloc((__char *)__FILE__, __LINE__, sizeof(Type) * (Count))
#else
#define __logic_new__(Type, Count)											LogicMalloc(NULL, 0, sizeof(Type) * (Count))
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_new_size__(Size)											LogicMalloc((__char *)__FILE__, __LINE__, Size)
#else
#define __logic_new_size__(Size)											LogicMalloc(NULL, 0, Size)
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_delete__(Pointer)											{LogicFree((__char *)__FILE__, __LINE__, (__void *)Pointer);Pointer = NULL;}
#else
#define __logic_delete__(Pointer)											{LogicFree(NULL, 0, (__void *)Pointer);Pointer = NULL;}
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_memcpy__(pDest, pSrc, iCount)								LogicMemcpy((__char *)__FILE__, __LINE__, pDest, pSrc, iCount)
#else
#define __logic_memcpy__(pDest, pSrc, iCount)								LogicMemcpy(NULL, 0, pDest, pSrc, iCount)
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_memset__(pSrc, bVal, iCount)								LogicMemset((__char *)__FILE__, __LINE__, pSrc, bVal, iCount)
#else
#define __logic_memset__(pSrc, bVal, iCount)								LogicMemset(NULL, 0, pSrc, bVal, iCount)
#endif

#define __logic_memcmp__(pS1, pS2, iCount)									LogicMemcmp(pS1, pS2, iCount)

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_memmove__(pDest, pSrc, iCount)								LogicMemmove((__char *)__FILE__, __LINE__, pDest, pSrc, iCount)
#else
#define __logic_memmove__(pDest, pSrc, iCount)								LogicMemmove(NULL, 0, pDest, pSrc, iCount)
#endif

#define __logic_strcmp__(pStr1, pStr2)										LogicStrcmp(pStr1, pStr2)
#define __logic_tcscmp__(pStr1, pStr2)										LogicTcscmp(pStr1, pStr2)

#define __logic_strncmp__(pStr1, pStr2, iCount)								LogicStrncmp(pStr1, pStr2, iCount)
#define __logic_tcsncmp__(pStr1, pStr2, iCount)								LogicTcsncmp(pStr1, pStr2, iCount)

#define __logic_strstr__(pStr, pFind)										LogicStrstr(pStr, pFind)
#define __logic_strstrinmem__(pStr, pFind, iMemLen)							LogicStrstrInMemory(pStr, pFind, iMemLen)

#define __logic_strlen__(pStr)												LogicStrlen(pStr)
#define __logic_tcslen__(pStr)												LogicTcslen(pStr)

#define __logic_str2lower__(pStr)											LogicStr2Lower(pStr)
#define __logic_tcs2lower_(pStr)											LogicTcs2Lower(pStr)

#define __logic_str2lower_n__(pStr, iCount)									LogicStr2LowerN(pStr, iCount)
#define __logic_tcs2lower_n_(pStr, iCount)									LogicTcs2LowerN(pStr, iCount)

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_strcpy__(pTo, pFrom)										LogicStrcpy((__char *)__FILE__, __LINE__, pTo, pFrom)
#else
#define __logic_strcpy__(pTo, pFrom)										LogicStrcpy(NULL, 0, pTo, pFrom)
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_tcscpy__(pTo, pFrom)										LogicTcscpy((__char *)__FILE__, __LINE__, pTo, pFrom)
#else
#define __logic_tcscpy__(pTo, pFrom)										LogicTcscpy(NULL, 0, pTo, pFrom)
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_strncpy__(pDest, pSrc, iCount)								LogicStrncpy((__char *)__FILE__, __LINE__, pDest, pSrc, iCount)
#else
#define __logic_strncpy__(pDest, pSrc, iCount)								LogicStrncpy(NULL, 0, pDest, pSrc, iCount)
#endif

#if defined(__LOGIC_CRUNTIME_ENABLE_DEBUG_RECORD_LOCATION__)
#define __logic_tcsncpy__(pDest, pSrc, iCount)								LogicTcsncpy((__char *)__FILE__, __LINE__, pDest, pSrc, iCount)
#else
#define __logic_tcsncpy__(pDest, pSrc, iCount)								LogicTcsncpy(NULL, 0, pDest, pSrc, iCount)
#endif

#define __logic_strchr__(pSrc, c)											LogicStrchr(pSrc, c)
#define __logic_tcschr__(pSrc, c)											LogicTcschr(pSrc, c)

#define __logic_strrchr__(pSrc, c)											LogicStrrchr(pSrc, c)
#define __logic_tcsrchr__(pSrc, c)											LogicTcsrchr(pSrc, c)

#define __logic_strcat__(pSrc, pAppend)										LogicStrcat(pSrc, pAppend)
#define __logic_tcscat__(pSrc, pAppend)										LogicTcscat(pSrc, pAppend)

#define __logic_str2tcs__(pSrc, pWSrc)										LogicStr2Tcs(pSrc, pWSrc)
#define __logic_tcs2str__(pWSrc, pSrc)										LogicTcs2Str(pWSrc, pSrc)

#define __logic_str2tcs_n__(pSrc, pWSrc, n)									LogicStr2TcsN(pSrc, pWSrc, n)
#define __logic_tcs2str_n__(pWSrc, pSrc, n)									LogicTcs2StrN(pWSrc, pSrc, n)

#define __logic_time__(pTime)												LogicTime(pTime)
#define __logic_srand__(iSeed)												LogicSrand(iSeed)
#define __logic_rand__()													LogicRand()

#define __logic_qsort__(pBase0, n, iSize, pComparFunc)						LogicQsort(pBase0, n, iSize, pComparFunc)

/*
 * 这里列出的是只在调试状态下使用
 */
#if defined(_DEBUG)
// 调试配置结构
typedef struct _DEBUG_CONFIGURE {
	__bool bLog2File;//记录到文件
	__bool bBreakWhenHeapOverflow;//暂停当堆溢出后
	__char *szLogFilePath;//日志文件路径
} DEBUG_CONFIGURE, *PDEBUG_CONFIGURE;
__bool __INTERNAL_FUNC__ DebugConfigure(PDEBUG_CONFIGURE pDebugConfigure);
__void __INTERNAL_FUNC__ FreeDebugConfigure();
__void __INTERNAL_FUNC__ CheckHeapOverflow(__char *szFileName, __integer iLine);
__integer __INTERNAL_FUNC__ ShowAllocCount(__char *szFileName, __integer iLine);
__integer __INTERNAL_FUNC__ ShowInvalidPointCount(__char *szFileName, __integer iLine);
__void __INTERNAL_FUNC__ ReleaseInvalidPointList();
#define __logic_debug_configure__(pDebugConfigurePointArg)					DebugConfigure((pDebugConfigurePointArg))
#define __logic_free_debug_configure__()									FreeDebugConfigure()
#define __logic_check_heap_overflow__()										CheckHeapOverflow((__char *)__FILE__, __LINE__)
#define __logic_show_alloc_count__()										ShowAllocCount((__char *)__FILE__, __LINE__)
#define __logic_show_invalid_point_count__()								ShowInvalidPointCount((__char *)__FILE__, __LINE__)
#define __logic_release_invalid_point_list__()								ReleaseInvalidPointList()
#else
#define __logic_debug_configure__(pDebugConfigurePointArg)
#define __logic_free_debug_configure__()
#define __logic_check_heap_overflow__()
#define __logic_show_alloc_count__()
#define __logic_show_invalid_point_count__()
#define __logic_release_invalid_point_list__()
#endif

#if defined(__cplusplus)
}
#endif

#endif
