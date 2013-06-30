#if !defined(__CHAOSVM_CPU_DISASM_H__)
#define __CHAOSVM_CPU_DISASM_H__

/*
 * 本结构用于保存前缀分析的结果
 */
typedef struct _DISASM_CONTEXT {
	__byte bPrefixLength;
	__bool bIsOperandSize16;//是否是16位操作数模式
	__bool bIsAddressSize16;//是否是16位寻址
	__bool bIsRep;//是否有REP前缀
} DISASM_CONTEXT, *PDISASM_CONTEXT;

__byte __INTERNAL_FUNC__ AnalysePrefix(PDISASM_CONTEXT pDisasmContext, __byte *pCode, __byte bMaxLength);
__byte __INTERNAL_FUNC__ IsCall(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength);
__byte __INTERNAL_FUNC__ IsRepString(PCHAOSVM_CPU pCPU, __byte *pCode, __byte bMaxLength);

#endif
