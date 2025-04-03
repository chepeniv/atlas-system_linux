#include <Python.h>
#include <wchar.h>
#include <locale.h>

/*
 * INSTRUCTIONS:
 * void print_python_string(PyObject *pystr)
 * if `pystr` is not a valid string print an error message
 * https://docs.python.org/3.9/howto/unicode.html
 * you're allowed to use the c standard library
 * compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,
 *    soname,libPython.so  -o libPython.so -fPIC
 *    I/usr/include/python3.9 4-python.c`
 */

/**
 * print_python_string - output basic information about a given python string
 * @obj: the PyObject to parse and analyse as a PyUnicodeObject
 *
 * output:
 * [.] string object info
 *   type: <type>
 *   length: <number of characters>
 *   value: <string value>
 * types: 'compact ascii' and 'compact unicode object'
 */

void print_python_string(PyObject *obj)
{
	char *data;
	Py_ssize_t len;

	setlocale(LC_ALL, "C.UTF-8");

	printf("[.] string object info\n");
	if (PyUnicode_Check(obj))
	{
		len  = PyUnicode_GET_LENGTH(obj);
		data = PyUnicode_DATA(obj);

		if (PyUnicode_IS_COMPACT_ASCII(obj))
		{
			printf(
					"  type: compact ascii\n"
					"  length: %ld\n"
					"  value: %s\n",
					len, data);
		}
		else
		{
			printf(
					"  type: compact unicode object\n"
					"  length: %ld\n",
					len);
			printf("  value: %ls\n", (wchar_t *) data);
		}
	}
	else
	{
		printf("  [ERROR] Invalid String Object\n");
	}
}
