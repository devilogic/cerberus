#include "Dump.h"
#include "Support.h"

__INLINE__ __void __INTERNAL_FUNC__ DumpMemory(FILE *fp, __memory pMem, __integer iFileSize, __integer iDumpSize) {
	__integer iDataSize = 0;
	__memory pData = NULL;
	__offset ofOffset = 0;
	__byte bByte = 0;
	__integer iCount = 0, i = 0;

	if ((iDumpSize == 0) || (iDumpSize >= iFileSize))
		iDataSize = iFileSize;
	else
		iDataSize = iDumpSize;

	pData = pMem;

	fprintf(fp, "<DumpMemory DecSize=\"%d\" HexSize=\"0x%X\">\n", iDataSize, iDataSize);

	while (1) {
		// 判断末尾
		if ((iCount != 0) && (iCount % 0x10 == 0) || (iCount >= iDataSize)) {
			fprintf(fp, "</x%X>\n", ofOffset);

			// 是否是末尾
			if (iCount >= iDataSize)
				break;

			ofOffset += 0x10;
		}

		if ((iCount == 0) || ((iCount != 0) && (iCount % 0x10 == 0)))
			fprintf(fp, "<x%X>", ofOffset);

		// 获取字节
		bByte = *((__byte *)pData + iCount);
		if (bByte == 0)
			fprintf(fp, "00 ");
		else if (bByte < 0x0F)
			fprintf(fp, "0%X ", bByte);
		else
			fprintf(fp, "%2X ", bByte);

		iCount++;
	}

	fprintf(fp, "</DumpMemory>\n");
	return;
}

__INLINE__ __void __INTERNAL_FUNC__ DumpEntry(FILE *fp, __memory pMem, __integer iDumpSize) {
	__integer iDataSize = 0;
	__memory pData = NULL;
	__offset ofOffset = 0;
	__byte bByte = 0;
	__integer iCount = 0, i = 0;
	PIMAGE_SECTION_HEADER pSecHdr = NULL;

	pSecHdr = GetEntryPointSection(pMem);
	if ((iDumpSize == 0) || (iDumpSize >= pSecHdr->SizeOfRawData))
		iDataSize = pSecHdr->SizeOfRawData;
	else
		iDataSize = iDumpSize;

	pData = pMem;

	fprintf(fp, "<DumpEntryMemory DecSize=\"%d\" HexSize=\"0x%X\">\n", iDataSize, iDataSize);

	while (1) {
		// 判断末尾
		if ((iCount != 0) && (iCount % 0x10 == 0) || (iCount >= iDataSize)) {
			fprintf(fp, "</x%X>\n", ofOffset);

			// 是否是末尾
			if (iCount >= iDataSize)
				break;

			ofOffset += 0x10;
		}

		if ((iCount == 0) || ((iCount != 0) && (iCount % 0x10 == 0)))
			fprintf(fp, "<x%X>", ofOffset);

		// 获取字节
		bByte = *((__byte *)pData + iCount);
		if (bByte == 0)
			fprintf(fp, "00 ");
		else if (bByte < 0x0F)
			fprintf(fp, "0%X ", bByte);
		else
			fprintf(fp, "%2X ", bByte);

		iCount++;
	}

	fprintf(fp, "</DumpEntryMemory>\n");
	return;
}

__bool __INTERNAL_FUNC__ Dump(__memory pMem, __tchar *pResultFilePath, PDUMP_CONFIGURE pConfigure) {
	FILE *fp = NULL;
	__char buf[1024] = {0};

	UnicodeToAnsi(pResultFilePath, MAX_PATH, buf, 1024);
	fp = fopen(buf, "w");
	if (!fp) return FALSE;

	// 输出信息头
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(fp, "<Dump>\n");

	if (pConfigure->bDump) {
		DumpMemory(fp, pMem, pConfigure->iFileSize, pConfigure->iDumpSize);
	}

	if (pConfigure->bEntry) {
		DumpEntry(fp, pMem, pConfigure->iDumpSize);
	}

	fprintf(fp, "</Dump>\n");
	fclose(fp);
	return TRUE;
}
