.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 12
	PUSH 1
	CALL printInt
	ADD esp, 4
	PUSH 1
	MOV [ebp - 4], DWORD PTR 1
	MOV ebx, DWORD PTR [ebp - 16]
	MOV [ebp - 8], ebx
	MOV [ebp - 12], DWORD PTR 5000000
	JMP _while_cond_1
_while_body_1:
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
	MOV ebx, [ebp - 8]
	ADD ebx, DWORD PTR [ebp - 4]
	MOV ecx, ebx
	SUB ecx, DWORD PTR [ebp - 8]
	MOV [ebp - 4], ebx
	MOV [ebp - 8], ecx
_while_cond_1:
	MOV eax, [ebp - 4]
	CMP eax, DWORD PTR [ebp - 12]
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

