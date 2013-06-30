#include "AssemblerSymbolTable.h"
#include "logic.h"

PHASHTREE g_pSymbolTable = NULL;
__char **g_pSymbolList = NULL;
__integer g_iSymbolIndex = 0;
__integer g_iSymbolNameMaxCount = 0;

__void __INTERNAL_FUNC__ BackSymbol() {
	g_iSymbolIndex--;
}

__integer __INTERNAL_FUNC__ GetNowSymbolIndex() {
	return g_iSymbolIndex;
}

__char * __INTERNAL_FUNC__ NextSymbol() {
	if (!g_pSymbolList)
		return NULL;
	return g_pSymbolList[g_iSymbolIndex++];
}

/*
 * 释放符号节点的回调函数
 */
__void __INTERNAL_FUNC__ HashNodeValueFreeCallBack(__memory pSymbolValue) {
	if (pSymbolValue)
		__logic_delete__(pSymbolValue);
}

#define DEF_ASMER_SYMBOL_ROOT			5
__void __INTERNAL_FUNC__ InitAsmerSymbolTable(__integer iSymbolNameLength, __integer iSymbolNameCount) {
	__integer i;
	g_iSymbolIndex = 0;
	g_iSymbolNameMaxCount = iSymbolNameCount;
	g_pSymbolList = (__char **)__logic_new__(__char *, iSymbolNameCount);
	for (i = 0; i < iSymbolNameCount; i++)
		g_pSymbolList[i] = (__char *)__logic_new__(__char, iSymbolNameLength);
	g_pSymbolTable = init_hashtree(DEF_ASMER_SYMBOL_ROOT, HashNodeValueFreeCallBack);
}

PASMER_SYMBOL_NODE __INTERNAL_FUNC__ QuerySymbolFromTable(__char *pName) {
	PHASHTREE_NODE pHashNode = query_node_hashtree(g_pSymbolTable, (__byte *)pName, (__integer)__logic_strlen__(pName));
	if (pHashNode == NULL) return NULL;
	return (PASMER_SYMBOL_NODE)(pHashNode->value);
}

PASMER_SYMBOL_NODE __INTERNAL_FUNC__ AddSymbolToTable(__char *pName, __offset ofOffset, ASMER_SYMBOL_TYPE Type) {
	PASMER_SYMBOL_NODE pNode = NULL;
	PHASHTREE_NODE pHashNode = NULL;
	__CreateSymbolNode__(pNode, Type, ofOffset);
	pHashNode = add_node_hashtree(g_pSymbolTable, (__byte *)pName, (__integer)__logic_strlen__(pName), (__memory)pNode);
	if (pHashNode == NULL) {
		// 增加不成功则删除当前分配的内存
		__DestorySymbolNode__(pNode);
		return NULL;
	}
	return pNode;
}

__void __INTERNAL_FUNC__ DestoryAsmerSymbolTable() {
	__integer i;
	g_iSymbolIndex = 0;
	if (g_pSymbolTable)
		free_hashtree(&g_pSymbolTable);
	for (i = 0; i < g_iSymbolNameMaxCount; i++)
		__logic_delete__(g_pSymbolList[i]);
	__logic_delete__(g_pSymbolList);
	g_pSymbolList = NULL;
	g_iSymbolNameMaxCount = 0;
}
