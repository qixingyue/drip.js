#include "pool.h"

pool_t * pool_new(size_t max_memory,over_size_t_handler too_much_mem_handler) {
	pool_t *pool;
	default_mem_sys.malloc = default_malloc;
	default_mem_sys.free = default_free;

	pool = (pool_t *)default_mem_sys.malloc(sizeof (pool_t));
	if (pool) {
		pool->blocks = NULL;
		pool->next_alloc = INITIAL_BLOCK_SIZE;
		pool->max_memory = max_memory;
		pool->current_memory = 0;
		if(NULL == too_much_mem_handler) {
			too_much_mem_handler = default_too_much_hanlder;
		}
		pool->too_much_handler = too_much_mem_handler;
	}
	return pool;
}

void pool_destroy(pool_t *pool) {
	struct block *block;
	_assert(NULL == pool,"POOL CANT'T BE NULL\n");
	while (pool->blocks) {
		block = pool->blocks;
		pool->blocks = block->next;
		default_mem_sys.free(block);
	}
	default_mem_sys.free(pool);
}

void * pool_malloc(pool_t *pool, size_t size) {
	int spc;
	struct block *block;
	char *ptr;

	_assert(NULL == pool,"POOL CANT'T BE NULL\n");

	/* Round size up to align to nearest ptr */
	// 跟sizeof (void *) 对齐
	spc = (size + ALIGN_SIZE ) & ~ ALIGN_SIZE;

  	for (;;) {
		/* Search blocks for enough space */
		for (block = pool->blocks; block; block = block->next) {
		    if (block->avail >= spc) {
				ptr = block->p;
				block->p += spc;
				block->avail -= spc;
				return ptr;
			}
		}

		if(pool->current_memory >= pool->max_memory) {
			pool->too_much_handler(pool->current_memory);
			return NULL;
		}

		/* No block had enough space. Make more blocks! */
		//扩大内存区
		while (pool->next_alloc < spc + sizeof (struct block))
			pool->next_alloc *= 2;

		block = (struct block *)default_mem_sys.malloc(pool->next_alloc);
		if (!block) {
			return NULL;
		}
		pool->current_memory += pool->next_alloc;
		//指向后边的内存区域
		block->p = (void *)(block + 1);
		//设置可用空间
		block->avail = pool->next_alloc - sizeof (struct block);
		//把分配的块加入到pool里边
		block->next = pool->blocks;
		pool->blocks = block;
		pool->next_alloc *= 2;
	}
}

void default_too_much_hanlder(size_t current_memory){
	printf("TOO MUCH MEMORY USED CURRENT MEMORY : %ld \n",current_memory);
	exit(0);
}

static void *default_malloc(size_t size){
	return malloc(size);
}

static void default_free(void *ptr){
	free(ptr);
}
