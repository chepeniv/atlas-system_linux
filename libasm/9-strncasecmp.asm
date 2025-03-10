BITS 64

; INSTRUCTIONS:
; copycat of strncasecmp(3)
; 'call' and 'syscall' are NOT allowed
;
; prototype:
;     int asm_strncasecmp(
;         const char *left,
;         const char *right,
;         size_t n);
;
; MAN (3):
; compare no more than 'n' bytes for two character strings while ignoring
; character case.
;
; RETURN:
; "an integer less than, equal to, or greater than zero if 'left' is, after
; ignoring case, found to be less than, to  match, or be greater than 'right',
; respectively." ~
;
; integers, pointers: RDI, RSI, RDX, RCX, R8, R9.

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

global asm_strncasecmp
asm_strncasecmp:

	; SETUP
	mov rax, 1
	mov rbx, 1
	mov rcx, -1

	; COMPARE
	next_char:
		inc rcx
		movzx rax, byte [rdi + rcx]
		movzx rbx, byte [rsi + rcx]

		test rax, rbx
		jz end_of_string

		jmp capitalize
		cont_next_char:

		cmp rax, rbx
		je next_char

	; RETURN
	end_of_string:
		sub rax, rbx
		ret
