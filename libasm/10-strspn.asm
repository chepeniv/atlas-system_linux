BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strspn(3)
;
; prototype:
;     size_t asm_strspn(const char *text, const char *filter);
;
; MAN (3):
; measure the length (in bytes) of a prefix substring -- the initial segment of
; 'text' which consists entirely of bytes in 'filter'
;
; RETURN:
; number of bytes in the head-end of 'text' that consist entirely of characters
; passing the filter
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/bin/ld warning

SECTION .text

; A-Z: 65-90  (41-5a)
; a-z: 97-122 (61-7a)
capitalize:
	cmp rax, 0x61
	jle no_cap_left
	cmp rax, 0x7a
	jge no_cap_left
	sub rax, 0x20
	no_cap_left:

	cmp rbx, 0x61
	jle no_cap_right
	cmp rbx, 0x7a
	jge no_cap_right
	sub rbx, 0x20
	no_cap_right:

	jmp cont_next_char

global asm_strspn
asm_strspn:

	; SETUP
	mov rax, 1
	mov rbx, 1
	mov rcx, -1

	; COMPARE
	next_char:
		inc rcx
		movzx rax, byte [rdi + rcx]
		movzx rbx, byte [rsi + rcx]

		cmp rcx, rdx
		je end_of_cmp
		test rax, rbx
		jz end_of_str

		jmp capitalize
		cont_next_char:

		cmp rax, rbx
		je next_char

	; RETURN
	end_of_str:
		sub rax, rbx
		ret

	end_of_cmp:
		mov rax, 0
		ret
