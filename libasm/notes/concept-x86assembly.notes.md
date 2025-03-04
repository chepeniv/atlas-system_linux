# ATLAS INTRANET CONCEPT: X86-44 ASSEMBLY

- [0x09-libasm_concept](https://github.com/hs-hq/0x09-libasm_concept)
- [wikipedia: prcessor register](https://en.wikipedia.org/wiki/Processor_register)
- [youtube: function stack](https://www.youtube.com/watch?v=KRaJoeVXF_8)

## intro

here we'll manipulate data with x86 assembly using registers, instructions, and
the stack. furthermore, we'll also control the flow of logic using loops and
conditions

### environment

the toolset: linux, ubuntu, nasm, and gcc

assembly syntax: x86, 64bit, intel

## assembly to elf file

the steps to transform a c file into an elf executable
- preprocessing - comment removal, macro replacement, include headers...
- compilation - c to assembly
- assembly - create object file
- linking - link object files together into an executable

in working with assembly code, we'll only use the last two steps. gcc will be
used for linking

to create an object file from assembly run `nasm -f elf64 <file.asm>`

## registers

declaring and using variables is not possible in assembly. for basic arithmetic,
an array of registers are provided. to save a value for later use push it to
the stack before calling any other function that could overwrite it.

some cpu registers play a specific role while others are free to the user. the
availability of registers is processor dependent.

### general purpose registers (gpr)

although 16 of these are provided, because some handle specific roles the might
hold values you wont want to override

registers are designed to be used with specific sizes depending on the values
handled by the instructions -- that is, values given to instructions have to
match the registers provided

```
64, 32, 16,8, 8
RAX|EAX|AX[AH|AL] RSI|ESI|SI|SIL R8 |R8D |R8W |R8B  R12|R12D|R12W|R12B
RBX|EBX|BX[BH|BL] RDI|EDI|DI|DIL R9 |R9D |R9W |R9B  R13|R13D|R13W|R13B
RCX|ECX|CX[CH|CL] RBP|EBP|BP|BPL R10|R10D|R10W|R10B R14|R14D|R14W|R14B
RDX|EDX|DX[DH|DL] RSP|ESP|SP|SPL R11|R11D|R11W|R11B R15|R15D|R15W|R15B
```

### gpr specific roles

- `RAX` - holds the return value of functions and system calls
- `RSP` - holds the stack pointer and is automatically updated every time
  something is pushed/popped from the stack. it is used implicitly by PUSH, POP,
  CALL, RET, ENTER, LEAVE...
- `RBP` - holds the current stack frame pointer although it is never
  automatically updated. used implicitly by ENTER and LEAVE
- `RCX` - used as a counter for loop and string instructions
- `RSI` - used the source pointer for string instructions
- `RDI` - used the destination pointer for string instructions

### other registers

```
64     32     16     64  32  16  80  64    128   16...
RFLAGS|EFLAGS|FLAGS  RIP|EIP|IP  STn|MMXn  XMMn (CS, DS, ES FS, GS)
```

- `RFLAGS` - used for conditional jumps
- `RIP` - stores the current instruction pointer
- `ST0...7` - store legacy 80bit floating point numbers
- `MMX0...7`(64bit) - store vectorial instructions
- `XMM0...15`(128bit) - store vectorial instructions
- segment registers for operating system instructions

### flags

most instructions set flags
- `CF` - unsigned carry (integer overflow)
- `0F` - signed overflow
- `ZF` - zero (null)
- `SF` - sign (negativity, leftmost bit = 1)
- `PF` - parity (evenness, rightmost bit = 0)

## instructions

in x86 assembly, all instructions and directives are case-insensitive, and
indentation and blank lines don't matter

### assembly directives

comments are set-off by semicolons:
```asm
; this is an x86 asm comment
```

the architecture is denoted by the following the start off the file:
```asm
BITS 64
```

sections within the file are demarcated by `SECTION`:
```asm
SECTION .secname
; asm code is written within sections

SECTION .data
; static data is declared here

SECTION .rodata
; read-only static data is declared here
```

anchor pointns within the asm file are mark as:
```asm
anch: ; this is a position which can be jumped to
      ; although they aren't functions they can be conceptualized as such
```

to mark a symbol as visible to external files use:
```asm
GLOBAL label_a ; this makes 'label_a' callable
```

to import a symbol use:
```asm
EXTERN label_a
; this is only available if 'label_a' has already been exported with 'GLOBAL'
```

declare static data with:
```asm
hello DB "hello world", 0Ah, 0
; "hello world" followed by a newline (0A hexa) and \0
```

### static sections

these can be analyzed with `nm` and `objdump`
```asm
SECTION .text  ; code
SECTION .ronly ; read-only data
SECTION .data  ; read/write data
SECTION .bss   ; uninitialized data
```

### instruction syntax

the order of the parameters is particular to the instruction
formats:
```
INSTR SRC DEST
INSTR DEST SRC
SRC
```
`SRC` denotes a value stored within the specified address or register\
`DEST` denotes a target address or register\
both arguments CANNOT be memory simultaneously

type is determined from "other parameter" if available or specified explicitly
with a prefix:
```asm
BYTE  ;  8 bit
WORD  ; 16 bit
DWORD ; 32 bit a double word
QWORD ; 64 bit a quadruple word
```

```asm
; examples
ADD RAX, RDX ; RAX = RAX + RDX
             ; where the RAX reg is the dest and RDX is the src

ADD RAX, 12  ; here 12 is a direct value
```

### memory access

for an address denoted as `[c + reg1 + reg2 * k]` c is an explicit constant, reg
is a general-purpose register and k is a coefficient power of two (1, 2, 4, or
8). these all are optional.
```asm
; examples ;
MOV RDX, [RBX + RCX * 4]
    ; move the 64 bits at address RBX + RCX * 4 into RDX

MOV BYTE [RDI + 1337], 98
    ; move the 8bit value 98 into the address [RDI + 1337]
```

### main instructions

- data movement: `MOV`, `XCHG`, `PUSH`, `POP`
- type conversion:
	- `CBW`: byte to word
	- `CWD`: word to double
	- `CWQ`: double to quad
- arithmetic:
	- `NEG`: two's complement negation
	- `INC`: increment
	- `DEC`: decrement
	- `ADD`: addition
	- `SUB`: subtraction
	- `IMUL`: signed multiply
	- `MUL`: unsigned multiply
	- `IDIV`: signed integer division
	- `DIV`: divide
- bitwise:
	- `NOT`: one's complement negation
	- `AND`: logical AND
	- `OR`: inclusive logical OR
	- `XOR`: exclusive OR
- bitshifts:
	- `SHL`: logical left shift
	- `SHR`: logical right shift
	- `SAL`: arithmetic left shift
	- `SAR`: arithmetic right shift
	- `ROL`: rotate left
	- `ROR`: rotate right
- set flags:
	- `CMP`: compare
	- `TEST`: test for bit pattern

### branching

these are used to move the current instruction pointer
- `JMP`: unconditional jump
- conditional jumps depend on `RFLAGS`
- `CALL <label>`: call the function at label
	- this is equivalent to `PUSH RIP` + `JMP <label>`
- `RET` is equivalent to `POP RIP`
- `SYSCALL` kernel interface for system calls

## memory

instructions are provided registers to be able to manipulate data. in order for
data to be saved it must be push onto the stack which needs to be setup
whenever entering a function and restored when leaving a function

### stack

this part of memory grows downwards and encodes the function's state. `RSP`
points to the top of the stack. `RBP` holds the frame pointer -- the beginning
of local variables.

### stack frame setup

although `RSP` varies with pushes and pops, `RBP` remains fixed. the simplest
way to access local variables is to calculate `RBP - c`

- function prologue: `PUSH RBP` and `MOV RBP, RSP` are carried out by `ENTER`
- function epilogue: `MOV RSP, RBP` and `POP RBP` are carried out by `LEAVE`

## functions and system calls

### function calling

to call a function in assembly setup its parameters first. the first six
integers and pointers have to be stored in order in RDI, RSI, RDX, RCX, R8, and
R9. the first eight floating point numbers go in XMM0...7. all the remaining
parameters go to the stack.

for variadic functions the number of FPN params has to be stored in RAX

RBP, RBX, R12, R13, R14, and R15 must be preserved by the callee. any other
registers may be altered at will

return values are placed in RAX (int, pointer) or XMM0 (FPN)

use `CALL <func>` to call a function

### system call

the calling convention for sys-calls are slightly different

the same registers are used for parameters, except for the fourth which is
placed in R10 rather than RCX

sys calls don't take floating-point values

the system call number is placed in RAX

RCX and R11 may be overwritten

the desired syscall is then initiated with `SYSCALL`

the return value is placed in RAX. errors are encoded by negative numbers -1
... -4095

----

## exercises

1. add me
2. swap
3. print alphabet

