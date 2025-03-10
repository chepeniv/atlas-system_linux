BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strcspn(3)
;
; PROTOTYPE:
; size_t asm_strcspn(const char *text, const char *exclude);
;
; MAN (3):
; measure the length (in bytes) of the prefix substring in 'text' which
; consists entirely of bytes NOT in 'exclude'
;
; RETURN:
; number of bytes in the head-end of 'text' that consist entirely of characters
; passing the filter
;
; NOTES:
; arguments : RDI, RSI, RDX, RCX, R8, R9.
; preserve  : RBP, RBX, R12, R13, R14, R15

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning

SECTION .text

global asm_strcspn
asm_strcspn:

	push rbx
	mov rcx, -1 ; next_char counter
	mov r8, 0   ; result

	next_char:
		inc rcx
		movzx rax, byte [rdi + rcx]

		test rax, rax
		jz end_of_cmp

		mov rdx, -1 ; reset check_char counter
		jmp check_char
		cont_next_char:
		inc r8

		cmp rax, rbx
		je next_char

	check_char:
		inc rdx
		movzx rbx, byte [rsi + rdx]

		test rbx, rbx
		jz end_of_cmp

		cmp rax, rbx
		je cont_next_char

		jmp check_char

	; RETURN
	end_of_cmp:
		pop rbx
		mov rax, r8
		ret
