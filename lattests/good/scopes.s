.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH 0
	CALL printInt
	ADD esp, 4
_t1:
	PUSH 1
	CALL printInt
	ADD esp, 4
_after_t1:
	PUSH 0
	CALL printInt
	ADD esp, 4
_t2:
	PUSH 2
	CALL printInt
	ADD esp, 4
_after_t2:
	PUSH 0
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

