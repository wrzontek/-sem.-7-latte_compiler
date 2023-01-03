.intel_syntax noprefix
.text
.globl main
main:
	push ebp
	mov ebp, esp
	push ebx
	push edi
	push esi
	MOV eax, 100
	CDQ
	PUSH 4
	IDIV DWORD PTR[ebp - 16]
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	pop esi
	pop edi
	pop ebx
	mov esp, ebp
	pop ebp
	ret

