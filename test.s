v:
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, [ebp + 8] (__arg__0)
	IMUL eax, [ebp + 8] (__arg__0)
	MOV [ebp + 8] (__arg__0), eax
	GOTO _if_false_1
_if_false_1:
	MOV eax, [ebp + 8] (__arg__0)
	SUB eax, 1
	MOV [ebp + 8] (__arg__0), eax
_end_if_1:
	MOV eax, [ebp + 8] (__arg__0)
	ADD eax, 5
	leave
	ret

main:
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV eax, 1
	MOV ebx, 2
	MOV ecx, 1
	MOV [ebp - 4] (_d0_a), eax
	MOV [ebp - 8] (_d0_b), ebx
	TEST ecx, ecx
	JNZ _if_true_2
	GOTO _if_false_2
_if_true_2:
	MOV eax, [ebp - 4] (_d0_a)
	leave
	ret
_if_false_2:
	MOV eax, [ebp - 8] (_d0_b)
	leave
	ret

f:
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 8] (__arg__0)
	CDQ
	IDIV [ebp + 12] (__arg__1)
	MOV eax, edx
	leave
	ret

