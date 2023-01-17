.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
_t1:
	MOV eax, 0
	SUB eax, 42
	MOV ebx, 0
	SUB ebx, 1
	CDQ
	IDIV ebx
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
_after_t1:
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

