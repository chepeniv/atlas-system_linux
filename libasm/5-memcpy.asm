BITS 64

; INSTRUCTIONS:
; 'call' and 'syscall' are NOT allowed
; copycat of memcpy(3)
;
; prototype:
;     void *asm_memcpy(
;         void       *dest,
;         const void *source,
;         size_t      n);
;
; MAN (3):
; copy n bytes from source into dest
;
; RETURN:
; pointer to dest
;
; argument order: RDI, RSI, RDX, RCX, R8, R9.

SECTION .note.GNU-stack ; suppress /usr/binl/ld warning

SECTION .text

global asm_memcpy
asm_memcpy:

	; SETUP
	mov rcx, -1
	movzx r8, byte [rsi]

	; EMPTY SEARCH PHRASE
	test r8, r8
	jz return_pointer

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
	return_pointer:
		mov rax, rdi
		ret

	; NO MATCH
	end_of_str:
		mov rax, 0
		ret

