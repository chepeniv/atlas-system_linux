# 0. step #0 - `syscall` number

write a program that executes and traces a given command

usage: `./strace_0 command [args...]`

- for every intercepted system call, print its number followed by a newline
- there's no need to handle the `PATH`: `command` will be given as a full path to a binary
- the `Makefile` must implement a `strace_0` rule

# 0. step #1 - `syscall` name

write a program that executes and traces a given command

usage: `./strace_1 command [args...]`

- for every intercepted system call, print its name followed by a newline
- no need to handle the `PATH`: `command` will be given as a full path to a binary
- the `Makefile` must implement a `strace_1` rule

# 0. step #2 - Return value

write a program that executes and traces a given command

usage: `./strace_2 command [args...]`

- for every intercepted system call, print its name and it's return value in
hexadecimal, followed by a newline
- no need to handle the `PATH`: `command` will be given as a full path to a binary
- the `Makefile` must implement a `strace_2` rule
- **NOTE**: it is impossible to retrieve the last system call's return value,
since it doesn't actually return. therefore, just print `?` as `strace` does
