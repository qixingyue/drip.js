#include <stdio.h>
#include <see/see.h>

int main(){
	struct SEE_interpreter interpreter;
	struct SEE_interpreter *interpreter_ptr = &interpreter;
	struct SEE_input *input;
	SEE_try_context_t try_ctx;
	struct SEE_value result;
	SEE_init();
	SEE_interpreter_init(interpreter_ptr);

	FILE *f = fopen("./b.js","r");
	input = SEE_input_file(interpreter_ptr,f,"./b.js",NULL);

	SEE_TRY (interpreter_ptr,try_ctx) {
		SEE_Global_eval(interpreter_ptr,input,&result);
		SEE_PrintValue(interpreter_ptr,&result,NULL);
		printf("\n");
	}

	SEE_INPUT_CLOSE(input);	

	if(SEE_CAUGHT(try_ctx)){
		printf("Exception happend . \n");	
	}


	return 0;

}
