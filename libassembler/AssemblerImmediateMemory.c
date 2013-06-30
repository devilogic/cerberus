#include "AssemblerImmediateMemory.h"

/*
 * 全局变量
 */
__memory g_pImmediateMemory = NULL;
__integer g_iImmediateMemoryIndex = 0;
__integer g_iImmediateMemoryMaxSize = 0;

__memory __INTERNAL_FUNC__ InitImmediateMemory(__integer iMaxSize) {
	g_pImmediateMemory = (__memory)__logic_new__(__byte, iMaxSize);
	if (!g_pImmediateMemory) return NULL;
	g_iImmediateMemoryMaxSize = iMaxSize;
	g_iImmediateMemoryIndex = 0;
	return g_pImmediateMemory;
}

__void __INTERNAL_FUNC__ FreeImmediateMemory() {
	__logic_delete__(g_pImmediateMemory);
	g_iImmediateMemoryIndex = g_iImmediateMemoryMaxSize = 0;
}

__memory __INTERNAL_FUNC__ GetImmediate(__integer iValueSize) {
	__memory pPoint = NULL;
	if (g_iImmediateMemoryIndex + iValueSize >= g_iImmediateMemoryMaxSize) return NULL;
	pPoint = g_pImmediateMemory + g_iImmediateMemoryIndex;
	g_iImmediateMemoryIndex += iValueSize;
	return pPoint;
}

__void __INTERNAL_FUNC__ BackImmediate(__integer iValueSize) {
	if (g_iImmediateMemoryIndex - iValueSize < 0) return;
	g_iImmediateMemoryIndex -= iValueSize;
}

__void __INTERNAL_FUNC__ ResetImmediate(__memory pMemory, __integer iSize) {
	if ((!g_pImmediateMemory) || (g_iImmediateMemoryIndex + iSize >= g_iImmediateMemoryMaxSize)) return;
	__logic_memcpy__(g_pImmediateMemory + g_iImmediateMemoryIndex, pMemory, iSize);
}
