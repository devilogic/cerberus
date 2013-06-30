#include "xor.h"

__dword __API__ PolyXorKey(__dword dwKey) {
	__integer i = 0, j = 0, n = 0;
	__memory pKey = (__memory)&dwKey;
	__byte bVal = 0, bTmp = 0, bTmp2 = 0;
	dwKey ^= 0x5DEECE66DL + 2531011;
	for (i = 0; i < sizeof(__dword); i++, pKey++) {
		bVal = *pKey;
		/*
		* 第一位与第二位异或放到第一位,依次类推
		* 到达第八位,与第一位异或放到第八位
		* 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
		*/
		for (j = 0x80, n = 7; j > 0x01; j /= 2, n--) {
			bTmp = (bVal & j) >> n;
			bTmp2 = (bVal & j / 2) >> (n - 1);
			bTmp ^= bTmp2;
			bTmp <<= n;
			bVal |= bTmp;
		}
		bTmp = bVal & 0x01;
		bTmp2 = bVal & 0x80 >> 7;
		bTmp ^= bTmp2;

		*pKey = bVal;
	}/* end for */
	return dwKey;
}

__void __API__ XorArray(__dword dwKey, __memory pPoint, __memory pOut, __integer iLength) {
	__dword dwNextKey = dwKey;
	__memory pKey = (__memory)&dwNextKey;
	__integer i = 0, j = 0;
	for (i = 0; i < iLength; i++) {
		pOut[i] = pPoint[i] ^ pKey[j];
		if (j == 3) {
			// 变换Key
			dwNextKey = PolyXorKey(dwNextKey);
			j = 0;
		} else j++;
	}
}

__void __API__ XorCoder(__memory pKey, __memory pBuffer, __integer iLength) {
	__integer i = 0;
	for (i = 0; i < iLength; i++)
		pBuffer[i] = pBuffer[i] ^ pKey[i];
}

__void __API__ XorKey32Bits(__dword dwKeyContext, __memory pKey, __integer iKeyLength) {
	__integer i = 0, iCount = 0;
	__dword dwKey = dwKeyContext;
	__memory pOutPut = pKey;
	iCount = (iKeyLength % sizeof(__dword) != 0) ? iKeyLength / sizeof(__dword) + 1 : iKeyLength / sizeof(__dword);

	while (iCount--) {
		dwKey = PolyXorKey(dwKey);
		*(__dword *)pOutPut ^= dwKey;
		pOutPut += sizeof(__dword);
	}
}

