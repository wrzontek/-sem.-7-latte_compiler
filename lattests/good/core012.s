.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "false"
.SC1:
	.string "string concatenation"
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
	PUSH DWORD PTR 33
	CALL printInt
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR 79
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH DWORD PTR -1288
	CALL printInt
	ADD esp, 4
	MOV esi, eax
	PUSH DWORD PTR 22
	CALL printInt
	ADD esp, 4
	PUSH eax
	PUSH DWORD PTR 0
	CALL printInt
	ADD esp, 4
	PUSH eax
	PUSH DWORD PTR 1
	CALL printBool
	ADD esp, 4
	PUSH eax
	PUSH DWORD PTR 0
	CALL printBool
	ADD esp, 4
	PUSH eax
	LEA eax, .SC1
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
_if_false_1:
	LEA eax, .SC0
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

