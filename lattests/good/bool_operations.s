.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "false"
.SC1:
	.string "true"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 24
	PUSH DWORD PTR 1
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l5
	JMP _false_l4
_middle_l5:
	PUSH DWORD PTR 2
	CALL f
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l3
	JMP _false_l4
_true_l3:
	MOV [ebp - 4], DWORD PTR 1
	JMP _end_l6
_false_l4:
	MOV [ebp - 4], DWORD PTR 0
_end_l6:
	PUSH DWORD PTR [ebp - 4]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l1
	JMP _false_l2
_true_l1:
	JMP _end_l7
_false_l2:
_end_l7:
	PUSH DWORD PTR 3
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l12
	JMP _false_l11
_middle_l12:
	PUSH DWORD PTR 4
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l10
	JMP _false_l11
_true_l10:
	MOV [ebp - 20], DWORD PTR 1
	JMP _end_l13
_false_l11:
	MOV [ebp - 20], DWORD PTR 0
_end_l13:
	PUSH DWORD PTR [ebp - 20]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l8
	JMP _false_l9
_true_l8:
	JMP _end_l14
_false_l9:
_end_l14:
	PUSH DWORD PTR 5
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l17
	JMP _middle_l19
_middle_l19:
	PUSH DWORD PTR 6
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l17
	JMP _false_l18
_true_l17:
	MOV [ebp - 24], DWORD PTR 1
	JMP _end_l20
_false_l18:
	MOV [ebp - 24], DWORD PTR 0
_end_l20:
	PUSH DWORD PTR [ebp - 24]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l15
	JMP _false_l16
_true_l15:
	JMP _end_l21
_false_l16:
_end_l21:
	PUSH DWORD PTR 7
	CALL f
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l26
	JMP _false_l25
_middle_l26:
	PUSH DWORD PTR 8
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l24
	JMP _false_l25
_true_l24:
	MOV [ebp - 8], DWORD PTR 1
	JMP _end_l27
_false_l25:
	MOV [ebp - 8], DWORD PTR 0
_end_l27:
	PUSH DWORD PTR [ebp - 8]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l22
	JMP _false_l23
_true_l22:
	JMP _end_l28
_false_l23:
_end_l28:
	PUSH DWORD PTR 9
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l33
	JMP _false_l32
_middle_l33:
	PUSH DWORD PTR 10
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l34
	JMP _false_l32
_middle_l34:
	PUSH DWORD PTR 11
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l31
	JMP _false_l32
_true_l31:
	MOV [ebp - 12], DWORD PTR 1
	JMP _end_l35
_false_l32:
	MOV [ebp - 12], DWORD PTR 0
_end_l35:
	PUSH DWORD PTR [ebp - 12]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l29
	JMP _false_l30
_true_l29:
	JMP _end_l36
_false_l30:
_end_l36:
	PUSH DWORD PTR 12
	CALL f
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l39
	JMP _middle_l41
_middle_l41:
	PUSH DWORD PTR 13
	CALL f
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l42
	JMP _false_l40
_middle_l42:
	PUSH DWORD PTR 14
	CALL t
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l39
	JMP _false_l40
_true_l39:
	MOV [ebp - 16], DWORD PTR 1
	JMP _end_l43
_false_l40:
	MOV [ebp - 16], DWORD PTR 0
_end_l43:
	PUSH DWORD PTR [ebp - 16]
	CALL b
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l37
	JMP _false_l38
_true_l37:
	JMP _end_l44
_false_l38:
_end_l44:
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
	PUSH DWORD PTR [ebp + 20]
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

t:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR [ebp + 20]
	CALL f
	ADD esp, 4
	MOV ebx, 1
	SUB ebx, eax
	MOV eax, ebx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

b:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 20]
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_1:
	LEA eax, .SC0
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

