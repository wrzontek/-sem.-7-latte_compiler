.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 5
	CDQ
	PUSH 3
	IDIV DWORD PTR [ebp - 4]
	MOV ebx, edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	MOV ebx, 0
	SUB ebx, 5
	MOV [ebp - 4], eax
	MOV eax, ebx
	CDQ
	PUSH 3
	IDIV DWORD PTR [ebp - 8]
	MOV ebx, edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

