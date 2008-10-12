#include <Python.h>
#include <PRP/Light/plDirectionalLightInfo.h>
#include "pyLightInfo.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyDirectionalLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDirectionalLightInfo* self = (pyDirectionalLightInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDirectionalLightInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDirectionalLightInfo_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyDirectionalLightInfo_FromDirectionalLightInfo(plDirectionalLightInfo::Convert(cre->fThis));
}

static PyMethodDef pyDirectionalLightInfo_Methods[] = {
    { "Convert", (PyCFunction)pyDirectionalLightInfo_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plDirectionalLightInfo" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyDirectionalLightInfo_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plDirectionalLightInfo",  /* tp_name */
    sizeof(pyDirectionalLightInfo),     /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plDirectionalLightInfo wrapper",   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDirectionalLightInfo_Methods,     /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDirectionalLightInfo_new,         /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyDirectionalLightInfo_Type() {
    pyDirectionalLightInfo_Type.tp_base = &pyLightInfo_Type;
    if (PyType_Ready(&pyDirectionalLightInfo_Type) < 0)
        return NULL;

    Py_INCREF(&pyDirectionalLightInfo_Type);
    return (PyObject*)&pyDirectionalLightInfo_Type;
}

int pyDirectionalLightInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyDirectionalLightInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyDirectionalLightInfo_Type))
        return 1;
    return 0;
}

PyObject* pyDirectionalLightInfo_FromDirectionalLightInfo(class plDirectionalLightInfo* light) {
    if (light == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDirectionalLightInfo* pyLight = PyObject_New(pyDirectionalLightInfo, &pyDirectionalLightInfo_Type);
    pyLight->fThis = light;
    pyLight->fPyOwned = false;
    return (PyObject*)pyLight;
}

}