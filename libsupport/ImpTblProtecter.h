#define __MAX_LIBRARY_KEY_COUNT__					256										//保护动态库密钥最大的数量
#define __MAX_API_NAME_CRC_COUNT__					2048									//保护引入函数的CRC列表最大的数量
#define __MAX_LIBRARY_COUNT__						__MAX_LIBRARY_KEY_COUNT__				//保护动态库最大的数量
#define __MAX_API_COUNT__							__MAX_API_NAME_CRC_COUNT__				//保护引入函数的最大数量
#define __MAX_LIBRARY_NAME_SIZE__					32										//保护动态库的名称最长长度
#define __MAX_JMP_ADDRESS_TABLE_COUNT__				__MAX_API_COUNT__ * 2					//新引入表中跳转指令表的计数
#define __USE_DEF_IMAGEBASE_AS_ORIG__				0xFFFFFFFF								//使用默认的基地址
#define __MAX_IMPORT_REFERENCE_COUNT__				4096									//指令引入地址

/*
 * 引入表保护结构
 */
typedef struct _IMPORT_PROTECT {
	__byte bXor;//用于解码CRC32值的KEY

	__integer iLibraryKeyCount;//库程序密钥数量
	__dword dwLibraryKeyList[__MAX_LIBRARY_KEY_COUNT__];//库程序密钥队列
	__integer iLibraryNameLengthList[__MAX_LIBRARY_KEY_COUNT__];//库名长度队列
	__char LibraryNameList[__MAX_LIBRARY_COUNT__][__MAX_LIBRARY_NAME_SIZE__];//库名列表

	__integer iApiNumberInThisLibrary[__MAX_LIBRARY_COUNT__];//当前库下有多少个API

	// 以下这4组拥有同一个计数就是iApiNameCrc32Count
	__integer iApiNameCrc32Count;//API名字CRC32数量
	__bool bIsOrdList[__MAX_API_NAME_CRC_COUNT__];//确定是否是以序数排序
	__dword dwApiNameCrc32List[__MAX_API_NAME_CRC_COUNT__];//存放CRC32的值
	__dword dwFirstThunkList[__MAX_API_NAME_CRC_COUNT__];//存放此函数对应的FirstThunk值RVA

	__address addrImageBase;//映射的基地址
	__offset ofJmpTableRva;//跳转表RVA

	HMODULE hDll;//当前DLL句柄

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为要重映射DLL的所需的字段
	__dword dwProtectDllCrc32List[__MAX_LIBRARY_COUNT__];//需要进行重映射的DLL的CRC值
	__integer iProtectDllCrc32Count;//需要进行重映射的DLL的CRC值列表计数
	__dword dwProtectDllCallDllMainCrc32List[__MAX_LIBRARY_COUNT__];//执行DllMain的库
	__integer iProtectDllCallDllMainCrc32Count;//不执行DllMain的库列表计数

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为进行API抽取所需字段
	__dword dwProtectApiCrc32List[__MAX_API_NAME_CRC_COUNT__];//需要进行API抽取的API, CRC32值
	__integer iProtectApiCrc32Count;//需要进行API抽取的API数量

	//////////////////////////////////////////////////////////////////////////
	// 以下字段为保存引用API指令抽取内存的RVA
	__offset ofImportTableReferenceAddressRVA[__MAX_IMPORT_REFERENCE_COUNT__];
	__offset ofAPINowRVA[__MAX_IMPORT_REFERENCE_COUNT__];
	__integer iImportTableReferenceAddressCount;
} IMPORT_PROTECT, *PIMPORT_PROTECT;

// 初始化引入表器
__void __API__ InitImportProtecter();
// 加密引入表
__bool __API__ EncryptImportTable(__memory pImageBase, PIMPORT_PROTECT pImportProtect, __bool bOnFile, __memory pOutImportTable);
// 解密引入表,在目标程序中调用
__bool __API__ DecryptImportTable(PIMPORT_PROTECT pImportProtect);

//////////////////////////////////////////////////////////////////////////
// 以下是强力的力量加解密引入表相关函数与结构的定义

// 在保护过程中生成花指令的函数回调指针
typedef __memory (__INTERNAL_FUNC__ *FPAddThunkCodeStub)(__address addrNowApiAddress);
typedef struct _POWERDECRYPTIMPORTTABLE_ARG {
	PIMPORT_PROTECT pImportProtect;//指向一个引入表保护结构
	FPAddThunkCodeStub pAddThunkCodeStub;//用户自定义的变形STUB函数
} POWERDECRYPTIMPORTTABLE_ARG, *PPOWERDECRYPTIMPORTTABLE_ARG;

// 这个记录记录了代码中引用引入表函数的位置
typedef struct _REFERENCE_IMPORT_TABLE_ADDRESS {
	ud_t ud_obj;//此指令的UD_T结构
	__address addrReferenceMemAddress;//引用内存地址
	__memory pReferenceFileAddress;//引用文件地址
	__offset ofReferenceRVA;//引用的RVA
	struct _REFERENCE_IMPORT_TABLE_ADDRESS *pNext;//下一个节点
} REFERENCE_IMPORT_TABLE_ADDRESS, *PREFERENCE_IMPORT_TABLE_ADDRESS;

// 释放引入地址链表
__void __API__ ReleaseReferenceImportTableAddress(PREFERENCE_IMPORT_TABLE_ADDRESS *pReferenceImportTableAddressPoint);
// 计算引入地址链表的个数
__integer __API__ CountReleaseReferenceImportTable(PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceImportTableAddress);
// 力量加密引入表
PREFERENCE_IMPORT_TABLE_ADDRESS __API__ PowerEncryptImportTable(__memory pMem, __address addrOrigImageBase, PIMPORT_PROTECT pImportProtect, __bool bOnFile, __offset ofJmpTableRva);
// 力量解密引入表,在目标文件中调用
__bool __API__ PowerDecryptImportTable(PPOWERDECRYPTIMPORTTABLE_ARG pArg);
