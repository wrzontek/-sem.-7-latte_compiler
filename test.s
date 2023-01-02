main:
	push ebp
	mov ebp, esp
	sub esp, 32
	MOV eax, 1
	MOV ebx, 2
	MOV ecx, 3
	MOV edi, 4
	MOV edx, 1
	MOV esi, 2
	PUSH eax
	MOV eax, 3
	PUSH ebx
	MOV ebx, 4
	MOV [ebp - 4] (_d0_a), [ebp + 40] (_d0_a_p1)
	MOV [ebp - 8] (_d0_b), [ebp + 44] (_d0_b_p2)
	MOV [ebp - 12] (_d0_c), ecx
	MOV [ebp - 16] (_d0_d), edi
	MOV [ebp - 20] (_d0_e), edx
	MOV [ebp - 24] (_d0_f), esi
	MOV [ebp - 28] (_d0_g), eax
	MOV [ebp - 32] (_d0_h), ebx
_t1:
	MOV eax, 123
_after_t1:
	MOV eax, [ebp - 4] (_d0_a)
	ADD eax, [ebp - 8] (_d0_b)
	ADD eax, [ebp - 12] (_d0_c)
	ADD eax, [ebp - 16] (_d0_d)
	ADD eax, [ebp - 20] (_d0_e)
	ADD eax, [ebp - 24] (_d0_f)
	ADD eax, [ebp - 28] (_d0_g)
	ADD eax, [ebp - 32] (_d0_h)
	leave
	ret

