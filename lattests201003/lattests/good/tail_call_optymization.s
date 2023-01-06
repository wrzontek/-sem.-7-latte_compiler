.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH 500000
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

sum:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 12
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_1
	JMP _end_if_1
_if_true_1:
	MOV eax, [ebp + 24]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_1:
	MOV eax, [ebp + 20]
	CDQ
	PUSH 2
	IDIV DWORD PTR [ebp - 16]
	CMP edx, 1
	MOV edx, 0
	SETE dl
	MOV [ebp - 12], eax
	TEST edx, edx
	JNZ _if_true_2
	JMP _end_if_2
_if_true_2:
	MOV eax, 0
	SUB eax, 1
	IMUL eax, DWORD PTR [ebp + 20]
	MOV [ebp - 12], eax
_end_if_2:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, [ebp + 24]
	ADD ebx, DWORD PTR [ebp - 12]
	MOV edi, eax
	PUSH ebx
	PUSH eax
	CALL sum
	ADD esp, 8
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

