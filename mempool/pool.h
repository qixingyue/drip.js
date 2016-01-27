#ifndef __POOL_H
#define __POOL_H

#include <stdlib.h>
#include <stdio.h>

#define _error_die(message) \
	printf("%s",message); \
	exit(1);

#define _assert(station,message) \
	if( station) { \
		_error_die(message); \
	}

//为每个原子请求分配一个pool,使用完成以后，释放掉整个的pool
//而非释放单纯的原子结构

#define INITIAL_BLOCK_SIZE	8192
#define ALIGN_SIZE (sizeof(void*) - 1)

#define POOL_RUN(max,handler) \
	_assert(NULL == pool , "YOU MUST END THE LAST POOL_RUN\n" ) ; \
	pool = pool_new(max,handler); 
#define POOL_RUN_END() pool_destroy(pool);

typedef struct pool pool_t;
typedef void (*over_size_t_handler)(size_t);

struct block {
	struct block *next;
	char *p;	
	int avail;
};

struct pool {
	struct block *blocks;
	size_t next_alloc;
	size_t max_block;
	over_size_t_handler too_much_handler;
};

pool_t * pool_new(size_t,over_size_t_handler);
void pool_destroy(pool_t *);
void * pool_malloc(pool_t *, size_t );
static void default_too_much_hanlder(size_t next_alloc);

pool_t *pool;

#endif
