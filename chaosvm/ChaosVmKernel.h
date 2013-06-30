#if !defined(__CHAOSVM_KERNEL_H__)
#define __CHAOSVM_KERNEL_H__

#include "Common.h"
#include "ChaosVmp.h"
#include "ChaosVm.h"
#include "ChaosVmJmpTargetDataBase.h"
#include "ChaosVmCpuGlobalExportVariable.h"

#if defined(__cplusplus)
extern "C"
{
#endif

__void __INTERNAL_FUNC__ ChaosVmCpuInit(PCHAOSVM_CPU pCPU);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunToOffset(PCHAOSVM_CPU pCPU, __offset ofOffset);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunToAddress(PCHAOSVM_CPU pCPU, __dword Address);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunStepIn(PCHAOSVM_CPU pCPU);
CPU_STATUS __INTERNAL_FUNC__ ChaosVmCpuRunStepOver(PCHAOSVM_CPU pCPU);

__void * __INTERNAL_FUNC__ ChaosVmCpuGetUserContext(PCHAOSVM_CPU pCPU);
__void __INTERNAL_FUNC__ ChaosVmCpuSetUserContext(PCHAOSVM_CPU pCPU, __void *pUserContext);
__void __INTERNAL_FUNC__ ChaosVmCpuSetMmAccessRoutine(PCHAOSVM_CPU pCPU, FPMmReadRoutine pChaosVmMmRead, FPMmWriteRoutine pChaosVmMmWrite, \
													  FPMmCodeReadRoutine pChaosVmMmCodeRead, FPMmReadDataPartRoutine pChaosVmMmReadDataPartRoutine, \
													  FPMmReadDispPartRoutine pChaosVmMmReadDispPartRoutine);
__void __INTERNAL_FUNC__ ChaosVmCpuBuildModrmSibRoutine(PCHAOSVM_CPU pCPU, FPCpuBuildModrmRoutine pBuildModrm, FPCpuBuildSibRoutine pBuildSib);
__void __INTERNAL_FUNC__ ChaosVmCpuSetErrorOutputRoutine(PCHAOSVM_CPU pCPU, FPCpuErrorOutputRoutine pChaosVmErrorOutput);
__void __INTERNAL_FUNC__ ChaosVmCpuSetHook(PCHAOSVM_CPU pCPU, __byte bType, __void *pChaosVmHookRoutine);
__dword __INTERNAL_FUNC__ ChaosVmCpuGetInstructionType(PCHAOSVM_CPU pCPU);
PINSTRUCTION_TYPE_INFO __INTERNAL_FUNC__ ChaosVmCpuGetInstructionTypeInfo(PCHAOSVM_CPU pCPU);
__void __INTERNAL_FUNC__ ChaosVmCpuSetInterruptHandler(PCHAOSVM_CPU pCPU, FPCpuInterruptHandleRoutine pChaosVmInterruptHandler);

/*
 * Í¨ÓÃ¼Ä´æÆ÷
 */
__dword __INTERNAL_FUNC__ ChaosVmCpuGR32Get(PCHAOSVM_CPU pCPU, __byte bGR32Index);
__void __INTERNAL_FUNC__ ChaosVmCpuGR32Set(PCHAOSVM_CPU pCPU, __byte bGR32Index, __dword dwNewValue);

/*
 * ¶Î¼Ä´æÆ÷
 */
__word __INTERNAL_FUNC__ ChaosVmCpuSRGet(PCHAOSVM_CPU pCPU, __byte bSegmentIndex);
__void __INTERNAL_FUNC__ ChaosVmCpuSRSet(PCHAOSVM_CPU pCPU, __byte bSegmentIndex, __word wNewValue);

/*
 * EIP¼Ä´æÆ÷
 */
__address __INTERNAL_FUNC__ ChaosVmCpuEIPGet(PCHAOSVM_CPU pCPU);
__void __INTERNAL_FUNC__ ChaosVmCpuEIPSet(PCHAOSVM_CPU pCPU, __address addrNewAddress);

/*
 * ±êÖ¾¼Ä´æÆ÷
 */
__byte __INTERNAL_FUNC__ ChaosVmCpuEFlagGet(PCHAOSVM_CPU pCPU, __byte bFlagIndex);
__void __INTERNAL_FUNC__ ChaosVmCpuEFlagSet(PCHAOSVM_CPU pCPU, __byte bFlagIndex, __byte bNewValue);

#if defined(__cplusplus)
}
#endif

#endif
