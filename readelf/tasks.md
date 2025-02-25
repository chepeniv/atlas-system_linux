# Tasks

## 0. ELF File Header (12pts)

**files** : `Makefile`

**description** : write a program that displays information contained in the
`ELF file header`. handle various operating systems and architectures. the
`stdout`, `stderr`, and status should be exactly the same as in `readelf -W -h`

**usage** : `./0-hreadelf elf_flie`

**makefile** :
- rule: `0-hreadelf`
- target: `0-hreadelf` executable

**example** :
```
$ ./0-hreadelf ubuntu64
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x400600
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6936 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 28
```

## 1. ELF Sections' Headers (12pts)

**files** : `Makefile`

**description** : write a program that displays information contained in the
`ELF sections' headers`. handle various operating systems and architectures.
the `stdout`, `stderr`, and status should be exactly the same as in
`readelf -W -S`

**usage** : `./1-hreadelf elf_flie`

**makefile** :
- rule: `1-hreadelf`
- target: `1-hreadelf` executable

## 2. ELF Program Headers (12pts)

**files** : `Makefile`

**description** : write a program that displays information contained in the
`ELF program headers`. handle various operating systems and architectures.
the `stdout`, `stderr`, and status should be exactly the same as in
`readelf -W -l`

**usage** : `./2-hreadelf elf_flie`

**makefile** :
- rule: `2-hreadelf`
- target: `2-hreadelf` executable
