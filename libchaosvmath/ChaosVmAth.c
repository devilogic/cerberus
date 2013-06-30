#include "ChaosVmAth.h"
#include "lcrypto.h"
#include "Support.h"

/*
 * 全局变量
 */
PCHAOSVMATH g_pChaosVmAth = NULL;

/*
 * 内部使用函数
 */
__void __INTERNAL_FUNC__ ChaosVmAthSetFileAddressToProcedureList(__memory pMem, PCHAOSVMATH_CONFIGURE pConfigure);//设置文件地址给要保护的函数,在全部要保护的函数选定以后调用
PCHAOSVMP_PROCEDURE __INTERNAL_FUNC__ ChaosVmAthProtectIt(PCHAOSVMATH pChaosVmAth, __memory pProcedure, __integer iProcedureSize, __offset ofProcedureRVA, __memory pKeyProcedure, __integer iKeyProcedureSize, __offset ofKeyProcedureRVA, __integer iIndex);//保护选定的
__integer __INTERNAL_FUNC__ ChaosVmAthSelected(PCHAOSVMATH pChaosVmAth);//相当于确认按钮

__dword __INTERNAL_FUNC__ ChaosVmAthHash(__memory pPoint, __integer iSize) {
	return crc32(pPoint, iSize);
}

__integer __INTERNAL_FUNC__ ChaosVmAthEncrypt(__memory pIn, __integer iSize, __dword dwKey, __memory pOut) {
	__byte *pBuf = __logic_new_size__(iSize + 0x10);
	__byte *pKey = __logic_new_size__(iSize + 0x10);
	__logic_memcpy__(pBuf, pIn, iSize);
	XorKey32Bits(dwKey, pKey, iSize);
	XorCoder(pKey, pBuf, iSize);
	__logic_memcpy__(pOut, pBuf, iSize);//输出
	__logic_delete__(pBuf);
	__logic_delete__(pKey);
	return iSize;
}

__integer __INTERNAL_FUNC__ ChaosVmAthInstRemainEncrypt(__memory pIn, __integer iSize, __dword dwKey, __memory pOut) {
	__byte *pBuf = __logic_new_size__(iSize + 0x10);
	__byte *pKey = __logic_new_size__(iSize + 0x10);
	__logic_memcpy__(pBuf, pIn, iSize);
	XorKey32Bits(dwKey, pKey, iSize);
	XorCoder(pKey, pBuf, iSize);
	__logic_memcpy__(pOut, pBuf, iSize);//输出
	__logic_delete__(pBuf);
	__logic_delete__(pKey);
	return iSize;
}

/*
 * 参数:
 *	pConfigure:执行混乱虚拟机附加器的配置结构
 *
 * 介绍:
 *	初始化混乱虚拟机附加器配置结构
 */
__void __API__ ChaosVmAthInitConfigure(PCHAOSVMATH_CONFIGURE pConfigure) {
	__logic_memset__(pConfigure, 0, sizeof(CHAOSVMATH_CONFIGURE));
}

/*
 * 参数:
 *	pConfigure:执行混乱虚拟机附加器的配置结构
 *	addrMemoryAddress:要保护函数的内存地址
 *	iSize:要保护函数的长度
 *
 * 介绍:
 *	设置要保护的函数,设置这个函数的内存地址与长度,通过此函数来设置要保护的函数
 */
__void __API__ ChaosVmAthSelectProcedure(PCHAOSVMATH_CONFIGURE pConfigure, __address addrMemoryAddress, __integer iSize, __address addrKeyMemoryAddress, __integer iKeySize) {
	PCHAOSVMATH_PROCEDURE pProcedure = &(pConfigure->ProceduceList);
	pProcedure[pConfigure->iProcedureCount].addrMemoryAddress = addrMemoryAddress;
	pProcedure[pConfigure->iProcedureCount].iSize = iSize;
	pProcedure[pConfigure->iProcedureCount].addrKeyMemoryAddress = addrKeyMemoryAddress;
	pProcedure[pConfigure->iProcedureCount].iKeySize = iKeySize;

	(pConfigure->iProcedureCount)++;
}

/*
 * 参数:
 *	pChaosVmAth:混乱虚拟机附加器结构指针
 *	iCount:要设置的混乱虚拟机运行环境的索引
 *
 * 介绍:
 *	设置默认的分派函数表给指定的混乱虚拟机运行环境
 */
__INLINE__ __void __INTERNAL_FUNC__ ChaosVmAthSetDefRunTables(PCHAOSVMATH pChaosVmAth, __integer iCount) {
	PCHAOSVM_RUNTIME pRuntime = &(pChaosVmAth->pChaosVmRuntimeList[iCount]);
	PCHAOSVM_CPU pCPU = &(pRuntime->Cpu);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryFF, pChaosVmAth->pOpcodeExtensionTableForOne_FF, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryFE, pChaosVmAth->pOpcodeExtensionTableForOne_FE, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryC6, pChaosVmAth->pOpcodeExtensionTableForOne_C6, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryC7, pChaosVmAth->pOpcodeExtensionTableForOne_C7, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08 * 2);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryF6, pChaosVmAth->pOpcodeExtensionTableForOne_F6, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryF7, pChaosVmAth->pOpcodeExtensionTableForOne_F7, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntry80, pChaosVmAth->pOpcodeExtensionTableForOne_80, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntry81, pChaosVmAth->pOpcodeExtensionTableForOne_81, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntry83, pChaosVmAth->pOpcodeExtensionTableForOne_83, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntry8F, pChaosVmAth->pOpcodeExtensionTableForOne_8F, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryC0, pChaosVmAth->pOpcodeExtensionTableForOne_C0, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryC1, pChaosVmAth->pOpcodeExtensionTableForOne_C1, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryD0, pChaosVmAth->pOpcodeExtensionTableForOne_D0, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryD1, pChaosVmAth->pOpcodeExtensionTableForOne_D1, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryD2, pChaosVmAth->pOpcodeExtensionTableForOne_D2, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntryD3, pChaosVmAth->pOpcodeExtensionTableForOne_D3, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->PargsDispatchTableEntry0FBA, pChaosVmAth->pOpcodeExtensionTableForTwo_0FBA, sizeof(PARGS_DISPATCH_TABLE_ENTRY) * 0x08);
	__logic_memcpy__(pCPU->OneOpcodeTableEntry, pChaosVmAth->pOneByteOpcodeTable, sizeof(ONE_OPCODE_TABLE_ENTRY) * 0x100);
	__logic_memcpy__(pCPU->TwoByteOpcodeTableEntry, pChaosVmAth->pTwoByteOpcodeTable, sizeof(TWO_BYTE_OPCODE_TABLE_ENTRY) * 0x100);
	__logic_memcpy__(pCPU->EFlagConditionTableEntry, pChaosVmAth->pEFlagContionTable, sizeof(EFLAG_CONDITION_TABLE_ENTRY) * 0x10);
	__logic_memcpy__(pCPU->ModrmByteAnalyseRoutineTableEntry, pChaosVmAth->pModRMAnalyseRoutineTable, sizeof(MODRM_BYTE_ANALYSE_ROUTINE_TABLE_ENTRY) * 0x02);
}

/*
 * 参数:
 *	pConfigure:混乱虚拟机附加器配置结构
 *
 * 介绍:
 *	核算要保护的所有函数的长度综合,并且最后使用__VMPPROCEDURE_DATA_SIZE__粒度进行对齐
 */
#define __VMPPROCEDURE_DATA_SIZE__		0x1000
__INLINE__ __integer __INTERNAL_FUNC__ ChaosVmAthCountVmpProcedureTotalSize(PCHAOSVMATH_CONFIGURE pConfigure) {
	__integer i = 0, iTotalSize = 0;
	for (i = 0; i < pConfigure->iProcedureCount; i++)
		iTotalSize += pConfigure->ProceduceList[i].iSize;
	iTotalSize = Alig(iTotalSize, __VMPPROCEDURE_DATA_SIZE__, TRUE);
	return iTotalSize;
}

/*
 * 参数:
 *	pMem:要保护的宿主文件的文件映射
 *	pConfigure:混乱虚拟机附加器配置结构
 *
 * 介绍:
 *	设置所有被保护的函数的文件地址通过当前的文件映射
 */
__void __INTERNAL_FUNC__ ChaosVmAthSetFileAddressToProcedureList(__memory pMem, PCHAOSVMATH_CONFIGURE pConfigure) {
	PCHAOSVMATH_PROCEDURE pProcedure = &(pConfigure->ProceduceList);
	__address addrImageBase = GetNtHeader(pMem)->OptionalHeader.ImageBase;
	__integer i = 0;
	for (i = 0; i < pConfigure->iProcedureCount; i++) {
		__memory pCurr = pMem + Rva2Raw(pMem, pProcedure[i].addrMemoryAddress - addrImageBase);
		__memory pKeyCurr = pMem + Rva2Raw(pMem, pProcedure[i].addrKeyMemoryAddress - addrImageBase);
		pProcedure[i].pAddress = pCurr;
		pProcedure[i].pKeyAddress = pKeyCurr;
	}
}

__INLINE__ __void __INTERNAL_FUNC__ FreeChaosVmAth(PCHAOSVMATH pChaosVmAth) {
	__memory pOrigChaosVm = NULL;
	__memory pChaosVm = NULL;
	PCHAOSVMATH_CONFIGURE pConfigure = NULL;
	__integer i = 0;
	__integer iCount = 0;

	if (!pChaosVmAth) return;

	pChaosVm = pChaosVmAth->pChaosVm;
	pOrigChaosVm = pChaosVmAth->pOrigChaosVm;
	pConfigure = pChaosVmAth->pConfigure;
	if (pChaosVmAth->piVmpProcedureCount) iCount = *(pChaosVmAth->piVmpProcedureCount);

	// 释放混乱虚拟机,会在DISAth中进行释放
	//if (pChaosVm) UnMapResourceData(pChaosVm);

	if (pOrigChaosVm) 
		__logic_delete__(pOrigChaosVm);

	for (i = 0; i < iCount; i++) {
		__logic_delete__(pChaosVmAth->pChaosVmpProcedure[i]);
	}

	__logic_delete__(pChaosVmAth);
	//__logic_memset__(pChaosVmAth, 0, sizeof(CHAOSVMATH));
}

/*
 * 参数:
 *	pConfigure:DIS配置结构
 *
 * 介绍:
 *	将虚拟机保护附加到要保护的程序上
 *
 *	要动态释放的内存有:
 *		1.目标文件映射本身
 *		2.混乱虚拟机的原始备份(原始数据,未来功能扩展使用)
 *		3.混乱虚拟机附加器结构
 *		4.目标文件末尾数据备份(如果存在末尾数据)
 *		5.混乱虚拟机本身
 */
__dword __API__ ChaosVmAthAttach(PDISATH_CONFIGURE pConfigure) {
	__dword dwRet = __DIS_ERROR_SUCCESS__;

	// 附加混乱虚拟机
	dwRet = DISAthAttach(pConfigure);
	if (!__DISATH_SUCCESS__(dwRet))
		FreeChaosVmAth(g_pChaosVmAth);

	return dwRet;
}

/*
 * 参数:
 *	pChaosVmAth:混乱虚拟机附加器结构
 *	iCount:要进行编码的运行环境时索引号
 *	pOpcodeTbl1:第一张编码表
 *	pOpcodeTbl2:第二张编码表
 *
 * 介绍:
 *	通过转码后的OPCODE表给某一个运行环境时(被保护的函数)的CPU派遣函数表进行顺序交换,这样做的目的是使每个被保护的函数的虚拟CPU的解释指令执行的派遣
 *	函数队列都有不同的随机顺序,这样防止对固定地址的分析
 */
__INLINE__ __void __INTERNAL_FUNC__ ChaosVmAthMixTables(PCHAOSVMATH pChaosVmAth, __integer iCount, __byte *pOpcodeTbl1, __byte *pOpcodeTbl2) {
	__bool bSwitched[0x100] = {FALSE};
	__integer i = 0;
	PCHAOSVM_RUNTIME pRuntime = &(pChaosVmAth->pChaosVmRuntimeList[iCount]);
	PCHAOSVM_CPU pCPU = &(pRuntime->Cpu);
	PONE_OPCODE_TABLE_ENTRY pOneByteOpcodeTable = &(pCPU->OneOpcodeTableEntry);
	PTWO_BYTE_OPCODE_TABLE_ENTRY pTwoByteOpcodeTable = &(pCPU->TwoByteOpcodeTableEntry);
	ONE_OPCODE_TABLE_ENTRY OneOpcodeTableEntryTmp;
	TWO_BYTE_OPCODE_TABLE_ENTRY TwoByteOpcodeTableEntryTmp;

	// 第一张表
	for (i = 0; i < 0x100; i++) {
		__byte bTargetIndex = pOpcodeTbl1[i];
		if (bSwitched[i]) continue;//如果已经得到了交换则继续

		__logic_memcpy__((__memory)(&OneOpcodeTableEntryTmp), (__memory)(&pOneByteOpcodeTable[i]), sizeof(ONE_OPCODE_TABLE_ENTRY));
		__logic_memcpy__((__memory)(&pOneByteOpcodeTable[i]), (__memory)(&pOneByteOpcodeTable[bTargetIndex]), sizeof(ONE_OPCODE_TABLE_ENTRY));
		__logic_memcpy__((__memory)(&pOneByteOpcodeTable[bTargetIndex]), (__memory)(&OneOpcodeTableEntryTmp), sizeof(ONE_OPCODE_TABLE_ENTRY));

		// 设置以交换标志
		bSwitched[i] = TRUE;
		bSwitched[bTargetIndex] = TRUE;
	}

	// 第二张表
	__logic_memset__(bSwitched, FALSE, 0x100);
	for (i = 0; i < 0x100; i++) {
		__byte bTargetIndex = pOpcodeTbl2[i];
		if (bSwitched[i]) continue;//如果已经得到了交换则继续

		__logic_memcpy__((__memory)(&TwoByteOpcodeTableEntryTmp), (__memory)(&pTwoByteOpcodeTable[i]), sizeof(TWO_BYTE_OPCODE_TABLE_ENTRY));
		__logic_memcpy__((__memory)(&pTwoByteOpcodeTable[i]), (__memory)(&pTwoByteOpcodeTable[bTargetIndex]), sizeof(TWO_BYTE_OPCODE_TABLE_ENTRY));
		__logic_memcpy__((__memory)(&pTwoByteOpcodeTable[bTargetIndex]), (__memory)(&TwoByteOpcodeTableEntryTmp), sizeof(TWO_BYTE_OPCODE_TABLE_ENTRY));

		// 设置以交换标志
		bSwitched[i] = TRUE;
		bSwitched[bTargetIndex] = TRUE;
	}
}

/*
 * 参数:
 *	pChaosVmAth:混乱虚拟机附加器结构
 *	pProcedure:要保护函数的文件地址
 *	iProcedureSize:要保护函数的大小
 *	addrProcedure:要保护函数的内存地址
 *	iIndex:保护函数的索引
 *
 * 介绍:
 *	执行对指定函数的虚拟化
 */
PCHAOSVMP_PROCEDURE __INTERNAL_FUNC__ ChaosVmAthProtectIt(PCHAOSVMATH pChaosVmAth, __memory pProcedure, __integer iProcedureSize, __offset ofProcedureRVA, \
															__memory pKeyProcedure, __integer iKeyProcedureSize, __offset ofKeyProcedureRVA, __integer iIndex) {
	__byte Opcode1Tbl[0x100] = {0};
	__byte Opcode2Tbl[0x100] = {0};
	__byte ModRmTbl[0x03] = {0};
	__byte SibTbl[0x03] = {0};
	__address addrWriteAddress = 0, addrTargetImageBase = 0;
	__offset ofOffset = 0, ofRVA = 0;
	__integer iWriteSize = 0;
	//__integer iCount = *(pChaosVmAth->piVmpProcedureCount);//获取当前在虚拟机附加器中的函数索引
	PCHAOSVMP_PROCEDURE pVmpProcedure = NULL;
	PCHAOSVMATH_CONFIGURE pConfigure = pChaosVmAth->pConfigure;
	PCHAOSVM_RUNTIME pRuntime = &(pChaosVmAth->pChaosVmRuntimeList[iIndex]);
	PCHAOSVM_CPU pCPU = &(pRuntime->Cpu);
	__bool bHeader = FALSE;
	__dword dwNextKey = 0;
	__memory pChaosVmInvokeThunkCode = NULL;
	__integer iChaosVmInvokeThunkCodeSize = 0;
	__memory pOrigVmpProcedure = NULL;

	// 是否是头函数
	if (iIndex == 0)
		bHeader = TRUE;

	// 每个函数都拥有自己的OPCODE表与独立的Modrm/Sib表
	GenerateRandOpcodeTable(Opcode1Tbl, NULL);
	GenerateRandOpcodeTable(Opcode2Tbl, NULL);
	GenerateRandModRmTable(ModRmTbl, NULL);
	GenerateRandSibTable(SibTbl, NULL);

	// 设定虚拟机保护调用头
	iChaosVmInvokeThunkCodeSize = iProcedureSize;
	if (pConfigure->pGenChaosVmInvokeThunkCode) {
		// 使用自定义的调用头
		pChaosVmInvokeThunkCode = pConfigure->pGenChaosVmInvokeThunkCode(iChaosVmInvokeThunkCodeSize);
		if (!pChaosVmInvokeThunkCode) goto _use_def_invoke_thunkcode;//如果花指令生成失败,则调用默认生成的花指令
	} else {
_use_def_invoke_thunkcode:
		// 使用默认的花指令修复函数
		pChaosVmInvokeThunkCode = (__memory)__logic_new_size__(iChaosVmInvokeThunkCodeSize);
		__logic_memset__(pChaosVmInvokeThunkCode, 0x90, iChaosVmInvokeThunkCodeSize);
	}

	// 保存原始的函数
	pOrigVmpProcedure = (__memory)__logic_new_size__(iProcedureSize);
	if (!pOrigVmpProcedure) {
		if (pChaosVmInvokeThunkCode) __logic_delete__(pChaosVmInvokeThunkCode);
	}
	__logic_memcpy__(pOrigVmpProcedure, pProcedure, iProcedureSize);

	// 进行虚拟机保护
	if (bHeader) {
		pVmpProcedure = VmpThisProcedure(pProcedure, iProcedureSize, ofProcedureRVA, pChaosVmAth->pVmHash, \
										pChaosVmAth->pVmEncrypt, pChaosVmAth->pVmInstRemainEncrypt, Opcode1Tbl, \
										Opcode2Tbl, ModRmTbl, SibTbl, pChaosVmInvokeThunkCode, iChaosVmInvokeThunkCodeSize, \
										0, TRUE, &dwNextKey, \
										pKeyProcedure, iKeyProcedureSize, ofKeyProcedureRVA);
	} else {
		pVmpProcedure = VmpThisProcedure(pProcedure, iProcedureSize, ofProcedureRVA, pChaosVmAth->pVmHash, \
										pChaosVmAth->pVmEncrypt, pChaosVmAth->pVmInstRemainEncrypt, Opcode1Tbl, \
										Opcode2Tbl, ModRmTbl, SibTbl, pChaosVmInvokeThunkCode, iChaosVmInvokeThunkCodeSize, \
										pChaosVmAth->dwKey, FALSE, &dwNextKey, \
										pKeyProcedure, iKeyProcedureSize, ofKeyProcedureRVA);
	}

	// 查看保护释放成功
	if (!pVmpProcedure)
		return NULL;

	// 释放调用头花指令
	if (pChaosVmInvokeThunkCode) __logic_delete__(pChaosVmInvokeThunkCode);

	// 设置基本信息
	pChaosVmAth->dwKey = dwNextKey;//更新KEY
	pChaosVmAth->pChaosVmpProcedure[iIndex] = pVmpProcedure;
	__logic_memcpy__(pVmpProcedure->ModRmTbl, &ModRmTbl, sizeof(__byte) * 3);
	__logic_memcpy__(pVmpProcedure->SibTbl, &SibTbl, sizeof(__byte) * 3);

	// 设置被VMP后的函数到新的数据区域
	if (pConfigure->Mode == CRM_INFECT) {
		/*
		 * 感染模式
		 */
		__memory pProcedureKeep = NULL;//用来保存被虚拟化后的函数指针
		iWriteSize = pVmpProcedure->iSize;//获取保护函数的长度
		__logic_memcpy__(pChaosVmAth->pProcedureWriteTo, pVmpProcedure->pVmpProcedure, iWriteSize);//写入到内存
		addrTargetImageBase = pChaosVmAth->addrTargetImageBase;
		ofOffset = (__offset)(pChaosVmAth->pProcedureWriteTo - pChaosVmAth->pXFileAttachInfo->pMem);//写入位置的偏移
		ofRVA = Raw2Rva(pChaosVmAth->pXFileAttachInfo->pMem, ofOffset);
		addrWriteAddress = (__address)(addrTargetImageBase + ofRVA);//目前没有用途,保留以后使用
		//__logic_delete__(pVmpProcedure->pVmpProcedure);//释放原先的内存
		pProcedureKeep = pVmpProcedure->pVmpProcedure;//保存一下
		//pVmpProcedure->pVmpProcedure = (__memory)addrWriteAddress;//将写入后的位置转换成内存地址
		pVmpProcedure->ofVmpProcedureRVA = (__offset)ofRVA;//写入RVA
		pChaosVmAth->pProcedureWriteTo += iWriteSize;
		__logic_memcpy__(&(pRuntime->Procedure), pVmpProcedure, sizeof(CHAOSVMP_PROCEDURE));

		// 设定回调函数,按照新的编码表
		ChaosVmAthSetDefRunTables(pChaosVmAth, iIndex);//初始化表
		ChaosVmAthMixTables(pChaosVmAth, iIndex, Opcode1Tbl, Opcode2Tbl);

		// 如果输出到字节码文件
		if (pChaosVmAth->pConfigure->bUseByteCodeFile) {
			PCHAOSVM_EMULATION_BYTECODE_PROCEDURE pByteCodeProcedure = NULL;
			// 将被保护的函数写入到bytecode文件
			pByteCodeProcedure = ChaosVmByteCodeFileAddByteCodeProcedureToFile(&(pChaosVmAth->pByteCodeFile), pProcedureKeep, iWriteSize);
			if (!pByteCodeProcedure) {
				// 写入函数到bytecode文件出错
			}
		}/* end if */

		(*(pChaosVmAth->piVmpProcedureCount))++;//增加被保护函数计数
		__logic_delete__(pProcedureKeep);//释放被虚拟化后的函数内存
	} else if (pConfigure->Mode == CRM_EMULATION) {
		/*
		 * 仿真模式
		 * 在仿真模式下,将被保护的函数在内存里记录一份原始的加密备份,并且输出成bytecode文件
		 */
		PCHAOSVM_EMULATION_BYTECODE_PROCEDURE pByteCodeProcedure = NULL;
		__dword dwOrigProcedureKey = 0xFBAC1983;

		iWriteSize = pVmpProcedure->iSize;//获取保护函数的长度
		XorArray(dwOrigProcedureKey, pOrigVmpProcedure, pChaosVmAth->pProcedureWriteTo, iWriteSize);//加密写入到内存
		pChaosVmAth->pProcedureWriteTo += iWriteSize;
		__logic_delete__(pOrigVmpProcedure);
		pChaosVmAth->pProcedureWriteTo += iWriteSize;
		__logic_memcpy__(&(pRuntime->Procedure), pVmpProcedure, sizeof(CHAOSVMP_PROCEDURE));

		// 将被保护的函数写入到bytecode文件
		pByteCodeProcedure = ChaosVmByteCodeFileAddByteCodeProcedureToFile(&(pChaosVmAth->pByteCodeFile), pVmpProcedure->pVmpProcedure, iWriteSize);
		if (!pByteCodeProcedure) {
			// 写入函数到bytecode文件出错
		}

		// 加密编码规则表
		XorArray(__CHAOSVM_DECRYPT_OPCODE_TABLE_KEY_EMULATION_MODE__, Opcode1Tbl, pRuntime->Opcode1Tbl, 0x100);
		XorArray(__CHAOSVM_DECRYPT_OPCODE_TABLE_KEY_EMULATION_MODE__, Opcode2Tbl, pRuntime->Opcode2Tbl, 0x100);

	} else if (pConfigure->Mode == CRM_EMULATION_SYS) {
		;
	} else if (pConfigure->Mode == CRM_NETWORK) {
		;
	} else {
		;
	}

	// 设定运行环境时索引
	pRuntime->iIndex = iIndex;//设定此函数的索引

	return pVmpProcedure;
}

/*
 * 参数:
 *	pChaosVmAth:混乱虚拟机附加器结构
 *
 * 介绍:
 *	保护被选定的函数
 */
__integer __INTERNAL_FUNC__ ChaosVmAthSelected(PCHAOSVMATH pChaosVmAth) {
	__integer i = 0;
	PCHAOSVMATH_CONFIGURE pConfigure = pChaosVmAth->pConfigure;
	__address addrTargetImageBase = pChaosVmAth->addrTargetImageBase;
	__offset ofProcedureRVA = 0;
	__offset ofKeyProcedureRVA = 0;

	for (i = 0; i < pConfigure->iProcedureCount; i++) {
		ofProcedureRVA = (__offset)(pConfigure->ProceduceList[i].addrMemoryAddress - addrTargetImageBase);
		// 如果addrKeyMemoryAddress == 0表示采用随机密钥
		if (pConfigure->ProceduceList[i].addrKeyMemoryAddress == 0) ofKeyProcedureRVA = 0;
		else ofKeyProcedureRVA = (__offset)(pConfigure->ProceduceList[i].addrKeyMemoryAddress - addrTargetImageBase);
		if (!ChaosVmAthProtectIt(
			pChaosVmAth, pConfigure->ProceduceList[i].pAddress, pConfigure->ProceduceList[i].iSize, ofProcedureRVA, \
			pConfigure->ProceduceList[i].pKeyAddress, pConfigure->ProceduceList[i].iKeySize, ofKeyProcedureRVA, i
			)) {
			return 0;
		}
	}
	return i;
}

/*
 * 参数:
 *	目标文件路径
 *
 * 介绍:
 *	返回目标文件类型
 */
CHAOSVMATH_FILETYPE __API__ ChaosVmAthGetFileType(__tchar *pTargetFilePath) {
	__memory pMem = NULL;
	__integer iTargetFileSize = 0;

	pMem = MappingFile(pTargetFilePath, &iTargetFileSize, FALSE, 0, 0);
	if (!pMem)
		return CFT_NONE;
	
	if (!IsValidPE32(pMem)) {
		UnMappingFile(pMem);
		return CFT_NONE;
	}

	if (IsDriverFile(pMem)) {
		return CFT_SYS;
	} else if (IsDriverFile(pMem)) {
		UnMappingFile(pMem);
		return CFT_DLL;
	} else {
		UnMappingFile(pMem);
		return CFT_EXE;
	}
	
	return CFT_NONE;
}

//__byte __INTERNAL_FUNC__ ChaosVmpAthOpcodeExchange(__byte bOpcode) {
//	return 0;
//}
//
//__byte* __INTERNAL_FUNC__ ChaosVmpAthModRmSibExchage(__byte *bOpcode) {
//	return NULL;
//}
//

// DIS附加器步骤
#include "ChaosVmAthDISAthSteps.c"