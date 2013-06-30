/*
 * 基本介绍:
 *	
 * 返回值:
 *	在回调函数中正常返回__DIS_ERROR_SUCCESS__,如果在某个回调函数中当它执行完毕想要直接到某个回调函数可以
 *	返回__DISATH_ERROR_SUCCESS_GOTO_X__(X为数字),那么执行完毕后会直接执行到X的回调函数
 *	如果需要返回错误则使用__MAKE_DISATH_CUSTOM_ERROR__(数字)产生自己的错误代码,最大数量为__DISATH_MAX_CUSTOM_ERROR__
 *
 * 链接时注意:
 *
 * 辅助函数:
 *
 * 文件介绍:
 *	DISAthError.h:定义了DIS附加器的出错代码
 *	DISAthSteps.h:定义了回调函数的原型与名称
 *	DISAth.h:定义了重要的数据结构
 */

#include "DISAthError.h"

/*
 * 参数:
 *	pConfigure:DIS附加器配置结构指针
 */
__dword __INTERNAL_FUNC__ DISAthStep0(PDISATH_CONFIGURE pConfigure);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pConfigure:DIS附加器配置结构指针
 */
__dword __INTERNAL_FUNC__ DISAthStep1(PXFILE_ATTACH_INFO pXFileAttachInfo, PDISATH_CONFIGURE pConfigure);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pXFileNtSectionHeader:X文件所在PE节
 */
__dword __INTERNAL_FUNC__ DISAthStep2(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_SECTION_HEADER pXFileNtSectionHeader);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pTargetNtHeader:要附加的目标文件NT头
 */
__dword __INTERNAL_FUNC__ DISAthStep3(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pNewXFileSection:DIS所在X节节头
 */
__dword __INTERNAL_FUNC__ DISAthStep4(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_SECTION_HEADER pNewXFileSection);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	addrDISImageBaseInTarget:DIS在目标文件中的基地址
 *	ofDISOffsetByXSectionBody:DIS离X节节体的偏移
 */
__dword __INTERNAL_FUNC__ DISAthStep5(PXFILE_ATTACH_INFO pXFileAttachInfo, __address addrDISImageBaseInTarget, __offset ofDISOffsetByXSectionBody);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDIS:DIS的映射指针
 *	iDISSize:DIS的长度
 */
__dword __INTERNAL_FUNC__ DISAthStep6(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDIS:DIS的映射指针
 *	iDISSize:DIS的长度
 *	iDISSizeOfImage:DIS的映射长度
 *	ofDISOffsetByXSectionBody:DIS离X节体的偏移
 *	piXSectionSize:此参数本身是DIS的X节的长度,但是可以返回新的X节长度
 */
__dword __INTERNAL_FUNC__ DISAthStep7(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize, __integer iDISSizeOfImage, __offset ofDISOffsetByXSectionBody, __integer *piXSectionSize);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDIS:DIS的映射指针
 *	iDISSize:DIS的长度
 *	pXFileNtSectionHeader:X文件所在PE头
 *	pXSection:DIS的X节
 *	dwDNA:DIS的DNA
 *	ofDISConfigureRVA:DIS配置结构在目标中的RVA
 */
__dword __INTERNAL_FUNC__ DISAthStep8(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __integer iDISSize, PIMAGE_SECTION_HEADER pXFileNtSectionHeader, PXFILE_SECTION_HEADER pXSection, __dword dwDNA, __offset ofDISConfigureRVA);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pTargetNtHeader:目标文件的PE头
 */
__dword __INTERNAL_FUNC__ DISAthStep9(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDIS:DIS映射指针
 *	pDISInTarget:DIS在目标文件中的位置
 *	iDISSizeOfImage:DIS的映射长度
 */
__dword __INTERNAL_FUNC__ DISAthStep10(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDIS, __memory pDISInTarget, __integer iDISSizeOfImage);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 *	ofDISNewAddressTableRva:DIS自身新的引入表的RVA
 */
__dword __INTERNAL_FUNC__ DISAthStep11(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, __offset ofDISNewAddressTableRva);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 *	pReferenceDISImportTableAddress:DIS引入表保护引用结构
 */
__dword __INTERNAL_FUNC__ DISAthStep12(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceDISImportTableAddress);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 *	ofTargetNewAddressTableRva:目标文件自身新的引入表的RVA
 */
__dword __INTERNAL_FUNC__ DISAthStep13(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, __offset ofTargetNewAddressTableRva);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 *	pReferenceTargetImportTableAddress:目标文件引入表保护引用结构
 */
__dword __INTERNAL_FUNC__ DISAthStep14(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure, PREFERENCE_IMPORT_TABLE_ADDRESS pReferenceTargetImportTableAddress);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 */
__dword __INTERNAL_FUNC__ DISAthStep15(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pTargetNtHeader:目标文件的PE头
 */
__dword __INTERNAL_FUNC__ DISAthStep16(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_NT_HEADERS pTargetNtHeader);

/*
 * 参数:
 *	pXFileAttachInfo:X文件附加信息
 *	pDISInTarget:DIS在目标文件中的位置
 *	pDISConfigure:DIS的配置结构,在目标文件中
 */
__dword __INTERNAL_FUNC__ DISAthStep17(PXFILE_ATTACH_INFO pXFileAttachInfo, __memory pDISInTarget, PDIS_CONFIGURE pDISConfigure);

/*
 * 参数:
 *	pConfigure:DIS附加结构的指针
 */
__dword __INTERNAL_FUNC__ DISAthStep18(PDISATH_CONFIGURE pConfigure);
