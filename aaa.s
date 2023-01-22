.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "before while"
.SC1:
	.string "while"
.text
.globl main
mulmod:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 16
	MOV eax, DWORD PTR [ebp + 20]
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV [ebp - 12], DWORD PTR 0
	MOV [ebp - 16], edx
	JMP _while_cond_1
_while_body_1:
	MOV eax, DWORD PTR [ebp + 24]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 20]
	CMP edx, 1
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _if_true_2
	JMP _end_if_2
_if_true_2:
	MOV eax, [ebp - 12]
	ADD eax, DWORD PTR [ebp - 16]
	MOV [ebp - 12], eax
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV [ebp - 12], edx
_end_if_2:
	MOV eax, [ebp - 16]
	IMUL eax, 2
	MOV [ebp - 16], eax
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV eax, DWORD PTR [ebp + 24]
	MOV [ebp - 16], edx
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 24]
	MOV [ebp + 24], eax
_while_cond_1:
	MOV eax, [ebp + 24]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	MOV eax, DWORD PTR [ebp - 12]
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV eax, edx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

modulo:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 16
	MOV eax, [ebp + 20]
	MOV [ebp - 12], DWORD PTR 1
	MOV [ebp - 16], eax
	JMP _while_cond_3
_while_body_3:
	MOV eax, DWORD PTR [ebp + 24]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 20]
	CMP edx, 1
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _if_true_4
	JMP _end_if_4
_if_true_4:
	MOV eax, [ebp - 12]
	IMUL eax, DWORD PTR [ebp - 16]
	MOV [ebp - 12], eax
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV [ebp - 12], edx
_end_if_4:
	MOV eax, [ebp - 16]
	IMUL eax, eax
	MOV [ebp - 16], eax
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV eax, DWORD PTR [ebp + 24]
	MOV [ebp - 16], edx
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 24]
	MOV [ebp + 24], eax
_while_cond_3:
	MOV eax, [ebp + 24]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_3
	JMP _end_while_3
_end_while_3:
	MOV eax, DWORD PTR [ebp - 12]
	CDQ
	IDIV DWORD PTR [ebp + 28]
	MOV eax, edx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

Miller:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 40
	MOV eax, [ebp + 20]
	CMP eax, 2
	MOV eax, 0
	SETL al
	MOV [ebp - 16], DWORD PTR 2137
	TEST eax, eax
	JNZ _if_true_5
	JMP _end_if_5
_if_true_5:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_5:
	MOV eax, [ebp + 20]
	CMP eax, 2
	MOV eax, 0
	SETNE al
	TEST eax, eax
	JNZ _middle_l3
	JMP _false_l2
_middle_l3:
	MOV eax, DWORD PTR [ebp + 20]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 44]
	CMP edx, 0
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _true_l1
	JMP _false_l2
_true_l1:
	MOV [ebp - 32], DWORD PTR 1
	JMP _end_l4
_false_l2:
	MOV [ebp - 32], DWORD PTR 0
_end_l4:
	MOV eax, [ebp - 32]
	TEST eax, eax
	JNZ _if_true_6
	JMP _end_if_6
_if_true_6:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_6:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV [ebp - 20], eax
	JMP _while_cond_7
_while_body_7:
	MOV eax, DWORD PTR [ebp - 20]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 48]
	MOV [ebp - 20], eax
_while_cond_7:
	MOV eax, DWORD PTR [ebp - 20]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 52]
	CMP edx, 0
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _while_body_7
	JMP _end_while_7
_end_while_7:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR [ebp + 20]
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH DWORD PTR [ebp - 16]
	CALL printInt
	ADD esp, 4
	MOV [ebp - 12], DWORD PTR 0
	JMP _while_cond_8
_while_body_8:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR [ebp + 20]
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH DWORD PTR [ebp - 16]
	CALL printInt
	ADD esp, 4
	MOV ecx, [ebp + 20]
	SUB ecx, 1
	PUSH eax
	MOV eax, DWORD PTR [ebp - 16]
	CDQ
	IDIV ecx
	ADD edx, 1
	MOV eax, [ebp - 20]
	MOV esi, eax
	PUSH edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	PUSH eax
	PUSH DWORD PTR [ebp + 20]
	PUSH DWORD PTR [ebp - 20]
	PUSH DWORD PTR [ebp - 60]
	CALL modulo
	ADD esp, 12
	MOV [ebp - 24], eax
	MOV [ebp - 28], esi
	JMP _while_cond_9
_while_body_9:
	PUSH DWORD PTR [ebp + 20]
	PUSH DWORD PTR [ebp - 24]
	PUSH DWORD PTR [ebp - 24]
	CALL mulmod
	ADD esp, 12
	MOV ebx, [ebp - 28]
	IMUL ebx, 2
	MOV [ebp - 24], eax
	MOV [ebp - 28], ebx
_while_cond_9:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, [ebp - 28]
	CMP ebx, eax
	MOV ebx, 0
	SETNE bl
	TEST ebx, ebx
	JNZ _middle_l7
	JMP _false_l6
_middle_l7:
	MOV eax, [ebp - 24]
	CMP eax, 1
	MOV eax, 0
	SETNE al
	TEST eax, eax
	JNZ _middle_l8
	JMP _false_l6
_middle_l8:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, [ebp - 24]
	CMP ebx, eax
	MOV ebx, 0
	SETNE bl
	TEST ebx, ebx
	JNZ _true_l5
	JMP _false_l6
_true_l5:
	MOV [ebp - 36], DWORD PTR 1
	JMP _end_l9
_false_l6:
	MOV [ebp - 36], DWORD PTR 0
_end_l9:
	MOV eax, [ebp - 36]
	TEST eax, eax
	JNZ _while_body_9
	JMP _end_while_9
_end_while_9:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, [ebp - 24]
	CMP ebx, eax
	MOV ebx, 0
	SETNE bl
	TEST ebx, ebx
	JNZ _middle_l12
	JMP _false_l11
_middle_l12:
	MOV eax, DWORD PTR [ebp - 28]
	CDQ
	PUSH DWORD PTR 2
	IDIV DWORD PTR [ebp - 68]
	CMP edx, 0
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _true_l10
	JMP _false_l11
_true_l10:
	MOV [ebp - 40], DWORD PTR 1
	JMP _end_l13
_false_l11:
	MOV [ebp - 40], DWORD PTR 0
_end_l13:
	MOV eax, [ebp - 40]
	TEST eax, eax
	JNZ _if_true_10
	JMP _end_if_10
_if_true_10:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_10:
	MOV eax, [ebp - 12]
	ADD eax, 1
	MOV ebx, [ebp - 16]
	IMUL ebx, 29
	MOV ecx, [ebp + 20]
	SUB ecx, 1
	MOV [ebp - 12], eax
	MOV eax, ebx
	CDQ
	IDIV ecx
	MOV [ebp - 16], edx
_while_cond_8:
	MOV eax, [ebp - 12]
	CMP eax, DWORD PTR [ebp + 24]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _while_body_8
	JMP _end_while_8
_end_while_8:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

dummyPrimeTest:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV [ebp - 8], DWORD PTR 2
	JMP _while_cond_11
_while_body_11:
	MOV eax, DWORD PTR [ebp + 20]
	CDQ
	IDIV DWORD PTR [ebp - 8]
	CMP edx, 0
	MOV edx, 0
	SETE dl
	TEST edx, edx
	JNZ _if_true_12
	JMP _end_if_12
_if_true_12:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_12:
	MOV eax, [ebp - 8]
	ADD eax, 1
	MOV [ebp - 8], eax
_while_cond_11:
	MOV eax, [ebp - 8]
	CMP eax, DWORD PTR [ebp + 20]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _while_body_11
	JMP _end_while_11
_end_while_11:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	PUSH DWORD PTR 5
	PUSH DWORD PTR 2047
	CALL Miller
	ADD esp, 8
	MOV ebx, eax
	MOV edi, eax
	PUSH DWORD PTR 2047
	CALL dummyPrimeTest
	ADD esp, 4
	CMP eax, ebx
	MOV eax, 0
	SETNE al
	MOV [ebp - 4], DWORD PTR 0
	MOV [ebp - 8], edi
	TEST eax, eax
	JNZ _if_true_13
	JMP _end_if_13
_if_true_13:
	PUSH DWORD PTR 5
	PUSH DWORD PTR 2047
	CALL Miller
	ADD esp, 8
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR 2047
	CALL dummyPrimeTest
	ADD esp, 4
	MOV edi, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH DWORD PTR 2047
	CALL printInt
	ADD esp, 4
_end_if_13:
	MOV eax, [ebp - 8]
	CMP eax, 1
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_14
	JMP _end_if_14
_if_true_14:
	MOV eax, [ebp - 4]
	ADD eax, 1
	MOV [ebp - 4], eax
_end_if_14:
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

