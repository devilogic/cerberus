#if !defined(__IATREF_H__)
#define __IATREF_H__

#include "Common.h"

typedef struct _IATREF_CONFIGURE {
	__bool bIATREF;
} IATREF_CONFIGURE, *PIATREF_CONFIGURE;

__bool __INTERNAL_FUNC__ IatRef(__memory pMem, __tchar *pResultFilePath, PIATREF_CONFIGURE pConfigure);

#endif