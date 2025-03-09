BITS 64

; INSTRUCTIONS:
; 'call' is NOT allowed
; write a procedure that prints a string to stdout
; return the total number of bytes written
; only one 'call' to 'asm_strlen' is permitted
; only ONE 'syscall' is permitted
; NO jump instructions permitted
;
; prototype: size_t asm_puts(const char *text);
;
; MAN (3):
; the implementation of this version might differ from glibc's
; which adds a trailing newline at the end and whose return might
; differ as well
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_puts
asm_puts:

	push rdi     ; mov val in rdi to the stack
				 ; rsp changes accordingly

	mov rdi, 1   ; fd = stdout
	mov rsi, rsp ; addr = stack pointer
	mov rdx, 1   ; 1 byte

	mov rax, 1   ; rax   ( rdi, rsi,  rdx )
	syscall      ; write ( fd,  addr, len )

	pop rdi      ; pop val from stack and restore rsp
	ret
