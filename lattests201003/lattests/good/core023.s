.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	PUSH 2
	PUSH 1
	CALL foo
	ADD esp, 56
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
	MOV eax, 2
	IMUL eax, DWORD PTR [ebp + 20]
	MOV [ebp + 20], eax
	MOV eax, DWORD PTR [ebp + 24]
	CDQ
	PUSH 2
	IDIV DWORD PTR [ebp - 4]
	MOV ebx, [ebp + 20]
	ADD ebx, eax
	ADD ebx, DWORD PTR [ebp + 28]
	ADD ebx, DWORD PTR [ebp + 32]
	ADD ebx, DWORD PTR [ebp + 36]
	ADD ebx, DWORD PTR [ebp + 40]
	ADD ebx, DWORD PTR [ebp + 44]
	ADD ebx, DWORD PTR [ebp + 48]
	ADD ebx, DWORD PTR [ebp + 52]
	MOV eax, DWORD PTR [ebp + 56]
	CDQ
	MOV [ebp - 4], DWORD PTR 2
	IDIV DWORD PTR [ebp - 4]
	ADD ebx, eax
	ADD ebx, DWORD PTR [ebp + 60]
	ADD ebx, DWORD PTR [ebp + 64]
	ADD ebx, DWORD PTR [ebp + 68]
	ADD ebx, DWORD PTR [ebp + 72]
	MOV eax, ebx
	CDQ
	MOV [ebp - 4], DWORD PTR 10
	IDIV DWORD PTR [ebp - 4]
	MOV ebx, edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	MOV eax, ebx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

