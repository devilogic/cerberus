// 执行成功
#define __DIS_ERROR_SUCCESS__					0

// 跳转流程
#define __DIS_ERROR_SUCCESS_GOTO__											0x70000000
#define __DIS_ERROR_SUCCESS_GOTO_0__										__DIS_ERROR_SUCCESS_GOTO__ + 0
#define __DIS_ERROR_SUCCESS_GOTO_1__										__DIS_ERROR_SUCCESS_GOTO__ + 1
#define __DIS_ERROR_SUCCESS_GOTO_2__										__DIS_ERROR_SUCCESS_GOTO__ + 2
#define __DIS_ERROR_SUCCESS_GOTO_3__										__DIS_ERROR_SUCCESS_GOTO__ + 3
#define __DIS_ERROR_SUCCESS_GOTO_4__										__DIS_ERROR_SUCCESS_GOTO__ + 4
#define __DIS_ERROR_SUCCESS_GOTO_5__										__DIS_ERROR_SUCCESS_GOTO__ + 5
#define __DIS_ERROR_SUCCESS_GOTO_6__										__DIS_ERROR_SUCCESS_GOTO__ + 6
#define __DIS_ERROR_SUCCESS_GOTO_7__										__DIS_ERROR_SUCCESS_GOTO__ + 7
#define __DIS_ERROR_SUCCESS_GOTO_8__										__DIS_ERROR_SUCCESS_GOTO__ + 8
#define __DIS_ERROR_SUCCESS_GOTO_9__										__DIS_ERROR_SUCCESS_GOTO__ + 9
#define __DIS_ERROR_SUCCESS_GOTO_A__										__DIS_ERROR_SUCCESS_GOTO__ + 0xA
#define __DIS_ERROR_SUCCESS_GOTO_B__										__DIS_ERROR_SUCCESS_GOTO__ + 0xB
#define __DIS_ERROR_SUCCESS_GOTO_ORIG_ENTRY__								__DIS_ERROR_SUCCESS_GOTO_B__

// 执行出错
#define __DIS_ERROR_ERROR__													0x80000000
#define __DIS_ERROR_CUSTOM_ERROR__											(__DIS_ERROR_ERROR__ | 0x0100)

// 最大的DIS自定义错误
#define __DIS_MAX_CUSTOM_ERROR__											0xFF

// 产生自己的错误
#define __MAKE_DIS_CUSTOM_ERROR__(x)										(__DIS_ERROR_CUSTOM_ERROR__ + (x))

// 测试是否成功
#define __DIS_SUCCESS__(x)													((x & __DIS_ERROR_ERROR__) != __DIS_ERROR_ERROR__)
