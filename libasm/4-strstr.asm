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
asm_strstr:

	; SETUP
	mov rcx, -1
	movzx r8, byte [rsi]

	; SEARCH
	search_loop:
		inc rcx
		movzx rax, byte [rdi + rcx]

		test rax, rax
		jz end_of_str
		cmp rax, r8
		jne search_loop

	; SETUP
	mov rdx, 0

	; CHECK
	match_loop:
		inc rcx
		inc rdx

		movzx rax, byte [rdi + rcx]
		movzx rbx, byte [rsi + rdx]

		test rbx, rbx
		jz match_found

		test rax, rax
		jz end_of_str

		cmp rax, rbx
		jne search_loop
		je match_loop

	; MATCH FOUND
	match_found:
		sub rcx, rdx ; get the correct offset
		add rdi, rcx ; get the new pointer
		mov rax, rdi
		ret

	; NO MATCH
	end_of_str:
		mov rax, 0
		ret

