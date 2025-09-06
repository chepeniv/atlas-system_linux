# `C - STRACE`

## Resources

- [intranet: strace](resources/intranet-concept-strace.pdf)
- [intranet: x86-64 assembly](resources/intranet-concept-x86-64_assembly.pdf)
- [system call tracing](resources/meng_ptrace_slides.pdf)
- [man: ptrace](resources/ptrace.man.txt)
- [man: strace](resources/strace.man.txt)

## Objectives

- what is strace and its purpose ?
- what is ptrace and the possibilities it offers ?
- what are the differences between `PTRACE_SINGLESTEP` and `PTRACE_SYSCALL` ?
- how to read from or write to the memory of a traced process

## Requirements

- programs and functions will be compiled with `gcc 9.4.0 -Wall -Werror -Wextra -pedantic`
- `c` code must be `Betty` compliant
    - it will be checked with `betty-style.pl` and `betty-doc.pl`
- **global variables are not allowed**
- **no more than five functions per file**
- use of the standard library is *allowed*
- all header files should be include guarded

## Info

- note: values given in the examples may be specific to the local machine

you're required to parse `/usr/include/asm/unistd_64.h` as well as `unistd_32.h`
in order to obtain the number corresponding to each system call. to get
information about syscall's prototypes, man-scraping will be necessary as well.
for this a header file has been provided. this permits you to focus on the
`ptrace` portion of this project. note, you're completely allowed to use your
own data structures as well as to modify the provided header file

