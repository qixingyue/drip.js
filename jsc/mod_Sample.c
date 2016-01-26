#include <see/see.h>
#include "mod_Sample.h"

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
