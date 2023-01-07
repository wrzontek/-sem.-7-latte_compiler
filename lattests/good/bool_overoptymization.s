.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "ahoj"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL print
	TEST eax, eax
	JNZ _middle_l3
	JMP _false_l2
_middle_l3:
	JMP _false_l2
_true_l1:
	JMP _end_l4
_false_l2:
_end_l4:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

print:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

