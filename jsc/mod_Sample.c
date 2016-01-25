#include <see/see.h>

#ifndef STR
#define STR(name) s##name
#endif

static int Sample_mod_init();
static void Sample_alloc(struct SEE_interpreter *);
static void Sample_init(struct SEE_interpreter *);

static struct SEE_string *STR(Sample) ;

struct SEE_module Sample_Module = {
	SEE_MODULE_MAGIC,               /* magic */
	"Sample",                         /* name */
	"1.0",                          /* version */
	0,                              /* index (set by SEE) */
	Sample_mod_init,                  /* mod_init */
	Sample_alloc,                     /* alloc */
	Sample_init/* init */
};

struct sample_private{

};

static int Sample_mod_init() {
	STR(Sample) = SEE_intern_global("Sample");
	return 0;
}

static void Sample_alloc(struct SEE_interpreter *interp) {
	SEE_MODULE_PRIVATE(interp, &Sample_Module) = SEE_NEW(interp, struct sample_private);
}

static void Sample_init(struct SEE_interpreter *interp) {

}
