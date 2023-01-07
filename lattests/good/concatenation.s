.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "a"
.SC1:
	.string "b"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	LEA eax, .SC1
	PUSH eax
	LEA eax, .SC0
	PUSH eax
	CALL _stringsConcat
	ADD esp, 8
	MOV ebx, eax
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

