# Navigating Elf File `struct`'s

## Definitions

```c
typedef struct {
	unsigned char e_ident[EI_NIDENT];
	uint16_t      e_type;
	uint16_t      e_machine;
	uint32_t      e_version;
	ElfN_Addr     e_entry;
	ElfN_Off      e_phoff;
	ElfN_Off      e_shoff;
	uint32_t      e_flags;
	uint16_t      e_ehsize;
	uint16_t      e_phentsize;
	uint16_t      e_phnum;
	uint16_t      e_shentsize;
	uint16_t      e_shnum;
	uint16_t      e_shstrndx;
} ElfN_Ehdr;

typedef struct {
	uint32_t   sh_name;
	uint32_t   sh_type;
	uint64_t   sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off  sh_offset;
	uint64_t   sh_size;
	uint32_t   sh_link;
	uint32_t   sh_info;
	uint64_t   sh_addralign;
	uint64_t   sh_entsize;
} Elf64_Shdr;

typedef struct {
	uint32_t      st_name;
	unsigned char st_info;
	unsigned char st_other;
	uint16_t      st_shndx;
	Elf64_Addr    st_value;
	uint64_t      st_size;
} Elf64_Sym;
```

## Variables and Values:

```c
uint64_t
	sym_count    = sect_headers->sh_size / sizeof(Elf64_Sym);

Elf64_Ehdr *
	entry_header;

Elf64_Shdr *
	sect_headers = entry_header + entry_header->e_shoff;

Elf64_Shdr *
	sym_header   = sect_headers + incr;

Elf64_Sym * /*incr to access other symbols */
	sym_table    = entry_header + sym_header->sh_offset;

char *
	str_table    = entry_header + sect_headers + sym_header->sh_link;

char *
	sym_str      = str_table + sym_table->st_name;

long int
	sym_val      = sym_table->st_value;

```
