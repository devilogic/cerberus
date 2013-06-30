/*
 * 常量
 */
#define __SIZE_OF_PARAMETER_BLOCK__ 4096

/*
 * DLL链表
 */
typedef struct _DLL_LIST {
	__void *pImageBase;
	__tchar svName[MAX_PATH];
	__dword dwFlags;
	__integer iLockCount;
	struct _DLL_LIST *pNext;
} DLL_LIST, *PDLL_LIST;

/*
 * 全局变量
 */
PDLL_LIST g_pDLLHead = NULL;//用于储存DLL链表
CRITICAL_SECTION g_DLLCrit;//用于同步DLL的加载

//增加DLL引用
/*
 * 返回值:
 * 0:表示增加新的引用
 * 1:表示新的DLL加载
 * -1:表示出错
 */
__integer __INTERNAL_FUNC__ AddDLLReference(__memory pImageBase, __tchar *svName, __dword dwFlags) {
	PDLL_LIST pCur = NULL;
	EnterCriticalSection(&g_DLLCrit);

	// 寻找DLL在列表
	for(pCur = g_pDLLHead ; pCur != NULL; pCur = pCur->pNext) {
		if(pCur->pImageBase == pImageBase) 
			break;
	}

	if(pCur) {
		// 增加DLL引用
		pCur->iLockCount++;
		LeaveCriticalSection(&g_DLLCrit);
		return 0;
	}

	// 增加新的DLL插件到列表
	pCur = __logic_new__(DLL_LIST, 1);
	if(!pCur) {
		LeaveCriticalSection(&g_DLLCrit);
		return -1;
	}

	pCur->pImageBase = pImageBase;
	if(svName) {
		__logic_tcsncpy__(pCur->svName, svName, MAX_PATH);
	} else {
		pCur->svName[0] = _T('\0');
	}
	pCur->iLockCount = 1;
	pCur->dwFlags = dwFlags;
	pCur->pNext = g_pDLLHead;
	g_pDLLHead = pCur;

	LeaveCriticalSection(&g_DLLCrit);
	return 1;
}

__integer __INTERNAL_FUNC__ RemoveDLLReference(__memory pImageBase, __tchar *svName, __dword *pdwFlags) {
	PDLL_LIST pCurr = NULL, pPrev = NULL;
	EnterCriticalSection(&g_DLLCrit);

	// 查询DLL在列表
	for(pCurr = g_pDLLHead; pCurr != NULL; pCurr = pCurr->pNext) {
		if(pCurr->pImageBase == pImageBase) break;
		pPrev = pCurr;
	}
	if(!pCurr) {
		LeaveCriticalSection(&g_DLLCrit);
		return -1;
	}

	pCurr->iLockCount--;//减少DLL引用
	*pdwFlags = pCurr->dwFlags;//查询DLL信息
	__logic_tcsncpy__(svName, pCurr->svName, MAX_PATH);

	if (pCurr->iLockCount == 0) {//移除
		if(!pPrev) {
			g_pDLLHead = g_pDLLHead->pNext;
			__logic_delete__(pCurr);
		} else {
			pCurr->pNext = pCurr->pNext;
			__logic_delete__(pCurr);
		}

		LeaveCriticalSection(&g_DLLCrit);
		return 1;
	}

	LeaveCriticalSection(&g_DLLCrit);
	return 0;
}

__bool __INTERNAL_FUNC__ RunDLLMain(__memory pImageBase, __dword dwImageSize, __bool bDetach) {
	__bool bRet;
	FPDllMain pDllMain;
	PIMAGE_NT_HEADERS pNt = GetNtHeader(pImageBase);
	if ((pNt->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) return TRUE;
	pDllMain =(FPDllMain)__RvaToVa__(pImageBase, pNt->OptionalHeader.AddressOfEntryPoint);
	if (bDetach)
		bRet = pDllMain((HMODULE)pImageBase, DLL_PROCESS_DETACH, NULL);
	else
		bRet = pDllMain((HMODULE)pImageBase, DLL_PROCESS_ATTACH, NULL);

	return bRet;
}
