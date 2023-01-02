main:
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, 1
	MOV [ebp - 4] (_d0_a), eax
_t1:
	MOV eax, [ebp - 4] (_d0_a)
	ADD eax, 1
_after_t1:
	MOV eax, [ebp - 4] (_d0_a)
	leave
	ret

f:
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 8] (__arg__0)
	ADD eax, [ebp + 8] (__arg__0)
	MOV ebx, [ebp + 8] (__arg__0)
	IMUL ebx, [ebp + 12] (__arg__1)
	ADD eax, ebx
	leave
	ret

