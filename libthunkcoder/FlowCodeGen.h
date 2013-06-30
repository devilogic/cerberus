#if !defined(__FLOWCODEGEN_H__)
#define __FLOWCODEGEN_H__

typedef struct _FLOWCODER *PFLOWCODER;

typedef enum _FLOW_IF_TYPE
{
	FIT_IF = 0,
	FIT_ELSE_IF,
	FIT_ELSE
} FLOW_IF_TYPE;

typedef enum _FLOW_SWITCH_TYPE
{
	FST_SWITCH = 0,
	FST_CASE,
	FST_DEF
} FLOW_SWITCH_TYPE;

typedef enum _FLOW_TYPE
{
	FT_IF = 0,
	FT_SWITCH,
	FT_WHILE
} FLOW_TYPE;

// IF语句序列结构
typedef struct _FLOW_IF
{
	struct _FLOW_IF *pNext;//下一个IF节点
	PDUMMYCODE pDummyCode;//傀儡代码
	PFLOWCODER pInside;//内嵌流程

	FLOW_IF_TYPE Type;//IF类型
} FLOW_IF, *PFLOW_IF;

// WHILE语句序列结构
typedef struct _FLOW_WHILE
{
	PDUMMYCODE pDummyCode;//傀儡代码
	PFLOWCODER pInside;//内嵌流程
} FLOW_WHILE, *PFLOW_WHILE;

// SWITCH语句序列结构
typedef struct _FLOW_SWITCH
{
	struct _FLOW_SWITCH *pNext;//下一个节点
	PDUMMYCODE pDummyCode;//傀儡代码
	PFLOWCODER pInside;//内嵌流程

	FLOW_SWITCH_TYPE Type;//SWITCH类型
} FLOW_SWITCH, *PFLOW_SWITCH;

// 流程模板
typedef struct _FLOWCODER
{
	struct _FLOWCODER *pNext;//下一个流程
	
	FLOW_TYPE Type;//类型

	PFLOW_IF pIf;
	PFLOW_WHILE pWhile;
	PFLOW_SWITCH pSwitch;

} FLOWCODER;

#endif
