// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

extern BOOL xDetoursInit(HMODULE hModule);
extern VOID xDetoursRelease();

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_THREAD_ATTACH:
	case DLL_PROCESS_ATTACH:
#if defined(_DEBUG)
		__asm int 3;
#endif
		if (xDetoursInit(hModule) == FALSE)
			return FALSE;
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		xDetoursRelease();
		break;
	}
	return TRUE;
}
