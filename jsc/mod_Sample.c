#include <see/see.h>

#ifndef STR
#define STR(name) s##name
#endif

#undef PRIVATE
#undef PUTOBJ
#undef PUTFUNC

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

static int Sample_mod_init() {
	STR(Sample) = SEE_intern_global("Sample");
	STR(sample_method) = SEE_intern_global("sample_method");
	return 0;
}

static void Sample_alloc(struct SEE_interpreter *interp) {
	SEE_MODULE_PRIVATE(interp, &Sample_Module) = SEE_NEW(interp, struct sample_private);
}

static void Sample_init(struct SEE_interpreter *interp) {
	struct SEE_value v;
	struct SEE_object *Sample,*Sample_protype;

	//处理继承关系,大块指针可以转化成小块指针
	Sample_protype = (struct SEE_object *)SEE_NEW(interp, struct SEE_native);
    SEE_native_init((struct SEE_native *)Sample_protype, interp,&sample_constructor_class,interp->Object_prototype);
	PUTFUNC(Sample_protype,sample_method, 0)
	PRIVATE(interp)->sample_protype = Sample_protype;

	Sample = (struct SEE_object *)SEE_NEW(interp, struct SEE_native);
	//不会访问到SEE_native的properties
    SEE_native_init((struct SEE_native *)Sample, interp,&sample_constructor_class,interp->Object_prototype);
    PUTOBJ(interp->Global, Sample, Sample);
}

static void sample_construct( struct SEE_interpreter *interp, struct SEE_object *self, struct SEE_object *thisobj, int argc, struct SEE_value **argv, struct SEE_value *res) {

	struct sample_object *sample_object;	
	sample_object = SEE_NEW_FINALIZE(interp,struct sample_object,sample_finalize,NULL);
	SEE_native_init(&sample_object->native, interp, &sample_constructor_class, PRIVATE(interp)->sample_protype);
	sample_object->number = 0;
	SEE_SET_OBJECT(res, (struct SEE_object *)sample_object);
}

static void sample_proto_sample_method(struct SEE_interpreter *interp, struct SEE_object *self, struct SEE_object *thisobj, int argc, struct SEE_value **argv, struct SEE_value *res) { 
	struct sample_object *so = to_sample_obj(interp,thisobj);
	so->number += 1;
	SEE_SET_NUMBER(res,so->number);
}

//处理释放关系,SEE自动执行
static void sample_finalize(struct SEE_interpreter *interp, void *sample_object, void *other_params) {

}

static struct sample_object* to_sample_obj(struct SEE_interpreter *interp,struct SEE_object *o){
        if (!o || o->objectclass != &sample_constructor_class)
                SEE_error_throw(interp, interp->TypeError, NULL);
        return (struct sample_object *)o;
}
