BITS 64

; DEFAULT REL

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
;
; integers, pointers: RDI, RSI, RDX, RCX, R8, R9.
; floats: XMM0...7

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning

SECTION .rodata

SECTION .text

global asm_strlen
asm_strlen:

	mov rcx, -1
	next_char:
		inc rcx
		mov rax, [rdi + rcx]
		cmp al,0
		jne next_char

	mov rax, rcx
	ret
