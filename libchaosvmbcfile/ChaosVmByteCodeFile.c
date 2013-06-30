#include "ChaosVmByteCodeFile.h"
#include "lcrypto.h"
#include "Support.h"

/*
 * 介绍:
 *	产生混乱虚拟机的字节码文件,成功返回字节码文件的节头,失败返回0
 *
 * ByteCode文件结构:
 *	CHAOSVM_EMULATION_BYTECODE_FILE
 *	N个CHAOSVM_EMULATION_BYTECODE_PROCEDURE + VmpProcedure
 */
PCHAOSVM_EMULATION_BYTECODE_FILE __API__ ChaosVmByteCodeFileGenByteCodeFile() {
	PCHAOSVM_EMULATION_BYTECODE_FILE pFile = NULL;
	pFile = (PCHAOSVM_EMULATION_BYTECODE_FILE)__logic_new__(CHAOSVM_EMULATION_BYTECODE_FILE, 1);
	pFile->dwSign = __CHAOSVM_BYTECODE_SIGN__;
	pFile->dwSize = sizeof(CHAOSVM_EMULATION_BYTECODE_FILE);
	return pFile;
}

/*
 * 参数:
 *	pFilePoint:指向字节码文件结构的指针的指针
 *
 * 介绍:
 *	释放指定的字节码文件的内存
 */
__void __API__ ChaosVmByteCodeFileReleaseByteCodeFile(PCHAOSVM_EMULATION_BYTECODE_FILE *pFilePoint) {
	__logic_delete__(*pFilePoint);
	*pFilePoint = NULL;
}

/*
 * 参数:
 *	pFilePoint:指向字节码文件结构的指针的指针
 *	pProcedure:要添加的函数
 *	iProcSize:函数的长度
 *
 * 介绍:
 *	增加一个被保护的函数到字节码文件
 */
PCHAOSVM_EMULATION_BYTECODE_PROCEDURE __API__ ChaosVmByteCodeFileAddByteCodeProcedureToFile(PCHAOSVM_EMULATION_BYTECODE_FILE *pFilePoint, __memory pProcedure, __integer iProcSize) {
	PCHAOSVM_EMULATION_BYTECODE_PROCEDURE pProc = NULL;
	__memory pNew = NULL, pOut = NULL;
	__integer iNewSize = 0;

	iNewSize = (*pFilePoint)->dwSize + sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE) + iProcSize;
	pNew = (__memory)__logic_new_size__(iNewSize);
	if (!pNew) return NULL;

	__logic_memcpy__(pNew, *pFilePoint, (*pFilePoint)->dwSize);
	pProc = (PCHAOSVM_EMULATION_BYTECODE_PROCEDURE)(pNew + (*pFilePoint)->dwSize);
	pProc->dwAttribute = 0;
	pProc->dwSize = sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE) + iProcSize;
	pOut = (__memory)pProc + sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE);
	__logic_memcpy__(pOut, pProcedure, iProcSize);//复制函数体
	__logic_delete__(*pFilePoint);//释放原型的内存
	*pFilePoint = (PCHAOSVM_EMULATION_BYTECODE_FILE)pNew;
	(*pFilePoint)->dwProcedureCount++;
	(*pFilePoint)->dwSize = iNewSize;
	pOut = (__memory)*pFilePoint + sizeof(CHAOSVM_EMULATION_BYTECODE_FILE);
	(*pFilePoint)->dwCrc32 = crc32(pOut, (*pFilePoint)->dwSize - sizeof(CHAOSVM_EMULATION_BYTECODE_FILE));
	return pProc;
}

/*
 * 参数:
 *	pFile:字节码文件指针
 *	pdwCrc32:输出当前字节码文件实时计算出的CRC32值
 *
 * 介绍:
 *	交易当前的字节码文件的CRC32值
 */
__bool __API__ ChaosVmByteCodeFileVerifySign(PCHAOSVM_EMULATION_BYTECODE_FILE pFile, __dword *pdwCrc32) {
	__memory pPoint = NULL;
	__integer iSize = 0;
	__dword dwCrc32 = 0;

	pPoint = (__memory)pFile + sizeof(CHAOSVM_EMULATION_BYTECODE_FILE);
	iSize = pFile->dwSize - sizeof(CHAOSVM_EMULATION_BYTECODE_FILE);

	dwCrc32 = crc32(pPoint, iSize);
	*pdwCrc32 = dwCrc32;

	if (dwCrc32 == pFile->dwCrc32)
		return TRUE;
	
	return FALSE;
}

/*
 * 参数:
 *	szFilePath:要输出成文件的的文件名
 *	pFile:字节码文件指针
 *
 * 介绍:
 *	将字节码文件输出到具体的文件中
 */
__bool __API__ ChaosVmByteCodeFileOutputByteCodeFileToFile(__tchar *szFilePath, PCHAOSVM_EMULATION_BYTECODE_FILE pFile) {
	__memory pMem = 0;
	pMem = (__memory)MappingFile(szFilePath, NULL, TRUE, 0, pFile->dwSize);
	if (!pMem) {
		return FALSE;
	}

	__logic_memcpy__(pMem, pFile, pFile->dwSize);

	UnMappingFile(pMem);
	return TRUE;
}

/*
 * 参数:
 *	pByteCodeFile:字节码文件指针
 *
 * 介绍:
 *	获取此文件下有多少个函数
 */
__integer __API__ ChaosVmByteCodeFileGetProcedureCount(PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile) {
	return pByteCodeFile->dwProcedureCount;
}

/*
 * 参数:
 *	iIndex:要取得函数的索引
 *	pByteCodeFile:字节码文件指针
 *
 * 介绍:
 *	获取索引指向的函数,成功返回这个函数体的内容,失败返回NULL
 */
__memory __API__ ChaosVmByteCodeFileGetProcedureByteCode(__integer iIndex, PCHAOSVM_EMULATION_BYTECODE_FILE pByteCodeFile) {
	__memory pPoint = NULL, pVmpProcedureByteCode = NULL;
	__integer iCount = 0, i = 0;
	PCHAOSVM_EMULATION_BYTECODE_PROCEDURE pProcedure = NULL;

	iCount = (__integer)(pByteCodeFile->dwProcedureCount);
	if (iIndex >= iCount) return NULL;

	pPoint = (__memory)pByteCodeFile;
	pPoint += sizeof(CHAOSVM_EMULATION_BYTECODE_FILE);
	pProcedure = (PCHAOSVM_EMULATION_BYTECODE_PROCEDURE)pPoint;//第一个字节码函数头

	for (i = 0; i < iIndex; i++)
		pProcedure = (PCHAOSVM_EMULATION_BYTECODE_PROCEDURE)((__memory)pProcedure + pProcedure->dwSize);

	pVmpProcedureByteCode = (__memory)pProcedure + sizeof(CHAOSVM_EMULATION_BYTECODE_PROCEDURE);
	return pVmpProcedureByteCode;
}