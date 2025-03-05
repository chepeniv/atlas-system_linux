BITS 64

; INSTRUCTIONS
; write a copycat of strlen(3)
; prototype: size_t asm_strlen(const char *str);

SECTION .rodata

SECTION .text

global _start
_start:

	; call exit(0);
	mov eax, 1
	mov ebx, 0
	int 0x80
