.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL p
	MOV ebx, eax
	PUSH 1
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

p:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

