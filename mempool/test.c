#include "pool.h"
#include <stdio.h>
#include <string.h>

struct test{
	int number;
	char name[20];
};

void too_much_handler(size_t);

int main(){
	size_t max_size = 1024 * 1024 * 256;
	struct test *tp;
	char *info = "Hello world";

	POOL_RUN(max_size,NULL);
	tp = (struct test *)pool_malloc(pool,sizeof(struct test));
	tp->number = 20;
	memcpy(tp->name,info,strlen(info));
	printf("%d , %s \n",tp->number,tp->name);
	POOL_RUN_END();

	POOL_RUN(max_size,NULL);
	tp = (struct test *)pool_malloc(pool,sizeof(struct test));
	tp->number = 20;
	memcpy(tp->name,info,strlen(info));
	printf("%d , %s \n",tp->number,tp->name);
	POOL_RUN_END()

	return 0;
}

