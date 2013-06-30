#if !defined(__VOLUMEINFO_H__)
#define __VOLUMEINFO_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __MAX_VOLUME_INFO_BUF_SIZE__		256

__bool __API__ IsReMovableDrive(__tchar *lpDev);
__dword __API__ GetVolumeSerialNumber(__tchar *lpVolumeName);

#if defined(__cplusplus)
}
#endif

#endif
