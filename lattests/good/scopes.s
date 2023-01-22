.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR 0
	CALL printInt
	ADD esp, 4
_t1:
	PUSH DWORD PTR 1
	CALL printInt
	ADD esp, 4
_after_t1:
	PUSH DWORD PTR 0
	CALL printInt
	ADD esp, 4
_t2:
	PUSH DWORD PTR 2
	CALL printInt
	ADD esp, 4
_after_t2:
	PUSH DWORD PTR 0
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

