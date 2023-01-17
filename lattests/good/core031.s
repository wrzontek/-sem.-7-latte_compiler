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
	SUB eax, 1
	MOV ebx, eax
	PUSH eax
	PUSH 1
	CALL f
	ADD esp, 8
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

f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 12
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _middle_l4
	JMP _middle_l3
_middle_l4:
	MOV eax, [ebp + 24]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _true_l1
	JMP _middle_l3
_middle_l3:
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _middle_l5
	JMP _false_l2
_middle_l5:
	MOV eax, [ebp + 24]
	CMP eax, 0
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _true_l1
	JMP _false_l2
_true_l1:
	MOV [ebp - 12], DWORD PTR 1
	JMP _end_l6
_false_l2:
	MOV [ebp - 12], DWORD PTR 0
_end_l6:
	MOV eax, [ebp - 12]
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	MOV eax, 7
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_1:
	MOV eax, 42
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

