#include <Python.h>

/**
 * print_python_list_items - prints out each elements position and type
 * @pylist: python list to iterate over
 * @list_len: the length of the list given
 */

void print_python_list_items(PyObject *pylist, Py_ssize_t list_len)
{
	PyTypeObject *type;
	PyObject *item;

	for (Py_ssize_t i = 0; i < list_len; i++)
	{
		item = PyList_GetItem(pylist, i);
		type = Py_TYPE(item);
		printf("Element %ld: %s\n", i, type->tp_name);
	}
}

/**
 * print_python_list - printout basic information about give python list object
 * @pylist: python object to analyze
 *
 * output:
 * [*] Python list info
 * [*] Size of the Python List = <number of elements>
 * [*] Allocated = <number of allocated items>
 * Element 0: <type of element 0>
 * Element 1: <type of element 1>
 * Element 2: <type of element 2>
 */

void print_python_list(PyObject *pylist)
{
	Py_ssize_t list_size, list_alloc;

	if (PyList_Check(pylist))
	{
		list_size = PyList_Size(pylist);
		list_alloc = list_size;

		printf(
			"[*] Python list info\n"
			"[*] Size of the Python List = %ld\n"
			"[*] Allocated = %ld\n",
			list_size, list_alloc
			);
		print_python_list_items(pylist, list_size);
	}
	else
	{
		printf("is not list");
	}
}
