#if !defined(__DUMP_H__)
#define __DUMP_H__

#include "Common.h"

typedef struct _DUMP_CONFIGURE {
	__bool bDump;//转存
	__integer iDumpSize;//转存的长度
	__bool bEntry;//转存入口点
	__integer iEntrySize;//转存入口点长度

	// 这个值是需要设置的
	__integer iFileSize;//文件的长度
} DUMP_CONFIGURE, *PDUMP_CONFIGURE;

__bool __INTERNAL_FUNC__ Dump(__memory pMem, __tchar *pResultFilePath, PDUMP_CONFIGURE pConfigure);

#endif