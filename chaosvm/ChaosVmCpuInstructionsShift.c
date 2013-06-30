/*
 * 本文件包含移位指令的相关宏和实现函数
 */
/*
 * 循环移位区别于一般移位的是移位时没有数位的丢失。循环左移时，用从左边移出的位填充字的右端，
 * 而循环右移时，用从右边移出的位填充字的左侧。这种情况在系统程序中时有使用，在一些控制程序
 * 中用得也不少。
 *
 * 设有数据说明： unsigned char a,b；现要把a循环移位2位，可以用如下语句段完成：
 *
 * b=a>>(8-2);用来得到正常左移丢失的位和循环移位后其正确位置
 *
 * a=a<<2;左移
 *
 * a=a|b;
 *
 * => a = (a<<2)|(a>>(8-2));
 *
 *
 */
/*
 * 循环移位指令的实现
 */

/*
 *
 *Operation
 *
 * (* RCL and RCR instructions *)
 * SIZE ← OperandSize;
 * CASE (determine count) OF
 * SIZE ← 8: tempCOUNT ← (COUNT AND 1FH) MOD 9;
 * SIZE ← 16: tempCOUNT ← (COUNT AND 1FH) MOD 17;
 * SIZE ← 32: tempCOUNT ← COUNT AND 1FH;
 * SIZE ← 64: tempCOUNT ← COUNT AND 3FH;
 * ESAC;
 *
 * (* RCL instruction operation *)
 * WHILE (tempCOUNT ≠ 0) 
 * DO
 * bTempCF ← MSB(DEST);
 * DEST ← (DEST * 2) + CF;
 * CF ← bTempCF;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 * ELIHW;
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR CF;
 * ELSE OF is undefined;
 * FI;
 *
 * (* RCR instruction operation *)
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR CF;
 * ELSE OF is undefined;
 * FI;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * bTempCF ← LSB(SRC);
 * DEST ← (DEST / 2) + (CF * 2SIZE);
 * CF ← bTempCF;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 * (* ROL and ROR instructions *)
 * SIZE ← OperandSize;
 * CASE (determine count) OF
 * SIZE ← 8: tempCOUNT ← (COUNT AND 1FH) MOD 8; (* Mask count before MOD *)
 * SIZE ← 16: tempCOUNT ← (COUNT AND 1FH) MOD 16;
 * SIZE ← 32: tempCOUNT ← (COUNT AND 1FH) MOD 32;
 * SIZE ← 64: tempCOUNT ← (COUNT AND 1FH) MOD 64;
 * ESAC;
 *
 * (* ROL instruction operation *)
 * IF (tempCOUNT > 0) (* Prevents updates to CF *)
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * bTempCF ← MSB(DEST);
 * DEST ← (DEST * 2) + bTempCF;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 * ELIHW;
 * CF ← LSB(DEST);
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR CF;
 * ELSE OF is undefined;
 * FI;
 * FI;
 *
 * (* ROR instruction operation *)
 * IF tempCOUNT > 0) (* Prevent updates to CF *)
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * bTempCF ← LSB(SRC);
 * DEST ← (DEST / 2) + (bTempCF * 2SIZE);
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 * ELIHW;
 * CF ← MSB(DEST);
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR MSB - 1(DEST);
 * ELSE OF is undefined;
 * FI;
 * FI;
 *
 *
 * Flags Affected
 * The CF flag contains the value of the bit shifted into it. The OF flag is affected only for singlebit
 * rotates (see “Description” above); it is undefined for multi-bit rotates. The SF, ZF, AF, and
 * PF flags are not affected.
 */

/*
 * ROL指令实现(包括对标志寄存器的修改)
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalROL8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 8;
	if (bInt8ShitftCount) {
		bInt8Value = (bInt8Value << bInt8ShitftCount) | ( (bInt8Value >> (8 - bInt8ShitftCount)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT8_LSB__(bInt8Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT8_MSB__(bInt8Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalROL16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 16;
	if (bInt8ShitftCount) {
		wInt16Value = (wInt16Value << bInt8ShitftCount) | ((wInt16Value >> (16 - bInt8ShitftCount)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT16_LSB__(wInt16Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT16_MSB__(wInt16Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalROL32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 32;
	if (bInt8ShitftCount) {
		dwInt32Value = (dwInt32Value << bInt8ShitftCount) | ( (dwInt32Value >> (32 - bInt8ShitftCount)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT32_LSB__(dwInt32Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT32_MSB__(dwInt32Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return dwInt32Value;
}


/*
 * ROR指令实现(包括对标志寄存器的修改)
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalROR8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 8;
	if (bInt8ShitftCount) {
		bInt8Value = (bInt8Value >> bInt8ShitftCount)  | ( (bInt8Value << (8 - bInt8ShitftCount)) );
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT8_MSB__(bInt8Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT8_MSB__(bInt8Value) ^ __UINT8_MSB_1__(bInt8Value);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalROR16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 16;
	if (bInt8ShitftCount) {
		wInt16Value = (wInt16Value >> bInt8ShitftCount)  | ((wInt16Value << (16 - bInt8ShitftCount)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wInt16Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT16_MSB__(wInt16Value) ^ __UINT16_MSB_1__(wInt16Value);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalROR32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 32;
	if (bInt8ShitftCount) {
		dwInt32Value = (dwInt32Value >> bInt8ShitftCount) | ((dwInt32Value << (32 - bInt8ShitftCount)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwInt32Value)));
		if (1 == bInt8ShitftBits) {
			__byte bOFTmp = __UINT32_MSB__(dwInt32Value) ^ __UINT32_MSB_1__(dwInt32Value);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
		} else {
			__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		}
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return dwInt32Value;
}

/*
 * RCL指令实现(包括对标志寄存器的修改)
 * Operation
 *
 *
 * SIZE ← OperandSize;
 * CASE (determine count) OF
 * SIZE ← 8: tempCOUNT ← (COUNT AND 1FH) MOD 9;
 * SIZE ← 16: tempCOUNT ← (COUNT AND 1FH) MOD 17;
 * SIZE ← 32: tempCOUNT ← COUNT AND 1FH;
 * SIZE ← 64: tempCOUNT ← COUNT AND 3FH;
 * ESAC;
 *
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * bTempCF ← MSB(DEST);
 * DEST ← (DEST * 2) + CF;
 * CF ← bTempCF;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 * ELIHW;
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR CF;
 * ELSE OF is undefined;
 * FI;
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalRCL8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 9;
	while (bInt8ShitftCount) {
		bTempCF = __UINT8_MSB__(bInt8Value);
		bInt8Value = bInt8Value * 2 + bTempCF;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	} 
	
	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT8_MSB__(bInt8Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalRCL16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 17;
	while (bInt8ShitftCount) {
		bTempCF = __UINT16_MSB__(wInt16Value);
		wInt16Value = wInt16Value * 2 + bTempCF;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	}

	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT16_MSB__(wInt16Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalRCL32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 0x1F;
	while (bInt8ShitftCount) {
		bTempCF = __UINT32_MSB__(dwInt32Value);
		dwInt32Value = dwInt32Value * 2 + bTempCF;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	}

	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT32_MSB__(dwInt32Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}
	return dwInt32Value;
}

/*
 * RCR指令实现(包括对标志寄存器的修改)
 * Operation
 *
 *
 * SIZE ← OperandSize;
 * CASE (determine count) OF
 * SIZE ← 8: tempCOUNT ← (COUNT AND 1FH) MOD 9;
 * SIZE ← 16: tempCOUNT ← (COUNT AND 1FH) MOD 17;
 * SIZE ← 32: tempCOUNT ← COUNT AND 1FH;
 * SIZE ← 64: tempCOUNT ← COUNT AND 3FH;
 * ESAC;
 *
 *
 * IF COUNT = 1
 * THEN OF ← MSB(DEST) XOR CF;
 * ELSE OF is undefined;
 * FI;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * bTempCF ← LSB(SRC);
 * DEST ← (DEST / 2) + (CF * 2SIZE);
 * CF ← bTempCF;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalRCR8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 9;
	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT8_MSB__(bInt8Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	while (bInt8ShitftCount) {
		bTempCF = __UINT8_LSB__(bInt8Value);
		bInt8Value = bInt8Value / 2 + bTempCF * 2 * 8;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	}

	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalRCR16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 17;
	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT16_MSB__(wInt16Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	while (bInt8ShitftCount) {
		bTempCF = __UINT16_LSB__(wInt16Value);
		wInt16Value = wInt16Value / 2 + bTempCF * 2 * 16;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	}

	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalRCR32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bTempCF;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F) % 17;
	if (1 == bInt8ShitftBits) {
		__byte bOFTmp = __UINT32_MSB__(dwInt32Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	while (bInt8ShitftCount) {
		bTempCF = __UINT32_LSB__(dwInt32Value);
		dwInt32Value = dwInt32Value / 2 + bTempCF * 2 * 16;
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(bTempCF));
		bInt8ShitftCount--;
	}

	return dwInt32Value;
}


/*
 * 算术移位指令的实现
 *
 * IF 64-Bit Mode and using REX.W
 * THEN
 * countMASK ← 3FH;
 * ELSE
 * countMASK ← 1FH;
 * FI
 * tempCOUNT ← (COUNT AND countMASK);
 * tempDEST ← DEST;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * IF instruction is SAL or SHL
 * THEN
 * CF ← MSB(DEST);
 * ELSE (* Instruction is SAR or SHR *)
 * CF ← LSB(DEST);
 * FI;
 * IF instruction is SAL or SHL
 * THEN
 * DEST ← DEST * 2;
 * ELSE
 * IF instruction is SAR
 * THEN
 * DEST ← DEST / 2; (* Signed divide, rounding toward negative infinity *)
 * ELSE (* Instruction is SHR *)
 * DEST ← DEST / 2 ; (* Unsigned divide *)
 * FI;
 * FI;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 *
 * (* Determine overflow for the various instructions *)
 * IF (COUNT and countMASK) = 1
 * THEN
 * IF instruction is SAL or SHL
 * THEN
 * OF ← MSB(DEST) XOR CF;
 * ELSE
 * IF instruction is SAR
 * THEN
 * OF ← 0;
 * ELSE (* Instruction is SHR *)
 * OF ← MSB(tempDEST);
 * FI;
 * FI;
 * ELSE IF (COUNT AND countMASK) = 0
 * THEN
 * All flags unchanged;
 * ELSE (* COUNT not 1 or 0 *)
 * OF ← undefined;
 * FI;
 * FI;
 *
 * Flags Affected
 * The CF flag contains the value of the last bit shifted out of the destination operand; it is undefined
 * for SHL and SHR instructions where the count is greater than or equal to the size (in bits)
 * of the destination operand. The OF flag is affected only for 1-bit shifts (see “Description”
 * above); otherwise, it is undefined. The SF, ZF, and PF flags are set according to the result. If the
 * count is 0, the flags are not affected. For a non-zero count, the AF flag is undefined.
 *
 * The OF flag is affected only on 1-bit shifts. For left shifts, the OF flag is set to 0 if the mostsignificant
 * bit of the result is the same as the CF flag (that is, the top two bits of the original
 * operand were the same); otherwise, it is set to 1. For the SAR instruction, the OF flag is cleared
 * for all 1-bit shifts. For the SHR instruction, the OF flag is set to the most-significant bit of the
 * original operand.
 *
 */

/*
 * SHL指令的实现
 *
 * IF 64-Bit Mode and using REX.W
 * THEN
 * countMASK ← 3FH;
 * ELSE
 * countMASK ← 1FH;
 * FI
 * tempCOUNT ← (COUNT AND countMASK);
 * tempDEST ← DEST;
 *
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * CF ← MSB(DEST);
 * DEST ← DEST * 2;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 *
 * (* Determine overflow for the various instructions *)
 * IF (COUNT and countMASK) = 1
 * THEN
 * OF ← MSB(DEST) XOR CF;
 * ELSE IF (COUNT AND countMASK) = 0
 * THEN
 * All flags unchanged;
 * ELSE (* COUNT not 1 or 0 *)
 * OF ← undefined;
 * FI;
 * FI;
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalSHL8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);
	for (; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT8_MSB__(bInt8Value)));
		bInt8Value = bInt8Value << 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__byte bOFTmp;
		bOFTmp = __UINT8_MSB__(bInt8Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*All flags unchanged*/
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(bInt8Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (bInt8Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(bInt8Value));
	}
	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalSHL16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);
	for (; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wInt16Value)));
		wInt16Value = wInt16Value << 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__byte bOFTmp;
		bOFTmp = __UINT16_MSB__(wInt16Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*The SF, ZF, and PF flags are set according to the result. */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(wInt16Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (wInt16Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wInt16Value));
	}

	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalSHL32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);
	for(; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwInt32Value)));
		dwInt32Value = dwInt32Value << 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__byte bOFTmp;
		bOFTmp = __UINT32_MSB__(dwInt32Value) ^ __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(bOFTmp));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(dwInt32Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (dwInt32Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwInt32Value));
	}

	return dwInt32Value;
}

/*
 * SAL指令的实现
 * IF 64-Bit Mode and using REX.W
 * THEN
 * countMASK ← 3FH;
 * ELSE
 * countMASK ← 1FH;
 * FI
 * tempCOUNT ← (COUNT AND countMASK);
 * tempDEST ← DEST;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * CF ← MSB(DEST);
 * DEST ← DEST * 2;
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 *
 * (* Determine overflow for the various instructions *)
 * IF (COUNT and countMASK) = 1
 * THEN
 * OF ← MSB(DEST) XOR CF;
 * ELSE IF (COUNT AND countMASK) = 0
 * THEN
 * All flags unchanged;
 * ELSE (* COUNT not 1 or 0 *)
 * OF ← undefined;
 * FI;
 * FI;
 *
 * 与SHL的算法一样
 */
#define __InternalSAL8__(pCPU, bInt8Value, bInt8ShitftBits)		InternalSHL8(pCPU, INT8_TO_UINT8(bInt8Value), bInt8ShitftBits)
#define __InternalSAL16__(pCPU, wInt16Value, bInt8ShitftBits)    InternalSHL16(pCPU, INT16_TO_UINT16(wInt16Value), bInt8ShitftBits)
#define __InternalSAL32__(pCPU, dwInt32Value, bInt8ShitftBits)    InternalSHL32(pCPU, INT32_TO_UINT32(dwInt32Value), bInt8ShitftBits)

/*
 * SHR指令的实现
 *
 * IF 64-Bit Mode and using REX.W
 * THEN
 * countMASK ← 3FH;
 * ELSE
 * countMASK ← 1FH;
 * FI
 * tempCOUNT ← (COUNT AND countMASK);
 * tempDEST ← DEST;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * CF ← LSB(DEST);
 * DEST ← DEST / 2 ; (* Unsigned divide *)
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 *
 * (* Determine overflow for the various instructions *)
 * IF (COUNT and countMASK) = 1
 * THEN
 * OF ← MSB(tempDEST);
 * ELSE IF (COUNT AND countMASK) = 0
 * THEN
 * All flags unchanged;
 * ELSE (* COUNT not 1 or 0 *)
 * OF ← undefined;
 * FI;
 * FI;
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalSHR8(PCHAOSVM_CPU pCPU, __byte bInt8Value, __byte bInt8ShitftBits) {
	__byte uInt8ValueBak = bInt8Value;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	for (; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT8_LSB__(bInt8Value)));
		bInt8Value = bInt8Value >> 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(__UINT8_MSB__(uInt8ValueBak)));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(bInt8Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (bInt8Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(bInt8Value));
	}

	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalSHR16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__word uInt16ValueBak = wInt16Value;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	for(; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT16_LSB__(wInt16Value)));
		wInt16Value = wInt16Value >> 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(uInt16ValueBak)));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(wInt16Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (wInt16Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wInt16Value));
	}

	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalSHR32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__dword uInt32ValueBak = dwInt32Value;
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	for (; bInt8ShitftCount; bInt8ShitftCount--) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT32_LSB__(dwInt32Value)));
		dwInt32Value = dwInt32Value >> 1;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(uInt32ValueBak)));
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(dwInt32Value));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (dwInt32Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwInt32Value));
	}

	return dwInt32Value;
}

/*
 * SAR指令的实现
 * IF 64-Bit Mode and using REX.W
 * THEN
 * countMASK ← 3FH;
 * ELSE
 * countMASK ← 1FH;
 * FI
 * tempCOUNT ← (COUNT AND countMASK);
 * tempDEST ← DEST;
 * WHILE (tempCOUNT ≠ 0)
 * DO
 * CF ← LSB(DEST);
 * DEST ← DEST / 2; (* Signed divide, rounding toward negative infinity *)
 * tempCOUNT ← tempCOUNT – 1;
 * OD;
 *
 *
 * (* Determine overflow for the various instructions *)
 * IF (COUNT and countMASK) = 1
 * THEN
 * OF ← 0;
 * ELSE IF (COUNT AND countMASK) = 0
 * THEN
 * All flags unchanged;
 * ELSE (* COUNT not 1 or 0 *)
 * OF ← undefined;
 * FI;
 * FI;
 */
__INLINE__ __char __INTERNAL_FUNC__ InternalSAR8(PCHAOSVM_CPU pCPU, __char bInt8Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	while (bInt8ShitftCount) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT8_LSB__(INT8_TO_UINT8(bInt8Value))));
		bInt8Value = bInt8Value / 2;
		bInt8ShitftCount--;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected.
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(INT8_TO_UINT8(bInt8Value)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (bInt8Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(INT8_TO_UINT8(bInt8Value)));
	}

	return bInt8Value;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalSAR16(PCHAOSVM_CPU pCPU, __word wInt16Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	while (bInt8ShitftCount) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT16_LSB__(INT16_TO_UINT16(wInt16Value))));
		wInt16Value = wInt16Value / 2;
		bInt8ShitftCount--;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected.
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(INT16_TO_UINT16(wInt16Value)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (wInt16Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(INT16_TO_UINT16(wInt16Value)));
	}

	return wInt16Value;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalSAR32(PCHAOSVM_CPU pCPU, __dword dwInt32Value, __byte bInt8ShitftBits) {
	__byte bInt8ShitftCount;
	bInt8ShitftCount = (bInt8ShitftBits & 0x1F);

	while (bInt8ShitftCount) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(__UINT32_LSB__(INT32_TO_UINT32(dwInt32Value))));
		dwInt32Value = dwInt32Value / 2;
		bInt8ShitftCount--;
	}

	if (1 == (bInt8ShitftBits & 0x1F)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	} else if (0 == (bInt8ShitftBits & 0x1F)) {
		/*
		 * All flags unchanged
		 */
	} else {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
	}

	/*
	 * For a non-zero count, the AF flag is undefined.
	 */
	if (bInt8ShitftBits) {
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	}

	if (0 == bInt8ShitftBits) {
		/*
		 * If the count is 0, the flags are not affected. 
		 */
	} else {
		/*
		 * The SF, ZF, and PF flags are set according to the result. 
		 */
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(INT32_TO_UINT32(dwInt32Value)));
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (dwInt32Value) ? __EFLAG_RESET__ : __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(INT32_TO_UINT32(dwInt32Value)));
	}

	return dwInt32Value;
}

#define __InternalSAR_uByte__(pCPU, bInt8Value, bInt8ShitftBits)		INT8_TO_UINT8( InternalSAR8(pCPU, UINT8_TO_INT8(bInt8Value), bInt8ShitftBits))
#define __InternalSAR_uWord__(pCPU, wInt16Value, bInt8ShitftBits)		INT16_TO_UINT16( InternalSAR16(pCPU, UINT16_TO_INT16(wInt16Value), bInt8ShitftBits))
#define __InternalSAR_uDword__(pCPU, dwInt32Value, bInt8ShitftBits)		INT32_TO_UINT32( InternalSAR32(pCPU, UINT32_TO_INT32(dwInt32Value), bInt8ShitftBits))

/*
 * C0 XX 
 * XXX  r/m8, imm8
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_C0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_C0", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_C0_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ROL r/m8, imm8    Rotate 8 bits r/m8 left imm8 times.
	 */
	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_C0_0", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength+1+pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_C0_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ROR r/m8, imm8     Rotate 8 bits r/m16 right imm8 times.
	 */
	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_C0_1", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_C0_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_C0_2", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_C0_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_C0_3", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_C0_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SHL r/m8, imm8     Multiply r/m8 by 2, imm8 times.
	 */

	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_C0_4", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_C0_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SHR r/m8, imm8    Unsigned divide r/m8 by 2, imm8 times.
	 */

	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_C0_5", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_C0_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SAR r/m8, imm8    Signed divide* r/m8 by 2, imm8 time.
	 */

	__byte bInt8Tmp;
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_C0_7", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, bInt8Imm);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, bInt8Imm);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_C0(PCHAOSVM_CPU pCPU) {//[C0]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_C0", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryC0[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * C1 XX
 * XXX r/m16, imm8
 * XXX r/m32, imm8
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_C1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_C1", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_C1_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ROL r/m16, imm8    Rotate 16 bits r/m16 left imm8 times.
	 * ROL r/m32, imm8    Rotate 32 bits r/m32 left imm8 times.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_C1_0", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_C1_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_C1_1", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_C1_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_C1_2", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_C1_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_C1_3", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_C1_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SHL r/m16, imm8    Multiply r/m16 by 2, imm8 times.
	 * SHL r/m32, imm8    Multiply r/m32 by 2, imm8 times.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_C1_4", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_C1_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SHR r/m16, imm8    Unsigned divide r/m16 by 2, imm8 times.
	 * 虽然白皮书上未说明，但此处似乎应该也允许32位寄存器
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_C1_5", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_C1_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SAR r/m32, imm8     Signed divide* r/m32 by 2, imm8 times.
	 */
	__byte bInt8Imm;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_C1_7", pCPU);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + pArgs->bLength, bInt8Imm);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, bInt8Imm);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, bInt8Imm);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, bInt8Imm);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, bInt8Imm);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_C1(PCHAOSVM_CPU pCPU) {//[C1]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_C1", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryC1[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * D0 XX
 * XXX r/m8, 1
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_D0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_D0", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_D0_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_D0_0", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_D0_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_D0_1", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_D0_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_D0_2", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_D0_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_D0_3", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_D0_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_D0_4", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_D0_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_D0_5", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_D0_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_D0_7", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, 1);
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, 1);
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_D0(PCHAOSVM_CPU pCPU) {//[D0]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_D0", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryD0[Args.bRegOpcode].DispatchFunction(pCPU, &Args);	

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * D1 XX
 * XXX r/m16, 1
 * XXX r/m32, 1
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_D1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_D1", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_D1_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * ROL r/m16, 1    Rotate 16 bits r/m16 left 1 times.
	 * ROL r/m32, 1    Rotate 32 bits r/m32 left 1 times.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_D1_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_D1_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_D1_1", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_D1_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_D1_2", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_D1_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_D1_3", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_D1_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SHL r/m16, 1    Multiply r/m16 by 2, 1 times.
	 * SHL r/m32, 1    Multiply r/m32 by 2, 1 times.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_D1_4", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_D1_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_D1_5", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_D1_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	/*
	 * SAR r/m32, 1     Signed divide* r/m32 by 2, 1 times.
	 */
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_D1_7", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, 1);
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, 1);
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, 1);
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, 1);
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_D1(PCHAOSVM_CPU pCPU) {//[D1]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_D1", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength+1, &Args);
	Status = pCPU->PargsDispatchTableEntryD1[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * D2 XX
 * XXX r/m8, CL
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_D2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_D2", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_D2_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_D2_0", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_D2_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_D2_1", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalROR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_D2_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_D2_2", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_D2_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_D2_3", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalRCR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_D2_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_D2_4", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHL8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_D2_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_D2_5", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = InternalSHR8(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_D2_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__byte bInt8Tmp;
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_D2_7", pCPU);
	if (pArgs->bIsEAReg) {
		bInt8Tmp = __CPU_GR8_GET__(pCPU, pArgs->EffectiveAddress.bRegIndex);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__CPU_GR8_SET__(pCPU, pArgs->EffectiveAddress.bRegIndex, bInt8Tmp);
	} else {
		__MM_READ_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
		bInt8Tmp = __InternalSAR_uByte__(pCPU, bInt8Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
		__MM_WRITE_UINT8_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, bInt8Tmp);
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_D2(PCHAOSVM_CPU pCPU) {//[D2]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_D2", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryD2[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * D3 XX
 */
CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_IncorrectOpcode_D3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_IncorrectOpcode_D3", pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pCPU);
	__CPU_UNREFERENCED_PARAMETER__(pArgs);
	return __CPU_STATUS_INVALID_OPCODE__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROL_D3_0(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROL_D3_0", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_ROR_D3_1(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_ROR_D3_1", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalROR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalROR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCL_D3_2(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCL_D3_2", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_RCR_D3_3(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_RCR_D3_3", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalRCR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalRCR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHL_D3_4(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHL_D3_4", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHL16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHL32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SHR_D3_5(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SHR_D3_5", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = InternalSHR16(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = InternalSHR32(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncExtForOne_SAR_D3_7(PCHAOSVM_CPU pCPU, PCPU_INSTRUCTION_ARGS pArgs) {
	__PrintDbgInfo_DebugerBreakPoint__("FuncExtForOne_SAR_D3_7", pCPU);
	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		__word wInt16Tmp;
		if (pArgs->bIsEAReg) {
			wInt16Tmp = __CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR16__(pCPU, pArgs->EffectiveAddress.bRegIndex) = wInt16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
			wInt16Tmp = __InternalSAR_uWord__(pCPU, wInt16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, wInt16Tmp);
		}
	} else {
		__dword dwInt32Tmp;
		if (pArgs->bIsEAReg) {
			dwInt32Tmp = __CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__CPU_GR32__(pCPU, pArgs->EffectiveAddress.bRegIndex) = dwInt32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
			dwInt32Tmp = __InternalSAR_uDword__(pCPU, dwInt32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL));
			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), pArgs->EffectiveAddress.addrAddress, dwInt32Tmp);
		}
	}

	pCPU->bOpcodeLength += 1 + pArgs->bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncOne_OpcodeExtDispatch_D3(PCHAOSVM_CPU pCPU) {//[D3]
	CPU_INSTRUCTION_ARGS Args;
	CPU_STATUS Status;
	__PrintDbgInfo_DebugerBreakPoint__("FuncOne_OpcodeExtDispatch_D3", pCPU);
	__ExecuteInstBefore__(pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	Status = pCPU->PargsDispatchTableEntryD3[Args.bRegOpcode].DispatchFunction(pCPU, &Args);

	__ExecuteInstAfter__(pCPU);
	return Status;
}

/*
 * SHLD指令
 * The instruction shifts the first operand (destination operand) to the left the number of bits specified
 * by the third operand (count operand). The second operand (source operand) provides bits
 * to shift in from the right (starting with bit 0 of the destination operand).
 *
 * Operation
 * IF (In 64-Bit Mode and REX.W = 1)
 * THEN COUNT ← COUNT MOD 64;
 * ELSE COUNT ← COUNT MOD 32;
 * FI
 *
 * SIZE ← OperandSize;
 * IF COUNT = 0
 * THEN
 * No operation;
 * ELSE
 * IF COUNT > SIZE
 * THEN (* Bad parameters *)
 * DEST is undefined;
 * CF, OF, SF, ZF, AF, PF are undefined;
 * ELSE (* Perform the shift *)
 * CF ← BIT[DEST, SIZE – COUNT];
 * (* Last bit shifted out on exit *)
 * FOR i ← SIZE – 1 DOWN TO COUNT
 * DO
 * Bit(DEST, i) ← Bit(DEST, i – COUNT);
 * OD;
 * FOR i ← COUNT – 1 DOWN TO 0
 * DO
 * BIT[DEST, i] ← BIT[SRC, i – COUNT + SIZE];
 * OD;
 * FI;
 * FI;
 *
 * Flags Affected
 * If the count is 1 or greater, the CF flag is filled with the last bit shifted out of the destination
 * operand and the SF, ZF, and PF flags are set according to the value of the result. For a 1-bit shift,
 * the OF flag is set if a sign change occurred; otherwise, it is cleared. For shifts greater than 1 bit,
 * the OF flag is undefined. If a shift occurs, the AF flag is undefined. If the count operand is 0, the
 * flags are not affected. If the count is greater than the operand size, the flags are undefined.
 *
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SHLD_0FA4(PCHAOSVM_CPU pCPU) {//[A4]
	/*
	 * SHLD r/m16, r16, imm8       Shift r/m16 to left imm8 places while shifting bits from r16 in from the right.
	 * SHLD r/m32, r32, imm8       Shift r/m32 to left imm8 places while shifting bits from r32 in from the right.
	 */
	__byte bInt8Imm;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SHLD_0FA4", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength+1 + Args.bLength, bInt8Imm);

	/*
	 * IF COUNT = 0 THEN No operation;
	 */
	if (bInt8Imm == 0)
		goto FuncTwo_SHLD_0FA4_Success;

	/*
	 * Is Count > OperandSize?
	 */
	if (bInt8Imm > ((__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) ? 16 : 32)) {
		/*
		 * Bad parameters
		 * DEST is undefined;
		 * CF, OF, SF, ZF, AF, PF are undefined;
		 */
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

		goto FuncTwo_SHLD_0FA4_Success;
	}

	/*
	 * If a shift occurs, the AF flag is undefined. 
	 * If the count operand is 0, the flags are not affected.
	 */
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位模式
		 */
		__word wInt16Source;
		__word wSHLD16Tmp;
		__word wSHLD16DestOrg;

		wInt16Source = __CPU_GR16__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			wSHLD16DestOrg = wSHLD16Tmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHLD16Tmp, 16 - bInt8Imm)));
			wSHLD16Tmp = wSHLD16Tmp << bInt8Imm;
			wSHLD16Tmp = wSHLD16Tmp | (wInt16Source >> (16 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHLD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHLD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wSHLD16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHLD16Tmp);
			wSHLD16DestOrg = wSHLD16Tmp;

			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHLD16Tmp, 16 - bInt8Imm)));
			wSHLD16Tmp = wSHLD16Tmp << bInt8Imm;
			wSHLD16Tmp = wSHLD16Tmp | (wInt16Source >> (16 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHLD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHLD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHLD16Tmp);
		}
	} else {
		/*
		 * 32位模式
		 */
		__dword dwInt32Source;
		__dword dwSHLD32Tmp;
		__dword dwSHLD32DestOrg;

		dwInt32Source = __CPU_GR32__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			dwSHLD32DestOrg = dwSHLD32Tmp = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHLD32Tmp, 32 - bInt8Imm)));
			dwSHLD32Tmp = dwSHLD32Tmp << bInt8Imm;
			dwSHLD32Tmp = dwSHLD32Tmp | (dwInt32Source >> (32 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHLD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHLD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwSHLD32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHLD32Tmp);
			dwSHLD32DestOrg = dwSHLD32Tmp;

			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHLD32Tmp, 32 - bInt8Imm)));
			dwSHLD32Tmp = dwSHLD32Tmp << bInt8Imm;
			dwSHLD32Tmp = dwSHLD32Tmp | (dwInt32Source >> (32 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHLD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHLD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHLD32Tmp);
		}
	}

FuncTwo_SHLD_0FA4_Success:
	pCPU->bOpcodeLength +=  1 + Args.bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SHLD_0FA5(PCHAOSVM_CPU pCPU) {
	/*
	 * SHLD r/m16, r16, CL    Shift r/m16 to left CL places while shifting bits from r16 in from the right.
	 * SHLD r/m32, r32, CL    Shift r/m32 to left CL places while shifting bits from r32 in from the right.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SHLD_0FA5", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);

	/*
	 * IF COUNT = 0 THEN No operation;
	 */
	if( __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 0)
		goto FuncTwo_SHLD_0FA5_Success;

	/*
	 * Is Count > OperandSize ?
	 */
	if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) > ((__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) ? 16 : 32)) {
		/*
		 * Bad parameters
		 * DEST is undefined;
		 * CF, OF, SF, ZF, AF, PF are undefined;
		 */
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

		goto FuncTwo_SHLD_0FA5_Success;
	}

	/*
	 * If a shift occurs, the AF flag is undefined. 
	 * If the count operand is 0, the flags are not affected.
	 */
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位模式
		 */
		__word wInt16Source;
		__word wSHLD16Tmp;
		__word wSHLD16DestOrg;

		wInt16Source = __CPU_GR16__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			wSHLD16DestOrg = wSHLD16Tmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHLD16Tmp, 16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL))));
			wSHLD16Tmp = wSHLD16Tmp << __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			wSHLD16Tmp = wSHLD16Tmp | (wInt16Source >> (16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHLD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHLD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wSHLD16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHLD16Tmp);
			wSHLD16DestOrg = wSHLD16Tmp;

			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHLD16Tmp, 16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL))));
			wSHLD16Tmp = wSHLD16Tmp << __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			wSHLD16Tmp = wSHLD16Tmp | (wInt16Source >> (16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHLD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHLD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHLD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHLD16Tmp);
		}
	} else {
		/*
		 * 32位模式
		 */
		__dword dwInt32Source;
		__dword dwSHLD32Tmp;
		__dword dwSHLD32DestOrg;

		dwInt32Source = __CPU_GR32__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			dwSHLD32DestOrg = dwSHLD32Tmp = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHLD32Tmp, 32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL))));
			dwSHLD32Tmp = dwSHLD32Tmp << __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			dwSHLD32Tmp = dwSHLD32Tmp | (dwInt32Source >> (32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHLD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHLD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwSHLD32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHLD32Tmp);
			dwSHLD32DestOrg = dwSHLD32Tmp;

			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination operand
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHLD32Tmp, 32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL))));
			dwSHLD32Tmp = dwSHLD32Tmp << __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			dwSHLD32Tmp = dwSHLD32Tmp | (dwInt32Source >> (32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHLD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHLD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHLD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHLD32Tmp);
		}
	}

FuncTwo_SHLD_0FA5_Success:
	pCPU->bOpcodeLength +=  1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

/*
 * SHRD指令
 *
 * The instruction shifts the first operand (destination operand) to the right the number of bits specified
 * by the third operand (count operand). The second operand (source operand) provides bits
 * to shift in from the left (starting with the most significant bit of the destination operand).
 * Operation
 *
 * IF (In 64-Bit Mode and REX.W = 1)
 * THEN COUNT ← COUNT MOD 64;
 * ELSE COUNT ← COUNT MOD 32;
 * FI
 *
 * SIZE ← OperandSize;
 * IF COUNT = 0
 * THEN
 * No operation;
 * ELSE
 * IF COUNT > SIZE
 * THEN (* Bad parameters *)
 * DEST is undefined;
 * CF, OF, SF, ZF, AF, PF are undefined;
 * ELSE (* Perform the shift *)
 * CF ← BIT[DEST, COUNT – 1]; (* Last bit shifted out on exit *)
 * FOR i ← 0 TO SIZE – 1 – COUNT
 * DO
 * BIT[DEST, i] ← BIT[DEST, i + COUNT];
 * OD;
 * FOR i ← SIZE – COUNT TO SIZE – 1
 * DO
 * BIT[DEST,i] ← BIT[SRC, i + COUNT – SIZE];
 * OD;
 * FI;
 * FI;
 *
 * Flags Affected
 * If the count is 1 or greater, the CF flag is filled with the last bit shifted out of the destination
 * operand and the SF, ZF, and PF flags are set according to the value of the result. For a 1-bit shift,
 * the OF flag is set if a sign change occurred; otherwise, it is cleared. For shifts greater than 1 bit,
 * the OF flag is undefined. If a shift occurs, the AF flag is undefined. If the count operand is 0, the
 * flags are not affected. If the count is greater than the operand size, the flags are undefined.
 */
CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SHRD_0FAC(PCHAOSVM_CPU pCPU) {//[AC]
	/*
	 * SHRD r/m16, r16, imm8    Shift r/m16 to right imm8 places while shifting bits from r16 in from the left.
	 * SHRD r/m32, r32, imm8     Shift r/m32 to right imm8 places while shifting bits from r32 in from the left.
	 */
	__byte bInt8Imm;
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SHRD_0FAC", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);
	__READ_DATA_UINT8_SAFE__(pCPU, pCPU->bOpcodeLength + 1 + Args.bLength, bInt8Imm);

	/*
	 * IF COUNT = 0 THEN No operation;
	 */
	if (bInt8Imm == 0)
		goto FuncTwo_SHRD_0FAC_Success;

	/*
	 * Is Count > OperandSize ?
	 */
	if (bInt8Imm > ((__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) ? 16 : 32)) {
		/*
		 * Bad parameters
		 * DEST is undefined;
		 * CF, OF, SF, ZF, AF, PF are undefined;
		 */
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

		goto FuncTwo_SHRD_0FAC_Success;
	}
	/*
	 * If a shift occurs, the AF flag is undefined.
	 * If the count operand is 0, the flags are not affected.
	 */
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位模式
		 */
		__word wInt16Source;
		__word wSHRD16Tmp;
		__word wSHRD16DestOrg;

		wInt16Source = __CPU_GR16__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			wSHRD16DestOrg = wSHRD16Tmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHRD16Tmp, bInt8Imm - 1)));
			wSHRD16Tmp = wSHRD16Tmp >> bInt8Imm;
			wSHRD16Tmp = wSHRD16Tmp | (wInt16Source << (16 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHRD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHRD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wSHRD16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHRD16Tmp);
			wSHRD16DestOrg = wSHRD16Tmp;
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHRD16Tmp, bInt8Imm - 1)));
			wSHRD16Tmp = wSHRD16Tmp >> bInt8Imm;
			wSHRD16Tmp = wSHRD16Tmp | (wInt16Source << (16 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHRD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHRD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHRD16Tmp);
		}

	} else {
		/*
		 * 32位模式
		 */
		__dword dwInt32Source;
		__dword dwSHRD32Tmp;
		__dword dwSHRD32DestOrg;

		dwInt32Source = __CPU_GR32__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			dwSHRD32DestOrg = dwSHRD32Tmp = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHRD32Tmp, bInt8Imm - 1)));
			dwSHRD32Tmp = dwSHRD32Tmp >> bInt8Imm;
			dwSHRD32Tmp = dwSHRD32Tmp | (dwInt32Source << (32 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHRD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHRD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwSHRD32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHRD32Tmp);
			dwSHRD32DestOrg = dwSHRD32Tmp;
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHRD32Tmp, bInt8Imm - 1)));
			dwSHRD32Tmp = dwSHRD32Tmp >> bInt8Imm;
			dwSHRD32Tmp = dwSHRD32Tmp | (dwInt32Source << (32 - bInt8Imm));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHRD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHRD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (bInt8Imm == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHRD32Tmp);
		}
	}

FuncTwo_SHRD_0FAC_Success:
	pCPU->bOpcodeLength +=  1 + Args.bLength + 1;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}

CPU_STATUS __INTERNAL_FUNC__ FuncTwo_SHRD_0FAD(PCHAOSVM_CPU pCPU) {//[AD]
	/*
	 * SHRD r/m16, r16, CL    Shift r/m16 to right CL places while shifting bits from r16 in from the left.
	 * SHRD r/m32, r32, CL    Shift r/m32 to right CL places while shifting bits from r32 in from the left.
	 */
	CPU_INSTRUCTION_ARGS Args;
	__PrintDbgInfo_DebugerBreakPoint__("FuncTwo_SHRD_0FAD", pCPU);
	__CPU_ANALYSE_MODRM__(pCPU, pCPU->bOpcodeLength + 1, &Args);


	/*
	 * IF COUNT = 0 THEN No operation;
	 */
	if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 0)
		goto FuncTwo_SHRD_0FAD_Success;

	/*
	 * Is Count > OperandSize ?
	 */
	if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) > ((__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) ? 16 : 32)) {
		/*
		 * Bad parameters
		 * DEST is undefined;
		 * CF, OF, SF, ZF, AF, PF are undefined;
		 */
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_CF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
		__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

		goto FuncTwo_SHRD_0FAD_Success;
	}
	/*
	 * If a shift occurs, the AF flag is undefined. 
	 * If the count operand is 0, the flags are not affected.
	 */
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);

	if (__IS_INSTRUCTION_OPERAND_SIZE_16__(pCPU)) {
		/*
		 * 16位模式
		 */
		__word wInt16Source;
		__word wSHRD16Tmp;
		__word wSHRD16DestOrg;

		wInt16Source = __CPU_GR16__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			wSHRD16DestOrg = wSHRD16Tmp = __CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHRD16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) - 1)));
			wSHRD16Tmp = wSHRD16Tmp >> __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			wSHRD16Tmp = wSHRD16Tmp | (wInt16Source << (16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHRD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHRD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR16__(pCPU, Args.EffectiveAddress.bRegIndex) = wSHRD16Tmp;
		} else {
			__MM_READ_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHRD16Tmp);
			wSHRD16DestOrg = wSHRD16Tmp;
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT16(wSHRD16Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) - 1)));
			wSHRD16Tmp = wSHRD16Tmp >> __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			wSHRD16Tmp = wSHRD16Tmp | (wInt16Source << (16 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, wSHRD16Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(wSHRD16Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT16_MSB__(wSHRD16DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}
			__MM_WRITE_UINT16_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, wSHRD16Tmp);
		}

	} else {
		/*
		 * 32位模式
		 */
		__dword dwInt32Source;
		__dword dwSHRD32Tmp;
		__dword dwSHRD32DestOrg;

		dwInt32Source = __CPU_GR32__(pCPU, Args.bRegOpcode);

		if (Args.bIsEAReg) {
			dwSHRD32DestOrg = dwSHRD32Tmp = __CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex);
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHRD32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) - 1)));
			dwSHRD32Tmp = dwSHRD32Tmp >> __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			dwSHRD32Tmp = dwSHRD32Tmp | (dwInt32Source << (32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHRD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHRD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__CPU_GR32__(pCPU, Args.EffectiveAddress.bRegIndex) = dwSHRD32Tmp;
		} else {
			__MM_READ_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHRD32Tmp);
			dwSHRD32DestOrg = dwSHRD32Tmp;
			/*
			 * If the count is 1 or greater, the CF flag is filled with the last 
			 * bit shifted out of the destination
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __NUM_TO_EFLAG_STATUS__(GET_BIT32(dwSHRD32Tmp, __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) - 1)));
			dwSHRD32Tmp = dwSHRD32Tmp >> __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL);
			dwSHRD32Tmp = dwSHRD32Tmp | (dwInt32Source << (32 - __CPU_GR8_GET__(pCPU, CHAOSVM_R_CL)));

			/*
			 * SF, ZF, and PF flags are set according to the value of the result.
			 */
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32Tmp)));
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, dwSHRD32Tmp ? __EFLAG_RESET__ : __EFLAG_SET__);
			__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(dwSHRD32Tmp));

			/*
			 * For a 1-bit shift,the OF flag is set if a sign change occurred; otherwise, it is cleared.
			 * For shifts greater than 1 bit, the OF flag is undefined.
			 */
			if (__CPU_GR8_GET__(pCPU, CHAOSVM_R_CL) == 1) {
				__byte bOFTmp = (__CPU_EFLAG_GET__(pCPU, CHAOSVM_ER_SF) != __NUM_TO_EFLAG_STATUS__(__UINT32_MSB__(dwSHRD32DestOrg))) ? __EFLAG_SET__ : __EFLAG_RESET__;
				__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, bOFTmp);
			} else {
				__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_OF);
			}

			__MM_WRITE_UINT32_SAFE__(pCPU, __INSTRUCTION_DATASEG__(pCPU), Args.EffectiveAddress.addrAddress, dwSHRD32Tmp);
		}
	}

FuncTwo_SHRD_0FAD_Success:
	pCPU->bOpcodeLength +=  1 + Args.bLength;
	__CPU_EIP__(pCPU) += pCPU->bOpcodeLength;
	return __CPU_STATUS_EXECUTE_SUCCESS__;
}


