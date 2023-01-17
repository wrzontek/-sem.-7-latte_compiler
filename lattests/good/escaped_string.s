.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "\"\npop\npowrot:\ngetstatic java/lang/System/out Ljava/io/PrintStream;\nldc \"zle \"\ninvokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\ngoto powrot\nldc \""
.text
.globl main
f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 20]
	SAL eax, 1
	MOV ebx, [ebp + 20]
	ADD ebx, eax
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV eax, ebx
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
	PUSH 1
	CALL f
	ADD esp, 4
	SUB eax, 3
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

