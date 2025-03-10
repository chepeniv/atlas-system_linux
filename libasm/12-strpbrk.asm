BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strpbrk(3)
;
; PROTOTYPE:
; char *asm_strpbrk(const char *text, const char *filter);
;
; MAN (3):
; search a string for a any of a set of bytes -- that is, locate the first
; occurrence of any one element of the 'filter' set
;
; RETURN:
; a pointer to the first byte in 'text' that matches any one of 'filter'
; if no such byte is found return NULL instead
;
; NOTES:
; arguments : RDI, RSI, RDX, RCX, R8, R9.
; preserve  : RBP, RBX, R12, R13, R14, R15

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning

SECTION .text

global asm_strpbrk
asm_strpbrk:

	push rbx
	mov rcx, -1

	next_char:
		inc rcx
		movzx rax, byte [rdi + rcx]

		test rax, rax
		jz no_match

		mov rdx, -1
		jmp check_char
		cont_next_char:

		jmp next_char

	check_char:
		inc rdx
		movzx rbx, byte [rsi + rdx]

		test rbx, rbx
		jz cont_next_char

		cmp rax, rbx
		jne check_char

	; match_found:
		pop rbx
		add rdi, rcx
		mov rax, rdi
		ret

	no_match:
		pop rbx
		mov rax, 0
		ret
