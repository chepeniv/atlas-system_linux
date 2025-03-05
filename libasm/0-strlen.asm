BITS 64
; build:
;   nasm -f elf64 -g -F dwarf hello.asm
; link:
;   ld hello.o -o hello.x
; vim config:
;   let g:asmsyntax = 'nasm'
;   let g:ale_linters = {'asm': ['nasm']}

SECTION .rodata

SECTION .text

global _start
_start:

	; call exit(0);
	mov eax, 1
	mov ebx, 0
	int 0x80
