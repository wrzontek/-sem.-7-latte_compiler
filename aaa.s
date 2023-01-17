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
	IMUL eax, eax
	ADD eax, eax
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 20]
	ADD eax, DWORD PTR [ebp + 24]
	ADD eax, eax
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

