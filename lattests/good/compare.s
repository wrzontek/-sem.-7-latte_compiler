.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "4"
.SC1:
	.string "6"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	JMP _if_true_1
_if_true_1:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_1:
	JMP _if_true_2
_if_true_2:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_2:
	JMP _if_true_3
_if_true_3:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_3:
	JMP _if_true_4
_if_true_4:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_4:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

