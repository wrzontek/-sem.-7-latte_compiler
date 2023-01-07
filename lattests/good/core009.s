.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL foo
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

foo:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 10
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

