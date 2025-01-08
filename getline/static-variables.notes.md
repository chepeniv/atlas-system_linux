# static variables in c

static variables preserve their value outside of their scope. thus they don't
need to be reinitialized within a new scope.

syntax:
```c
static data_type var_name = var_value;
```

they offer persistence across function calls

# points of interest

static `int` variables remain in memory throughout the lifetime of a program.
basic variables are destroyed after a function returns.

regardless of the flow of logic, static variables are only ever initialized
once

static variables are allocated in the data segment and not the stack segment

if not initialized explicitly, static variables will default to a value of `0`.
in contrast to typical variables which will reference garbage if not initialized
explicitly.

static variables can only ever be initialized with constant literals. therefore,
any runtime calculation to determine their value will not be permitted.
(**note**: in `c++`, this is allowed)

static global variables and functions are also possible. their purpose is to
limit the scope only to a single file [(static functions in c)](https://www.geeksforgeeks.org/what-are-static-functions-in-c/)

static variables **should NOT** be declared within a structure, since the c
compiler requires the entirety of the structure to be stored together typically
via memory allocation. this allows the structure remain contiguous in memory.

structures may be declared withing a function which would place them on the
stack. if memory is allocated dynamically for them, then that would place them
in the heap. if they are global, that would place them within data or BSS.

whichever the case, elements of a structure are accessed via offsets. separating
out the various elements in memory would defeat the purpose of a structure, yet
structures themselves can be set as static
