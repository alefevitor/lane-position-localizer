#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
 
int main() {
	printf("teste");
    Py_Initialize();
	// Importe um módulo Python
PyObject *pModule = PyImport_ImportModule("len_test");

// Obtenha uma referência para uma função Python
PyObject *pFunction = PyObject_GetAttrString(pModule, "detect");

// Crie argumentos e chame a função
PyObject *pArgs = PyTuple_Pack(1, PyUnicode_DecodeFSDefault("consegui"));
PyObject *pValue = PyObject_CallObject(pFunction, pArgs);

// Converta o resultado para um tipo C
int resultado = PyLong_AsLong(pValue);

// Libere objetos e finalize o interpretador Python
Py_XDECREF(pArgs);
Py_DECREF(pFunction);
Py_DECREF(pModule);
Py_Finalize();
     

}