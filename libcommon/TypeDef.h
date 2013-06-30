#if !defined(__TYPEDEF_H__)
#define __TYPEDEF_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#define __BYTES_PER_KB__                    1024LL
#define __BYTES_PER_MB__                    1048576LL
#define __BYTES_PER_GB__                    1073741824LL
#define __BYTES_PER_TB__                    1099511627776LL
#define __BYTES_PER_PB__                    1125899906842624LL

#ifdef _MSC_VER
typedef signed __int8			__char;
typedef signed __int16			__sword;
typedef signed __int32			__sdword;
typedef signed __int64			__sqword;

typedef unsigned __int8			__byte;
typedef unsigned __int16		__word;
typedef unsigned __int32		__dword;
typedef unsigned __int64		__qword;

#else //! _MSC_VER
#include <inttypes.h>
#include <limits.h>
typedef char					__char;
typedef short					__sword;
typedef long					__sdword;
typedef long long               __sqword;

typedef unsigned char			__byte;
typedef unsigned short		    __word;
typedef unsigned long		    __dword;
typedef unsigned long long		__qword;
#endif

typedef float					__float;
typedef double					__double;

typedef __byte					__bool;
#if !defined(TRUE)
#define TRUE	1
#endif

#if !defined(FALSE)
#define FALSE	0
#endif

typedef void					__void;
typedef __byte*					__memory;
typedef __word					__wchar;

#if defined(_UNICODE)
#define __tchar					__wchar
#else
#define __tchar					__char
#endif

#define __MAX_BYTE_SIZE__		0xFF
#define __MAX_WORD_SIZE__		0xFFFF
#define __MAX_DWORD_SIZE__		0xFFFFFFFF
#define __MAX_QWORD_SIZE__		0xFFFFFFFFFFFFFFFF
#define __MAX_FLOAT_SIZE__		0xFFFFFFFF
#define __MAX_DOUBLE_SIZE__		0xFFFFFFFFFFFFFFFF

#if defined(__X64__)
typedef __qword					__time;
typedef __qword					__address;
typedef __qword					__offset;
typedef __qword					__integer;
typedef __sqword				__sinteger;
#define __MAX_INTEGER_SIZE__	0xFFFFFFFFFFFFFFFF
#else
typedef __dword					__time;
typedef __dword					__address;
typedef __dword					__offset;
typedef __dword					__integer;
typedef __sdword				__sinteger;
#define __MAX_INTEGER_SIZE__	0xFFFFFFFF
#endif

#define __IsNegative8__(uNumber)			((unsigned char)(uNumber) >= 0x80)
#define __IsNegative16__(uNumber)			((unsigned short)(uNumber) >= 0x8000)
#define __IsNegative32__(uNumber)			((unsigned long)(uNumber) >= 0x80000000)
#define __IsNegative64__(uNumber)			((unsigned long)(uNumber) >= 0x8000000000000000)

#define __ToNegative__(uNumber)				(~(uNumber) + 1)

#define __DEF_ALIGN__						sizeof(__integer)

#define __Is_Align__(uNumber, Alignment)\
	((uNumber) < (Alignment) ? 0:\
	(((uNumber) % (Alignment)) == 0))

#define __Alig__(uNumber, Alignment)\
	((uNumber) < (Alignment) ? (Alignment) :\
	(uNumber) % (Alignment) == 0 ? (uNumber) :\
	(uNumber) - (uNumber) % (Alignment) + (Alignment))

#define __CountOf__(Type, Size)				((Size) / sizeof(Type))

#if !defined(NULL)
#define NULL					0
#endif

#if !defined(_T)
#define _T(x)					L ## x
#endif

#define __MakeWord__(a, b)		((__word)(((__byte)(((__dword *)(a)) & 0xff)) | ((__word)((__byte)(((__dword)(b)) & 0xff))) << 8))
#define __MakeDword__(a, b)     ((__dword)(((__word)(((__dword *)(a)) & 0xffff)) | ((__dword)((__word)(((__dword)(b)) & 0xffff))) << 16))
#define __LoWord__(l)           ((__word)(((__dword)(l)) & 0xffff))
#define __HiWord__(l)           ((__word)((((__dword)(l)) >> 16) & 0xffff))
#define __LoByte__(w)           ((__byte)(((__dword)(w)) & 0xff))
#define __HiByte__(w)           ((__byte)((((__dword)(w)) >> 8) & 0xff))

#if defined(__cplusplus)
}
#endif

#endif
