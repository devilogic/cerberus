__INLINE__ __bool __INTERNAL_FUNC__ FindRegisterFromPrevList(PX86INSTRUCTION pInstruction, enum ud_type TargetReg) {
	PX86INSTRUCTION pCurr = pInstruction;
	while (pCurr) {
		ud_t *pud_obj = &(pInstruction->ud_obj);
		/*
		 * 这里没有考虑那些不进行存储的指令
		 */
		if (pud_obj->operand[0].type == UD_OP_REG) {
			if (pud_obj->operand[0].base == TargetReg)
				return TRUE;
		}
		pCurr = pCurr->pPrev;
	}

	return FALSE;
}

__INLINE__ __void __INTERNAL_FUNC__ ErrorLogicModrmSib(PX86INSTRUCTION pInstruction) {
	ud_t *pud_obj = &(pInstruction->ud_obj);
	__address addrStartAddress = pInstruction->addrMemoryBlockStart;
	__integer iSize = pInstruction->iBlockSize;
	__memory pMem = pInstruction->pMem;

	// 无操作数直接退出
	if (pud_obj->operand[0].type == UD_NONE)
		return;

	// 只要是引用非32位一切算违法行为
	if (pud_obj->pfx_adr == 0x67) {
		pInstruction->bErrorLogicInstruction = TRUE;
		return;
	}

	if ((pud_obj->operand[0].type == UD_OP_MEM) && (pud_obj->operand[0].base == UD_NONE) && \
		(pud_obj->operand[0].index == UD_NONE) && (pud_obj->operand[0].offset)) {
		__address addrRefAddress = (__address)(pud_obj->operand[0].lval.udword);
		VALID_ADDR ValidAddr = CheckValidAddress(pMem, addrRefAddress, CHK_IN_IMAGE_MEM);
		if (__IsInvalidAddressLevel__(ValidAddr, IN_IMAGE_MEM)) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}
	} else if ((pud_obj->operand[1].type == UD_OP_MEM) && (pud_obj->operand[1].base == UD_NONE) && \
		(pud_obj->operand[1].index == UD_NONE) && (pud_obj->operand[1].offset)) {
		__address addrRefAddress = (__address)(pud_obj->operand[1].lval.udword);
		VALID_ADDR ValidAddr = CheckValidAddress(pMem, addrRefAddress, CHK_IN_IMAGE_MEM);
		if (__IsInvalidAddressLevel__(ValidAddr, IN_IMAGE_MEM)) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}
	} else if ((pud_obj->operand[0].type == UD_OP_MEM) && ((pud_obj->operand[0].base != UD_NONE) || (pud_obj->operand[0].index != UD_NONE))) {
		if (!(pInstruction->pPrev)) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}

		/*
		 * 取出寄存器,进行反馈分析
		 * 寻找base寄存器
		 */
		if (pud_obj->operand[0].base != UD_NONE) {
			if (!FindRegisterFromPrevList(pInstruction, pud_obj->operand[0].base)) {
				pInstruction->bErrorLogicInstruction = TRUE;
				return;
			}
		}

		// 寻找index
		if (pud_obj->operand[0].index != UD_NONE) {
			if (!FindRegisterFromPrevList(pInstruction, pud_obj->operand[0].index)) {
				pInstruction->bErrorLogicInstruction = TRUE;
				return;
			}
		}
	} else if ((pud_obj->operand[1].type == UD_OP_MEM) && ((pud_obj->operand[1].base != UD_NONE) || (pud_obj->operand[1].index != UD_NONE))) {
		if (!(pInstruction->pPrev)) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}
		/*
		 * 取出寄存器,进行反馈分析
		 * 寻找base寄存器
		 */
		if (pud_obj->operand[1].base != UD_NONE) {
			if (!FindRegisterFromPrevList(pInstruction, pud_obj->operand[1].base)) {
				pInstruction->bErrorLogicInstruction = TRUE;
				return;
			}
		}
		// 寻找index
		if (pud_obj->operand[1].index != UD_NONE) {
			if (!FindRegisterFromPrevList(pInstruction, pud_obj->operand[1].index)) {
				pInstruction->bErrorLogicInstruction = TRUE;
				return;
			}
		}
	}/* end else if */
}

__INLINE__ __void __INTERNAL_FUNC__ ErrorLogicJcc(PX86INSTRUCTION pInstruction) {
	__address addrTargetAddress = 0, addrCurrentAddress = pInstruction->addrCurrMemoryAddress;
	__address addrStartAddress = pInstruction->addrMemoryBlockStart;
	__integer iSize = pInstruction->iBlockSize;
	ud_t *pud_obj = &(pInstruction->ud_obj);

	if (pud_obj->operand[0].type == UD_OP_JIMM) {
		if (pud_obj->operand[0].size == 8) {
			__byte bOffset = pud_obj->operand[0].lval.ubyte;
			if (__IsNegative8__(bOffset)) {
				bOffset = __JmpUpOffset__(bOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - bOffset;
			} else {
				bOffset = __JmpDownOffset__(bOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + bOffset;
			}
		} else if (pud_obj->operand[0].size == 16) {
			__word wOffset = pud_obj->operand[0].lval.uword;
			if (__IsNegative16__(wOffset)) {
				wOffset = __JmpUpOffset__(wOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - wOffset;
			} else {
				wOffset = __JmpDownOffset__(wOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + wOffset;
			}
		} else if (pud_obj->operand[0].size == 32) {
			__dword dwOffset = pud_obj->operand[0].lval.udword;
			if (__IsNegative32__(dwOffset)) {
				dwOffset = __JmpUpOffset__(dwOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - dwOffset;
			} else {
				dwOffset = __JmpDownOffset__(dwOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + dwOffset;
			}
		}

		// 如果是JCC跳转范围不能超过当前段
		if ((addrTargetAddress < addrStartAddress) || (addrTargetAddress >= (addrStartAddress + iSize))) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}
	}/* end if */
	else if (pud_obj->operand[0].type == UD_OP_MEM)
		ErrorLogicModrmSib(pInstruction);
}

__INLINE__ __void __INTERNAL_FUNC__ ErrorLogicJmp(PX86INSTRUCTION pInstruction) {
	VALID_ADDR ValidAddr;
	__address addrTargetAddress = 0, addrCurrentAddress = pInstruction->addrCurrMemoryAddress;
	__memory pMem = pInstruction->pMem;
	ud_t *pud_obj = &(pInstruction->ud_obj);

	if (pud_obj->operand[0].type == UD_OP_JIMM) {
		if (pud_obj->operand[0].size == 8) {
			__byte bOffset = pud_obj->operand[0].lval.ubyte;
			if (__IsNegative8__(bOffset)) {
				bOffset = __JmpUpOffset__(bOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - bOffset;
			} else {
				bOffset = __JmpDownOffset__(bOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + bOffset;
			}
		} else if (pud_obj->operand[0].size == 16) {
			__word wOffset = pud_obj->operand[0].lval.uword;
			if (__IsNegative16__(wOffset)) {
				wOffset = __JmpUpOffset__(wOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - wOffset;
			} else {
				wOffset = __JmpDownOffset__(wOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + wOffset;
			}
		} else if (pud_obj->operand[0].size == 32) {
			__dword dwOffset = pud_obj->operand[0].lval.udword;
			if (__IsNegative32__(dwOffset)) {
				dwOffset = __JmpUpOffset__(dwOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress - dwOffset;
			} else {
				dwOffset = __JmpDownOffset__(dwOffset, ud_insn_len(pud_obj));
				addrTargetAddress = addrCurrentAddress + dwOffset;
			}
		}

		// 如果是JMP/CALL跳转范围不能超过代码节
		ValidAddr = CheckValidAddress(pMem, addrTargetAddress, CHK_IN_CAN_EXEC);
		if (__IsInvalidAddressLevel__(ValidAddr, IN_CAN_EXEC)) {
			pInstruction->bErrorLogicInstruction = TRUE;
			return;
		}
	} else if (pud_obj->operand[0].type == UD_OP_MEM)
		ErrorLogicModrmSib(pInstruction);
}


#define __ErrorLogicDefaultHandle__(pInstruction)			(pInstruction)->bErrorLogicInstruction = TRUE
#define __ErrorLogicWithAccessEspEbp__(pInstruction){\
	ud_t *pud_obj;\
	ErrorLogicModrmSib(pInstruction);\
	pud_obj = &(pInstruction->ud_obj);\
	if (pud_obj->operand[0].type == UD_OP_REG){\
		if ((pud_obj->operand[0].base == UD_R_ESP) || (pud_obj->operand[0].base == UD_R_EBP))\
			pInstruction->bErrorLogicInstruction = TRUE;}\
	if (pud_obj->operand[1].type == UD_OP_REG){\
		if ((pud_obj->operand[1].base == UD_R_ESP) || (pud_obj->operand[1].base == UD_R_EBP))\
			pInstruction->bErrorLogicInstruction = TRUE;}}
/*
 * 指令处理
 */
__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_I3dnow(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaaa(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaad(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaam(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaas(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iadc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iadd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddsubpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iaddsubps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iand(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iandpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iandps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iandnpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iandnps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iarpl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsxd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibound(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibsf(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibsr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibswap(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibtc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibtr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ibts(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icall(PX86INSTRUCTION pInstruction) {
	ErrorLogicJmp(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icbw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icwde(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icdqe(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iclc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iclflush(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iclgi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icli(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iclts(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovo(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovno(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovae(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovz(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovnz(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovbe(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmova(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovns(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovnp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovge(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovle(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmovg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmp(PX86INSTRUCTION pInstruction) {
	ErrorLogicModrmSib(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmppd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpsb(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpsw(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpsd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpsq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpxchg(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icmpxchg8b(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icomisd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icomiss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icpuid(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtdq2pd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtdq2ps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtpd2dq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtpd2pi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtpd2ps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtpi2ps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtpi2pd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtps2dq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtps2pi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtps2pd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtsd2si(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtsd2ss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtsi2ss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtss2si(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtss2sd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttpd2pi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttpd2dq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttps2dq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttps2pi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttsd2si(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvtsi2sd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icvttss2si(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icwd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icdq(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Icqo(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idaa(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idas(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idec(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idiv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idivpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idivps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idivsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idivss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iemms(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ienter(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_If2xm1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifabs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifadd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifaddp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifbld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifbstp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifchs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifclex(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmove(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovbe(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovu(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovnb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovne(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovnbe(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcmovnu(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifucomi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcom(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcom2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcomp3(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcomi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifucomip(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcomip(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcomp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcomp5(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcompp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifcos(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifdecstp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifdiv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifdivp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifdivr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifdivrp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifemms(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iffree(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iffreep(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ificom(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ificomp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifild(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifncstp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifninit(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifiadd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifidivr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifidiv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifisub(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifisubr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifist(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifistp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifisttp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifld1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldl2t(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldl2e(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldlpi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldlg2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldln2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldz(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldcw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifldenv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifmul(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifmulp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifimul(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifnop(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifpatan(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifprem(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifprem1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifptan(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifrndint(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifrstor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifnsave(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifscale(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsin(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsincos(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsqrt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifstp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifstp1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifstp8(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifstp9(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifst(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifnstcw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifnstenv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifnstsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsub(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsubp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsubr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifsubrp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iftst(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifucom(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifucomp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifucompp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxam(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxch(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxch4(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxch7(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxrstor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifxsave(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifpxtract(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifyl2x(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ifyl2xp1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ihaddpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ihaddps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ihlt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ihsubpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ihsubps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iidiv(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iin(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iimul(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinsb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iint1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iint3(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iint(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinto(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinvd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinvlpg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinvlpga(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iiretw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iiretd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iiretq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijo(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijno(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijb(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijae(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijz(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijnz(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijbe(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ija(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijs(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijns(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijp(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijnp(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijl(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijge(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijle(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijg(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijcxz(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijecxz(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijrcxz(PX86INSTRUCTION pInstruction) {
	ErrorLogicJcc(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ijmp(PX86INSTRUCTION pInstruction) {
	ErrorLogicJmp(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilahf(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilar(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilddqu(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ildmxcsr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilds(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilea(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iles(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilfs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilgs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilidt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ileave(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilfence(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilgdt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Illdt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilmsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilock(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilodsb(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilodsw(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilodsd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilodsq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iloopnz(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iloope(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iloop(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ilsl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iltr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imaskmovq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imaxpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imaxps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imaxsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imaxss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imfence(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iminpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iminps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iminsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iminss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imonitor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imov(PX86INSTRUCTION pInstruction) {
	ErrorLogicModrmSib(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovapd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovaps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovddup(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovdqa(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovdqu(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovdq2q(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovhpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovhps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovlhps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovlpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovlps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovhlps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovmskpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovmskps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovntdq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovnti(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovntpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovntps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovntq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovqa(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovq2dq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsb(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsw(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsldup(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovshdup(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovsx(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovupd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovups(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imovzx(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imul(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imulpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imulps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imulsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imulss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Imwait(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ineg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Inop(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Inot(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ior(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iorpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iorps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iout(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ioutsb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ioutsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ioutsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ioutsq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipacksswb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipackssdw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipackuswb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddsb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddusb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipaddusw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipand(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipandn(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipause(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipavgb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipavgw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpeqb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpeqw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpeqd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpgtb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpgtw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipcmpgtd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipextrw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipinsrw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmaddwd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmaxsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmaxub(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipminsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipminub(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmovmskb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmulhuw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmulhw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmullw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmuludq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipop(PX86INSTRUCTION pInstruction) {
	ErrorLogicModrmSib(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipopa(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipopad(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipopfw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipopfd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipopfq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iprefetch(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iprefetchnta(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iprefetcht0(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iprefetcht1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iprefetcht2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsadbw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipshufd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipshufhw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipshuflw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipshufw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipslldq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsllw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipslld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsllq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsraw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsrad(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsrlw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsrld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsrlq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsrldq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubsb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubusb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipsubusw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpckhbw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpckhwd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpckhdq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpckhqdq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpcklbw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpcklwd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpckldq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipunpcklqdq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipi2fw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipi2fd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipf2iw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipf2id(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfnacc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfpnacc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfcmpge(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfmin(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfrcp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfrsqrt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfsub(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfadd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfcmpgt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfmax(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfrcpit1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfrspit1(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfsubr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfacc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfcmpeq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfmul(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipfrcpit2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipmulhrw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipswapd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipavgusb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipush(PX86INSTRUCTION pInstruction) {
	ErrorLogicModrmSib(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipusha(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipushad(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipushfw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipushfd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipushfq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ipxor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ircl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ircr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irol(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iror(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ircpps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ircpss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irdmsr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irdpmc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irdtsc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irdtscp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irepne(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irep(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iret(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iretf(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irsm(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irsqrtps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Irsqrtss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isahf(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isal(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isalc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isar(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isbb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iscasb(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iscasw(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iscasd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iscasq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iseto(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetno(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetnb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetz(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetnz(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetbe(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iseta(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isets(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetns(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetnp(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetl(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetge(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetle(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isetg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isfence(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isgdt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishrd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishufpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ishufps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isidt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isldt(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ismsw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isqrtps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isqrtpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isqrtsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isqrtss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istc(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istgi(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isti(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iskinit(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istmxcsr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istosb(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istosw(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istosd(PX86INSTRUCTION pInstruction) {
	//
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istosq(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Istr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isub(PX86INSTRUCTION pInstruction) {
	ErrorLogicModrmSib(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isubpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isubps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isubsd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isubss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iswapgs(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isyscall(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isysenter(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isysexit(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Isysret(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Itest(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iucomisd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iucomiss(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iud2(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iunpckhpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iunpckhps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iunpcklps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iunpcklpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iverr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iverw(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmcall(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmclear(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmxon(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmptrld(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmptrst(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmresume(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmxoff(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmrun(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmmcall(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmload(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ivmsave(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iwait(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iwbinvd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iwrmsr(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixadd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixchg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixlatb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicWithAccessEspEbp__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixorpd(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ixorps(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Idb(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Iinvalid(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Id3vil(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Ina(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_reg(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_rm(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_vendor(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_x87(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_mode(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_osize(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_asize(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Igrp_mod(PX86INSTRUCTION pInstruction) {
	__ErrorLogicDefaultHandle__(pInstruction);
}

__void __INTERNAL_FUNC__ AnalyzeDataFromInstructionDispatcher_Inone(PX86INSTRUCTION pInstruction) {
	//////////////////////////////////////////////////////////////////////////
}
