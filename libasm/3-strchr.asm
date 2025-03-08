BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of strchr(3)
;
; prototype:
;     int asm_strchr(const char *text, int c);
;
; MAN (3):
; returns a pointer to the first occurrence of the character 'c' within the
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
	mov rbx, 1
	mov rcx, -1

	; COMPARE
	next_char:
		cmp rcx, rdx
		je end_of_cmp
		test rax, rbx
		jz end_of_cmp

		inc rcx
		movzx rax, byte [rdi + rcx]
		movzx rbx, byte [rsi + rcx]

		cmp rax, rbx
		je next_char

	; RETURN
	end_of_cmp:
		sub rax, rbx
		ret
