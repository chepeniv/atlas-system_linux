# x86 Assembly - libASM

- [concept: x86-64 Assembly](https://intranet.atlasschool.com/concepts/924)
- [wikipedia: x86-64 Assembly](https://en.wikipedia.org/wiki/X86_assembly_language)
- [wikipedia: x86 registers](https://en.wikipedia.org/wiki/X86#x86_registers)
- [wikibook: x86 Architecture](https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture)

## objectives

- what is the difference between `Intel` and `AT&T` syntaxes
- what are the different x86 GPR
- what are the different flag registers
- what is the stack frame
- how to setup a stack frame
- how to call a function
- how to make a system call
- how to pass parameters to a function
- how to retrieve parameters

## requirements

- `ASM` programs and functions will be compiled with `NASM` v 2.14.02 and
  the added `-f elf64` flag
- prototypes for all functions should be included in the `libasm.h` header
- include-guard your headers

### functions and syscalls

no lib or sys calls are allowed -- specifically, `call` and `syscall`
instructions are prohibited

## configuration

### vim config:

if using the ALE plugin

```vim
let g:asmsyntax = 'nasm'
let g:ale_linters = {'asm': ['nasm']}
```
