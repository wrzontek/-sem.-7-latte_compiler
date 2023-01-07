.intel_syntax noprefix
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL readInt
	MOV ebx, eax
	CALL readString
	MOV edi, eax
	CALL readString
	SUB ebx, 5
	MOV esi, eax
	PUSH ebx
	CALL printInt
	ADD esp, 4
	MOV ebx, eax
	PUSH esi
	PUSH edi
	CALL _stringsConcat
	ADD esp, 8
	MOV edi, eax
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

