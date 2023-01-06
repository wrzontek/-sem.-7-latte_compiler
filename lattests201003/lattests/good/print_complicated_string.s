.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "\\a\\n\n\tb\""
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	LEA eax, .SC0
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

