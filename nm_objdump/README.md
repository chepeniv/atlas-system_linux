# ELF: nm/objdump

- [Executable and Linkable Format](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
- [stevens ELF](https://stevens.netmeister.org/631/elf.html)
- [cmu elf](https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/docs/elf.pdf)

- `/usr/include/elf.h`
- `man 5 elf`
- `man 1 nm`
- `man 1 objdump`

## objectives

- what is the ELF format ?
- what are the `nm` and `objdump` commands ?
- how to properly use them ?
- how to parse the content of an ELF file ?
- what information can be extracted from an ELF file ?
- what are the differences between `nm` and `objdump` ?

## requirements

- the compilation flags used are `-Wall -Werror -Wextra -pedantic`
- code must be Betty compliant
- no more than five functions per file
- all headers should be include-guarded

### functions and syscalls

- unless specified otherwise use of glibc is allowed
- `system` (3) is not permitted
- `exec*` (2 and 3) are not permitted

### test

- handle both 32-bit and 64-bit ELF files
- handle both little and big endian ELF file
- handle all types of ELF files

# task

## 0. nm (12 pts)

write a copycat of the `GNU nm` command

- usage: `hnm [objfile ...]`
- the output must be the exact same as `nm -p`
- everything must be compiled and linked using a `Makefile`
- the Makefile must define the `hnm` rule that compiles the needed sources in
  order to create the `hnm` executable

### checks

- README is present and not empty
- file is present
- make `hnm`
- correct output - `netbsd32`
- correct output - `solaris32`
- correct output - `sortix32`
- correct output - `sparcbigendian32`
- correct output - `ubuntu64`
- correct output - `jpeg.mod`
- correct output - `python.obj`
- correct output - `libperl.so.5.18`
- correct output - `sftp-server`
- correct output - `vgpreload_memcheck-x86-linux.so`
- Betty coding style (recursive)
- Betty documentation style (recursive)
