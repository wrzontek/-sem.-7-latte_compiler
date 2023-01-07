.intel_syntax noprefix
.text
.globl main
f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	JMP _if_true_1
_if_true_1:
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

g:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	JMP _if_false_2
_if_false_2:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_2:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

p:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL p
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

