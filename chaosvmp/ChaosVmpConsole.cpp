#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#include "resource.h"
#include "ChaosVmAth.h"
#include "Support.h"
#include "lcrypto.h"
#include "ChaosVmKey.h"
#include "ChaosVmLdrKey.h"
#include "PowerProtecterAth.h"

//////////////////////////////////////////////////////////////////////////
// 使用XML
#define TIXML_USE_STL
#include "CTinyXml.h"
//////////////////////////////////////////////////////////////////////////

#include "ChaosVmpSDK.h"

#if defined(_UNICODE)
#define _cin				wcin
#else
#define _cin				cin
#endif

UINT GetLine(TCHAR *Buffer, UINT iCount)
{
	UINT iLen = 0;
	ZeroMemory(Buffer, 0x100 * sizeof(TCHAR));
	_cin.getline(Buffer, iCount, _T('\n'));
	iLen = _tcslen(Buffer);
	return iLen;
}

#define __GetLine__(){iBufferLen = GetLine(szBuffer, 0x100);}

/*
 * 参数:
 *	szAddress:16进制的字符串地址
 *
 * 介绍:
 *	将16进制的字符串转换成数字,形式为0xaabbccdd,如果形式不对则返回0xFFFFFFFF
 */

__integer __INTERNAL_FUNC__ HexString2Byte(__char *szString) {
	__integer iRet = 0;
	__char ch = 0;

	ch = tolower(szString[0]);
	if ((ch >= 'a' ) && (ch <= 'f'))
		iRet = (ch - 'a' + 0x0A) * 0x10;
	else
		iRet = (ch - '0') * 0x10;

	ch = tolower(szString[1]);
	if ((ch >= 'a' ) && (ch <= 'f'))
		iRet += (ch - 'a' + 0x0A);
	else
		iRet += (ch - '0');

	return iRet;
}

__address __INTERNAL_FUNC__ String2Address(__char *szAddress) {
	__address addrAddress = 0;
	__char *p = NULL;
	__integer i = 0;
	__integer iLen = 0;
	__integer v0 = 0, v1 = 0, v2 = 0, v3 = 0;

	iLen = strlen((char *)szAddress);
	if (iLen != 10)
		return 0xFFFFFFFF;

	// 验证
	if ((szAddress[0] != '0') || (szAddress[1] != 'x'))
		return 0xFFFFFFFF;

	p = &(szAddress[2]);

	for (i = 0; i < (iLen - 2); p+=2, i+=2) {
		switch (i) {
		case 0: {
			v0 = HexString2Byte(p);
			v0 = v0 * 0x1000000;
		} break;
		case 2: {
			v1 = HexString2Byte(p);
			v1 = v1 * 0x10000;
		} break;
		case 4: {
			v2 = HexString2Byte(p);
			v2 = v2 * 0x100;
		} break;
		case 6: {
			v3 = HexString2Byte(p);
		} break;
		}/* end switch */
	}

	addrAddress = (__address)(v0 + v1 + v2 + v3);

	return addrAddress;
}

//// 全命令配置
//__void __INTERNAL_FUNC__ Usage() {
//	printf("version:3.1\r\n");
//	printf("http://www.xffffffff.org\r\n");
//	printf("usage:chaosvmp [options] [messagebox] <filepath> <target>\r\n");
//
//	printf("<target>\r\n");
//	printf("<[addr1:size1*key1:ksize1,addr2:size2*r,...] | [s]>\r\n");
//	printf("\r\n");
//
//	printf("[options]\r\n");
//	printf("/backup target file\r\n");															//备份原文件
//	printf("/mode(0:infect,1:emulation,...(other modes for future) <x>(mode)\r\n");				//使用混乱虚拟机的模式
//	printf("\r\n");
//
//	printf("[messagebox]\r\n");
//	printf("/chaosvm bytecode file not exist <message>(mbfne)\r\n");							//如果混乱虚拟机字节码不存在,显示什么消息
//	printf("/chaosvm emulation file not exist <message>(mefne)\r\n");							//如果混乱虚拟机的仿真器不存在,显示什么消息
//	printf("/mesage box title<title>(mbt)\r\n");												//消息框的名称
//	printf("/mesage box style<style>(mbs)\r\n");												//消息框的风格,同MSDN
//	printf("\r\n");
//
//	printf("[mode]\r\n");
//	printf("/chaosvm bytecode <filename>(cbc)\r\n");											//混乱虚拟机字节码文件的名称
//	printf("*****\r\n");
//
//	printf("mode:infect\r\n");																	//如果是感染模式
//	printf("-----\r\n");
//	printf("mode:emulation\r\n");																//如果是仿真模式
//	printf("/chaosvm emulation <filename>(ce)\r\n");											//混乱虚拟机仿真器的名称
//	printf("\r\n");
//	printf("!!!:the procedure is protected, that mix size = 19 bytes\r\n");
//	printf("\r\n");
//}
__void __INTERNAL_FUNC__ Usage() {
	printf("version:3.141\r\n");
	printf("email:logic.yan@gmail.com\r\n");
	printf("chaosvmp [options]\r\n");
	printf("[options]\r\n");
	printf("\t/cmdf <command file> load command file\r\n");
	printf("\t/sdk <target file> <xml file> extract sign\r\n");
	printf("\t/help print usage\r\n");
	printf("\r\n");
}

typedef struct _CHAOSVMP_CONSOLE_CONFIGURE {
	__tchar szTargetFilePath[MAX_PATH];//目标文件
	__bool bBackupOrigFile;//备份原文件
	CHAOSVM_RUN_MODE Mode;//使用混乱虚拟机的模式,0:感染型,1:仿真型

	union {
		__bool bUseByteCodeFileInInfectMode;//使用字节码文件在感染模式下
		__bool bUseChaosVmEmulationInResource;//使用在资源中的仿真器模块
	};

	// 混乱虚拟机仿真器的名称
	__tchar szChaosVmNameInEmulation[0x20];

	// 混乱虚拟机字节码的文件名
	union {
		__tchar szChaosVmByteCodeFileName[0x20];
		__tchar szChaosVmByteCodeFileNameInInfect[0x20];
		__tchar szChaosVmByteCodeFileNameInEmulation[0x20];
	};

	//////////////////////////////////////////////////////////////////////////
	// 提示框选项
	__tchar szMessageBoxTitle[0x40];
	__tchar szMessageBoxOnByteCodeFileNotExist[0x100];
	__tchar szMessageBoxOnEmulationFileNotExist[0x100];
	__dword dwMessageStyle;//消息框风格

	//////////////////////////////////////////////////////////////////////////
	// 调试虚拟机选项
	// 2012.2.9 新增
	CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE DebugConfigure;
} CHAOSVMP_CONSOLE_CONFIGURE, *PCHAOSVMP_CONSOLE_CONFIGURE;

/*
 * 参数:
 *	pFilePath:命令文件
 *	pConfigure:混乱虚拟机附加器配置结构
 *	szTargetFilePath:目标文件路径
 *	pXImportTableConfigure:控制台配置结构
 *
 * 介绍:
 *	读取命令文件
 */
__bool __INTERNAL_FUNC__ ReadCommandFile(__tchar *pFilePath, PCHAOSVMATH_CONFIGURE pConfigure, PDISATH_CONFIGURE pDisAthConfigure, PCHAOSVMP_CONSOLE_CONFIGURE pChaosVmpConsoleConfigure) {
	CTinyXml TinyXml;
	XMLNode *RootNode = NULL, *Node = NULL;
	XMLNodes Nodes;
	
	__char szFilePath[MAX_PATH] = {0};
	UnicodeToAnsi(pFilePath, __logic_tcslen__(pFilePath), szFilePath, MAX_PATH);

	if (!TinyXml.Load((const char *)szFilePath)) return FALSE;

	// 获取根节点
	RootNode = TinyXml.GetRootChild("ChaosVmp");

	// 是否调试混乱虚拟机
	Node = RootNode->GetChild("DebugChaosVm");
	if (Node) {
		XMLNode *DebugNode = NULL;
		__integer iValue = 0;

		// 是否启用调试
		if (Node->GetAttrUINT("enable", iValue)) {
			if (iValue == 1) {
				pChaosVmpConsoleConfigure->DebugConfigure.bDebugChaosVm = TRUE;

				// 是否以断点形式启动
				DebugNode = Node->GetChild("BreakPoint");
				if (DebugNode) {
					if (DebugNode->Value().A2I() == 1)
						pChaosVmpConsoleConfigure->DebugConfigure.bBreakPoint = TRUE;
					else
						pChaosVmpConsoleConfigure->DebugConfigure.bBreakPoint = FALSE;
				} else {
					pChaosVmpConsoleConfigure->DebugConfigure.bBreakPoint = FALSE;
				}		

			} else
				pChaosVmpConsoleConfigure->DebugConfigure.bDebugChaosVm = FALSE;
		} else {
			pChaosVmpConsoleConfigure->DebugConfigure.bDebugChaosVm = FALSE;
		}
	} else {
		pChaosVmpConsoleConfigure->DebugConfigure.bDebugChaosVm = FALSE;
	}

	// 目标文件路径
	Node = RootNode->GetChild("TargetFileName");
	AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szTargetFilePath, MAX_PATH);
	
	// 是否备份文件
	Node = RootNode->GetChild("BackupOrigFile");
	pChaosVmpConsoleConfigure->bBackupOrigFile = (Node->Value().A2I() == 1) ? TRUE : FALSE;

	// 混乱虚拟机运行模式,0:感染型,1:仿真型
	Node = RootNode->GetChild("ChaosVmRunMode");
	pChaosVmpConsoleConfigure->Mode = (Node->Value().A2I() == 0) ? CRM_INFECT : CRM_EMULATION;

	// 字节码文件路径
	Node = RootNode->GetChild("ByteCodeFileName");
	AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szChaosVmByteCodeFileName, MAX_PATH);

	// 两种模式下的不同配置
	if (pChaosVmpConsoleConfigure->Mode == CRM_INFECT) {
		// 是否使用字节码文件
		Node = RootNode->GetChild("UseByteFile");
		pChaosVmpConsoleConfigure->bUseByteCodeFileInInfectMode = (Node->Value().A2I() == 1) ? TRUE : FALSE;
		
		
	} else if (pChaosVmpConsoleConfigure->Mode == CRM_EMULATION) {
		// 是否使用默认的仿真器	
		Node = RootNode->GetChild("ChaosVmNameInEmulation");
		if (Node) {
			AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szChaosVmNameInEmulation, MAX_PATH);
			if (__logic_tcslen__(pChaosVmpConsoleConfigure->szChaosVmNameInEmulation) == 0)
				pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = TRUE;
		} else {
			pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = FALSE;
		}

	}

	//////////////////////////////////////////////////////////////////////////
	// 配置对话框
	Node = RootNode->GetChild("MessageBoxTitle");
	AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szMessageBoxTitle, 0x40);

	Node = RootNode->GetChild("MessageBoxOnByteCodeFileNotExist");
	AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szMessageBoxOnByteCodeFileNotExist, 0x100);

	Node = RootNode->GetChild("MessageBoxOnEmulationFileNotExist");
	AnsiToUnicode((__char *)Node->Value().GetString(), Node->Value().GetLens(), pChaosVmpConsoleConfigure->szMessageBoxOnEmulationFileNotExist, 0x100);

	Node = RootNode->GetChild("MessageStyle");
	pChaosVmpConsoleConfigure->dwMessageStyle = Node->Value().A2I();
	//////////////////////////////////////////////////////////////////////////

	// 虚拟机保护
	Node = RootNode->GetChild("x");
	Nodes = Node->GetChilds("Procedure");
	for (int i = 0; i < Nodes.size(); i++)
	{
		XMLNode *ProcedureNode = NULL, *AddressNode = NULL, *KeyNode = NULL;
		__address addrAddress = 0, addrKeyAddress = 0;
		__integer iProcedureSize = 0, iKeySize = 0;

		ProcedureNode = Nodes[i];

		// 获取函数长度
		if (!ProcedureNode->GetAttrUINT("size", iProcedureSize)) {
			// 获取长度属性失败
		}

		// 获取地址
		AddressNode = ProcedureNode->GetChild("Address");
		addrAddress = String2Address((__char *)AddressNode->Value().GetString());

		// 获取Key函数
		KeyNode = ProcedureNode->GetChild("KeyProcedure");
		if (KeyNode) {
			addrKeyAddress = String2Address((__char *)KeyNode->Value().GetString());

			// 获取Key函数长度
			if (!KeyNode->GetAttrUINT("size", iKeySize)) {
				// 获取长度属性失败
			}
		}/* end if */

		// 加入混乱虚拟机保护队列
		ChaosVmAthSelectProcedure(pConfigure, addrAddress, iProcedureSize, addrKeyAddress, iKeySize);
	}

	/*
	 * 力量保护只在感染模式下起作用
	 */
	if (pChaosVmpConsoleConfigure->Mode != CRM_INFECT) goto _dis_setting;

	// 力量保护
	PPOWER_PROTECTER_ATTACH_CONFIGURE pPowerProtecterAthConfigure = NULL;
	PPOWER_PROTECTER_PROCEDURE pRecord = NULL;
	PPOWER_PROTECTER_INSTRUCTION pInstructions = NULL;
	__integer iInstCount = 0;

	pPowerProtecterAthConfigure = &(pConfigure->PowerProtecterAttachConfigure);
	pRecord = &(pPowerProtecterAthConfigure->PowerProtecterProcedure);

	Node = RootNode->GetChild("y");
	// 如果没有力量保护
	if (!Node) goto _dis_setting;
	Nodes = Node->GetChilds("Procedure");
	for (int i = 0; i < Nodes.size(); i++)
	{
		XMLNodes InstNodes;
		XMLNode *ProcedureNode = NULL, *AddressNode = NULL, *KeyNode = NULL, *WatchNode = NULL;
		__address addrProcedure = 0, addrKeyAddress = 0, addrInstAddress = 0, addrWatchAddress = 0;
		__integer iProcedureSize = 0, iKeySize = 0, iWatchSize = 0;

		ProcedureNode = Nodes[i];

		// 获取函数长度
		if (!ProcedureNode->GetAttrUINT("size", iProcedureSize)) {
			// 获取长度属性失败
		}

		// 获取地址
		AddressNode = ProcedureNode->GetChild("Address");
		addrProcedure = String2Address((__char *)AddressNode->Value().GetString());

		// 获取Key函数
		KeyNode = ProcedureNode->GetChild("KeyProcedure");
		if (KeyNode)
			addrKeyAddress = String2Address((__char *)KeyNode->Value().GetString());

		// 获取Key函数长度
		if (!KeyNode->GetAttrUINT("size", iKeySize)) {
			// 获取长度属性失败
		}

		// 获取指令节点
		InstNodes = ProcedureNode->GetChilds("Instruction");
		if (InstNodes.size() != 0) {
			pInstructions = (PPOWER_PROTECTER_INSTRUCTION)__logic_new_size__(sizeof(POWER_PROTECTER_INSTRUCTION) * __POWER_PROTECT_MAX_INSTRUCTION__);
			for (int j = 0; j < InstNodes.size(); j++)
			{
				XMLNode *InstNode = NULL;
				InstNode = InstNodes[i];

				// 指令地址
				AddressNode = InstNode->GetChild("Address");
				addrInstAddress = String2Address((__char *)AddressNode->Value().GetString());
				pInstructions->Instruction.addrMemAddress = addrInstAddress;

				// 监视地址
				WatchNode = InstNode->GetChild("WatchAddress");
				if (WatchNode)
				{
					if (WatchNode->Value().GetLens() != 0) {
						addrWatchAddress = String2Address((__char *)WatchNode->Value().GetString());
						pInstructions->WatchRecord.addrMemAddress = addrWatchAddress;

						if (!WatchNode->GetAttrUINT("size", iWatchSize)) {
							// 获取长度属性失败
						}
						pInstructions->WatchRecord.iSize = iWatchSize;
						pInstructions->bWatched = TRUE;
					} else {
						pInstructions->bWatched = FALSE;
					}
				}/* end if */

				// 指令增加
				pInstructions++;
				iInstCount++;
			}/* end for */
		}/* end if */

		// 加入混乱虚拟机保护队列
		PowerProtectAthSelectProcedure(pRecord, addrProcedure, iProcedureSize, addrKeyAddress, iKeySize, pInstructions, iInstCount);

		// 释放指令结构
		if (pInstructions) __logic_delete__(pInstructions);
	}

_dis_setting:
	// 设定配置DIS结构
	pDisAthConfigure->bIfXFileExistFailed = TRUE;
	if (pChaosVmpConsoleConfigure->Mode == CRM_INFECT) {
		pDisAthConfigure->wResourceID = IDR_CHAOSVM;
		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_XFILE_DNA__;
		pDisAthConfigure->dwDISResourceKey = __CHAOSVM_DECRYPT_KEY__;
	} else if (pChaosVmpConsoleConfigure->Mode == CRM_EMULATION) {
		pDisAthConfigure->wResourceID = IDR_CHAOSVM_EMULATION;
		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_LOADER_XFILE_DNA__;
		pDisAthConfigure->dwDISResourceKey = __CHAOSVMLDR_DECRYPT_KEY__;
	}

	pDisAthConfigure->szResourceType = (__tchar *)_T("BIN");
	pDisAthConfigure->XFileAttachInfo.szTargetFilePath = pChaosVmpConsoleConfigure->szTargetFilePath;
	pDisAthConfigure->XFileAttachInfo.bKeepTailData = TRUE;
	pDisAthConfigure->XFileAttachInfo.szSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
	pDisAthConfigure->XFileAttachInfo.szXSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
	pDisAthConfigure->bProtectMyIAT = TRUE;
	pDisAthConfigure->bProtectTargetIAT = TRUE;
	pDisAthConfigure->XFileAttachInfo.bCloseNX = TRUE;
	pDisAthConfigure->XFileAttachInfo.bCloseRandAddressMap = TRUE;
	pDisAthConfigure->XFileAttachInfo.bRandomAllSectionName = TRUE;
	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
	pDisAthConfigure->XFileAttachInfo.bSetAllSectionCanWrite = TRUE;
	__logic_memset__(pDisAthConfigure->XFileAttachInfo.bWillDelDataDirectoryIndexs, FALSE, 0x10);
	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
	pDisAthConfigure->XFileAttachInfo.bKeepSameOrigImpLib = TRUE;

	pDisAthConfigure->iDISProtectDllCrc32Count = 0;
	pDisAthConfigure->iDISProtectDllCallDllMainCrc32Count = 0;
	pDisAthConfigure->iDISProtectApiCrc32Count = 0;
	pDisAthConfigure->iTargetProtectDllCrc32Count = 0;
	pDisAthConfigure->iTargetProtectDllCallDllMainCrc32Count = 0;
	pDisAthConfigure->iTargetProtectApiCrc32Count = 0;

	return TRUE;
}

__bool __INTERNAL_FUNC__ HandleConsoleArguments(__integer iArgc, __tchar *pArgv[], PCHAOSVMATH_CONFIGURE pConfigure, PDISATH_CONFIGURE pDisAthConfigure, PCHAOSVMP_CONSOLE_CONFIGURE pChaosVmpConsoleConfigure) {
	TCHAR szBuffer[0x100] = {0};
	UINT iBufferLen = 0;
	PPOWER_PROTECTER_ATTACH_CONFIGURE pPowerProtecterAthConfigure = NULL;

	// 是否需要备份原文件
	do {
		cout << "Target file:";__GetLine__();
	} while (_tcslen(szBuffer) == 0);
	_tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szTargetFilePath), szBuffer);

	// 是否需要备份原文件
	cout << "Backup orig target file(yes or no):";__GetLine__();
	if (_tcsicmp(szBuffer, _T("yes")) == 0) {
		pChaosVmpConsoleConfigure->bBackupOrigFile = TRUE;
	} else if (_tcsicmp(szBuffer, _T("no")) == 0) {
		pChaosVmpConsoleConfigure->bBackupOrigFile = FALSE;
	} else {
		pChaosVmpConsoleConfigure->bBackupOrigFile = FALSE;
	}

	// 配置对话框
	cout << "Message caption:";__GetLine__();
	if (_tcslen(szBuffer) == 0) _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxTitle), _T("chaosvmp"));
	else _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxTitle), szBuffer);

	cout << "Message on bytecode file not exist:";__GetLine__();
	if (_tcslen(szBuffer) == 0) _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxOnByteCodeFileNotExist), _T("bytecode file is not exist"));
	else _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxOnByteCodeFileNotExist), szBuffer);

	cout << "Message on chaosvm emulation file not exist:";__GetLine__();
	if (_tcslen(szBuffer) == 0) _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxOnEmulationFileNotExist), _T("emulation file is not exist"));
	else _tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szMessageBoxOnEmulationFileNotExist), szBuffer);

	cout << "Message style:";__GetLine__();
	if (_tcslen(szBuffer) == 0) pChaosVmpConsoleConfigure->dwMessageStyle = 0;
	else pChaosVmpConsoleConfigure->dwMessageStyle = _ttoi(szBuffer);

	// 选择模式
	cout << "Select mode(infect,emulation):";__GetLine__();
	if (_tcsicmp(szBuffer, _T("infect")) == 0) {
		pChaosVmpConsoleConfigure->Mode = CRM_INFECT;
	} else if (_tcsicmp(szBuffer, _T("emulation")) == 0) {
		pChaosVmpConsoleConfigure->Mode = CRM_EMULATION;
	} else {
		pChaosVmpConsoleConfigure->Mode = CRM_INFECT;
	}

	// 按照模式再继续
	if (pChaosVmpConsoleConfigure->Mode == CRM_INFECT) {

		// 是否使用字节码
		cout << "Using chaosvm byte code file:";__GetLine__();
		if (_tcslen(szBuffer) != 0) {
			pChaosVmpConsoleConfigure->bUseByteCodeFileInInfectMode = TRUE;
			_tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szChaosVmByteCodeFileNameInInfect), szBuffer);
		} else {
			pChaosVmpConsoleConfigure->bUseByteCodeFileInInfectMode = FALSE;
		}

	} else if (pChaosVmpConsoleConfigure->Mode == CRM_EMULATION) {

		// 使用字节码
		do {
			cout << "Using chaosvm byte code file:";__GetLine__();
		} while (_tcslen(szBuffer) == 0);
		_tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szChaosVmByteCodeFileNameInEmulation), szBuffer);

		// 是否使用指定的仿真机
		cout << "Using chaosvm emulation file:";__GetLine__();
		if (_tcslen(szBuffer) != 0) {
			_tcscpy((TCHAR *)(pChaosVmpConsoleConfigure->szChaosVmNameInEmulation), szBuffer);
			pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = FALSE;
		} else {
			memset(pChaosVmpConsoleConfigure->szChaosVmNameInEmulation, 0, sizeof(TCHAR) * 0x20);
			pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = TRUE;
		}
	
	} else {
		cout << "Other mode not support now" << endl;
		return FALSE;
	}

	// 选择目标地址
	cout << "Chaosvmp it---" << endl;
	{
		__integer iCount = 0;
		__address addrProcedure = 0, addrKeyProcedure = 0;
		__integer iProcedureSize = 0, iKeyProcedureSize = 0;
		__char szAddress[0x40] = {0};

		// 选定混乱虚拟机保护的函数
		while (TRUE) {

			// 被保护函数
			cout << "[" << iCount << "]" << "Procedure address:";__GetLine__();
			if (_tcslen(szBuffer) == 0) break;//什么都不输入则退出
			UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
			addrProcedure = String2Address(szAddress);
			
			// 函数长度
			cout << "Procedure size:";__GetLine__();
			iProcedureSize = _ttoi(szBuffer);

			// 密钥函数
			cout << "Key procedure address:";__GetLine__();
			if (_tcsclen(szBuffer) != 0) {
				UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
				addrKeyProcedure = String2Address(szAddress);
				
				// 密钥函数的长度
				cout << "Key procedure size:";__GetLine__();
				iKeyProcedureSize = _ttoi(szBuffer);
			} else {
				addrKeyProcedure = 0;
				iKeyProcedureSize = 0;
			}
			iCount++;

			// 加入混乱虚拟机保护队列
			ChaosVmAthSelectProcedure(pConfigure, addrProcedure, iProcedureSize, addrKeyProcedure, iKeyProcedureSize);

		}/* end while */
	}

	/*
	 * 力量保护只在感染模式下起作用
	 */
	if (pChaosVmpConsoleConfigure->Mode != CRM_INFECT) goto _dis_setting;
	cout << "Power protect it---" << endl;
	{
		__integer iCount = 0;
		__address addrProcedure = 0, addrKeyProcedure = 0;
		__integer iProcedureSize = 0, iKeyProcedureSize = 0;
		__char szAddress[0x40] = {0};

		PPOWER_PROTECTER_PROCEDURE pRecord = NULL;
		PPOWER_PROTECTER_INSTRUCTION pInstructions = NULL;

		__integer iInstCount = 0;

		pPowerProtecterAthConfigure = &(pConfigure->PowerProtecterAttachConfigure);
		pRecord = &(pPowerProtecterAthConfigure->PowerProtecterProcedure);

		// 选定函数
		while (TRUE) {

			// 被保护函数
			cout << "[" << iCount << "]" << "Procedure address:";__GetLine__();
			if (_tcslen(szBuffer) == 0) break;//什么都不输入则退出
			UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
			addrProcedure = String2Address(szAddress);

			// 函数长度
			cout << "Procedure size:";__GetLine__();
			iProcedureSize = _ttoi(szBuffer);

			// 密钥函数
			cout << "Key procedure address:";__GetLine__();
			if (_tcsclen(szBuffer) != 0) {
				UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
				addrKeyProcedure = String2Address(szAddress);

				// 密钥函数的长度
				cout << "Key procedure size:";__GetLine__();
				iKeyProcedureSize = _ttoi(szBuffer);
			} else {
				addrKeyProcedure = 0;
				iKeyProcedureSize = 0;
			}

			// 选定函数内的指令
			pInstructions = (PPOWER_PROTECTER_INSTRUCTION)__logic_new_size__(sizeof(POWER_PROTECTER_INSTRUCTION) * __POWER_PROTECT_MAX_INSTRUCTION__);
			while (TRUE) {
				cout << "[" << iInstCount << "]" << "Instruction address:";__GetLine__();
				if (_tcslen(szBuffer) == 0) break;//什么都不输入则退出
				UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
				pInstructions->Instruction.addrMemAddress = String2Address(szAddress);

				cout << "Watch address:";__GetLine__();
				if (_tcslen(szBuffer) != 0) {
					UnicodeToAnsi((__tchar *)szBuffer, _tcslen(szBuffer), szAddress, 0x40);
					pInstructions->WatchRecord.addrMemAddress = String2Address(szAddress);

					cout << "Watch size:";__GetLine__();
					pInstructions->WatchRecord.iSize = _ttoi(szBuffer);

					pInstructions->bWatched = TRUE;
				} else {
					pInstructions->bWatched = FALSE;
				}

				pInstructions++;
				iInstCount++;
			}/* end while */

			// 加入混乱虚拟机保护队列
			PowerProtectAthSelectProcedure(pRecord, addrProcedure, iProcedureSize, addrKeyProcedure, iKeyProcedureSize, pInstructions, iInstCount);
			
			// 释放指令结构
			if (pInstructions) __logic_delete__(pInstructions);

			iCount++;
		}/* end while */
	}

_dis_setting:
	// 设定配置DIS结构
	pDisAthConfigure->bIfXFileExistFailed = TRUE;
	if (pChaosVmpConsoleConfigure->Mode == CRM_INFECT) {
		pDisAthConfigure->wResourceID = IDR_CHAOSVM;
		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_XFILE_DNA__;
		pDisAthConfigure->dwDISResourceKey = __CHAOSVM_DECRYPT_KEY__;
	} else if (pChaosVmpConsoleConfigure->Mode == CRM_EMULATION) {
		pDisAthConfigure->wResourceID = IDR_CHAOSVM_EMULATION;
		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_LOADER_XFILE_DNA__;
		pDisAthConfigure->dwDISResourceKey = __CHAOSVMLDR_DECRYPT_KEY__;
	}
	
	pDisAthConfigure->szResourceType = (__tchar *)_T("BIN");
	pDisAthConfigure->XFileAttachInfo.szTargetFilePath = pChaosVmpConsoleConfigure->szTargetFilePath;
	pDisAthConfigure->XFileAttachInfo.bKeepTailData = TRUE;
	pDisAthConfigure->XFileAttachInfo.szSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
	pDisAthConfigure->XFileAttachInfo.szXSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
	pDisAthConfigure->bProtectMyIAT = TRUE;
	pDisAthConfigure->bProtectTargetIAT = TRUE;
	pDisAthConfigure->XFileAttachInfo.bCloseNX = TRUE;
	pDisAthConfigure->XFileAttachInfo.bCloseRandAddressMap = TRUE;
	pDisAthConfigure->XFileAttachInfo.bRandomAllSectionName = TRUE;
	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
	pDisAthConfigure->XFileAttachInfo.bSetAllSectionCanWrite = TRUE;
	__logic_memset__(pDisAthConfigure->XFileAttachInfo.bWillDelDataDirectoryIndexs, FALSE, 0x10);
	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
	pDisAthConfigure->XFileAttachInfo.bKeepSameOrigImpLib = TRUE;
	
	pDisAthConfigure->iDISProtectDllCrc32Count = 0;
	pDisAthConfigure->iDISProtectDllCallDllMainCrc32Count = 0;
	pDisAthConfigure->iDISProtectApiCrc32Count = 0;
	pDisAthConfigure->iTargetProtectDllCrc32Count = 0;
	pDisAthConfigure->iTargetProtectDllCallDllMainCrc32Count = 0;
	pDisAthConfigure->iTargetProtectApiCrc32Count = 0;

	return TRUE;
}

/*
 * 参数:
 *	iArgc:命令行个数
 *	pArgv:命令行参数
 *	pConfigure:混乱虚拟机附加器配置结构
 *	szTargetFilePath:目标文件路径
 *	pXImportTableConfigure:控制台配置结构
 *
 * 介绍:
 *	处理命令行
 */
typedef enum _HANDLE_ARGS_DO {
	HAD_FAILED,				// 处理命令行失败
	HAD_SUCCESS,			// 处理命令行成功
	HAD_EXIT				// 直接退出
} HANDLE_ARGS_DO;
HANDLE_ARGS_DO __INTERNAL_FUNC__ HandleArguments(__integer iArgc, __tchar *pArgv[], PCHAOSVMATH_CONFIGURE pConfigure, PDISATH_CONFIGURE pDisAthConfigure, PCHAOSVMP_CONSOLE_CONFIGURE pChaosVmpConsoleConfigure) {
	if (iArgc >= 2) {

		// 分析命令行
		__integer i = 1;
		__tchar *pCurrArgv = NULL;

		for (i = 1; i < iArgc; i++) {
			if (pArgv[i][0] == _T('/')) {
				switch (pArgv[i][1]) {
				case _T('c'):
					if (__logic_tcscmp__(pArgv[i], (__tchar *)_T("/cmdf")) == 0) {

						i++;
						pCurrArgv = pArgv[i];

						// 读取命令行
						if (!ReadCommandFile(pCurrArgv, pConfigure, pDisAthConfigure, pChaosVmpConsoleConfigure))
							return HAD_FAILED;
					}
				break;
				case _T('s'):
					if (__logic_tcscmp__(pArgv[i], (__tchar *)_T("/sdk")) == 0) {
						__tchar *pTargetFile = NULL, *pSdkXml = NULL;

						i++;
						pTargetFile = pArgv[i];

						i++;
						pSdkXml = pArgv[i];

						// 读取命令行
						if (!ChaosVmSDK(pTargetFile, pSdkXml)) {
							return HAD_FAILED;
						} else {
							return HAD_EXIT;
						}
					}/* end if */
				break;
				case _T('h'):
					if (__logic_tcscmp__(pArgv[i], (__tchar *)_T("/help")) == 0) {
						Usage();
						return HAD_EXIT;
					}
				break;
				}/* end switch */
			}/* end if */
		}/* end for */
	} else {
		if (!HandleConsoleArguments(iArgc, pArgv, pConfigure, pDisAthConfigure, pChaosVmpConsoleConfigure))
			return HAD_FAILED;
	}

	return HAD_SUCCESS;
}

//__integer __INTERNAL_FUNC__ HandleArguments(__integer iArgc, __tchar *pArgv[], PCHAOSVMATH_CONFIGURE pConfigure, PDISATH_CONFIGURE pDisAthConfigure, PCHAOSVMP_CONSOLE_CONFIGURE pChaosVmpConsoleConfigure) {
//	__integer i = 1, iTarget = 0;
//	__bool bBackupOrigFile = FALSE;//备份原文件
//	CHAOSVM_RUN_MODE Mode;
//
//	__tchar szChaosVmEmulationName[0x20] = {0};
//	__tchar szChaosVmByteCodeFile[0x20] = {0};
//
//	__tchar szMessageBoxTitle[0x40] = {0};
//	__tchar szMessageBoxOnByteCodeFileNotExist[0x100] = {0};
//	__tchar szMessageBoxOnEmulationFileNotExist[0x100] = {0};
//	__dword dwMessageStyle = 0;//消息框风格
//
//	// 命令行最小数
//	if (iArgc == 1) {
//		Usage();
//		return 0;
//	}
//
//	// 处理命令行
//	for (i = 1; i < (iArgc - 2); i++) {
//		if (pArgv[i][0] == _T('/')) {
//			switch (pArgv[i][1]) {
//			case _T('b'):case _T('B'):
//				bBackupOrigFile = TRUE;
//			break;
//			case _T('c'):case _T('C'):
//				if (_tcscmp(pArgv[i], _T("/cbc")) == 0) {
//					i++;
//					_tcscpy(szChaosVmByteCodeFile, pArgv[i]);
//				} else if (_tcscmp(pArgv[i], _T("/ce")) == 0) {
//					i++;
//					_tcscpy(szChaosVmEmulationName, pArgv[i]);
//				} else {
//					Usage();
//					return 0;
//				}
//			break;
//			case _T('m'):case _T('M'):
//				// 设置模式
//				if (_tcsicmp(pArgv[i], _T("/mode")) == 0) {
//					__integer iMode = 0;
//					i++;
//					iMode = _ttoi(pArgv[i]);
//
//					if (iMode == 0) {
//						Mode = CRM_INFECT;
//					} else if (iMode == 1) {
//						Mode = CRM_EMULATION;
//					} else {
//						Mode = CRM_INFECT;
//					}/* end else */
//				} else {
//					// 消息框设定
//					if (_tcsicmp(pArgv[i], _T("/mbfne")) == 0) {
//						i++;
//						_tcscpy(szMessageBoxOnByteCodeFileNotExist, pArgv[i]);
//					} else if (_tcsicmp(pArgv[i], _T("/mefne")) == 0) {
//						i++;
//						_tcscpy(szMessageBoxOnEmulationFileNotExist, pArgv[i]);
//					} else if (_tcsicmp(pArgv[i], _T("/mbt")) == 0) {
//						i++;
//						_tcscpy(szMessageBoxTitle, pArgv[i]);
//					} else if (_tcsicmp(pArgv[i], _T("/mbs")) == 0) {
//						i++;
//						dwMessageStyle = _ttoi(pArgv[i]);
//					} else {
//						Usage();
//						return 0;
//					}
//				}/* end else */
//			break;
//			}/* end switch */
//		}/* end if */
//	}/* end for */
//
//	// 设定配置DIS结构
//	pDisAthConfigure->bIfXFileExistFailed = TRUE;
//	if (Mode == CRM_INFECT) {
//		pDisAthConfigure->wResourceID = IDR_CHAOSVM;
//		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_XFILE_DNA__;
//		pDisAthConfigure->dwDISResourceKey = __CHAOSVM_DECRYPT_KEY__;
//	} else if (Mode == CRM_EMULATION) {
//		pDisAthConfigure->wResourceID = IDR_CHAOSVM_EMULATION;
//		pDisAthConfigure->XFileAttachInfo.dwDNA = __CHAOSVM_LOADER_XFILE_DNA__;
//		pDisAthConfigure->dwDISResourceKey = __CHAOSVMLDR_DECRYPT_KEY__;
//	}
//
//	pDisAthConfigure->szResourceType = (__tchar *)_T("BIN");
//	iTarget = i;//记录目标路径索引
//	pDisAthConfigure->XFileAttachInfo.szTargetFilePath = pArgv[i];i++;//命令索引增加
//	pDisAthConfigure->XFileAttachInfo.bKeepTailData = TRUE;
//	pDisAthConfigure->XFileAttachInfo.szSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
//	pDisAthConfigure->XFileAttachInfo.szXSectionName = (__char *)__CHAOSVMP_SECTION_NAME__;
//	pDisAthConfigure->bProtectMyIAT = TRUE;
//	pDisAthConfigure->bProtectTargetIAT = TRUE;
//	pDisAthConfigure->XFileAttachInfo.bCloseNX = TRUE;
//	pDisAthConfigure->XFileAttachInfo.bCloseRandAddressMap = TRUE;
//	pDisAthConfigure->XFileAttachInfo.bRandomAllSectionName = TRUE;
//	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
//	pDisAthConfigure->XFileAttachInfo.bSetAllSectionCanWrite = TRUE;
//	__logic_memset__(pDisAthConfigure->XFileAttachInfo.bWillDelDataDirectoryIndexs, FALSE, 0x10);
//	pDisAthConfigure->XFileAttachInfo.bResetCheckSum = TRUE;
//	
//	pDisAthConfigure->iDISProtectDllCrc32Count = 0;
//	pDisAthConfigure->iDISProtectDllCallDllMainCrc32Count = 0;
//	pDisAthConfigure->iDISProtectApiCrc32Count = 0;
//	pDisAthConfigure->iTargetProtectDllCrc32Count = 0;
//	pDisAthConfigure->iTargetProtectDllCallDllMainCrc32Count = 0;
//	pDisAthConfigure->iTargetProtectApiCrc32Count = 0;
//
//	// 分析要设定的地址
//	{
//		__char seps[] = ":*,";
//		__char *token = NULL;
//		__char szAddrSizeList[256] = {0};
//		__integer iType = 0;
//		__address addrProcAddress = 0, addrKeyProcAddress = 0;
//		__integer iProcSize = 0, iKeyProcSize = 0;
//
//		UnicodeToAnsi(pArgv[i], _tcslen(pArgv[i]), szAddrSizeList, 256);
//		token = strtok(szAddrSizeList, seps);
//		while (token) {
//			if (iType == 0) {
//				if ((token[0] == 's') || (token[0] == 'S')) {
//					/*
//					 * 是否是通过扫描标记得到
//					 * 扫描标记,并且获取要保护的函数地址
//					 * 暂时未实现SDK功能
//					 */
//					goto _set_chaosvmp_console_configure;
//				} else {
//					addrProcAddress = String2Address(token);
//					iType++;
//				}
//			} else if (iType == 1) {
//				iProcSize = atoi(token);
//				iType++;
//			} else if (iType == 2) {
//				if ((token[0] == 'r') || (token[0] == 'R')) {
//					addrKeyProcAddress = 0;
//					iKeyProcSize = 0;
//					ChaosVmAthSelectProcedure(pConfigure, addrProcAddress, iProcSize, addrKeyProcAddress, iKeyProcSize);
//					iType = 0;
//					goto _next_token;
//				} else {
//					addrKeyProcAddress = String2Address(token);
//					iType++;
//				}
//			} else if (iType == 3) {
//				iKeyProcSize = atoi(token);
//				ChaosVmAthSelectProcedure(pConfigure, addrProcAddress, iProcSize, addrKeyProcAddress, iKeyProcSize);
//				iType = 0;
//			}
//		_next_token:
//			// 下一个标记
//			token = (__char *)strtok(NULL, seps);
//		}/* end while */
//	}
//
//	// 设置混乱虚拟机控制台结构
//_set_chaosvmp_console_configure:
//	pChaosVmpConsoleConfigure->bBackupOrigFile = bBackupOrigFile;
//	//pDisAthConfigure->pUserData0 = (__void *)pConfigure;
//
//	// 模式设定
//	if (Mode == CRM_INFECT) {
//		if (_tcslen(szChaosVmByteCodeFile) != 0) {
//			pChaosVmpConsoleConfigure->bUseByteCodeFileInInfectMode = TRUE;
//			_tcscpy(pChaosVmpConsoleConfigure->szChaosVmByteCodeFileNameInInfect, szChaosVmByteCodeFile);
//		} else {
//			pChaosVmpConsoleConfigure->bUseByteCodeFileInInfectMode = FALSE;
//			memset(pChaosVmpConsoleConfigure->szChaosVmByteCodeFileNameInInfect, 0, sizeof(__tchar) * 0x20);
//		}
//	} else if (Mode == CRM_EMULATION) {
//		_tcscpy(pChaosVmpConsoleConfigure->szChaosVmByteCodeFileNameInEmulation, szChaosVmByteCodeFile);//设置bytecode文件名称
//		if (_tcslen(szChaosVmEmulationName) == 0) {
//			pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = TRUE;
//			memset(pChaosVmpConsoleConfigure->szChaosVmNameInEmulation, 0, sizeof(__tchar) * 0x20);
//		} else {
//			_tcscpy(pChaosVmpConsoleConfigure->szChaosVmNameInEmulation, szChaosVmEmulationName);
//			pChaosVmpConsoleConfigure->bUseChaosVmEmulationInResource = FALSE;
//		}
//	}
//	pChaosVmpConsoleConfigure->Mode = Mode;
//
//	// 设置对话框
//	if (_tcslen(szMessageBoxTitle)) _tcscpy(pChaosVmpConsoleConfigure->szMessageBoxTitle, szMessageBoxTitle);
//	else memset(pChaosVmpConsoleConfigure->szMessageBoxTitle, 0, sizeof(__tchar) * 0x40);
//
//	if (_tcslen(szMessageBoxOnByteCodeFileNotExist)) _tcscpy(pChaosVmpConsoleConfigure->szMessageBoxOnByteCodeFileNotExist, szMessageBoxOnByteCodeFileNotExist);
//	else memset(pChaosVmpConsoleConfigure->szMessageBoxOnByteCodeFileNotExist, 0, sizeof(__tchar) * 0x100);
//
//	if (_tcslen(szMessageBoxOnEmulationFileNotExist)) _tcscpy(pChaosVmpConsoleConfigure->szMessageBoxOnEmulationFileNotExist, szMessageBoxOnEmulationFileNotExist);
//	else memset(pChaosVmpConsoleConfigure->szMessageBoxOnEmulationFileNotExist, 0, sizeof(__tchar) * 0x100);
//
//	pChaosVmpConsoleConfigure->dwMessageStyle = dwMessageStyle;
//
//	return iTarget;
//}

// 产生被保护代码区域的花指令
__memory __API__ GenChaosVmInvokeThunkCode(__integer iSize) {
	__memory pThunkCode = NULL;
	pThunkCode = (__memory)__logic_new_size__(iSize);
	if (!pThunkCode) return NULL;

	return pThunkCode;
}

CHAOSVMATH_CONFIGURE g_ChaosVmAthConfigure;
CHAOSVMP_CONSOLE_CONFIGURE g_ChaosVmpConsoleConfigure;
DISATH_CONFIGURE g_DisAthConfigure;

__integer _tmain(__integer iArgc, __tchar *pArgv[]) {
	/*__integer iTarget = 0;*/

	// 初始化混乱虚拟机附加器配置结构
	ChaosVmAthInitConfigure(&g_ChaosVmAthConfigure);
	ZeroMemory(&g_ChaosVmpConsoleConfigure, sizeof(CHAOSVMP_CONSOLE_CONFIGURE));
	ZeroMemory(&g_DisAthConfigure, sizeof(DISATH_CONFIGURE));

	// 分析命令行并设置配置结构
	//iTarget = HandleArguments(iArgc, pArgv, &g_ChaosVmAthConfigure, &g_DisAthConfigure, &g_ChaosVmpConsoleConfigure);
	//if (!iTarget)
	//	return -1;

	// 参数分析
	{
		HANDLE_ARGS_DO BackValue;
		BackValue = HandleArguments(iArgc, pArgv, &g_ChaosVmAthConfigure, &g_DisAthConfigure, &g_ChaosVmpConsoleConfigure);
		
		if (BackValue == HAD_FAILED)
			return -1;
		else if (BackValue == HAD_SUCCESS)
			goto _start;
		else if (BackValue == HAD_EXIT)
			return 0;
	}

_start:
	// 检验是否需要备份
	if (g_ChaosVmpConsoleConfigure.bBackupOrigFile) {
		__tchar szBackUpFilePath[MAX_PATH] = {0};
		__logic_tcscpy__(szBackUpFilePath, g_DisAthConfigure.XFileAttachInfo.szTargetFilePath);
		__logic_tcscat__(szBackUpFilePath, (__wchar *)_T(".bk"));
		CopyFile((LPCTSTR)(g_DisAthConfigure.XFileAttachInfo.szTargetFilePath), (LPCTSTR)szBackUpFilePath, FALSE);
	}

	// 保护丫的
	{
		__dword dwRet = 0;
		CHAOSVMATH_RET_INFO RetInfo = {0};

		//////////////////////////////////////////////////////////////////////////
		//设置ChaosVm附加器的配置结构

		// 设置字节码的文件名
		_tcscpy((TCHAR *)(g_ChaosVmAthConfigure.szChaosVmByteCodeFileName), (TCHAR *)(g_ChaosVmpConsoleConfigure.szChaosVmByteCodeFileNameInInfect));

		// 设置不同模式下的选项
		if (g_ChaosVmpConsoleConfigure.Mode == CRM_INFECT) {

			g_ChaosVmAthConfigure.bUseByteCodeFile = g_ChaosVmpConsoleConfigure.bUseByteCodeFileInInfectMode;

		} else if (g_ChaosVmpConsoleConfigure.Mode == CRM_EMULATION) {

			g_ChaosVmAthConfigure.bUseChaosVmEmulationInResource = g_ChaosVmpConsoleConfigure.bUseChaosVmEmulationInResource;
			_tcscpy((TCHAR *)(g_ChaosVmAthConfigure.szChaosVmEmulationFileName), (TCHAR *)(g_ChaosVmpConsoleConfigure.szChaosVmNameInEmulation));

		}
		g_ChaosVmAthConfigure.Mode = g_ChaosVmpConsoleConfigure.Mode;
		
		// 消息框设定
		_tcscpy((TCHAR *)(g_ChaosVmAthConfigure.szMessageBoxTitle), (TCHAR *)(g_ChaosVmpConsoleConfigure.szMessageBoxTitle));
		_tcscpy((TCHAR *)(g_ChaosVmAthConfigure.szMessageBoxOnByteCodeFileNotExist), (TCHAR *)(g_ChaosVmpConsoleConfigure.szMessageBoxOnByteCodeFileNotExist));
		_tcscpy((TCHAR *)(g_ChaosVmAthConfigure.szMessageBoxOnEmulationFileNotExist), (TCHAR *)(g_ChaosVmpConsoleConfigure.szMessageBoxOnEmulationFileNotExist));
		g_ChaosVmAthConfigure.dwMessageStyle = g_ChaosVmpConsoleConfigure.dwMessageStyle;

		// 调试虚拟机,2012.2.9 新增
		__logic_memcpy__(&(g_ChaosVmAthConfigure.DebugConfigure), &(g_ChaosVmpConsoleConfigure.DebugConfigure), sizeof(CHAOSVM_EMULATION_CONFIGURE_DEBUG_CONFIGURE));

		g_ChaosVmAthConfigure.pGenChaosVmInvokeThunkCode = GenChaosVmInvokeThunkCode;
		g_ChaosVmAthConfigure.PowerProtecterAttachConfigure.pGenPowerProtecterInvokeThunkCode = GenChaosVmInvokeThunkCode;
		g_DisAthConfigure.pUserData0 = (__void *)&g_ChaosVmAthConfigure;
		g_DisAthConfigure.pUserData1 = (__void *)&RetInfo;
		dwRet = ChaosVmAthAttach(&g_DisAthConfigure);
		if (__DISATH_SUCCESS__(dwRet))
			printf("^_^ success\r\n");
		else
			printf("-_- failed\r\n");
	}

	//如果是在调试模式下,则将目标程序设定为窗口程序
#if defined(__PRINT_DBG_INFO__)
	{
		__memory pMem = NULL;
		PIMAGE_NT_HEADERS pNtHdr = NULL;

		pMem = MappingFile(g_ChaosVmpConsoleConfigure.szTargetFilePath, NULL, TRUE, 0, 0);
		pNtHdr = GetNtHeader(pMem);
		pNtHdr->OptionalHeader.Subsystem = IMAGE_SUBSYSTEM_WINDOWS_GUI;
		UnmapViewOfFile(pMem);
	}
#endif

	return 0;
}
