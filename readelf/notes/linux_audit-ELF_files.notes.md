# Linux ELF Files: Understanding And Analysis

source : https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/
by : Michael Boelen

- why is ELF used and for what kind of file ?
- what is the structure of an ELF file ?
- how to read and analyse an ELF file ?
- what tools can be used for binary analysis ?

# What Is An ELF File

- it defines the structure of binaries, libraries, and core files
- allows an operating system to interpret the machine instructions
  correctly
- these are typically the output of compilers and linkers

## Details

- comprehending the ELF format helps to understand the workings of an
  operating system
- it helps in identifying what goes wrong and why
- being able to parse ELF data also aids sniffing out
  suspicious files

## From Source To Process

any operating system needs to be able to translate functions in to the
language of the CPU

compilers translate a programming language into object code; which is then
linked together into a full binary file

# Anatomy Of An ELF File

ELF files are also commonly used for object files (partial pieces),
shared libraries, and core dumps.

## Structure

given the extensible specification, the structure of an ELF file varies
case-by-case.

the two main components are the **ELF header** and the **File data**

### ELF Header

the section is mandatory. it ensures data is correctly interpreted

typical header fields :

Class
- this value determines the (32/64bit) architecture of the file

Data
- this field determines the endianess (LSB/MSB) of the file, to further parse
  the remainder -- this is crucial as different processors deal differently
  with incoming instructions and data structures

OS/ABI
- the Application Binary Interface (ABI) determines the correct set of
  instructions that the OS supports

Machine
- denotes the expected machine type (typically a processor)

Type
- denotes the purpose/role of the current file - common types:
	- (4) CORE
	- (3) DYN - shared object file (library)
	- (2) EXEC - executable (binary)
	- (1) REL - relocatable (before linkage)

### File Data

three additional parts may be included as well:
- **Program Headers** (Segments)
- **Section Headers** (Sections)
- **Data**

ELF files have two "views". the first is used by the linker to incorporate
segments (this seems inaccurate). the other categorizes instructions and data (sections).

### Program Headers

an ELF file may posses zero or more segments which describe how to create a
process/memory image for runtime execution. the kernel uses the segments to
properly map the virtual address space via the `mmap` syscall.

#### GNU_EH_FRAME

this is a sorted queue used by gcc. it stores exception handlers. when
something goes wrong, this area is used to deal with problems correctly

#### GNU_STACK

this header stores stack information. the stack is an LIFO data structure that
keeps track of the running functions -- stacks themselves are not executable as
this would be too much of a security risk.

if the GNU_STACK segment is not available, then an executable stack may be used.
`scanelf` and `execstack` can be used to analyze stack details

### Elf Sections

this defines the sections. it is used for linking and relocation. these are
created after the compiler turns c into assembly and assembled into an object

a _segment_ can have zero or more _sections_. for executables there are four
main sections `.text`, `.data`, `.rodata`, and `.bss`. each of which is loaded
with different access rights

#### .text

contains executable code. it is packaged into a segment with read and execute
access rights. it is loaded once and it's contents don't change.

#### .data

initialized data with read and write access rights

#### .rodata

initialized data with read access only (A)

#### .bss

uninitialized data with read and write access rights (WA)

#### analysis

- `dumpelf`
- `elfls -p`
- `eu-readelf --section-headers`
- `readelf -S`
- `objdump -h`

#### section groups

sections may be grouped together given their inter-dependency. this is only
supported by newer linkers

## Static Vs Dynamic Binaries

ELF files may be either static or dynamic which refers to the `included`
libraries. that is, dynamic ELF files need to load in external components to
run correctly. on the other hand, static ELF files have all libraries included
within, and although larger they are more portable.

# Tools For Binary Analysis

some analysis toolkits allow for reverse engineering binaries.

with **static analysis** files are inspected without actually executing them.
afterwards, **dynamic analysis** is used to run _samples_ and examine their
behaviour.

**Radare2** used in reverse engineering

## Software Packages

- `binutils`
- `elfutils`
- `elfkickers`
- `pax-utils`
- `prelink`

# FAQ

what is abi ?
- specifies the low-level interface between the operating system and an
executable

what is elf ?
- a formal specification that outlines how instructions are stored

# Conclusion

- segments are handled by the kernel and mapped into memory via `mmap`
- sections are handled by the linker to compose an executable or shared object
- headers are critical components for parsing an ELF file
