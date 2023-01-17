.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "jeszcze raz"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
_while_body_1:
	CALL readInt
	CMP eax, 1
	MOV eax, 0
	SETE al
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
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_2:
_while_cond_1:
	MOV eax, 1
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

