.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "!"
.SC1:
	.string "&&"
.SC2:
	.string "false"
.SC3:
	.string "true"
.SC4:
	.string "||"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 32
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR -1
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l5
	JMP _false_l4
_middle_l5:
	PUSH DWORD PTR 0
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l3
	JMP _false_l4
_true_l3:
	MOV [ebp - 12], DWORD PTR 1
	JMP _end_l6
_false_l4:
	MOV [ebp - 12], DWORD PTR 0
_end_l6:
	PUSH DWORD PTR [ebp - 12]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l1
	JMP _false_l2
_true_l1:
	JMP _end_l7
_false_l2:
_end_l7:
	PUSH DWORD PTR -2
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l12
	JMP _false_l11
_middle_l12:
	PUSH DWORD PTR 1
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l10
	JMP _false_l11
_true_l10:
	MOV [ebp - 32], DWORD PTR 1
	JMP _end_l13
_false_l11:
	MOV [ebp - 32], DWORD PTR 0
_end_l13:
	PUSH DWORD PTR [ebp - 32]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l8
	JMP _false_l9
_true_l8:
	JMP _end_l14
_false_l9:
_end_l14:
	PUSH DWORD PTR 3
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l19
	JMP _false_l18
_middle_l19:
	PUSH DWORD PTR -5
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l17
	JMP _false_l18
_true_l17:
	MOV [ebp - 4], DWORD PTR 1
	JMP _end_l20
_false_l18:
	MOV [ebp - 4], DWORD PTR 0
_end_l20:
	PUSH DWORD PTR [ebp - 4]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l15
	JMP _false_l16
_true_l15:
	JMP _end_l21
_false_l16:
_end_l21:
	PUSH DWORD PTR 234234
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _middle_l26
	JMP _false_l25
_middle_l26:
	PUSH DWORD PTR 21321
	CALL test
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
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l22
	JMP _false_l23
_true_l22:
	JMP _end_l28
_false_l23:
_end_l28:
	LEA eax, .SC4
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR -1
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l31
	JMP _middle_l33
_middle_l33:
	PUSH DWORD PTR 0
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l31
	JMP _false_l32
_true_l31:
	MOV [ebp - 16], DWORD PTR 1
	JMP _end_l34
_false_l32:
	MOV [ebp - 16], DWORD PTR 0
_end_l34:
	PUSH DWORD PTR [ebp - 16]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l29
	JMP _false_l30
_true_l29:
	JMP _end_l35
_false_l30:
_end_l35:
	PUSH DWORD PTR -2
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l38
	JMP _middle_l40
_middle_l40:
	PUSH DWORD PTR 1
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l38
	JMP _false_l39
_true_l38:
	MOV [ebp - 20], DWORD PTR 1
	JMP _end_l41
_false_l39:
	MOV [ebp - 20], DWORD PTR 0
_end_l41:
	PUSH DWORD PTR [ebp - 20]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l36
	JMP _false_l37
_true_l36:
	JMP _end_l42
_false_l37:
_end_l42:
	PUSH DWORD PTR 3
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l45
	JMP _middle_l47
_middle_l47:
	PUSH DWORD PTR -5
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l45
	JMP _false_l46
_true_l45:
	MOV [ebp - 24], DWORD PTR 1
	JMP _end_l48
_false_l46:
	MOV [ebp - 24], DWORD PTR 0
_end_l48:
	PUSH DWORD PTR [ebp - 24]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l43
	JMP _false_l44
_true_l43:
	JMP _end_l49
_false_l44:
_end_l49:
	PUSH DWORD PTR 234234
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l52
	JMP _middle_l54
_middle_l54:
	PUSH DWORD PTR 21321
	CALL test
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l52
	JMP _false_l53
_true_l52:
	MOV [ebp - 28], DWORD PTR 1
	JMP _end_l55
_false_l53:
	MOV [ebp - 28], DWORD PTR 0
_end_l55:
	PUSH DWORD PTR [ebp - 28]
	CALL printBool
	ADD esp, 4
	TEST eax, eax
	JNZ _true_l50
	JMP _false_l51
_true_l50:
	JMP _end_l56
_false_l51:
_end_l56:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR 1
	CALL printBool
	ADD esp, 4
	MOV edi, eax
	PUSH DWORD PTR 0
	CALL printBool
	ADD esp, 4
	MOV eax, 0
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
	MOV eax, 1
	SUB eax, DWORD PTR [ebp + 20]
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	LEA eax, .SC2
	PUSH eax
	CALL printString
	ADD esp, 4
	JMP _end_if_1
_if_false_1:
	LEA eax, .SC3
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

test:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR [ebp + 20]
	CALL printInt
	ADD esp, 4
	MOV ebx, [ebp + 20]
	CMP ebx, 0
	MOV ebx, 0
	SETG bl
	MOV eax, ebx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

