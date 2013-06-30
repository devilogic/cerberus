__bool __API__ DecompressFile(HMODULE hModule, __word wResourceID, __tchar *theResourceName, __tchar *theExName, __tchar *theType);
__memory __API__ GetResourcePoint(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize);
__memory __API__ MapResourceData(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize);
__memory __API__ MapResourceDataEx(HMODULE hModule, __word wResourceID, __tchar *theType, __integer *piResourceSize, __dword dwKey);
__memory __API__ MapResourceDataPlusNewSize(__memory pMap, __integer iOldSize, __integer iNewPlusSize);
__memory __API__ MapResourceDataSubNewSize(__memory pMap, __integer iOldSize, __integer iSubSize);
__void __API__ UnMapResourceData(__memory pMap);
__bool __API__ UnMapResourceDataToFile(__tchar *pFilePath, __memory pMap, __integer iMapSize);
