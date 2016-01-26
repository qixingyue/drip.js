#ifndef MOD_SAMPLE_H
#define MOD_SAMPLE_H

#undef PRIVATE
#undef PUTOBJ
#undef PUTFUNC
#undef STR

#define STR(name) s##name

#define PRIVATE(interp) ((struct sample_private*)SEE_MODULE_PRIVATE(interp, &Sample_Module))

#define PUTOBJ(parent, name, obj)                                       \
        SEE_SET_OBJECT(&v, obj);                                        \
        SEE_OBJECT_PUT(interp, parent, STR(name), &v, SEE_ATTR_DEFAULT);

#define PUTFUNC(obj, name, len)                                         \
        SEE_SET_OBJECT(&v, SEE_cfunction_make(interp, sample_proto_##name,\
                STR(name), len));                                       \
        SEE_OBJECT_PUT(interp, obj, STR(name), &v, SEE_ATTR_DEFAULT);

static int Sample_mod_init();
static void Sample_alloc(struct SEE_interpreter *);
static void Sample_init(struct SEE_interpreter *);
static void sample_construct(struct SEE_interpreter *,struct SEE_object *, struct SEE_object *,int,struct SEE_value **, struct SEE_value *) ;
static void sample_finalize(struct SEE_interpreter *, void *, void *);
static void sample_proto_sample_method(struct SEE_interpreter *, struct SEE_object *, struct SEE_object *, int , struct SEE_value **, struct SEE_value *);
static struct sample_object* to_sample_obj(struct SEE_interpreter *,struct SEE_object *);

static struct SEE_string *STR(Sample),*STR(sample_method);

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
	struct SEE_object *sample_protype;
};

struct sample_object{
	struct SEE_native        native;
	int number;
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

#endif
