#include "approxidate.h"
#include <Python.h>

static PyObject* approxidate_approx(PyObject* self, PyObject* args)
{
	const char*     date;
	PyObject*       relative_to;
	struct timeval  ret;
	struct timeval  rel;
	struct timeval* relp = NULL;

	if (!PyArg_ParseTuple(args, "sO", &date, &relative_to)) {
		return NULL;
	}

	if (relative_to != Py_None) {
		double drel = PyFloat_AsDouble(relative_to);

		// Error getting relative_to as a double?
		if (PyErr_Occurred() != NULL) {
			return NULL;
		}

		rel.tv_sec  = drel;
		rel.tv_usec = (drel - rel.tv_sec) * 100000;
		relp        = &rel;
	}

	if (approxidate_relative(date, &ret, relp) < 0) {
		return PyErr_Format(PyExc_ValueError, "could not parse date: %s", date);
	}

	return PyFloat_FromDouble(ret.tv_sec + (ret.tv_usec / 1000000.0));
}

static PyMethodDef module_funcs[] = {
	{ "approx", approxidate_approx, METH_VARARGS, NULL },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef module = {
	PyModuleDef_HEAD_INIT,
	"_c",         /* m_name */
	NULL,         /* m_doc */
	-1,           /* m_size */
	module_funcs, /* m_methods */
	NULL,         /* m_reload */
	NULL,         /* m_traverse */
	NULL,         /* m_clear */
	NULL,         /* m_free */
};

PyMODINIT_FUNC PyInit__c(void)
{
	return PyModule_Create(&module);
}
