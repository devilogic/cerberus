//#define __CHAOSVM_DEBUG_STEP__				1
__void __INTERNAL_FUNC__ DISStep0(__dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 0
		pop eax
		int 3
	}
#endif
	return;
}

__dword __INTERNAL_FUNC__ DISStep1(__dword hModule, __dword ul_reason_for_call, __void *lpReserved) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 1
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep2(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 2
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep3(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, __dword *pOutMyDNA) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 3
		pop eax
		int 3
	}
#endif

	if (pOutMyDNA)
		*pOutMyDNA = __CHAOSVM_XFILE_DNA__;

	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep4(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 4
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep5(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 5
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep6(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 6
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep7(PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 7
		pop eax
		int 3
	}
#endif

	// 到这里就可以设置全局变量
	g_addrNowChaosVmImageBase = (__address)pDISImageBase;
	g_addrOrigChaosVmImageBase = addrDISOrigImageBase;
	g_addrOrigImageBase = pDISConfigure->addrOrigImageBase;
	g_iOrigSizeOfImage = pDISConfigure->iOrigSizeOfImage;
	g_iNowSizeOfImage = pDISConfigure->iNowSizeOfImage;
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep8() {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 8
		pop eax
		int 3
	}
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep9(__memory pTargetImageBase) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 9
		pop eax
		int 3
	}
#endif
	g_addrNowTargetImageBase = (__address)pTargetImageBase;
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep10() {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
		push eax
		mov eax, 10
		pop eax
		int 3
	}
#endif
	// 进入混乱虚拟机
#if defined(__CHAOSVM_MODE_INFECT__)
	ChaosVmEntry();
#endif
	return __DIS_ERROR_SUCCESS__;
}

__dword __INTERNAL_FUNC__ DISStep11(__address addrOrigEntryAddress) {
#if defined(__CHAOSVM_DEBUG_STEP__)
	__asm {
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
