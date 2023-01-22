.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV [ebp - 4], DWORD PTR 17
	JMP _while_cond_1
_while_body_1:
	MOV eax, [ebp - 4]
	SUB eax, 2
	MOV [ebp - 4], eax
_while_cond_1:
	MOV eax, [ebp - 4]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	MOV eax, [ebp - 4]
	CMP eax, 0
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _if_true_2
	JMP _if_false_2
_if_true_2:
	PUSH DWORD PTR 0
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_2:
	PUSH DWORD PTR 1
	CALL printInt
	ADD esp, 4
	MOV eax, 0
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

