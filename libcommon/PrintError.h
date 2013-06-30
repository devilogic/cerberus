#if !defined(__PRINTERROR_H__)
#define __PRINTERROR_H__

#include "TypeDef.h"
#include "Configure.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__void __INTERNAL_FUNC__ LogicPrintError(__char *szMsg, __integer iErrNo, __integer iLine, __char *szFile);

#define __LogicPrintError__(Msg, ErrNo)					LogicPrintError((__char *)(Msg), (__integer)(ErrNo), (__integer)__LINE__, (__char *)__FILE__)

#if defined(__cplusplus)
}
#endif

#endif
