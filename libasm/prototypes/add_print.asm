BITS 64

; COMPILATION
; nasm -f elf64 add_print.asm
; gcc add_print.o
;
; RUN
; ./a.out

; DEFAULT REL ; use this to not explicitly declare addressing mode each time

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning

SECTION .rodata

format_str db "%d", 0xA, 0

SECTION .text

extern printf

global main
main:

	mov rsi, 8
	add rsi, 7
	lea rdi, [rel format_str]

	push rbp
	call printf wrt ..plt
	pop rbp

	mov rax, 60
	mov rdi, 0
	syscall

