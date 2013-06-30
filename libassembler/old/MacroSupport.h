#if !defined(__MACROSUPPORT_H__)
#define __MACROSUPPORT_H__

#define __new__(Type, Count)				new Type [(Count)]
#define __delete__(Pointer)					delete [] (Pointer)

#define __IsNegative8__(uNumber)			((unsigned char)(uNumber) >= 0x80)
#define __IsNegative16__(uNumber)			((unsigned short)(uNumber) >= 0x8000)
#define __IsNegative32__(uNumber)			((unsigned long)(uNumber) >= 0x80000000)

#define __ToNegative__(uNumber)				(~(uNumber) + 1)

#define __Alig__(uNumber, Alignment)			((((uNumber) % (Alignment)) == 0) ? (uNumber) : ((uNumber) - ((uNumber) % (Alignment)) + (Alignment)))

#endif
