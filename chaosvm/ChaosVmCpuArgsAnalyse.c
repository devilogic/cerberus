__byte g_SibTbl[4] = {1,2,4,8};

MODRM_TABLE_ENTRY_32 g_ModrmTbl32[] = {
	/*00 000*/{0, CHAOSVM_R_EAX, __DISP_INVALID__},
	/*00 001*/{0, CHAOSVM_R_ECX, __DISP_INVALID__},
	/*00 010*/{0, CHAOSVM_R_EDX, __DISP_INVALID__},
	/*00 011*/{0, CHAOSVM_R_EBX, __DISP_INVALID__},
	/*00 100*/{1, __REG_INVALID__, __DISP_INVALID__},
	/*00 101*/{0, __REG_INVALID__, __DISP_SIZE_32__},
	/*00 110*/{0, CHAOSVM_R_ESI, __DISP_INVALID__},
	/*00 111*/{0, CHAOSVM_R_EDI, __DISP_INVALID__},

	/*01 000*/{0, CHAOSVM_R_EAX, __DISP_SIZE_8__},
	/*01 001*/{0, CHAOSVM_R_ECX, __DISP_SIZE_8__},
	/*01 010*/{0, CHAOSVM_R_EDX, __DISP_SIZE_8__},
	/*01 011*/{0, CHAOSVM_R_EBX, __DISP_SIZE_8__},
	/*01 100*/{1, __REG_INVALID__, __DISP_SIZE_8__},
	/*01 101*/{0, CHAOSVM_R_EBP, __DISP_SIZE_8__},
	/*01 110*/{0, CHAOSVM_R_ESI, __DISP_SIZE_8__},
	/*01 111*/{0, CHAOSVM_R_EDI, __DISP_SIZE_8__},

	/*10 000*/{0, CHAOSVM_R_EAX, __DISP_SIZE_32__},
	/*10 001*/{0, CHAOSVM_R_ECX, __DISP_SIZE_32__},
	/*10 010*/{0, CHAOSVM_R_EDX, __DISP_SIZE_32__},
	/*10 011*/{0, CHAOSVM_R_EBX, __DISP_SIZE_32__},
	/*10 100*/{1, __REG_INVALID__, __DISP_SIZE_32__},
	/*10 101*/{0, CHAOSVM_R_EBP, __DISP_SIZE_32__},
	/*10 110*/{0, CHAOSVM_R_ESI, __DISP_SIZE_32__},
	/*10 111*/{0, CHAOSVM_R_EDI, __DISP_SIZE_32__},

	/*11 000*/{0, CHAOSVM_R_EAX, __DISP_INVALID__},
	/*11 001*/{0, CHAOSVM_R_ECX, __DISP_INVALID__},
	/*11 010*/{0, CHAOSVM_R_EDX, __DISP_INVALID__},
	/*11 011*/{0, CHAOSVM_R_EBX, __DISP_INVALID__},
	/*11 100*/{0, CHAOSVM_R_ESP, __DISP_INVALID__},
	/*11 101*/{0, CHAOSVM_R_EBP, __DISP_INVALID__},
	/*11 110*/{0, CHAOSVM_R_ESI, __DISP_INVALID__},
	/*11 111*/{0, CHAOSVM_R_EDI, __DISP_INVALID__}
};

MODRM_TABLE_ENTRY_16 g_ModrmTbl16[] = {
	{{CHAOSVM_R_EBX, CHAOSVM_R_ESI}, __DISP_INVALID__},
	{{CHAOSVM_R_EBX, CHAOSVM_R_EDI}, __DISP_INVALID__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_ESI}, __DISP_INVALID__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_EDI}, __DISP_INVALID__},
	{{CHAOSVM_R_ESI, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_EDI, __REG_INVALID__}, __DISP_INVALID__},
	{{__REG_INVALID__, __REG_INVALID__}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBX, __REG_INVALID__}, __DISP_INVALID__},

	{{CHAOSVM_R_EBX, CHAOSVM_R_ESI}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EBX, CHAOSVM_R_EDI}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_ESI}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_EDI}, __DISP_SIZE_8__},
	{{CHAOSVM_R_ESI, __REG_INVALID__}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EDI, __REG_INVALID__}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EBP, __REG_INVALID__}, __DISP_SIZE_8__},
	{{CHAOSVM_R_EBX, __REG_INVALID__}, __DISP_SIZE_8__},

	{{CHAOSVM_R_EBX, CHAOSVM_R_ESI}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBX, CHAOSVM_R_EDI}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_ESI}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBP, CHAOSVM_R_EDI}, __DISP_SIZE_16__},
	{{CHAOSVM_R_ESI, __REG_INVALID__}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EDI, __REG_INVALID__}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBP, __REG_INVALID__}, __DISP_SIZE_16__},
	{{CHAOSVM_R_EBX, __REG_INVALID__}, __DISP_SIZE_16__},

	{{CHAOSVM_R_EAX, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_ECX, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_EDX, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_EBX, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_ESP, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_EBP, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_ESI, __REG_INVALID__}, __DISP_INVALID__},
	{{CHAOSVM_R_EDI, __REG_INVALID__}, __DISP_INVALID__},
};

/*
 * 分析32寻址模式下的ModRM和SIB位
 * 返回值:
 * 成功解析           CPU_STATUS_EXECUTE_SUCCESS
 * 解析结果长度不正确 CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT
 *
 * 注:需确保pModRMRegByte指向的内存至少有12字节可读取，否则将引发读取异常
 */
CPU_STATUS __INTERNAL_FUNC__ GetInstructionArgs32(PCHAOSVM_CPU pCPU, __byte *pModRMRegByte, __byte bDataLength, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte Len = 0;
	__address addrAddress = 0;
	__byte bModRMTableIndex = 0;
	__dword dwDisplacement = 0;
	__byte bModRMReg = *(__byte *)pModRMRegByte;

	//__PrintDbgInfo_DebugerBreakPoint__("Entry GetInstructionArgs32", pCPU);

	/*
	 * 重建ModRM
	 */
	__logic_memset__(pArgs, 0, sizeof(CPU_INSTRUCTION_ARGS));
	bModRMReg = pCPU->pBuildModrm(pCPU, pCPU->pUserContext, bModRMReg);
	pArgs->bRegOpcode = (bModRMReg & 0x38) >> 3;
	bModRMTableIndex = (((bModRMReg & 0xC0) >> 3) | (bModRMReg & 0x7)); 

	/*
	 * 对SIB位存在的情况单独处理
	 * SIB存在时,RegisterIndex和Disp域均无效
	 */
	if (g_ModrmTbl32[bModRMTableIndex].bIsSibExist) {
		__byte SIBByte = 0;
		__byte Scale = 0;
		__byte Index = 0;
		__byte Base = 0;

		SIBByte = *((__byte *)(pModRMRegByte + 1));
		/* 
		 * 重建SIB
		 */
		SIBByte = pCPU->pBuildSib(pCPU, pCPU->pUserContext, SIBByte);
		Scale = (SIBByte & 0xC0) >> 6;
		Index = (SIBByte & 0x38) >> 3;
		Base = SIBByte & 0x7;

		pArgs->bIsEAReg = 0;
		/*
		 * 处理 MOD=0 && BASE = 5 的情况
		 */
		if ((0 == ((bModRMReg & 0xC0) >> 3)) && (5 == Base)) {
			__READ_DISP_INT32_SAFE__(pCPU, pModRMRegByte + 2, dwDisplacement);
			addrAddress = __CPU_GR32__(pCPU ,Index) * g_SibTbl[Scale];
			addrAddress = __CalculateFinalAddress_Offset_32Bits__(addrAddress, dwDisplacement);
			Len = 6; /*1 + 1 + 4*/
		} else {
			if (CHAOSVM_R_ESP == Index)
				addrAddress = 0;
			else
				addrAddress = __CPU_GR32__(pCPU ,Index) * g_SibTbl[Scale];
			addrAddress += __CPU_GR32__(pCPU ,Base);

			switch(g_ModrmTbl32[bModRMTableIndex].bDisp) {
			//case __DISP_SIZE_8__: sdwDisplacement = *((__byte *)(pModRMRegByte + 2));break;	
			//case __DISP_SIZE_16__: sdwDisplacement = *((__word *)(pModRMRegByte + 2));break;	
			//case __DISP_SIZE_32__: sdwDisplacement = *((__dword *)(pModRMRegByte + 2));break;
			case __DISP_SIZE_8__: {
				__READ_DISP_INT8_SAFE__(pCPU, pModRMRegByte + 2, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_8Bits__(addrAddress, dwDisplacement);
			}break;
			case __DISP_SIZE_16__: {
				__READ_DISP_INT16_SAFE__(pCPU, pModRMRegByte + 2, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_16Bits__(addrAddress, dwDisplacement);
			}break;
			case __DISP_SIZE_32__: {
				__READ_DISP_INT32_SAFE__(pCPU, pModRMRegByte + 2, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_32Bits__(addrAddress, dwDisplacement);
			}break;
			default: dwDisplacement = 0;
			}
			Len = 2 + g_ModrmTbl32[bModRMTableIndex].bDisp;
		}
		pArgs->EffectiveAddress.addrAddress = addrAddress;
	} else {
		/*
		 * Mod = 3 的情况单独处理
		 * 此时EffactiveAddress是寄存器
		 */
		if (3 == ((bModRMReg & 0xC0) >> 6)) {
			Len = 1;
			pArgs->bIsEAReg = 1;
			pArgs->EffectiveAddress.bRegIndex = g_ModrmTbl32[bModRMTableIndex].bRegisterIndex;
		} else {
			/*
			 * 处理__REG_INVALID__
			 */
			if (g_ModrmTbl32[bModRMTableIndex].bRegisterIndex != __REG_INVALID__) {
				addrAddress = __CPU_GR32__(pCPU , g_ModrmTbl32[bModRMTableIndex].bRegisterIndex);
			} else
				addrAddress = 0;

			switch(g_ModrmTbl32[bModRMTableIndex].bDisp)
			{
			//case __DISP_SIZE_8__: sdwDisplacement = *((__byte *) (pModRMRegByte + 1));break;	
			//case __DISP_SIZE_16__: sdwDisplacement = *((__word *)(pModRMRegByte + 1));break;	
			//case __DISP_SIZE_32__: sdwDisplacement = *((__dword *) (pModRMRegByte + 1));break;
			case __DISP_SIZE_8__: {
				__READ_DISP_INT8_SAFE__(pCPU, pModRMRegByte + 1, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_8Bits__(addrAddress, dwDisplacement);
			}break;
			case __DISP_SIZE_16__: {
				__READ_DISP_INT16_SAFE__(pCPU, pModRMRegByte + 1, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_16Bits__(addrAddress, dwDisplacement);
								   }break;
			case __DISP_SIZE_32__: {
				__READ_DISP_INT32_SAFE__(pCPU, pModRMRegByte + 1, dwDisplacement);
				addrAddress = __CalculateFinalAddress_Offset_32Bits__(addrAddress, dwDisplacement);
			}break;
			default: dwDisplacement = 0;
			}

			pArgs->bIsEAReg = 0;
			pArgs->EffectiveAddress.addrAddress = addrAddress;

			Len = 1 + g_ModrmTbl32[bModRMTableIndex].bDisp;
		}
	}
	pArgs->bLength = Len;
	if (pArgs->bLength > bDataLength)
		return __CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT__;

	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * 分析16寻址模式下的ModRM位
 * 返回值:
 * 成功解析           CPU_STATUS_EXECUTE_SUCCESS
 * 解析结果长度不正确 CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT
 *
 * 注:需确保pModRMRegByte指向的内存至少有12字节可读取，否则将引发读取异常
 */
CPU_STATUS __INTERNAL_FUNC__ GetInstructionArgs16(PCHAOSVM_CPU pCPU, __byte *pModRMRegByte, __byte bDataLength, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte Len = 0;
	__word uInt16Address = 0;
	__byte bModRMTableIndex;
	__word wDisplacement = 0;
	__byte bModRMReg = *(__byte *)pModRMRegByte;

	//__PrintDbgInfo_DebugerBreakPoint__("Entry GetInstructionArgs16", pCPU);

	/*
	 * 重建ModRM
	 */
	__logic_memset__(pArgs, 0, sizeof(CPU_INSTRUCTION_ARGS));
	bModRMReg = pCPU->pBuildModrm(pCPU, pCPU->pUserContext, bModRMReg);
	pArgs->bRegOpcode = (bModRMReg & 0x38) >> 3;
	bModRMTableIndex = (((bModRMReg & 0xC0) >> 3) | (bModRMReg & 0x7)); 

	/*
	 * Mod=3的情况
	 */
	if (3 == ((bModRMReg & 0xC0) >> 6)) {
		Len = 1;
		pArgs->bIsEAReg = 1;
		pArgs->EffectiveAddress.bRegIndex = g_ModrmTbl16[bModRMTableIndex].RegisterIndex[0];
	} else {
		uInt16Address = 0;
		if (__REG_INVALID__ != g_ModrmTbl16[bModRMTableIndex].RegisterIndex[0]) {
			uInt16Address = uInt16Address + __CPU_GR16__(pCPU, g_ModrmTbl16[bModRMTableIndex].RegisterIndex[0]);

			if(__REG_INVALID__ != g_ModrmTbl16[bModRMTableIndex].RegisterIndex[1])
				uInt16Address = uInt16Address + __CPU_GR16__(pCPU, g_ModrmTbl16[bModRMTableIndex].RegisterIndex[1]);
		}

		switch (g_ModrmTbl16[bModRMTableIndex].bDisp) {
		//case __DISP_SIZE_8__: swDisplacement = *((__byte *)(pModRMRegByte + 1));break;	
		//case __DISP_SIZE_16__: swDisplacement = *((__word *)(pModRMRegByte + 1));break;
		case __DISP_SIZE_8__: {
			__READ_DISP_INT8_SAFE__(pCPU, pModRMRegByte + 1, wDisplacement);
			uInt16Address = (__word)__CalculateFinalAddress_Offset_8Bits__(uInt16Address, wDisplacement);
		}break;
		case __DISP_SIZE_16__: {
			__READ_DISP_INT16_SAFE__(pCPU, pModRMRegByte + 1, wDisplacement);
			uInt16Address = (__word)__CalculateFinalAddress_Offset_16Bits__(uInt16Address, wDisplacement);
		}break;
		default: wDisplacement = 0;
		}
		pArgs->bIsEAReg = 0;
		pArgs->EffectiveAddress.addrAddress = (__address)UINT16_TO_UINT32(uInt16Address);

		Len = 1 + g_ModrmTbl16[bModRMTableIndex].bDisp;
	}
	pArgs->bLength = Len;

	if (pArgs->bLength > bDataLength)
		return __CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT__;

	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ GetInstructionArgsLength32(PCHAOSVM_CPU pCPU, __byte *pModRMRegByte, __byte bDataLength, __byte *pLength) {
	__byte Len = 0;
	__byte bModRMTableIndex;
	__byte bModRMReg = *(__byte *)pModRMRegByte;
	/*
	 * 重建ModRM
	 */
	bModRMReg = pCPU->pBuildModrm(pCPU, pCPU->pUserContext, bModRMReg);
	bModRMTableIndex = (((bModRMReg & 0xC0) >> 3) | (bModRMReg & 0x7)); 

	/*
	 * 对SIB位存在的情况单独处理
	 * SIB存在时,RegisterIndex和Disp域均无效
	 */
	if (g_ModrmTbl32[bModRMTableIndex].bIsSibExist) {
		__byte SIBByte = 0;
		__byte Base = 0;

		SIBByte = *((__byte *)(pModRMRegByte + 1));
		/*
		 * 重建SIB
		 */
		SIBByte = pCPU->pBuildSib(pCPU, pCPU->pUserContext, SIBByte);
		Base = SIBByte & 0x7;

		/*
		 * 处理 MOD=0 &&BASE = 5 的情况
		 */
		if ((0 == ((bModRMReg & 0xC0) >> 3)) && (5 == Base))
			Len = 6; /*1 + 1 + 4*/
		else
			Len = 2 + g_ModrmTbl32[bModRMTableIndex].bDisp;
	} else {
		/*
		 * Mod = 3 的情况单独处理
		 * 此时EffactiveAddress是寄存器
		 */
		if (3 == ((bModRMReg & 0xC0) >> 6))
			Len = 1;
		else
			Len = 1 + g_ModrmTbl32[bModRMTableIndex].bDisp;
	}

	if (Len > bDataLength)
		return __CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT__;

	*pLength = Len;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ GetInstructionArgsLength16(PCHAOSVM_CPU pCPU, __byte *pModRMRegByte, __byte bDataLength, __byte *pLength) {
	__byte Len = 0;
	__byte bModRMTableIndex;
	__byte bModRMReg = *(__byte *)pModRMRegByte ;
	/*
	 * 重建ModRM
	 */
	bModRMReg = pCPU->pBuildModrm(pCPU, pCPU->pUserContext, bModRMReg);
	bModRMTableIndex = (((bModRMReg & 0xC0) >> 3) | (bModRMReg & 0x7)); 

	/*
	 * Mod=3的情况
	 */
	if (3 == ((bModRMReg & 0xC0) >> 6))
		Len = 1;
	else
		Len = 1 + g_ModrmTbl16[bModRMTableIndex].bDisp;

	if (Len > bDataLength)
		return __CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT__;

	*pLength = Len;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}
