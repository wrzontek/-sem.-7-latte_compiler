.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 266
	CDQ
	PUSH 3
	IDIV DWORD PTR[ebp - 4]
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

