#include <Python.h>

/*
 * INSTRUCTIONS:
 * create a c function that prints python integers
 *
 * if `pyint` is not a valid string print an error message
 * translate the python `int` to a C `unsigned long int`, and then use printf
 * to output the number. if the value is too large to be contained within the
 * given c type, print `C unsigned long int overflow\n`
 *
 * resource: `longintrepr.h`
 *
 * allowed macros and functions
 *     c standard library
 *     PyLong_SHIFT`
 *     PyLong_Check`
 */

/**
 * print_python_int - if possible, extract and output the integer value from
 * the given PyObject
 * @pyint: the PyObject to parse and analyse as an 'unsigned long int'
 *
 * error messages:
 * "C unsigned long int overflow"
 * "Invalid Int Object"
 */

void print_python_int(PyObject *pyint)
{
	unsigned long int value;
	int overflow = 0;

	if (PyLong_Check(pyint))
	{
		value = PyLong_AsLongAndOverflow(pyint, &overflow);
		if (overflow)
		{
			value = PyLong_AsLongAndOverflow(pyint, &overflow);
			printf("C unsigned long int overflow\n");
		}
		else
			printf("%ld\n", value);
	}
	else
		printf("Invalid Int Object\n");
}
