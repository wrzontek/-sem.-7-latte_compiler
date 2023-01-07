.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
_while_body_1:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_while_cond_1:
	MOV eax, 1
	TEST eax, eax
	JNZ _while_body_1
	JMP _end_while_1
_end_while_1:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

