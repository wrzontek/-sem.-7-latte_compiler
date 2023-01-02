main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 123
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx

f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 8] (__arg__0)
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx

