.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "C"
.SC1:
	.string "E"
.SC2:
	.string "L"
.SC3:
	.string "S"
.SC4:
	.string "T"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
_t1:
_after_t1:
	MOV [ebp - 4], DWORD PTR 4
	MOV [ebp - 8], DWORD PTR 5
_t2:
_after_t2:
	PUSH DWORD PTR 22
	CALL printInt
	ADD esp, 4
	MOV ebx, 0
	TEST ebx, ebx
	JNZ _if_true_3
	JMP _end_if_3
_if_true_3:
	LEA eax, .SC2
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_3:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 8]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _if_true_4
	JMP _end_if_4
_if_true_4:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_4:
	MOV eax, [ebp - 8]
	CMP eax, DWORD PTR [ebp - 4]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_5
	JMP _end_if_5
_if_true_5:
	LEA eax, .SC3
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_5:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 8]
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _if_true_6
	JMP _end_if_6
_if_true_6:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_6:
	MOV eax, [ebp - 8]
	CMP eax, DWORD PTR [ebp - 4]
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _if_true_7
	JMP _end_if_7
_if_true_7:
	LEA eax, .SC4
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_7:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 8]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_8
	JMP _end_if_8
_if_true_8:
	LEA eax, .SC1
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_8:
	MOV [ebp - 4], DWORD PTR 21
	MOV [ebp - 8], DWORD PTR 37
	MOV eax, 0
	TEST eax, eax
	JNZ _if_true_9
	JMP _end_if_9
_if_true_9:
	LEA eax, .SC3
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_9:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 8]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _if_true_10
	JMP _end_if_10
_if_true_10:
	LEA eax, .SC4
	PUSH eax
	CALL printString
	ADD esp, 4
_end_if_10:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

