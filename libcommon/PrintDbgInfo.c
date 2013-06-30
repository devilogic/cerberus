#include "PrintDbgInfo.h"
#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>

__void __INTERNAL_FUNC__ PrintDbgInfo_DumpMemory(__char *pInfo, __memory pMemory, __integer iLength) {
	__integer i = 1;
	printf("%s%s\n", __PRINTDBGINFO_TITLE__, pInfo);
	printf("DumpMemory(%d bytes):\n", iLength);
	for (/*i = 0*/; i <= iLength; i++) {
		// 打印换行
		if (pMemory[i-1] < 0x10)
			printf("0x0%X", pMemory[i-1]);
		else
			printf("0x%2X", pMemory[i-1]);
		if (i % 16 == 0) printf("\n");
		else if (i < iLength) printf(" ");
	}/* end while */
	if (i % 16 != 0)
		printf("\n");
}

__void __INTERNAL_FUNC__ PrintDbgInfo_DumpMemoryToFile(__char *pInfo, __char *pFileName, __memory pMemory, __integer iLength) {
	FILE *fp = fopen(pFileName, "w");
	if (fp == NULL) return;
	printf("%s%s\n", __PRINTDBGINFO_TITLE__, pInfo);
	printf("DumpMemory to %s(%d bytes):\n", pFileName, iLength);
	fwrite(pMemory, sizeof(__byte), iLength, fp);
	fflush(fp);
	fclose(fp);
}

__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgString(__char *pString) {
	OutputDebugStringA(pString);
}

__void __INTERNAL_FUNC__ Byte2String(__byte bByte, __char *pOutBuffer) {
	__char szValue[2] = {0};
	__byte bLow = 0, bHigh = 0;
	if (bByte == 0) {
		__logic_strcpy__(pOutBuffer, "00");
	}
	bLow = (bByte & 0xF0) >> 0x04;
	bHigh = bByte & 0x0F;
	if (bLow < 0x0A) {
		szValue[0] = bLow + '0';
		szValue[1] = '\0';
		__logic_strcpy__(pOutBuffer, szValue);
	} else if (bLow >= 0x0A) {
		szValue[0] = bLow - 0x0A + 'A';
		szValue[1] = '\0';
		__logic_strcpy__(pOutBuffer, szValue);		
	}

	if (bHigh < 0x0A) {
		szValue[0] = bHigh + '0';
		szValue[1] = '\0';
		__logic_strcat__(pOutBuffer, szValue);
	} else if (bHigh >= 0x0A) {
		szValue[0] = bHigh - 0x0A + 'A';
		szValue[1] = '\0';
		__logic_strcat__(pOutBuffer, szValue);
	}
}
__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgInteger(__integer iInteger) {
	__char szOutputBuffer[1024] = {0};
	__char szValue[8] = {0};
	__byte bTmp1 = 0, bTmp2 = 0, bTmp3 = 0, bTmp4 = 0;
	__logic_strcpy__(szOutputBuffer, "0x");
	bTmp1 = (__byte)(iInteger >> 24);
	bTmp2 = (__byte)(iInteger >> 16);
	bTmp3 = (__byte)(iInteger >> 8);
	bTmp4 = (__byte)(iInteger);

	if (bTmp1 != 0) {
		Byte2String(bTmp1, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	}

	if (bTmp2 != 0) {
		Byte2String(bTmp2, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	}

	if (bTmp3 != 0) {
		Byte2String(bTmp3, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	}

	if (bTmp4 != 0) {
		Byte2String(bTmp4, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	}

	OutputDebugStringA(szOutputBuffer);
	OutputDebugStringA("\n");
}

__void __INTERNAL_FUNC__ PrintDbgInfo_OutputDbgDumpMemory(__char *pInfo, __memory pMemory, __integer iSize) {
	__integer i = 0;
	__char OutBuffer[0x04] = {0};
	OutputDebugStringA(pInfo);
	for (i = 0; i < iSize; i++) {
		if ((i != 0) && (i % 0x10 == 0))
			OutputDebugStringA("\n");
		Byte2String((__byte)pMemory[i], OutBuffer);
		OutputDebugStringA(OutBuffer);
		OutputDebugStringA(" ");
	}
	OutputDebugStringA("\n");
}

__dword __INTERNAL_FUNC__ PrintDbgInfo_RecordToFileInit(__char *pFilePath) {
	HANDLE hRecordHandle = 0;
	DeleteFileA(pFilePath);
	hRecordHandle = CreateFileA(pFilePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
	if (hRecordHandle == INVALID_HANDLE_VALUE) {
		hRecordHandle = 0;
	}
	return (__dword)hRecordHandle;
}

__void __INTERNAL_FUNC__ PrintDbgInfo_RecordStringToFile(__dword hHandle, __char *pInfo) {
	if (hHandle) {
		__dword dwNumberOfWritten = 0;
		WriteFile((HANDLE)hHandle, pInfo, __logic_strlen__(pInfo), &dwNumberOfWritten, NULL);
		FlushFileBuffers((HANDLE)hHandle);
	}
}

__void __INTERNAL_FUNC__ PrintDbgInfo_RecordIntegerToFile(__dword hHandle, __integer iInteger) {
	__char szOutputBuffer[1024] = {0};
	__char szValue[8] = {0};
	__byte bTmp1 = 0, bTmp2 = 0, bTmp3 = 0, bTmp4 = 0;
	__logic_strcpy__(szOutputBuffer, "0x");
	bTmp1 = (__byte)(iInteger >> 24);
	bTmp2 = (__byte)(iInteger >> 16);
	bTmp3 = (__byte)(iInteger >> 8);
	bTmp4 = (__byte)(iInteger);

	if (bTmp1 != 0) {
		Byte2String(bTmp1, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp2 != 0) {
		Byte2String(bTmp2, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp3 != 0) {
		Byte2String(bTmp3, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp4 != 0) {
		Byte2String(bTmp4, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}
	__logic_strcat__(szOutputBuffer, "\n");
	if (hHandle) {
		__dword dwNumberOfWritten = 0;
		WriteFile((HANDLE)hHandle, szOutputBuffer, __logic_strlen__(szOutputBuffer), &dwNumberOfWritten, NULL);
		FlushFileBuffers((HANDLE)hHandle);
	}
}

__void __INTERNAL_FUNC__ PrintDbgInfo_RecordDumpMemoryToFile(__dword hHandle, __char *pInfo, __memory pMemory, __integer iSize) {
	__integer i = 0;
	__char OutBuffer[0x04] = {0};
	PrintDbgInfo_RecordStringToFile(hHandle, pInfo);
	for (i = 0; i < iSize; i++) {
		if ((i != 0) && (i % 0x10 == 0))
			PrintDbgInfo_RecordStringToFile(hHandle, "\n");
		Byte2String((__byte)pMemory[i], OutBuffer);
		PrintDbgInfo_RecordStringToFile(hHandle, OutBuffer);
		PrintDbgInfo_RecordStringToFile(hHandle, " ");
	}
	PrintDbgInfo_RecordStringToFile(hHandle, "\n");
}

__void __INTERNAL_FUNC__ PrintDbgInfo_RecordToFileClose(__dword hHandle) {
	if (hHandle)
		CloseHandle((HANDLE)hHandle);
}

__void __INTERNAL_FUNC__ PrintDbgInfo_DebugBreak(__char *pName) {
	CloseHandle((HANDLE)(pName));
	__asm int 3;
}

HANDLE g_hWriteConsole = 0;
HANDLE g_hReadConsole = 0;
FPCustomDebuger g_pDebuger = NULL;
__bool __INTERNAL_FUNC__ PrintDbgInfo_DebugerInit(FPCustomDebuger pDebuger) {
	if(!AllocConsole()) {
		if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
			__dword dwLastRet = GetLastError();
			return FALSE;
		}
	}
	g_hWriteConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (g_hWriteConsole == INVALID_HANDLE_VALUE) {
		g_hWriteConsole = 0;
		return FALSE;
	}
	g_hReadConsole = GetStdHandle(STD_INPUT_HANDLE);
	if (g_hReadConsole == INVALID_HANDLE_VALUE) {
		g_hReadConsole = 0;
		return FALSE;
	}

	g_pDebuger = pDebuger;
	return TRUE;
}

__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWrite(__char *pInfo) {
	__integer iWritten = 0;
	if (g_hWriteConsole) {
		if (!WriteConsoleA(g_hWriteConsole, pInfo, __logic_strlen__(pInfo), &iWritten, NULL))
			return 0;
		return iWritten;
	}
	return 0;
}

#define __PRINTDBGINFO_WRITECONSOLE_BUFFER_SIZE__	1024
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteLine(__char *pInfo) {
	__char szText[__PRINTDBGINFO_WRITECONSOLE_BUFFER_SIZE__] = {0};
	__integer iWritten = 0;
	__logic_strcpy__(szText, pInfo);
	__logic_strcat__(szText, "\n");
	if (g_hWriteConsole) {
		if (!WriteConsoleA(g_hWriteConsole, szText, __logic_strlen__(szText), &iWritten, NULL))
			return 0;
		return iWritten;
	}
	return 0;
}

__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteInteger(__integer iInteger) {
	__char szOutputBuffer[1024] = {0};
	__char szValue[8] = {0};
	__byte bTmp1 = 0, bTmp2 = 0, bTmp3 = 0, bTmp4 = 0;
	__logic_strcpy__(szOutputBuffer, "0x");
	bTmp1 = (__byte)(iInteger >> 24);
	bTmp2 = (__byte)(iInteger >> 16);
	bTmp3 = (__byte)(iInteger >> 8);
	bTmp4 = (__byte)(iInteger);

	if (bTmp1 != 0) {
		Byte2String(bTmp1, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp2 != 0) {
		Byte2String(bTmp2, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp3 != 0) {
		Byte2String(bTmp3, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	if (bTmp4 != 0) {
		Byte2String(bTmp4, szValue);
		__logic_strcat__(szOutputBuffer, szValue);
	} else {
		__logic_strcat__(szOutputBuffer, "00");
	}

	return PrintDbgInfo_DebugerWrite(szOutputBuffer);
}

__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteFormatStringInteger(__char *pInfo, __integer iInteger) {
	__integer iRet = 0;
	iRet = PrintDbgInfo_DebugerWrite(pInfo);
	iRet += PrintDbgInfo_DebugerWriteInteger(iInteger);
	iRet += PrintDbgInfo_DebugerWrite("\r\n");
	return iRet;
}

__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerReadLine(__memory pOutBuffer, __integer iMaxSize) {
	__integer iRet = 0;
	// 接受数据
	if (!ReadConsoleA(g_hReadConsole, (__void *)pOutBuffer, iMaxSize, &iRet, NULL))
		return 0;
	return iRet;
}

__bool g_bSkipAllBreakPoint = FALSE;
#define __PRINTDBGINFO_READCONSOLE_BUFFER_SIZE__	1024
#define __PRINTDBGINFO_DEBUGER_TITLE__				"#>"
__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerBreakPoint(__char *pInfo, __void *pParam) {
	__integer iReads = 0;
	__char *pText = NULL;

	if ((!g_hWriteConsole) || (!g_hReadConsole)) return 0;//退出

	if (g_bSkipAllBreakPoint) return 0;

	PrintDbgInfo_DebugerWriteLine(pInfo);

	pText = (__char *)__logic_new_size__(__PRINTDBGINFO_READCONSOLE_BUFFER_SIZE__);

	while (1) {
		// 输出命令行
		PrintDbgInfo_DebugerWrite(__PRINTDBGINFO_DEBUGER_TITLE__);
		// 接收命令
		if (!ReadConsoleA(g_hReadConsole, (__void *)pText, __PRINTDBGINFO_READCONSOLE_BUFFER_SIZE__, &iReads, NULL))
			return 0;

		// 是否继续
		if ((__logic_memcmp__(pText, "\x0d\x0a", 2) == 0) || 
			(__logic_strncmp__(pText, "#continue", __logic_strlen__("#continue")) == 0)) {
				break;//跳出循环
		} else if (__logic_memcmp__(pText, "#break", 6) == 0) {
			__asm int 3;
			break;
		} else {
			if (g_pDebuger)
				g_bSkipAllBreakPoint = g_pDebuger(pText, pParam);
		}
	}
	
	__logic_delete__(pText);
	return iReads;

}

__void __INTERNAL_FUNC__ PrintDbgInfo_DebugerRelease() {
	FreeConsole();
}
