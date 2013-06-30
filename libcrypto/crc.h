#if !defined(__CRC_H__)
#define __CRC_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define UPDC32(octet, crc)\
  (__dword)((crc_32_tab[(((__dword)(crc)) ^ ((__byte)(octet))) & 0xff] ^ (((__dword)(crc)) >> 8)))

__dword __API__ crc32(__memory data, __integer length);
__dword __API__ crc32int(__dword *data);
__bool __API__ crc32_selftests ();
	
extern __dword crc_32_tab[];
	
#if defined(__cplusplus)
}
#endif

#endif
