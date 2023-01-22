.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR 5
	CALL fac
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

fac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV eax, [ebp + 16]
	MOV [ebp - 4], eax
	MOV [ebp - 8], DWORD PTR 1
	JMP _while_cond_1
_while_body_1:
	MOV eax, [ebp - 8]
	IMUL eax, DWORD PTR [ebp - 4]
	MOV ebx, [ebp - 4]
	SUB ebx, 1
	MOV [ebp - 4], ebx
	MOV [ebp - 8], eax
_while_cond_1:
	MOV eax, [ebp - 4]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	MOV eax, [ebp - 8]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

