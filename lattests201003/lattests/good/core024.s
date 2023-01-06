.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "NOOO"
.SC1:
	.string "yes"
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
	CALL f
	ADD esp, 8
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
	sub esp, 4
	MOV eax, [ebp + 24]
	CMP eax, DWORD PTR [ebp + 20]
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _true_l1
	JMP _middle_l3
_middle_l3:
	CALL e
	TEST eax, eax
	JNZ _true_l1
	JMP _false_l2
_true_l1:
	MOV [ebp - 4], DWORD PTR 1
	JMP _end_l4
_false_l2:
	MOV [ebp - 4], DWORD PTR 0
_end_l4:
	MOV eax, [ebp - 4]
	TEST eax, eax
	JNZ _if_true_1
	JMP _end_if_1
_if_true_1:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_1:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

e:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

