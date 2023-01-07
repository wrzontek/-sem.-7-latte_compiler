.intel_syntax noprefix
.section  .rodata
.SC0:
	.string " "
.SC1:
	.string "concatenation"
.SC2:
	.string "false"
.SC3:
	.string "string"
.SC4:
	.string "true"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 0
	SUB eax, 23
	MOV ebx, 56
	ADD ebx, eax
	MOV edi, eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV ebx, 56
	SUB ebx, edi
	MOV esi, eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV ebx, 56
	IMUL ebx, edi
	PUSH eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV ebx, 45
	SAR ebx, 1
	PUSH eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	PUSH eax
	MOV eax, 78
	CDQ
	PUSH 3
	IDIV DWORD PTR [ebp - 16]
	MOV ebx, edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	MOV ebx, 56
	SUB ebx, edi
	MOV ecx, 56
	ADD ecx, edi
	CMP ebx, ecx
	MOV ebx, 0
	SETG bl
	MOV [ebp - 16], eax
	PUSH ebx
	CALL printBool
	ADD esp, 4
	PUSH eax
	MOV eax, 56
	CDQ
	IDIV edi
	MOV ebx, 56
	IMUL ebx, edi
	CMP eax, ebx
	MOV eax, 0
	SETLE al
	MOV ebx, eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV ebx, eax
	LEA eax, .SC0
	PUSH eax
	LEA eax, .SC3
	PUSH eax
	CALL _stringsConcat
	ADD esp, 8
	MOV edi, eax
	LEA eax, .SC1
	PUSH eax
	PUSH edi
	CALL _stringsConcat
	ADD esp, 8
	MOV edi, eax
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

printBool:
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
	LEA eax, .SC4
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
	LEA eax, .SC2
	PUSH eax
	CALL printString
	ADD esp, 4
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_1:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

