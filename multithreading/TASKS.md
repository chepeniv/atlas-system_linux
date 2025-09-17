# TASKS

# 0. thread entry point

`0-thread_entry.c`

create a function that serves as the entry point into a new thread

prototype: `void *thread_entry(void *arg);`
- `arg` holds the address of a string, followed by a newline, that must be
printed

- respect the order of in which strings are printed out in the given examples

# 1. thread logger

`1-tprintf.c`

create a function that uses any `printf` function to output a given formatted
string

prototype: `int tprintf(char const *format, ...);`
- output must be preceded by the calling thread ID

# 2. --

# 3. --

# 4. thread logger v2

create a function that uses any `printf` function to output a given formatted
string

you must use a `mutex` to avoid race conditions,

a `mutex` needs to be initialized and destroyed, but without having to do that
in our main.c

reference: [constructors and destructors with GCC]()

prototype: `int tprintf(char const *format, ...);`

- output must be preceded by the calling thread ID
- tip: You are allowed to use global variables
	- run Betty with `--allow-global-variables`

tip: compile with the first version of `tprintf` to demonstrate the consequence
of a race condition

# 5. number to prime factors

create a functions that factorizes a number into a list of prime numbers

prototype: `list_t *prime_factors(char const *s);`
- `s` is the string representation of of the number to factorize
	- this number will be positive and fit into an `unsigned long`
- code will be compiled with the file `list.c`
- **note**: this task does not require multithreading and will not be linked to
the `pthread` library

# 6. number to prime factors v2

reproduce the previous task, and improve it with a thread pool to execute a list
of tasks.

in the same file, write three functions:

## Create task

- prototype: `task_t *create_task(task_entry_t entry, void *param);`
	- `entry` is a pointer to the entry function of the task,
	- `param` is the parameter that will later be passed to the entry function
	- return a pointer to the created task structure

## Destroy task

- prototype: `void destroy_task(task_t *task);`
	- `task` is a pointer to the task to destroy

## Execute task list - Thread entry

- prototype: `void *exec_tasks(list_t const *tasks);`
	- `tasks` is a pointer to the list of tasks to be executed
	- serves as a thread entry
	- can safely return NULL as its return value will not be retrieved
	- go through the list of tasks and execute them
	- multiple threads will be going through the list of tasks, and a task must
	only be executed once
	- use `tprintf` to print when a task is started, and completed

