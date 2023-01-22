.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, 0
	TEST eax, eax
	JNZ _if_true_1
	JMP _if_false_1
_if_true_1:
	MOV [ebp - 4], DWORD PTR 1
	JMP _end_if_1
_if_false_1:
	MOV [ebp - 4], DWORD PTR 2
_end_if_1:
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

