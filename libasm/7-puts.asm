BITS 64

; INSTRUCTIONS:
;
; write a procedure that prints a string to stdout
; return the total number of bytes written
;
; NO jump instructions permitted
; only ONE 'call' to 'asm_strlen' is permitted
; only ONE 'syscall' is permitted
;
; prototype:
;     size_t asm_puts(const char *text);
;
; MAN (3):
; the implementation of this version might differ from glibc's
; which adds a trailing newline at the end and whose return might
; differ as well
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

extern asm_strlen

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_puts
asm_puts:

	call asm_strlen

	mov rsi, rdi
	mov rdi, 1
	mov rdx, rax

	mov rax, 1
	syscall

	ret
