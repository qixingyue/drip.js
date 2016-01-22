struct method {
	const char *name;
	void (*fn)(struct SEE_interpreter *, struct SEE_object *, 
		struct SEE_object *, int, struct SEE_value **, 
		struct SEE_value *);
	int expected_args;
};

static void add_methods(struct SEE_interpreter *interp, struct SEE_object *object, const struct method *methods) {
	unsigned int i;
	for (i = 0; methods[i].name; i++)
		SEE_CFUNCTION_PUTA(interp, object, methods[i].name, methods[i].fn, methods[i].expected_args, 0);
}

static void print_fn(struct SEE_interpreter *interp, struct SEE_object *self, struct SEE_object *thisobj, int argc,  struct SEE_value **argv, struct SEE_value *res)
{
	struct SEE_value v;
	int i;

	for (i = 0; i < argc; i++) {
                SEE_ToString(interp, argv[i], &v);
                SEE_string_fputs(v.u.string, stdout);
        }
	printf("\n");
	fflush(stdout);
	SEE_SET_NUMBER(res,i);
}

static const struct method global_methods[] = {
	{"print",print_fn,1}
	,{0}
};
