.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "foo"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV [ebp - 4], DWORD PTR 78
_t1:
	PUSH 1
	CALL printInt
	ADD esp, 4
_after_t1:
	PUSH 78
	CALL printInt
	ADD esp, 4
	JMP _while_cond_2
_while_body_2:
	MOV eax, [ebp - 4]
	SUB eax, 1
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV ecx, ebx
	ADD ebx, 7
	MOV edi, eax
	MOV esi, ecx
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV [ebp - 4], esi
_while_cond_2:
	MOV eax, [ebp - 4]
	CMP eax, 76
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_2
	JMP _end_while_2
_end_while_2:
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
	MOV ebx, [ebp - 4]
	CMP ebx, 4
	MOV ebx, 0
	SETG bl
	TEST ebx, ebx
	JNZ _if_true_3
	JMP _if_false_3
_if_true_3:
	PUSH 4
	CALL printInt
	ADD esp, 4
	JMP _end_if_3
_if_false_3:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_3:
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

