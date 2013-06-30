/*
 * 基本介绍:
 *	这里的函数必须外部提供实现代码,在7以后重定位完成可以使用公共变量,在8以后自身引入表解密完成可以使用API
 *	0号步骤为,流程代码所有都自己定义,所以不需要返回代码
 *	使用公共变量简称:G,使用API简称:I
 *
 * 返回值:
 *	在回调函数中正常返回__DIS_ERROR_SUCCESS__,如果在某个回调函数中当它执行完毕想要直接到某个回调函数可以
 *	返回__DISATH_ERROR_SUCCESS_GOTO__(X为数字),那么执行完毕后会直接执行到X的回调函数,如果返回__DIS_ERROR_SUCCESS_GOTO_ORIG_ENTRY__
 *	则直接到第11号回调函数,如果需要返回错误则使用__MAKE_DIS_CUSTOM_ERROR__(数字)产生自己的错误代码,最大数量为__DIS_MAX_CUSTOM_ERROR__
 *
 * 链接时注意:
 *	链接时请将DISEntry,DISEntryInDll两个函数,g_DISConfigure一个全局变量引出,libdisath静态库将会做处理
 *
 * 辅助函数:
 *	DISAddThunkCodeStub,是解密引出表时,如果为某个API设定了保护,那么会调用此函数产生自己的API Invoke Stub.如果要使用默认函数,请将此函数
 *	返回NULL值
 *
 * 文件介绍:
 *	DISError.h:定义了DIS出错的值
 *	DISKernel.h:定义了关键的数据结构与引出函数原型
 *	DISSteps.h:定义了回调函数原型与名称
 */

#include "DISError.h"

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,则此项为0
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *
 * 特性:
 *	NG,NI
 */
__void __INTERNAL_FUNC__ DISStep0(__dword hModule, __dword ul_reason_for_call, __void *lpReserved);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep1(__dword hModule, __dword ul_reason_for_call, __void *lpReserved);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *	pNtSectionHeader:是宿主映射的NT头
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep2(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *	pNtSectionHeader:是宿主映射的NT头
 *	pXFileHeader:DIS所在的X文件
 *	pOutMyDNA:输出当前DIS的DNA
 *
 * 介绍:
 *	此函数是比较重要的函数,在此回调函数中要返回当前DIS的DNA
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep3(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, __dword *pOutMyDNA);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *	pNtSectionHeader:是宿主映射的NT头
 *	pXFileHeader:DIS所在的X文件
 *	pXFileSectionHeader:DIS所在的X节
 *	pXFileFatherSectionHeader:如果DIS拥有父DIS节,则此为有效值,否则则为NULL,如果此值有效则当前DIS不直接在宿主体内
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep4(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *	pNtSectionHeader:是宿主映射的NT头
 *	pXFileHeader:DIS所在的X文件
 *	pXFileSectionHeader:DIS所在的X节
 *	pXFileFatherSectionHeader:如果DIS拥有父DIS节,则此为有效值,否则则为NULL,如果此值有效则当前DIS不直接在宿主体内
 *	pDISConfigure:DIS的配置结构
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep5(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure);

/*
 * 参数:
 *	hModule:当前宿主映射的基地址,如果是EXE,当前值有效
 *	ul_reason_for_call:如果宿主映射是DLL,那么此参数是挂载的原因,如果是EXE永远为0
 *	lpReserved:如果宿主映射是DLL,那么值为dllmain第三个参数,如果是EXE永远为NULL
 *	pNtSectionHeader:是宿主映射的NT头
 *	pXFileHeader:DIS所在的X文件
 *	pXFileSectionHeader:DIS所在的X节
 *	pXFileFatherSectionHeader:如果DIS拥有父DIS节,则此为有效值,否则则为NULL,如果此值有效则当前DIS不直接在宿主体内
 *	pDISConfigure:DIS的配置结构
 *	pDISImageBase:DIS当前的映射基地址
 *	addrDISOrigImageBase:DIS的映射的原基地址
 *
 * 特性:
 *	NG,NI
 */
__dword __INTERNAL_FUNC__ DISStep6(__dword hModule, __dword ul_reason_for_call, __void *lpReserved, PIMAGE_SECTION_HEADER pNtSectionHeader, PXFILE_HEADER pXFileHeader, PXFILE_SECTION_HEADER pXFileSectionHeader, PXFILE_SECTION_HEADER pXFileFatherSectionHeader, PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase);

/*
 * 参数:
 *	pDISConfigure:DIS的配置结构
 *	pDISImageBase:DIS当前的映射基地址
 *	addrDISOrigImageBase:DIS的映射的原基地址
 *
 * 特性:
 *	G,NI
 */
__dword __INTERNAL_FUNC__ DISStep7(PDIS_CONFIGURE pDISConfigure, __memory pDISImageBase, __address addrDISOrigImageBase);

/*
 * 特性:
 *	G,I
 */
__dword __INTERNAL_FUNC__ DISStep8();

/*
 * 参数:
 *	pTargetImageBase:DIS所在的目标文件的基地址
 *	pDISImageBase:DIS当前的映射基地址
 *	addrDISOrigImageBase:DIS的映射的原基地址
 *
 * 特性:
 *	G,I
 */
__dword __INTERNAL_FUNC__ DISStep9(__memory pTargetImageBase);

/*
 * 特性:
 *	G,I
 */
__dword __INTERNAL_FUNC__ DISStep10();

/*
 * 参数:
 *	addrOrigEntryAddress:原始入口点地址
 *
 * 特性:
 *	G,I
 */
__dword __INTERNAL_FUNC__ DISStep11(__address addrOrigEntryAddress);
