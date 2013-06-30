#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>

#include "Common.h"
#include "crc.h"

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.0\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:crc32er [string1,string2,...]\r\n");
}

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__char szString[2048] = {0};
	__dword dwCrc32 = 0;
	__tchar *tscString = NULL;


	if (iArgc < 2) {
		Usage();
		return -1;
	}

	// 转换字符为标准编码
	tscString = pArgv[1];
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, tscString, _tcslen(tscString), szString, 2048, 0L, 0L);

	{
		__char seps[] = ",";
		__char *token = NULL;
		__integer iCount = 0;

		token = strtok(szString, seps);
		while (token) {
			dwCrc32 = crc32(token, strlen(token));
			printf("0x%4X = crc32(%s)\r\n", dwCrc32, token);
			token = (__char *)strtok(NULL, seps);
			iCount++;
		}/* end while */
	}

	return 0;
}