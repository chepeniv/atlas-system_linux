BITS 64

; INSTRUCTIONS:
; copycat of strncmp(3)
; 'call' and 'syscall' are NOT allowed
;
; prototype:
;     int asm_strncmp(
;         const char *left,
;         const char *right,
;         size_t n);
;
; MAN (3):
; similar to strcmp except that analyzes at most n bytes
;
; RETURN:
; returns an integer indicating the result of the comparison:
;     0, if the s1 and s2 are equal up to n
;
;     otherwise, the ascii difference of the last mismatching
;     characters is returned
;
; integers, pointers: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .rodata

SECTION .text

global asm_strncmp
asm_strncmp:

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
		cmp rax, rbx
		je next_char

		; RETURN
		; len(left-match) = n
		;     AND
		; len(left-match) < len(right-match)
		;     return 0

		; len(left-match) < n
		;     AND
		; len(left-match) < len(right-match)
		;     return diff

		end_of_str:
			sub rax, rbx
			ret

		end_of_cmp:
			mov rax, 0
			ret
