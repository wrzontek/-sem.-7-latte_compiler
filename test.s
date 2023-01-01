main:
	push ebp
	mov ebp, esp
	sub esp, 12
	MOV eax, 1
	MOV ebx, 2
	MOV ecx, 3
	MOV edi, ebx
	SUB ebx, eax
	MOV [ebp - 4] (_d0_a), edi
	MOV [ebp - 8] (_d0_c), ecx
	MOV [ebp - 12] (_d0_t), ebx
_t1:
_after_t1:
	MOV eax, [ebp - 4] (_d0_a)
	SUB eax, [ebp - 8] (_d0_c)
	MOV ebx, [ebp - 12] (_d0_t)
	ADD ebx, eax
	ADD ebx, eax
	MOV eax, ebx
	leave
	ret

f:
	push ebp
	mov ebp, esp
	MOV eax, 
	ADD eax, 1
	leave
	ret

