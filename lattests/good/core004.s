.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 1
	TEST eax, eax
	JNZ _if_true_1
	JMP _end_if_1
_if_true_1:
	PUSH DWORD PTR 42
	CALL printInt
	ADD esp, 4
_end_if_1:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

