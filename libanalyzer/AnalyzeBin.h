#if !defined(__ANALYZEBIN_H__)
#define __ANALYZEBIN_H__

/*
 *
 * !注:以下方法对使用汇编器直接编译的程序,识别稳定较低
 * 此文件为分析函数帧的代码
 * 鉴别单个函数帧流程:
 * 1)从当前位置开始进行反汇编
 * 2)记录所有跳转流程指令
 * 3)遇到ret或者retn指令后,回溯整个跳转流程链表
 * 4)如果找到jcc则判断是否跳转后的地址是否大于当前的指令地址
 * 5-1)大于,则跳转到流程1,进入预分析结尾流程
 * 5-2)无大于的情况,此函数分析完毕,返回
 * 把以上函数类型成为A类型
 * 预分析结尾:
 * 这里鉴别函数帧也可能造成不稳定,有些函数在ret之后还有一些指令
 * 在这些指令之后必定有一个JMP跳转到最后一个ret或者之前
 * 利用此来进行预分析结尾
 * 这里出现3种情况
 * 1)找到上述那个最后的JMP则将此视为结尾
 * 2)如果找到nop视为结尾(用户可以指定此选项,默认存在)
 * 3)如果找到int3视为结尾(用户可以指定此选项,默认存在)
 * 4)如果找到0视为结尾(用户可以指定此选项,默认存在)
 *
 * 
 * 分析出整个文件的函数帧流程:
 * 1)从PE文件中取出入口点
 * 2)从这个位置开始反汇编进行分析,直到鉴别出入口函数
 * 3)从入口函数的跳转流程链表中,依次寻找CALL到其他函数的跳转指令
 * 4)找打一个函数入口并开始递归这个过程
 * 5)直到这个过程鉴别完毕
 *
 * 除了从一个函数鉴别出所有函数外,在整个函数中还存在着没有通过跳转指令
 * 鉴别出的函数,大部分的原因是因为动态跳转
 * 这种函数定义为B,B函数类型,(不准备采取)
 * 识别B函数的流程
 * 1)遍历整个节表,将拥有执行权限的节全部找出来
 * 2)将A函数的链表使用函数头内存地址进行从低到高的排序
 * 3)通过A链表与这些筛选出的代码节做对比,重点是在A链表中没有涉及到的地方
 * 4)在这些内存进行寻找,寻找方案有两套
 * 5-1)通过函数特征头来鉴别(收集各种编译器与编译选项造成的函数头),找到后进入单个函数帧鉴别流程
 *     在这里的特征库筛选是通过,通过预判断此程序是什么编译编译而成而设定的,如果没有鉴别出是何种编译器
 *     则依次遍历特征库
 * 5-2)通过寻找NOP,CC等明显的编译器造成的对齐标记来区分函数块
 * 6)区分出的代码块做单函数帧鉴别,如果在反汇编的过程中,遇到反汇编失败(无效的IA32编码),则将此作为
 *   区块进行处理
 *
 *
 * 分析函数链
 * 第一遍分析
 * 1)依次对所有指令进行分析,设定指令是否可以交换,并进行初步HOOK分析刺探,将通过偏移的
 *   的跳转指令进行识别,并鉴别HOOK成功率,并填充这条指令对标志寄存器的影响和通用寄存器的影响
 * 2)通过IsProcEnd(上述已经阐述了其算法)函数确立入口函数的长度
 * 3)再次遍历入口函数,通过分析入口函数的CALL指令,分析出其他函数
 * 4)循环1,2过程直到把映射中所有的函数都鉴别出来
 * 5)进行链表排序(地址由低到高)
 * 6)将链表与映射内存由高到低依次进行对比,找出未找到的代码块,并使用,1,2方法进行鉴别
 *   将无法分析的代码识为数据
 *
 * 第二遍分析
 * 1)遍历函数链
 * 2)在识别过程中,鉴别出一个函数开辟的局部变量所需的空间,具体监视sub esp, XXX指令
 * 3)在遍历过程中如果发现有指令直接对全局变量进行引用,记录其访问地址
 * 4)如果遇到跳转指令,则设置它目标地址指令的跳转引用链表
 * 
 * 第三遍分析
 * 1)遍历函数链
 * 2)找到所有动态跳转指令,并对它进行反馈分析,直到找出动态跳转寄存器值的合成结果,并进行运算
 *   这里反馈的结束算法是
 *   查看当前跳转指令,是否由引用指令
 *   如果有则遍历这个引用链
 *   如果没有则向上分析1条指令,如果没有存在可以影响寄存器的mov,lea指令,则直接视此指令为不可
 *   HOOK的指令,如果动态跳转出现使用两个寄存器做内存跳转的直接视为不可HOOK的指令
 *
 * B类型函数将不采用
 * 直接将B段视为可使用部分(函数间隙的使用),有可能会对IAT代理表造成破坏,以下是IAT代理跳转表的描述
 * 分析IAT表跳转结构
 * 有些编译器在执行IAT表的时候,会将跳入到IAT的部分单独使用一个代码块来替代
 * 而在本代码体使用call dword ptr [stub_iat_address]来替代
 * 跳转表多数为jmp dword ptr [iat_address]
 * iat_address指向真正的API地址
 *
 */
#include "Common.h"
#include "logic.h"
#include "udis86.h"
#include "ValidAddress.h"
#include "CpuContext.h"
#include "ImportTableReference.h"
#include "x86Instruction.h"
#include "Proecdure.h"

#if defined(__cplusplus)
extern "C"
{
#endif

// 分析配置结构
#define __DEF_VALID_ADDR_LEVEL__				CHK_IN_USER_MEM
#define __DEF_CODE_MIX_SIZE__					6
typedef struct _ANALYZE_CONFIGURE {
	__bool bEnableDiscoveryUnknowZoon;//是否开启对未知区域性的探索
	__bool bNopIsNotEnd;//分析时不将NOP指令视为函数结束
	__bool bZeroIsNotEnd;//分析时不将0字符视为函数结束
	__bool bInt3IsNotEnd;//分析时不将CC指令视为函数结束
	CHECK_VALID_ADDR_LEVEL ValidAddressLevel;//用户指定的有效地址级别
	__byte bCodeMixSize;//最小的代码长度,低于此长度,直接视为数据
	__bool bDisInvalidOpcodeIsData;//关闭如果无效编码则此区域直接视为数据
	__bool bEnableImportTableReference;//开启引入表引用分析
	__address addrFromHereStartAnalyze;//指定入口点进行分析
} ANALYZE_CONFIGURE, *PANALYZE_CONFIGURE;

/*
 * 函数指针
 */
typedef __integer (__API__ *FPRva2Raw)(__memory pMem, __integer iRva);
typedef __integer (__API__ *FPRaw2Rva)(__memory pMem, __integer iRaw);
typedef __void * (__API__ *FPGetCodeSectionHeader)(__memory pMem);
typedef __void * (__API__ *FPGetNtHeader)(__memory pMem);

// 所需信息结构
typedef struct _ANALYZE_BASIC_INFO {
	__memory pMem;//文件头指针
	__memory pCodeSeg;//指向代码段区域
	__memory pTailData;//指向末尾多余数据

	__address ImageBase;//加载基地址
	__address addrCodeSegMemoryAddress;//代码段内存地址

	__integer iBinSize;//文件长度
	__integer iCodeSegSize;//代码区长度
	__integer iTailDataSize;//末尾数据长度
	__integer iEntryRva;//末尾数据长度

	FPRva2Raw pRva2Raw;
	FPRaw2Rva pRaw2Rva;
	FPGetCodeSectionHeader pGetCodeSectionHeader;
	FPGetNtHeader pGetNtHeader;
} ANALYZE_BASIC_INFO, *PANALYZE_BASIC_INFO;

// 程序结构
typedef struct _PROGRAM {
	__memory pMem;//文件头指针
	__memory pCodeSeg;//指向代码段区域
	__memory pTailData;//指向末尾多余数据

	__address ImageBase;//加载基地址
	__address addrCodeSegMemoryAddress;//代码段内存地址

	__integer iBinSize;//处于莫问数据后的长度
	__integer iCodeSegSize;//代码区长度
	__integer iTailDataSize;//末尾数据长度
	__integer iEntryRva;//末尾数据长度

	PPROCEDURE pEntryProcedure;//入口函数指针
	PPROCEDURE pProcedureList;//函数链表,这里需要释放内存

	__integer iProcCount;//函数计数
	__integer iAllBlockCount;//所有的块计数
	__integer iInlineProcCount;//内联函数数量

	PIMPORT_TABLE_REFERENCE pImportTableReference;//引入表引用

	ANALYZE_CONFIGURE AnalyzeConfigure;//分析配置
} PROGRAM, *PPROGRAM;

#define __GetInstructionJmpParents__(pInstJmp)						((PX86INSTRUCTION)((pInstJmp)->pParents))
#define __GetInstructionParents__(pInstruction)						((PPROCEDURE)((pInstruction)->pParents))
#define __GetProcedureParents__(pProcedure)							((PPROGRAM)((pProcedure)->pParents))
#define __GetProgramFromInstruction__(pInstruction)					(__GetProcedureParents__(__GetInstructionParents__((pInstruction))))
#define __GetValidAddressLevelFromInstruction__(pInstruction)		(__GetProgramFromInstruction__((pInstruction))->AnalyzeConfigure.ValidAddressLevel)
#define __GetValidAddressLevelFromInstructionJmp__(pInstJmp)		(__GetValidAddressLevelFromInstruction__(__GetInstructionJmpParents__((pInstJmp))))

__void __API__ ReleaseProgram(PPROGRAM *pProgramPoint);
PPROGRAM __API__ AnalyzeProgram(PANALYZE_CONFIGURE pAnalyzeConfigure, PANALYZE_BASIC_INFO pAnalyzeBasicInfo);
PX86INSTRUCTION __API__ FindInstructionByAddress(PPROGRAM pProgram, __address addrInstruction);
PPROCEDURE __API__ FindProcedureByAddress(PPROGRAM pProgram, __address addrProcedure);
PPROCEDURE __API__ FindProcedureByInsideAddress(PPROGRAM pProgram, __address addrAddress);

#if defined(__cplusplus)
}
#endif

#endif

