BITS 64

; for the as/gas assemblers add the directives
; .intel_syntax noprefix
; .intel_mnemonic

; syscall defs
;     /usr/include/asm/unistd_64.h

SECTION .rodata

SECTION .text

global asm_add
asm_add:
	mov rax, rdi
	add rax, rsi
	ret
