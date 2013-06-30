#if !defined(__ENDIAN_H__)
#define __ENDIAN_H__

#include "Configure.h"
#include "TypeDef.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define __IS_LITTLE_ENDIAN__
//#define __IS_BIG_ENDIAN__

#if defined(__IS_LITTLE_ENDIAN__)
#if !defined(__LITTLE_ENDIAN__)
#define __LITTLE_ENDIAN__ 1234
#endif

#if !defined(__BYTE_ORDER__)
#define __BYTE_ORDER__ __LITTLE_ENDIAN__
#endif

#elif defined(__IS_BIG_ENDIAN__)
#if !defined(__BIG_ENDIAN__)
#define __BIG_ENDIAN__ 4321
#endif

#if !defined(__BYTE_ORDER__)
#define __BYTE_ORDER__ __BIG_ENDIAN__
#endif

#endif

#if __BYTE_ORDER__ == __BIG_ENDIAN__
#define __LE16__(x) MirrorBytes16(x)
#define __LE32__(x) MirrorBytes32(x)
#define __LE64__(x) MirrorBytes64(x)
#else
#define __LE16__(x) (x)
#define __LE32__(x) (x)
#define __LE64__(x) (x)
#endif

#if __BYTE_ORDER__ == __LITTLE_ENDIAN__
#define __BE16__(x) MirrorWord(x)
#define __BE32__(x) MirrorDword(x)
#define __BE64__(x) MirrorQword(x)
#else
#define __BE16__(x) (x)
#define __BE32__(x) (x)
#define __BE64__(x) (x)
#endif

__word __INTERNAL_FUNC__ MirrorWord(__word x);
__dword __INTERNAL_FUNC__ MirrorDword(__dword x);
__qword __INTERNAL_FUNC__ MirrorQword(__qword x);

#if defined(__cplusplus)
}
#endif

#endif
