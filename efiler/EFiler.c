#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>

#include "Common.h"
#include "lcrypto.h"
#include "Support.h"

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.1\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:efiler <password> <file> <macro name>\r\n");
}

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__char szPassword[1024] = {0};
	__integer iPsSize = 0;
	__tchar *szTargetPath = NULL;
	__integer iFileSize = 0;
	__dword dwCrc32 = 0;
	__memory pMem = NULL;
	__char szMacroName[1024] = {0};

	if (iArgc != 4) {
		Usage();
		return -1;
	}

	// 获取命令参数
	iPsSize = _tcslen(pArgv[1]);
	UnicodeToAnsi(pArgv[1], iPsSize, szPassword, 1024);
	szTargetPath = pArgv[2];

	dwCrc32 = crc32(szPassword, iPsSize);

	pMem = MappingFile(szTargetPath, &iFileSize, TRUE, 0, 0);
	if (!pMem) {
		goto _error;
	}

	XorArray(dwCrc32, pMem, pMem, iFileSize);

	UnMappingFile(pMem);

	// 输出.h文件
	{
		__memory pHFile = NULL;
		__char OutPut[128] = {0};
		pHFile = MappingFile(_T("efiler.h"), NULL, TRUE, 0, 1024);
		if (!pHFile) {
			goto _error;
		}
		
		UnicodeToAnsi(pArgv[3], _tcslen(pArgv[3]), szMacroName, 1024);
		sprintf(OutPut, "#define %s				0x%4X\r\n", szMacroName, dwCrc32);

		__logic_memcpy__(pHFile, OutPut, sizeof(OutPut));

		UnMappingFile(pHFile);
	}

	printf("^_^ Happy\r\n");

	return 0;

_error:
	printf("-_- Unhappy\r\n");
	return -1;
}
