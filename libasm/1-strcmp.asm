BITS 64

; INSTRUCTIONS:
; copycat of strcmp(3)
; 'call' and 'syscall' are NOT allowed
; prototype:
;     int asm_strcmp(const char *left, const char *right);
;
; MAN (3):
; compares two strings.  locale is not taken into account.  comparison is done
; using unsigned characters.
;
; RETURN:
; returns an integer indicating the result of the comparison:
;     0, if the s1 and s2 are equal;
;     negative value if s1 is less than s2;
;     positive value if s1 is greater than s2.
;
; integers, pointers: RDI, RSI, RDX, RCX, R8, R9.

SECTION .rodata

SECTION .text

global asm_strcmp
asm_strcmp:

	mov rcx, -1
	next_char:
		inc rcx
		mov rax, [rdi + rcx]
		cmp al,0
		jne next_char

	mov rax, rcx
	ret
