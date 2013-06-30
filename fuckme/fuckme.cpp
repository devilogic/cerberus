// fuckme.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>

#include "CDK.h"

typedef VOID (__stdcall *FPFuckYou)();

__POWER_START__(foo)
int foo()
{

	__POWER_PROTECT__(foo)
		MessageBox(NULL, _T("xxx"), _T("yyy"), MB_OK);
	return 0;
}
__POWER_END__(foo)

__VMP_START__(main)
int _tmain(int argc, _TCHAR* argv[])
{

	__VMP_PROTECT__(main)

	HANDLE hModule = INVALID_HANDLE_VALUE;
	FPFuckYou pFuckYou = NULL;
	printf("hello world\r\n");
	hModule = LoadLibrary(_T("fuckyou.dll"));
	pFuckYou = (FPFuckYou)GetProcAddress((HMODULE)hModule, "FuckYou");
	pFuckYou();

	__asm {mov eax, fs:[0]}
	//__asm {pop fs:[0]}

	foo();
	return 0;
}
__VMP_END__(main)
