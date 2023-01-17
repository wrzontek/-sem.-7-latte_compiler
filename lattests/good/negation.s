.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH 1
	CALL printInt
	ADD esp, 4
	MOV ebx, 0
	SUB ebx, 1
	MOV edi, eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV ebx, 2
	ADD ebx, 1
	MOV esi, eax
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

