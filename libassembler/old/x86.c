/*
 * 用于编译x86指令
 */

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 37             AAA              Invalid           Valid          ASCII adjust AL after addition.
 *
 * Description
 * Adjusts the sum of two unpacked BCD values to create an unpacked BCD result. The
 * AL register is the implied source and destination operand for this instruction. The AAA
 * instruction is only useful when it follows an ADD instruction that adds (binary addition)
 * two unpacked BCD values and stores a byte result in the AL register. The AAA
 * instruction then adjusts the contents of the AL register to contain the correct 1-digit
 * unpacked BCD result.
 * If the addition produces a decimal carry, the AH register increments by 1, and the CF
 * and AF flags are set. If there was no decimal carry, the CF and AF flags are cleared
 * and the AH register is unchanged. In either case, bits 4 through 7 of the AL register
 * are set to 0.
 * This instruction executes as described in compatibility mode and legacy mode. It is
 * not valid in 64-bit mode.
 * Operation
 * IF 64-Bit Mode
 * THEN
 * #UD;
 * ELSE
 * IF ((AL AND 0FH) > 9) or (AF = 1)
 * THEN
 * AL ← AL + 6;
 * AH ← AH + 1;
 * AF ← 1;
 * CF ← 1;
 * AL ← AL AND 0FH;
 * ELSE
 * AF ← 0;
 * CF ← 0;
 * AL ← AL AND 0FH;
 * FI;
 * FI;
 * Flags Affected
 * The AF and CF flags are set to 1 if the adjustment results in a decimal carry; otherwise
 * they are set to 0. The OF, SF, ZF, and PF flags are undefined.
 * Opcode Instruction 64-Bit Mode Compat/
 * Leg Mode
 * Description
 * 37 AAA Invalid Valid ASCII adjust AL after addition.
 * 3-20 Vol. 2A AAA—ASCII Adjust After Addition
 * INSTRUCTION SET REFERENCE, A-M
 * Protected Mode Exceptions
 * #UD If the LOCK prefix is used.
 * Real-Address Mode Exceptions
 * Same exceptions as protected mode.
 * Virtual-8086 Mode Exceptions
 * Same exceptions as protected mode.
 * Compatibility Mode Exceptions
 * Same exceptions as protected mode.
 * 64-Bit Mode Exceptions
 * #UD If in 64-bit mode.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_AAA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	if (OptForm == OF_OP) {
		__MemPut8Bits__(pInstBuf, 0x37);
		return 1;
	}
	return 0;
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * D5 0A          AAD              Invalid           Valid          ASCII adjust AX before division.
 * D5 ib          (No mnemonic)    Invalid           Valid          Adjust AX before division to
 *                                                                  number base imm8.
 * Description
 * Adjusts two unpacked BCD digits (the least-significant digit in the AL register and the
 * most-significant digit in the AH register) so that a division operation performed on
 * the result will yield a correct unpacked BCD value. The AAD instruction is only useful
 * when it precedes a DIV instruction that divides (binary division) the adjusted value in
 * the AX register by an unpacked BCD value.
 * The AAD instruction sets the value in the AL register to (AL + (10 * AH)), and then
 * clears the AH register to 00H. The value in the AX register is then equal to the binary
 * equivalent of the original unpacked two-digit (base 10) number in registers AH
 * and AL.
 * The generalized version of this instruction allows adjustment of two unpacked digits
 * of any number base (see the “Operation” section below), by setting the imm8 byte to
 * the selected number base (for example, 08H for octal, 0AH for decimal, or 0CH for
 * base 12 numbers). The AAD mnemonic is interpreted by all assemblers to mean
 * adjust ASCII (base 10) values. To adjust values in another number base, the instruction
 * must be hand coded in machine code (D5 imm8).
 * This instruction executes as described in compatibility mode and legacy mode. It is
 * not valid in 64-bit mode.
 * Operation
 * IF 64-Bit Mode
 * THEN
 * #UD;
 * ELSE
 * tempAL ← AL;
 * tempAH ← AH;
 * AL ← (tempAL + (tempAH ∗ imm8)) AND FFH;
 * (* imm8 is set to 0AH for the AAD mnemonic.*)
 * AH ← 0;
 * FI;
 * The immediate value (imm8) is taken from the second byte of the instruction.
 * INSTRUCTION SET REFERENCE, A-M
 * Flags Affected
 * The SF, ZF, and PF flags are set according to the resulting binary value in the AL
 * register; the OF, AF, and CF flags are undefined.
 * Protected Mode Exceptions
 * #UD If the LOCK prefix is used.
 * Real-Address Mode Exceptions
 * Same exceptions as protected mode.
 * Virtual-8086 Mode Exceptions
 * Same exceptions as protected mode.
 * Compatibility Mode Exceptions
 * Same exceptions as protected mode.
 * 64-Bit Mode Exceptions
 * #UD If in 64-bit mode.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_AAD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	if (OptForm == OF_OP) {
		__MemPut8Bits__(pInstBuf, 0xD5);
		__MemPut8Bits__(pInstBuf, 0x0A);
		return 2;
	} else if (OptForm == OF_I8) {
		__MemPut8Bits__(pInstBuf, 0xD5);
		__MemPut8Bits__(pInstBuf, pAsmObj->Operand[0].Val.uByte);
		return 2;
	}
	return 0;
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 04 0A          AAM              Invalid           Valid          ASCII adjust AX after multiply.
 * 04 ib          (No mnemonic)    Invalid           Valid          Adjust AX after multiply to number
 *                                                                  base imm8.
 * Description
 * Adjusts the result of the multiplication of two unpacked BCD values to create a pair
 * of unpacked (base 10) BCD values. The AX register is the implied source and destination
 * operand for this instruction. The AAM instruction is only useful when it follows
 * an MUL instruction that multiplies (binary multiplication) two unpacked BCD values
 * and stores a word result in the AX register. The AAM instruction then adjusts the
 * contents of the AX register to contain the correct 2-digit unpacked (base 10) BCD
 * result.
 * The generalized version of this instruction allows adjustment of the contents of the
 * AX to create two unpacked digits of any number base (see the “Operation” section
 * below). Here, the imm8 byte is set to the selected number base (for example, 08H
 * for octal, 0AH for decimal, or 0CH for base 12 numbers). The AAM mnemonic is interpreted
 * by all assemblers to mean adjust to ASCII (base 10) values. To adjust to
 * values in another number base, the instruction must be hand coded in machine code
 * (D4 imm8).
 * This instruction executes as described in compatibility mode and legacy mode. It is
 * not valid in 64-bit mode.
 * Operation
 * IF 64-Bit Mode
 * THEN
 * #UD;
 * ELSE
 * tempAL ← AL;
 * AH ← tempAL / imm8; (* imm8 is set to 0AH for the AAM mnemonic *)
 * AL ← tempAL MOD imm8;
 * FI;
 * The immediate value (imm8) is taken from the second byte of the instruction.
 * Flags Affected
 * The SF, ZF, and PF flags are set according to the resulting binary value in the AL
 * register. The OF, AF, and CF flags are undefined.
 * INSTRUCTION SET REFERENCE, A-M
 * Protected Mode Exceptions
 * #DE If an immediate value of 0 is used.
 * #UD If the LOCK prefix is used.
 * Real-Address Mode Exceptions
 * Same exceptions as protected mode.
 * Virtual-8086 Mode Exceptions
 * Same exceptions as protected mode.
 * Compatibility Mode Exceptions
 * Same exceptions as protected mode.
 * 64-Bit Mode Exceptions
 * #UD If in 64-bit mode.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_AAM(PASM_OBJ pAsmObj, __memory pInstBuf) {
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	if (OptForm == OF_OP) {
		__MemPut8Bits__(pInstBuf, 0x04);
		__MemPut8Bits__(pInstBuf, 0x0A);
		return 2;
	} else if (OptForm == OF_I8) {
		__MemPut8Bits__(pInstBuf, 0x04);
		__MemPut8Bits__(pInstBuf, pAsmObj->Operand[0].Val.uByte);		
		return 2;
	}
	return 0;	
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 3F             AAS              Invalid           Valid          ASCII adjust AL after subtraction.
 *
 * Description
 * Adjusts the result of the subtraction of two unpacked BCD values to create a
 * unpacked BCD result. The AL register is the implied source and destination operand
 * for this instruction. The AAS instruction is only useful when it follows a SUB instruction
 * that subtracts (binary subtraction) one unpacked BCD value from another and
 * stores a byte result in the AL register. The AAA instruction then adjusts the contents
 * of the AL register to contain the correct 1-digit unpacked BCD result.
 * If the subtraction produced a decimal carry, the AH register decrements by 1, and the
 * CF and AF flags are set. If no decimal carry occurred, the CF and AF flags are cleared,
 * and the AH register is unchanged. In either case, the AL register is left with its top
 * nibble set to 0.
 * This instruction executes as described in compatibility mode and legacy mode. It is
 * not valid in 64-bit mode.
 * Operation
 * IF 64-bit mode
 * THEN
 * #UD;
 * ELSE
 * IF ((AL AND 0FH) > 9) or (AF = 1)
 * THEN
 * AL ← AL – 6;
 * AH ← AH – 1;
 * AF ← 1;
 * CF ← 1;
 * AL ← AL AND 0FH;
 * ELSE
 * CF ← 0;
 * AF ← 0;
 * AL ← AL AND 0FH;
 * FI;
 * FI;
 * Flags Affected
 * The AF and CF flags are set to 1 if there is a decimal borrow; otherwise, they are
 * cleared to 0. The OF, SF, ZF, and PF flags are undefined.
 * INSTRUCTION SET REFERENCE, A-M
 * Protected Mode Exceptions
 * #UD If the LOCK prefix is used.
 * Real-Address Mode Exceptions
 * Same exceptions as protected mode.
 * Virtual-8086 Mode Exceptions
 * Same exceptions as protected mode.
 * Compatibility Mode Exceptions
 * Same exceptions as protected mode.
 * 64-Bit Mode Exceptions
 * #UD If in 64-bit mode.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_AAS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	if (OptForm == OF_OP) {
		__MemPut8Bits__(pInstBuf, 0x3F);
		return 1;
	}
	return 0;
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 14 ib          ADC AL, imm8     Valid             Valid          Add with carry imm8 to AL.
 * 15 iw          ADC AX, imm16    Valid             Valid          Add with carry imm16 to AX.
 * 15 id          ADC EAX,         Valid             Valid          Add with carry imm32 to EAX.
 *                imm32
 * REX.W+15 id    ADC RAX,         Valid             N.E.           Add with carry imm32 sign
 *                imm32                                             extended to 64-bits to RAX.
 * 80 /2 ib       ADC r/m8,        Valid             Valid          Add with carry imm8 to r/m8.
 *                imm8
 * REX+80 /2 ib   ADC r/m8,        Valid             N.E.           Add with carry imm8 to r/m8.
 *                imm8
 * 81 /2 iw       ADC r/m16,       Valid             Valid          Add with carry imm16 to r/m16.
 *                imm16
 * 81 /2 id       ADC r/m32,       Valid             Valid          Add with CF imm32 to r/m32.
 *                imm32
 * REX.W+81 /2 id ADC r/m64,       Valid             N.E.           Add with CF imm32 sign
 *                imm32                                             extended to 64-bits to r/m64.
 * 83 /2 ib       ADC r/m16,       Valid             Valid          Add with CF sign-extended
 *                imm8                                              imm8 to r/m16.
 * 83 /2 ib       ADC r/m32,       Valid             Valid          Add with CF sign-extended
 *                imm8                                              imm8 into r/m32.
 * REX.W+83 /2 ib ADC r/m64,       Valid             N.E.           Add with CF sign-extended
 *                imm8                                              imm8 into r/m64.
 * 10 /r          ADC r/m8, r8     Valid             Valid          Add with carry byte register to
 *                                                                  r/m8.
 * REX+10 /r      ADC r/m8, r8     Valid             N.E.           Add with carry byte register to
 *                                                                  r/m64.
 * 11 /r          ADC r/m16, r16   Valid             Valid          Add with carry r16 to r/m16.
 * 11 /r          ADC r/m32, r32   Valid             Valid          Add with CF r32 to r/m32.
 * REX.W+11 /r    ADC r/m64, r64   Valid             N.E.           Add with CF r64 to r/m64.
 * 12 /r          ADC r8, r/m8     Valid             Valid          Add with carry r/m8 to byte
 *                                                                  register.
 * REX+12 /r      ADC r8, r/m8     Valid             N.E.           Add with carry r/m64 to byte
 *                                                                  register.
 * 13 /r          ADC r16, r/m16   Valid             Valid          Add with carry r/m16 to r16.
 * 13 /r          ADC r32, r/m32   Valid             Valid          Add with CF r/m32 to r32.
 * REX.W+13 /r    ADC r64, r/m64   Valid             N.E.           Add with CF r/m64 to r64.
 *
 * NOTES:
 * In 64-bit mode, r/m8 can not be encoded to access the following byte registers if a REX prefix is
 * used: AH, BH, CH, DH.
 * 
 * Description
 * Adds the destination operand (first operand), the source operand (second operand),
 * and the carry (CF) flag and stores the result in the destination operand. The destination
 * operand can be a register or a memory location; the source operand can be an
 * immediate, a register, or a memory location. (However, two memory operands
 * cannot be used in one instruction.) The state of the CF flag represents a carry from a
 * previous addition. When an immediate value is used as an operand, it is signextended
 * to the length of the destination operand format.
 * The ADC instruction does not distinguish between signed or unsigned operands.
 * Instead, the processor evaluates the result for both data types and sets the OF and
 * CF flags to indicate a carry in the signed or unsigned result, respectively. The SF flag
 * indicates the sign of the signed result.
 * The ADC instruction is usually executed as part of a multibyte or multiword addition
 * in which an ADD instruction is followed by an ADC instruction.
 * This instruction can be used with a LOCK prefix to allow the instruction to be
 * executed atomically.
 * In 64-bit mode, the instruction’s default operation size is 32 bits. Using a REX prefix
 * in the form of REX.R permits access to additional registers (R8-R15). Using a REX
 * prefix in the form of REX.W promotes operation to 64 bits. See the summary chart at
 * the beginning of this section for encoding data and limits.
 * Operation
 * DEST ← DEST + SRC + CF;
 * Flags Affected
 * The OF, SF, ZF, AF, CF, and PF flags are set according to the result.
 * Protected Mode Exceptions
 * #GP(0) If the destination is located in a non-writable segment.
 * If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * If the DS, ES, FS, or GS register is used to access memory and it
 * contains a NULL segment selector.
 * #SS(0) If a memory operand effective address is outside the SS
 * segment limit.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made while the current privilege level is 3.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Real-Address Mode Exceptions
 * #GP If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * #SS If a memory operand effective address is outside the SS
 * segment limit.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Virtual-8086 Mode Exceptions
 * #GP(0) If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * #SS(0) If a memory operand effective address is outside the SS
 * segment limit.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Compatibility Mode Exceptions
 * Same exceptions as in protected mode.
 * 64-Bit Mode Exceptions
 * #SS(0) If a memory address referencing the SS segment is in a noncanonical
 * form.
 * #GP(0) If the memory address is in a non-canonical form.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made while the current privilege level is 3.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ADC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	__integer iInstLength = 0;
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	PASMER_OPERAND pOpt0 = (PASMER_OPERAND)&(pAsmObj->Operand[0]);
	PASMER_OPERAND pOpt1 = (PASMER_OPERAND)&(pAsmObj->Operand[1]);
	if (OptForm == OF_R8_I8) {
		if (pOpt0->Type == R_AL) {
			__MemPut8Bits__(pInstBuf, 0x14);
			__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
			return 2;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x80", 1, 2);
			__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
			iInstLength++;
			return iInstLength;
		}
	} else if (OptForm == OF_R16_I8) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R32_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R64_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R16_I16) {
		__SetPrefix66__(pInstBuf)
		if (pOpt0->Type == R_AX) {
			__MemPut8Bits__(pInstBuf, 0x15);
			__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
			return 4;
		} else {
			iInstLength++;			
			iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
			__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
			iInstLength += 2;
			return iInstLength;
		}
	} else if (OptForm == OF_R32_I32) {
		if (pOpt0->Type == R_EAX) {
			__MemPut8Bits__(pInstBuf, 0x15);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			return 5;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			iInstLegnth += 4;
			return iInstLength;
		}
	} else if (OptForm == OF_R64_I32) {
		if (pOpt0->Type == R_RAX) {
			__SetREX_W__(pInstBuf);
			__MemPut8Bits__(pInstBuf, 0x15);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			return 6;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			iInstLength += 4;
			return iInstLength;
		}
	} else if (OptForm == OF_M8_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x80", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M16_I8) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M32_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M64_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 2);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;		
	} else if (OptForm == OF_M16_I16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
		__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
		iInstLength += 2;
		return iInstLength;
	} else if (OptForm == OF_M32_I32) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
		*(__dword *)(pInstBuf + iInstLength) = pOpt1->Val.uDword;
		iInstLength += 4;
		return iInstLength;
	} else if (OptForm == OF_M64_I32) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 2);
		__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
		iInstLength += 4;
		return iInstLength;
	} else if (OptForm == OF_M8_R8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x10", 1, OPEX_NONE);
	} else if (OptForm == OF_M16_R16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_M32_R32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
	} else if (OptForm == OF_M64_R64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
	} else if (OptForm == OF_R8_M8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x12", 1, OPEX_NONE);
	} else if (OptForm == OF_R16_M16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x13", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_R32_M32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x13", 1, OPEX_NONE);
	} else if (OptForm == OF_R64_M64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x13", 1, OPEX_NONE);
	} else if (OptForm == OF_R8_R8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x10", 1, OPEX_NONE);
	} else if (OptForm == OF_R16_R16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_R32_R32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
	} else if (OptForm == OF_R64_R64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x11", 1, OPEX_NONE);
	}
	return 0;
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 04 ib          ADD AL, imm8     Valid             Valid          Add imm8 to AL.
 * 05 iw          ADD AX, imm16    Valid             Valid          Add imm16 to AX.
 * 05 id          ADD EAX, imm32   Valid             Valid          Add imm32 to EAX.
 * REX.W+05 id    ADD REX, imm32   Valid             N.E.           Add imm32 sign- 
 *                                                                  extended to 64-bits
 *                                                                  to RAX.
 * 80 /0 ib       ADD r/m8, imm8   Valid             Valid          Add imm8 to r/m8.
 * REX+80 /0 ib   ADD r/m8, imm8   Valid             N.E.           Add sign-extended
 *                                                                  imm8 to r/m64.
 * 81 /0 iw       ADD r/m16, imm16 Valid             Valid          Add imm16 to r/m16.
 * 81 /0 id       ADD r/m32, imm32 Valid             Valid          Add imm32 to r/m32.
 * REW.W+81 /0 id ADD r/m64, imm32 Valid             N.E.           Add imm32 sign- 
 *                                                                  extended to 64-bits
 *                                                                  to r/m64.
 * 83 /0 ib       ADD r/m16, imm8  Valid             Valid          Add sign-extended
 *                                                                  imm8 to r/m16.
 * 83 /0 ib       ADD r/m32, imm8  Valid             Valid          Add sign-extended
 *                                                                  imm8 to r/m32.
 * REX.W+83 /0 ib ADD r/m64, imm8  Valid             N.E.           Add sign-extended
 *                                                                  imm8 to r/m64.
 * 00 /r          ADD r/m8, r8     Valid             Valid          Add r8 to r/m8.
 * REX+00 /r      ADD r/m8, r8     Valid             N.E.           Add r8 to r/m8.
 * 01 /r          ADD r/m16, r16   Valid             Valid          Add r16 to r/m16.
 * 01 /r          ADD r/m32, r32   Valid             Valid          Add r32 to r/m32.
 * REX.W+01 /r    ADD r/m64, r64   Valid             N.E.           Add r64 to r/m64.
 * 02 /r          ADD r8, r/m8     Valid             Valid          Add r/m8 to r8.
 * REX+02 /r      ADD r8, r/m8     Valid             N.E.           Add r/m8 to r8.
 * 03 /r          ADD r16, r/m16   Valid             Valid          Add r/m16 to r16.
 * 03 /r          ADD r32, r/m32   Valid             Valid          Add r/m32 to r32.
 * REW.W+03 /r    ADD r64, r/m64   Valid             Valid          Add r/m64 to r64.
 *
 * NOTES:
 * In 64-bit mode, r/m8 can not be encoded to access the following byte registers if a REX prefix is
 * used: AH, BH, CH, DH.
 *
 * Description
 * Adds the destination operand (first operand) and the source operand (second
 * operand) and then stores the result in the destination operand. The destination
 * operand can be a register or a memory location; the source operand can be an immediate,
 * a register, or a memory location. (However, two memory operands cannot be
 * used in one instruction.) When an immediate value is used as an operand, it is signextended
 * to the length of the destination operand format.
 * The ADD instruction performs integer addition. It evaluates the result for both signed
 * and unsigned integer operands and sets the OF and CF flags to indicate a carry (overflow)
 * in the signed or unsigned result, respectively. The SF flag indicates the sign of
 * the signed result.
 * This instruction can be used with a LOCK prefix to allow the instruction to be
 * executed atomically.
 * In 64-bit mode, the instruction’s default operation size is 32 bits. Using a REX prefix
 * in the form of REX.R permits access to additional registers (R8-R15). Using a REX a
 * REX prefix in the form of REX.W promotes operation to 64 bits. See the summary
 * chart at the beginning of this section for encoding data and limits.
 * Operation
 * DEST ← DEST + SRC;
 * Flags Affected
 * The OF, SF, ZF, AF, CF, and PF flags are set according to the result.
 * Protected Mode Exceptions
 * #GP(0) If the destination is located in a non-writable segment.
 * If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * If the DS, ES, FS, or GS register is used to access memory and it
 * contains a NULL segment selector.
 * #SS(0) If a memory operand effective address is outside the SS
 * segment limit.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made while the current privilege level is 3.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Real-Address Mode Exceptions
 * #GP If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * #SS If a memory operand effective address is outside the SS
 * segment limit.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Virtual-8086 Mode Exceptions
 * #GP(0) If a memory operand effective address is outside the CS, DS,
 * ES, FS, or GS segment limit.
 * #SS(0) If a memory operand effective address is outside the SS
 * segment limit.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 * Compatibility Mode Exceptions
 * Same exceptions as in protected mode.
 * 64-Bit Mode Exceptions
 * #SS(0) If a memory address referencing the SS segment is in a noncanonical
 * form.
 * #GP(0) If the memory address is in a non-canonical form.
 * #PF(fault-code) If a page fault occurs.
 * #AC(0) If alignment checking is enabled and an unaligned memory
 * reference is made while the current privilege level is 3.
 * #UD If the LOCK prefix is used but the destination is not a memory
 * operand.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ADD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	__integer iInstLength = 0;
	OPT_FORM OptForm = ToOptForm(pAsmObj);
	PASMER_OPERAND pOpt0 = (PASMER_OPERAND)&(pAsmObj->Operand[0]);
	PASMER_OPERAND pOpt1 = (PASMER_OPERAND)&(pAsmObj->Operand[1]);
	if (OptForm == OF_R8_I8) {
		if (pOpt0->Type == R_AL) {
			__MemPut8Bits__(pInstBuf, 0x04);
			__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
			return 2;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x80", 1, 0);
			__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
			iInstLength++;
			return iInstLength;
		}
	} else if (OptForm == OF_R16_I8) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R32_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R64_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_R16_I16) {
		__SetPrefix66__(pInstBuf)
		if (pOpt0->Type == R_AX) {
			__MemPut8Bits__(pInstBuf, 0x05);
			__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
			return 4;
		} else {
			iInstLength++;			
			iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
			__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
			iInstLength += 2;
			return iInstLength;
		}
	} else if (OptForm == OF_R32_I32) {
		if (pOpt0->Type == R_EAX) {
			__MemPut8Bits__(pInstBuf, 0x05);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			return 5;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			iInstLegnth += 4;
			return iInstLength;
		}
	} else if (OptForm == OF_R64_I32) {
		if (pOpt0->Type == R_RAX) {
			__SetREX_W__(pInstBuf);
			__MemPut8Bits__(pInstBuf, 0x05);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			return 6;
		} else {
			iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
			__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
			iInstLength += 4;
			return iInstLength;
		}
	} else if (OptForm == OF_M8_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x80", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M16_I8) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M32_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;
	} else if (OptForm == OF_M64_I8) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x83", 1, 0);
		__MemPut8Bits__(pInstBuf, pOpt1->Val.uByte);
		iInstLength++;
		return iInstLength;		
	} else if (OptForm == OF_M16_I16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
		__MemPut16Bits__(pInstBuf, pOpt1->Val.uWord);
		iInstLength += 2;
		return iInstLength;
	} else if (OptForm == OF_M32_I32) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
		*(__dword *)(pInstBuf + iInstLength) = pOpt1->Val.uDword;
		iInstLength += 4;
		return iInstLength;
	} else if (OptForm == OF_M64_I32) {
		iInstLength = SetComplexCode(pAsmObj, &pInstBuf, "0x81", 1, 0);
		__MemPut32Bits__(pInstBuf, pOpt1->Val.uDword);
		iInstLength += 4;
		return iInstLength;
	} else if (OptForm == OF_M8_R8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x00", 1, OPEX_NONE);
	} else if (OptForm == OF_M16_R16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_M32_R32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
	} else if (OptForm == OF_M64_R64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
	} else if (OptForm == OF_R8_M8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x02", 1, OPEX_NONE);
	} else if (OptForm == OF_R16_M16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x03", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_R32_M32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x03", 1, OPEX_NONE);
	} else if (OptForm == OF_R64_M64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x03", 1, OPEX_NONE);
	} else if (OptForm == OF_R8_R8) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x00", 1, OPEX_NONE);
	} else if (OptForm == OF_R16_R16) {
		__SetPrefix66__(pInstBuf);
		iInstLength++;
		iInstLength += SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
		return iInstLength;
	} else if (OptForm == OF_R32_R32) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
	} else if (OptForm == OF_R64_R64) {
		return SetComplexCode(pAsmObj, &pInstBuf, "0x01", 1, OPEX_NONE);
	}	
	return 0;
}

/*
 * Opcode         Instruction      64-Bit Mode       Compat/        Description
 *                                                   Leg Mode
 *                                                   
 * 37             AAA              Invalid           Valid          ASCII adjust AL after addition.
 */
__INLINE__ __integer __INTERNAL_FUNC__ Asm_AND(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ARPL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BOUND(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BSF(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BSR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BSWAP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BTC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BTR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_BTS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CALL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CBW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CWDE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CDQE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CLC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CLD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CLFLUSH(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CLI(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CLTS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVNO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVAE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVNZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVBE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVNS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVNP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVGE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVLE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMOVG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPSQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPXCHG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CMPXCHG8B(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CPUID(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CWD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CDQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_CQO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_DAA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_DAS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_DEC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_DIV(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ENTER(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_HLT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IDIV(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IMUL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IN(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INT1(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INT3(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INTO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INVD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_INVLPG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IRETW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IRETD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_IRETQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JNO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JAE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JNZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JBE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JNS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JNP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JGE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JLE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JCXZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JECXZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JRCXZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_JMP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LAHF(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LAR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LDMXCSR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LDS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LES(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LFS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LGS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LSS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LEA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LEAVE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LFENCE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LGDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LIDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LLDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LMSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LOCK(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LODSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LODSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LODSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LODSQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LOOPNZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LOOPE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LOOP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LSL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_LTR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MFENCE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MONITOR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOV(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSX(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVSXD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MOVZX(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MUL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_MWAIT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_NEG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_NOP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_NOT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_OR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_OUT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_OUTSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_OUTSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_OUTSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POPA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POPAD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POPF(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POPFD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POPFQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_POR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PREFETCH(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PUSH(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PUSHA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PUSHAD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PUSHF(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_PUSHFD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
v}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RCL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RCR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ROL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_ROR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RDMSR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RDPMC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RDTSC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_REP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_REPE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_REPZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_REPNE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_REPNZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RET(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_RSM(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SAHF(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SAL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SAR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SHL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SHR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SBB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SCASB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SCASW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SCASD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SCASQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETNO(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETNB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETNZ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETBE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETA(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETNS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETNP(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETGE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETLE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SETG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SFENCE(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SGDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SHLD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SHRD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SIDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SLDT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SMSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STC(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STI(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STMXCSR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STOSB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STOSW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STOSD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STOSQ(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_STR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SUB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SWAPGS(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SYSCALL(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SYSENTER(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SYSEXIT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_SYSRET(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_TEST(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_UD2(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_VERR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_VERW(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_WAIT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_FWAIT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_WBINVD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_WRMSR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_XADD(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_XCHG(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_XLAT(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_XLATB(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}
__INLINE__ __integer __INTERNAL_FUNC__ Asm_XOR(PASM_OBJ pAsmObj, __memory pInstBuf) {
	return 0;
}

__INLINE__ __integer __INTERNAL_FUNC__ Asm_x86(PASM_OBJ pAsmObj, __memory pInstBuf) {
	__integer iInstLength = 0;
	switch (pAsmObj->Inst) {
	case AAA: {
		iInstLength = Asm_AAA(pAsmObj, pInstBuf);
	}break;
	case AAD: {
		iInstLength = Asm_AAD(pAsmObj, pInstBuf);
	}break;
	case AAM: {
		iInstLength = Asm_AAM(pAsmObj, pInstBuf);	
	}break;
	case AAS: {
		iInstLength = Asm_AAS(pAsmObj, pInstBuf);
	}break;
	case ADC: {
		iInstLength = Asm_ADC(pAsmObj, pInstBuf);
	}break;
	case ADD: {
		iInstLength = Asm_ADD(pAsmObj, pInstBuf);
	}break;
	case AND: {
		iInstLength = Asm_AND(pAsmObj, pInstBuf);
	}break;
	case ARPL: {
		iInstLength = Asm_ARPL(pAsmObj, pInstBuf);
	}break;
	case BOUND: {
		iInstLength = Asm_BOUND(pAsmObj, pInstBuf);
	}break;
	case BSF: {
		iInstLength = Asm_BSF(pAsmObj, pInstBuf);
	}break;
	case BSR: {
		iInstLength = Asm_BSR(pAsmObj, pInstBuf);
	}break;
	case BSWAP: {
		iInstLength = Asm_BSWAP(pAsmObj, pInstBuf);
	}break;
	case BT: {
		iInstLength = Asm_BT(pAsmObj, pInstBuf);
	}break;
	case BTC: {
		iInstLength = Asm_BTC(pAsmObj, pInstBuf);
	}break;
	case BTR: {
		iInstLength = Asm_BTR(pAsmObj, pInstBuf);
	}break;
	case BTS: {
		iInstLength = Asm_BTS(pAsmObj, pInstBuf);
	}break;
	case CALL: {
		iInstLength = Asm_CALL(pAsmObj, pInstBuf);
	}break;
	case CBW: {
		iInstLength = Asm_CBW(pAsmObj, pInstBuf);
	}break;
	case CWDE: {
		iInstLength = Asm_CWDE(pAsmObj, pInstBuf);
	}break;
	case CDQE: {
		iInstLength = Asm_CDQE(pAsmObj, pInstBuf);
	}break;
	case CLC: {
		iInstLength = Asm_CLC(pAsmObj, pInstBuf);
	}break;
	case CLD: {
		iInstLength = Asm_CLD(pAsmObj, pInstBuf);
	}break;
	case CLFLUSH: {
		iInstLength = Asm_CLFLUSH(pAsmObj, pInstBuf);
	}break;
	case CLI: {
		iInstLength = Asm_CLI(pAsmObj, pInstBuf);
	}break;
	case CLTS: {
		iInstLength = Asm_CLTS(pAsmObj, pInstBuf);
	}break;
	case CMC: {
		iInstLength = Asm_CMC(pAsmObj, pInstBuf);
	}break;
	case CMOVO: {
		iInstLength = Asm_CMOVO(pAsmObj, pInstBuf);
	}break;
	case CMOVNO: {
		iInstLength = Asm_CMOVNO(pAsmObj, pInstBuf);
	}break;
	case CMOVB: {
		iInstLength = Asm_CMOVB(pAsmObj, pInstBuf);
	}break;
	case CMOVAE: {
		iInstLength = Asm_CMOVAE(pAsmObj, pInstBuf);
	}break;
	case CMOVZ: {
		iInstLength = Asm_CMOVZ(pAsmObj, pInstBuf);
	}break;
	case CMOVNZ: {
		iInstLength = Asm_CMOVNZ(pAsmObj, pInstBuf);
	}break;
	case CMOVBE: {
		iInstLength = Asm_CMOVBE(pAsmObj, pInstBuf);
	}break;
	case CMOVA: {
		iInstLength = Asm_CMOVA(pAsmObj, pInstBuf);
	}break;
	case CMOVS: {
		iInstLength = Asm_CMOVS(pAsmObj, pInstBuf);
	}break;
	case CMOVNS: {
		iInstLength = Asm_CMOVNS(pAsmObj, pInstBuf);
	}break;
	case CMOVP: {
		iInstLength = Asm_CMOVP(pAsmObj, pInstBuf);
	}break;
	case CMOVNP: {
		iInstLength = Asm_CMOVNP(pAsmObj, pInstBuf);
	}break;
	case CMOVL: {
		iInstLength = Asm_CMOVL(pAsmObj, pInstBuf);
	}break;
	case CMOVGE: {
		iInstLength = Asm_CMOVGE(pAsmObj, pInstBuf);
	}break;
	case CMOVLE: {
		iInstLength = Asm_CMOVLE(pAsmObj, pInstBuf);
	}break;
	case CMOVG: {
		iInstLength = Asm_CMOVG(pAsmObj, pInstBuf);
	}break;
	case CMP: {
		iInstLength = Asm_CMP(pAsmObj, pInstBuf);
	}break;
	case CMPSB: {
		iInstLength = Asm_CMPSB(pAsmObj, pInstBuf);
	}break;
	case CMPSW: {
		iInstLength = Asm_CMPSW(pAsmObj, pInstBuf);
	}break;
	case CMPSD: {
		iInstLength = Asm_CMPSD(pAsmObj, pInstBuf);
	}break;
	case CMPSQ: {
		iInstLength = Asm_CMPSQ(pAsmObj, pInstBuf);
	}break;
	case CMPXCHG: {
		iInstLength = Asm_CMPXCHG(pAsmObj, pInstBuf);
	}break;
	case CMPXCHG8B: {
		iInstLength = Asm_CMPXCHG8B(pAsmObj, pInstBuf);
	}break;
	case CPUID: {
		iInstLength = Asm_CPUID(pAsmObj, pInstBuf);
	}break;
	case CWD: {
		iInstLength = Asm_CWD(pAsmObj, pInstBuf);
	}break;
	case CDQ: {
		iInstLength = Asm_CDQ(pAsmObj, pInstBuf);
	}break;
	case CQO: {
		iInstLength = Asm_CQO(pAsmObj, pInstBuf);
	}break;
	case DAA: {
		iInstLength = Asm_DAA(pAsmObj, pInstBuf);
	}break;
	case DAS: {
		iInstLength = Asm_DAS(pAsmObj, pInstBuf);
	}break;
	case DEC: {
		iInstLength = Asm_DEC(pAsmObj, pInstBuf);
	}break;
	case DIV: {
		iInstLength = Asm_DIV(pAsmObj, pInstBuf);
	}break;
	case ENTER: {
		iInstLength = Asm_ENTER(pAsmObj, pInstBuf);
	}break;
	case HLT: {
		iInstLength = Asm_HLT(pAsmObj, pInstBuf);
	}break;
	case IDIV: {
		iInstLength = Asm_IDIV(pAsmObj, pInstBuf);
	}break;
	case IMUL: {
		iInstLength = Asm_IMUL(pAsmObj, pInstBuf);
	}break;
	case IN: {
		iInstLength = Asm_IN(pAsmObj, pInstBuf);
	}break;
	case INC: {
		iInstLength = Asm_INC(pAsmObj, pInstBuf);
	}break;
	case INSB: {
		iInstLength = Asm_INSB(pAsmObj, pInstBuf);
	}break;
	case INSW: {
		iInstLength = Asm_INSW(pAsmObj, pInstBuf);
	}break;
	case INSD: {
		iInstLength = Asm_INSD(pAsmObj, pInstBuf);
	}break;
	case INT1: {
		iInstLength = Asm_INT1(pAsmObj, pInstBuf);
	}break;
	case INT3: {
		iInstLength = Asm_INT3(pAsmObj, pInstBuf);
	}break;
	case INT: {
		iInstLength = Asm_INT(pAsmObj, pInstBuf);
	}break;
	case INTO: {
		iInstLength = Asm_INTO(pAsmObj, pInstBuf);
	}break;
	case INVD: {
		iInstLength = Asm_INVD(pAsmObj, pInstBuf);
	}break;
	case INVLPG: {
		iInstLength = Asm_INVLPG(pAsmObj, pInstBuf);
	}break;
	case IRETW: {
		iInstLength = Asm_IRETW(pAsmObj, pInstBuf);
	}break;
	case IRETD: {
		iInstLength = Asm_IRETD(pAsmObj, pInstBuf);
	}break;
	case IRETQ: {
		iInstLength = Asm_IRETQ(pAsmObj, pInstBuf);
	}break;
	case JO: {
		iInstLength = Asm_JO(pAsmObj, pInstBuf);
	}break;
	case JNO: {
		iInstLength = Asm_JNO(pAsmObj, pInstBuf);
	}break;
	case JB: {
		iInstLength = Asm_JB(pAsmObj, pInstBuf);
	}break;
	case JAE: {
		iInstLength = Asm_JAE(pAsmObj, pInstBuf);
	}break;
	case JZ: {
		iInstLength = Asm_JZ(pAsmObj, pInstBuf);
	}break;
	case JNZ: {
		iInstLength = Asm_JNZ(pAsmObj, pInstBuf);
	}break;
	case JBE: {
		iInstLength = Asm_JBE(pAsmObj, pInstBuf);
	}break;
	case JA: {
		iInstLength = Asm_JA(pAsmObj, pInstBuf);
	}break;
	case JS: {
		iInstLength = Asm_JS(pAsmObj, pInstBuf);
	}break;
	case JNS: {
		iInstLength = Asm_JNS(pAsmObj, pInstBuf);
	}break;
	case JP: {
		iInstLength = Asm_JP(pAsmObj, pInstBuf);
	}break;
	case JNP: {
		iInstLength = Asm_JNP(pAsmObj, pInstBuf);
	}break;
	case JL: {
		iInstLength = Asm_JL(pAsmObj, pInstBuf);
	}break;
	case JGE: {
		iInstLength = Asm_JGE(pAsmObj, pInstBuf);
	}break;
	case JLE: {
		iInstLength = Asm_JLE(pAsmObj, pInstBuf);
	}break;
	case JG: {
		iInstLength = Asm_JG(pAsmObj, pInstBuf);
	}break;
	case JCXZ: {
		iInstLength = Asm_JCXZ(pAsmObj, pInstBuf);
	}break;
	case JECXZ: {
		iInstLength = Asm_JECXZ(pAsmObj, pInstBuf);
	}break;
	case JRCXZ: {
		iInstLength = Asm_JRCXZ(pAsmObj, pInstBuf);
	}break;
	case JMP: {
		iInstLength = Asm_JMP(pAsmObj, pInstBuf);
	}break;
	case LAHF: {
		iInstLength = Asm_LAHF(pAsmObj, pInstBuf);
	}break;
	case LAR: {
		iInstLength = Asm_LAR(pAsmObj, pInstBuf);
	}break;
	case LDMXCSR: {
		iInstLength = Asm_LDMXCSR(pAsmObj, pInstBuf);
	}break;
	case LDS: {
		iInstLength = Asm_LDS(pAsmObj, pInstBuf);
	}break;
	case LES: {
		iInstLength = Asm_LES(pAsmObj, pInstBuf);
	}break;
	case LFS: {
		iInstLength = Asm_LFS(pAsmObj, pInstBuf);
	}break;
	case LGS: {
		iInstLength = Asm_LGS(pAsmObj, pInstBuf);
	}break;
	case LSS: {
		iInstLength = Asm_LSS(pAsmObj, pInstBuf);
	}break;
	case LEA: {
		iInstLength = Asm_LEA(pAsmObj, pInstBuf);
	}break;
	case LEAVE: {
		iInstLength = Asm_LEAVE(pAsmObj, pInstBuf);
	}break;
	case LFENCE: {
		iInstLength = Asm_LFENCE(pAsmObj, pInstBuf);
	}break;
	case LGDT: {
		iInstLength = Asm_LGDT(pAsmObj, pInstBuf);
	}break;
	case LIDT: {
		iInstLength = Asm_LIDT(pAsmObj, pInstBuf);
	}break;
	case LLDT: {
		iInstLength = Asm_LLDT(pAsmObj, pInstBuf);
	}break;
	case LMSW: {
		iInstLength = Asm_LMSW(pAsmObj, pInstBuf);
	}break;
	case LOCK: {
		iInstLength = Asm_LOCK(pAsmObj, pInstBuf);
	}break;
	case LODSB: {
		iInstLength = Asm_LODSB(pAsmObj, pInstBuf);
	}break;
	case LODSW: {
		iInstLength = Asm_LODSW(pAsmObj, pInstBuf);
	}break;
	case LODSD: {
		iInstLength = Asm_LODSD(pAsmObj, pInstBuf);
	}break;
	case LODSQ: {
		iInstLength = Asm_LODSQ(pAsmObj, pInstBuf);
	}break;
	case LOOPNZ: {
		iInstLength = Asm_LOOPNZ(pAsmObj, pInstBuf);
	}break;
	case LOOPE: {
		iInstLength = Asm_LOOPE(pAsmObj, pInstBuf);
	}break;
	case LOOP: {
		iInstLength = Asm_LOOP(pAsmObj, pInstBuf);
	}break;
	case LSL: {
		iInstLength = Asm_LSL(pAsmObj, pInstBuf);
	}break;
	case LTR: {
		iInstLength = Asm_LTR(pAsmObj, pInstBuf);
	}break;
	case MFENCE: {
		iInstLength = Asm_MFENCE(pAsmObj, pInstBuf);
	}break;
	case MONITOR: {
		iInstLength = Asm_MONITOR(pAsmObj, pInstBuf);
	}break;
	case MOV: {
		iInstLength = Asm_MOV(pAsmObj, pInstBuf);
	}break;
	case MOVSB: {
		iInstLength = Asm_MOVSB(pAsmObj, pInstBuf);
	}break;
	case MOVSW: {
		iInstLength = Asm_MOVSW(pAsmObj, pInstBuf);
	}break;
	case MOVSD: {
		iInstLength = Asm_MOVSD(pAsmObj, pInstBuf);
	}break;
	case MOVSQ: {
		iInstLength = Asm_MOVSQ(pAsmObj, pInstBuf);
	}break;
	case MOVSX: {
		iInstLength = Asm_MOVSX(pAsmObj, pInstBuf);
	}break;
	case MOVSXD: {
		iInstLength = Asm_MOVSXD(pAsmObj, pInstBuf);
	}break;
	case MOVZX: {
		iInstLength = Asm_MOVZX(pAsmObj, pInstBuf);
	}break;
	case MUL: {
		iInstLength = Asm_MUL(pAsmObj, pInstBuf);
	}break;
	case MWAIT: {
		iInstLength = Asm_MWAIT(pAsmObj, pInstBuf);
	}break;
	case NEG: {
		iInstLength = Asm_NEG(pAsmObj, pInstBuf);
	}break;
	case NOP: {
		iInstLength = Asm_NOP(pAsmObj, pInstBuf);
	}break;
	case NOT: {
		iInstLength = Asm_NOT(pAsmObj, pInstBuf);
	}break;
	case OR: {
		iInstLength = Asm_OR(pAsmObj, pInstBuf);
	}break;
	case OUT: {
		iInstLength = Asm_OUT(pAsmObj, pInstBuf);
	}break;
	case OUTSB: {
		iInstLength = Asm_OUTSB(pAsmObj, pInstBuf);
	}break;
	case OUTSW: {
		iInstLength = Asm_OUTSW(pAsmObj, pInstBuf);
	}break;
	case OUTSD: {
		iInstLength = Asm_OUTSD(pAsmObj, pInstBuf);
	}break;
	case POP: {
		iInstLength = Asm_POP(pAsmObj, pInstBuf);
	}break;
	case POPA: {
		iInstLength = Asm_POPA(pAsmObj, pInstBuf);
	}break;
	case POPAD: {
		iInstLength = Asm_POPAD(pAsmObj, pInstBuf);
	}break;
	case POPF: {
		iInstLength = Asm_POPF(pAsmObj, pInstBuf);
	}break;
	case POPFD: {
		iInstLength = Asm_POPFD(pAsmObj, pInstBuf);
	}break;
	case POPFQ: {
		iInstLength = Asm_POPFQ(pAsmObj, pInstBuf);
	}break;
	case POR: {
		iInstLength = Asm_POR(pAsmObj, pInstBuf);
	}break;
	case PREFETCH: {
		iInstLength = Asm_PREFETCH(pAsmObj, pInstBuf);
	}break;
	case PUSH: {
		iInstLength = Asm_PUSH(pAsmObj, pInstBuf);
	}break;
	case PUSHA: {
		iInstLength = Asm_PUSHA(pAsmObj, pInstBuf);
	}break;
	case PUSHAD: {
		iInstLength = Asm_PUSHAD(pAsmObj, pInstBuf);
	}break;
	case PUSHF: {
		iInstLength = Asm_PUSHF(pAsmObj, pInstBuf);
	}break;
	case PUSHFD: {
		iInstLength = Asm_PUSHFD(pAsmObj, pInstBuf);
	}break;
	case RCL: {
		iInstLength = Asm_RCL(pAsmObj, pInstBuf);
	}break;
	case RCR: {
		iInstLength = Asm_RCR(pAsmObj, pInstBuf);
	}break;
	case ROL: {
		iInstLength = Asm_ROL(pAsmObj, pInstBuf);
	}break;
	case ROR: {
		iInstLength = Asm_ROR(pAsmObj, pInstBuf);
	}break;
	case RDMSR: {
		iInstLength = Asm_RDMSR(pAsmObj, pInstBuf);
	}break;
	case RDPMC: {
		iInstLength = Asm_RDPMC(pAsmObj, pInstBuf);
	}break;
	case RDTSC: {
		iInstLength = Asm_RDTSC(pAsmObj, pInstBuf);
	}break;
	case REP: {
		iInstLength = Asm_REP(pAsmObj, pInstBuf);
	}break;
	case REPE: {
		iInstLength = Asm_REPE(pAsmObj, pInstBuf);
	}break;
	case REPZ: {
		iInstLength = Asm_REPZ(pAsmObj, pInstBuf);
	}break;
	case REPNE: {
		iInstLength = Asm_REPNE(pAsmObj, pInstBuf);
	}break;
	case REPNZ: {
		iInstLength = Asm_REPNZ(pAsmObj, pInstBuf);
	}break;
	case RET: {
		iInstLength = Asm_RET(pAsmObj, pInstBuf);
	}break;
	case RSM: {
		iInstLength = Asm_RSM(pAsmObj, pInstBuf);
	}break;
	case SAHF: {
		iInstLength = Asm_SAHF(pAsmObj, pInstBuf);
	}break;
	case SAL: {
		iInstLength = Asm_SAL(pAsmObj, pInstBuf);
	}break;
	case SAR: {
		iInstLength = Asm_SAR(pAsmObj, pInstBuf);
	}break;
	case SHL: {
		iInstLength = Asm_SHL(pAsmObj, pInstBuf);
	}break;
	case SHR: {
		iInstLength = Asm_SHR(pAsmObj, pInstBuf);
	}break;
	case SBB: {
		iInstLength = Asm_SBB(pAsmObj, pInstBuf);
	}break;
	case SCASB: {
		iInstLength = Asm_SCASB(pAsmObj, pInstBuf);
	}break;
	case SCASW: {
		iInstLength = Asm_SCASW(pAsmObj, pInstBuf);
	}break;
	case SCASD: {
		iInstLength = Asm_SCASD(pAsmObj, pInstBuf);
	}break;
	case SCASQ: {
		iInstLength = Asm_SCASQ(pAsmObj, pInstBuf);
	}break;
	case SETO: {
		iInstLength = Asm_SETO(pAsmObj, pInstBuf);
	}break;
	case SETNO: {
		iInstLength = Asm_SETNO(pAsmObj, pInstBuf);
	}break;
	case SETB: {
		iInstLength = Asm_SETB(pAsmObj, pInstBuf);
	}break;
	case SETNB: {
		iInstLength = Asm_SETNB(pAsmObj, pInstBuf);
	}break;
	case SETZ: {
		iInstLength = Asm_SETZ(pAsmObj, pInstBuf);
	}break;
	case SETNZ: {
		iInstLength = Asm_SETNZ(pAsmObj, pInstBuf);
	}break;
	case SETBE: {
		iInstLength = Asm_SETBE(pAsmObj, pInstBuf);
	}break;
	case SETA: {
		iInstLength = Asm_SETA(pAsmObj, pInstBuf);
	}break;
	case SETS: {
		iInstLength = Asm_SETS(pAsmObj, pInstBuf);
	}break;
	case SETNS: {
		iInstLength = Asm_SETNS(pAsmObj, pInstBuf);
	}break;
	case SETP: {
		iInstLength = Asm_SETP(pAsmObj, pInstBuf);
	}break;
	case SETNP: {
		iInstLength = Asm_SETNP(pAsmObj, pInstBuf);
	}break;
	case SETL: {
		iInstLength = Asm_SETL(pAsmObj, pInstBuf);
	}break;
	case SETGE: {
		iInstLength = Asm_SETGE(pAsmObj, pInstBuf);
	}break;
	case SETLE: {
		iInstLength = Asm_SETLE(pAsmObj, pInstBuf);
	}break;
	case SETG: {
		iInstLength = Asm_SETG(pAsmObj, pInstBuf);
	}break;
	case SFENCE: {
		iInstLength = Asm_SFENCE(pAsmObj, pInstBuf);
	}break;
	case SGDT: {
		iInstLength = Asm_SGDT(pAsmObj, pInstBuf);
	}break;
	case SHLD: {
		iInstLength = Asm_SHLD(pAsmObj, pInstBuf);
	}break;
	case SHRD: {
		iInstLength = Asm_SHRD(pAsmObj, pInstBuf);
	}break;
	case SIDT: {
		iInstLength = Asm_SIDT(pAsmObj, pInstBuf);
	}break;
	case SLDT: {
		iInstLength = Asm_SLDT(pAsmObj, pInstBuf);
	}break;
	case SMSW: {
		iInstLength = Asm_SMSW(pAsmObj, pInstBuf);
	}break;
	case STC: {
		iInstLength = Asm_STC(pAsmObj, pInstBuf);
	}break;
	case STD: {
		iInstLength = Asm_STD(pAsmObj, pInstBuf);
	}break;
	case STI: {
		iInstLength = Asm_STI(pAsmObj, pInstBuf);
	}break;
	case STMXCSR: {
		iInstLength = Asm_STMXCSR(pAsmObj, pInstBuf);
	}break;
	case STOSB: {
		iInstLength = Asm_STOSB(pAsmObj, pInstBuf);
	}break;
	case STOSW: {
		iInstLength = Asm_STOSW(pAsmObj, pInstBuf);
	}break;
	case STOSD: {
		iInstLength = Asm_STOSD(pAsmObj, pInstBuf);
	}break;
	case STOSQ: {
		iInstLength = Asm_STOSQ(pAsmObj, pInstBuf);
	}break;
	case STR: {
		iInstLength = Asm_STR(pAsmObj, pInstBuf);
	}break;
	case SUB: {
		iInstLength = Asm_SUB(pAsmObj, pInstBuf);
	}break;
	case SWAPGS: {
		iInstLength = Asm_SWAPGS(pAsmObj, pInstBuf);
	}break;
	case SYSCALL: {
		iInstLength = Asm_SYSCALL(pAsmObj, pInstBuf);
	}break;
	case SYSENTER: {
		iInstLength = Asm_SYSENTER(pAsmObj, pInstBuf);
	}break;
	case SYSEXIT: {
		iInstLength = Asm_SYSEXIT(pAsmObj, pInstBuf);
	}break;
	case SYSRET: {
		iInstLength = Asm_SYSRET(pAsmObj, pInstBuf);
	}break;
	case TEST: {
		iInstLength = Asm_TEST(pAsmObj, pInstBuf);
	}break;
	case UD2: {
		iInstLength = Asm_UD2(pAsmObj, pInstBuf);
	}break;
	case VERR: {
		iInstLength = Asm_VERR(pAsmObj, pInstBuf);
	}break;
	case VERW: {
		iInstLength = Asm_VERW(pAsmObj, pInstBuf);
	}break;
	case WAIT: {
		iInstLength = Asm_WAIT(pAsmObj, pInstBuf);
	}break;
	case FWAIT: {
		iInstLength = Asm_FWAIT(pAsmObj, pInstBuf);
	}break;
	case WBINVD: {
		iInstLength = Asm_WBINVD(pAsmObj, pInstBuf);
	}break;
	case WRMSR: {
		iInstLength = Asm_WRMSR(pAsmObj, pInstBuf);
	}break;
	case XADD: {
		iInstLength = Asm_XADD(pAsmObj, pInstBuf);
	}break;
	case XCHG: {
		iInstLength = Asm_XCHG(pAsmObj, pInstBuf);
	}break;
	case XLAT: {
		iInstLength = Asm_XLAT(pAsmObj, pInstBuf);
	}break;
	case XLATB: {
		iInstLength = Asm_XLATB(pAsmObj, pInstBuf);
	}break;
	case XOR: {
		iInstLength = Asm_XOR(pAsmObj, pInstBuf);
	}break;
	default:
	}/* end switch */
	return iInstLength;
}
