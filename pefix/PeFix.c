#include "Support.h"
#include <tchar.h>

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.1\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:pefix [options] <filepath>\r\n");
	printf("[options]\r\n");
	printf("/delete data directory <1,2,...>(ddd)\r\n");
	printf("/nx compatible clear\r\n");
	printf("/rand address mapping clear(ramc)\r\n");
	printf("/rand all section names(rasn)\r\n");
}

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__integer i = 1;
	__bool bWillDelDataDirectoryIndexs[0x10] = {0};
	__bool bCloseNX = FALSE;
	__bool bCloseRandAddressMap = FALSE;
	__bool bRandomAllSectionName = FALSE;
	__tchar *pTargetPath = NULL;

	// 命令行最小数
	if (iArgc == 1) {
		Usage();
		return FALSE;
	}

	// 处理命令行
	for (i = 1; i < (iArgc - 1); i++) {
		if (pArgv[i][0] == _T('/')) {
			switch (pArgv[i][1]) {
			case _T('d'):
			case _T('D'): {
				if (_tcsicmp(pArgv[i], _T("/ddd")) == 0) {
					// 要删除的数据目录
					__char seps[] = ",";
					__char *token = NULL;
					__char szString[2048] = {0};
					__integer iIndex = 0;

					// 指向参数
					i++;

					// 取出要删除的数据目录
					UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
					token = strtok(szString, seps);
					while (token) {
						iIndex = atoi(token);
						bWillDelDataDirectoryIndexs[iIndex] = TRUE;
						token = (__char *)strtok(NULL, seps);
					}/* end while */
				} else {
					Usage();
					return -1;
				}
			} break;
			case _T('n'):
			case _T('N'):{
				bCloseNX = TRUE;
			}break;
			case _T('r'):
			case _T('R'):{
				if (_tcsicmp(pArgv[i], _T("/ramc")) == 0) {
					bCloseRandAddressMap = TRUE;
				} else if (_tcsicmp(pArgv[i], _T("/rasn")) == 0) {
					bRandomAllSectionName = TRUE;
				}
			}break;
			}/* end switch */
		} else {
			Usage();
			return -1;
		}
	}/* end for */

	pTargetPath = pArgv[i];

	// 执行
	{
		__memory pMem = NULL;
		PIMAGE_NT_HEADERS pNtHdr = NULL;
		__integer n = 0;

		pMem = MappingFile(pTargetPath, NULL, TRUE, 0, 0);
		if (!pMem){
			goto _error;
		}
		pNtHdr = GetNtHeader(pMem);
		if (bCloseNX) pNtHdr->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_NX_COMPAT;//关闭DEP兼容
		if (bCloseRandAddressMap){if (!IsDllFile(pMem) && !(IsDriverFile(pMem))) pNtHdr->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;}//检查需要关闭随机地址化映射,如果是DLL则忽略此设置
		if (bRandomAllSectionName) RandomAllSectionName(pMem);
		for (n = 0; n < 0x10; n++)
			if (bWillDelDataDirectoryIndexs[n]) DeleteDataDirectoryObject(pMem, n);
		UnMappingFile(pMem);
		printf("^_^ Happy\r\n");
	}
	return 0;

_error:
	printf("-_- Unhappy\r\n");
}
