BITS 64

; for the as/gas assemblers add the directives
; .intel_syntax noprefix
; .intel_mnemonic

; syscall defs
;     /usr/include/asm/unistd_64.h

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning
SECTION .note.GNU-stack

SECTION .text

global asm_dbl
asm_dbl:
	add rdi, rdi
	mov rax, rdi
	ret
