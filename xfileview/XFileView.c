#include "Support.h"
#include <stdio.h>
#include <tchar.h>

typedef struct _XFILEVIEW_CONFIGURE {
	__dword dwDNA;//查询指定的DNA是否存在
	__bool bPrintXFileHeader;//打印X文件头
} XFILEVIEW_CONFIGURE, *PXFILEVIEW_CONFIGURE;

/*
 * 参数:
 *	szAddress:16进制的字符串地址
 *
 * 介绍:
 *	将16进制的字符串转换成数字,形式为0xaabbccdd,如果形式不对则返回0xFFFFFFFF
 */

__integer __INTERNAL_FUNC__ HexString2Byte(__char *szString) {
	__integer iRet = 0;
	__char ch = 0;

	ch = tolower(szString[0]);
	if ((ch >= 'a' ) && (ch <= 'f'))
		iRet = (ch - 'a' + 0x0A) * 0x10;
	else
		iRet = (ch - '0') * 0x10;

	ch = tolower(szString[1]);
	if ((ch >= 'a' ) && (ch <= 'f'))
		iRet += (ch - 'a' + 0x0A);
	else
		iRet += (ch - '0');

	return iRet;
}

#define String2Dword		String2Address
__address __INTERNAL_FUNC__ String2Address(__char *szAddress) {
	__address addrAddress = 0;
	__char *p = NULL;
	__integer i = 0;
	__integer iLen = 0;
	__integer v0 = 0, v1 = 0, v2 = 0, v3 = 0;

	iLen = strlen(szAddress);
	if (iLen != 10)
		return 0xFFFFFFFF;

	// 验证
	if ((szAddress[0] != '0') || (szAddress[1] != 'x'))
		return 0xFFFFFFFF;

	p = &(szAddress[2]);

	for (i = 0; i < (iLen - 2); p+=2, i+=2) {
		switch (i) {
		case 0: {
			v0 = HexString2Byte(p);
			v0 = v0 * 0x1000000;
		} break;
		case 2: {
			v1 = HexString2Byte(p);
			v1 = v1 * 0x10000;
		} break;
		case 4: {
			v2 = HexString2Byte(p);
			v2 = v2 * 0x100;
		} break;
		case 6: {
			v3 = HexString2Byte(p);
		} break;
		}/* end switch */
	}

	addrAddress = (__address)(v0 + v1 + v2 + v3);

	return addrAddress;
}

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.0\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:xfileview [options] <filepath>\r\n");
	printf("[options]\r\n");
	printf("/xfile header\r\n");
	printf("/dna is exist <DNA>\r\n");
}

__bool __INTERNAL_FUNC__ HandleArguments(__integer iArgc, __tchar *pArgv[], __tchar *szTargetFilePath, PXFILEVIEW_CONFIGURE pXFileViewConfigure) {
	__integer i = 1;
	__dword dwDNA = 0;
	__bool bPrintXFileHeader = FALSE;

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
				__char szAddress[0x10] = {0};

				// 指针++
				i++;

				UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szAddress, 0x10);
				dwDNA = (__dword)String2Dword(szAddress);
			}break;
			case _T('x'):
			case _T('X'): {
				bPrintXFileHeader = TRUE;
			}break;
			default: {
				Usage();
				return FALSE;
			}}/* end switch */
		}  else {
			Usage();
			return FALSE;
		}/* end else */
	}/* end for */

	pXFileViewConfigure->dwDNA = dwDNA;
	pXFileViewConfigure->bPrintXFileHeader = bPrintXFileHeader;

	// 目标文件路径
	_tcscpy(szTargetFilePath, pArgv[i]);

	return TRUE;
}

__void __INTERNAL_FUNC__ PrintXSectionHeader(PXFILE_SECTION_HEADER pXFileSectionHeader) {
	printf("pXFileSectionHeader->szSectionName = %s\r\n", pXFileSectionHeader->szSectionName);
	printf("pXFileSectionHeader->dwDNA = 0x%4X\r\n", pXFileSectionHeader->dwDNA);
	printf("pXFileSectionHeader->dwPointerToRawData = 0x%4X\r\n", pXFileSectionHeader->dwPointerToRawData);
	printf("pXFileSectionHeader->dwOffsetByXFile = 0x%4X\r\n", pXFileSectionHeader->dwOffsetByXFile);
	printf("pXFileSectionHeader->dwSizeOfSection = 0x%4X\r\n", pXFileSectionHeader->dwSizeOfSection);
	printf("pXFileSectionHeader->dwVirtualAddress = 0x%4X\r\n", pXFileSectionHeader->dwVirtualAddress);
	printf("pXFileSectionHeader->ofMemImageBaseOffset = 0x%4X\r\n", pXFileSectionHeader->ofMemImageBaseOffset);
	printf("pXFileSectionHeader->dwCharacteristics = 0x%4X\r\n", pXFileSectionHeader->dwCharacteristics);
	printf("pXFileSectionHeader->dwCustomDataRVA = 0x%4X\r\n", pXFileSectionHeader->dwCustomDataRVA);
	printf("\r\n");
}

__void __INTERNAL_FUNC__ PrintXFileHeader(PXFILE_HEADER pXFileHeader) {
	printf("pXFileHeader->dwSign = 0x%4X\r\n", pXFileHeader->dwSign);
	printf("pXFileHeader->dwAlignment = 0x%4X\r\n", pXFileHeader->dwAlignment);
	printf("pXFileHeader->dwSectionNumber = 0x%4X\r\n", pXFileHeader->dwSectionNumber);
	printf("pXFileHeader->dwMaxSectionNumber = 0x%4X\r\n", pXFileHeader->dwMaxSectionNumber);
	printf("pXFileHeader->dwSizeOfAllHeaders = 0x%4X\r\n", pXFileHeader->dwSizeOfAllHeaders);
	printf("pXFileHeader->dwVersion = 0x%4X\r\n", pXFileHeader->dwVersion);
	printf("pXFileHeader->dwXFileNtSectionHdrFileOffset = 0x%4X\r\n", pXFileHeader->dwXFileNtSectionHdrFileOffset);
	printf("pXFileHeader->dwXFileNtSectionHdrMemoryOffset = 0x%4X\r\n", pXFileHeader->dwXFileNtSectionHdrMemoryOffset);
	printf("pXFileHeader->dwXFileSectionHdrFileOffset = 0x%4X\r\n", pXFileHeader->dwXFileSectionHdrFileOffset);
	printf("pXFileHeader->dwXFileSectionHdrMemoryOffset = 0x%4X\r\n", pXFileHeader->dwXFileSectionHdrMemoryOffset);
	printf("pXFileHeader->dwXFileSize = 0x%4X\r\n", pXFileHeader->dwXFileSize);
	printf("\r\n");
}

XFILEVIEW_CONFIGURE g_XFileViewConfigure = {0};
__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	XFILE_ATTACH_INFO XFileAttachInfo = {0};
	PXFILE_SECTION_HEADER pXFileSectionHeader = NULL, pFatherXFileSectionHeader = NULL;
	PXFILE_HEADER pXFileHeader = NULL;
	PIMAGE_SECTION_HEADER pXFileNtSectionHeader = NULL;
	__tchar szTargetFile[MAX_PATH];

	// 分析命令行并设置配置结构
	if (!HandleArguments(iArgc, pArgv, szTargetFile, &g_XFileViewConfigure))
		return -1;

	XFileAttachInfo.szTargetFilePath = szTargetFile;
	if (!XFileAttachInfoInit(&XFileAttachInfo)) {
		printf("[fatal error] Mapping target file failed\r\n");
		return -1;
	}

	// 检查当前文件是否拥有X文件
	pXFileNtSectionHeader = XFileExistXFileInPEFile(XFileAttachInfo.pMem);
	if (!pXFileNtSectionHeader) {
		printf("[fatal error] Target file is not has xfile\r\n");
		return -1;
	}

	// 获取X文件的具体位置
	pXFileHeader = (PXFILE_HEADER)(XFileAttachInfo.pMem + pXFileNtSectionHeader->PointerToRawData);

	// 打印X文件头
	if (g_XFileViewConfigure.bPrintXFileHeader) {
		printf("X File:\r\n");
		PrintXFileHeader(pXFileHeader);
	}

	// 释放要查询DNA
	if (g_XFileViewConfigure.dwDNA) {
		pXFileSectionHeader = XFileGetXFileSectionHeaderByDNA(XFileAttachInfo.pMem, pXFileHeader, g_XFileViewConfigure.dwDNA, TRUE, &pFatherXFileSectionHeader);
		if (pXFileSectionHeader) {
			// 打印此X节的信息
			printf("Query DNA X Section:\r\n");
			PrintXSectionHeader(pXFileSectionHeader);
		} else {
			printf("This XFile has not query DNA section\r\n");
		}
	}

	XFileReleaseXFileAttach(&XFileAttachInfo);

	return 0;
}
