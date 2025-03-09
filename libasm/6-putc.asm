BITS 64

; INSTRUCTIONS:
; 'call' is NOT allowed
; write a procedure that print a single character to stdout
; return the total number of bytes written
; only ONE 'syscall' is permitted
;
; prototype: size_t asm_putc(int c);
;
; MAN (3): this implementation differs from glibc's
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_putc
asm_putc:

	push rdi     ; mov val in rdi to the stack
				 ; rsp changes accordingly

	mov rdi, 1   ; fd = stdout
	mov rsi, rsp ; addr = stack pointer
	mov rdx, 1   ; 1 byte

	mov rax, 1   ;   rax(rdi, rsi,  rdx);
	syscall      ; write(fd,  addr, len);

	pop rdi      ; pop val from stack and restore rsp
	ret
