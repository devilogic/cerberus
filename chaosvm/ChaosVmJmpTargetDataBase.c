#include "ChaosVmJmpTargetDataBase.h"
#include "logic.h"

// 记录了每个保护函数的跳转目标地址结构
PHASHTREE g_pJmpTargetTableList[__MAX_VMP_PROCEDURE__];

/*
 * 参数:
 *	pSymbolValue:符号的值
 *
 * 释放符号节点的回调函数,此函数在logic.h中的hashtree中被回调使用
 */
__void __INTERNAL_FUNC__ JmpTargetHashNodeValueFreeCallBack(__memory pSymbolValue) {
	if (pSymbolValue)
		__logic_delete__(pSymbolValue);
}

/*
 * 参数:
 *	iIndex:要保护函数的索引号
 *
 * 初始化跳转目标指令的哈希表
 */
#define __DEF_JMPTARGET_ROOT__			5
__void __INTERNAL_FUNC__ InitJmpTargetDataBaseTable(__integer iIndex) {
	PHASHTREE *pJmpTargetTablePoint = &(g_pJmpTargetTableList[iIndex]);
	(*pJmpTargetTablePoint) = init_hashtree(__DEF_JMPTARGET_ROOT__, JmpTargetHashNodeValueFreeCallBack);
}

/*
 * 参数:
 *	iIndex:要保护函数的索引号
 *	addrAddress:要查询的地址
 *
 * 查询一个地址是否是跳转目标地址,如果是返回这个跳转目标地址的指令结构(PCHAOSVMP_JMPTARGET_INST),如果不是则返回NULL
 */
PCHAOSVMP_JMPTARGET_INST __INTERNAL_FUNC__ QueryJmpTargetInstFromTable(__integer iIndex, __address addrAddress) {
	PHASHTREE pJmpTargetTable = g_pJmpTargetTableList[iIndex];
	PHASHTREE_NODE pHashNode = query_node_hashtree(pJmpTargetTable, (__byte *)&addrAddress, sizeof(__address));
	if (pHashNode == NULL) return NULL;
	return (PCHAOSVMP_JMPTARGET_INST)(pHashNode->value);
}

/*
 * 参数:
 *	iIndex:要保护函数的索引号
 *	addrAddress:要查询的地址
 *	pJmpTargetInst:跳转目标地址结构
 *
 * 增加一个跳转目标指令到跳转目标地址结构中
 */
PCHAOSVMP_JMPTARGET_INST __INTERNAL_FUNC__ AddJmpTargetInstToTable(__integer iIndex, __address addrAddress,  PCHAOSVMP_JMPTARGET_INST pJmpTargetInst) {
	PHASHTREE pJmpTargetTable = g_pJmpTargetTableList[iIndex];
	PHASHTREE_NODE pHashNode = NULL;
	pHashNode = add_node_hashtree(pJmpTargetTable, (__byte *)&addrAddress, sizeof(__address), (__memory)pJmpTargetInst);
	if (pHashNode == NULL)
		return NULL;
	return pJmpTargetInst;
}

/*
 * 参数:
 *	iIndex:要保护函数的索引号
 *
 * 销毁一个跳转目标数据库
 */
__void __INTERNAL_FUNC__ DestoryJmpTargetTable(__integer iIndex){
	PHASHTREE pJmpTargetTable = g_pJmpTargetTableList[iIndex];
	if (pJmpTargetTable)
		free_hashtree(&pJmpTargetTable);
}