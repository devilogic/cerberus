/*
 * 代码读取接口
 */
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmReadCode(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte bSizeToReadByte, \
												  __byte *pOutputBuffer, __byte *pbSizeReturnedByte) {
	__byte bSizeReturned = 0;
	CPU_STATUS Status = pCPU->pMmCodeRead(pCPU, pCPU->pUserContext, wSeg, addrAddress, bSizeToReadByte, pOutputBuffer, &bSizeReturned);
	__SET_LAST_STATUS__(pCPU, Status);
	if (__CPU_STATUS_MM_ACCESS_SUCCESS__ != Status) {
		/*
		 * 读取出错，此处设置访问中断
		 */
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_GP__;
		if (__CPU_STATUS_MM_INVALID_ADDRESS__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_INVALID_ADDRESS__;
		else if (__CPU_STATUS_MM_BAD_PRIVILEGE__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_BAD_PRIVILEGE__;

		pCPU->InterruptInfomation.Infomation.GP.wSeg = wSeg;
		pCPU->InterruptInfomation.Infomation.GP.addrMemoryAddress = addrAddress;
		pCPU->InterruptInfomation.Infomation.GP.dwRequestOpreation = __MM_ACCESS_FOR_EXECUTE__;
		return Status;
	}

	if (pbSizeReturnedByte)
		*pbSizeReturnedByte = bSizeReturned;
	return Status;
}

/*
 * 普通数据读取接口
 */
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmReadBlockAndSetInterrupt(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, \
																  __byte bSizeToReadByte, __byte *pOutputBuffer) {
	__byte bSizeReturnedByte;
	__byte ReadBuffer[32] = {0};
	CPU_STATUS Status = pCPU->pMmRead(pCPU, pCPU->pUserContext, wSeg, addrAddress, bSizeToReadByte, ReadBuffer, &bSizeReturnedByte);
	__SET_LAST_STATUS__(pCPU, Status);

	if (__CPU_STATUS_MM_ACCESS_SUCCESS__ != Status) {
		/*
		 * 读取出错，此处设置访问中断
		 */
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_GP__;
		if (__CPU_STATUS_MM_INVALID_ADDRESS__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_INVALID_ADDRESS__;
		else if (__CPU_STATUS_MM_BAD_PRIVILEGE__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_BAD_PRIVILEGE__;

		pCPU->InterruptInfomation.Infomation.GP.wSeg = wSeg;
		pCPU->InterruptInfomation.Infomation.GP.addrMemoryAddress = addrAddress;
		pCPU->InterruptInfomation.Infomation.GP.dwRequestOpreation = __MM_ACCESS_FOR_READ__;

		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return Status;
	}

	if (bSizeToReadByte != bSizeReturnedByte) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_GP__;
		pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_INVALID_ADDRESS__;
		pCPU->InterruptInfomation.Infomation.GP.wSeg = wSeg;
		pCPU->InterruptInfomation.Infomation.GP.addrMemoryAddress = addrAddress;
		pCPU->InterruptInfomation.Infomation.GP.dwRequestOpreation = __MM_ACCESS_FOR_READ__;

		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_MM_INVALID_ADDRESS_2__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __CPU_STATUS_MM_INVALID_ADDRESS_2__;
	}
	__logic_memcpy__(pOutputBuffer, ReadBuffer, bSizeToReadByte);
	return  Status;
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __char *pInt8Value) {
	return ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__char), (__byte *)pInt8Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sword *pInt16Value) {
	return ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__sword), (__byte *)pInt16Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sdword *pInt32Value) {
	return ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__dword), (__byte *)pInt32Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sqword *pInt64Value) {
	return  ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__qword), (__byte *)pInt64Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte *puInt8Value) {
	return  ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__byte), (__byte *)puInt8Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __word *puInt16Value) {
	return  ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__word), (__byte *)puInt16Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __dword *puInt32Value) {
	return  ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__dword), (__byte *)puInt32Value);
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __qword *puInt64Value) {
	return  ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__qword), (__byte *)puInt64Value);
}

/*
 *普通数据写入接口
 */
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWriteBlockAndSetInterrupt(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, \
																   __byte bSizeToWriteByte, __byte *pInputBuffer) {
	CPU_STATUS Status = pCPU->pMmWrite(pCPU, pCPU->pUserContext, wSeg, addrAddress, bSizeToWriteByte, pInputBuffer);
	__SET_LAST_STATUS__(pCPU, Status);

	if (__CPU_STATUS_MM_ACCESS_SUCCESS__ != Status) {
		/*
		 * 读取出错，此处设置访问中断
		 */
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_GP__;
		if (__CPU_STATUS_MM_INVALID_ADDRESS__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_INVALID_ADDRESS__;
		else if(__CPU_STATUS_MM_BAD_PRIVILEGE__ == Status)
			pCPU->InterruptInfomation.dwErrorCode = __INTERRUPT_GP_ERRORCODE_BAD_PRIVILEGE__;

		pCPU->InterruptInfomation.Infomation.GP.wSeg = wSeg;
		pCPU->InterruptInfomation.Infomation.GP.addrMemoryAddress = addrAddress;
		pCPU->InterruptInfomation.Infomation.GP.dwRequestOpreation = __MM_ACCESS_FOR_WRITE__;

		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return Status;
	}
	return  Status;
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __char Int8Value) {
	return ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__char), (__byte *)(&Int8Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sword Int16Value) {
	return ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__sword), (__byte *)(&Int16Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sdword Int32Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__sdword), (__byte *)(&Int32Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sqword Int64Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__sqword), (__byte *)(&Int64Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte uInt8Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__byte), (__byte *)(&uInt8Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __word uInt16Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__word), (__byte *)(&uInt16Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __dword uInt32Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__dword), (__byte *)(&uInt32Value));
}

CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __qword uInt64Value) {
	return  ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, sizeof(__qword), (__byte *)(&uInt64Value));
}
