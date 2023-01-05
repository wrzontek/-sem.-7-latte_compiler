.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV [ebp - 4], DWORD PTR 1
	MOV [ebp - 8], DWORD PTR 100
	JMP _while_cond_1
_while_body_1:
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
	MOV ebx, [ebp - 4]
	ADD ebx, 1
	MOV [ebp - 4], ebx
_while_cond_1:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 8]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

