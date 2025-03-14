# C - Signals

- [signal](https://en.wikipedia.org/wiki/Signal_%28IPC%29)
- [asynchrony](https://en.wikipedia.org/wiki/Asynchrony_%28computer_programming%29)
- [glibc: signal sets](https://www.gnu.org/software/libc/manual/html_node/Signal-Sets.html)

- `signal (7)`
- `signal (2)`
- `sinaction (2)`
- `kill (2)`

## objectives

- what is a signal ?
- why do they exist ?
- when are they delivered and by whom ?
- what are the default actions of signals ?
- how to set up a handler for a signal ?
- how to send signals ?
- what signals can't be caught ?

## requirements

- gcc compilation will be done with the `-Wall -Werror -Wextra -pedantic` flags
- code and documentation should be betty compliant
- no more than five functions per file will be permitted
- all declarations of all functions should be included in the `signals.h` header
  file
- all header files should be include guarded

## libc and syscalls

unless specified otherwise, use of the c standard library is allowed
