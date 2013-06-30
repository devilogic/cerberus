/*
 * XFILE文件结构是一种对于添加新节的解决方案,等于在新节中自己维护了一个类似PE结构的文件结构
 * 此结构分为三个部分,一个是节头部分'XFILE_HEADER'类似PE头中的DOS头+NT头结构,接下来是各个节
 * 表部分'XFILE_SECTION_HEADER'此结构类似PE节表头部分,这个部分有1-N个.最后的部分是节内容部分
 * 这个部分用来记录不同类似数据,目前节部分可以存储三种类型数据,一种是PE文件数据,一种是XFILE
 * 本身的类型,此结构可以拥有子XFILE,最后一种是用户自定义的数据.
 *
 * 需要注意的是,每个PE文件中只可以有一个X文件节,并且此节一定要处于PE文件的末尾
 */

#if !defined(__XFILE_FORMAT_H__)
#define __XFILE_FORMAT_H__

#include "Common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

// X文件标志
#define __XFILE_SIGN__										0x83121004
#define __XFILE_SUB_SIGN__									0x83120410
// 版本号
#define __XFILE_VERSION__									0x10000000
// X格式文件节名最长长度
#define __XFILE_SECTION_NAME_SIZE__							8

// 确定是XFILE文件
#define __IS_XFILE__(x)										(((x) == __XFILE_SIGN__) || ((x) == __XFILE_SUB_SIGN__))

// X文件的格式头
typedef struct _XFILE_HEADER {
	__dword dwSign;//X文件的标志
	__dword dwVersion;//X文件格式的版本
	__dword dwSectionNumber;//节数量
	__dword dwMaxSectionNumber;//最大的节数量
	__dword dwXFileSize;//整个X文件节经过对齐的长度
	__dword dwAlignment;//节的对齐力度
	__dword dwSizeOfAllHeaders;//所有头的总长度并根据粒度对齐

	union {
		__dword dwXFileSectionHdrFileOffset;//X文件节头的文件偏移,用于子XFile
		__dword dwXFileNtSectionHdrFileOffset;//X文件NT头的文件偏移
	};

	union {
		__dword dwXFileSectionHdrMemoryOffset;//X文件节头的内存偏移,用于子XFile
		__dword dwXFileNtSectionHdrMemoryOffset;//X文件NT头的内存偏移
	};
} XFILE_HEADER, *PXFILE_HEADER;

// X文件节属性
#define __XFILE_SECTION_CHARACTERISTICS_USED__						0x01//表明此节正在使用中

#define __XFILE_SECTION_CHARACTERISTICS_PE__						0x8000000//表明此节中的数据是一个PE文件
#define __XFILE_SECTION_CHARACTERISTICS_PE_FILE_ALIGN__				0x02//如果过是一个PE文件则使用文件对齐,如果未设置则使用内存对齐

#define __XFILE_SECTION_CHARACTERISTICS_X__							0x80000000//表明此节的数据是一个XFILE文件

// X文件的节头
typedef struct _XFILE_SECTION_HEADER {
	__char szSectionName[__XFILE_SECTION_NAME_SIZE__];//节名字
	__dword dwCharacteristics;//节属性
	__dword dwDNA;//此节的唯一标识码
	__dword dwPointerToRawData;//文件偏移
	__dword dwVirtualAddress;//内存偏移
	__dword dwOffsetByXFile;//离XFile的偏移
	__dword dwSizeOfSection;//映射大小

	union {
		__dword dwEx1;
		__offset ofMemImageBaseOffset;//如果此节为PE文件并且是通过内存对齐的,则此自动表明离节头的偏移
	};

	union {
		__dword dwEx2;
		__dword dwCustomDataRVA;//此字段表明X节内容所自定义的一些数据离目标文件的RVA
	};
} XFILE_SECTION_HEADER, *PXFILE_SECTION_HEADER;

// X文件附加记录结构
typedef struct _XFILE_ATTACH_INFO {
	__bool bUsed;//是否正在被使用
	__bool bResetCheckSum;//重新设置校验和
	__bool bSetAllSectionCanWrite;//设置所有节可写
	__bool bRandomAllSectionName;//随机设置所有节的名字
	__bool bCloseNX;//关闭数据执行保护
	__bool bCloseRandAddressMap;//关闭随机地址化映射
	__bool bWillDelDataDirectoryIndexs[0x10];//删除数据目录的索引
	__bool bCompatibility;//提高兼容性
	__bool bKeepSameOrigImpLib;//保留原始引入表的一些值,以提高兼容性

	__char *szSectionName;//DIS所属的X文件添加到目标文件的节名
	__char *szXSectionName;//DIS所属的X节添加到X文件的节名
	__dword dwDNA;//DIS的DNA

	//////////////////////////////////////////////////////////////////////////
	// 目标文件相关
	union {
		__tchar *szTargetFilePath;//目标文件路径
		__dword dwTargetId;//资源ID
	};
	__dword dwResourceDecodeKey;//如果资源进行过加密,这里是解密所需的Key
	__tchar *szResourceType;//如果是以资源引出那么资源的类型
	__memory pMem;//目标文件的映射指针,如果bUsed = TRUE,那么表示pMem是有效的文件映射
	__integer iFileSize;//当前文件的大小
	__integer iOrigFileSize;//最原本的文件大小
	__bool bImageBaseRelocate;//基地址要重映射
	IMAGE_NT_HEADERS OrigTargetNtHeader;//原始目标PE头
	__memory pOrigImportDescriptor;//原始引入表描述符
	__memory pDummyImportTable;//傀儡引入表
	__integer iDummyImportTableSize;//傀儡引入表所占用的空间

	//////////////////////////////////////////////////////////////////////////
	// 末尾数据相关
	__bool bKeepTailData;//保持末尾数据
	__bool bTailDataIsSecurityDataDirectory;//末尾数据是证书节
	__memory pTailData;//末尾数据
	__offset ofOrigTailDataRawOffset;//末尾数据的文件偏移
	__offset ofSecurityDataDirectoryRawOffsetByTailData;//安全证书节离末尾数据的文件偏移
	__integer iTailDataSize;//末尾数据长度
} XFILE_ATTACH_INFO, *PXFILE_ATTACH_INFO;

/*
 * 以下函数在附加器中使用,所有偏移使用文件偏移
 */
// 预先获取新X节的节头
__bool __API__ XFilePredictNewSectionHeader(__memory pMem, PXFILE_SECTION_HEADER pNewSectionHeader);
// 获取一个X文件的第一个X节在PE文件中
PXFILE_SECTION_HEADER __API__ XFileGetFirstSectionInPEFile(__memory pMem);
// 获取一个X文件的最后一个X节在PE文件中
PXFILE_SECTION_HEADER __API__ XFileGetTailSectionInPEFile(__memory pMem);
// 确定一个文件是否已经存在X文件
PIMAGE_SECTION_HEADER __API__ XFileExistXFileInPEFile(__memory pMem);
// 计算一个X文件的头的长度
__integer __API__ XFileCalcXFileHeaderSize(__dword dwMaxSectionNumber);
// 自动填充X文件附加结构
__bool __API__ XFileAttachInfoInit(PXFILE_ATTACH_INFO pXFileAttachInfo);
// 增加X文件到一个PE文件
PIMAGE_SECTION_HEADER __API__ XFileAddXFileToPEFile(PXFILE_ATTACH_INFO pXFileAttachInfo, __integer iSectionSize, __dword dwMaxSectionNumber);
// 增加X文件到一个X节
PXFILE_HEADER __API__ XFileAddXFileToXFileSection(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_SECTION_HEADER pXFileSectionHeader, __integer iSectionSize, __dword dwMaxSectionNumber);
// 添加X节通过X文件所在NT节,这个是添加根X节,大小不进行限制
PXFILE_SECTION_HEADER __API__ XFileAddXFileSectionByNtSectionHeader(PXFILE_ATTACH_INFO pXFileAttachInfo, PIMAGE_SECTION_HEADER pXFileNtSectionHeader, __integer iSectionSize, __dword dwCharacteristics, __dword dwEx1, __dword dwEx2);
// 添加X节通过X文件
PXFILE_SECTION_HEADER __API__ XFileAddXFileSectionByXFileHeader(PXFILE_ATTACH_INFO pXFileAttachInfo, PXFILE_HEADER pXFileHeader, __integer iSectionSize, __dword dwCharacteristics, __dword dwEx1, __dword dwEx2);
// 释放目标
__void __API__ XFileReleaseXFileAttach(PXFILE_ATTACH_INFO pXFileAttachInfo);

/*
 * 以下函数绝大部分情况下是在加载器中使用
 */
// 判断一个偏移是否在某个节内
__bool __API__ XFileInThisXFileSection(PXFILE_SECTION_HEADER pSectH, __offset ofOffset, __bool bRva);
// 从一个偏移获取这个X节头
PXFILE_SECTION_HEADER __API__ XFileGetXFileSectionHeaderByOffset(PXFILE_HEADER pXFileHeader, __offset ofOffset, __bool bRva);
// 从一个DNA获取这个X节头
PXFILE_SECTION_HEADER __API__ XFileGetXFileSectionHeaderByDNA(__memory pMem, PXFILE_HEADER pXFileHeader, __dword dwDNA, __bool bFile, PXFILE_SECTION_HEADER *pXFatherSectionHdrPoint);

#if defined(__cplusplus)
}
#endif

#endif
