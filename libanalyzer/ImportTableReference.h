typedef struct _IMPORT_TABLE_REFERENCE {
	ud_t ud_obj;//此指令的UD_T结构
	__char szLibName[0x20];//库名称

	__bool bOrdinal;//以序号引出
	union {
		__word wOrdinal;//序号
		__char szProcName[0x40];//函数名
	};

	__address addrFirstThunk;//用于保存地址的内存地址
	__offset ofFirstThunkFileOffset;//用于保存地址的文件偏移
	__offset ofFirstThunk;//用于保存地址的RVA
	__address addrReferenceMemAddress;//引用内存地址
	__offset ofReferenceFileOffset;//引用文件偏移
	__offset ofReferenceRVA;//引用的RVA

	__address addrAddressReferenceMemAddress;//引用地址内存地址
	__offset ofAddressReferenceFileOffset;//引用地址文件偏移
	__offset ofAddressReferenceRVA;//引用地址的RVA

	struct _IMPORT_TABLE_REFERENCE *pNext;//下一个节点
} IMPORT_TABLE_REFERENCE, *PIMPORT_TABLE_REFERENCE;

PIMPORT_TABLE_REFERENCE __API__ GenerateImportTableReference(__memory pMem);
__void __API__ ReleaseImportTableReference(PIMPORT_TABLE_REFERENCE *pImportTableReferencePoint);