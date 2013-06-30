#include "PowerProtecter.h"
#include "lcrypto.h"

/*
 * 要引出的全局变量
 */
__EXPORT__ __integer g_iPowerProtecterEncryptProcedures = 0;
__EXPORT__ PPOWER_PROTECTER_ENCRYPT_PROCEDURE g_pPowerProtecterEncryptProcedures = NULL;

/*
 * 自己使用的全局变量
 */
POWER_PROTECTER_INFO g_PowerProtecterInfo = {0};//力量保护器的信息
POWER_PROTECTER_CONFIGURE g_PowerProtecterConfigure = {0};//力量保护器的配置结构
CRITICAL_SECTION g_PowerProtecterCriticalSection = {0};//全局同步对象
__address g_addrInvokeProcAddress = 0;
__dword g_dwEFlag = 0;
__dword g_dwEAX, g_dwECX, g_dwEDX, g_dwEBX;
__dword g_dwESP, g_dwEBP, g_dwESI, g_dwEDI;
__address g_addrNowStackPointer = 0;

#define __POWER_PROTECTER_OFFSET_TO_INVOKE_INDEX_FIX__				0x04
#define __POWER_PROTECTER_OFFSET_TO_INVOKE_RANDNUMBER_FIX__			0x09
#define __POWER_PROTECTER_OFFSET_TO_INVOKE_RETADDR_FIX__			0x0E

/*
 * 参数:
 *	iIndex:被保护函数的索引
 *
 * 介绍:
 *	获取索引指定的力量加密函数结构
 */
__INLINE__ PPOWER_PROTECTER_ENCRYPT_PROCEDURE __INTERNAL_FUNC__ GetCurrEncryptProcedureStruct(__integer iIndex) {
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pRet = g_pPowerProtecterEncryptProcedures;
	__integer i = 0;
	if (iIndex >= g_iPowerProtecterEncryptProcedures) return NULL;
	for (i = 0; i < g_iPowerProtecterEncryptProcedures; i++) {
		if (i == iIndex) break;
		pRet = (PPOWER_PROTECTER_ENCRYPT_PROCEDURE)((__memory)pRet + pRet->iTotalSize);
	}
	return pRet;
}

/*
 * 参数:
 *	iIndex:加密函数的索引
 *	pPowerProtecterRunContext:用来记录当前的寄存器状况
 *
 * 介绍:
 *	这里负责进行切栈,分配空间等重要操作,此函数是被保护调用后的入口
 */
typedef __void (__API__ *FPPowerProtecterSetupLocalHandler)(__integer iIndex, PPOWER_PROTECTER_RUN_CONTEXT pPowerProtecterRunContext);
__void __API__ PowerProtecterSetupLocalHandler(__integer iIndex, PPOWER_PROTECTER_RUN_CONTEXT pPowerProtecterRunContext) {
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure = NULL;
	__memory pNewStack = NULL;
	__memory pNewEsp = NULL;
	__memory pEncryptProcedureBuffer = NULL;
	__dword dwRetAddress = 0;
	__dword *pStackPoint = NULL;
	__integer i = 0;

	// 获取自身的加密函数体
	pEncryptProcedure = GetCurrEncryptProcedureStruct(iIndex);

	// 是否初始化了
	if (!(pEncryptProcedure->bInit)) {
		InitializeCriticalSection(&(pEncryptProcedure->LocalCriticalSection));
		pEncryptProcedure->bInit = TRUE;
	}

	EnterCriticalSection(&(pEncryptProcedure->LocalCriticalSection));
	// 检验是否是头一次进入此,如果是头一次则分配运行内存,并进行解密
	if (pEncryptProcedure->iHandleCount == 0) {
		__integer iDecryptSpaceSize = 0;
		__dword dwKeyX = 0;
		__dword dwKeyZ = 0;
		__dword dwKeyY = 0;
		__memory pKeyProcedure = NULL;
		__integer iKeyProcedureSize = 0;
		PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pInstructions = NULL;
		__integer iInstructionSize = 0;
		pEncryptProcedure->pRunSpace = (__memory)__logic_new_size__(pEncryptProcedure->iProcSize);
		pEncryptProcedureBuffer = (__memory)pEncryptProcedure + sizeof(POWER_PROTECTER_ENCRYPT_PROCEDURE);//此时是密体
		// 分配解密空间
		iDecryptSpaceSize = sizeof(POWER_PROTECTER_DECRYPT_PROCEDURE) + sizeof(POWER_PROTECTER_ENCRYPT_INSTRUCTION) * pEncryptProcedure->iEncryptInstCount;
		(__memory)(pEncryptProcedure->pDecryptProcedure) = __logic_new_size__(iDecryptSpaceSize);

		dwKeyZ = crc32(pEncryptProcedureBuffer, pEncryptProcedure->iProcSize);//通过自身密体产生KeyZ
		// 解密目标地址结构
		XorArray(dwKeyZ, \
				(__memory)&(pEncryptProcedure->KeyProcedure), \
				(__memory)&(pEncryptProcedure->pDecryptProcedure->KeyProcedure), \
				sizeof(POWER_PROTECTER_WATCH_RECORD));
		//// 解密函数真正的地址
		//XorArray(dwKeyZ, \
		//		(__memory)&(pEncryptProcedure->addrProcAddress), \
		//		(__memory)&(pEncryptProcedure->pDecryptProcedure->addrProcAddress), \
		//		sizeof(__address));

		// 设置密钥函数的正确的内存地址
		pEncryptProcedure->pDecryptProcedure->KeyProcedure.addrMemAddress = \
			pEncryptProcedure->pDecryptProcedure->KeyProcedure.ofMemRVA + g_PowerProtecterInfo.addrNowTargetImageBase;

		// 产生解密函数体的KeyY
		pKeyProcedure = (__memory)(pEncryptProcedure->pDecryptProcedure->KeyProcedure.addrMemAddress);
		iKeyProcedureSize = pEncryptProcedure->pDecryptProcedure->KeyProcedure.iSize;
		dwKeyY = crc32(pKeyProcedure, iKeyProcedureSize);
		// 解密函数体
		XorArray(dwKeyY, pEncryptProcedureBuffer, pEncryptProcedure->pRunSpace, pEncryptProcedure->iProcSize);
		// 产生密钥X
		dwKeyX = crc32(pEncryptProcedure->pRunSpace, pEncryptProcedure->iProcSize);
		// 解密指令结构
		pInstructions = (PPOWER_PROTECTER_ENCRYPT_INSTRUCTION)(pEncryptProcedureBuffer + pEncryptProcedure->iProcSize);
		iInstructionSize = sizeof(POWER_PROTECTER_ENCRYPT_INSTRUCTION) * pEncryptProcedure->iEncryptInstCount;
		XorArray(dwKeyX, \
				(__memory)pInstructions, \
				((__memory)(pEncryptProcedure->pDecryptProcedure) + sizeof(POWER_PROTECTER_DECRYPT_PROCEDURE)), \
				iInstructionSize);

		// 将加密指令结构中的地址设置为当前的基地址
		for (i = 0; i < pEncryptProcedure->iEncryptInstCount; i++) {
			// 设置当前指令的内存地址
			pInstructions->addMemAddress = pInstructions->ofMemRVA + g_PowerProtecterInfo.addrNowTargetImageBase;
			// 如果非流程指令
			if (pInstructions->JmpType != PPFT_NONE) 
				pInstructions->addrTargetMemAddress = pInstructions->ofTargetMemRVA + g_PowerProtecterInfo.addrNowTargetImageBase;
			// 如果有监视内存则设定监视内存当前的地址
			if (pInstructions->bIsWatched) {
				pInstructions->WatchRecord.addrMemAddress = pInstructions->WatchRecord.ofMemRVA + g_PowerProtecterInfo.addrNowTargetImageBase;
			}
			pInstructions++;
		}

		// 增加句柄技术
		pEncryptProcedure->iHandleCount++;
	}

	// 复制上下文结构
	//__logic_memcpy__((__memory)&(pEncryptProcedure->Context), (__memory)pPowerProtecterRunContext, sizeof(POWER_PROTECTER_RUN_CONTEXT));
	LeaveCriticalSection(&(pEncryptProcedure->LocalCriticalSection));

	// 这里保存信息到全局变量
	EnterCriticalSection(&g_PowerProtecterCriticalSection);
	g_dwEFlag = pPowerProtecterRunContext->dwEFlag;
	g_dwEAX = pPowerProtecterRunContext->EAX;
	g_dwECX = pPowerProtecterRunContext->ECX;
	g_dwEDX = pPowerProtecterRunContext->EDX;
	g_dwEBX = pPowerProtecterRunContext->EBX;
	g_dwESP = pPowerProtecterRunContext->ESP;
	g_dwEBP = pPowerProtecterRunContext->EBP;
	g_dwESI = pPowerProtecterRunContext->ESI;
	g_dwEDI = pPowerProtecterRunContext->EDI;
	g_addrInvokeProcAddress = (__address)(pEncryptProcedure->pRunSpace);//获取到原本的函数地址

	// 重要的切栈
	__asm {
		mov esp, g_dwESP								; 这条指令执行之后所有的局部变量将不可用
		push g_addrInvokeProcAddress					; 调用地址
		;;
		;; 恢复真正的运行环境
		;;
		push g_dwEFlag									; 标志寄存器
		push g_dwEAX
		push g_dwECX
		push g_dwEDX
		push g_dwEBX
		push g_dwESP
		push g_dwEBP
		push g_dwESI
		push g_dwEDI
	}
	// 释放同步对象
	LeaveCriticalSection(&g_PowerProtecterCriticalSection);

	__asm {
		popad
		popfd
		ret												; 跳入到函数执行,这里也回到函数最初调用
	}
}

// 调用头
//__NAKED__ __void __API__ LocalPowerProtecterInvoke() {
//	__asm {
//		;;
//		;; 在保护退出时,恢复到物理环境,堆栈将切换到此刻
//		;; 这时esp刚好指向调用保护函数的返回地址,直接ret即可返回
//		;;
//		pushad													;1
//		pushfd													;1
//		push esp												;1
//		push 0x19831210;这里要修改为被保护的函数索引			;5
//		push 0x19831210;随便压入一个值,用作平衡堆栈				;5
//		push 0x19831204;这里需要修改,SetupLocalPowerProtecter的内存地址
//		ret
//	}
//}
//__NAKED__ __void __API__ EndLocalPowerProtecterInvoke() {
//	if (IsDebuggerPresent() == TRUE)
//		ExitProcess(0);
//}

// 默认的调用头
#define __POWER_PROTECTER_DEF_INVOKE_STUB_SIZE__					19
__byte g_DefaultPowerProtecterInvokeStub[0x20] = {
	"\x60\x9C\x54\x68\x10\x12\x83\x19\x68\x10\x12\x83\x19\x68\x04\x12\x83\x19\xC3"
};
__bool __INTERNAL_FUNC__ PowerProtecterGenInvokeAlgorithm(__integer iIndex, __memory pProcAddress, __integer iProcSize, \
														FPPowerProtecterSetupLocalHandler pPowerProtecterSetupLocalHandler) {
	__memory pInvoke = NULL;
	__integer iInvokeSize = 0;

	//pInvoke = (__memory)LocalPowerProtecterInvoke;
	//iInvokeSize = (__integer)EndLocalPowerProtecterInvoke - (__integer)LocalPowerProtecterInvoke;
	pInvoke = (__memory)g_DefaultPowerProtecterInvokeStub;
	iInvokeSize = __POWER_PROTECTER_DEF_INVOKE_STUB_SIZE__;
	if (iInvokeSize > iProcSize) return FALSE;

	// 复制调用头,并设置偏移
	__logic_memcpy__(pProcAddress, pInvoke, iInvokeSize);
	*(__dword *)(pProcAddress + __POWER_PROTECTER_OFFSET_TO_INVOKE_INDEX_FIX__) = (__dword)iIndex;
	*(__dword *)(pProcAddress + __POWER_PROTECTER_OFFSET_TO_INVOKE_RANDNUMBER_FIX__) = (__dword)GenerateRandomNumber(); 
	*(__dword *)(pProcAddress + __POWER_PROTECTER_OFFSET_TO_INVOKE_RETADDR_FIX__) = (__dword)pPowerProtecterSetupLocalHandler;

	return TRUE;
}

/*
 * 参数:
 *	iIndex:被保护函数的索引
 *	pEncryptProcedure:加密函数的结构
 *
 * 介绍:
 *	产生函数的调用头
 */
__bool __INTERNAL_FUNC__ PowerProtecterGenInvoke(__integer iIndex, PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure) {
	__memory pProcAddress = NULL;
	__integer iProcSize = 0;
	__bool bRet = FALSE;
	
	pProcAddress = (__memory)(pEncryptProcedure->addrProcAddress);
	iProcSize = pEncryptProcedure->iProcSize;

	// 如果被保护函数长度小于调用头最小长度
	if (__POWER_PROTECTER_DEF_INVOKE_STUB_SIZE__ > iProcSize) return FALSE;

	bRet = PowerProtecterGenInvokeAlgorithm(iIndex, pProcAddress, iProcSize, PowerProtecterSetupLocalHandler);

	return bRet;
}

/*
 * 参数:
 *	pEncryptProcedure:被保护函数的结构
 *	addrInstAddress:指令的内存地址
 *
 * 介绍:
 *	确定指定的指令是否是被保护的指令
 */
__INLINE__ __bool __INTERNAL_FUNC__ IsProtectInstruction(PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure, __address addrInstAddress) {
	PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pEncryptInstructions = NULL;
	__integer iCount = 0;
	__integer i = 0;

	iCount = pEncryptProcedure->iEncryptInstCount;
	pEncryptInstructions = \
		(PPOWER_PROTECTER_ENCRYPT_INSTRUCTION)((__memory)pEncryptProcedure + sizeof(POWER_PROTECTER_ENCRYPT_PROCEDURE) + pEncryptProcedure->iProcSize);
	for (i = 0; i < iCount; i++) {
		if (addrInstAddress == pEncryptInstructions->addMemAddress)
			return TRUE;
		pEncryptInstructions++;//移动到下一条指令
	}

	return FALSE;
}

/*
 * 参数:
 *	addrExpAddress:异常触发的地址
 *
 * 介绍:
 *	寻找到指定的地址是在哪个被保护函数之内,如果找到则返回加密函数结构指针,否则返回NULL
 */
__INLINE__ PPOWER_PROTECTER_ENCRYPT_PROCEDURE __INTERNAL_FUNC__ FindEncryptProcedureByExpInstAddress(__address addrExpAddress) {
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure = NULL;
	__integer i = 0;

	pEncryptProcedure = g_pPowerProtecterEncryptProcedures;
	for (i = 0; i < g_iPowerProtecterEncryptProcedures; i++) {
		if ((addrExpAddress >= (__address)(pEncryptProcedure->pRunSpace)) && (addrExpAddress < (__address)(pEncryptProcedure->pRunSpace + pEncryptProcedure->iTotalSize)))
			return pEncryptProcedure;
		pEncryptProcedure = (PPOWER_PROTECTER_ENCRYPT_PROCEDURE)((__memory)pEncryptProcedure + pEncryptProcedure->iTotalSize);
	}
	return NULL;
}

/*
 * 参数:
 *	pEncryptProcedure:加密函数结构
 *	addrExpAddress:异常触发的地址
 *
 * 介绍:
 *	通过指定的内存地址,找到对应的加密指令结构
 */
__INLINE__ PPOWER_PROTECTER_ENCRYPT_INSTRUCTION __INTERNAL_FUNC__ FindEncryptInstructionByExpInstAddress(PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure, __address addrExpAddress) {
	PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pInstruction = NULL;
	PPOWER_PROTECTER_DECRYPT_PROCEDURE pDecryptProcedure = NULL;
	__address addrProcAddress = 0;
	__address addrRealAddress = 0;
	__integer i = 0;

	addrProcAddress = pEncryptProcedure->addrProcAddress;
	pDecryptProcedure = pEncryptProcedure->pDecryptProcedure;
	addrRealAddress = addrExpAddress - (__address)(pEncryptProcedure->pRunSpace) + addrProcAddress;
	pInstruction = (PPOWER_PROTECTER_ENCRYPT_INSTRUCTION)((__memory)(pDecryptProcedure) + sizeof(POWER_PROTECTER_DECRYPT_PROCEDURE));

	for (i = 0; i < pEncryptProcedure->iEncryptInstCount; i++) {
		if (addrRealAddress == pInstruction->addMemAddress)
			return pInstruction;
		pInstruction++;
	}
	return NULL;
}

#include "PowerProtecterTestEFlag.c"
/*
 * 参数:
 *	pExceptionInfo:异常结构
 *
 * 介绍:
 *	局部的异常保护,此函数是主要负责运行被保护函数的
 */
__integer __API__ LocalPowerProtecter(PEXCEPTION_POINTERS pExceptionInfo) {
	PEXCEPTION_RECORD pExceptionRecord = NULL;
	PCONTEXT pContextRecord = NULL;
	__address addrExceptAddress = 0;
	__address addrTargetAddress = 0;
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pEncryptProcedure = NULL;
	PPOWER_PROTECTER_ENCRYPT_INSTRUCTION pEncryptInstruction = NULL;
	__dword dwEFlags = 0;
	__integer iInstLen = 0;
	__bool bOut = FALSE;

	pExceptionRecord = pExceptionInfo->ExceptionRecord;
	pContextRecord = pExceptionInfo->ContextRecord;

	addrExceptAddress = (__address)(pExceptionRecord->ExceptionAddress);//获取异常地址

	/*
	 * 获取加密函数结构
	 * 通过异常的地址查找加密函数结构,如果为NULL,则表示此指令不是我们保护的
	 * 则返回__EXCEPTION_CONTINUE_SEARCH__继续寻找对应的异常处理
	 */
	pEncryptProcedure = FindEncryptProcedureByExpInstAddress(addrExceptAddress);
	if (!pEncryptProcedure) return __EXCEPTION_CONTINUE_SEARCH__;

	/*
	 * 查询此地址对应的解密指令结构
	 * 如果已经确定此指令是在我们的加密函数中,则找到对应的加密指令结构
	 * 如果没找到,则表明不是我们保护的指令,则返回__EXCEPTION_CONTINUE_SEARCH__继续寻找对应的异常处理
	 */
	pEncryptInstruction = FindEncryptInstructionByExpInstAddress(pEncryptProcedure, addrExceptAddress);
	if (!pEncryptInstruction) return __EXCEPTION_CONTINUE_SEARCH__;

	/*
	 * 判断此指令是什么类型
	 * 如果bOut = FALSE则表示不是一条流程指令,或者是一条指令,但是跳转的目标在保护函数范围内
	 */
	bOut = pEncryptInstruction->bOut;
	dwEFlags = pContextRecord->EFlags;
	switch (pEncryptInstruction->JmpType) {
	case PPFT_JO:{
		// 70
		if (PowerProtecter_Test_00(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JNO:{
		// 71
		if (PowerProtecter_Test_01(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JB:{
		// 72
		if (PowerProtecter_Test_02(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JAE:{
		// 73
		if (PowerProtecter_Test_03(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JZ:{
		// 74
		if (PowerProtecter_Test_04(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JNZ:{
		// 75
		if (PowerProtecter_Test_05(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JBE:{
		// 76
		if (PowerProtecter_Test_06(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JA:{
		// 77
		if (PowerProtecter_Test_07(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JS:{
		// 78
		if (PowerProtecter_Test_08(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JNS:{
		// 79
		if (PowerProtecter_Test_08(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JP:{
		// 7A
		if (PowerProtecter_Test_0A(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JNP:{
		// 7B
		if (PowerProtecter_Test_0B(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JL:{
		// 7C
		if (PowerProtecter_Test_0C(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JGE:{
		// 7D
		if (PowerProtecter_Test_0D(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JLE:{
		// 7E
		if (PowerProtecter_Test_0E(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JG:{
		// 7F
		if (PowerProtecter_Test_0F(dwEFlags)) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JCXZ:{
		// E3
		if (pContextRecord->Ecx == 0) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JECXZ:{
		// E3
		if (pContextRecord->Ecx == 0) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JRCXZ:{
		// E3
		if (pContextRecord->Ecx == 0) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_LOOPNE:{
		if ((0 != pContextRecord->Ecx) && (0 == __POWER_PROTECTER_CPU_EFLAG_GET__(dwEFlags, PP_ER_ZF))) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_LOOPE:{
		if ((0 != pContextRecord->Ecx) && (1 == __POWER_PROTECTER_CPU_EFLAG_GET__(dwEFlags, PP_ER_ZF))) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_LOOP:{
		if (0 != pContextRecord->Ecx) {
			addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		} else {
			addrTargetAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		}
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_JMP:{
		addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_CALL:{
		// 这里手动压入下一条指令的地址到堆栈
		__dword *pEsp = NULL;
		__address addrNextInstAddress = 0;
		addrNextInstAddress = addrExceptAddress + pEncryptInstruction->iInstLen;
		pEsp = (__dword *)(pContextRecord->Esp);
		pEsp--;//移动堆栈
		*pEsp = (__dword)addrNextInstAddress;
		pContextRecord->Esp = (__dword)pEsp;

		// 跳转到目标地址
		addrTargetAddress = pEncryptInstruction->addrTargetMemAddress;
		pContextRecord->Eip = addrTargetAddress;
	}break;
	case PPFT_RET:{
		__address *paddrCurrEsp = NULL;
		// 这里将返回地址修改为卸载本地保护的函数
		paddrCurrEsp = (__address *)(pContextRecord->Esp);
		addrTargetAddress = *paddrCurrEsp;
		pContextRecord->Eip = addrTargetAddress;

		// 这里做平衡堆栈操作
		(__address)paddrCurrEsp = (__address)paddrCurrEsp + sizeof(__address);
		(__address)paddrCurrEsp = (__address)paddrCurrEsp + pEncryptInstruction->iRetSize;
		(__address *)(pContextRecord->Esp) = paddrCurrEsp;
	}break;
	default:{
		__byte *pInstBuf = NULL;
		__integer iInstLen = 0;
		__memory pCurrInstPoint = NULL;
		__address addrContinueAddress = 0;
		iInstLen = pEncryptInstruction->iInstLen;
		pInstBuf = pEncryptInstruction->InstBuf;
		pCurrInstPoint = (__memory)addrExceptAddress;
		// 如果这条指令被监视
		if (pEncryptInstruction->bIsWatched) {
			__dword dwKey = 0;
			__address addrWatchAddress = 0;
			__integer iWatchSize = 0;
			addrWatchAddress = pEncryptInstruction->WatchRecord.addrMemAddress;
			iWatchSize = pEncryptInstruction->WatchRecord.iSize;
			dwKey = crc32((__memory)addrWatchAddress, iWatchSize);
			XorArray(dwKey, pInstBuf, pCurrInstPoint, iInstLen);
		} else {
			// 使用指定的Key进行解密
			__dword dwKey = 0;

			dwKey = pEncryptInstruction->dwKey;
			XorArray(dwKey, pInstBuf, pCurrInstPoint, iInstLen);
			__logic_memcpy__(pCurrInstPoint, pInstBuf, iInstLen);
		}
	}/* end default */
	}/* end switch */

	// 如果是跳转指令并跳向外边
	if (bOut) {
		// 这里为向外跳转的代码
		EnterCriticalSection(&(pEncryptProcedure->LocalCriticalSection));
		// 减少计数
		(pEncryptProcedure->iHandleCount)--;
		// 释放函数运行空间
		if (!(pEncryptProcedure->iHandleCount)) {
			// 释放当前函数运行空间
			__logic_delete__(pEncryptProcedure->pRunSpace);
			pEncryptProcedure->pRunSpace = NULL;
			// 释放解密结构解密结构
			__logic_delete__(pEncryptProcedure->pDecryptProcedure);
		}
		LeaveCriticalSection(&(pEncryptProcedure->LocalCriticalSection));
	}

	/*
	 * 返回__EXCEPTION_CONTINUE_EXECUTION__表明异常已经得到修复,继续运行
	 */
	return __EXCEPTION_CONTINUE_EXECUTION__;
}

/*
 * 参数:
 *	lpTopLevelExceptionFilter:异常结构
 *
 * 介绍:
 *	全局的异常保护,由SetUnhandledExceptionFilter设置的处理函数
 *	当前没有任何作用
 */
LONG __API__ GlobalPowerProtecter(PEXCEPTION_POINTERS pExceptionPointers) {
	return 0;
}

/*
 * 介绍:
 *	为每个解密函数产生调用头
 */
__void __INTERNAL_FUNC__ PowerProtecterGenInvokeStubs() {
	__integer i = 0;
	PPOWER_PROTECTER_ENCRYPT_PROCEDURE pCurrEncryptProcedure = NULL;

	pCurrEncryptProcedure = g_pPowerProtecterEncryptProcedures;
	for (i = 0; i < g_iPowerProtecterEncryptProcedures; i++) {
		// 设置正确的函数地址
		pCurrEncryptProcedure->addrProcAddress = pCurrEncryptProcedure->ofProcRVA + g_PowerProtecterInfo.addrNowTargetImageBase;
		PowerProtecterGenInvoke(i, pCurrEncryptProcedure);
		pCurrEncryptProcedure = (PPOWER_PROTECTER_ENCRYPT_PROCEDURE)((__memory)pCurrEncryptProcedure + pCurrEncryptProcedure->iTotalSize);
	}
}

/*
 * 参数:
 *	pConfigure:力量保护的配置结构
 *
 * 介绍:
 *	力量保护初始化
 */
__void __API__ PowerProtecterInit(PPOWER_PROTECTER_CONFIGURE pConfigure, PPOWER_PROTECTER_INFO pInfo) {
	__integer i = 0;

	// 复制信息
	__logic_memcpy__(&g_PowerProtecterConfigure, pConfigure, sizeof(POWER_PROTECTER_CONFIGURE));
	__logic_memcpy__(&g_PowerProtecterInfo, pInfo, sizeof(POWER_PROTECTER_INFO));

	// 以新的基地址获取加密函数所在内存地址
	g_pPowerProtecterEncryptProcedures = (PPOWER_PROTECTER_ENCRYPT_PROCEDURE)((__offset)g_pPowerProtecterEncryptProcedures + g_PowerProtecterInfo.addrNowTargetImageBase);

	// 初始化全局同步对象
	InitializeCriticalSection(&g_PowerProtecterCriticalSection);

	// 为每个被保护的函数,产生调用头
	PowerProtecterGenInvokeStubs();

	// 设置全局异常钩子
	SetUnhandledExceptionFilter(GlobalPowerProtecter);

	// 设置局部异常处理,没有这个被保护的函数执行不起来
	AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)LocalPowerProtecter);
}

// 向一个堆栈中压入一个4字节数据
//__INLINE__ __dword * __INTERNAL_FUNC__ PushDwordToStack(__dword *pEsp, __dword dwValue) {
//	__dword *pCurr = NULL;
//	pCurr = pEsp - 1;
//	*pCurr = dwValue;
//	return pCurr;
//}

