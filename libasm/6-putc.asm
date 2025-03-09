BITS 64

; INSTRUCTIONS:
; 'call' is NOT allowed
; write a procedure that print a single character to stdout
; return the total number of bytes written
; only ONE 'syscall' is permitted
;
; prototype: size_t asm_putc(int c);
;
; MAN (3): this implementation differs from clib's
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_putc
asm_putc:

	mov rcx, 0
	copy:
		cmp rcx, rdx
		jge conclude

		mov al, byte [rsi + rcx]

		cmp al, 0
		je conclude

		mov [rdi + rcx], al

		inc rcx
		jmp copy

	conclude:
		mov rax, rdi
		ret
