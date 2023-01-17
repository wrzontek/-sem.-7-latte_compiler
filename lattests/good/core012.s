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
	MOV ecx, 56
	SUB ecx, edi
	MOV esi, eax
	PUSH ecx
	PUSH ecx
	CALL printInt
	ADD esp, 4
	MOV ecx, 56
	IMUL ecx, edi
	PUSH eax
	PUSH ecx
	PUSH ecx
	CALL printInt
	ADD esp, 4
	MOV ecx, 45
	SAR ecx, 1
	PUSH eax
	PUSH ecx
	PUSH ecx
	CALL printInt
	ADD esp, 4
	MOV [ebp - 20], eax
	MOV eax, 78
	CDQ
	PUSH 3
	IDIV DWORD PTR [ebp - 24]
	MOV [ebp - 24], edx
	PUSH edx
	CALL printInt
	ADD esp, 4
	MOV ecx, [ebp - 4]
	CMP ecx, ebx
	MOV ecx, 0
	SETG cl
	MOV ebx, eax
	MOV [ebp - 24], ecx
	PUSH ecx
	CALL printBool
	ADD esp, 4
	MOV [ebp - 24], eax
	MOV eax, 56
	CDQ
	IDIV edi
	CMP eax, DWORD PTR [ebp - 12]
	MOV eax, 0
	SETLE al
	MOV edi, eax
	PUSH eax
	CALL printBool
	ADD esp, 4
	MOV edi, eax
	LEA eax, .SC0
	PUSH eax
	LEA eax, .SC3
	PUSH eax
	CALL _stringsConcat
	ADD esp, 8
	MOV [ebp - 4], eax
	LEA eax, .SC1
	PUSH eax
	PUSH DWORD PTR [ebp - 4]
	CALL _stringsConcat
	ADD esp, 8
	MOV [ebp - 4], eax
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

