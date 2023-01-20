.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 2
	ADD eax, 3
	MOV ebx, 2
	SUB ebx, 3
	MOV ecx, 3
	SAL ecx, 1
	MOV edi, 3
	SAR edi, 1
	ADD eax, eax
	ADD eax, ebx
	ADD eax, ebx
	ADD eax, ecx
	ADD eax, ecx
	ADD eax, edi
	ADD eax, edi
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

