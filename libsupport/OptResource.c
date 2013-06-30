#include "OptResource.h"

__bool __API__ DecompressFile(HMODULE hModule, __word wResourceID, __tchar *theResourceName, __tchar *theExName, __tchar *theType) {
	HRSRC aResourceH;
	HGLOBAL aResourceHGlobal;
	__memory aFilePtr = NULL;
	__integer aFileSize = 0;
	HANDLE hFileHandle;
	__tchar FileName[MAX_PATH];
	__dword dwNumWritten = 0;

	aResourceH = FindResource(hModule, MAKEINTRESOURCE(wResourceID), theType);
	if (!aResourceH)
		return FALSE;
	aResourceHGlobal = LoadResource(hModule, aResourceH);
	if (!aResourceHGlobal)
		return FALSE;
	aFileSize = SizeofResource(hModule, aResourceH);
	aFilePtr = (unsigned char *)LockResource(aResourceHGlobal);
	if (!aFilePtr)
		return FALSE;

	__logic_tcscpy__(FileName, theResourceName);
	__logic_tcscat__(FileName, _T("."));
	__logic_tcscat__(FileName, theExName);
	hFileHandle = CreateFile(FileName, FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFileHandle == INVALID_HANDLE_VALUE) {
		__dword dwErr = GetLastError();
		if ((ERROR_ALREADY_EXISTS == dwErr) || (32 == dwErr))
			return TRUE;
		return FALSE;
	}

	// –¥»Î
	WriteFile(hFileHandle, aFilePtr, aFileSize, &dwNumWritten, NULL);
	//while (aFileSize--)
	//{
	//	WriteFile(hFileHandle, aFilePtr, 1, &dwNumWritten, NULL);
	//	aFilePtr++;
	//}
	CloseHandle(hFileHandle);
	return TRUE;
}

__memory __API__ GetResourcePoint(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize) {
	HRSRC aResourceH;
	__memory aFilePtr = NULL;
	__integer aFileSize = 0;
	HGLOBAL aResourceHGlobal;

	aResourceH = FindResource(hModule, MAKEINTRESOURCE(wResourceID), theType);
	if (!aResourceH)
		return NULL;
	aResourceHGlobal = LoadResource(hModule, aResourceH);
	if (!aResourceHGlobal)
		return NULL;
	aFileSize = SizeofResource(hModule, aResourceH);
	aFilePtr = (unsigned char *)LockResource(aResourceHGlobal);
	if (!aFilePtr)
		return NULL;

	*piResourceSize = aFileSize;
	return (__memory)aFilePtr;
}

__memory __API__ MapResourceData(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize) {
	return MapResourceDataEx(hModule, wResourceID, theType, piResourceSize, 0);
}

__memory __API__ MapResourceDataEx(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize, __dword dwKey) {
	__memory pMap = NULL;
	__integer iResourceDataSize = 0;
	__memory pResourceData = GetResourcePoint(hModule, wResourceID, theType, &iResourceDataSize);
	if (!pResourceData)
		return NULL;

	pMap = (__memory)__logic_new_size__(iResourceDataSize);
	__logic_memcpy__(pMap, pResourceData, iResourceDataSize);
	if (dwKey != 0)
		XorArray(dwKey, pMap, pMap, iResourceDataSize);
	*piResourceSize = iResourceDataSize;
	return pMap;
}

__memory __API__ MapResourceDataPlusNewSize(__memory pMap, __integer iOldSize, __integer iNewPlusSize) {
	__integer iTotalSize = iOldSize + iNewPlusSize;
	__memory pNewMap = (__memory)__logic_new_size__(iTotalSize);
	if (!pNewMap)
		return NULL;
	__logic_memcpy__(pNewMap, pMap, iOldSize);
	__logic_delete__((__void *)pMap);
	return pNewMap;
}

__memory __API__ MapResourceDataSubNewSize(__memory pMap, __integer iOldSize, __integer iSubSize) {
	__integer iNewSize = iOldSize - iSubSize;
	__memory pNewMap = (__memory)__logic_new_size__(iNewSize);
	if (!pNewMap)
		return NULL;
	__logic_memcpy__(pNewMap, pMap, iNewSize);
	__logic_delete__((__void *)pMap);
	return pNewMap;
}

__void __API__ UnMapResourceData(__memory pMap) {
	if (pMap)__logic_delete__((__void *)pMap);
}

__bool __API__ UnMapResourceDataToFile(__tchar *pFilePath, __memory pMap, __integer iMapSize) {
	HANDLE hFileHandle;
	__dword dwNumWritten = 0;
	__memory aFilePtr = pMap;
	__integer aFileSize = iMapSize;

	hFileHandle = CreateFile(pFilePath, FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFileHandle == INVALID_HANDLE_VALUE) {
		__dword dwErr = GetLastError();
		if ((ERROR_ALREADY_EXISTS == dwErr) || (32 == dwErr))
			return TRUE;
		return FALSE;
	}

	// –¥»Î
	WriteFile(hFileHandle, aFilePtr, aFileSize, &dwNumWritten, NULL);
	//while (aFileSize--)
	//{
	//	WriteFile(hFileHandle, aFilePtr, 1, &dwNumWritten, NULL);
	//	aFilePtr++;
	//}
	CloseHandle(hFileHandle);
	return TRUE;
}
