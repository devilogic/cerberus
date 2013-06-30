#include <stdlib.h>
#include <tchar.h>
#include "lcrypto.h"
#include "Support.h"
#include "ChaosVmByteCodeFile.h"

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.0 alpha\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:cbcfileview [option] <filepath>\r\n");
	printf("[option]\r\n");
	printf("/print bytecode file header(pbfh)\r\n");
	printf("/print procedure crc32(ppc)\r\n");
}

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__memory pMem = NULL;
	__integer iMemSize = 0;
	PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile = NULL;
	__tchar *pTargetFile = NULL;

	if (iArgc != 3) {
		Usage();
		return -1;
	}

	pTargetFile = pArgv[2];

	pMem = MappingFile(pTargetFile, &iMemSize, FALSE, 0, 0);
	if (!pMem) {
		printf("Mapping target file failed\r\n");
		return -1;
	}

	pByteCodeFile = (PCHAOSVM_EMULATION_BYTECODE_FILE)pMem;

	if (_tcsicmp(pArgv[1], _T("/pbfh")) == 0) {
		printf("pByteCodeFile->dwSign = 0x%4X\r\n", pByteCodeFile->dwSign);
		printf("pByteCodeFile->dwProcedureCount = %d\r\n", pByteCodeFile->dwProcedureCount);
		printf("pByteCodeFile->dwSize = %d bytes\r\n", pByteCodeFile->dwSize);
		printf("pByteCodeFile->dwCrc32 = 0x%4X\r\n", pByteCodeFile->dwCrc32);
	} else if (_tcsicmp(pArgv[1], _T("/ppc")) == 0) {
		__integer i = 0;
		PCHAOSVM_EMULATION_BYTECODE_PROCEDURE pProcedure = NULL;
		__memory pProcedureCode = NULL;
		__integer iProcedureSize = 0;
		__dword dwCrc32 = 0;

		pProcedure = (PCHAOSVM_EMULATION_BYTECODE_PROCEDURE)((__memory)pByteCodeFile + sizeof(CHAOSVM_EMULATION_BYTECODE_FILE));
		for (i = 0; i < pByteCodeFile->dwProcedureCount; i++) {
			pProcedureCode = (__memory)pProcedure + sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE);
			iProcedureSize = pProcedure->dwSize - sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE);
			dwCrc32 = crc32(pProcedureCode, iProcedureSize);
			printf("Procedure[%d] size = %d bytes, attribute = %d, crc32 = 0x%4X\r\n", i, iProcedureSize, pProcedure->dwAttribute, dwCrc32);
			pProcedure = (PCHAOSVM_EMULATION_BYTECODE_PROCEDURE)((__memory)pProcedure + pProcedure->dwSize);
		}
	} else {
		Usage();
		return -1;
	}


	UnMappingFile(pMem);

	return 0;
}