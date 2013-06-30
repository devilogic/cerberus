// xdetours.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <vector>
using namespace std;

BOOL g_LoadIt = FALSE;

DWORD g_dwValidHandleCount = 0;
HANDLE g_hLibList[__MAX_DETOURS_LIB__] = {0};
DWORD g_dwLibProcList[__MAX_DETOURS_LIB__][__MAX_DETOURS_PROC__] = {0};
LPDWORD g_dwLibTrampoline[__MAX_DETOURS_LIB__] = {0};
DWORD g_dwTargetProcList[__MAX_DETOURS_LIB__][__MAX_DETOURS_PROC__] = {0};
PDETOUR_TRAMPOLINE g_pTrampoline[__MAX_DETOURS_LIB__][__MAX_DETOURS_PROC__] = {0};
HMODULE g_hModule = NULL;
PXDETOURS_CONFIGURE g_xDetoursConfigure = NULL;
PXDETOURS_LIB_CONFIGURE g_LibConfigureList = NULL;
TCHAR g_LibPath[MAX_PATH] = {0};

#if defined(_DEBUG)
#define __STR_LOG_FILE_NAME__					_T("C:\\xdetours.txt")
VOID __cdecl Log2File(LPSTR pBuffer, DWORD dwLength) {
	DWORD dwNumber = 0;
	DWORD dwWriteLength = 0;
	HANDLE hLogFile = NULL;

	hLogFile = CreateFile(__STR_LOG_FILE_NAME__, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hLogFile) {
		MessageBox(NULL, _T("Create Log File Invalid"), _T("FuckCmbc"), MB_OK);
		return;
	}

	// 设置到末尾
	SetFilePointer(hLogFile, 0, NULL, FILE_END);

	if (dwLength == 0)
		dwWriteLength = strlen((CHAR *)pBuffer);
	else
		dwWriteLength = dwLength;
	if (hLogFile == INVALID_HANDLE_VALUE)
		MessageBox(NULL, _T("Log File Handle Invalid"), _T("FuckCmbc"), MB_OK);
	else
		WriteFile(hLogFile, (LPVOID)pBuffer, dwWriteLength, &dwNumber, NULL);
	CloseHandle(hLogFile);
}

#define __Log2File__						Log2File
#else
#define __Log2File__
#endif

BYTE *MappingFile(TCHAR *lpszFile, UINT *piFileSize, BOOL bWrite, UINT iMaximumSizeHigh, UINT iMaximumSizeLow) {
	BYTE *pRet = NULL;
	UINT iFileSize = 0, iMapSize;
	HANDLE hFileMapping;

	__try
	{
		HANDLE hFile = CreateFile(lpszFile, (bWrite ? (GENERIC_READ | GENERIC_WRITE) : GENERIC_READ), bWrite ? 0 : FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
			return NULL;

		iFileSize = GetFileSize(hFile, NULL);

		if (piFileSize)
			*piFileSize = iFileSize;

		iMapSize = iMaximumSizeLow;

		// 如果低位为0则使用当前文件大小进行映射
		if (iMapSize == 0)
			iMapSize = iFileSize;

		hFileMapping = CreateFileMapping(hFile, NULL, (bWrite ? PAGE_READWRITE : PAGE_READONLY), iMaximumSizeHigh, iMapSize, NULL);
		CloseHandle(hFile);
		if (!hFileMapping)
			return NULL;

		pRet = (unsigned char *)MapViewOfFile(hFileMapping, (bWrite ? (FILE_MAP_WRITE | FILE_MAP_READ) : FILE_MAP_READ), 0, 0, 0);
		CloseHandle(hFileMapping);
		return pRet;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return NULL;
	}
}

BOOL UnMappingFile(BYTE *pBaseAddress) {
	__try
	{
		FlushViewOfFile(pBaseAddress, 0);
		return UnmapViewOfFile(pBaseAddress);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
}


BOOL xDetorusGlobalInit() {

	g_xDetoursConfigure = (PXDETOURS_CONFIGURE )GlobalAlloc(GPTR, sizeof(XDETOURS_CONFIGURE));
	if (!g_xDetoursConfigure) 
	{
		__Log2File__("g_xDetoursConfigure = (PXDETOURS_CONFIGURE )GlobalAlloc(GPTR, sizeof(XDETOURS_CONFIGURE)); failed\r\n", 0);
		return FALSE;
	}

	g_LibConfigureList = (PXDETOURS_LIB_CONFIGURE)GlobalAlloc(GPTR, sizeof(XDETOURS_LIB_CONFIGURE) * __MAX_DETOURS_LIB__);
	if (!g_LibConfigureList) {
		GlobalFree(g_xDetoursConfigure);
		__Log2File__("g_LibConfigureList = (PXDETOURS_LIB_CONFIGURE)GlobalAlloc(GPTR, sizeof(XDETOURS_LIB_CONFIGURE) * __MAX_DETOURS_LIB__); failed\r\n", 0);
		return FALSE;
	}

	return TRUE;
}

VOID xDetorusGlobalRelease() {

	if (g_xDetoursConfigure)
		GlobalFree(g_xDetoursConfigure);

	if (g_LibConfigureList) 
		GlobalFree(g_LibConfigureList);

	return;
}

BOOL xDetorusStart() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (UINT i = 0; i < g_dwValidHandleCount; i++) {
		for (UINT j = 0; j < g_LibConfigureList[i].dwProcCount; j++) {
			PDETOUR_TRAMPOLINE pTrampoline = NULL;
			DWORD dwRet = DetourAttachEx(&(PVOID&)g_dwTargetProcList[i][j], (PVOID)g_dwLibProcList[i][j], &pTrampoline, NULL, NULL);
			if (dwRet != NO_ERROR)
			{
				__Log2File__("DWORD dwRet = DetourAttachEx(&(PVOID&)g_dwTargetProcList[i][j], (PVOID)g_dwLibProcList[i][j], &pTrampoline, NULL, NULL); failed\r\n", 0);
				return FALSE;
			}
			else
			{
				g_pTrampoline[i][j] = pTrampoline;
			}
		}

		// 将Trampoline复制给对方
		memcpy_s(g_dwLibTrampoline[i], sizeof(PDETOUR_TRAMPOLINE) * g_LibConfigureList[i].dwProcCount, &g_pTrampoline[i], sizeof(PDETOUR_TRAMPOLINE) * g_LibConfigureList[i].dwProcCount);
	}

	DetourTransactionCommit();

	return TRUE;
}

VOID xDetorusEnd() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (UINT i = 0; i < g_dwValidHandleCount; i++) {
		for (UINT j = 0; j < g_LibConfigureList[i].dwProcCount; j++) {
			DetourDetach(&(PVOID&)g_dwTargetProcList[i][j], (PVOID)g_dwLibProcList[i][j]);
		}
	}

	DetourTransactionCommit();
}

BOOL LoadServiceLibrarys()
{
	TCHAR LibPath[MAX_PATH] = {0};
	UINT i = 0, j = 0;
	if (g_xDetoursConfigure->dwLibCount == 0)
		return FALSE;

	// 加载动态库
	g_dwValidHandleCount = 0;
	for (i = 0; i < g_xDetoursConfigure->dwLibCount; i++) {
		// 合成服务库路径
		_tcscpy_s(LibPath, g_LibPath);
		_tcscat_s(LibPath, g_xDetoursConfigure->LibNames[i]);

		g_hLibList[i] = GetModuleHandle(LibPath);
		if (g_hLibList[i] == NULL) g_hLibList[i] = LoadLibrary(LibPath);
		if (g_hLibList[i] == NULL) {
#if defined(_DEBUG)
			DWORD dwError = GetLastError();
			__Log2File__("g_hLibList[i] = LoadLibrary(LibPath); failed\r\n", 0);
#endif
			if (i == 0) return FALSE;
			i--;
		} 
		else g_dwValidHandleCount++;
	}

	if (g_dwValidHandleCount == 0) 
	{
		__Log2File__("if (g_dwValidHandleCount == 0)  failed\r\n", 0);
		return FALSE;
	}

	// 获取每个库的函数以及Trampoline数组地址
	for (i = 0; i < g_dwValidHandleCount; i++) {

		// 获取服务库的Trampoline数组地址
		g_dwLibTrampoline[i] = (LPDWORD)GetProcAddress((HMODULE)g_hLibList[i], g_LibConfigureList[i].TrampolineName);

		// 获取函数地址
		for (j = 0; j < g_LibConfigureList[i].dwProcCount; j++) {
			g_dwLibProcList[i][j] = (DWORD)GetProcAddress((HMODULE)g_hLibList[i], g_LibConfigureList[i].ProcNames[j]);

			// 加载目标库
			HANDLE hHandle = GetModuleHandle(g_LibConfigureList[i].Targets[j].LibName);
			if (hHandle == NULL) hHandle = LoadLibrary(g_LibConfigureList[i].Targets[j].LibName);
			if (hHandle == NULL) 
			{
				g_dwTargetProcList[i][j] = 0;
				__Log2File__("hHandle = LoadLibrary(g_LibConfigureList[i].Targets[j].LibName);  failed\r\n", 0);
			}
			else g_dwTargetProcList[i][j] = (DWORD)GetProcAddress((HMODULE)hHandle, g_LibConfigureList[i].Targets[j].ProcName);
		}
	}

	return TRUE;
}

BOOL ReadConfigure() {
	// 合成配置文件路径
	TCHAR szConfigurePath[MAX_PATH] = {0};
	TCHAR *p = NULL;
	DWORD dwConfigurePathSize = 0;
	dwConfigurePathSize = GetModuleFileName(g_hModule, szConfigurePath, MAX_PATH * sizeof(TCHAR));
	if (dwConfigurePathSize == 0) 
		return FALSE;
	p = (TCHAR *)(_tcsrchr(szConfigurePath, _T('\\')) + 1);
	*p = L'\0';//设置末尾为0

	_tcscpy_s(g_LibPath, szConfigurePath);
	_tcscat_s(szConfigurePath, __CONFIGURE_FILE_NAME__);

	// 从配置文件获取
	UINT iFileSize = 0;
	LPBYTE pMem = NULL, _in = NULL, _out = NULL;
	LPBYTE pDecode = NULL;

	pMem = MappingFile(szConfigurePath, &iFileSize, FALSE, 0, 0);
	if (!pMem) 
	{
		__Log2File__("pMem = MappingFile(szConfigurePath, &iFileSize, FALSE, 0, 0);  failed\r\n", 0);
		return FALSE;
	}

	pDecode = (LPBYTE)GlobalAlloc(GPTR, iFileSize + 0x10);
	if (!pDecode) {
		UnMappingFile(pMem);
		__Log2File__("pDecode = (LPBYTE)GlobalAlloc(GPTR, iFileSize + 0x10);  failed\r\n", 0);
		return FALSE;
	}

	_in = (LPBYTE)pMem;
	_out = (LPBYTE)pDecode;
	for (UINT i = 0; i < iFileSize; i++, _in++) {
		*(_out + i) = *_in ^ __XDETOURS_CONFIGURE_FILE_KEY__;
	}

	PXDETOURS_CONFIGURE_FILE pConfigureFile = (PXDETOURS_CONFIGURE_FILE)_out;
	memcpy_s(g_xDetoursConfigure, sizeof(XDETOURS_CONFIGURE), &(pConfigureFile->Names), sizeof(XDETOURS_CONFIGURE));
	memcpy_s(g_LibConfigureList, sizeof(XDETOURS_LIB_CONFIGURE) * __MAX_DETOURS_LIB__, &(pConfigureFile->Info), sizeof(XDETOURS_LIB_CONFIGURE) * __MAX_DETOURS_LIB__);

	return LoadServiceLibrarys();
}

VOID UnLoadLib()
{
	for (UINT i = 0; i < g_dwValidHandleCount; i++)
	{
		if (g_hLibList[i] != 0) FreeLibrary((HMODULE)g_hLibList[i]);
	}
	ZeroMemory(g_hLibList, sizeof(HANDLE) * __MAX_DETOURS_LIB__);
	g_dwValidHandleCount = 0;
}

BOOL xDetoursInit(HMODULE hModule) {
	__try
	{
		if (g_LoadIt == FALSE) {
			// 设置模块句柄
			g_hModule = hModule;
			SetDetourModule(hModule);

			// 分配内存
			if (xDetorusGlobalInit() == FALSE)
				return FALSE;

			// 读取配置文件
			if (ReadConfigure() == FALSE)
				return FALSE;

			// 开始进行HOOK
			if (xDetorusStart() == FALSE) {
				UnLoadLib();
				return FALSE;
			}
			g_LoadIt = TRUE;
#if defined(_DEBUG)
			MessageBox((HWND)hModule, _T("xdetours init success"), _T("xdetours"), MB_OK);
#endif
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#if defined(_DEBUG)
		MessageBox((HWND)hModule, _T("xdetours init except"), _T("xdetours"), MB_OK);
#endif
		return FALSE;
	}

	return TRUE;
}

VOID xDetoursRelease() {
	__try
	{
		xDetorusEnd();
		UnLoadLib();
		xDetorusGlobalRelease();
		g_LoadIt = FALSE;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return;
	}
}
