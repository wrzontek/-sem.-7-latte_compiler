.intel_syntax noprefix
.text
.globl main
main:
	push ebp
	mov ebp, esp
	push ebx
	push edi
	push esi
	PUSH 10
	CALL ifac
	ADD esp, 4
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

ifac:
	push ebp
	mov ebp, esp
	push ebx
	push edi
	push esi
	PUSH DWORD PTR [ebp + 8]
	PUSH 1
	CALL ifac2f
	ADD esp, 8
	pop esi
	pop edi
	pop ebx
	mov esp, ebp
	pop ebp
	ret

ifac2f:
	push ebp
	mov ebp, esp
	push ebx
	push edi
	push esi
	sub esp, 8
	MOV eax, [ebp + 8]
	CMP eax, DWORD PTR [ebp + 12]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_1
	JMP _end_if_1
_if_true_1:
	MOV eax, [ebp + 8]
	pop esi
	pop edi
	pop ebx
	mov esp, ebp
	pop ebp
	ret
_end_if_1:
	MOV eax, [ebp + 8]
	CMP eax, DWORD PTR [ebp + 12]
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _if_true_2
	JMP _end_if_2
_if_true_2:
	MOV eax, 1
	pop esi
	pop edi
	pop ebx
	mov esp, ebp
	pop ebp
	ret
_end_if_2:
	MOV eax, [ebp + 8]
	ADD eax, DWORD PTR [ebp + 12]
	CDQ
	PUSH 2
	IDIV DWORD PTR[ebp - 0]
	MOV ebx, eax
	PUSH eax
	PUSH DWORD PTR [ebp + 8]
	CALL ifac2f
	ADD esp, 8
	ADD ebx, 1
	MOV edi, eax
	PUSH DWORD PTR [ebp + 12]
	PUSH ebx
	CALL ifac2f
	ADD esp, 8
	IMUL edi, eax
	MOV eax, edi
	pop esi
	pop edi
	pop ebx
	mov esp, ebp
	pop ebp
	ret

