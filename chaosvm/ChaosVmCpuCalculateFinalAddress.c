__INLINE__ __address __INTERNAL_FUNC__ CalculateFinalAddress(__address addrCurrAddress, __dword dwDisplacement, __integer iSize) {
	__dword dwChangeDisplacement = 0;

	if (iSize == sizeof(__byte)) {
		if (__IsNegative8__(dwDisplacement)) {
			(__byte)dwChangeDisplacement = (__byte)__ToNegative__(dwDisplacement);
			addrCurrAddress -= dwChangeDisplacement;
		} else {
			addrCurrAddress += dwDisplacement;
		}
	} else if (iSize == sizeof(__word)) {
		if (__IsNegative16__(dwDisplacement)) {
			(__word)dwChangeDisplacement = (__word)__ToNegative__(dwDisplacement);
			addrCurrAddress -= dwChangeDisplacement;
		} else {
			addrCurrAddress += dwDisplacement;
		}
	} else if (iSize == sizeof(__dword)) {
		if (__IsNegative32__(dwDisplacement)) {
			(__dword)dwChangeDisplacement = (__dword)__ToNegative__(dwDisplacement);
			addrCurrAddress -= dwChangeDisplacement;
		} else {
			addrCurrAddress += dwDisplacement;
		}
	}
	return addrCurrAddress;
}

#define __JmpUpOffset__(Offset, InstLen) ((~(Offset) + 1) - (InstLen))
#define __JmpDownOffset__(Offset, InstLen) ((Offset) + (InstLen))

#define __JmpBit8Up__()\
	bOffset = __JmpUpOffset__(bOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress - bOffset;

#define __JmpBit8Down__()\
	bOffset = __JmpDownOffset__(bOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress + bOffset;

#define __JmpBit16Up__()\
	wOffset = __JmpUpOffset__(wOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress - wOffset;

#define __JmpBit16Down__()\
	wOffset = __JmpDownOffset__(wOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress + wOffset;

#define __JmpBit32Up__()\
	dwOffset = __JmpUpOffset__(dwOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress - dwOffset;

#define __JmpBit32Down__()\
	dwOffset = __JmpDownOffset__(dwOffset, bInstLength);\
	addrTargetAddress = addrTargetAddress + dwOffset;

__INLINE__ __address __INTERNAL_FUNC__ CalculateJmpAddress(__address addrCurrAddress, __dword dwInstLength, __dword dwOffsetValue, __integer iSize) {
	__byte bInstLength = (__byte)dwInstLength;
	__address addrTargetAddress = addrCurrAddress;

	if (iSize == sizeof(__byte)) {
		__byte bOffset = (__byte)dwOffsetValue;
		if (__IsNegative8__(bOffset)) {
			__JmpBit8Up__();
		} else {
			__JmpBit8Down__();
		}
	} else if (iSize == sizeof(__word)) {
		__word wOffset = (__word)dwOffsetValue;
		if (__IsNegative16__(wOffset)) {
			__JmpBit16Up__();
		} else {
			__JmpBit16Down__();
		}
	} else if (iSize == sizeof(__dword)) {
		__dword dwOffset = (__dword)dwOffsetValue;
		if (__IsNegative32__(dwOffset)) {
			__JmpBit32Up__();
		} else {
			__JmpBit32Down__();
		}
	}
	return addrTargetAddress;
}
