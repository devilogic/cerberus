#include "MemoryOperate.h"

#define __MAX_DYNAMICARRAY_COUNT__			0x1000
#define __EXCEPTION_EXECUTE_HANDLER__       1
#define __EXCEPTION_CONTINUE_SEARCH__       0
#define __EXCEPTION_CONTINUE_EXECUTION__    -1

__integer __INTERNAL_FUNC__ InputValueToMemory(__memory *pMemoryPoint, __integer iPoint, __memory pValue, __integer iValueSize) {
	__memory pArray = *pMemoryPoint;
	if (!pArray) {
		pArray = __logic_new__(__byte, (__MAX_DYNAMICARRAY_COUNT__ * iValueSize));
		__logic_memcpy__(pArray, pValue, iValueSize);
		*pMemoryPoint = pArray;
	} else {
		__try {
			__logic_memcpy__(pArray + iPoint, pValue, iValueSize);
		} __except(__EXCEPTION_EXECUTE_HANDLER__) {
			__integer iNewSize = __Alig__(iPoint + (__MAX_DYNAMICARRAY_COUNT__ * iValueSize), __DEF_ALIGN__);
			__memory pTmpBuffer = __logic_new__(__byte, iPoint);//¡Ÿ ±ª∫≥Â«¯
			__logic_memcpy__(pTmpBuffer, pArray, iPoint);
			__logic_delete__(pArray);
			pArray = __logic_new__(__byte, iNewSize);
			__logic_memset__(pArray, 0, iNewSize);
			__logic_memcpy__(pArray, pTmpBuffer, iPoint);
			__logic_delete__(pTmpBuffer);
			__logic_memcpy__(pArray + iPoint, pValue, iValueSize);
			iPoint += iValueSize;
		}
	}/* end else */
	return iPoint;
}

__memory __INTERNAL_FUNC__ GetValueFormMemory(__memory pMemory, __integer iPoint, __integer iValueSize) {
	__memory pPoint = NULL;
	__try {
		__integer iPlusSize = iPoint * iValueSize;
		pPoint = pMemory + iPlusSize;
	} __except(__EXCEPTION_EXECUTE_HANDLER__) {
		pPoint = NULL;
	}

	return pPoint;
}
