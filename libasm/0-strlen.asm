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
;
; integers pointer:
;     RDI, RSI, RDX, RCX, R8, and R9.
;
; floats:
;     XMM0...7

SECTION .text

global asm_strlen
asm_strlen:
	; next_char:
	;     get the next 1 byte pos
	; jump back to next_char if not null
	; subtract end addr from start addr
	mov rax, rdi
	ret
