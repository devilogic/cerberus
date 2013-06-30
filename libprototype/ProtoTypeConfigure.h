#if !defined(__PROTOTYPECONFIGURE_H__)
#define __PROTOTYPECONFIGURE_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __MAX_CIPHER_KEY__			32

typedef struct _PROTOTYPE_MATHEXP_ASM_CONFIGURE {
	ASMER_BIT Bit;//操作数位
	ASMER_TYPE ResultReg;//结果寄存器
	ASMER_TYPE VarReg;//变量所用的寄存器
	union{
		ASMER_TYPE KeyReg;//密钥寄存器
		ASMER_TYPE TmpReg;//临时寄存器
	};
} PROTOTYPE_MATHEXP_ASM_CONFIGURE, *PPROTOTYPE_MATHEXP_ASM_CONFIGURE;
typedef PROTOTYPE_MATHEXP_ASM_CONFIGURE PROTOTYPE_CIPHEREXP_ASM_CONFIGURE, *PPROTOTYPE_CIPHEREXP_ASM_CONFIGURE;

typedef struct _PROTOTYPE_CONFIGURE {
	union {
		__bool MathExpRollArray[100];//数学函数骨子队列
		__bool CipherExpRollArray[100];//解密算是骨子队列
	};
} PROTOTYPE_CONFIGURE, *PPROTOTYPE_CONFIGURE;

#if defined(__cplusplus)
}
#endif

#endif
