#include "Endian.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__word __INTERNAL_FUNC__ MirrorWord(__word x) {
	return (x << 8) | (x >> 8);
}

__dword __INTERNAL_FUNC__ MirrorDword(__dword x) {
	__dword n = (__byte) x;
	n <<= 8; n |= (__byte)(x >> 8);
	n <<= 8; n |= (__byte)(x >> 16);
	return (n << 8) | (__byte)(x >> 24);
}

__qword __INTERNAL_FUNC__ MirrorQword(__qword x) {
	__qword n = (__byte) x;
	n <<= 8; n |= (__byte)(x >> 8);
	n <<= 8; n |= (__byte)(x >> 16);
	n <<= 8; n |= (__byte)(x >> 24);
	n <<= 8; n |= (__byte)(x >> 32);
	n <<= 8; n |= (__byte)(x >> 40);
	n <<= 8; n |= (__byte)(x >> 48);
	return (n << 8) | (__byte)(x >> 56);
}

#if defined(__cplusplus)
}
#endif