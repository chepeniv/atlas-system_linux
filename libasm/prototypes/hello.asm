BITS 64

; for the as/gas assemblers add the directives
; .intel_syntax noprefix
; .intel_mnemonic
;
; build:
;     nasm -f elf64 -g -F dwarf hello.asm
;
;     '-F dwarf' specifies the debug information format
;     '-g' generates debug information
; link:
;     ld hello.o -o hello.x
;
; for the 'dense-analysis/ale' plugin on neovim to work with the nasm syntax
; add the following to your vim .config file
;     let g:asmsyntax = 'nasm'
;     let g:ale_linters = {'asm': ['nasm']}
;
; syscall defs
;     /usr/include/asm/unistd_64.h

SECTION .rodata

hello db "hello, world :)", 0x0A, 0
hlen equ $ - hello

SECTION .text

global _start
_start:

	; call write(1, hello, hlen);
	mov eax, 4
	mov ebx, 1
	mov ecx, hello
	mov edx, hlen
	int 0x80

	; call exit(0);
	mov eax, 1
	mov ebx, 0
	int 0x80
