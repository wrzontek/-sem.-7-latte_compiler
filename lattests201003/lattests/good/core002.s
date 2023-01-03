main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	CALL foo
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx

foo:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH  ; argument
	CALL printString
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx

