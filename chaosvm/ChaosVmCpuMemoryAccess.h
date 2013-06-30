#if !defined(__CHAOSVM_CPU_MEMORY_ACCESS_H__)
#define __CHAOSVM_CPU_MEMORY_ACCESS_H__

#define __INTERRUPT_GP_ERRORCODE_INVALID_ADDRESS__		1
#define __INTERRUPT_GP_ERRORCODE_BAD_PRIVILEGE__		2

#if 1
#define __MM_ACCESS_FOR_READ__					1
#define __MM_ACCESS_FOR_WRITE__					2
#define __MM_ACCESS_FOR_RW__					(__MM_ACCESS_FOR_READ__ | __MM_ACCESS_FOR_WRITE__)
#define __MM_ACCESS_FOR_EXECUTE__				4
#else
#define __MM_ACCESS_FOR_READ__					0x02
#define __MM_ACCESS_FOR_WRITE__					__MM_ACCESS_FOR_RW__
#define __MM_ACCESS_FOR_RW__					0x04
#define __MM_ACCESS_FOR_EXECUTE_READ__			0x20
#endif


CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmReadCode(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte bSizeToReadByte, \
												  __byte *pOutputBuffer, __byte *pbSizeReturnedByte);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmReadBlockAndSetInterrupt(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, \
																  __byte bSizeToReadByte, __byte *pOutputBuffer);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __char *pInt8Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sword *pInt16Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sdword *pInt32Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_sQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sqword *pInt64Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte *puInt8Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __word *puInt16Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __dword *puInt32Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmRead_uQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __qword *puInt64Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWriteBlockAndSetInterrupt(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, \
																   __byte bSizeToWriteByte, __byte *pInputBuffer);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __char Int8Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sword Int16Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sdword Int32Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_sQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __sqword Int64Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uByte(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __byte uInt8Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uWord(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __word uInt16Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uDword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __dword uInt32Value);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmMmWrite_uQword(PCHAOSVM_CPU pCPU, __word wSeg, __address addrAddress, __qword uInt64Value);

#define __MM_READ_UINT8_SAFE__(pCPU, wSeg, addrAddress, uByte) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_uByte(pCPU, wSeg, addrAddress, &(uByte)))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#define __MM_READ_UINT16_SAFE__(pCPU, wSeg, addrAddress, uWord) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_uWord(pCPU, wSeg, addrAddress, &(uWord)))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#define __MM_READ_UINT32_SAFE__(pCPU, wSeg, addrAddress, uDword) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_uDword(pCPU, wSeg, addrAddress, &(uDword)))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#define __MM_READ_INT8_SAFE__(pCPU, wSeg, addrAddress, sByte) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_sByte(pCPU, wSeg, addrAddress, &(sByte)))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_READ_INT16_SAFE__(pCPU, wSeg, addrAddress, sWord) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_sWord(pCPU, wSeg, addrAddress, &(sWord)))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_READ_INT32_SAFE__(pCPU, wSeg, addrAddress, sDword) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmRead_sDword(pCPU, wSeg, addrAddress, &(sDword)))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_UINT8_SAFE__(pCPU, wSeg, addrAddress, uByte) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_uByte(pCPU, wSeg, addrAddress, uByte))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_UINT16_SAFE__(pCPU, wSeg, addrAddress, uWord) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_uWord(pCPU, wSeg, addrAddress, uWord))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_UINT32_SAFE__(pCPU, wSeg, addrAddress, uDword) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_uDword(pCPU, wSeg, addrAddress, uDword))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_INT8_SAFE__(pCPU, wSeg, addrAddress, sByte) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_sByte(pCPU, wSeg, addrAddress, sByte))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_INT16_SAFE__(pCPU, wSeg, addrAddress, sWord) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_sWord(pCPU, wSeg, addrAddress, sWord))) {\
	return __GET_LAST_STATUS__(pCPU);}}


#define __MM_WRITE_INT32_SAFE__(pCPU, wSeg, addrAddress, sDword) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWrite_sDword(pCPU, wSeg, addrAddress, sDword))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#define __MM_READ_BLOCK_SAFE__(pCPU, wSeg, addrAddress, bSizeToReadByte, pOutputBuffer) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmReadBlockAndSetInterrupt(pCPU, wSeg, addrAddress, bSizeToReadByte, pOutputBuffer))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#define __MM_WRITE_BLOCK_SAFE__(pCPU, wSeg, addrAddress, bSizeToWriteByte, pInputBuffer) {\
	if (!__CPU_STATUS_SUCCESS__(ChaosVmMmWriteBlockAndSetInterrupt(pCPU, wSeg, addrAddress, bSizeToWriteByte, pInputBuffer))) {\
	return __GET_LAST_STATUS__(pCPU);}}

#endif

