.intel_syntax noprefix
.text
.globl main
d:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

s:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	MOV eax, [ebp + 20]
	ADD eax, 1
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
	CALL d
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL s
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV eax, 0
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

