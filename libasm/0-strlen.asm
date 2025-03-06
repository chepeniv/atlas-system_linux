BITS 64

; INSTRUCTIONS:
;
; lib and sys calls are NOT permitted, specifically 'call' and 'syscall'
;
; copycat of strlen(3)
;
; prototype:
;     size_t asm_strlen(const char *text);
;
; MAN (3): calculate and return the length in bytes of given string pointed to
; by text excluding the terminating null character

SECTION .rodata

SECTION .text

c_exit: ; call exit(0);
	mov eax, 1
	mov ebx, 0
	int 0x80

global _start
_start:

	;ret
	jmp c_exit
