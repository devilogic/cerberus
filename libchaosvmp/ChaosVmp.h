#if !defined(__CHAOSVMP_H__)
#define __CHAOSVMP_H__

#include "Common.h"
#include "lcrypto.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __MAX_VMP_PROCEDURE__		64

typedef enum _MODRM_LOCAL {
	MSL_MOD = 0,
	MSL_RO = 1,
	MSL_RM = 2
} MODRM_LOCAL;

typedef enum _SIB_LOCAL {
	MSL_SS = 0,
	MSL_INDEX = 1,
	MSL_BASE = 2
} SIB_LOCAL;

#define __MAX_PROTECT_INSTRUCTION__		4096
typedef struct _CHAOSVMP_INSTRUCTION {
	//__bool bRelocate;//此条指令需要重定位
	__integer iInstEncryptLength;//指令部分长度
} CHAOSVMP_INSTRUCTION, *PCHAOSVMP_INSTRUCTION;

typedef struct _CHAOSVMP_JMPTARGET_INST {
	union {
		__address addrAddress;
		__offset ofRVA;//相对于被保护程序基地址的内存偏移
	};
	__offset ofOffsetByProcedure;//相对于被保护函数头的偏移
	__memory pAddress;
	__integer iPrevInstRandLen;//随机抽取上条指令全指令范围内的长度
	__integer iInstIndex;//标记指令的索引
} CHAOSVMP_JMPTARGET_INST, *PCHAOSVMP_JMPTARGET_INST;

typedef struct _CHAOSVMP_JMPTARGET {
	CHAOSVMP_JMPTARGET_INST pInstList[__MAX_PROTECT_INSTRUCTION__];
	__integer iAddressCount;
} CHAOSVMP_JMPTARGET, *PCHAOSVMP_JMPTARGET;

/*
 * 被保护函数的虚拟化结构
 * 这里面有两个重要的字段,在ChaosVm中后,
 * addrProcedureMemoryAddress:表示函数原本的内存地址;
 * pVmpProcedure:表示函数被虚拟化后的地址
 * 这两个字段在混乱虚拟机运行时会参与内存地址转换的重要操作
 */
#define __MAX_JMPTARGET_KEY_LEN__	1024
typedef struct _CHAOSVMP_PROCEDURE {
	__bool bHeader;//是否是头函数
	//////////////////////////////////////////////////////////////////////////
	//保护后的函数相关信息
	union {
		__address addrRealAddress;
		__address addrProcedureMemoryAddress;//函数头内存地址
		__offset ofProcedureMemoryAddress;//函数头内存RVA,被保护函数真实所在的位置
	};
	union {
		__address addrVisualAddress;
		__memory pVmpProcedure;
		__offset ofVmpProcedureRVA;//这个RVA是加密后被保护函数所在的RVA
	};
	__integer iSize;//函数的长度
	__dword dwKey;//当前被保护函数的KEY

	//////////////////////////////////////////////////////////////////////////
	// 解密Key定义
	__offset ofKeyRVA;//当前被保护函数的Key的RVA
	union {
		__bool bUseProcKey;//是否采用函数Key
		__integer iKeySize;//当前被保护函数的Key的长度,如果此长度为0,则采用随机选取
	};
	__dword dwProcKey;//函数Key
	
	CHAOSVMP_JMPTARGET JmpTargetRecord;//记录跳转目标地址
	CHAOSVMP_INSTRUCTION ProtectInstruction[__MAX_PROTECT_INSTRUCTION__];//当前函数的所有指令信息
	__integer iInstCount;//指令计数

	__byte ModRmTbl[0x03];
	__byte SibTbl[0x03];
} CHAOSVMP_PROCEDURE, *PCHAOSVMP_PROCEDURE;

// 产生密钥
#define __GenProcedureKey__(p, s)				PolyXorKey(crc32(p, s))

// 要外部编写的回调函数
#define __VMP_INST_NOT_SUPPORT__				0x81								//检测到此指令ChaosVmp当前版本不支持
__void __INTERNAL_FUNC__ VmpThisInstructionErrorNotification(__integer iError, __char *pInstHex, __char *pInst, __integer iInstLength, __offset ofOffset);

// 加密函数和转换函数的函数类型定义
typedef __byte (__INTERNAL_FUNC__ *FPOpcodeExchange)(__byte bOpcode);
typedef __byte* (__INTERNAL_FUNC__ *FPModRmSibExchage)(__byte *bOpcode);
typedef __dword (__INTERNAL_FUNC__ *FPVmHash)(__memory pPoint, __integer iSize);
typedef __integer (__INTERNAL_FUNC__ *FPVmEncrypt)(__memory pIn, __integer iSize, __dword dwKey, __memory pOut);
typedef __integer (__INTERNAL_FUNC__ *FPVmDecrypt)(__memory pIn, __integer iSize, __dword dwKey, __memory pOut);
typedef __integer (__INTERNAL_FUNC__ *FPVmInstRemainEncrypt)(__memory pIn, __integer iSize, __dword dwKey, __memory pOut);
typedef __integer (__INTERNAL_FUNC__ *FPVmInstRemainDecrypt)(__memory pIn, __integer iSize, __dword dwKey, __memory pOut);

__void __API__ GenerateRandOpcodeTable(__byte *pOpcode, FPOpcodeExchange pOpcodeExchange);
__byte * __API__ GenerateRandModRmTable(__byte *pModRm, FPModRmSibExchage pModRmSibExchage);
__byte * __API__ GenerateRandSibTable(__byte *pSib, FPModRmSibExchage pModRmSibExchage);

PCHAOSVMP_PROCEDURE __API__ VmpThisProcedure(__memory pProcedure, __integer iSize, __offset ofProcedureRVA, FPVmHash pVmHash, \
											FPVmEncrypt pVmEncrypt, FPVmInstRemainEncrypt pInstRemainEncrypt, __byte *pOpcode1Tbl, \
											__byte *pOpcode2Tbl, __byte *pModRmTbl, __byte *pSibTbl, __memory pInvokeThunkCode, __integer iInvokeThunkCodeSize, \
											__dword dwKey, __bool bHeader, __dword *pNextKey, \
											__memory pKeyProcedure, __integer iKeyProcedureSize, __offset ofKeyProcedureRVA);

#if defined(__cplusplus)
}
#endif

#endif
