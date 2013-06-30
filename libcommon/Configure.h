#if !defined(__CONFIGURE_H__)
#define __CONFIGURE_H__

#include "xConfigure.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
#define __EXTERN__ extern "C"
#else
#define __EXTERN__ extern
#endif

#if defined(_MSC_VER)
#define __INLINE__ __inline
#define __API__ __stdcall
#define __INTERNAL_FUNC__ __cdecl
#define __FASTCALL__ __fastcall
#define __NAKED__ __declspec(naked)
#define __EXPORT__	extern __declspec(dllexport)
#define __STATIC__ static
#define __NEED_EXPORT__
#else
#define __INLINE__ __inline
#define __API__	__stdcall
#define __INTERNAL_FUNC__ __stdcall
#define __FASTCALL__ __fastcall
#define __NAKED__ __declspec(naked)
#define __EXPORT__ __declspec(naked)
#define __STATIC__ static
#define __NEED_EXPORT__
#endif

#define __REGISTER__ register

#if !defined( __GNUC__ ) && (defined( __MSDOS__ ) || defined( __WIN16__ ))	
#define __CONST__ const far
#else
#define __CONST__ const
#endif

#if defined(_MSC_VER)
#define __ALIGN__(Alignment) __declspec(align(Alignment))
#else
#define __ALIGN__()
#endif
	
#if defined(__cplusplus)
}
#endif

#endif
