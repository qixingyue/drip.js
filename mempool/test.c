#include "pool.h"
#include <stdio.h>
#include <string.h>

struct test{
	int number;
	char name[20];
};

void too_much_handler(size_t);

int main(){
	size_t max_size = 1024 * 2;
	struct test *tp[1000];
	char *info = "Hello world";
	int i = 0;

	POOL_RUN(max_size,NULL);
	for(;i<1000;i++){
		printf("\n============%d====================\n",i);
		tp[i] = (struct test *)pool_malloc(pool,sizeof(struct test));
		tp[i]->number = 20;
		memcpy(tp[i]->name,info,strlen(info));
		printf("%d , %s \n",tp[i]->number,tp[i]->name);
		printf("Current Memory : %ld\n",pool->current_memory);
	}
	POOL_RUN_END();

	POOL_RUN(max_size,NULL);
	//tp = (struct test *)pool_malloc(pool,sizeof(struct test));
	//tp->number = 20;
	//memcpy(tp->name,info,strlen(info));
	//printf("%d , %s \n",tp->number,tp->name);
	POOL_RUN_END()

	return 0;
}

