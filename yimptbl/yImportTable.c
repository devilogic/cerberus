#include "yImportTable.h"
#include "DISKernel.h"
#include "Support.h"

//#define __DEBUG_Y_IMPORTTABLE__			1

/*
 * 引入变量
 */
__offset g_ofOrigEntry = 0;
IMPORT_PROTECT g_MyImportProtect = {0};

__void __INTERNAL_FUNC__ DISStep0(__dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 0
		pop eax
		int 3
	}
#endif
	return;
}

__dword __INTERNAL_FUNC__ DISStep1(__dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 1
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep2(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 2
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep3(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, __dword *pOutMyDNA) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 3
		pop eax
		int 3
	}
#endif

	// 设置应该返回的DNA
	if (pOutMyDNA)
		*pOutMyDNA = __Y_IMPORT_TABLE_DNA__;

	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep4(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 4
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep5(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 5
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep6(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 6
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep7(PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 7
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep8() {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 8
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep9(__memory pTargetImageBase) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 9
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep10() {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 10
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep11(__address addrOrigEntryAddress) {
#if defined(__DEBUG_Y_IMPORTTABLE__)
	__asm 
	{
		push eax
		mov eax, 11
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__memory __INTERNAL_FUNC__ DISAddThunkCodeStub(__address addrNowApiAddress) {
	return NULL;
}
