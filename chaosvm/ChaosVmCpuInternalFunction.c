/*
 * 位操作函数
 */
// 获取一个Byte/Word/Dword的指定的位
__INLINE__ __byte __INTERNAL_FUNC__ GET_BIT8(__byte uInt8BitString, __byte uInt8BitIndex) {
	return ((uInt8BitString >> (uInt8BitIndex % 8)) & 0x1);
}

__INLINE__ __byte __INTERNAL_FUNC__ GET_BIT16(__word uInt16BitString, __word uInt16BitIndex) {
	return UINT16_TO_UINT8((uInt16BitString >> (uInt16BitIndex % 16)) & 0x1);
}
__INLINE__ __byte __INTERNAL_FUNC__ GET_BIT32(__dword uInt32BitString, __dword uInt32BitIndex) {
	return UINT32_TO_UINT8((uInt32BitString >> (uInt32BitIndex % 32)) & 0x1);
}

// 指定位置位
__INLINE__ __byte __INTERNAL_FUNC__ SET_BIT8(__byte uInt8BitString, __byte uInt8BitIndex) {
	return uInt8BitString | ((__byte)0x1 << (uInt8BitIndex % 8));
}

__INLINE__ __word __INTERNAL_FUNC__ SET_BIT16(__word uInt16BitString, __word uInt16BitIndex) {
	return uInt16BitString | ((__word)0x1 << (uInt16BitIndex % 16));
}
__INLINE__ __dword __INTERNAL_FUNC__ SET_BIT32(__dword uInt32BitString, __dword uInt32BitIndex) {
	return uInt32BitString | ((__dword)0x1 << (uInt32BitIndex % 32));
}


// 指定位清零
__INLINE__ __byte __INTERNAL_FUNC__ RESET_BIT8(__byte uInt8BitString, __byte uInt8BitIndex) {
	return uInt8BitString & ~UINT32_TO_UINT8(((__dword)1 << (uInt8BitIndex % 8)));
}

__INLINE__ __word __INTERNAL_FUNC__ RESET_BIT16(__word uInt16BitString, __word uInt16BitIndex) {
	return uInt16BitString & ~UINT32_TO_UINT16((__dword)1 << (uInt16BitIndex % 16));
}
__INLINE__ __dword __INTERNAL_FUNC__ RESET_BIT32(__dword uInt32BitString, __dword uInt32BitIndex) {
	return uInt32BitString & ~((__dword)1 << (uInt32BitIndex % 32));
}

// 指定位求反
__INLINE__ __byte __INTERNAL_FUNC__ COMPLEMENT_BIT8(__byte uInt8BitString, __byte uInt8BitIndex) {
	if (GET_BIT8(uInt8BitString, uInt8BitIndex))
		uInt8BitString = RESET_BIT8(uInt8BitString, uInt8BitIndex);
	else
		uInt8BitString = SET_BIT8(uInt8BitString, uInt8BitIndex);
	return uInt8BitString;
}

__INLINE__ __word __INTERNAL_FUNC__ COMPLEMENT_BIT16(__word uInt16BitString, __word uInt16BitIndex) {
	if (GET_BIT16(uInt16BitString, uInt16BitIndex))
		uInt16BitString = RESET_BIT16(uInt16BitString, uInt16BitIndex);
	else
		uInt16BitString = SET_BIT16(uInt16BitString, uInt16BitIndex);
	return uInt16BitString;
}

__INLINE__ __dword __INTERNAL_FUNC__ COMPLEMENT_BIT32(__dword uInt32BitString, __dword uInt32BitIndex) {
	if (GET_BIT32(uInt32BitString, uInt32BitIndex))
		uInt32BitString = RESET_BIT32(uInt32BitString, uInt32BitIndex);
	else
		uInt32BitString = SET_BIT32(uInt32BitString, uInt32BitIndex);
	return uInt32BitString;
}

/*
 * 计算AF值
 */
__INLINE__ __byte __INTERNAL_FUNC__ GenerateADDAF8(__byte uInt8Value1, __byte uInt8Value2, __byte CF) {
	uInt8Value1 = (uInt8Value1 & 0xF) + (uInt8Value2 & 0xF) + CF;
	return (uInt8Value1 & 0xF0) ? __EFLAG_SET__ : __EFLAG_RESET__;
}
#define __GenerateADDAF16__(uInt16Value1, uInt16Value2, uInt8CF)   GenerateADDAF8(UINT16_TO_UINT8(uInt16Value1), UINT16_TO_UINT8(uInt16Value2), uInt8CF)
#define __GenerateADDAF32__(uInt32Value1, uInt32Value2, uInt8CF)   GenerateADDAF8(UINT32_TO_UINT8(uInt32Value1), UINT32_TO_UINT8(uInt32Value2), uInt8CF)

__INLINE__ __byte __INTERNAL_FUNC__ GenerateSUBAF8(__byte uInt8Value1, __byte uInt8Value2, __byte CF) {
	uInt8Value1 = (uInt8Value1 & 0xF) - (uInt8Value2 & 0xF) - CF;
	return (uInt8Value1 & 0xF0) ? __EFLAG_SET__ : __EFLAG_RESET__;
}
#define __GenerateSUBAF16__(uInt16Value1, uInt16Value2, uInt8CF)   GenerateSUBAF8(UINT16_TO_UINT8(uInt16Value1), UINT16_TO_UINT8(uInt16Value2), uInt8CF)
#define __GenerateSUBAF32__(uInt32Value1, uInt32Value2, uInt8CF)   GenerateSUBAF8(UINT32_TO_UINT8(uInt32Value1), UINT32_TO_UINT8(uInt32Value2), uInt8CF)

/*
 * 计算PF值
 * PF 低8位，1的个数为偶数 PF=1,否则 PF=0
 */
__INLINE__ __byte __INTERNAL_FUNC__ GenerateParity8(__byte uInt8Value) {
	__byte uInt8Result;
	uInt8Result = ( uInt8Value & 0x55) + (( uInt8Value >> 1) & 0x55);
	uInt8Result = (uInt8Result & 0x33) + ((uInt8Result >> 2) & 0x33);
	uInt8Result = (uInt8Result & 0x0F) + ((uInt8Result >> 4) & 0x0F);
	uInt8Result = (uInt8Result + 1) % 2;
	return __NUM_TO_EFLAG_STATUS__(uInt8Result);
}
#define __GenerateParity16__(uInt16Value)   GenerateParity8(UINT16_TO_UINT8(uInt16Value))
#define __GenerateParity32__(uInt32Value)   GenerateParity8(UINT32_TO_UINT8(uInt32Value))

#define __IS_OVERFLOW_FOR_INT8__(Int16Value)     ((Int16Value > 0x7F) || (Int16Value < -0x80))
#define __IS_OVERFLOW_FOR_INT16__(Int32Value)    ((Int32Value > 0x7FFF) || (Int32Value < -0x8000))
#define __IS_OVERFLOW_FOR_INT32__(Int64Value)    ((Int64Value > 0x7FFFFFFF) || (Int64Value < ((__sqword)0-0x80000000)))

#define __InternalPushNextAsNearRetAddress__(pCPU, CurrentInstructionLength) {\
	if (__IS_INSTRUCTION_ADDRESS_MODE_16__(pCPU)){\
	__InternalPush_uWord__(pCPU, __CPU_IP__(pCPU) + CurrentInstructionLength);}\
	else {\
	__InternalPush_uDword__(pCPU, __CPU_EIP__(pCPU) + CurrentInstructionLength);}}

/*
 * PUSH/POP指令实现(包括对ESP的修改)
 */
#define __InternalPush_uDword__(pCPU, uDword) {\
	__MM_WRITE_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 4, uDword);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 4;}

#define __InternalPush_uWord__(pCPU, uWord) {\
	__MM_WRITE_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), (__CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 2), uWord);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 2;}

#define __InternalPop_uDword__(pCPU, uDword) {\
	__MM_READ_UINT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), uDword);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 4;}

#define __InternalPop_uWord__(pCPU, uWord) {\
	__MM_READ_UINT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), uWord);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 2;}

#define __InternalPush_sDword__(pCPU, sDword) {\
	__MM_WRITE_INT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 4, sDword);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 4;}

#define __InternalPush_sWord__(pCPU, sWord) {\
	__MM_WRITE_INT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), (__CPU_GR32__(pCPU, CHAOSVM_R_ESP) - 2), sWord);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) -= 2;}

#define __InternalPop_sDword__(pCPU, sDword) {\
	__MM_READ_INT32_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), sDword);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 4;}

#define __InternalPop_sWord__(pCPU, sWord) {\
	__MM_READ_INT16_SAFE__(pCPU, __CPU_SR__(pCPU, CHAOSVM_SR_SS), __CPU_GR32__(pCPU, CHAOSVM_R_ESP), sWord);\
	__CPU_GR32__(pCPU, CHAOSVM_R_ESP) += 2;}

/*
 * NEG指令实现(包括对标志寄存器的修改)
 * Flags Affected
 * The OF, SF, ZF, AF, PF, and CF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalNEG8(PCHAOSVM_CPU pCPU, __byte bInt8Value) {
	__sword swInt16Result;
	__byte bInt8ResultLow;

	swInt16Result = 0 - INT8_TO_INT16(UINT8_TO_INT8(bInt8Value));
	bInt8ResultLow = __Low8__(INT16_TO_UINT16(swInt16Result));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((bInt8Value) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(swInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(bInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (bInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(bInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateSUBAF8(0, bInt8Value, 0));

	return bInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalNEG16(PCHAOSVM_CPU pCPU, __word uInt16Value) {
	__sdword Int32Result;
	__word uInt16ResultLow;

	Int32Result = 0 - INT16_TO_INT32(UINT16_TO_INT16(uInt16Value));
	uInt16ResultLow = __Low16__(INT32_TO_UINT32(Int32Result));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((uInt16Value) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF16__(0, uInt16Value, 0));

	return uInt16ResultLow;
}
__INLINE__ __dword __INTERNAL_FUNC__ InternalNEG32(PCHAOSVM_CPU pCPU, __dword uInt32Value) {
	__sqword Int64Result;
	__dword uInt32ResultLow;

	Int64Result = 0 - INT32_TO_INT64(UINT32_TO_INT32(uInt32Value));
	uInt32ResultLow = __Low32__(INT64_TO_UINT64(Int64Result));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((uInt32Value ) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF32__(0, uInt32Value, 0));

	return uInt32ResultLow;
}

/*
 * XOR指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * DEST ← DEST XOR SRC;
 * Flags Affected
 * The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. 
 * The state of the AF flag is undefined.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalXOR8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__byte uInt8Result;
	uInt8Result = uInt8Value1 ^ uInt8Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt8Result;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalXOR16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__word uInt16Result;
	uInt16Result = uInt16Value1 ^ uInt16Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt16Result;
}
__INLINE__ __dword __INTERNAL_FUNC__ InternalXOR32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__dword uInt32Result;
	uInt32Result = uInt32Value1 ^ uInt32Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt32Result;
}

/*
 * OR指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * DEST ← DEST XOR SRC;
 * Flags Affected
 * The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. 
 * The state of the AF flag is undefined.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalOR8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__byte uInt8Result;
	uInt8Result = uInt8Value1 | uInt8Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt8Result;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalOR16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__word uInt16Result;
	uInt16Result = uInt16Value1 | uInt16Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt16Result;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalOR32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__dword uInt32Result;
	uInt32Result = uInt32Value1 | uInt32Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt32Result;
}

/*
 * AND指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * DEST ← DEST AND SRC;
 * Flags Affected
 * The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result.
 *The state of the AF flag is undefined.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalAND8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__byte uInt8Result;
	uInt8Result = uInt8Value1 & uInt8Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt8Result;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalAND16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__word uInt16Result;
	uInt16Result = uInt16Value1 & uInt16Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16Result) );
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt16Result;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalAND32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__dword uInt32Result;
	uInt32Result = uInt32Value1 & uInt32Value2;	
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32Result) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32Result));
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	return uInt32Result;
}

/*
 * TEST指令的实现
 *
 * Operation:
 * TEMP ← SRC1 AND SRC2;
 * SF ← MSB(TEMP);
 * IF TEMP = 0
 * THEN
 * ZF ← 1;
 * ELSE
 * ZF ← 0;
 * FI:
 *
 * PF ← BitwiseXNOR(TEMP[0:7]);
 * CF ← 0;
 * OF ← 0;
 * (* AF is undefined *)
 *
 * Flags Affected:
 * The OF and CF flags are set to 0. The SF, ZF, and PF flags are set according to the result (see
 * the “Operation” section above). The state of the AF flag is undefined.
 */
#define __InternalTEST8__(pCPU, uInt8Value1, uInt8Value2)      InternalAND8(pCPU, uInt8Value1, uInt8Value2)
#define __InternalTEST16__(pCPU, uInt16Value1, uInt16Value2)   InternalAND16(pCPU, uInt16Value1, uInt16Value2)
#define __InternalTEST32__(pCPU, uInt32Value1, uInt32Value2)   InternalAND32(pCPU, uInt32Value1, uInt32Value2)

/*
 * ADD指令实现(包括对标志寄存器的修改)
 *
 * Flags Affected
 * The OF, SF, ZF, AF, CF, and PF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalADD8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) + UINT8_TO_UINT16(uInt8Value2);	
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) + INT8_TO_INT16(UINT8_TO_INT8(uInt8Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High8__(uInt16Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__ );
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateADDAF8(uInt8Value1, uInt8Value2, 0));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalADD16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) + UINT16_TO_UINT32(uInt16Value2);	
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32( UINT16_TO_INT16(uInt16Value1)) + INT16_TO_INT32(UINT16_TO_INT16(uInt16Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High16__(uInt32Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF16__(uInt16Value1, uInt16Value2, 0));

	return uInt16ResultLow;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalADD32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) + UINT32_TO_UINT64(uInt32Value2);	
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64( UINT32_TO_INT32(uInt32Value1)) + INT32_TO_INT64(UINT32_TO_INT32(uInt32Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High32__(uInt64Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF32__(uInt32Value1, uInt32Value2, 0));

	return uInt32ResultLow;
}

/*
 * ADC指令实现(包括对标志寄存器的修改)
 *
 * Flags Affected
 * The OF, SF, ZF, AF, CF, and PF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalADC8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) + UINT8_TO_UINT16(uInt8Value2) + UINT8_TO_UINT16(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) + INT8_TO_INT16(UINT8_TO_INT8(uInt8Value2)) + INT8_TO_INT16(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateADDAF8(uInt8Value1, uInt8Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High8__(uInt16Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalADC16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) + UINT16_TO_UINT32(uInt16Value2) + UINT8_TO_UINT32(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));	
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32(UINT16_TO_INT16(uInt16Value1)) + INT16_TO_INT32(UINT16_TO_INT16(uInt16Value2)) + INT8_TO_INT32(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF16__(uInt16Value1, uInt16Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High16__(uInt32Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));

	return uInt16ResultLow;
}


__INLINE__ __dword __INTERNAL_FUNC__ InternalADC32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) + UINT32_TO_UINT64(uInt32Value2) + UINT8_TO_UINT64(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));	
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64(UINT32_TO_INT32(uInt32Value1)) + INT32_TO_INT64(UINT32_TO_INT32(uInt32Value2)) + INT8_TO_INT16(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF32__(uInt32Value1, uInt32Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High32__(uInt64Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));

	return uInt32ResultLow;
}

/*
 * INC指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * DEST ← DEST + 1;
 * Flags Affected
 * The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalINC8(PCHAOSVM_CPU pCPU, __byte uInt8Value1) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) + 1;	
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) + 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateADDAF8(uInt8Value1, 1, 0) );
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalINC16(PCHAOSVM_CPU pCPU, __word uInt16Value1) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) + 1;
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32(UINT16_TO_INT16(uInt16Value1)) + 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF16__(uInt16Value1, 1, 0));
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result)?__EFLAG_SET__:__EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));

	return uInt16ResultLow;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalINC32(PCHAOSVM_CPU pCPU, __dword uInt32Value1) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) + 1;	
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64(UINT32_TO_INT32(uInt32Value1)) + 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateADDAF32__(uInt32Value1, 1, 0));
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__ ));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));

	return uInt32ResultLow;
}

/*
 * SUB指令实现(包括对标志寄存器的修改)
 *
 * Flags Affected
 * The OF, SF, ZF, AF, PF, and CF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalSUB8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) - UINT8_TO_UINT16(uInt8Value2);	
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) - INT8_TO_INT16(UINT8_TO_INT8(uInt8Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateSUBAF8(uInt8Value1, uInt8Value2, 0));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High8__(uInt16Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow ) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalSUB16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) - UINT16_TO_UINT32(uInt16Value2);	
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32(UINT16_TO_INT16(uInt16Value1)) - INT16_TO_INT32(UINT16_TO_INT16(uInt16Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF16__(uInt16Value1, uInt16Value2, 0));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High16__(uInt32Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));

	return uInt16ResultLow;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalSUB32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) - UINT32_TO_UINT64(uInt32Value2);	
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64(UINT32_TO_INT32(uInt32Value1)) - INT32_TO_INT64(UINT32_TO_INT32(uInt32Value2));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF32__(uInt32Value1, uInt32Value2, 0));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High32__(uInt64Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));

	return uInt32ResultLow;
}

/*
 * SBB指令实现(包括对标志寄存器的修改)
 *
 * Flags Affected
 * The OF, SF, ZF, AF, PF, and CF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalSBB8(PCHAOSVM_CPU pCPU, __byte uInt8Value1, __byte uInt8Value2) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) - UINT8_TO_UINT16(uInt8Value2) - UINT8_TO_UINT16(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));	
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) - INT8_TO_INT16(UINT8_TO_INT8(uInt8Value2)) - INT8_TO_INT16(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateSUBAF8(uInt8Value1, uInt8Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High8__(uInt16Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalSBB16(PCHAOSVM_CPU pCPU, __word uInt16Value1, __word uInt16Value2) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) - UINT16_TO_UINT32(uInt16Value2) - UINT8_TO_UINT32(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32(UINT16_TO_INT16(uInt16Value1)) - INT16_TO_INT32(UINT16_TO_INT16(uInt16Value2)) - INT8_TO_INT32(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF16__(uInt16Value1, uInt16Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High16__(uInt32Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, ( uInt16ResultLow ) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));

	return uInt16ResultLow;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalSBB32(PCHAOSVM_CPU pCPU, __dword uInt32Value1, __dword uInt32Value2) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) - UINT32_TO_UINT64(uInt32Value2) - UINT8_TO_UINT64(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF));
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64(UINT32_TO_INT32(uInt32Value1)) - INT32_TO_INT64(UINT32_TO_INT32(uInt32Value2)) - INT8_TO_INT16(UINT8_TO_INT8(__CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF32__(uInt32Value1, uInt32Value2, __CPU_EFLAG_GET_AS_NUM__(pCPU, CHAOSVM_ER_CF)));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, ((__High32__(uInt64Result)) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));

	return uInt32ResultLow;
}

/*
 * DEC指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * DEST ← DEST – 1;
 * Flags Affected
 * The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result.
 */
__INLINE__ __byte __INTERNAL_FUNC__ InternalDEC8(PCHAOSVM_CPU pCPU, __byte uInt8Value1) {
	__word uInt16Result;
	__sword Int16Result;
	__byte uInt8ResultLow;

	uInt16Result = UINT8_TO_UINT16(uInt8Value1) - 1;	
	uInt8ResultLow = __Low8__(uInt16Result);
	Int16Result = INT8_TO_INT16(UINT8_TO_INT8(uInt8Value1)) - 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, GenerateSUBAF8(uInt8Value1, 1, 0) );
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT8__(Int16Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT8_MSB__(uInt8ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt8ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, GenerateParity8(uInt8ResultLow));

	return uInt8ResultLow;
}

__INLINE__ __word __INTERNAL_FUNC__ InternalDEC16(PCHAOSVM_CPU pCPU, __word uInt16Value1) {
	__dword uInt32Result;
	__sdword Int32Result;
	__word uInt16ResultLow;

	uInt32Result = UINT16_TO_UINT32(uInt16Value1) - 1;	
	uInt16ResultLow = __Low16__(uInt32Result);
	Int32Result = INT16_TO_INT32(UINT16_TO_INT16(uInt16Value1)) - 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF16__(uInt16Value1, 1, 0));
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT16__(Int32Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT16_MSB__(uInt16ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt16ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity16__(uInt16ResultLow));

	return uInt16ResultLow;
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalDEC32(PCHAOSVM_CPU pCPU, __dword uInt32Value1) {
	__qword uInt64Result;
	__sqword Int64Result;
	__dword uInt32ResultLow;

	uInt64Result = UINT32_TO_UINT64(uInt32Value1) - 1;	
	uInt32ResultLow = __Low32__(uInt64Result);
	Int64Result = INT32_TO_INT64(UINT32_TO_INT32(uInt32Value1)) - 1;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_AF, __GenerateSUBAF32__(uInt32Value1, 1, 0));
	__CPU_EFLAG_NOT_AFFECT__(pCPU, CHAOSVM_ER_CF);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, (__IS_OVERFLOW_FOR_INT32__(Int64Result) ? __EFLAG_SET__ : __EFLAG_RESET__));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_SF, __UINT32_MSB__(uInt32ResultLow));
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_ZF, (uInt32ResultLow) ? __EFLAG_RESET__ : __EFLAG_SET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_PF, __GenerateParity32__(uInt32ResultLow));

	return uInt32ResultLow;
}

/*
 * CMP指令实现(包括对标志寄存器的修改)
 *
 * Operation
 * temp ← SRC1 - SignExtend(SRC2);
 * ModifyStatusFlags; (* Modify status flags in the same manner as the SUB instruction*)
 * Flags Affected
 * The CF, OF, SF, ZF, AF, and PF flags are set according to the result.
 */
#define __InternalCMP8__(pCPU, uInt8Value1, uInt8Value2)      InternalSUB8(pCPU, uInt8Value1, uInt8Value2)
#define __InternalCMP16__(pCPU, uInt16Value1, uInt16Value2)   InternalSUB16(pCPU, uInt16Value1, uInt16Value2)
#define __InternalCMP32__(pCPU, uInt32Value1, uInt32Value2)   InternalSUB32(pCPU, uInt32Value1, uInt32Value2)

/*
 * MUL指令实现(包括保存结果和对标志寄存器的修改)
 *
 * Operation
 * IF (Byte operation)
 * THEN
 * AX ← AL * SRC;
 * ELSE (* Word or doubleword operation *)
 * IF OperandSize = 16
 * THEN
 * DX:AX ← AX * SRC;
 * ELSE IF OperandSize = 32
 * THEN EDX:EAX ← EAX * SRC; FI;
 * ELSE (* OperandSize = 64 *)
 * RDX:RAX ← RAX * SRC;
 * FI;
 * FI;
 * Flags Affected
 * The OF and CF flags are set to 0 if the upper half of the result is 0; otherwise, they are set to 1.
 *The SF, ZF, AF, and PF flags are undefined.
 *
 *
 * The result is stored in register AX, register pair DX:AX, or register pair EDX:EAX (depending
 * on the operand size), with the high-order bits of the product contained in register AH, DX, or
 * EDX, respectively. 
 */
__INLINE__ __void __INTERNAL_FUNC__ InternalMUL8(PCHAOSVM_CPU pCPU, __byte uInt8Value) {
	__word uInt16Result;
	uInt16Result = UINT8_TO_UINT16(uInt8Value) * UINT8_TO_UINT16(__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = uInt16Result;

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __High8__(uInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __High8__(uInt16Result) ? __EFLAG_SET__ : __EFLAG_RESET__);

	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
}

__INLINE__ __void __INTERNAL_FUNC__ InternalMUL16(PCHAOSVM_CPU pCPU, __word uInt16Value) {
	__dword uInt32Result;
	uInt32Result = UINT16_TO_UINT32(uInt16Value) * UINT16_TO_UINT32(__CPU_GR16__(pCPU, CHAOSVM_R_AX));
	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __Low16__(uInt32Result);
	__CPU_GR16__(pCPU, CHAOSVM_R_DX) = __High16__(uInt32Result);

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __High16__(uInt32Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __High16__(uInt32Result) ? __EFLAG_SET__ : __EFLAG_RESET__);

	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
}

__INLINE__ __void __INTERNAL_FUNC__ InternalMUL32(PCHAOSVM_CPU pCPU, __dword uInt32Value) {
	__qword uInt64Result;
	uInt64Result = UINT32_TO_UINT64(uInt32Value) * UINT32_TO_UINT64(__CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __Low32__(uInt64Result);
	__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = __High32__(uInt64Result);

	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __High32__(uInt64Result) ? __EFLAG_SET__ : __EFLAG_RESET__);
	__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __High32__(uInt64Result) ? __EFLAG_SET__ : __EFLAG_RESET__);

	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
}

/*
 * IMUL指令实现(包括对寄存器的修改)
 */
/*
 * Performs a signed multiplication of two operands. This instruction has three forms, depending
 * on the number of operands.
 * 1)One-operand form — This form is identical to that used by the MUL instruction. Here,
 * the source operand (in a general-purpose register or memory location) is multiplied by the
 * value in the AL, AX, EAX, or RAX register (depending on the operand size) and the
 * product is stored in the AX, DX:AX, EDX:EAX, or RDX:RAX registers, respectively.
 * 2)Two-operand form — With this form the destination operand (the first operand) is
 * multiplied by the source operand (second operand). The destination operand is a generalpurpose
 * register and the source operand is an immediate value, a general-purpose register,
 * or a memory location. The product is then stored in the destination operand location.
 * 3)Three-operand form — This form requires a destination operand (the first operand) and
 * two source operands (the second and the third operands). Here, the first source operand
 * (which can be a general-purpose register or a memory location) is multiplied by the second
 * source operand (an immediate value). The product is then stored in the destination operand
 * (a general-purpose register).
 *
 * Flags Affected
 * For the one operand form of the instruction, the CF and OF flags are set when significant bits
 * are carried into the upper half of the result and cleared when the result fits exactly in the lower
 * half of the result. For the two- and three-operand forms of the instruction, the CF and OF flags
 * are set when the result must be truncated to fit in the destination operand size and cleared when
 * the result fits exactly in the destination operand size. The SF, ZF, AF, and PF flags are undefined.
 */
// IMUL单操作数
__INLINE__ __void __INTERNAL_FUNC__ InternalIMUL1_8(PCHAOSVM_CPU pCPU, __char Int8Value) {
	__sword Int16Result;
	__char Int8Result;

	Int16Result = INT8_TO_INT16(Int8Value) * INT8_TO_INT16(UINT8_TO_INT8(__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL)));
	Int8Result = Int8Value *  UINT8_TO_INT8(__CPU_GR8_GET__(pCPU, CHAOSVM_R_AL));
	if( Int16Result != INT8_TO_INT16(Int8Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = INT16_TO_UINT16(Int16Result);
}

__INLINE__ __void __INTERNAL_FUNC__ InternalIMUL1_16(PCHAOSVM_CPU pCPU, __sword Int16Value) {
	__sdword Int32Result;
	__sword Int16Result;

	Int32Result = INT16_TO_INT32(Int16Value) * INT16_TO_INT32(UINT16_TO_INT16(__CPU_GR16__(pCPU, CHAOSVM_R_AX)));
	Int16Result = Int16Value *  UINT16_TO_INT16(__CPU_GR16__(pCPU, CHAOSVM_R_AX));
	if( Int32Result != INT16_TO_INT32(Int16Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = __Low16__(INT32_TO_UINT32(Int32Result));
	__CPU_GR16__(pCPU, CHAOSVM_R_DX) = __High16__(INT32_TO_UINT32(Int32Result));
}

__INLINE__ __void __INTERNAL_FUNC__ InternalIMUL1_32(PCHAOSVM_CPU pCPU, __sdword Int32Value) {
	__sqword Int64Result;
	__sdword Int32Result;

	Int64Result = INT32_TO_INT64(Int32Value) * INT32_TO_INT64(UINT32_TO_INT32(__CPU_GR32__(pCPU, CHAOSVM_R_EAX)));
	Int32Result = Int32Value *  UINT32_TO_INT32(__CPU_GR32__(pCPU, CHAOSVM_R_EAX));
	if (Int64Result != INT32_TO_INT64(Int32Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);

	__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = __Low32__(INT64_TO_UINT64(Int64Result));
	__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = __High32__(INT64_TO_UINT64(Int64Result));
}

// IMUL两操作数
#define __InternalIMUL2_8__(pCPU, Int8Value1, Int8Value2)		InternalIMUL3_8(pCPU, Int8Value1, Int8Value2)
#define __InternalIMUL2_16__(pCPU, Int16Value1, Int16Value2)    InternalIMUL3_16(pCPU, Int16Value1, Int16Value2)
#define __InternalIMUL2_32__(pCPU, Int32Value1, Int32Value2)    InternalIMUL3_32(pCPU, Int32Value1, Int32Value2)

// IMUL三操作数
__INLINE__ __byte __INTERNAL_FUNC__ InternalIMUL3_8(PCHAOSVM_CPU pCPU, __char Int8Value1, __char Int8Value2) {
	__sword Int16Result;
	__char Int8Result;

	Int16Result = INT8_TO_INT16(Int8Value1) * INT8_TO_INT16(Int8Value2);
	Int8Result = Int8Value1 * Int8Value2;
	if (Int16Result != INT8_TO_INT16(Int8Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
	return __Low8__(INT16_TO_UINT16(Int16Result));
}

__INLINE__ __word __INTERNAL_FUNC__ InternalIMUL3_16(PCHAOSVM_CPU pCPU, __sword Int16Value1, __sword Int16Value2) {
	__sdword Int32Result;
	__sword Int16Result;

	Int32Result = INT16_TO_INT32(Int16Value1) * INT16_TO_INT32(Int16Value2);
	Int16Result = Int16Value1 * Int16Value2;
	if (Int32Result != INT16_TO_INT32(Int16Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
	return __Low16__(INT32_TO_UINT32(Int32Result));
}

__INLINE__ __dword __INTERNAL_FUNC__ InternalIMUL3_32(PCHAOSVM_CPU pCPU, __sdword Int32Value1, __sdword Int32Value2) {
	__sqword Int64Result;
	__sdword Int32Result;

	Int64Result = INT32_TO_INT64(Int32Value1) * INT32_TO_INT64(Int32Value2);
	Int32Result = Int32Value1 * Int32Value2;
	if (Int64Result != INT32_TO_INT64(Int32Result)) {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_SET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_SET__);
	} else {
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_OF, __EFLAG_RESET__);
		__CPU_EFLAG_SET__(pCPU, CHAOSVM_ER_CF, __EFLAG_RESET__);
	}
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__(pCPU, CHAOSVM_ER_PF);
	return __Low32__(INT64_TO_UINT64(Int64Result));
}



/*
 * DIV指令实现(包括保存结果和对标志寄存器的修改)
 *
 * IF SRC = 0
 * THEN #DE; FI; (* Divide Error *)
 * IF OperandSize = 8 (* Word/Byte Operation *)
 * THEN
 * temp ← AX / SRC;
 * IF temp > FFH
 * THEN #DE; (* Divide error *)
 * ELSE
 * AL ← temp;
 * AH ← AX MOD SRC;
 * FI;
 * ELSE IF OperandSize = 16 (* Doubleword/word operation *)
 * THEN
 * temp ← DX:AX / SRC;
 * IF temp > FFFFH
 * THEN #DE; (* Divide error *)
 * ELSE
 * AX ← temp;
 * DX ← DX:AX MOD SRC;
 * FI;
 * FI;
 * ELSE IF Operandsize = 32 (* Quadword/doubleword operation *)
 * THEN
 * temp ← EDX:EAX / SRC;
 * IF temp > FFFFFFFFH
 * THEN #DE; (* Divide error *)
 * ELSE
 * EAX ← temp;
 * EDX ← EDX:EAX MOD SRC;
 * FI;
 * FI;
 * FI;
 *
 * Flags Affected
 *The CF, OF, SF, ZF, AF, and PF flags are undefined.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalDIV8(PCHAOSVM_CPU pCPU, __byte uInt8Value) {
	if (0 == uInt8Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, UINT16_TO_UINT8(__CPU_GR16__(pCPU, CHAOSVM_R_AX) / UINT8_TO_UINT16(uInt8Value)) );
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, UINT16_TO_UINT8(__CPU_GR16__(pCPU, CHAOSVM_R_AX) % UINT8_TO_UINT16(uInt8Value)));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalDIV16(PCHAOSVM_CPU pCPU, __word uInt16Value) {
	__dword uInt32Dividend;
	if (0 == uInt16Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	uInt32Dividend = __MAKE_UINT32__( __CPU_GR16__(pCPU, CHAOSVM_R_AX), __CPU_GR16__(pCPU, CHAOSVM_R_DX));
	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = UINT32_TO_UINT16(uInt32Dividend / UINT16_TO_UINT32(uInt16Value));
	__CPU_GR16__(pCPU, CHAOSVM_R_DX) = UINT32_TO_UINT16(uInt32Dividend % UINT16_TO_UINT32(uInt16Value));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalDIV32(PCHAOSVM_CPU pCPU, __dword uInt32Value) {
	__qword uInt64Dividend;
	if (0 == uInt32Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	uInt64Dividend = __MAKE_UINT64__(__CPU_GR32__(pCPU, CHAOSVM_R_EAX), __CPU_GR32__(pCPU, CHAOSVM_R_EDX));
	__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = UINT64_TO_UINT32(uInt64Dividend / UINT32_TO_UINT64(uInt32Value));
	__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = UINT64_TO_UINT32(uInt64Dividend % UINT32_TO_UINT64(uInt32Value));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}
#define __InternalDIV8_SAFE__(pCPU, uInt8Value)          if (!__CPU_STATUS_SUCCESS__(InternalDIV8(pCPU, uInt8Value)))   return __GET_LAST_STATUS__(pCPU);
#define __InternalDIV16_SAFE__(pCPU, uInt16Value)        if (!__CPU_STATUS_SUCCESS__(InternalDIV16(pCPU, uInt16Value)))    return __GET_LAST_STATUS__(pCPU); 
#define __InternalDIV32_SAFE__(pCPU, uInt32Value)        if (!__CPU_STATUS_SUCCESS__(InternalDIV32(pCPU, uInt32Value)))    return __GET_LAST_STATUS__(pCPU); 

/*
 * IDIV指令实现(包括保存结果和对标志寄存器的修改)
 * IF SRC = 0
 * THEN #DE; (* Divide error *)
 * FI;
 * IF OperandSize = 8 (* Word/byte operation *)
 * THEN
 * temp ← AX / SRC; (* Signed division *)
 * IF (temp > 7FH) or (temp < 80H)
 * (* If a positive result is greater than 7FH or a negative result is less than 80H *)
 * THEN #DE; (* Divide error *)
 * ELSE
 * AL ← temp;
 * AH ← AX SignedModulus SRC;
 * FI;
 * ELSE IF OperandSize = 16 (* Doubleword/word operation *)
 * THEN
 * temp ← DX:AX / SRC; (* Signed division *)
 * IF (temp > 7FFFH) or (temp < 8000H)
 * (* If a positive result is greater than 7FFFH or a negative result is less than 8000H *)
 * THEN
 * #DE; (* Divide error *)
 * ELSE
 * AX ← temp;
 * DX ← DX:AX SignedModulus SRC;
 * FI;
 * FI;
 * ELSE IF OperandSize = 32 (* Quadword/doubleword operation *)
 * temp ← EDX:EAX / SRC; (* Signed division *)
 * IF (temp > 7FFFFFFFH) or (temp < 80000000H)
 * (* If a positive result is greater than 7FFFFFFFH or a negative result is less than 80000000H *)
 * THEN
 * #DE; (* Divide error *)
 * ELSE
 * EAX ← temp;
 * EDX ← EDXE:AX SignedModulus SRC;
 * FI;
 * FI;
 * ELSE IF OperandSize = 64 (* Doublequadword/quadword operation *)
 * temp ← RDX:RAX / SRC; (* Signed division *)
 * IF (temp > 7FFFFFFFFFFFH) or (temp < 8000000000000000H)
 * (* If a positive result is greater than 7FFFFFFFFFFFH or a negative result is less than 8000000000000000H *)
 * THEN
 * #DE; (* Divide error *)
 * ELSE
 * RAX ← temp;
 * RDX ← RDE:RAX SignedModulus SRC;
 * FI;
 * FI;
 * FI;
 *
 * Flags Affected
 * The CF, OF, SF, ZF, AF, and PF flags are undefined.
 */
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalIDIV8(PCHAOSVM_CPU pCPU, __char Int8Value) {
	__sword Int16Dividend;
	__sword Int16Quotient;
	__sword Int16Remainder;
	if (0 == Int8Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	Int16Dividend = UINT16_TO_INT16(__CPU_GR16__(pCPU, CHAOSVM_R_AX));
	Int16Quotient = Int16Dividend / INT8_TO_INT16(Int8Value);
	Int16Remainder = Int16Dividend % INT8_TO_INT16(Int8Value);

	if (__IS_OVERFLOW_FOR_INT8__( Int16Quotient )) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}

	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AL, INT8_TO_UINT8(INT16_TO_INT8(Int16Quotient)));
	__CPU_GR8_SET__(pCPU, CHAOSVM_R_AH, INT8_TO_UINT8(INT16_TO_INT8(Int16Remainder)));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalIDIV16(PCHAOSVM_CPU pCPU, __sword Int16Value) {
	__sdword Int32Dividend;
	__sdword Int32Quotient;
	__sdword Int32Remainder;
	if (0 == Int16Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	Int32Dividend = UINT32_TO_INT32(__MAKE_UINT32__( __CPU_GR16__(pCPU, CHAOSVM_R_AX), __CPU_GR16__(pCPU, CHAOSVM_R_DX)));
	Int32Quotient = Int32Dividend / INT16_TO_INT32(Int16Value);
	Int32Remainder = Int32Dividend % INT16_TO_INT32(Int16Value);

	if (__IS_OVERFLOW_FOR_INT16__(Int32Quotient)) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}

	__CPU_GR16__(pCPU, CHAOSVM_R_AX) = INT16_TO_UINT16(INT32_TO_INT16(Int32Quotient));
	__CPU_GR16__(pCPU, CHAOSVM_R_DX) = INT16_TO_UINT16(INT32_TO_INT16(Int32Remainder));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ InternalIDIV32(PCHAOSVM_CPU pCPU, __sdword Int32Value) {
	__sqword Int64Dividend;
	__sqword Int64Quotient;
	__sqword Int64Remainder;
	if (0 == Int32Value) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}
	Int64Dividend = UINT64_TO_INT64(__MAKE_UINT64__(__CPU_GR32__(pCPU, CHAOSVM_R_EAX), __CPU_GR32__(pCPU, CHAOSVM_R_EDX)));
	Int64Quotient = Int64Dividend / INT32_TO_INT64(Int32Value);
	Int64Remainder = Int64Dividend % INT32_TO_INT64(Int32Value);

	if (__IS_OVERFLOW_FOR_INT32__(Int64Quotient)) {
		pCPU->InterruptInfomation.bInterruptId = __CPU_INTERRUPT_DE__;
		pCPU->InterruptInfomation.dwErrorCode = 0;
		__SET_LAST_STATUS__(pCPU, __CPU_STATUS_DIVIDE_ERROR__);
		__CPU_SET_INTERRUPT_OCCUR__(pCPU);
		return __GET_LAST_STATUS__(pCPU);
	}

	__CPU_GR32__(pCPU, CHAOSVM_R_EAX) = INT32_TO_UINT32(INT64_TO_INT32(Int64Quotient));
	__CPU_GR32__(pCPU, CHAOSVM_R_EDX) = INT32_TO_UINT32(INT64_TO_INT32(Int64Remainder));

	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_CF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_OF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_SF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_ZF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_AF);
	__CPU_EFLAG_AFFECT_UNDEFINED__((pCPU), CHAOSVM_ER_PF);

	__SET_LAST_STATUS__(pCPU, __CPU_STATUS_EXECUTE_SUCCESS__);
	return __GET_LAST_STATUS__(pCPU);
}
#define __InternalIDIV8_SAFE__(pCPU, Int8Value)          if (!__CPU_STATUS_SUCCESS__(InternalIDIV8(pCPU, Int8Value)))		return __GET_LAST_STATUS__(pCPU);
#define __InternalIDIV16_SAFE__(pCPU, Int16Value)        if (!__CPU_STATUS_SUCCESS__(InternalIDIV16(pCPU, Int16Value)))		return __GET_LAST_STATUS__(pCPU); 
#define __InternalIDIV32_SAFE__(pCPU, Int32Value)        if (!__CPU_STATUS_SUCCESS__(InternalIDIV32(pCPU, Int32Value)))		return __GET_LAST_STATUS__(pCPU);

// HOOK
__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuInternalCallHookRoutineCall(PCHAOSVM_CPU pCPU, __word NewSeg, __dword dwNewAddress, __byte bOpcodeLength) {
	CPU_STATUS Status;
	if (pCPU->HookRoutine.pCall)
		Status = pCPU->HookRoutine.pCall(pCPU, pCPU->pUserContext, NewSeg, (__address)dwNewAddress, bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;
	return Status;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuInternalCallHookRoutineRet(PCHAOSVM_CPU pCPU, __word NewSeg, __dword dwNewAddress, __byte bOpcodeLength) {
	CPU_STATUS Status;
	if (pCPU->HookRoutine.pRet)
		Status = pCPU->HookRoutine.pRet(pCPU, pCPU->pUserContext, NewSeg, (__address)dwNewAddress, bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;
	return Status;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuInternalCallHookRoutineJmp(PCHAOSVM_CPU pCPU, __word NewSeg, __dword dwNewAddress, __byte bOpcodeLength) {
	CPU_STATUS Status;
	if (pCPU->HookRoutine.pJmp)
		Status = pCPU->HookRoutine.pJmp(pCPU, pCPU->pUserContext, NewSeg, (__address)dwNewAddress, bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;
	return Status;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuInternalCallHookRoutineJcc(PCHAOSVM_CPU pCPU, __dword dwNewAddress, __byte bOpcodeLength) {
	CPU_STATUS Status;
	if (pCPU->HookRoutine.pJcc)
		Status = pCPU->HookRoutine.pJcc(pCPU, pCPU->pUserContext, (__address)dwNewAddress, bOpcodeLength);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;
	return Status;
}

__INLINE__ CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuInternalCallHookRoutineExecuteInstruction(PCHAOSVM_CPU pCPU) {
	CPU_STATUS Status;
	if (pCPU->HookRoutine.pExecuteInstruction)
		Status = pCPU->HookRoutine.pExecuteInstruction(pCPU, pCPU->pUserContext);
	else
		Status = __CPU_STATUS_HOOK_NOT_HANDLE__;
	return Status;
}

