#include <stdio.h>
#include <see/see.h>

int main(){
	struct SEE_interpreter interpreter;
	struct SEE_interpreter *interpreter_ptr = &interpreter;
	struct SEE_input *input;
	SEE_try_context_t try_ctx;
	struct SEE_value result;
	char *jscode = "12";

	SEE_init();
	SEE_interpreter_init(interpreter_ptr);

	input = SEE_input_utf8(interpreter_ptr,jscode);

	SEE_TRY (interpreter_ptr,try_ctx) {
		SEE_Global_eval(interpreter_ptr,input,&result);
		if(SEE_VALUE_GET_TYPE(&result) == SEE_NUMBER){
			printf("The answer is %f \n",result.u.number);	
		} else {
			printf("Unexpected answer\n");	
		}
	}

	SEE_INPUT_CLOSE(input);	

	if(SEE_CAUGHT(try_ctx)){
		printf("Exception happend . \n");	
	}

	return 0;

}
