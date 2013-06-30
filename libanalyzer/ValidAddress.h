// 有效地址校验值
typedef enum _VALID_ADDR {
	INVALID_ADDRESS	= 0,
	IN_USER_MEM,
	IN_IMAGE_MEM,
	IN_SEC_MEM,
	IN_CAN_EXEC
} VALID_ADDR;

typedef enum _CHECK_VALID_ADDR_LEVEL {
	CHK_IN_USER_MEM = 1,
	CHK_IN_IMAGE_MEM,
	CHK_IN_SEC_MEM,
	CHK_IN_CAN_EXEC
} CHECK_VALID_ADDR_LEVEL;

#define __IsValidAddressLevel__(Result, Level)		((Result) == (Level))
#define __IsInvalidAddressLevel__(Result, Level)	((Result) < (Level))