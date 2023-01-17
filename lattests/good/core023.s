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
	MOV eax, [ebp + 20]
	SAL eax, 1
	MOV ebx, [ebp + 24]
	SAR ebx, 1
	ADD eax, ebx
	ADD eax, DWORD PTR [ebp + 28]
	ADD eax, DWORD PTR [ebp + 32]
	ADD eax, DWORD PTR [ebp + 36]
	ADD eax, DWORD PTR [ebp + 40]
	ADD eax, DWORD PTR [ebp + 44]
	ADD eax, DWORD PTR [ebp + 48]
	ADD eax, DWORD PTR [ebp + 52]
	MOV ebx, [ebp + 56]
	SAR ebx, 1
	ADD eax, ebx
	ADD eax, DWORD PTR [ebp + 60]
	ADD eax, DWORD PTR [ebp + 64]
	ADD eax, DWORD PTR [ebp + 68]
	ADD eax, DWORD PTR [ebp + 72]
	CDQ
	MOV [ebp + 20], DWORD PTR 10
	IDIV DWORD PTR [ebp + 20]
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

