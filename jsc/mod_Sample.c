#include <see/see.h>

#ifndef STR
#define STR(name) s##name
#endif

#ifndef PRIVATE
#define PRIVATE(interp) ((struct sample_private*)SEE_MODULE_PRIVATE(interp, &Sample_Module))
#endif

#ifndef PUTOBJ
#define PUTOBJ(parent, name, obj)                                       \
        SEE_SET_OBJECT(&v, obj);                                        \
        SEE_OBJECT_PUT(interp, parent, STR(name), &v, SEE_ATTR_DEFAULT);
#endif

#ifndef PUTFUNC
#define PUTFUNC(obj, name, len)                                         \
        SEE_SET_OBJECT(&v, SEE_cfunction_make(interp, file_proto_##name,\
                STR(name), len));                                       \
        SEE_OBJECT_PUT(interp, obj, STR(name), &v, SEE_ATTR_DEFAULT);
#endif


static int Sample_mod_init();
static void Sample_alloc(struct SEE_interpreter *);
static void Sample_init(struct SEE_interpreter *);
static void sample_construct(struct SEE_interpreter *,struct SEE_object *, struct SEE_object *,int,struct SEE_value **, struct SEE_value *) ;

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

struct sample_object{
	struct SEE_native        native;
};

static struct SEE_objectclass sample_constructor_class = {
        "Sample",                         /* Class */
        SEE_native_get,                 /* Get */
        SEE_native_put,                 /* Put */
        SEE_native_canput,              /* CanPut */
        SEE_native_hasproperty,         /* HasProperty */
        SEE_native_delete,              /* Delete */
        SEE_native_defaultvalue,        /* DefaultValue */
        SEE_native_enumerator,          /* DefaultValue */
        sample_construct,                 /* Construct */
        NULL                            /* Call */
};

static int Sample_mod_init() {
	STR(Sample) = SEE_intern_global("Sample");
	return 0;
}

static void Sample_alloc(struct SEE_interpreter *interp) {
	SEE_MODULE_PRIVATE(interp, &Sample_Module) = SEE_NEW(interp, struct sample_private);
}

static void Sample_init(struct SEE_interpreter *interp) {
	struct SEE_value v;
	struct SEE_object *Sample;
	Sample = (struct SEE_object *)SEE_NEW(interp, struct sample_object);
    SEE_native_init((struct SEE_native *)Sample, interp,&sample_constructor_class,interp->Object_prototype);
    PUTOBJ(interp->Global, Sample, Sample);
}

static void sample_construct( struct SEE_interpreter *interp, struct SEE_object *self, struct SEE_object *thisobj, int argc, struct SEE_value **argv, struct SEE_value *res) {
	SEE_SET_UNDEFINED(res);
}

