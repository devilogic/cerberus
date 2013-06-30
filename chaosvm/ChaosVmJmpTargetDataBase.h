#if !defined(__CHAOSVMJMPTARGETDATABASE_H__)
#define __CHAOSVMJMPTARGETDATABASE_H__

#include "Common.h"
#include "ChaosVmp.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__void __INTERNAL_FUNC__ InitJmpTargetDataBaseTable(__integer iIndex);
PCHAOSVMP_JMPTARGET_INST __INTERNAL_FUNC__ QueryJmpTargetInstFromTable(__integer iIndex, __address addrAddress);
PCHAOSVMP_JMPTARGET_INST __INTERNAL_FUNC__ AddJmpTargetInstToTable(__integer iIndex, __address addrAddress,  PCHAOSVMP_JMPTARGET_INST pJmpTargetInst);
__void __INTERNAL_FUNC__ DestoryJmpTargetTable(__integer iIndex);

#if defined(__cplusplus)
}
#endif

#endif