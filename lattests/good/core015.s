.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR 17
	CALL ev
	ADD esp, 4
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

ev:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	MOV eax, [ebp + 20]
	SUB eax, 2
	MOV ebx, eax
	PUSH eax
	CALL ev
	ADD esp, 4
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_1:
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _if_true_2
	JMP _if_false_2
_if_true_2:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_2:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_2:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_1:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

