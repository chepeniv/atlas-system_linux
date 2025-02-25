# C - ELF: readelf

- [Wikipedia: ELF](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
- [ELF: Understanding & Analysis](https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/)
- `man 5 elf`
- `man 1 readelf`
- `/usr/include/elf.h`

## Objectives

- what is the ELF format ?
- what kind of files are in the ELF format ?
- what are the different parts of an ELF file ?
- what information is present in the file header ?
- what information is present in the sections header table ?
- what information is present in the program header table ?
- how to parse an ELF file using C structures ?

## Requirements

- programs will be compiled with the `-Wall -Werror -Wextra -pedantic` flags
- no more than five functions per file
- all headers should be include-guarded
- `README.md` at the root of the project is mandatory
- _all_ C source files in all directories must be Betty-compliant

### Permitted functions and syscalls

- unless specified otherwise, use of the C standard library is allowed
- `system` (3) in NOT allowed
- `exec*` (2 and 3) in NOT allowed

### Testing

- handle both 32 and 64 bit ELF files
- handle both little and big endian ELF files
- handle all types of ELF files
