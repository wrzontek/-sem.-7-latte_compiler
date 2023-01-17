.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 0
	SUB eax, 36
	MOV ebx, eax
	PUSH 45
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

