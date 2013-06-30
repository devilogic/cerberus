#include "SignDefined.h"
#include "ChaosVmpSDK.h"

#define __MAX_SIGN_BLOCK_NUM__ 0x100

typedef struct _CHARACTERS_MATCH {
	__offset ofPetn1Start;
	__offset ofPetn1End;
	__offset ofPetn2Start;
	__offset ofPetn2End;
	__integer iProtectedSize;
	__offset ofProtectedStart;
	__offset ofProtectedEnd;
	__offset ofProtectedFlag;
	__integer iFlagSize;
	__address addrProtectedMemStart;
	__address addrProtectedMemEnd;
} CHARACTERS_MATCH, *PCHARACTERS_MATCH;

/*
 * 参数配置结构体
 */
typedef struct _FILE_BASIC {
	__tchar *pFileName;
	__integer iFileSize;
	__memory pMapBase;
} FILE_BASIC,*PFILE_BASIC;


PCHARACTERS_MATCH g_ChaosVmpSign[__MAX_SIGN_BLOCK_NUM__];
PCHARACTERS_MATCH g_PowerProtectSign[__MAX_SIGN_BLOCK_NUM__];
FILE_BASIC g_FileBasic;


__integer __INTERNAL_FUNC__ GetSignInfo(__memory pMem, \
										__char *pPt1, __char *pPt2, __char *pFlag, \
										__integer iPt1Size,__integer iPt2Size, __integer iFlagSize, PCHARACTERS_MATCH *ppCharactersMatch) {
	__integer iSearchRange;
	__integer iIndex1, iIndex2, iIndex3;
	__integer iSignNum;
	__integer iCodeSize;
	__integer iCodeSecOffset = 0;
	__memory pBase, pCode, pPoint;
	__dword dwImageBase;
	PIMAGE_SECTION_HEADER pCodeSec = NULL;

	iSignNum = 0;
	pBase = pMem;
	pCodeSec = GetEntryPointSection(pMem);
	iSearchRange = pCodeSec->SizeOfRawData;

	dwImageBase = GetNtHeader(pMem)->OptionalHeader.ImageBase;
	pPoint = pCode = pMem + pCodeSec->PointerToRawData;

	iCodeSecOffset = (__integer)(pCode - pMem);
	while (iSearchRange > 0) {
		iIndex1 = bm_matcher(pPoint, iSearchRange, (__byte *)pPt1, iPt1Size);
		if (iIndex1 != -1) {
			// 只有保护头存在了才有后续的
			iIndex2 = bm_matcher(pPoint, iSearchRange, (__byte *)pPt2, iPt2Size);
			iIndex3 = bm_matcher(pPoint, iSearchRange, (__byte *)pFlag, iFlagSize);
		} else {
			iIndex1 = iIndex2 = iIndex3 = -1;
		}

		if ((iIndex1 != -1) && (iIndex2 != -1) && (iIndex3 != -1)) {
			// 分配内存
			PCHARACTERS_MATCH cm = (PCHARACTERS_MATCH)__logic_new_size__(sizeof(CHARACTERS_MATCH));

			// 保护特征起始
			cm->ofPetn1Start = iIndex1 + iCodeSecOffset;
			cm->ofPetn1End = iIndex1 + iCodeSecOffset + iPt1Size;

			// 保护特征结束
			cm->ofPetn2Start = iIndex2 + iCodeSecOffset;
			cm->ofPetn2End = iIndex2 + iCodeSecOffset + iPt2Size;

			// 保护区域开始
			cm->ofProtectedStart = cm->ofPetn1End + 5;//5为Pet1末尾的call xxxxx 指令长度
			cm->ofProtectedEnd = cm->ofPetn2Start;
			cm->iFlagSize = iFlagSize + 5;
			cm->ofProtectedFlag = iIndex3 + iCodeSecOffset;

			// 设置地址
			cm->addrProtectedMemStart = (__address)(Raw2Rva(pBase, cm->ofProtectedStart) + dwImageBase);
			cm->addrProtectedMemEnd = (__address)(Raw2Rva(pBase, cm->ofProtectedEnd) + dwImageBase);

			// 修订地址
			cm->addrProtectedMemStart = __Alig__(cm->addrProtectedMemStart, 0x10);

			// 计算保护范围
			cm->iProtectedSize = (__integer)(cm->addrProtectedMemEnd - cm->addrProtectedMemStart);

			// 更新剩余空间
			iSearchRange -= (__integer)(pBase + cm->ofPetn2End - pPoint);

			// 更新起始内存地址
			pPoint += (__integer)(pBase + cm->ofPetn2End - pPoint);

			// 保存结构体
			ppCharactersMatch[iSignNum] = cm;
			++iSignNum;
		} else break;
	}

	return iSignNum;
}

__void __INTERNAL_FUNC__ EraseSign(__memory pMem, __integer iNum, PCHARACTERS_MATCH *ppCharactersMatch) {
	__integer i;

	for (i = 0; i < iNum; ++i) {
		memset((__void*)(pMem + ppCharactersMatch[i]->ofProtectedFlag), 0x90, (size_t)(ppCharactersMatch[i]->iFlagSize));
		memset((__void*)(pMem + ppCharactersMatch[i]->ofPetn1Start), 0x90, (size_t)(ppCharactersMatch[i]->ofPetn1End - ppCharactersMatch[i]->ofPetn1Start + 5));//call xxxx 这条指令式个字节
		memset((__void*)(pMem + ppCharactersMatch[i]->ofPetn2Start), 0x90, (size_t)(ppCharactersMatch[i]->ofPetn2End - ppCharactersMatch[i]->ofPetn2Start));
	}
}

__integer __INTERNAL_FUNC__ ExtractSign(__tchar *pTargetFilePath, PCHARACTERS_MATCH *ppCharactersMatch, PFILE_BASIC pFileBasic, __bool bVmp) {
	__memory pMem;
	__integer iFileSize;
	__integer iPt1Len, iPt2Len, iPt3Len;
	__integer iTotalSignBlockNum = 0;

	if (!pTargetFilePath)
		return -1;

	pMem = MappingFile(pTargetFilePath, &iFileSize, TRUE, 0, 0);
	if (!pMem) return -1;

	pFileBasic->pFileName = pTargetFilePath;
	pFileBasic->iFileSize = iFileSize;
	pFileBasic->pMapBase = pMem;

	if (IsValidPE32(pMem)) {
		__char *pPt1 = NULL, *pPt2 = NULL, *pFlag = NULL;

		if (bVmp) {
			pPt1 = (__char *)__VMP_PROTECT_START_PET__;
			pPt2 = (__char *)__VMP_PROTECT_END_PET__;
			pFlag = (__char *)__VMP_PROTECTED_FLAG__;
		} else {
			pPt1 = (__char *)__POWER_PROTECT_START_PET__;
			pPt2 = (__char *)__POWER_PROTECT_END_PET__;
			pFlag = (__char *)__POWER_PROTECTED_FLAG__;
		}

		//iPt1Len = __logic_strlen__(pPt1);
		//iPt2Len = __logic_strlen__(pPt2);
		//iPt3Len = __logic_strlen__(pFlag);

		iPt1Len = 16;
		iPt2Len = 17;
		iPt3Len = 9;

		iTotalSignBlockNum = GetSignInfo(pMem, \
										pPt1, pPt2, pFlag, \
										iPt1Len, iPt2Len, iPt3Len, \
										ppCharactersMatch);
		EraseSign(pMem, iTotalSignBlockNum, ppCharactersMatch);
	}

	// 取消映射
	if (pFileBasic->pMapBase != NULL) {
		UnmapViewOfFile(pFileBasic->pMapBase);
		pFileBasic->pMapBase = NULL;
	}

	return iTotalSignBlockNum;
}

__bool __INTERNAL_FUNC__ GenChaosVmSignInfo(__tchar *pSignInfoFilePath, __integer iTotalVmpSign, __integer iTotalPowerSign) {
	__char pFileName[MAX_PATH];
	__char pBuf[0x1000];
	__integer iPlus = 0;
	FILE *fp = NULL;

	// 首先删除一次
	DeleteFile((LPTSTR)pSignInfoFilePath);

	// 输出根节点
	iPlus = sprintf((char *)pBuf, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	iPlus += sprintf((char *)(pBuf + iPlus), "<ProtectTarget>\n");

	// 虚拟机保护
	if (iTotalVmpSign != 0) {
		iPlus += sprintf((char *)(pBuf + iPlus), "<x>\n");

		for (int i = 0; i < iTotalVmpSign; i++) {
			
			iPlus += sprintf((char *)(pBuf + iPlus), "<Procedure size=\"%d\">0x%08x</Procedure>\n", g_ChaosVmpSign[i]->iProtectedSize,  g_ChaosVmpSign[i]->addrProtectedMemStart);
		}

		iPlus += sprintf((char *)(pBuf + iPlus), "</x>\n");
	}

	// 力量保护
	if (iTotalPowerSign != 0) {
		iPlus += sprintf((char *)(pBuf + iPlus), "<y>\n");

		for (int i = 0; i < iTotalPowerSign; i++) {

			iPlus += sprintf((char *)(pBuf + iPlus), "<Procedure size=\"%d\">0x%08x</Procedure>\n", g_PowerProtectSign[i]->iProtectedSize,  g_PowerProtectSign[i]->addrProtectedMemStart);

		}

		iPlus += sprintf((char *)(pBuf + iPlus), "</y>\n");
	}

	iPlus += sprintf((char *)(pBuf + iPlus), "</ProtectTarget>\n");


	// 写入文件
	memset(pFileName, 0, MAX_PATH);
	UnicodeToAnsi(pSignInfoFilePath, __logic_tcslen__(pSignInfoFilePath), pFileName, MAX_PATH);
	fp = fopen((char *)pFileName, "w");
	if (!fp)
		return FALSE;

	fprintf(fp, "%s", (char *)pBuf);

	fclose(fp);

	return TRUE;
}

__bool __INTERNAL_FUNC__ ChaosVmSDK(__tchar *pTargetFilePath, __tchar *pSdkXmlFilePath) {
	__integer iTotalVmpSign = 0, iTotalPowerSign = 0;

	iTotalVmpSign = ExtractSign(pTargetFilePath, (PCHARACTERS_MATCH *)&g_ChaosVmpSign, &g_FileBasic, TRUE);
	if (iTotalVmpSign == -1) return FALSE;
	iTotalPowerSign = ExtractSign(pTargetFilePath, (PCHARACTERS_MATCH *)&g_PowerProtectSign, &g_FileBasic, FALSE);
	if (iTotalPowerSign == -1) return FALSE;

	if (GenChaosVmSignInfo(pSdkXmlFilePath, iTotalVmpSign, iTotalPowerSign) == FALSE)
		return FALSE;

	// 释放 每个记录标志结构所占一段内存
	for (int i = 0; i < iTotalVmpSign; ++i) {
		if(g_ChaosVmpSign[i] != NULL) {
			__logic_delete__(g_ChaosVmpSign[i]);
			g_ChaosVmpSign[i] = NULL;
		}
	}

	for (int j = 0; j < iTotalPowerSign; ++j) {
		if(g_PowerProtectSign[j] != NULL) {
			__logic_delete__(g_PowerProtectSign[j]);
			g_PowerProtectSign[j] = NULL;
		}
	}

	return TRUE;
}