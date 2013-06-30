#include <tchar.h>
#include "Support.h"
#include "lcrypto.h"

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.0\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:xsign [options] <filepath>\r\n");
	printf("[options]\r\n");
	printf("/code calc code crc32(cc)\r\n");
	printf("/code calc static code crc32(csc)\r\n");
}

__dword CalcCodeCrc32(__memory pMem) {
	__dword dwCodeCrc32 = 0;
	__memory pCode = NULL;
	__integer iCodeSize = 0;
	PIMAGE_SECTION_HEADER pEntrySection = NULL;
	
	pEntrySection = GetEntryPointSection(pMem);
	if (!pEntrySection)
		return 0;
	pCode = pMem + pEntrySection->PointerToRawData;
	iCodeSize = pEntrySection->Misc.VirtualSize;

	dwCodeCrc32 = crc32(pCode, iCodeSize);

	return dwCodeCrc32;
}

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	PIMAGE_SECTION_HEADER pCodeSection = NULL;
	__integer iIndex = 0;
	__bool bCalcCodeCrc32 = FALSE;
	__memory pMem = NULL;
	__tchar *pFilePath = NULL;

	if (iArgc != 3) {
		Usage();
		return -1;
	}

	// 处理命令行
	if (_tcscmp(pArgv[1], _T("/cc")) == 0) {
		bCalcCodeCrc32 = TRUE;
	} else {
		Usage();
		return -1;
	}
	pFilePath = pArgv[2];

	// 映射文件
	pMem = MappingFile(pFilePath, NULL, FALSE, 0, 0);
	if (!pMem) {
		printf("[-]Mapping target file failed\r\n");
		return -1;
	}

	// 计算代码节的CRC32值
	if (bCalcCodeCrc32) {
		__dword dwCodeCrc32 = 0;
		dwCodeCrc32 = CalcCodeCrc32(pMem);
		printf("Code crc32 = 0x%4X\r\n", dwCodeCrc32);
	}

	UnMappingFile(pMem);
	return 0;
}