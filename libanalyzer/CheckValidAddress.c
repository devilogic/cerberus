/*
 * 这里是唯一使用系统相关的源文件
 */

#include <Windows.h>

#define __GetDosHeader__(x) ((PIMAGE_DOS_HEADER)(x))
#define __GetNtHeader__(x) ((PIMAGE_NT_HEADERS)((__dword)__GetDosHeader__(x)->e_lfanew + (__dword)(x)))

#define __InThisSectionByAddress__(pSectH, ImageBase, Address)\
	((Address) >= (ImageBase) + (pSectH)->VirtualAddress) && ((Address) < ((ImageBase) + (pSectH)->VirtualAddress + (pSectH)->Misc.VirtualSize))

#define __CheckLevelInCheckValidAddress__(Valid)\
	if (CheckLevel <= CHK_ ## Valid) {\
		ValidAddr = Valid;\
		goto __exit;}
VALID_ADDR __INTERNAL_FUNC__ CheckValidAddress(__memory pMem, __address addrAddress, CHECK_VALID_ADDR_LEVEL CheckLevel) {
	VALID_ADDR ValidAddr = INVALID_ADDRESS;
	PIMAGE_NT_HEADERS pNtHdr = __GetNtHeader__(pMem);
	__address ImageBase = (__address)(pNtHdr->OptionalHeader.ImageBase);
	__integer iSizeOfImage = (__integer)(pNtHdr->OptionalHeader.SizeOfImage);
	if (addrAddress < 0x80000000) {//用户范围内
		__CheckLevelInCheckValidAddress__(IN_USER_MEM);

		if ((addrAddress >= ImageBase) && (addrAddress < (ImageBase + iSizeOfImage))) {
			__word wNumberOfSection = pNtHdr->FileHeader.NumberOfSections;
			PIMAGE_SECTION_HEADER p1thSecHdr = IMAGE_FIRST_SECTION(pNtHdr);
			__address addr1thSecStartAddress = ImageBase + (__address)(p1thSecHdr->VirtualAddress);
			PIMAGE_SECTION_HEADER pTailSecHdr = p1thSecHdr + (wNumberOfSection - 1);
			__address addrTailSecEndAddress = ImageBase + (__address)(pTailSecHdr->VirtualAddress + pTailSecHdr->Misc.VirtualSize);

			// 是否在映射范围内
			__CheckLevelInCheckValidAddress__(IN_IMAGE_MEM);

			// 检查是否在节内范围
			if ((addrAddress >= addr1thSecStartAddress) && (addrAddress < addrTailSecEndAddress)) {
				PIMAGE_SECTION_HEADER pSecHdr = NULL;
				__CheckLevelInCheckValidAddress__(IN_SEC_MEM);
				
				// 是否是可以运行的内存
				for (pSecHdr = p1thSecHdr; wNumberOfSection > 0; wNumberOfSection--, pSecHdr++) {
					// 检查此节是否有可执行熟悉
					__dword dwCharacteristics = pSecHdr->Characteristics;
					if ((dwCharacteristics & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE) {
						// 检查内存是否在此节内
						if (__InThisSectionByAddress__(pSecHdr, ImageBase, addrAddress)) {
							__CheckLevelInCheckValidAddress__(IN_CAN_EXEC);
							
							// 走到这里说明发生异常了
						}
					}
				}/* end for */
			}/* end if */
		}/*end if */
	}
__exit:
	return ValidAddr;
}