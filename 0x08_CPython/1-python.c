#include <Python.h>

/**
 * print_python_list - printout basic information about give python list object
 * @pylist: python list to analyze
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
	if (PyList_Check(pylist))
	{
		printf("is list");
	}
	else
	{
		printf("is not list");
	}
}
