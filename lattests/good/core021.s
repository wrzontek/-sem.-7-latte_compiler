.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	JMP _if_true_1
_if_true_1:
	PUSH 1
	CALL printInt
	ADD esp, 4
	MOV eax, 0
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

