# introduction

`strace` is a tool capable of intercepting both system calls made and signals
received by a running process it gets attached to. it can retrieve all
information about `syscalls` made (`params`, `return` val, etc.)

# intercepting syscalls

the single syscall `ptrace` (process trace) can "trace" the entirety of a
running process. it is a powerful interface with the ability to control another
process. it can interrupt and resume a target process as well as obtain and
modify information about its stack, memory, and registers.

it's great for debugging!

carefully read `man 2 ptrace` before using it.

# practice

there are two ways of tracing a process

- `PTRACE_ATTACH` -- trace a running process by specifying it's PID
- `PTRACE_TRACEME` -- is called by a 'tracee' to indicate that it should be
traced by it's parent

`strace` can be used in two different ways: either by giving it a command to
execute and trace, or by giving it a PID of an already running process

## exercise 0

usage: `./ex_0 binary_to_trace`

fork and do the following:

- within the child process: call `ptrace` with the request `PTRACE_TRACEME` and
  use `execve` to execute the given binary
- within the parent: wait for the child and trace using `ptrace` in a loop with
  the request `PTRACE_SINGLESTEP`. print `single step` at each iteration. print
  the tracee exit status when done

`PTRACE_SINGLESTEP` suspends the tracee every time the register `ip` changes,
which is the instruction pointer holding the address of the current bytecode to
be executed.

## exercise 1

the `PTRACE_SYSCALL` request needs to be called twice for every syscall made by
the tracee

write a simple program which will execute the same as the last, but this time
try to use `PTRACE_SYSCALL`, and print 'syscall' whenever syscall is made and
'return' when syscall returns

`PTRACE_SYSCALL` suspends the tracee every time a syscall is made, not every
step

## exercise 2

`ptrace` can retrieve a tracee's register values with the request
`PTRACE_GETREGS` which is useful for obtaining the parameters and return value
of syscalls made

write a program that prints the syscall number whenever a syscall is made

## going further

to get the name of a syscall from its number parse the file
`/usr/include/asm/unistd_64.h`
