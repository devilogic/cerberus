// xhooker.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <atlconv.h>

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <io.h>

#include "xdetours.h"

//#include "Support.cpp"

using namespace std;

XDETOURS_CONFIGURE_FILE g_xDetoursConfigure = {0};
HANDLE g_hFile = INVALID_HANDLE_VALUE;

TCHAR *GetConfigurePath(TCHAR *szConfigurePath) {
	TCHAR *p = NULL;
	DWORD dwConfigurePathSize = 0;
	dwConfigurePathSize = GetModuleFileName(NULL, szConfigurePath, MAX_PATH * sizeof(TCHAR));
	if (dwConfigurePathSize == 0) 
		return NULL;
	p = (TCHAR *)(_tcsrchr(szConfigurePath, _T('\\')) + 1);
	*p = _T('\0');//设置末尾为0
	_tcscat(szConfigurePath, __CONFIGURE_FILE_NAME__);

	return szConfigurePath;
}

void Usage() {
	printf("version:1.0 alpha\r\n");
	printf("http://www.xffffffff.org\r\n");
	printf("usage:xhooker [options]\r\n");
	printf("/read configure <filepath>\r\n");
	printf("\r\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szFilePath[MAX_PATH] = {0};
	CHAR line[1024] = {0};

	USES_CONVERSION; 

	// 处理命令行
	if (argc == 1) {
		Usage();
		goto _write;
	} else if (argc == 3) {
		// 读取
		if (_tcscmp(argv[1], _T("/r")) == 0) {
			LPBYTE pOrg = NULL;
			DWORD dwSize = 0, dwWritten = 0;
			PXDETOURS_CONFIGURE_FILE pConfigureFile = NULL;

			_tcscpy(szFilePath, argv[2]);
			g_hFile = CreateFile(szFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (g_hFile == INVALID_HANDLE_VALUE)
				return 0;
			dwSize = GetFileSize(g_hFile, NULL);
			pOrg = (LPBYTE)&g_xDetoursConfigure;
			if (ReadFile(g_hFile, pOrg, dwSize, &dwWritten, NULL))
				for(int i = 0; i < dwSize; i++)
					*(pOrg + i) ^= __XDETOURS_CONFIGURE_FILE_KEY__;

			// 要读取的配置文件
			pConfigureFile = (PXDETOURS_CONFIGURE_FILE)pOrg;

			printf("There are %d service libraries\r\n", pConfigureFile->Names.dwLibCount);
			for (UINT i = 0; i < pConfigureFile->Names.dwLibCount; i++) {
				_tprintf(_T("Service library name:%s\r\n"), pConfigureFile->Names.LibNames[i]);
				printf("\tTrampoline list name:%s\r\n", pConfigureFile->Info[i].TrampolineName);
				for (UINT j = 0; j < pConfigureFile->Info[i].dwProcCount; j++) {
					printf("\tHook procedure name:%s\r\n", pConfigureFile->Info[i].ProcNames[j]);
					printf("\tTarget procedure name:%s\r\n", pConfigureFile->Info[i].Targets[j].ProcName);
					printf("\tTarget procedure has %d arguments\r\n", pConfigureFile->Info[i].dwProcArgCount[j]);
					_tprintf(_T("\tTarget procedure in library:%s\r\n"), pConfigureFile->Info[i].Targets[j].LibName);
					printf("-----\r\n");
				}
			}
			CloseHandle(g_hFile);
		} else {
			goto _error;
		}

		return 0;
	}

	// 写入
_write:
	PXDETOURS_CONFIGURE pConfigure = NULL;
	PXDETOURS_LIB_CONFIGURE pLibConfigure = NULL;
	PXDETOURS_TARGET pTarget = NULL;
	
	//创建文件
	GetConfigurePath(szFilePath);
	g_hFile = CreateFile(szFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (g_hFile == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == 80)
		{
			g_hFile = CreateFile(szFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (g_hFile == INVALID_HANDLE_VALUE)
			{
				printf("[-] Create file is error: %d\r\n", GetLastError());
				goto _error;
			}
		}
		
	}

	// 输入XDETOURS_CONFIGURE结构
	printf("Service library count:");cin.getline(line, sizeof(line));
	pConfigure = &g_xDetoursConfigure.Names;
	pConfigure->dwLibCount = atoi(line);//有几个服务库
	for(int i = 0; i < pConfigure->dwLibCount; i++)
	{
		printf("Service library[%d]:", i);cin.getline(line, sizeof(line));
		_tcscpy(pConfigure->LibNames[i], A2W(line));

		// 配置XDETOURS_LIB_CONFIGURE
		pLibConfigure = &g_xDetoursConfigure.Info[i];

		// 输入trampoline数组的名称
		printf("\Trampoline list name:");cin.getline(line, sizeof(line));
		strcpy(pLibConfigure->TrampolineName, line);

		printf("\tHook procedure count:");cin.getline(line, sizeof(line));
		pLibConfigure->dwProcCount = atoi(line);

		// 输入要HOOK的函数名称
		for(int j = 0; j < pLibConfigure->dwProcCount; j++)
		{
			printf("\tHooker procedure[%d] Name:", j);cin.getline(line, sizeof(line));
			//ProcName;
			strcpy(pLibConfigure->ProcNames[j], line);
			//ProcArg
			printf("\tHooker procedure[%d] argument count:", j);cin.getline(line, sizeof(line));
			pLibConfigure->dwProcArgCount[j] = atoi(line);

			// XDETOURS_TARGET 
			pTarget = &g_xDetoursConfigure.Info[i].Targets[j];
			printf("\tTarget library[%d] name:", j);cin.getline(line, sizeof(line));
			_tcscpy(pTarget->LibName, A2W(line));
			printf("\tTarget procedure[%d] name:", j);cin.getline(line, sizeof(line));
			strcpy(pTarget->ProcName, line);
		}
	}/* end for */

	PBYTE pOrg = (PBYTE)&g_xDetoursConfigure;
	DWORD dwSize = sizeof(XDETOURS_CONFIGURE_FILE);
	DWORD dwWritten = 0;
	
	//加密
	for(UINT i = 0; i < dwSize; i++)
		*(pOrg + i) ^= __XDETOURS_CONFIGURE_FILE_KEY__;

	if (WriteFile(g_hFile, pOrg, dwSize, &dwWritten, NULL))
		printf("[+] The xdetours configure file generate success\r\n");
	else
		printf("[-] Write file error:%d\r\n", GetLastError());
	

	//关闭文件
	CloseHandle(g_hFile);

	return 0;

_error:
	printf("-_- Unhappy\r\n");
	return -1;
}
