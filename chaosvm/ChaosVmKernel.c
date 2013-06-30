#include "ChaosVmKernel.h"
#include "ChaosVmCpuInternalHeader.h"
#include "ChaosVmCpuInstructionsOneByteGeneral.h"
#include "ChaosVmCpuInstructionsOneByteMov.h"
#include "ChaosVmCpuInstructionsOneByteBitwise.h"
#include "ChaosVmCpuInstructionsOneByteMath.h"
#include "ChaosVmCpuInstructionsOneByteExtension.h"
#include "ChaosVmCpuInstructionsOneByteString.h"
#include "ChaosVmCpuInstructionsOneByteSegment.h"//2012.2.8新增
#include "ChaosVmCpuInstructionsShift.h"
#include "ChaosVmCpuInstructionsTwoByteGeneral.h"
#include "ChaosVmCpuInstructionsTwoByteExtension.h"

#include "ChaosVmCpuDisasm.h"

/*
 * !注:以下文件顺序不得改动
 */
#include "ChaosVmCpuDataTypeConversion.c"
#include "ChaosVmCpuCalculateFinalAddress.c"
#include "ChaosVmCpuReadDataPart.c"
#include "ChaosVmCpuReadDispPart.c"
#include "ChaosVmCpuReadImm.c"
#include "ChaosVmCpuMemoryAccess.c"
#include "ChaosVmCpuArgsAnalyse.c"
#include "ChaosVmCpuInternalFunction.c"
#include "ChaosVmCpuEFlagContion.c"
#include "ChaosVmCpuInstructionsOneByteGeneral.c"
#include "ChaosVmCpuInstructionsOneByteMov.c"
#include "ChaosVmCpuInstructionsOneByteBitwise.c"
#include "ChaosVmCpuInstructionsOneByteMath.c"
#include "ChaosVmCpuInstructionsOneByteExtension.c"
#include "ChaosVmCpuInstructionsOneByteString.c"
#include "ChaosVmCpuInstructionsOneByteSegment.c"//2012.2.8新增
#include "ChaosVmCpuInstructionsShift.c"
#include "ChaosVmCpuInstructionsTwoByteGeneral.c"
#include "ChaosVmCpuInstructionsTwoByteExtension.c"
#include "ChaosVmCpuDisasm.c"

/*
 * 全局引出的变量
 */
#include "ChaosVmCpuGlobalExportVariable.c"

__void __INTERNAL_FUNC__ ChaosVmCpuInit(PCHAOSVM_CPU pCPU) {
	pCPU->bRepPrefixEnable = __REP_PREFIX_NULL__;
	pCPU->bDefaultAddressingMode = __CPU_ADDRESSING_MODE_32__;
	pCPU->bDefaultOperandType = __CPU_OPERAND_TYPE_32__;
	pCPU->bDefaultDataSegmentRegister = CHAOSVM_SR_DS;
}

__INLINE__ __void __INTERNAL_FUNC__ ChaosVmCpuPrepareForRun(PCHAOSVM_CPU pCPU) {
	pCPU->bAddressingMode = pCPU->bDefaultAddressingMode;
	pCPU->bOperandType = pCPU->bDefaultOperandType;
	pCPU->bDataSegmentRegister = pCPU->bDefaultDataSegmentRegister;
	pCPU->bRepPrefixEnable = __REP_PREFIX_NULL__;

	pCPU->bOpcodeLength = 0;
	pCPU->bOpcodeMaxLength = 0;
	pCPU->bIsInterruptOccur = FALSE;
	__CPU_INSTRUCTION_TYPE_SET__(pCPU, __INSTRUCTION_TYPE_NONE__);

#if defined(__USE_INSTRUCTION_INFORMATION__)
	pCPU->InstructionInfomation.AffectedRegister.bType = __CPU_INSTRUCTION_REG_TYPE_NONE__;
	pCPU->InstructionInfomation.bInstructionLength = 0;
	pCPU->InstructionInfomation.bIsHasDirectAddress = FALSE;
	pCPU->InstructionInfomation.wPrefix = 0;
	pCPU->InstructionInfomation.bPrefixLength = 0;
#endif

}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuHandleInterrupt(PCHAOSVM_CPU pCPU) {
	if (pCPU->pInterruptHandler)
		return pCPU->pInterruptHandler(pCPU, pCPU->pUserContext);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_INTERRRUPT_UNHANDLE__);
	return __CPU_STATUS_INTERRRUPT_UNHANDLE__;
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunToOffset(PCHAOSVM_CPU pCPU, __offset ofOffset) {
	CPU_STATUS Status = {0};
	__byte bInt8CodeByte = 0;
	__address addrStartAddress = 0;

	// 断点
	__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Entry ChaosVmCpuRunToOffset", pCPU);

	addrStartAddress = __CPU_EIP__(pCPU);
	while (TRUE) {
		if (__CPU_EIP__(pCPU) >= addrStartAddress + (__address)ofOffset) {
			Status = __CPU_STATUS_EXECUTE_SUCCESS__;//执行到指定地址
			break;
		}

		//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto ChaosVmCpuPrepareForRun", pCPU);
		ChaosVmCpuPrepareForRun(pCPU);

		/*
		 * 调用HOOK函数
		 */
		//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto ChaosVmCpuInternalCallHookRoutineExecuteInstruction", pCPU);
		Status = ChaosVmCpuInternalCallHookRoutineExecuteInstruction(pCPU);
		if (__CPU_STATUS_HOOK_STOP_CPU__ == Status)
			break;
		else if(__CPU_STATUS_HOOK_HANDLE__ == Status)
			continue;

		/* 到达这里时 ChaosVmCpuInternalCallHookRoutineExecuteInstruction 通常状况下返回__CPU_STATUS_HOOT_NOT_HANDLE__ */

		/*
		 * 读取指令
		 */
		//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto ChaosVmMmReadCode", pCPU);
		if (!__CPU_STATUS_SUCCESS__(ChaosVmMmReadCode(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU), __CPU_CONTEXT_OPCODE_BUFFER_SIZE__, \
									pCPU->OpcodeBuffer,  &(pCPU->bOpcodeMaxLength)) )) {
			return __GET_LAST_STATUS__(pCPU);
		}

		// 读取OPCODE
		//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto __READ_IMM_UINT8_SAFE__", pCPU);
		__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

		/*
		 * 执行指令
		 */
		//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Next Instruction: Status = pCPU->OneOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);");
		Status = pCPU->OneOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);
		if (__CPU_IS_INTERRUPT_OCCUR__(pCPU)) {
			//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto ChaosVmCpuHandleInterrupt", pCPU);
			Status = ChaosVmCpuHandleInterrupt(pCPU);
		} else if ((pCPU->bIsSingleStepMode)) {
			/*
			 * 如果当前没有发生中断,且处于单步模式,则触发1号中断
			 * 清除TF标志
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_TF, __EFLAG_SET__);

			pCPU->InterruptInfomation.bInterruptId = 1;
			pCPU->InterruptInfomation.dwErrorCode = 0;
			//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Already goto ChaosVmCpuHandleInterrupt", pCPU);
			Status = ChaosVmCpuHandleInterrupt(pCPU);
		}

		/*
		 * 执行出错则退出
		 */
		if (!__CPU_STATUS_SUCCESS__(Status))
			break;

		/*
		 * 收到退出类型的返回码则退出
		 */
		if (__CPU_STATUS_IS_SUCCESS_EXIT__(Status))
			break;
	}

	//__PrintDbgInfo_DebugerBreakPoint__("<chaosvm>Exit ChaosVmCpuRunToOffset", pCPU);

	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunToAddress(PCHAOSVM_CPU pCPU, __address addrAddress) {
	CPU_STATUS Status;
	__byte bInt8CodeByte;
	while (TRUE) {
		if(__CPU_EIP__(pCPU) == addrAddress) {
			/*
			 * 执行到指定地址
			 */
			Status = __CPU_STATUS_EXECUTE_SUCCESS__;
			break;
		}

		ChaosVmCpuPrepareForRun(pCPU);

		/*
		 * 调用HOOK函数
		 */
		Status = ChaosVmCpuInternalCallHookRoutineExecuteInstruction(pCPU);
		if (__CPU_STATUS_HOOK_STOP_CPU__ == Status)
			return Status;
		else if (__CPU_STATUS_HOOK_HANDLE__ == Status)
			continue;

		/*
		 * 读取指令
		 */
		if (!__CPU_STATUS_SUCCESS__(ChaosVmMmReadCode(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU), __CPU_CONTEXT_OPCODE_BUFFER_SIZE__, \
									pCPU->OpcodeBuffer,  &(pCPU->bOpcodeMaxLength)))) {
			return __GET_LAST_STATUS__(pCPU);
		}

		/*
		 * 如果是TF标志设置了,则在设置单步模式
		 */
		pCPU->bIsSingleStepMode = (__EFLAG_SET__ == __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_TF)) ? 1 : 0;
		__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
		Status = pCPU->OneOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);

		if (__CPU_IS_INTERRUPT_OCCUR__(pCPU))
			Status = ChaosVmCpuHandleInterrupt(pCPU);
		else if ((pCPU->bIsSingleStepMode)) {
			/*
			 * 如果当前没有发生中断,且处于单步模式,则触发1号中断
			 * 清除TF标志
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_TF, __EFLAG_SET__);

			pCPU->InterruptInfomation.bInterruptId = 1;
			pCPU->InterruptInfomation.dwErrorCode = 0;
			Status = ChaosVmCpuHandleInterrupt(pCPU);
		}

		/*
		 * 执行出错则退出
		 */
		if (!__CPU_STATUS_SUCCESS__(Status))
			break;

		/*
		 * 收到退出类型的返回码则退出
		 */
		if (__CPU_STATUS_IS_SUCCESS_EXIT__(Status))
			break;
	}

	return Status;	
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunStepIn(PCHAOSVM_CPU pCPU) {
	CPU_STATUS Status;
	__byte bInt8CodeByte;

	ChaosVmCpuPrepareForRun(pCPU);

	/*
	 * 调用HOOK函数
	 */
	Status = ChaosVmCpuInternalCallHookRoutineExecuteInstruction(pCPU);
	if (__CPU_STATUS_HOOK_STOP_CPU__ == Status)
		return Status;
	else if(__CPU_STATUS_HOOK_HANDLE__ == Status)
		return Status;

	/*
	 * 读取指令
	 */
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmReadCode(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU), __CPU_CONTEXT_OPCODE_BUFFER_SIZE__, \
								pCPU->OpcodeBuffer,  &(pCPU->bOpcodeMaxLength)) )) {
		return __GET_LAST_STATUS__(pCPU);
	}

	/*
	 * 如果是TF标志设置了,则在设置单步模式
	 */
	pCPU->bIsSingleStepMode = (__EFLAG_SET__ == __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_TF)) ? 1 : 0;

	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);
	Status = pCPU->OneOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);

	/*
	 * 如果当前没有发生中断,且处于单步模式,则触发1号中断(但并处理中断)
	 */
	if (!__CPU_IS_INTERRUPT_OCCUR__(pCPU)  && (pCPU->bIsSingleStepMode) ) {
		/*
		 * 清除TF标志
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_TF, __EFLAG_SET__);
		pCPU->InterruptInfomation.bInterruptId = 1;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		Status = __CPU_STATUS_INTERRRUPT_OCCUR__;
	}
	return Status;
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunStepOver(PCHAOSVM_CPU pCPU) {
	CPU_STATUS Status;
	__byte bInt8CodeByte;
	__byte bInstructionLength;

	ChaosVmCpuPrepareForRun(pCPU);

	/*
	 * 调用HOOK函数
	 */
	Status = ChaosVmCpuInternalCallHookRoutineExecuteInstruction(pCPU);
	if (__CPU_STATUS_HOOK_STOP_CPU__ == Status)
		return Status;
	else if(__CPU_STATUS_HOOK_HANDLE__ == Status)
		return Status;

	/*
	 * 读取指令
	 */
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmReadCode(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_CS), __CPU_EIP__(pCPU), __CPU_CONTEXT_OPCODE_BUFFER_SIZE__, \
								pCPU->OpcodeBuffer,  &(pCPU->bOpcodeMaxLength)))) {
		return __GET_LAST_STATUS__(pCPU);
	}

	/*
	 * 是不是CALL指令?
	 */
	bInstructionLength = IsCall(pCPU, pCPU->OpcodeBuffer, pCPU->bOpcodeMaxLength);
	if (bInstructionLength)//是CALL指令则运行到一条指令
		return ChaosVmCpuRunToAddress(pCPU, __CPU_EIP__(pCPU) + bInstructionLength);

	/*
	 * 是不是带前缀的串指令?
	 */
	bInstructionLength = IsRepString(pCPU, pCPU->OpcodeBuffer, pCPU->bOpcodeMaxLength);
	if (bInstructionLength)//是带前缀的串指令则运行到下一条指令
		return ChaosVmCpuRunToAddress(pCPU, __CPU_EIP__(pCPU) + bInstructionLength);

	/*
	 * 不是CALL指令和带前缀串指令则单步执行
	 */

	/*
	 * 如果是TF标志设置了,则在设置单步模式
	 */
	pCPU->bIsSingleStepMode = (__EFLAG_SET__ == __CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_TF)) ? 1 : 0;
	__READ_IMM_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength, bInt8CodeByte);

	Status = pCPU->OneOpcodeTableEntry[bInt8CodeByte].DispatchFunction(pCPU);

	/*
	 * 如果当前没有发生中断,且处于单步模式,则触发1号中断(但并处理中断)
	 */
	if (!__CPU_IS_INTERRUPT_OCCUR__(pCPU) && (pCPU->bIsSingleStepMode)) {
		/*
		 * 清除TF标志
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_TF, __EFLAG_SET__);

		pCPU->InterruptInfomation.bInterruptId = 1;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		Status = __CPU_STATUS_INTERRRUPT_OCCUR__;
	}

	return Status;
}

__void * __INTERNAL_FUNC__ ChaosVmCpuGetUserContext(PCHAOSVM_CPU pCPU) {
	return pCPU->pUserContext;
}

__void __INTERNAL_FUNC__ ChaosVmCpuSetUserContext(PCHAOSVM_CPU pCPU, __void *pUserContext) {
	pCPU->pUserContext = pUserContext;
}

__void __INTERNAL_FUNC__ ChaosVmCpuSetMmAccessRoutine(PCHAOSVM_CPU pCPU, FPMmReadRoutine pChaosVmMmRead, FPMmWriteRoutine pChaosVmMmWrite, \
													  FPMmCodeReadRoutine pChaosVmMmCodeRead, FPMmReadDataPartRoutine pChaosVmMmReadDataPartRoutine, \
													  FPMmReadDispPartRoutine pChaosVmMmReadDispPartRoutine) {
	pCPU->pMmRead = pChaosVmMmRead;
	pCPU->pMmWrite = pChaosVmMmWrite;
	pCPU->pMmCodeRead = pChaosVmMmCodeRead;
	pCPU->pMmReadDataPart = pChaosVmMmReadDataPartRoutine;
	pCPU->pMmReadDispPart = pChaosVmMmReadDispPartRoutine;

}

__void __INTERNAL_FUNC__ ChaosVmCpuSetErrorOutputRoutine(PCHAOSVM_CPU pCPU, FPCpuErrorOutputRoutine pChaosVmErrorOutput) {
	pCPU->pErrorOut = pChaosVmErrorOutput;
}

__void __INTERNAL_FUNC__ ChaosVmCpuBuildModrmSibRoutine(PCHAOSVM_CPU pCPU, FPCpuBuildModrmRoutine pBuildModrm, FPCpuBuildSibRoutine pBuildSib) {
	pCPU->pBuildModrm = pBuildModrm;
	pCPU->pBuildSib = pBuildSib;
}

__void __INTERNAL_FUNC__ ChaosVmCpuSetHook(PCHAOSVM_CPU pCPU, __byte bType, __void *pChaosVmHookRoutine) {
	switch (bType) {
	case HOOK_CALL:{
		pCPU->HookRoutine.pCall = (FPCpuFlowControlHookRoutine)pChaosVmHookRoutine;
	}break;
	case HOOK_RET:{
		pCPU->HookRoutine.pRet = (FPCpuFlowControlHookRoutine)pChaosVmHookRoutine;	
	}break;
	case HOOK_JMP:{
		pCPU->HookRoutine.pJmp = (FPCpuFlowControlHookRoutine)pChaosVmHookRoutine;
	}break;
	case HOOK_JCC:{
		pCPU->HookRoutine.pJcc = (FPCpuJccFlowControlHookRoutine)pChaosVmHookRoutine;
	}break;
	case HOOK_EXECUTEINSTRUCTION:{
		pCPU->HookRoutine.pExecuteInstruction = (FPCpuExecuteInstructionHookRoutine)pChaosVmHookRoutine;
	}break;
	case HOOK_EXECUTEEACHINSTRUCTION:{
		pCPU->HookRoutine.pExecuteEachInstruction = (FPCpuExecuteEachInstructionHookRoutine)pChaosVmHookRoutine;
	}break;
	case HOOK_EXECUTEEACHINSTRUCTIONCOMPLETED:{
		pCPU->HookRoutine.pExecuteEachInstructionCompleted = (FPCpuExecuteEachInstructionCompletedHookRoutine)pChaosVmHookRoutine;
	}break;
	}/* end switch */
}

__dword __INTERNAL_FUNC__ ChaosVmCpuGetInstructionType(PCHAOSVM_CPU pCPU) {
	return pCPU->InstructionTypeInfo.wInstructionType;
}

PINSTRUCTION_TYPE_INFO __INTERNAL_FUNC__ ChaosVmCpuGetInstructionTypeInfo(PCHAOSVM_CPU pCPU) {
	return &(pCPU->InstructionTypeInfo);
}

__void __INTERNAL_FUNC__ ChaosVmCpuSetInterruptHandler(PCHAOSVM_CPU pCPU, FPCpuInterruptHandleRoutine pChaosVmInterruptHandler) {
	pCPU->pInterruptHandler = pChaosVmInterruptHandler;
}

__dword __INTERNAL_FUNC__ ChaosVmCpuGR32Get(PCHAOSVM_CPU pCPU, __byte bGR32Index) {
	return __CPU_GR32__(pCPU, bGR32Index);
}

__void __INTERNAL_FUNC__ ChaosVmCpuGR32Set(PCHAOSVM_CPU pCPU, __byte bGR32Index, __dword dwNewValue) {
	__CPU_GR32__(pCPU, bGR32Index) = dwNewValue;
}

__word __INTERNAL_FUNC__ ChaosVmCpuSRGet(PCHAOSVM_CPU pCPU, __byte bSegmentIndex) {
	return __CPU_SR__(pCPU, bSegmentIndex);
}

__void __INTERNAL_FUNC__ ChaosVmCpuSRSet(PCHAOSVM_CPU pCPU, __byte bSegmentIndex, __word wNewValue) {
	__CPU_SR__(pCPU, bSegmentIndex) = wNewValue;
}

__address __INTERNAL_FUNC__ ChaosVmCpuEIPGet(PCHAOSVM_CPU pCPU) {
	return __CPU_EIP__(pCPU);
}

__void __INTERNAL_FUNC__ ChaosVmCpuEIPSet(PCHAOSVM_CPU pCPU, __address addrNewAddress) {
	__CPU_EIP__(pCPU) = addrNewAddress;
}

__byte __INTERNAL_FUNC__ ChaosVmCpuEFlagGet(PCHAOSVM_CPU pCPU, __byte bFlagIndex) {
	return __CPU_EFLAG_GET_AS_NUM__(pCPU, bFlagIndex);
}

__void __INTERNAL_FUNC__ ChaosVmCpuEFlagSet(PCHAOSVM_CPU pCPU, __byte bFlagIndex, __byte bNewValue) {
	__CPU_EFLAG_SET__(pCPU, bFlagIndex, __NUM_TO_EFLAG_STATUS__(bNewValue));
}

__void __INTERNAL_FUNC__ ChaosVmCpuErrorOutput(PCHAOSVM_CPU pCPU, __char *pFormatStr, __char *Info) {
	if (pCPU->pErrorOut) {
		//__word wInfoLength;
		//__char Buffer[1024];
		//va_list ap;

		//va_start(ap, pFormatStr);
		//wInfoLength = (__word)vsprintf(Buffer,(const __char *)pFormatStr, ap);
		//va_end(ap);
		//pCPU->pErrorOut(pCPU, pCPU->pUserContext, (__char *)Buffer);

		//__CPU_ASSERT__(wInfoLength < 1024);
	}
	return;
}

#if defined(__CPU_INTERNAL_DEBUG__)
__void __INTERNAL_FUNC__ ChaosVmCpuAssert(int Result,const char *SourceFile, const char * FunctionName, int LineNo, char * Exp) {
	if(Result) {
		printf("\nAssert!!!\n");
		printf("File:      %s\n",SourceFile);
		printf("Function:  %s\n",FunctionName);
		printf("Line:      %d\n",LineNo);
		printf("Exp:       %s\n",Exp);
	}
	return;
}
#endif
