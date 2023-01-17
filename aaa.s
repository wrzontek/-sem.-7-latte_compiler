.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 123
	ADD eax, eax
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

