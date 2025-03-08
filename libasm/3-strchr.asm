BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strchr(3)
;
; prototype:
;     char *asm_strchr(const char *text, int c);
;
; MAN (3):
; return a pointer to the first occurrence of the character 'c' within the
; given string 'text' if found, otherwise NULL. the terminating null byte '\0'
; is considered a valid argument
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_strchr
asm_strchr:

	; SETUP
	mov rax, 1
	mov rcx, -1

	; COMPARE
	next_char:
		test rax, rax
		jz end_of_str

		inc rcx
		movzx rax, byte [rdi + rcx]
		cmp rax, rsi
		jne next_char

		; MATCH FOUND
		add rdi, rcx
		mov rax, rdi
		ret

	; NO MATCH
	end_of_str:
		mov rax, 0
		ret
