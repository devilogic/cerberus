PHASHTREE g_pSymbolTable = NULL;//符号表
CHAR **g_pSymbolList = NULL;
DWORD g_dwSymbolIndex = 0;

INLINE VOID CHARM_INTERNAL_FUNC BackSymbol()
{
	g_dwSymbolIndex--;
}

INLINE DWORD CHARM_INTERNAL_FUNC GetNowSymbolIndex()
{
	return g_dwSymbolIndex;
}

CHAR *CHARM_INTERNAL_FUNC NextSymbol()
{
	if (g_pSymbolList == NULL)
	{
		return NULL;
	}
	return g_pSymbolList[g_dwSymbolIndex++];
}

/*
 * 释放符号节点的回调函数
 */
void __cdecl HashNodeValueFreeCallBack(void *pSymbolValue)
{
	if (pSymbolValue != NULL)
	{
		__delete__(pSymbolValue);
	}
}

#define DEF_ASMER_SYMBOL_ROOT			5
INLINE VOID CHARM_INTERNAL_FUNC InitAsmerSymbolTable(PASM_SOURCE pAsmSource)
{
	g_pSymbolList = pAsmSource->pSymbolList;
	g_dwSymbolIndex = 0;
	g_pSymbolTable = init_hashtree(DEF_ASMER_SYMBOL_ROOT, HashNodeValueFreeCallBack);
}

PASMER_SYMBOL_NODE CHARM_INTERNAL_FUNC QuerySymbolFromTable(CHAR *pName)
{
	PHASHTREE_NODE pHashNode = query_node_hashtree(g_pSymbolTable, (byte_t *)pName, (dword_t)strlen(pName));
	if (pHashNode == NULL) return NULL;
	return (PASMER_SYMBOL_NODE)(pHashNode->value);
}

PASMER_SYMBOL_NODE CHARM_INTERNAL_FUNC AddSymbolToTable(CHAR *pName, DWORD dwOffset, ASMER_SYMBOL_TYPE Type)
{
	PASMER_SYMBOL_NODE pNode = NULL;
	__CreateSymbolNode__(pNode, Type, dwOffset);
	PHASHTREE_NODE pHashNode = add_node_hashtree(g_pSymbolTable, (byte_t *)pName, (dword_t)strlen(pName), (void *)pNode);
	if (pHashNode == NULL)
	{
		// 增加不成功则删除当前分配的内存
		__DestorySymbolNode__(pNode);
		return NULL;
	}
	return pNode;
}

INLINE VOID CHARM_INTERNAL_FUNC DestoryAsmerSymbolTable()
{
	g_pSymbolList = NULL;
	g_dwSymbolIndex = 0;
	if (g_pSymbolTable != NULL)
		free_hashtree(&g_pSymbolTable);
}
