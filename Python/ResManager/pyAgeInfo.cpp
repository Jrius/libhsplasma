#include <Python.h>
#include <ResManager/plAgeInfo.h>
#include "pyResManager.h"
#include "../Stream/pyStream.h"
#include "../PRP/KeyedObject/pyKey.h"

extern "C" {

static void pyAgeInfo_dealloc(pyAgeInfo* self) {
    if (self->fPyOwned)
        delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pyAgeInfo___init__(pyAgeInfo* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyAgeInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAgeInfo* self = (pyAgeInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAgeInfo_readFromFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "readFromFile expects a string");
        return NULL;
    }
    self->fThis->readFromFile(filename);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_writeToFile(pyAgeInfo* self, PyObject* args) {
    const char* filename;
    int version;
    if (!PyArg_ParseTuple(args, "si", &filename, &version)) {
        PyErr_SetString(PyExc_TypeError, "writeToFile expects string, int");
        return NULL;
    }
    self->fThis->writeToFile(filename, (PlasmaVer)version);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getNumPages(pyAgeInfo* self) {
    return PyInt_FromLong(self->fThis->getNumPages());
}

static PyObject* pyAgeInfo_getPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getPage expects an int");
        return NULL;
    }
    plAgeInfo::PageEntry pe = self->fThis->getPage(idx);
    return Py_BuildValue("sii", pe.fName.cstr(), pe.fSeqSuffix, pe.fLoadFlags);
}

static PyObject* pyAgeInfo_setPage(pyAgeInfo* self, PyObject* args) {
    int idx;
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "i(sii)", &idx, &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "setPage expects int, (string, int, int)");
        return NULL;
    }
    self->fThis->setPage(idx, plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_addPage(pyAgeInfo* self, PyObject* args) {
    const char* name;
    int seqSuffix, flags;

    if (!PyArg_ParseTuple(args, "(sii)", &name, &seqSuffix, &flags)) {
        PyErr_SetString(PyExc_TypeError, "addPage expects a tuple(string, int, int)");
        return NULL;
    }
    self->fThis->addPage(plAgeInfo::PageEntry(name, seqSuffix, flags));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAgeInfo_getPageFilename(pyAgeInfo* self, PyObject* args) {
    int idx, version;
    if (!PyArg_ParseTuple(args, "ii", &idx, &version)) {
        PyErr_SetString(PyExc_TypeError, "getPageFilename expects int, int");
        return NULL;
    }
    return PyString_FromString(self->fThis->getPageFilename((size_t)idx, (PlasmaVer)version).cstr());
}

static PyObject* pyAgeInfo_getPageLoc(pyAgeInfo* self, PyObject* args) {
    int idx, ver;
    if (!PyArg_ParseTuple(args, "ii", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getPageLoc expects int, int");
        return NULL;
    }
    return pyLocation_FromLocation(self->fThis->getPageLoc((size_t)idx, (PlasmaVer)ver));
}

static PyObject* pyAgeInfo_getName(pyAgeInfo* self, void*) {
    return PyString_FromString(self->fThis->getAgeName().cstr());
}

static PyObject* pyAgeInfo_getStartDateTime(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getStartDateTime());
}

static PyObject* pyAgeInfo_getDayLength(pyAgeInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDayLength());
}

static PyObject* pyAgeInfo_getMaxCapacity(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getMaxCapacity());
}

static PyObject* pyAgeInfo_getLingerTime(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getLingerTime());
}

static PyObject* pyAgeInfo_getSeqPrefix(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getSeqPrefix());
}

static PyObject* pyAgeInfo_getReleaseVersion(pyAgeInfo* self, void*) {
    return PyInt_FromLong(self->fThis->getReleaseVersion());
}

static int pyAgeInfo_setName(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setAgeName("");
    } else {
        if (!PyString_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "name must be a string");
            return -1;
        }
        self->fThis->setAgeName(PyString_AsString(value));
    }
    return 0;
}

static int pyAgeInfo_setStartDateTime(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setStartDateTime(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "startDateTime must be an int");
            return -1;
        }
        self->fThis->setStartDateTime(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setDayLength(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setDayLength(0.0f);
    } else {
        if (!PyFloat_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "dayLength must be a float");
            return -1;
        }
        self->fThis->setDayLength(PyFloat_AsDouble(value));
    }
    return 0;
}

static int pyAgeInfo_setMaxCapacity(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setMaxCapacity(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "maxCapacity must be an int");
            return -1;
        }
        self->fThis->setMaxCapacity(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setLingerTime(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setLingerTime(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "lingerTime must be an int");
            return -1;
        }
        self->fThis->setLingerTime(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setSeqPrefix(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSeqPrefix(-1);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "seqPrefix must be an int");
            return -1;
        }
        self->fThis->setSeqPrefix(PyInt_AsLong(value));
    }
    return 0;
}

static int pyAgeInfo_setReleaseVersion(pyAgeInfo* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setReleaseVersion(0);
    } else {
        if (!PyInt_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "releaseVersion must be an int");
            return -1;
        }
        self->fThis->setReleaseVersion(PyInt_AsLong(value));
    }
    return 0;
}

static PyMethodDef pyAgeInfo_Methods[] = {
    { "readFromFile", (PyCFunction)pyAgeInfo_readFromFile, METH_VARARGS,
      "Params: filename\n"
      "Reads the AgeInfo from a .age file" },
    { "writeToFile", (PyCFunction)pyAgeInfo_writeToFile, METH_VARARGS,
      "Params: filename, version\n"
      "Write the AgeInfo to a .age file" },
    { "getNumPages", (PyCFunction)pyAgeInfo_getNumPages, METH_NOARGS,
      "Returns the number of pages described by this AgeInfo" },
    { "getPage", (PyCFunction)pyAgeInfo_getPage, METH_VARARGS,
      "Params: idx\n"
      "Returns a tuple (name, pageNum, loadFlags) for the specified page" },
    { "setPage", (PyCFunction)pyAgeInfo_setPage, METH_VARARGS,
      "Params: idx, (name, pageNum, loadFlags)\n"
      "Sets info for the specified page" },
    { "addPage", (PyCFunction)pyAgeInfo_addPage, METH_VARARGS,
      "Params: (name, pageNum, loadFlags)\n"
      "Adds a page to the AgeInfo" },
    { "getPageFilename", (PyCFunction)pyAgeInfo_getPageFilename, METH_VARARGS,
      "Params: idx, version\n"
      "Returns the standard Page Filename for the specified page" },
    { "getPageLoc", (PyCFunction)pyAgeInfo_getPageLoc, METH_VARARGS,
      "Params: idx\n"
      "Returns a plLocation for the specified page" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAgeInfo_GetSet[] = {
    { "name", (getter)pyAgeInfo_getName, (setter)pyAgeInfo_setName,
      "The Name of the age", NULL },
    { "startDateTime", (getter)pyAgeInfo_getStartDateTime, (setter)pyAgeInfo_setStartDateTime,
      "StartDateTime field", NULL },
    { "dayLength", (getter)pyAgeInfo_getDayLength, (setter)pyAgeInfo_setDayLength,
      "DayLength field", NULL },
    { "maxCapacity", (getter)pyAgeInfo_getMaxCapacity, (setter)pyAgeInfo_setMaxCapacity,
      "MaxCapacity field", NULL },
    { "lingerTime", (getter)pyAgeInfo_getLingerTime, (setter)pyAgeInfo_setLingerTime,
      "LingerTime field", NULL },
    { "seqPrefix", (getter)pyAgeInfo_getSeqPrefix, (setter)pyAgeInfo_setSeqPrefix,
      "SeqPrefix field", NULL },
    { "releaseVersion", (getter)pyAgeInfo_getReleaseVersion, (setter)pyAgeInfo_setReleaseVersion,
      "ReleaseVersion field", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAgeInfo_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plAgeInfo",               /* tp_name */
    sizeof(pyAgeInfo),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyAgeInfo_dealloc,      /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    NULL,                               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAgeInfo_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeInfo_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyAgeInfo___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeInfo_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAgeInfo_Type() {
    if (PyType_Ready(&pyAgeInfo_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagPreventAutoLoad",
                         PyInt_FromLong(plAgeInfo::kPreventAutoLoad));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagLoadIfSDLPresent",
                         PyInt_FromLong(plAgeInfo::kLoadIfSDLPresent));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsLocalOnly",
                         PyInt_FromLong(plAgeInfo::kIsLocalOnly));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kFlagIsVolatile",
                         PyInt_FromLong(plAgeInfo::kIsVolatile));

    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageTextures",
                         PyInt_FromLong(plAgeInfo::kTextures));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kPageGlobal",
                         PyInt_FromLong(plAgeInfo::kGlobal));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kNumCommonPages",
                         PyInt_FromLong(plAgeInfo::kNumCommonPages));

    PyObject* list = PyList_New(plAgeInfo::kNumCommonPages);
    for (size_t i=0; i<plAgeInfo::kNumCommonPages; i++)
        PyList_SET_ITEM(list, i, PyString_FromString(plAgeInfo::kCommonPages[i]));
    PyDict_SetItemString(pyAgeInfo_Type.tp_dict, "kCommonPages", list);

    Py_INCREF(&pyAgeInfo_Type);
    return (PyObject*)&pyAgeInfo_Type;
}

int pyAgeInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyAgeInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyAgeInfo_Type))
        return 1;
    return 0;
}

PyObject* pyAgeInfo_FromAgeInfo(class plAgeInfo* age) {
    if (age == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAgeInfo* obj = PyObject_New(pyAgeInfo, &pyAgeInfo_Type);
    obj->fThis = age;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}