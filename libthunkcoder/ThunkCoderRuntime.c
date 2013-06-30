/*
 * 用于确定在花指令运行过程中哪些寄存器可以使用,哪些不能使用
 */
#include "ThunkCoderRuntime.h"

THUNKCODER_REGISTER __INTERNAL_FUNC__ AsmTokenToThunkCoderRegiste(ASMER_TYPE AsmToken) {
	THUNKCODER_REGISTER ThunkCoderRegister;
	switch (AsmToken) {
	case R_AL:case R_AH:case R_AX:case R_EAX:
	ThunkCoderRegister = TC_REG_EAX;break;
	case R_CL:case R_CH:case R_CX:case R_ECX:
	ThunkCoderRegister = TC_REG_ECX;break;
	case R_DL:case R_DH:case R_DX:case R_EDX:
	ThunkCoderRegister = TC_REG_EDX;break;
	case R_BL:case R_BH:case R_BX:case R_EBX:
	ThunkCoderRegister = TC_REG_EBX;break;
	case R_SP:case R_ESP:
	ThunkCoderRegister = TC_REG_ESP;break;
	case R_BP:case R_EBP:
	ThunkCoderRegister = TC_REG_EBP;break;
	case R_SI:case R_ESI:
	ThunkCoderRegister = TC_REG_ESI;break;
	case R_DI:case R_EDI:
	ThunkCoderRegister = TC_REG_EDI;break;
	}
	return ThunkCoderRegister;
}

THUNKCODER_REGISTER __INTERNAL_FUNC__ ChooseRegisterToken() {
	THUNKCODER_REGISTER AsmToken = TC_REG_EAX;
	do { 
		AsmToken = TC_REG_EAX + (GetRandDword() % __MAX_THUNKCODER_REGISTER__);
		if (AsmToken == TC_REG_EBP) || (AsmToken == TC_REG_ESP) continue;
	} while (TRUE);
	return AsmToken;
}

PTHUNKCODER_RUNTIME __INTERNAL_FUNC__ GenerateThunkCoderRuntime(__integer iTmpVarCount, __integer iTmpVarBase, __integer iVarBase) {
	PTHUNKCODER_RUNTIME pThunkCoderRuntime = NULL;
	pThunkCoderRuntime = __logic_new__(THUNKCODER_RUNTIME, 1);
	memset((pThunkCoderRuntime), 0, sizeof(THUNKCODER_RUNTIME));
	pThunkCoderRuntime->pUseTmpVar = __logic_new__(__bool, iTmpVarCount);
	pThunkCoderRuntime->iTmpVariableCount = iTmpVarCount;
	pThunkCoderRuntime->iTmpVariableBase = iTmpVarBase;
	pThunkCoderRuntime->iVariableBase = iVarBase;
	return pThunkCoderRuntime;
}

__void __INTERNAL_FUNC__ DestoryThunkCoderRuntime(PTHUNKCODER_RUNTIME pThunkCoderRuntime) {
	if (pThunkCoderRuntime) {
		if (pThunkCoderRuntime->pUseTmpVar) __logic_delete__(pThunkCoderRuntime->pUseTmpVar);
		__logic_delete__(pThunkCoderRuntime);
		pThunkCoderRuntime = NULL;
	}
}
