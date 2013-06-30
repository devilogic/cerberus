#include "xRand.h"
#include "RandRoll.h"

__INLINE__ __dword __INTERNAL_FUNC__ GenerateRandomSeed()
{
	//DWORD dwRandSeed = 0;
	//dwRandSeed = GetTickCount();
	////__asm
	////{
	////	push edx
	////	push eax
	////	rdtsc
	////	mov dwRandSeed, eax
	////	pop eax
	////	pop edx
	////}
	//return dwRandSeed;
	return GetRandDword();
}

__dword __API__ GenerateRandomNumber() {
	__byte bNew1, bNew2, bNew3, bNew4;
	__dword dwSeed = 0, dwRand = 0;
	__memory pPoint = NULL;
	dwSeed = GenerateRandomSeed();
	bNew1 = (__byte)dwSeed;
	dwSeed = GenerateRandomSeed();
	bNew2 = (__byte)dwSeed;
	dwSeed = GenerateRandomSeed();
	bNew3 = (__byte)dwSeed;
	dwSeed = GenerateRandomSeed();
	bNew4 = (__byte)dwSeed;

	pPoint = (__memory)&dwRand;
	*pPoint = bNew4;
	*(pPoint + 1) = bNew2;
	*(pPoint + 2) = bNew1;
	*(pPoint + 3) = bNew3;

	return dwRand;
}

__bool __API__ RandRoll(__bool *pInBoolArray) {
	__dword dwRoll = GenerateRandomNumber() % 100;
	return pInBoolArray[dwRoll];
}

__void __API__ GenerateRollArray(__bool *pOutBoolArray, __integer iSeed) {
	MakeRandArray((__bool *)pOutBoolArray, iSeed);
}
