#if !defined(__CHAOSVM_CPU_STATUS_H__)
#define __CHAOSVM_CPU_STATUS_H__

#include "Common.h"

// 成功类型的返回码,将使CPU继续运行,错误类型的返回码,将导致CPU中止运行
typedef __dword CPU_STATUS;

#define __CPU_STATUS_SUCCESS__(Status)				(((__sdword)(Status)) >= 0 )//是否执行成功

// 判断是否发生中断
#define __CPU_IS_INTERRUPT_OCCUR__(pCPU)			(1 == (pCPU)->bIsInterruptOccur)
#define __CPU_SET_INTERRUPT_OCCUR__(pCPU)			((pCPU)->bIsInterruptOccur = 1)

// 退出
#define __CPU_STATUS_IMMEDIATELY_EXIT__				(0x10000000)
#define __CPU_STATUS_IS_SUCCESS_EXIT__(Status)		((((__dword)(Status)) >= 0x10000000)&& (((__dword)(Status)) < 0x20000000))

// 上条指令有触发中断,但中断处理成功
#define __CPU_STATUS_INTERRRUPT_HANDLE_SUCCESS__	10

// 指令执行成功
#define __CPU_STATUS_EXECUTE_SUCCESS__				0

// 设置错误返回码类型为"中断"
#define __CPU_STATUS_INTERRRUPT_OCCUR__				(0x50000100)

// GP类异常的返回值
//__CPU_STATUS_MM_INVALID_ADDRESS__
//__CPU_STATUS_MM_INVALID_ADDRESS_2__

// UD类异常的返回值
#define __CPU_STATUS_INVALID_OPCODE__				__CPU_STATUS_INTERRRUPT_OCCUR__
// DE类异常的返回值
#define __CPU_STATUS_DIVIDE_ERROR__					__CPU_STATUS_INTERRRUPT_OCCUR__
// BP异常的返回值
#define __CPU_STATUS_BREAK_POINT__					__CPU_STATUS_INTERRRUPT_OCCUR__

// 上条指令有触发中断,中断处理不成功
#define __CPU_STATUS_INTERRRUPT_UNHANDLE__			(0x80000001)
// 遇到未识别定义的机器码
#define __CPU_STATUS_UNIMPLEMENT_OPCODE__			(0x80000002)
// 遇到不完整的机器码
#define __CPU_STATUS_INCOMPLETE_OPCODE__	        (0x80000004)
// MODRM位解析时出错
#define __CPU_STATUS_MODRM_DATA_LENGTH_INCORRECT__  (0x80000103)

#define __CPU_STATUS_IGNORE__                       (0x80000303)

// 内存接口使用
#define __CPU_STATUS_MM_ACCESS_SUCCESS__			__CPU_STATUS_EXECUTE_SUCCESS__
#define __CPU_STATUS_MM_INVALID_ADDRESS__			(0xC0000001)
#define __CPU_STATUS_MM_BAD_PRIVILEGE__				(0xC0000002)
#define __CPU_STATUS_MM_INVALID_ADDRESS_2__			(0xC0000003)

// HOOK函数所使用的返回值
// 继续执行正常流程
#define __CPU_STATUS_HOOK_NOT_HANDLE__				(0x60000003)
// 跳过当前指令
#define __CPU_STATUS_HOOK_HANDLE__				    (0x60000004)
// 退出
#define __CPU_STATUS_HOOK_STOP_CPU__				(0x60000001)

#endif
