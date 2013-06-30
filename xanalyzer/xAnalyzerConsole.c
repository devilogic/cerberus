#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include "Common.h"
#include "Support.h"

// 子功能模块
#include "PeView.h"
#include "Dump.h"
#include "Disasm.h"
#include "Analyze.h"
#include "Monitor.h"
#include "Setting.h"

#define __RESULT_DIR_PREFIX__				_T("results_")

#define __PEVIEW_OUTPUT_FILE_NAME__			_T("peview_result.xml")
#define __DUMP_OUTPUT_FILE_NAME__			_T("dump_result.xml")
#define __DISASM_OUTPUT_FILE_NAME__			_T("disasm_result.xml")
#define __ANALYZE_OUTPUT_FILE_NAME__		_T("analyze_result.xml")
#define __MONITOR_OUTPUT_FILE_NAME__		_T("monitor_result.xml")

#define __SETTING_DOT_NAME__				_T("dot.exe")

typedef struct _XANALYZER_CONFIGURE {
	__tchar szResultDirPath[MAX_PATH];//输出结果文件

	/*
	 * 各种配置
	 */
	__bool bEnablePeView;//启用PE浏览器
	PEVIEW_CONFIGURE PeViewConfigure;//PE浏览器配置

	__bool bEnableDump;//启用转存配置
	DUMP_CONFIGURE DumpConfigure;//转存配置

	__bool bEnableDisasm;//启用反汇编
	DISASM_CONFIGURE DisAsmConfigure;//反汇编配置

	__bool bEnableAnalyze;//启用分析配置
	ANALYZE_CONFIGURE AnalyzeConfigure;//分析引擎配置

	__bool bEnableMonitor;//启用监视
	MONITOR_CONFIGURE MonitorConfigure;//监视器配置

	__bool bEnableSetting;//启用配置
} XANALYZER_CONFIGURE, *PXANALYZER_CONFIGURE;

__INLINE__ __tchar * __INTERNAL_FUNC__ GetTargetFileName(__tchar *pFileName, __tchar *pFilePath) {
	__tchar *p = NULL;

	_tcscpy(pFileName, pFilePath);
	p = _tcsrchr(pFileName, _T('.'));
	*p = _T('\0');

	p = _tcsrchr(pFileName, _T('\\')) + 1;

	return p;
}

__byte HexString2Byte(__char *szString) {
	__byte iRet = 0;
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

__address String2Address(__char *szAddress) {
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

// 全命令配置
__void __INTERNAL_FUNC__ Usage() {
	printf("version:1.6\n");
	printf("email:logic.yan@gmail.com\n");
	printf("usage:xanalyzer [options] <filepath>\n");
	printf("[options]\n");
	printf("-peview,-dump,-disasm,-analyze,-monitor,-setting\n");
	printf("\n");

	printf("[output options]\n");
	printf("\t/output <path>(out)\n");
	printf("\n");

	printf("-peview [peview options]\n");
	printf("[peview options]\n");
	printf("\t/print pe header(peh)\n");
	printf("\t/print section headers(pshs)\n");
	printf("\t/print export table(pet)\n");
	printf("\t/print import table(pit)\n");
	printf("\t/print resource table(prst)\n");
	//printf("\t/print debug table(pdt)\n");
	printf("\t/print relocate table(prlt)\n");
	printf("\n");

	printf("-dump [dump options]\n");
	printf("[dump options]\n");
	printf("\tdump memory <dec(length)>(dp)\n");
	printf("\tentry <dec(length)>(dpe)\n");
	printf("\n");

	printf("-disasm [disasm options]\n");
	printf("[disasm options]\n");
	printf("\tdissambler(dis)\n");
	printf("\tuse AT&T syntax(att)\n");
	printf("\n");

	printf("-analyze [analyze options]\n");
	printf("[analyze options]\n");
	printf("\t/check valid address level <1|2|3|4>(cval)\n");
	printf("\t\t1:user memory\n");
	printf("\t\t2:image memory\n");
	printf("\t\t3:section memory\n");
	printf("\t\t4:section memory that it can be executed\n");
	//printf("\t/enable discovery unknow zoon(eduz)\n");
	printf("\t/disable invalid opcode is data(dioid)\n");
	printf("\t/mix code size <size>(mcs),default size = 6 bytes\n");
	printf("\t/nop is not end(nine)\n");
	printf("\t/int3 is not end(iine)\n");
	printf("\t/zero is not end(zine)\n");
	printf("\t/import table reference(iatref)\n");
	printf("\t/assign entry point address <addr>(aepa)\n");

	// 流程图选项
	printf("\t/output flowchart(ofc)\n");
	printf("\n");

	printf("-monitor <target program> <analyze result file> [monitor options]\n");
	printf("[monitor options]\n");
	printf("\tmonitoring api(mapi) <api1,api2,...>\n");
	printf("\tmonitoring procedure(mproc) <proc1,proc2,...>\n");
	printf("\tmonitoring all procedure(maproc)\n");
	printf("\tmonitoring all api(maapi)\n");
	printf("\tmonitoring all call(macall)\n");

	printf("-setting [setting options]\n");
	printf("[setting options]\n");
	printf("\t/griphivz path <path>(gp)\n");
	printf("\t/xhook path <path>(xp)\n");

	printf("\n");
}

__integer __INTERNAL_FUNC__ HandleArguments(__integer iArgc, __tchar *pArgv[], PXANALYZER_CONFIGURE pxAnalyzeConfigure) {
	__integer iTarget = 0, i = 0;
	
	if (iArgc == 1) {
		Usage();
		return 0;
	}

	for (i = 1; i < iArgc - 1; i++) {
		__tchar *pCurrArgv = NULL;

		pCurrArgv = pArgv[i];

		if ((pCurrArgv[0] == _T('/')) || (pCurrArgv[0] == _T('-'))) {
			switch (pCurrArgv[1]) {
			case 'a':case 'A':{
				if (_tcsicmp(&pCurrArgv[1], _T("analyze")) == 0) {
					pxAnalyzeConfigure->bEnableAnalyze = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("att")) == 0) {
					pxAnalyzeConfigure->DisAsmConfigure.bATT = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("aepa")) == 0) {
					__char Ansi[128] = {0};

					i++;//指向下一个参数
					pCurrArgv = pArgv[i];

					// 转换到Ansic
					UnicodeToAnsi(pCurrArgv, _tcslen(pCurrArgv), Ansi, 128);
					pxAnalyzeConfigure->AnalyzeConfigure.addrFromHereStartAnalyze = String2Address(Ansi);
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'o':case 'O':{
				if (_tcsicmp(&pCurrArgv[1], _T("out")) == 0) {

					i++;//指向下一个参数
					pCurrArgv = pArgv[i];

					_tcscpy(pxAnalyzeConfigure->szResultDirPath, pCurrArgv);
					if (pxAnalyzeConfigure->szResultDirPath[_tcsclen(pxAnalyzeConfigure->szResultDirPath) - 1] != _T('\\'))
						_tcscat(pxAnalyzeConfigure->szResultDirPath, _T("\\"));
					_tcscat(pxAnalyzeConfigure->szResultDirPath, __RESULT_DIR_PREFIX__);
				} else if (_tcsicmp(&pCurrArgv[1], _T("ofc")) == 0) {
					g_bGenProcedureFlowChart = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'c':case 'C':{
				if (_tcsicmp(&pCurrArgv[1], _T("cval")) == 0) {
					__integer iLevel = 0;

					i++;//指向下一个参数
					pCurrArgv = pArgv[i];

					// 检查地址级别
					iLevel = _ttoi(pCurrArgv);

					pxAnalyzeConfigure->AnalyzeConfigure.ValidAddressLevel = (CHECK_VALID_ADDR_LEVEL)iLevel;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'e':case 'E':{
				if (_tcsicmp(&pCurrArgv[1], _T("eduz")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bEnableDiscoveryUnknowZoon = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'd':case 'D':{
				if (_tcsicmp(&pCurrArgv[1], _T("dump")) == 0) {
					pxAnalyzeConfigure->bEnableDump = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("disasm")) == 0) {
					pxAnalyzeConfigure->bEnableDisasm = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("dp")) == 0) { 
					pxAnalyzeConfigure->DumpConfigure.bDump = TRUE;
					i++;
					pCurrArgv = pArgv[i];
					pxAnalyzeConfigure->DumpConfigure.iDumpSize = _ttoi(pCurrArgv);
				} else if (_tcsicmp(&pCurrArgv[1], _T("dpe")) == 0) {
					pxAnalyzeConfigure->DumpConfigure.bEntry = TRUE;
					i++;
					pCurrArgv = pArgv[i];
					pxAnalyzeConfigure->DumpConfigure.iEntrySize = _ttoi(pCurrArgv);
				} else if (_tcsicmp(&pCurrArgv[1], _T("dis")) == 0) {
					pxAnalyzeConfigure->DisAsmConfigure.bDisAsm = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("dioid")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bDisInvalidOpcodeIsData = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 's':case 'S':{
				if (_tcsicmp(&pCurrArgv[1], _T("setting")) == 0) {
					pxAnalyzeConfigure->bEnableSetting = TRUE;
				}
			}break;
			case 'p':case 'P':{
				if (_tcsicmp(&pCurrArgv[1], _T("peview")) == 0) {
					pxAnalyzeConfigure->bEnablePeView = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("peh")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintPEHeader = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("pshs")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintSectionHeaders = TRUE; 
				} else if (_tcsicmp(&pCurrArgv[1], _T("pet")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintExportTable = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("pit")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintImportTable = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("pdt")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintDebugTable = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("prlt")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintRelocateTable = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("prst")) == 0) {
					pxAnalyzeConfigure->PeViewConfigure.bPrintResourceTable = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'g':case 'G':{
				if (_tcsicmp(&pCurrArgv[1], _T("gp")) == 0) {

					i++;// 指向下一个参数
					pCurrArgv = pArgv[i];

					_tcscpy(g_szGraphvizPath, pCurrArgv);
					if (g_szGraphvizPath[_tcsclen(g_szGraphvizPath) - 1] != _T('\\'))
						_tcscat(g_szGraphvizPath, _T("\\"));
					_tcscat(g_szGraphvizPath, __SETTING_DOT_NAME__);
				}
			}break;
			case 'm':case 'M':{
				if (_tcsicmp(&pCurrArgv[1], _T("mcs")) == 0) {
					__integer iMixCodeSize = 0;

					i++;// 指向下一个参数
					pCurrArgv = pArgv[i];

					// 检查地址级别
					iMixCodeSize = _ttoi(pCurrArgv);

					pxAnalyzeConfigure->AnalyzeConfigure.bCodeMixSize = (__byte)iMixCodeSize;
				} else if (_tcsicmp(&pCurrArgv[1], _T("monitor")) == 0) {
					pxAnalyzeConfigure->bEnableMonitor = TRUE;
				
					// 获取目标程序文件名
					i++;
					pCurrArgv = pArgv[i];
					_tcscpy(pxAnalyzeConfigure->MonitorConfigure.szProgramName, pCurrArgv);

					// 获取分析文件名称
					i++;
					pCurrArgv = pArgv[i];
					_tcscpy(pxAnalyzeConfigure->MonitorConfigure.szAnalyzeFileName, pCurrArgv);
				} else if (_tcsicmp(&pCurrArgv[1], _T("mapi")) == 0) {
					__char szAPI[0x20] = {0};
					__char szAPIs[1024] = {0};
					PIAT_MONITOR_ITEM pIatMonitor = NULL;

					i++;// 指向下一个参数
					pCurrArgv = pArgv[i];

					UnicodeToAnsi(pCurrArgv, _tcslen(pCurrArgv), szAPIs, 1024);

				} else if (_tcsicmp(&pCurrArgv[1], _T("mproc")) == 0) {
					__address addrAddress = 0;
					PPROC_MONITOR_ITEM pProcMonitor = NULL;
					__char szAddresses[1024] = {0};

					i++;// 指向下一个参数
					pCurrArgv = pArgv[i];

					UnicodeToAnsi(pCurrArgv, _tcslen(pCurrArgv), szAddresses, 1024);

				} else if (_tcsicmp(&pCurrArgv[1], _T("maproc")) == 0) {
					pxAnalyzeConfigure->MonitorConfigure.iProcMonitorCount = 0xFFFFFFFF;
				} else if (_tcsicmp(&pCurrArgv[1], _T("maapi")) == 0) {
					pxAnalyzeConfigure->MonitorConfigure.iIatMonitorCount = 0xFFFFFFFF;
				} else if (_tcsicmp(&pCurrArgv[1], _T("macall")) == 0) {
					pxAnalyzeConfigure->MonitorConfigure.bAllCall = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'n':case 'N':{
				if (_tcsicmp(&pCurrArgv[1], _T("nine")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bNopIsNotEnd = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'i':case 'I':{
				if (_tcsicmp(&pCurrArgv[1], _T("iine")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bInt3IsNotEnd = TRUE;
				} else if (_tcsicmp(&pCurrArgv[1], _T("iatref")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bEnableImportTableReference = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			case 'x':case 'X':{
				if (_tcsicmp(&pCurrArgv[1], _T("xp")) == 0) {

					i++;// 指向下一个参数
					pCurrArgv = pArgv[i];

					_tcscpy(g_szXHookPath, pCurrArgv);
					if (g_szXHookPath[_tcsclen(g_szXHookPath) - 1] != _T('\\'))
						_tcscat(g_szXHookPath, _T("\\"));
				}
			}break;
			case 'z':case 'Z':{
				if (_tcsicmp(&pCurrArgv[1], _T("zine")) == 0) {
					pxAnalyzeConfigure->AnalyzeConfigure.bZeroIsNotEnd = TRUE;
				} else {
					Usage();
					return 0;
				}
			}break;
			default:{
				Usage();
				return 0;
			}/* end default */
			}/* end switch */
		} else {
			Usage();
			return 0;
		}/* end else */
	}/* end for */

	iTarget = i;

	// 判断合成目录
	{
		__tchar *pResultDirPath = NULL, *pTargetName = NULL;
		__tchar szTargetName[MAX_PATH] = {0};

		// 获取目标程序名
		pTargetName = GetTargetFileName(szTargetName, pArgv[iTarget]);

		pResultDirPath = pxAnalyzeConfigure->szResultDirPath;
		if (_tcslen(pResultDirPath) != 0) {
			_tcscat(pxAnalyzeConfigure->szResultDirPath, pTargetName);
		} else {
			__tchar szLocalPath[MAX_PATH] = {0};

			GetLocalPath(NULL, szLocalPath);
			_tcscpy(pxAnalyzeConfigure->szResultDirPath, szLocalPath);
			_tcscat(pxAnalyzeConfigure->szResultDirPath, __RESULT_DIR_PREFIX__);
			_tcscat(pxAnalyzeConfigure->szResultDirPath, pTargetName);
		}

		// 如果目录不存在则创建
		CreateDirectory(pxAnalyzeConfigure->szResultDirPath, NULL);

		// 增加最后的分隔符
		_tcscat(pxAnalyzeConfigure->szResultDirPath, _T("\\"));
	}

	return iTarget;
}

XANALYZER_CONFIGURE g_xAnalyzeConfigure = {0};
__tchar g_szPeViewResultFilePath[MAX_PATH] = {0};
__tchar g_szDumpResultFilePath[MAX_PATH] = {0};
__tchar g_szDisAsmResultFilePath[MAX_PATH] = {0};
__tchar g_szAnalyzeResultFilePath[MAX_PATH] = {0};
__tchar g_szMonitorResultFilePath[MAX_PATH] = {0};

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	__integer iTarget = 0;
	__tchar *pTargetFilePath = NULL;
	XFILE_ATTACH_INFO Target = {0};

	// 默认设置
	ZeroMemory(&g_xAnalyzeConfigure, sizeof(XANALYZER_CONFIGURE));

	// 分析命令行
	iTarget = HandleArguments(iArgc, pArgv, &g_xAnalyzeConfigure);
	if (iTarget == 0)
		return -1;

	// 目标文件路径
	pTargetFilePath = pArgv[iTarget];

	// 合成各个选项的文件目录
	_stprintf(g_szPeViewResultFilePath, _T("%s%s"), g_xAnalyzeConfigure.szResultDirPath, __PEVIEW_OUTPUT_FILE_NAME__);
	_stprintf(g_szDumpResultFilePath, _T("%s%s"), g_xAnalyzeConfigure.szResultDirPath, __DUMP_OUTPUT_FILE_NAME__);
	_stprintf(g_szDisAsmResultFilePath, _T("%s%s"), g_xAnalyzeConfigure.szResultDirPath, __DISASM_OUTPUT_FILE_NAME__);
	_stprintf(g_szAnalyzeResultFilePath, _T("%s%s"), g_xAnalyzeConfigure.szResultDirPath, __ANALYZE_OUTPUT_FILE_NAME__);
	_stprintf(g_szMonitorResultFilePath, _T("%s%s"), g_xAnalyzeConfigure.szResultDirPath, __MONITOR_OUTPUT_FILE_NAME__);

	// 映射目标文件
	Target.szTargetFilePath = pTargetFilePath;
	if (!XFileAttachInfoInit(&Target)) {
		printf("[-]Mapping target file failed\r\n");
		return -1;
	}

	// 按照参数进行工作
	if (g_xAnalyzeConfigure.bEnablePeView) {
		if (!PeView(Target.pMem, g_szPeViewResultFilePath, &(g_xAnalyzeConfigure.PeViewConfigure))) {
			// 浏览PE结果失败
		}
	}

	if (g_xAnalyzeConfigure.bEnableDump) {
		g_xAnalyzeConfigure.DumpConfigure.iFileSize = Target.iFileSize;
		if (!Dump(Target.pMem, g_szDumpResultFilePath, &(g_xAnalyzeConfigure.DumpConfigure))) {
			// 转存失败
		}
	}

	if (g_xAnalyzeConfigure.bEnableDisasm) {
		if (!DisAsm(Target.pMem, g_szDisAsmResultFilePath, &(g_xAnalyzeConfigure.DisAsmConfigure))) {
			// 转存失败
		}
	}

	if (g_xAnalyzeConfigure.bEnableAnalyze) {
		if (!Analyze(&Target, g_xAnalyzeConfigure.szResultDirPath, g_szAnalyzeResultFilePath, &(g_xAnalyzeConfigure.AnalyzeConfigure))) {
			// 分析程序失败
		}
	}

	if (g_xAnalyzeConfigure.bEnableMonitor) {
		XFileReleaseXFileAttach(&Target);
		if (!Monitor(g_szMonitorResultFilePath, &(g_xAnalyzeConfigure.MonitorConfigure))) {
			// 监视程序失败
		}
	}

	_tprintf(_T("result in %s\n"), g_xAnalyzeConfigure.szResultDirPath);
	XFileReleaseXFileAttach(&Target);
	return 0;
}
