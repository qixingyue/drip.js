#include <stdio.h>
#include <see/see.h>

#include "addFunc.c"
#include "mod_File.c"

int main(int argc,char** argv){

	if(argc != 2){
		printf("./drip a.js\n");
		exit(0);	
	} 
	char *jsfile = argv[1];
	struct SEE_interpreter interpreter;
	struct SEE_interpreter *interpreter_ptr = &interpreter;
	struct SEE_input *input;
	SEE_try_context_t try_ctx;
	struct SEE_value result;

	SEE_init();
	SEE_module_add(&File_module);
	SEE_interpreter_init(interpreter_ptr);

	add_methods(interpreter_ptr, interpreter_ptr->Global, global_methods);

	FILE *f = fopen(jsfile,"r");
	if(NULL == f) {
		printf("ERROR HAPPEND FILE : %s  NOT EXIST !\n", jsfile);	
		exit(1);
	}
	input = SEE_input_file(interpreter_ptr,f,jsfile,NULL);

	SEE_TRY (interpreter_ptr,try_ctx) {
		SEE_Global_eval(interpreter_ptr,input,&result);
		SEE_PrintValue(interpreter_ptr,&result,NULL);
	}

	SEE_INPUT_CLOSE(input);	

	if(SEE_CAUGHT(try_ctx)){
		printf("Exception happend . \n");	
	}

	return 0;

}
