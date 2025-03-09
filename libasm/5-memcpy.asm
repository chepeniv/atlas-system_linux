BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of memcpy(3)
;
; prototype:
;     void *asm_memcpy(
;         void       *dest,
;         const void *source,
;         size_t      n);
;
; MAN (3):
; copy n bytes from source into dest
;
; RETURN:
; pointer to dest
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_memcpy
asm_memcpy:

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
