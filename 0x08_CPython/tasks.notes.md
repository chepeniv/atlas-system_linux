# tasks

## 0. Lists big O (12 pts)

files: `0-python_lists_bigO`

write big O notations for the following list of operations -- one per line, in
the order given:

- L01 - list item assignment: `alist[idx] = val`
- L02 - append to list: `alist.append(val)`
- L03 - concatenate a list of n elements: `alist + blist`
- L04 - insert on item in list: `alist.insert(pos, val)`
- L05 - remove element from list: `alist.remove(val)`
- L06 - remove and return last list item: `alist.pop()`
- L07 - pop an element at given position: `alist.pop(pos)`
- L08 - clear a list: `alist.clear()`
- L09 - measure a list: `alist.count()`
- L10 - sort a list: `alist.sort()`
- L11 - reverse a list: `alist.reverse()`
- L12 - delete a list: `del alist`

## 1. CPython #0: Python lists (13 pts)

files: `1-python.c`

Cpython is the reference implementation of the Python programming language. it
allows us to "look under the hood" of python.

create a c function that prints some basic info about python lists.

- prototype: `void print_python_list(PyObject *pylist);`
- compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,
  -soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.9 1-python.c`

### resources

- `listobject.h`
- `object.h`
- [c-api: structures](https://docs.python.org/3.4/c-api/structures.html)
- [c-api: list](https://docs.python.org/3.4/c-api/list.html)

## 2. CPython #1: PyBytesObject (15 pts)

files: `2-python.c`

create two c functions that print some basic info about python lists and python
byte objects

- compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared
  -Wl,-soname,libPython.so  -o libPython.so -fPIC
  -I/usr/include/python3.9 2-python.c`
- prohibited macros and functions:
	- `Py_SIZE`
	- `Py_TYPE`
	- `PyList_GetItem`
	- `PyBytes_AS_STRING`
	- `PyBytes_GET_SIZE`

### python lists:

- prototype: `void print_python_list(PyObject *pylist);`

### python bytes:

- prototype: `void print_python_bytes(PyObject *pybytes);`
- print a maximum of 10 bytes
- if `pybytes` is not a valid `PyBytesObject` print an error message
- resource: `bytesobject.h`

## 3. CPython #2: PyFloatObject (17 pts)

files: `3-python.c`

create three c functions that print some basic info about lists, python bytes,
and python float objects

- you're allowed to use the c standard library
- compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,
  -soname,libPython.so  -o libPython.so -fPIC
  -I/usr/include/python3.9 3-python.c`
- prohibited macros and functions:
	- `Py_SIZE`
	- `Py_TYPE`
	- `PyList_Size`
	- `PyList_GetItem`
	- `PyBytes_AS_STRING`
	- `PyBytes_GET_SIZE`
	- `PyBytes_AsString`
	- `PyFloat_AS_DOUBLE`
	- `PySequence_GetItem`
	- `PySequence_Fast_GET_SIZE`
	- `PySequence_Fast_GET_ITEM`
	- `PySequence_ITEM`
	- `PySequence_Fast_ITEMS`
- python scripts will be ran with the `-u`
- use either `setbuf(stdout, NULL)` or `fflush(stdout)` if using `printf` since
  since python's `print` and libc's `printf` don't share the same buffer which
  may cause the output to become disordered

### python lists:

- prototype: `void print_python_list(PyObject *pylist)`
- if `pylist` is not a valid `PyListObject` print an error message

### python bytes:

- prototype: `void print_bytes(PyObject *pybytes)`
- if `pybytes` is not a valid `PyBytesObject` print an error message

### python float:

- prototype: `void print_float(PyObject *pyfloat)`
- if `pyfloat` is not a valid `PyFloatObject` print an error message
- resource: `floatobject.h`

## 4. CPython #3: Python Strings (14 pts)

files: `4-python.c`

create a function that prints python strings

- prototype: `void print_python_string(PyObject *pystring)`
- if `pyfloat` is not a valid string print an error message
- resource: [python unicode](https://docs.python.org/3.9/howto/unicode.html)

- you're allowed to use the c standard library
- compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,
  -soname,libPython.so  -o libPython.so -fPIC
  -I/usr/include/python3.9 4-python.c`

## 5. CPython Integers (12 pts)

files: `5-python.c`

create a c function that prints python integers

- prototype: `void print_python_int(PyObject *pyint)`
- if `pyfloat` is not a valid string print an error message
- translate the python `int` to a C `unsigned long int`, and then use printf to
  output the number. if the value is too large to be contained within the given
  c type, print `C unsigned long int overflow\n`
- resource: `longintrepr.h`

- you're allowed to use the c standard library
- allowed macros and functions
	- `PyLong_SHIFT`
	- `PyLong_Check`
- compilation: `gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,
  -soname,libPython.so  -o libPython.so -fPIC
  -I/usr/include/python3.9 5-python.c`
