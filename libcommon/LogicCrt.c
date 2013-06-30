#include "LogicCrt.h"
#include <Windows.h>

#define __ROUND_DOWN__(n, align) \
	(((__integer)n) & ~((align) - 1l))

#define __ROUND_UP__(n, align) \
	__ROUND_DOWN__(((__integer)n) + (align) - 1, (align))

/*
 * 内部函数声明
 */
__void *__INTERNAL_FUNC__ InternalAllocMemory(__integer iSize);
__bool __INTERNAL_FUNC__ InternalFreeMemory(__void *pPoint);

/*
 * 为了检测堆内存释放平衡
 * 仅在调试时使用
 */
#if defined(_DEBUG)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 用于记录地址的链表
typedef struct _DEBUG_ALLOC_ADDRESS {
	__address addrAddress;//分配的地址
	__address addrTailSign;//末尾标志地址
	__integer iSize;//长度
	__char *pFilePath;//文件路径
	__integer iLine;//行号
	struct _DEBUG_ALLOC_ADDRESS *pNext;
} DEBUG_ALLOC_ADDRESS, *PDEBUG_ALLOC_ADDRESS;

// 用于记录无效指针
typedef struct _DEBUG_INVALID_POINT {
	__address addrAddress;//指针地址
	__char *pFilePath;//文件路径
	__integer iLine;//行号
	struct _DEBUG_INVALID_POINT *pNext;
} DEBUG_INVALID_POINT, *PDEBUG_INVALID_POINT;

__integer g_iAllocCount = 0;
PDEBUG_ALLOC_ADDRESS g_pAllocHeader = NULL;
PDEBUG_ALLOC_ADDRESS *g_pAllocCurrent = &g_pAllocHeader;

// 无效指针
__integer g_iInvalidPointCount = 0;
PDEBUG_INVALID_POINT g_pInvalidPointHeader = NULL;
PDEBUG_INVALID_POINT *g_pInvalidPointCurrent = &g_pInvalidPointHeader;

DEBUG_CONFIGURE g_DebugConfigure;
FILE *g_pDebugLogFile = NULL;

#define __HEAP_TAIL_SIGN_1__		0xFF1C54AB
#define __HEAP_TAIL_SIGN_2__		0xDE7A3C48
#define __HEAP_TAIL_SIGN_SIZE__		8

// 输出宏
#if (MSVC_VER > 8)
#define __LogicDebugOutput__(pFmt, ...) { \
	if (g_DebugConfigure.bLog2File) { \
		fprintf(g_pDebugLogFile, pFmt, __VA_ARGS__); \
	} else { \
		printf(pFmt, __VA_ARGS__); \
	}\
}
#else
#define __LogicDebugOutput__
#endif

#define __BreakWhenHeapOverflow__()					(g_DebugConfigure.bBreakWhenHeapOverflow)

// 配置调试配置
__bool __INTERNAL_FUNC__ DebugConfigure(PDEBUG_CONFIGURE pDebugConfigure) {
	g_DebugConfigure.bBreakWhenHeapOverflow = pDebugConfigure->bBreakWhenHeapOverflow;
	g_DebugConfigure.bLog2File = pDebugConfigure->bLog2File;
	// 如果将调试信息输出到日志
	if (g_DebugConfigure.bLog2File) {
		g_DebugConfigure.szLogFilePath = pDebugConfigure->szLogFilePath;
		// 新建日志文件
		g_pDebugLogFile = fopen(g_DebugConfigure.szLogFilePath, "w");
		if (!g_pDebugLogFile) return FALSE;
	}
	return TRUE;
}

// 释放调试配置
__void __INTERNAL_FUNC__ FreeDebugConfigure() {
	// 关闭日志文件
	if (g_DebugConfigure.bLog2File) {
		fclose(g_pDebugLogFile);
		g_pDebugLogFile = NULL;
	}
}

// 检测堆溢出情况
__void __INTERNAL_FUNC__ CheckHeapOverflow(__char *szFileName, __integer iLine) {
	PDEBUG_ALLOC_ADDRESS pCurr = g_pAllocHeader;
	__integer i = 0;
	while (pCurr) {
		// 检测末尾内存
		__dword *pTailSign = NULL;
		pTailSign = (__dword *)(pCurr->addrTailSign);
		if ((*pTailSign != __HEAP_TAIL_SIGN_1__) || (*(pTailSign + 1) != __HEAP_TAIL_SIGN_2__)) {
			__LogicDebugOutput__("<Debug>at source code[%s:%lu] file = %s, line = %d, address = 0x%4X, size = %d\n", szFileName, iLine, \
								pCurr->pFilePath, pCurr->iLine, \
								pCurr->addrAddress, pCurr->iSize);
			i++;
		}
		pCurr = pCurr->pNext;
	}

	if (!i) {
		__LogicDebugOutput__("<Debug>no heap overflow\n");
	} else {
		__LogicDebugOutput__("<Debug>%d heap overflow\n", i);
	}
}

// 显示分配内存的计数
__integer __INTERNAL_FUNC__ ShowAllocCount(__char *szFileName, __integer iLine) {
	PDEBUG_ALLOC_ADDRESS pCurr = g_pAllocHeader;
	/* 无内存泄漏 */
	if (!g_iAllocCount) {
		__LogicDebugOutput__("<Debug>no memory leak! ^_^\n");
		return g_iAllocCount;
	}
	__LogicDebugOutput__("<Debug>%d memory not free\n", g_iAllocCount);
	while (pCurr) {
		__LogicDebugOutput__("<Debug>at source code[%s:%lu] -> %p,size=%lu\n", pCurr->pFilePath, pCurr->iLine, pCurr->addrAddress, pCurr->iSize);
		pCurr = pCurr->pNext;
	}

	return g_iAllocCount;
}

// 通过地址获取记录结构
PDEBUG_ALLOC_ADDRESS __INTERNAL_FUNC__ QueryDebugAllocAddress(__address addrAddress) {
	PDEBUG_ALLOC_ADDRESS pCurr = NULL;
	pCurr = g_pAllocHeader;
	while (pCurr) {
		if (pCurr->addrAddress == addrAddress)
			return pCurr;
		pCurr = pCurr->pNext;
	}
	return NULL;
}

// 显示无效指针
__integer __INTERNAL_FUNC__ ShowInvalidPointCount(__char *szFileName, __integer iLine) {
	PDEBUG_INVALID_POINT pInvalidCurr = g_pInvalidPointHeader;

	if (g_iInvalidPointCount) {
		printf("<Debug>there are %d invalid point\n", g_iInvalidPointCount);
		// 检测无效指针
		while (pInvalidCurr) {
			__LogicDebugOutput__("<Debug>there is a invalid point at source code[%s:%lu] -> %p\n", \
								pInvalidCurr->pFilePath, pInvalidCurr->iLine, pInvalidCurr->addrAddress);
			pInvalidCurr = pInvalidCurr->pNext;
		}
	} else {
		__LogicDebugOutput__("<Debug>no invalid point! ^_^\n", g_iInvalidPointCount);
	}

	return g_iInvalidPointCount;
}

// 释放无效指针链
__void __INTERNAL_FUNC__ ReleaseInvalidPointList() {
	PDEBUG_INVALID_POINT pInvalidCurr = g_pInvalidPointHeader;
	PDEBUG_INVALID_POINT pNext = NULL;
	while (pInvalidCurr) {
		pNext = pInvalidCurr->pNext;
		InternalFreeMemory(pInvalidCurr);
		pInvalidCurr = pNext;
	}
	g_pInvalidPointHeader = NULL;
	g_pInvalidPointCurrent = &g_pInvalidPointHeader;
	g_iInvalidPointCount = 0;
}

__void __INTERNAL_FUNC__ DebugFreeMemory(__char *szFileName, __integer iLine, __address addrAddress) {
	PDEBUG_ALLOC_ADDRESS pCurr = g_pAllocHeader;
	PDEBUG_ALLOC_ADDRESS pSwitch = NULL;
	/* 遍历链表 */
	while (pCurr) {
		/* 找到要删除的节点 */
		if (pCurr->addrAddress == addrAddress) {
			/* 如果是头节点 */
			if (!pSwitch) {
				pSwitch = pCurr->pNext;
				if (pCurr->addrAddress) InternalFreeMemory((__void *)(pCurr->addrAddress));
				InternalFreeMemory(pCurr);
				g_pAllocHeader = pSwitch;
				/* 如果链表中只有一个头节点 */
				if (!g_pAllocHeader) g_pAllocCurrent = &g_pAllocHeader;
				/* 如果是尾节点 */
			} else if (!(pCurr->pNext)) {
				if (pCurr->addrAddress) InternalFreeMemory((__void *)(pCurr->addrAddress));
				InternalFreeMemory(pCurr);
				pSwitch->pNext = NULL;
				g_pAllocCurrent = &(pSwitch->pNext);
				/* 如果删除的节点属于中间位置 */
			} else {
				pSwitch->pNext = pCurr->pNext;
				if (pCurr->addrAddress) InternalFreeMemory((__void *)(pCurr->addrAddress));
				InternalFreeMemory(pCurr);
			}/* end else */
			// 这里应该是正常退出
			g_iAllocCount--;
			return;
		}/* end if */
		pSwitch = pCurr;
		pCurr = pCurr->pNext;
	}/* end while */

	// 到达这里说明了,指针不在链表里,属于无效指针
	(*g_pInvalidPointCurrent) = (PDEBUG_INVALID_POINT)InternalAllocMemory(sizeof(DEBUG_INVALID_POINT));
	(*g_pInvalidPointCurrent)->pFilePath = szFileName;
	(*g_pInvalidPointCurrent)->iLine = iLine;
	(*g_pInvalidPointCurrent)->addrAddress = addrAddress;
	(*g_pInvalidPointCurrent)->pNext = NULL;
	g_pInvalidPointCurrent = &((*g_pInvalidPointCurrent)->pNext);
	g_iInvalidPointCount++;
}

#endif

/*
 * 用于分配与释放内存
 */
__void *__INTERNAL_FUNC__ InternalAllocMemory(__integer iSize) {
	__void *pPoint = NULL;
	HANDLE hHeap = NULL;
	__dword dwOldProtect = 0;
	hHeap = GetProcessHeap();
	pPoint = (__void *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, iSize);
	if (pPoint)
		VirtualProtect(pPoint, iSize, PAGE_EXECUTE_READWRITE, (__dword *)&dwOldProtect);
	return pPoint;
}

__bool __INTERNAL_FUNC__ InternalFreeMemory(__void *pPoint) {
	__bool bRet = FALSE;
	HANDLE hHeap = NULL;
	hHeap = GetProcessHeap();
	bRet = HeapFree(hHeap, 0, pPoint);
	return bRet;
}

/* 
 * round to 16 bytes + alloc at minimum 16 bytes 
 */
#define __ROUND_SIZE__(size) ((16 >= __ROUND_UP__(size, 16)) ? 16 : __ROUND_UP__(size, 16))
__void * __INTERNAL_FUNC__ LogicMalloc(__char *szFileName, __integer iLine, __integer iSize) {
	__dword dwOldProtect = 0;
	__integer nSize = 0;
	__void * pPoint = NULL;

#if defined(_DEBUG)
		{
			__memory pTailSign = NULL;

			nSize = __ROUND_SIZE__(iSize + __HEAP_TAIL_SIGN_SIZE__);
			if (nSize < iSize)
				return NULL;

			// 检测堆溢出
			CheckHeapOverflow(szFileName, iLine);

			// 分配内存
			pPoint = (__void *)InternalAllocMemory(nSize);
			
			// 写入标志
			pTailSign = (__memory)pPoint + nSize - __HEAP_TAIL_SIGN_SIZE__;
			*(__dword *)pTailSign = __HEAP_TAIL_SIGN_1__;
			*(__dword *)(pTailSign + sizeof(__dword)) = __HEAP_TAIL_SIGN_2__;
			__LogicDebugOutput__("<Debug LogicMalloc>file = %s, line = %d, address = 0x%4X, size = 0x%4X\n", szFileName, iLine, (__address)pPoint, iSize);

			// 记录到链表
			(*g_pAllocCurrent) = (PDEBUG_ALLOC_ADDRESS)InternalAllocMemory(sizeof(DEBUG_ALLOC_ADDRESS));
			(*g_pAllocCurrent)->pFilePath = szFileName;
			(*g_pAllocCurrent)->iLine = iLine;
			(*g_pAllocCurrent)->addrAddress = (__address)pPoint;
			(*g_pAllocCurrent)->addrTailSign = (__address)pTailSign;
			(*g_pAllocCurrent)->iSize = nSize;
			(*g_pAllocCurrent)->pNext = NULL;
			g_pAllocCurrent = &((*g_pAllocCurrent)->pNext);
			g_iAllocCount++;
		}
#else
	nSize = __ROUND_SIZE__(iSize);
	if (nSize < iSize)
		return NULL;
	pPoint = (__void *)InternalAllocMemory(nSize);
	if (pPoint) {
		VirtualProtect(pPoint, nSize, PAGE_EXECUTE_READWRITE, (__dword *)&dwOldProtect);
	}
#endif
	return pPoint;
}

__void __INTERNAL_FUNC__ LogicFree(__char *szFileName, __integer iLine, __void *pPoint) {
	if (pPoint) {
#if defined(_DEBUG)
		{
			__LogicDebugOutput__("<Debug LogicFree>file = %s, line = %d, address = 0x%4X\n", szFileName, iLine, (__address)pPoint);
			CheckHeapOverflow(szFileName, iLine);//检测堆溢出
			DebugFreeMemory(szFileName, iLine, (__address)pPoint);
		}
#else
		InternalFreeMemory(pPoint);
#endif
	}
}

__void * __INTERNAL_FUNC__ LogicMemcpy(__char *szFileName, __integer iLine, __void *pDest, __void *pSrc, __integer iCount) {
	__memory pCharDest = (__memory)pDest;
	__memory pCharSrc = (__memory)pSrc;

	if ((pCharDest <= pCharSrc) || (pCharDest >= (pCharSrc + iCount))) {
		/*
		 * non-overlapping buffers 
		 */
		while (iCount > 0) {
			*pCharDest = *pCharSrc;
			pCharDest++;
			pCharSrc++;
			iCount--;
		}
	} else {
		/* 
		 * overlaping buffers 
		 */
		pCharDest = (__memory)pDest + iCount - 1;
		pCharSrc = (__memory)pSrc + iCount - 1;

		while (iCount > 0) {
			*pCharDest = *pCharSrc;
			pCharDest--;
			pCharSrc--;
			iCount--;
		}
	}

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pDest);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicMemcpy>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X, size = 0x4X\n", \
									szFileName, \
									iLine, \
									pSrc, \
									pDest, \
									iCount);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pDest;
}

__void * __INTERNAL_FUNC__ LogicMemset(__char *szFileName, __integer iLine, __void *pSrc, __byte bVal, __integer iCount) {
	__memory pCharSrc = (__memory)pSrc;
	//__integer i = 0;
	//for (i = 0; i < iCount; i++) {
	//	*pCharSrc = bVal;
	//	pCharSrc++;
	//}

	while (iCount > 0) {
		*pCharSrc = bVal;
		pCharSrc++;
		iCount--;
	}

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pSrc);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicMemset>file = %s, line = %d, It's overflow, address = 0x%4X, size = 0x4X\n", \
									szFileName, \
									iLine, \
									pSrc, \
									iCount);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pSrc;
}

__sinteger __INTERNAL_FUNC__ LogicMemcmp(__void *pS1, __void *pS2, __integer iCount) {
	if (iCount) {
		__memory p1 = (__memory)pS1, p2 = (__memory)pS2;
		do {
			if (*p1++ != *p2++) {
				__byte bM1 = *--p1, bM2 = *--p2;
				return (__sinteger)(bM1 - bM2);
			}
		} while (--iCount != 0);
	}
	return 0;
}

__void * __INTERNAL_FUNC__ LogicMemmove(__char *szFileName, __integer iLine, __void *pDest, __void *pSrc, __integer iCount) {
	__memory pCharDest = (__memory)pDest;
	__memory pCharSrc = (__memory)pSrc;

	if ((pCharDest <= pCharSrc) || (pCharDest >= (pCharSrc + iCount))) {
		/* 
		 * non-overlapping buffers 
		 */
		while(iCount > 0) {
			*pCharDest = *pCharSrc;
			pCharDest++;
			pCharSrc++;
			iCount--;
		}
	} else {
		/* 
		 * overlaping buffers 
		 */
		pCharDest = (__memory)pDest + iCount - 1;
		pCharSrc = (__memory)pSrc + iCount - 1;

		while(iCount > 0) {
			*pCharDest = *pCharSrc;
			pCharDest--;
			pCharSrc--;
			iCount--;
		}
	}

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pDest);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicMemmove>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X, size = 0x4X\n", \
									szFileName, \
									iLine, \
									pSrc, \
									pDest, \
									iCount);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pDest;
}

__char * __INTERNAL_FUNC__ LogicStr2Lower(__char *pStr) {
	__char *s = NULL;

	if (!pStr) return 0;
	for(s = pStr; *s; s++) {
		*s = __logic_tolower__(*s);
	}
	return pStr;
}

__char * __INTERNAL_FUNC__ LogicStr2LowerN(__char *pStr, __integer iCount) {
	__char *s = NULL;
	__integer i = 0;

	if (!pStr) return 0;
	for(s = pStr; i < iCount; s++, i++) {
		*s = __logic_tolower__(*s);
	}
	return pStr;
}

__integer __INTERNAL_FUNC__ LogicStrlen(__char *pStr) {
	__char *s = NULL;

	if (!pStr) return 0;
	for(s = pStr; *s; ++ s);
	return s - pStr;
}

__sinteger __INTERNAL_FUNC__ LogicStrcmp(__char *pStr1, __char *pStr2) {
	while(*pStr1 == *pStr2) {
		if (*pStr1 == 0) return 0;

		pStr1++;
		pStr2++;
	}

	return (__sinteger)(*pStr1 - *pStr2);
}

__sinteger __INTERNAL_FUNC__ LogicStrncmp(__char *pStr1, __char *pStr2, __integer iCount) {
	if (iCount == 0) return 0;

	do {
		if (*pStr1 != *pStr2 ++) return (__sinteger)(*pStr1 - *-- pStr2);
		if (*pStr1 ++ == 0) break;
	} while (--iCount != 0);

	return 0;
}

__char * __INTERNAL_FUNC__ LogicStrstr(__char *pStr, __char *pFind) {
	__char c, sc;
	__integer iLen = 0;

	if ((c = *pFind++) != 0) {
		iLen = LogicStrlen(pFind);
		do {
			do {
				if ((sc = *pStr++) == 0)
					return NULL;
			} while (sc != c);
		} while (LogicStrncmp(pStr, pFind, iLen) != 0);
		pStr--;
	}
	return pStr;
}

__char * __INTERNAL_FUNC__ LogicStrstrInMemory(__char *pStr, __char *pFind, __integer iMemLen) {
	__char c, sc;
	__integer iLen = 0, iCount = 0;

	if ((c = *pFind++) != 0) {
		iLen = LogicStrlen(pFind);
		do {
			do {
				if (iCount == iMemLen)
					return NULL;
				else
					sc = *pStr++;
				iCount++;
			} while (sc != c);
		} while (LogicStrncmp(pStr, pFind, iLen) != 0);
		pStr--;
	}
	return pStr;
}

__char * __INTERNAL_FUNC__ LogicStrcpy(__char *szFileName, __integer iLine, __char *pTo, __char* pFrom) {
	__char *pSave = pTo;
	for (; (*pTo = *pFrom); ++pFrom, ++pTo);

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pTo);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicStrcpy>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X\n", \
									szFileName, \
									iLine, \
									pFrom, \
									pTo);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pSave;
}

__char * __INTERNAL_FUNC__ LogicStrncpy(__char *szFileName, __integer iLine, __char *pDest, __char *pSrc, __integer iCount) {
	__integer iOrigCount = 0;
	iOrigCount = iCount;
	if (iCount != 0) {
		__char *d = pDest;
		__char *s = pSrc;

		do {
			if((*d ++ = *s ++) == 0) {
				while (--iCount != 0) *d ++ = 0;
				break;
			}
		} while(--iCount != 0);
	}

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pDest);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicStrncpy>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X, size = 0x%4X\n", \
									szFileName, \
									iLine, \
									pSrc, \
									pDest, \
									iOrigCount);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pDest;
}

__char * __INTERNAL_FUNC__ LogicStrchr(__char *pSrc, __char c) {
	__char cc = c;

	while(*pSrc) {
		if (*pSrc == cc) return (__char *)pSrc;

		pSrc++;
	}

	if(cc == 0) return (__char *)pSrc;

	return 0;
}

__char * __INTERNAL_FUNC__ LogicStrrchr(__char *pSrc, __char c) {
	__char cc = c;
	__char *pSp = (__char *)0;

	while (*pSrc) {
		if(*pSrc == cc) pSp = pSrc;
		pSrc++;
	}

	if (cc == 0) pSp = pSrc;

	return (__char *)pSp;
}

__char * __INTERNAL_FUNC__ LogicStrcat(__char *pSrc, __char *pAppend) {
	__char *pSave = pSrc;
	for(; *pSrc; ++pSrc);

	while ((*pSrc++ = *pAppend++));

	return pSave;
}

__tchar * __INTERNAL_FUNC__ LogicStr2Tcs(__char *pStr, __tchar *pWStr) {
	__char *s = NULL;
	__tchar *t = NULL;

	s = pStr;
	t = pWStr;

	for (s = pStr, t = pWStr; *s; s++, t++) {
		*(__char *)t = *s;
		*(__char *)(t + 1) = '\0';
	}

	return pWStr;
}

__tchar * __INTERNAL_FUNC__ LogicStr2TcsN(__char *pStr, __tchar *pWStr, __integer iCount) {
	__char *s = NULL;
	__tchar *t = NULL;
	__integer i = 0;

	s = pStr;
	t = pWStr;

	for (s = pStr, t = pWStr, i = 0; i < iCount; s++, t++, i++) {
		*(__char *)t = *s;
		*(__char *)(t + 1) = '\0';
	}

	return pWStr;
}

__tchar * __INTERNAL_FUNC__ LogicTcs2Lower(__tchar *pStr) {
	__tchar *s = NULL;

	if (!pStr) return 0;
	for(s = pStr; *s; s++) {
		*(__char *)s = __logic_tolower__(*(__char *)s);
	}
	return pStr;
}

__tchar * __INTERNAL_FUNC__ LogicTcs2LowerN(__tchar *pStr, __integer iCount) {
	__tchar *s = NULL;
	__integer i = 0;

	if (!pStr) return 0;
	for(s = pStr; i < iCount; s++, i++) {
		*(__char *)s = __logic_tolower__(*(__char *)s);
	}
	return pStr;
}

__integer __INTERNAL_FUNC__ LogicTcslen(__tchar *pStr) {
	__tchar *s = NULL;

	if (!pStr) return 0;
	for(s = pStr; *s; ++ s);
	return s - pStr;
}

__sinteger __INTERNAL_FUNC__ LogicTcscmp(__tchar* pStr1, __tchar* pStr2) {
	while(*pStr1 == *pStr2) {
		if (*pStr1 == 0) return 0;

		pStr1++;
		pStr2++;
	}

	return (__sinteger)(*pStr1 - *pStr2);
}

__sinteger __INTERNAL_FUNC__ LogicTcsncmp(__tchar* pStr1, __tchar* pStr2, __integer iCount) {
	if (iCount == 0) return 0;

	do {
		if (*pStr1 != *pStr2 ++) return (__sinteger)(*pStr1 - *-- pStr2);
		if (*pStr1 ++ == 0) break;
	} while (--iCount != 0);

	return 0;
}

__tchar * __INTERNAL_FUNC__ LogicTcscpy(__char *szFileName, __integer iLine, __tchar *pTo, __tchar* pFrom) {
	__tchar *pSave = pTo;
	for (; (*pTo = *pFrom); ++pFrom, ++pTo);

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pTo);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicTcscpy>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X\n", \
									szFileName, \
									iLine, \
									pFrom, \
									pTo);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pSave;
}

__tchar * __INTERNAL_FUNC__ LogicTcsncpy(__char *szFileName, __integer iLine, __tchar *pDest, __tchar *pSrc, __integer iCount) {
	__integer iOrigCount = 0;
	iOrigCount = iCount;
	if (iCount != 0) {
		__tchar *d = pDest;
		__tchar *s = pSrc;

		do {
			if((*d ++ = *s ++) == 0) {
				while (--iCount != 0) *d ++ = 0;
				break;
			}
		} while(--iCount != 0);
	}

#if defined(_DEBUG)
	{
		// 这里开始检验
		PDEBUG_ALLOC_ADDRESS pDebugAllocAddress = NULL;
		pDebugAllocAddress = QueryDebugAllocAddress((__address)pDest);
		// 如果找到了则进行末尾验证
		if (pDebugAllocAddress) {
			__memory pTailSign = NULL;
			pTailSign = (__memory)(pDebugAllocAddress->addrTailSign);
			// 标志判断
			if ((*(__dword *)pTailSign != __HEAP_TAIL_SIGN_1__) || (*(__dword *)(pTailSign + sizeof(__dword)) != __HEAP_TAIL_SIGN_2__)) {
				__LogicDebugOutput__("<Debug LogicStrncpy>file = %s, line = %d, It's overflow, 0x%4X -> 0x%4X, size = 0x%4X\n", \
									szFileName, \
									iLine, \
									pSrc, \
									pDest, \
									iOrigCount);
				if (__BreakWhenHeapOverflow__())
					fgetc(stdin);
			}
		}
	}
#endif

	return pDest;
}

__tchar * __INTERNAL_FUNC__ LogicTcschr(__tchar *pSrc, __tchar c) {
	__tchar cc = c;

	while(*pSrc) {
		if (*pSrc == cc) return (__tchar *)pSrc;

		pSrc++;
	}

	if(cc == 0) return (__tchar *)pSrc;

	return 0;
}

__tchar * __INTERNAL_FUNC__ LogicTcsrchr(__tchar *pSrc, __tchar c) {
	__tchar cc = c;
	__tchar *pSp = (__tchar *)0;

	while (*pSrc) {
		if(*pSrc == cc) pSp = pSrc;
		pSrc++;
	}

	if (cc == 0) pSp = pSrc;

	return (__tchar *)pSp;
}

__tchar * __INTERNAL_FUNC__ LogicTcscat(__tchar *pSrc, __tchar *pAppend) {
	__tchar *pSave = pSrc;
	for(; *pSrc; ++pSrc);

	while ((*pSrc++ = *pAppend++));

	return pSave;
}

__char * __INTERNAL_FUNC__ LogicTcs2Str(__tchar *pWStr, __char *pStr) {
	__char *s = NULL;
	__tchar *t = NULL;

	s = pStr;
	t = pWStr;

	for (s = pStr, t = pWStr; *t; s++, t++) {
		*s = *(__char *)t;
	}

	return pStr;
}

__char * __INTERNAL_FUNC__ LogicTcs2StrN(__tchar *pWStr, __char *pStr, __integer iCount) {
	__char *s = NULL;
	__tchar *t = NULL;
	__integer i = 0;

	s = pStr;
	t = pWStr;

	for (s = pStr, t = pWStr, i = 0; i < iCount; s++, t++, i++) {
		*s = *(__char *)t;
	}

	return pStr;
}

#define __LOGIC_DIFFTIME__ 0x19DB1DED53E8000ULL
__INLINE__ __time __INTERNAL_FUNC__ LogicFileTimeToUnixTime(FILETIME *pFileTime, __word *pMillitm) {
	ULARGE_INTEGER ULargeInt;
	__time Time;

	ULargeInt.LowPart = pFileTime->dwLowDateTime;
	ULargeInt.HighPart = pFileTime->dwHighDateTime;
	ULargeInt.QuadPart -= __LOGIC_DIFFTIME__;

	Time = ULargeInt.QuadPart / 10000000;
	if (pMillitm)
		*pMillitm = (ULargeInt.QuadPart % 10000000) / 10000;

	return Time;
}

__time __INTERNAL_FUNC__ LogicTime(__time* pTime) {
	FILETIME SystemTime;
	__time Time = 0;
	GetSystemTimeAsFileTime(&SystemTime);
	Time = LogicFileTimeToUnixTime(&SystemTime, NULL);

	if (pTime)
		*pTime = Time;
	return Time;
}

__integer g_iSeed = 0;
__void __INTERNAL_FUNC__ LogicSrand(__integer iSeed) {
	g_iSeed = iSeed;
}

#define __RAND_MAX__		 0x7FFF
__integer __INTERNAL_FUNC__ LogicRand() {
	g_iSeed = g_iSeed * 0x5DEECE66DLL + 2531011;
	return (__integer)((g_iSeed >> 16) & RAND_MAX);
}
