#if WITH_EDITOR
#include "UnrealEnginePythonPrivatePCH.h"

#include "UEPySGraphEditor.h"



#define GET_s_graph_editor SGraphEditor *s_graph_editor = (SGraphEditor*) self->s_compound_widget.s_widget.s_widget


static PyObject *ue_PySGraphEditor_str(ue_PySGraphEditor *self)
{
	return PyUnicode_FromFormat("<unreal_engine.SGraphEditor '%p'>",
		self->s_compound_widget.s_widget.s_widget);
}

static PyMethodDef ue_PySGraphEditor_methods[] = {
	{ NULL }  /* Sentinel */
};

PyTypeObject ue_PySGraphEditorType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"unreal_engine.SGraphEditor", /* tp_name */
	sizeof(ue_PySGraphEditor), /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,       /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	(reprfunc)ue_PySGraphEditor_str,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
	"Unreal Engine SGraphEditor",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	ue_PySGraphEditor_methods,             /* tp_methods */
};

static int ue_py_sgraph_editor_init(ue_PySGraphEditor *self, PyObject *args, PyObject *kwargs) {
	PyObject *py_graph;
	if (!PyArg_ParseTuple(args, "O", &py_graph)) {
		return -1;
	}

	UEdGraph *graph = ue_py_check_type<UEdGraph>(py_graph);
	if (!graph) {
		PyErr_SetString(PyExc_Exception, "argument is not a EdGraph");
		return -1;
	}
	self->s_compound_widget.s_widget.s_widget_owned = SNew(SGraphEditor).GraphToEdit(graph);
	self->s_compound_widget.s_widget.s_widget = &self->s_compound_widget.s_widget.s_widget_owned.Get();
	return 0;
}

void ue_python_init_sgraph_editor(PyObject *ue_module) {
	ue_PySGraphEditorType.tp_new = PyType_GenericNew;

	ue_PySGraphEditorType.tp_init = (initproc)ue_py_sgraph_editor_init;

	ue_PySGraphEditorType.tp_base = &ue_PySCompoundWidgetType;

	if (PyType_Ready(&ue_PySGraphEditorType) < 0)
		return;

	Py_INCREF(&ue_PySGraphEditorType);
	PyModule_AddObject(ue_module, "SGraphEditor", (PyObject *)&ue_PySGraphEditorType);
}
#endif
