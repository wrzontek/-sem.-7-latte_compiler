.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "apa"
.SC1:
	.string "false"
.SC2:
	.string "true"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 20
	MOV eax, 3
	CMP eax, 4
	MOV eax, 0
	SETLE al
	MOV [ebp - 4], DWORD PTR 4
	TEST eax, eax
	JNZ _middle_l3
	JMP _false_l2
_middle_l3:
	MOV eax, 4
	CMP eax, 2
	MOV eax, 0
	SETNE al
	TEST eax, eax
	JNZ _middle_l4
	JMP _false_l2
_middle_l4:
	JMP _true_l1
_true_l1:
	MOV [ebp - 8], DWORD PTR 1
	JMP _end_l5
_false_l2:
	MOV [ebp - 8], DWORD PTR 0
_end_l5:
	MOV eax, [ebp - 8]
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	PUSH 1
	CALL printBool
	ADD esp, 4
	JMP _end_if_1
_if_false_1:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_1:
	MOV eax, 1
	CMP eax, eax
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _true_l8
	JMP _middle_l10
_middle_l10:
	PUSH 1
	CALL dontCallMe
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l8
	JMP _false_l9
_true_l8:
	MOV [ebp - 20], DWORD PTR 1
	JMP _end_l11
_false_l9:
	MOV [ebp - 20], DWORD PTR 0
_end_l11:
	PUSH DWORD PTR [ebp - 20]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l6
	JMP _false_l7
_true_l6:
	JMP _end_l12
_false_l7:
_end_l12:
	MOV eax, 0
	SUB eax, 5
	MOV ebx, 4
	CMP ebx, eax
	MOV ebx, 0
	SETL bl
	TEST ebx, ebx
	JNZ _middle_l17
	JMP _false_l16
_middle_l17:
	PUSH 2
	CALL dontCallMe
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l15
	JMP _false_l16
_true_l15:
	MOV [ebp - 12], DWORD PTR 1
	JMP _end_l18
_false_l16:
	MOV [ebp - 12], DWORD PTR 0
_end_l18:
	PUSH DWORD PTR [ebp - 12]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l13
	JMP _false_l14
_true_l13:
	JMP _end_l19
_false_l14:
_end_l19:
	MOV eax, 4
	CMP eax, DWORD PTR [ebp - 4]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _middle_l24
	JMP _false_l23
_middle_l24:
	MOV eax, 1
	SUB eax, 0
	MOV ebx, 1
	CMP ebx, eax
	MOV ebx, 0
	SETE bl
	TEST ebx, ebx
	JNZ _middle_l25
	JMP _false_l23
_middle_l25:
	JMP _true_l22
_true_l22:
	MOV [ebp - 16], DWORD PTR 1
	JMP _end_l26
_false_l23:
	MOV [ebp - 16], DWORD PTR 0
_end_l26:
	PUSH DWORD PTR [ebp - 16]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l20
	JMP _false_l21
_true_l20:
	JMP _end_l27
_false_l21:
_end_l27:
	PUSH 0
	PUSH 0
	CALL implies
	ADD esp, 8
	MOV ebx, eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV ebx, eax
	PUSH 1
	PUSH 0
	CALL implies
	ADD esp, 8
	MOV edi, eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV edi, eax
	PUSH 0
	PUSH 1
	CALL implies
	ADD esp, 8
	MOV esi, eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV esi, eax
	PUSH 1
	PUSH 1
	CALL implies
	ADD esp, 8
	PUSH eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

dontCallMe:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR [ebp + 20]
	CALL printInt
	ADD esp, 4
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

printBool:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 20]
	TEST eax, eax
	JNZ _if_true_2
	JMP _if_false_2
_if_true_2:
	LEA eax, .SC2
	PUSH eax
	CALL printString
	ADD esp, 4
	JMP _end_if_2
_if_false_2:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_2:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

implies:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 12
	MOV eax, [ebp + 20]
	TEST eax, eax
	JNZ _middle_l30
	JMP _true_l28
_middle_l30:
	MOV eax, [ebp + 20]
	CMP eax, DWORD PTR [ebp + 24]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _true_l28
	JMP _false_l29
_true_l28:
	MOV [ebp - 12], DWORD PTR 1
	JMP _end_l31
_false_l29:
	MOV [ebp - 12], DWORD PTR 0
_end_l31:
	MOV eax, [ebp - 12]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

