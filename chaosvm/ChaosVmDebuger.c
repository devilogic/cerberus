/*
 * 这份文件实现了用于在附加到目标程序以后对混乱虚拟机的调试
 */

/*
 * 参数:
 *	pRegisters:寄存器队列
 *
 * 介绍:
 *	打印混乱虚拟机当前的寄存器的值
 */
__void __INTERNAL_FUNC__ ChaosVmDebugerPrintCurrRegisters(PCPU_BASIC_REGISTERS pRegisters) {
	PrintDbgInfo_DebugerWriteFormatStringInteger("EAX = ", pRegisters->GeneralRegister.Interface.EAX.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("ECX = ", pRegisters->GeneralRegister.Interface.ECX.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("EDX = ", pRegisters->GeneralRegister.Interface.EDX.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("EBX = ", pRegisters->GeneralRegister.Interface.EBX.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("ESP = ", pRegisters->GeneralRegister.Interface.ESP.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("EBP = ", pRegisters->GeneralRegister.Interface.EBP.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("ESI = ", pRegisters->GeneralRegister.Interface.ESI.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("EDI = ", pRegisters->GeneralRegister.Interface.EDI.dwValue32);
	PrintDbgInfo_DebugerWriteFormatStringInteger("EFL = ", pRegisters->EFlag.BitArray);
}

/*
 * 参数:
 *	pCPU:虚拟CPU
 *
 * 介绍:
 *	打印混乱虚拟机当前的CPU的状态
 */
__void __INTERNAL_FUNC__ ChaosVmDebugerPrintCurrCpu(PCHAOSVM_CPU pCPU) {
	PrintDbgInfo_DebugerWriteFormatStringInteger("EIP = ", pCPU->CurrentRegistersStatus.EIP);
	ChaosVmDebugerPrintCurrRegisters(&(pCPU->CurrentRegistersStatus.BasicRegister));//打印寄存器
}

/*
 * 参数:
 *	pProcedure:当前被保护函数的结构
 *
 * 介绍:
 *	打印混乱虚拟机当前的被保护的函数信息
 */
__void __INTERNAL_FUNC__ ChaosVmDebugerPrintCurrProcedure(PCHAOSVMP_PROCEDURE pProcedure) {
	// 是否是头函数
	if (pProcedure->bHeader) {
		PrintDbgInfo_DebugerWriteLine("This Procedure is Header");
	} else {
		PrintDbgInfo_DebugerWriteLine("This Procedure is Normal");
	}

	PrintDbgInfo_DebugerWriteFormatStringInteger("Rel Address = ", (__integer)(pProcedure->addrRealAddress));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Vis Address = ", (__integer)(pProcedure->addrVisualAddress));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Procedure Size = ", (__integer)(pProcedure->iSize));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Procedure Init Key = ", (__integer)(pProcedure->dwKey));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Procedure Instruction Count = ", (__integer)(pProcedure->iInstCount));
}

/*
 * 参数:
 *	pRuntime:当前被保护函数的运行环境时
 *
 * 介绍:
 *	打印混乱虚拟机当前的被保护的函数的运行环境时
 */
__void __INTERNAL_FUNC__ ChaosVmDebugerPrintCurrRuntime(PCHAOSVM_RUNTIME pRuntime) {
	PrintDbgInfo_DebugerWriteFormatStringInteger("Stack Address = ", (__integer)(pRuntime->pStack));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Stack Size = ", (__integer)(pRuntime->iStackSize));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Index = ", (__integer)(pRuntime->iIndex));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Next Key = ", (__integer)(pRuntime->dwKey));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Prev Procedure Address = ", (__integer)(pRuntime->addrPrevProcedureAddress));
	PrintDbgInfo_DebugerWriteFormatStringInteger("Prev Procedure Size = ", (__integer)(pRuntime->iPrevProcedureSize));
}

/*
 *
 * 介绍:
 *	混乱虚拟机调试器配置
 */

typedef struct _CHAOSVM_DEBUGER_CONFIGURE {
	__bool bSkipAllBreakPoint;//跳过所有断点
} CHAOSVM_DEBUGER_CONFIGURE, *PCHAOSVM_DEBUGER_CONFIGURE;
CHAOSVM_DEBUGER_CONFIGURE g_ChaosVmDebugerConfigure;//全局变量

#define __CHAOSVM_DEBUGER_COMMAND_SIZE__				1024
#define __CHAOSVM_DEBUGER_CONFIGURE_TITLE__				"chaosvm-debuger-configure#"
__void __INTERNAL_FUNC__ ChaosVmDebugerConfigure() {
	__char szCommand[__CHAOSVM_DEBUGER_COMMAND_SIZE__];

	while (1) {
		// 输出命令行
		__PrintDbgInfo_DebugerWrite__(__CHAOSVM_DEBUGER_CONFIGURE_TITLE__);
		// 接收命令
		__PrintDbgInfo_DebugerReadLine__(szCommand, __CHAOSVM_DEBUGER_COMMAND_SIZE__);

		if (__logic_strncmp__(szCommand, "skip-all-breakpoint", __logic_strlen__("skip-all-breakpoint")) == 0) {
			// 忽略所有断点
			g_ChaosVmDebugerConfigure.bSkipAllBreakPoint = TRUE;
		} else if (__logic_strncmp__(szCommand, "exit-configure", __logic_strlen__("exit-configure")) == 0) {
			// 退出配置
			break;
		}
	}/* end while */
}

/*
 * 参数:
 *	pCommand:当前要输入的命令
 *	pParam:命令行的附加参数
 *
 * 介绍:
 *	混乱虚拟机调试器
 */
__bool __INTERNAL_FUNC__ ChaosVmDebuger(__char *pCommand, __void *pParam) {
	if (!pParam) {
		PrintDbgInfo_DebugerWriteLine("Param is NULL");
		return FALSE;
	}

	if ((__logic_strncmp__(pCommand, "print-cpu", __logic_strlen__("print-cpu")) == 0) ||
		(__logic_strncmp__(pCommand, "pc", __logic_strlen__("pc")) == 0)) {
		ChaosVmDebugerPrintCurrCpu((PCHAOSVM_CPU)pParam);
	} else if ((__logic_strncmp__(pCommand, "print-procedure", __logic_strlen__("print-procedure")) == 0) ||
		(__logic_strncmp__(pCommand, "pp", __logic_strlen__("pp")) == 0)) {
		ChaosVmDebugerPrintCurrProcedure((PCHAOSVMP_PROCEDURE)pParam);
	} else if ((__logic_strncmp__(pCommand, "print-registers", __logic_strlen__("print-registers")) == 0) ||
		(__logic_strncmp__(pCommand, "pr", __logic_strlen__("pr")) == 0)) {
		ChaosVmDebugerPrintCurrRegisters((PCPU_BASIC_REGISTERS)pParam);
	} else if ((__logic_strncmp__(pCommand, "prt", __logic_strlen__("prt")) == 0) ||
		(__logic_strncmp__(pCommand, "print-runtime", __logic_strlen__("print-runtime")) == 0)) {
		ChaosVmDebugerPrintCurrRuntime((PCHAOSVM_RUNTIME)pParam);
	} else if (__logic_strncmp__(pCommand, "chaosvm-debuger-configure", __logic_strlen__("chaosvm-debuger-configure")) == 0) {
		ChaosVmDebugerConfigure();
		return g_ChaosVmDebugerConfigure.bSkipAllBreakPoint;//返回
	} else {
		// 暂时没有命令
	}
	return FALSE;
}
