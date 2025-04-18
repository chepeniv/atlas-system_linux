#include <Python.h>

/*
 * INSTRUCTIONS: create two c functions that print some basic info about
 * python lists and python byte objects:
 *     void print_python_list(PyObject *pylist)
 *     void print_python_bytes(PyObject *pybytes)
 */

/**
 * print_bytes - output at most ten bytes in hexadecimal form
 * @obj: the python object from which to extract the bytes
 * @size: a size limit that prevents invalid access
 */

void print_bytes(PyObject *obj, Py_ssize_t size)
{
	unsigned char *objbytes;
	int readlen = (size < 10) ? size : 10;

	objbytes = (unsigned char *) ((PyBytesObject *) obj)->ob_sval;

	if (objbytes[readlen] == '\0')
		readlen++;
	printf("  first %d bytes:", readlen);
	for (Py_ssize_t x = 0; x < readlen; x++)
		printf(" %02x", objbytes[x]);
	putchar('\n');
}

/**
 * print_python_bytes - printout some basic information about the given python
 * byte object
 * @pybytes: python object to parse and analyze as a PyBytesObject
 *
 * details:
 * if argument passed is not a valid `PyBytesObject` print an error message.
 * output no more than the first 10 bytes
 *
 * output:
 * [.] bytes object info
 *   size: <n>
 *   trying string: <text>
 *   first <m> bytes: %02x %02x ...
 * Element <i>: <type>
 * ...
 */

void print_python_bytes(PyObject *pybytes)
{
	Py_ssize_t obj_size;
	char *try_string;

	printf("[.] bytes object info\n");
	if (PyBytes_Check(pybytes))
	{
		obj_size = PyBytes_Size(pybytes);
		try_string = (char *) ((PyBytesObject *) pybytes)->ob_sval;

		printf(
			"  size: %ld\n"
			"  trying string: %s\n",
			obj_size, try_string
			);
		print_bytes(pybytes, obj_size);
	}
	else
	{
		printf("  [ERROR] Invalid Bytes Object\n");
	}
}

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
		item = ((PyListObject *) pylist)->ob_item[i];
		type = item->ob_type;
		printf("Element %ld: %s\n", i, type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
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
		list_alloc = ((PyListObject *)pylist)->allocated;

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
