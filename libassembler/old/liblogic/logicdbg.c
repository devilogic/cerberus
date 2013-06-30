/*
 * 头文件
 */
#include "logicdbg.h"

/*
 * 结构定义
 */
/* 内存记录指针 */
typedef struct _ALLOCRCD
{
	/* 分配的内存 */
	void *memory;
	/* 内存的长度 */
	unsigned long size;
	/* 属于的文件 */
	const char *file;
	/* 行号 */
	unsigned long line;
	/* 下一个节点 */
	struct _ALLOCRCD *next;
} ALLOCRCD, *PALLOCRCD;

/*
 * 公共变量
 */
PALLOCRCD alloc_header = NULL;
PALLOCRCD *alloc_current = &alloc_header;
unsigned long alloc_count = 0;

/*
 * 函数定义
 */
/*
 * 作者:玩命
 * 开始日期:2009-6-14
 * 完成日期:2009-6-14
 * 参数:
 *    sz:要分配的内存.
 *    file:源文件名.
 *    line:行号.
 * 返回值:
 *	  分配的内存指针.
 *    失败返回NULL.
 * 说明:
 *    分配内存并记录到内存链中.
 */
void *debug_memory_alloc(unsigned long sz, const char *file, unsigned long line) {
	void *p = (void *)malloc(sz);
	if (!p) return NULL;
	/* 加入到链中 */
	(*alloc_current) = (PALLOCRCD)malloc(sizeof(ALLOCRCD));
	assert(*alloc_current);
	(*alloc_current)->file = file;
	(*alloc_current)->line = line;
	(*alloc_current)->memory = p;
	(*alloc_current)->size = sz;
	(*alloc_current)->next = NULL;
	alloc_current = &((*alloc_current)->next);
	alloc_count++;
	return p;
}/* end debug_memory_alloc */

/*
 * 作者:玩命
 * 开始日期:2009-6-14
 * 完成日期:2009-6-14
 * 参数:
 *    p:要释放的内存.
 * 返回值:
 * 说明:
 *    释放内存.
 */
void debug_memory_free(void *p) {
	PALLOCRCD t = alloc_header;PALLOCRCD b = NULL;
	assert(p && alloc_header);
	/* 遍历链表 */
	while (t) {
		/* 找到要删除的节点 */
		if (t->memory == p) {
			/* 如果是头节点 */
			if (!b) {
				b = t->next;
				if (t->memory) free(t->memory);
				free(t);
				alloc_header = b;
				/* 如果链表中只有一个头节点 */
				if (!alloc_header) alloc_current = &alloc_header;
			/* 如果是尾节点 */
			} else if (!(t->next)) {
				if (t->memory) free(t->memory);
				free(t);
				b->next = NULL;
				alloc_current = &(b->next);
			/* 如果删除的节点属于中间位置 */
			} else {
				b->next = t->next;
				if (t->memory) free(t->memory);
				free(t);
			}/* end else */
			alloc_count--;
			return;
		}/* end if */
		b = t;
		t = t->next;
	}/* end while */
}/* debug_memory_free */

/*
 * 作者:玩命
 * 开始日期:2009-6-14
 * 完成日期:2009-6-14
 * 参数:
 * 返回值:
 * 说明:
 *    检查内存泄漏,最好在程序运行完毕时使用.
 */
void debug_check_leak(void) {
	PALLOCRCD t = alloc_header;
	/* 无内存泄漏 */
	if (!alloc_count) {
		printf("aha... no memory leak! ^_^\n");
		return;
	}
	printf("%d memory not logic_free\n", alloc_count);
	while (t) {
		printf("at source code[%s:%lu] -> %p,size=%lu\n", t->file, t->line, t->memory, t->size);
		t = t->next;
	}
}/* end debug_show_alloc */