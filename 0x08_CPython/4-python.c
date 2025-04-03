#include <Python.h>

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
	PyUnicodeObject *pystr;
	char *type;

	printf("[.] string object info\n");
	if (PyUnicode_Check(obj))
	{
		pystr = (PyUnicodeObject *) obj;
		type = (PyUnicode_KIND(pystr) == 1) ?
			"compact ascii" : "compact unicode object" ;

		printf(
			"  type: \n"
			"  length: \n"
			"  value: \n"
			);
	}
	else
	{
		printf("  [ERROR] Invalid String Object\n");
	}
}
