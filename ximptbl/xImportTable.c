#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include "resource.h"
#include "lcrypto.h"
#include "Support.h"
#include "DISAth.h"
#include "yImportTable.h"
#include "YImpTblKey.h"

// Y引入表保护解密密钥
#define __YIMPTBL_DECRYPT_KEY__									__EFILER_KEY__

//#define __TEST_DECRYPT_IMPORTTABLE__							1
//#define __TEST_DECRYPT_IMPORTTABLE_IN_DLL__					1
#define __DEF_XIMPORT_TABLE_SECTION_NAME__						"XIMPTBL"
#define __DEF_XIMPORT_TABLE_X_SECTION_NAME__					"XXIMPTBL"

// 测试调试命令
//(1) /ddd 6 /k /c /s test /n /ramc /rtl kernel32.dll /b

__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.0 alpha\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("usage:ximptbl [options] <filepath>\r\n");
	printf("[options]\r\n");
	printf("/delete data directory <1,2,...>(ddd)\r\n");										//保护完成后删除掉某个数据目录
	printf("/keep tail data\r\n");																//保持末尾数据
	printf("/checksum reset(cr)\r\n");															//重新计算校验和
	printf("/compatibility increase(ci)\r\n");													//提高兼容性
	printf("/section <name>\r\n");																//设定新节的节名
	printf("/nx compatible clear\r\n");															//数据执行保护兼容关闭
	printf("/rand address mapping clear(ramc)\r\n");											//随机地址化映射兼容关闭
	printf("/rand all section names(rasn)\r\n");												//随机所有节名
	printf("/remap target lib(rtl) <lib1,lib2,...>\r\n");										//重新映射目标文件的DLL
	printf("/remap dis lib(rdl) <lib1,lib2,...>\r\n");											//重新映射壳的DLL
	printf("/recall target dllmain(rtd) <lib1,lib2,...>\r\n");									//再次进入目标文件的重映射的DLL的dllmain
	printf("/recall dis dllmain(rdd) <lib1,lib2,...>\r\n");										//再次进入壳的重映射的DLL的dllmain
	printf("/protect target API(pta) <api1,api2,...>\r\n");										//要特别保护目标文件的API
	printf("/protect dis API(pda) <api1,api2,...>\r\n");										//要特别保护壳的API
	printf("/import table protect close(itpc)\r\n");											//关闭引入表保护
	printf("/import table keep same orig data(itksod)\r\n");									//保留一些原始引入表中的数据,提高兼容性	
	printf("/backup target file\r\n");															//备份原文件
	printf("/x <dispath>\r\n");																	//外部引入的DIS壳(yimptbl.dll)
	printf("\r\n");
	printf("Waiting Fixed:some features(rtl,rdl) is not stable in win vista above\r\n");
}

// xImpTbl配置结构
typedef struct _XIMPORT_TABLE_CONFIGURE {
	__bool bBackupOrigFile;//备份原文件
} XIMPORT_TABLE_CONFIGURE, *PXIMPORT_TABLE_CONFIGURE;

/*
 * 参数:
 *	iArgc:命令行个数
 *	pArgv:命令行参数
 *	pConfigure:混乱虚拟机附加器配置结构
 *	szTargetFilePath:目标文件路径
 *	pXImportTableConfigure:控制台配置结构
 *
 * 介绍:
 *	处理命令行
 */
__bool __INTERNAL_FUNC__ HandleArguments(__integer iArgc, __tchar *pArgv[], PDISATH_CONFIGURE pDisAthConfigure, PXIMPORT_TABLE_CONFIGURE pImportTableConfigure) {
	__integer i = 1;

	// 命令行最小数
	if (iArgc == 1) {
		Usage();
		return FALSE;
	}

	// 默认设置保护选项
	pDisAthConfigure->bProtectMyIAT = TRUE;
	pDisAthConfigure->bProtectTargetIAT = TRUE;

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
						pDisAthConfigure->XFileAttachInfo.bWillDelDataDirectoryIndexs[iIndex] = TRUE;
						token = (__char *)strtok(NULL, seps);
					}/* end while */
				} else {
					Usage();
					return FALSE;
				}
			} break;
			case _T('k'):
			case _T('K'): {
				if (pArgv[i][2] != _T('\0')) {
					Usage();
					return FALSE;
				}
				pDisAthConfigure->XFileAttachInfo.bKeepTailData = TRUE;
			} break;
			case _T('c'):
			case _T('C'): {
				if (_tcsicmp(pArgv[i], _T("/cr")) == 0) {
					pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
				} else if (_tcsicmp(pArgv[i], _T("/ci")) == 0) {
					pDisAthConfigure->XFileAttachInfo.bCompatibility = TRUE;
				} else {
					Usage();
					return FALSE;
				}
			} break;
			case _T('s'):
			case _T('S'): {
				// 指向参数
				pDisAthConfigure->XFileAttachInfo.szSectionName = (__char *)__logic_new_size__(0x10);
				i++;
				UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), pDisAthConfigure->XFileAttachInfo.szSectionName, 8);
			} break;
			case _T('b'):
			case _T('B'): {
				pImportTableConfigure->bBackupOrigFile = TRUE;
			} break;
			case _T('n'):
			case _T('N'): {
				pDisAthConfigure->XFileAttachInfo.bCloseNX = TRUE;
			} break;
			case _T('r'):
			case _T('R'): {
				__char seps[] = ",";
				__char *token = NULL;
				__char szString[2048] = {0};
				__integer iCount = 0;

				if (_tcsicmp(pArgv[i], _T("/ramc")) == 0) {
					pDisAthConfigure->XFileAttachInfo.bCloseRandAddressMap = TRUE;
				} else if (_tcsicmp(pArgv[i], _T("/rasn")) == 0) {
					pDisAthConfigure->XFileAttachInfo.bRandomAllSectionName = TRUE;
				} else if (_tcsicmp(pArgv[i], _T("/rtl")) == 0) {

					// 指向参数
					i++;

					UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
					token = strtok(szString, seps);
					while (token) {
						 pDisAthConfigure->dwTargetProtectDllCrc32List[iCount++] = crc32(token, strlen(token));
						token = (__char *)strtok(NULL, seps);
					}/* end while */
					pDisAthConfigure->iTargetProtectDllCrc32Count = iCount;

				} else if (_tcsicmp(pArgv[i], _T("/rdl")) == 0) {

					// 指向参数
					i++;

					UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
					token = strtok(szString, seps);
					while (token) {
						pDisAthConfigure->dwDISProtectDllCrc32List[iCount++] = crc32(token, strlen(token));
						token = (__char *)strtok(NULL, seps);
					}/* end while */
					pDisAthConfigure->iDISProtectDllCrc32Count = iCount;

				} else if (_tcsicmp(pArgv[i], _T("/rtd")) == 0) {

					// 指向参数
					i++;

					UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
					token = strtok(szString, seps);
					while (token) {
						pDisAthConfigure->dwTargetProtectDllCallDllMainCrc32List[iCount++] = crc32(token, strlen(token));
						token = (__char *)strtok(NULL, seps);
					}/* end while */
					pDisAthConfigure->iTargetProtectDllCallDllMainCrc32Count = iCount;

				} else if (_tcsicmp(pArgv[i], _T("/rdd")) == 0) {

					// 指向参数
					i++;

					UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
					token = strtok(szString, seps);
					while (token) {
						pDisAthConfigure->dwDISProtectDllCallDllMainCrc32List[iCount++] = crc32(token, strlen(token));
						token = (__char *)strtok(NULL, seps);
					}/* end while */
					pDisAthConfigure->iDISProtectDllCallDllMainCrc32Count = iCount;

				} else {
					Usage();
					return FALSE;
				}
			} break;
			case _T('p'):
			case _T('P'): {
				__char seps[] = ",";
				__char *token = NULL;
				__char szString[2048] = {0};
				__integer iCount = 0;
				__integer *pCountOut = NULL;
				__dword *pCrc32List = NULL;

				if (_tcsicmp(pArgv[i], _T("/pta")) == 0) {
					// 要特殊保护目标文件的API列表
					pCrc32List = (__dword *)&(pDisAthConfigure->dwTargetProtectApiCrc32List);
					pCountOut = (__integer *)&(pDisAthConfigure->iTargetProtectApiCrc32Count);
				} else if (_tcsicmp(pArgv[i], _T("/pda")) == 0) {
					// 要特殊保护壳的API列表
					pCrc32List = (__dword *)&(pDisAthConfigure->dwDISProtectApiCrc32List);
					pCountOut = (__integer *)&(pDisAthConfigure->iDISProtectApiCrc32Count);
				} else {
					Usage();
					return FALSE;
				}

				// 指向参数
				i++;

				// 取出要保护的API名称, 分析要设定的地址
				UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szString, 2048);
				token = strtok(szString, seps);
				while (token) {
					pCrc32List[iCount++] = crc32(token, strlen(token));
					token = (__char *)strtok(NULL, seps);
				}/* end while */
				*pCountOut = iCount;

			} break;
			case _T('i'):
			case _T('I'): {
				if (_tcsicmp(pArgv[i], _T("/itpc")) == 0) {
					pDisAthConfigure->bProtectMyIAT = FALSE;
					pDisAthConfigure->bProtectTargetIAT = FALSE;
				} else if (_tcsicmp(pArgv[i], _T("/itksod")) == 0) {
					pDisAthConfigure->XFileAttachInfo.bKeepSameOrigImpLib = TRUE;
				} else {
					Usage();
					return FALSE;
				}
			} break;
			default: {
				Usage();
				return FALSE;
			}}/* end switch */
		}  else {
			Usage();
			return FALSE;
		}/* end else */
	}/* end for */

	// 设定配置结构
	pDisAthConfigure->bIfXFileExistFailed = TRUE;//如果目标文件已经存在X文件则添加X文件失败
	pDisAthConfigure->szResourceType = (__tchar *)_T("BIN");
	pDisAthConfigure->dwDISResourceKey = __YIMPTBL_DECRYPT_KEY__;
	pDisAthConfigure->wResourceID = IDR_YIMPORTTABLE;
	pDisAthConfigure->XFileAttachInfo.bSetAllSectionCanWrite = TRUE;
	pDisAthConfigure->XFileAttachInfo.dwDNA = __Y_IMPORT_TABLE_DNA__;

	// PE节节名
	if (!pDisAthConfigure->XFileAttachInfo.szSectionName) {
		pDisAthConfigure->XFileAttachInfo.szSectionName = (__char *)__logic_new_size__(0x10);
		if (strlen(pDisAthConfigure->XFileAttachInfo.szSectionName) == 0)
			strcpy(pDisAthConfigure->XFileAttachInfo.szSectionName, __DEF_XIMPORT_TABLE_SECTION_NAME__);
	}

	// X节节名
	pDisAthConfigure->XFileAttachInfo.szXSectionName = (__char *)__logic_new_size__(0x10);
	strcpy(pDisAthConfigure->XFileAttachInfo.szXSectionName, __DEF_XIMPORT_TABLE_X_SECTION_NAME__);

	// 目标文件路径
	pDisAthConfigure->XFileAttachInfo.szTargetFilePath = pArgv[i];

	return TRUE;
}

DISATH_CONFIGURE g_DisAthConfigure = {0};
XIMPORT_TABLE_CONFIGURE g_xImportTableConfigure = {0};
__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__tchar szTargetFile[MAX_PATH] = {0};
	__dword dwRet = 0;

	// 分析命令行并设置配置结构
	if (!HandleArguments(iArgc, pArgv, &g_DisAthConfigure, &g_xImportTableConfigure))
		return -1;

	// 是否需要备份
	{
		__tchar szBackUpFilePath[MAX_PATH] = {0};
		_stprintf(szBackUpFilePath, _T("%s.bk"), g_DisAthConfigure.XFileAttachInfo.szTargetFilePath);
		if (g_xImportTableConfigure.bBackupOrigFile)
			CopyFile(g_DisAthConfigure.XFileAttachInfo.szTargetFilePath, szBackUpFilePath, FALSE);
	}

	// 附加
	dwRet = DISAthAttach(&g_DisAthConfigure);
	if (__DIS_SUCCESS__(dwRet)) {
		printf("^_^ happy now\r\n");
	} else {
		printf("-_- not happy\r\n");
	}

	// 测试DLL
#if defined(__TEST_DECRYPT_IMPORTTABLE_IN_DLL__)
	{
		HMODULE hTestDll = LoadLibrary((LPCTSTR)szTargetFile);
	}
#endif

	return 0;
}

__dword __INTERNAL_FUNC__ DISAthStep0(PDISATH_CONFIGURE pConfigure) {
	_tprintf(_T("Start protect %s import table\r\n"), pConfigure->XFileAttachInfo.szTargetFilePath);
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep1(PXFILE_ATTACH_INFO pXFileAttachInfo, PDISATH_CONFIGURE pConfigure) {
	printf("[+] Mapping target file success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep2(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_SECTION_HEADER pXFileNtSectionHeader) {
	printf("[+] Add X File to target success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep3(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader) {
	printf("[+] Get target NT header success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep4(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_SECTION_HEADER pNewXFileSection) {
	printf("[+] Predict new X section success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep5(PXFILE_ATTACH_INFO pXFileAttachInfo, __address addrDISImageBaseInTarget, __offset ofDISOffsetByXSectionBody) {
	printf("[+] Get DIS in target ImageBase success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep6(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize) {
	printf("[+] Mapping DIS success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep7(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize, __integer iDISSizeOfImage, __offset ofDISOffsetByXSectionBody, __integer *piXSectionSize) {
	printf("[+] Calc new X section size success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep8(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize, PIMAGE_SECTION_HEADER pXFileNtSectionHeader, PXFILE_SECTION_HEADER pXSection, __dword dwDNA, __offset ofDISConfigureRVA) {
	printf("[+] Add new X section success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep9(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader) {
	printf("[+] Reget target NT header success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep10(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __memory pDISInTarget, __integer iDISSizeOfImage) {
	printf("[+] Copy DIS to target on memory alignemtn success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep11(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, __offset ofDISNewAddressTableRva) {
	printf("Already encrypt DIS import table\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep12(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceDISImportTableAddress) {
	printf("[+] Encrypt DIS import table success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep13(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, __offset ofTargetNewAddressTableRva) {
	printf("Already encrypt target import table\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep14(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceTargetImportTableAddress) {
	printf("[+] Encrypt target import table success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep15(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure) {
	printf("Already modify target entry address\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep16(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader) {
	printf("[+] Modify target entry address success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}

#if defined(__TEST_DECRYPT_IMPORTTABLE__)
// 测试解密引入表
__void __INTERNAL_FUNC__ TestDecryptImportTable(PXFILE_ATTACH_INFO pXFileAttachInfo, PDIS_CONFIGURE pDISConfigure) {
	POWERDECRYPTIMPORTTABLE_ARG PowerDecryptTargetImportTableArg = {0};
	PIMPORT_PROTECT pTargetImportProtect = NULL;
	__memory pNew = pXFileAttachInfo->pMem;
	PIMAGE_NT_HEADERS pNtHdr = GetNtHeader(pNew); 
	__memory pTo = (__memory)VirtualAlloc((LPVOID)NULL, pNtHdr->OptionalHeader.SizeOfImage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// 重定位
	CopyMemToMemBySecAlign(pNew, pTo, pNtHdr->OptionalHeader.SizeOfImage);
	BaseRelocation(pTo, pNtHdr->OptionalHeader.ImageBase, (__address)pTo, FALSE);

	// 解密引入表
	pTargetImportProtect = &(pDISConfigure->TargetImportProtect);
	pTargetImportProtect->addrImageBase = (__address)pTo;

	// 修复目标程序的引入表
	PowerDecryptTargetImportTableArg.pImportProtect = pTargetImportProtect;
	PowerDecryptTargetImportTableArg.pAddThunkCodeStub = NULL;
	PowerDecryptImportTable(&PowerDecryptTargetImportTableArg);

	VirtualFree(pTo, pNtHdr->OptionalHeader.SizeOfImage, MEM_DECOMMIT);
	return;
}
#endif

__dword __INTERNAL_FUNC__ DISAthStep17(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure) {
	printf("[+] Modify target some PE infos success\r\n");
	
#if defined(__TEST_DECRYPT_IMPORTTABLE__)
	// 测试解密引入表
	InitImportProtecter();
	TestDecryptImportTable(pXFileAttachInfo, pDISConfigure);
#endif

	return __DISATH_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISAthStep18(PDISATH_CONFIGURE pConfigure) {
	printf("[+] Unmaping target success\r\n");
	return __DISATH_ERROR_SUCCESS__;
}
