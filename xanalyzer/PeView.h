#if !defined(__PEVIEW_H__)
#define __PEVIEW_H__

#include "Common.h"

typedef struct _PEVIEW_CONFIGURE {
	__bool bPrintPEHeader;
	__bool bPrintSectionHeaders;
	__bool bPrintImportTable;
	__bool bPrintExportTable;
	__bool bPrintDebugTable;
	__bool bPrintRelocateTable;
	__bool bPrintResourceTable;
} PEVIEW_CONFIGURE, *PPEVIEW_CONFIGURE;

__bool __INTERNAL_FUNC__ PeView(__memory pMem, __tchar *pResultFilePath, PPEVIEW_CONFIGURE pConfigure);

#endif