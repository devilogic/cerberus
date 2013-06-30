#if !defined(__JUNKCODEGEN_H__)
#define __JUNKCODEGEN_H__

#include "Common.h"
#include "ThunkCoderRandRoll.h"
#include "ThunkCoderConfigure.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__memory __INTERNAL_FUNC__ GenerateJunkCode(__integer *piOutSize, PTHUNKCODER_CONFIGURE pThunkCoderConfigure);

#if defined(__cplusplus)
}
#endif

#endif
