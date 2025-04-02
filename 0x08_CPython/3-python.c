#include <Python.h>

/*
 * INSTRUCTIONS:
 * create three c functions that print some basic info about lists, python
 * bytes, and python float objects
 *
 * the c standard library is allowed
 *
 * python scripts will be ran with the `-u`
 *
 * use either `setbuf(stdout, NULL)` or `fflush(stdout)` if using `printf`
 * since python's `print` and libc's `printf` don't share the same buffer which
 * may cause the output to become disordered
 *
 * PYTHON LISTS:
 * void print_python_list(PyObject *pylist)
 * if `pylist` is not a valid `PyListObject` print an error message
 *
 * PYTHON BYTES:
 * void print_python_bytes(PyObject *pybytes)
 * if `pybytes` is not a valid `PyBytesObject` print an error message
 *
 * PYTHON FLOAT:
 * void print_python_float(PyObject *pyfloat)
 * if `pyfloat` is not a valid `PyFloatObject` print an error message
 * resource: floatobject.h
 */

/**
 * print_python_float - printout the value of a python PyFloatObject as a c
 * double
 * @obj: the python object to parse
 */

void print_python_float(PyObject *obj)
{
	double value;

	if (PyFloat_Check(obj))
	{
		value = ((PyFloatObject *) obj)->ob_fval;
		printf(
			"[.] float object info\n"
			"  value: %g\n",
			value);
	}
	else
		printf("  [ERROR] Invalid Float Object\n");
}

/**
 * print_hex_bytes - output at most ten bytes in hexadecimal form
 * @obj: the python object from which to extract the bytes
 * @size: a size limit that prevents invalid access
 */

void print_hex_bytes(PyObject *obj, Py_ssize_t size)
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
		print_hex_bytes(pybytes, obj_size);
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
		if (PyFloat_Check(item))
			print_python_float(item);
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
		list_size = ((PyListObject *)pylist)->ob_base.ob_size;
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
		printf("  [ERROR] Invalid Bytes Object\n");
	}
}
