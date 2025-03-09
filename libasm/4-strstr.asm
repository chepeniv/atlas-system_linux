BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strstr(3)
;
; prototype:
;     char *asm_strstr(const char *text, const char *phrase);
;
; MAN (3):
; this function finds  the  first  occurrence of the substring 'phrase' in the
; string 'text'.  terminating null bytes ('\0') are not compared.
;
; RETURN:
; pointer to the beginning of the found 'phrase', otherwise NULL if nothing
; found
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_strstr
asm_strchr:

	; SETUP
	mov rax, 1
	mov rcx, -1

	; SEARCH
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
