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
	PUSH 0
	CALL printInt
	ADD esp, 4
	MOV [ebp - 4], DWORD PTR 0
_t1:
	PUSH 1
	CALL printInt
	ADD esp, 4
_after_t1:
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
_t2:
	PUSH 2
	CALL printInt
	ADD esp, 4
_after_t2:
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

