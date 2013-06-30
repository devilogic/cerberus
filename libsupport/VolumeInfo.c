#include "VolumeInfo.h"
#include <Windows.h>
#include <Setupapi.h>

#pragma comment(lib, "setupapi.lib")

__bool __API__ IsReMovableDrive(__tchar *lpDev) {
	if (GetDriveType(lpDev) == DRIVE_REMOVABLE)
		return TRUE;
	return FALSE;
}

__dword __API__ GetVolumeSerialNumber(__tchar *lpVolumeName) {
	__dword dwVolumeSerialNumber = 0;
	if (GetVolumeInformation(lpVolumeName, NULL, 0, (__dword *)&dwVolumeSerialNumber, NULL, NULL, NULL, 0))
		return dwVolumeSerialNumber;
	return 0;
}
