#include <stdlib.h>
#include <tchar.h>
#include "Support.h"

__integer g_iCount = 0;
__integer g_1MB = 0;
__integer g_3MB = 0;
__integer g_5MB = 0;
__integer g_10MB = 0;
__integer g_10PlusMB = 0;


__void __INTERNAL_FUNC__ Usage(__tchar *pName) {
	_tprintf(_T("%s dirpath 1|0\r\n"), pName);
}

__void __INTERNAL_FUNC__ SearchFileFullPath(__tchar *pStrPath, __bool bCheckSubDir)
{
	__tchar strTempString[MAX_PATH] = {0}; 
	__tchar strFullPath[MAX_PATH] = {0};
	__tchar strFile[MAX_PATH] = {0};
	WIN32_FIND_DATA wfd = {0};
	HANDLE hSearch = NULL;
	BOOL bResult = TRUE;
	//__integer iCount = 0;
	//__integer i1MB = 0;
	//__integer i3MB = 0;
	//__integer i5MB = 0;
	//__integer i10MB = 0;
	//__integer i10PlusMB = 0;

	__logic_tcscpy__(strFullPath, pStrPath);
	__logic_tcscpy__(strFile, strFullPath);
	__logic_tcscat__(strFile,  _T("\\*.*"));

	hSearch = FindFirstFile(strFile, &wfd);
	if (hSearch == INVALID_HANDLE_VALUE)
		return;

	while(bResult)
	{
		if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (bCheckSubDir)
				{
					if(wfd.cFileName[0] != '.')
					{
						__logic_tcscpy__(strTempString, strFullPath);
						__logic_tcscat__(strTempString, _T("\\"));
						__logic_tcscat__(strTempString, wfd.cFileName);
						SearchFileFullPath(strTempString, TRUE);
					}
				}
			}
			else 
			{
				// 获取文件大小
				__memory pMem = NULL;
				__dword dwFileSize = 0;
				__float fFileSize = 0;

				__logic_tcscpy__(strTempString, strFullPath);
				__logic_tcscat__(strTempString, _T("\\"));
				__logic_tcscat__(strTempString, wfd.cFileName);
				pMem = MappingFile(strTempString, &dwFileSize, FALSE, 0, 0);
				if (pMem == NULL) goto _next_file;
				if (IsValidPE32(pMem) == FALSE) goto _next_file;
				UnmapViewOfFile(pMem);
				
				fFileSize = (__float)dwFileSize;
				fFileSize /= 1024;		// 换成KB
				fFileSize /= 1024;		// 换成MB

				if (fFileSize < 10.0) {
					if (fFileSize < 5.0) {
						if (fFileSize < 3.0) {
							if (fFileSize < 1.0) {
								g_1MB++;
							} else {
								// 1 < x < 3
								g_3MB++;
							}
						} else {
							// 3 < x < 5
							g_5MB++;
						}
					} else {
						// 5 < x < 10
						g_10MB++;
					}
				} else {
					// 大于10MB
					g_10PlusMB++;
				}
				g_iCount++;
			}
		}
_next_file:
		bResult= FindNextFile(hSearch, &wfd);
	}
	FindClose(hSearch);
}

int _tmain(int argc, _TCHAR* argv[])
{	
	__tchar strDriverName[MAX_PATH];
	__bool bCheckSub = FALSE;

	if (argc != 3) {
		Usage(argv[0]);
		return -1;
	}

	if (argv[2][0] == _T('0'))
		bCheckSub = FALSE;
	else
		bCheckSub = TRUE;

	__logic_tcscpy__(strDriverName, argv[1]);
	if (strDriverName[__logic_tcslen__(strDriverName) - 1] == _T('\\'))
		strDriverName[__logic_tcslen__(strDriverName) - 1] = _T('\0');
	SearchFileFullPath(strDriverName, bCheckSub);
	
	_tprintf(_T("Directory:%s\r\n"), argv[1]);
	printf("Total PE file:%d\r\n", g_iCount);
	printf("----------------------------------------------------------\r\n");
	printf("<1MB:%d, %.2f%%\r\n", g_1MB, ((float)g_1MB / g_iCount) * 100);
	printf("<3MB:%d, %.2f%%\r\n", g_3MB, ((float)g_3MB / g_iCount) * 100);
	printf("<5MB:%d, %.2f%%\r\n", g_5MB, ((float)g_5MB / g_iCount) * 100);
	printf("<10MB:%d, %.2f%%\r\n", g_10MB, ((float)g_10MB / g_iCount) * 100);
	printf(">=10MB:%d, %.2f%%\r\n", g_10PlusMB, ((float)g_10PlusMB / g_iCount) * 100);
	printf("----------------------------------------------------------\r\n");

	return 0;
}

