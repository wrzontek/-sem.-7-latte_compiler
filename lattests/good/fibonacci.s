.intel_syntax noprefix
.section  .rodata
.SC0:
	.string "Expected a non-negative integer, but got:"
.text
.globl main
fibonacci:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 16
	MOV eax, [ebp + 20]
	CMP eax, 1
	MOV eax, 0
	SETLE al
	TEST eax, eax
	JNZ _if_true_1
	JMP _end_if_1
_if_true_1:
	MOV eax, [ebp + 20]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_1:
	MOV [ebp - 8], DWORD PTR 0
	MOV [ebp - 12], DWORD PTR 1
	MOV [ebp - 16], DWORD PTR 2
	JMP _while_cond_2
_while_body_2:
	MOV eax, [ebp - 12]
	ADD eax, DWORD PTR [ebp - 8]
	MOV ebx, [ebp - 12]
	MOV ecx, [ebp - 16]
	ADD ecx, 1
	MOV [ebp - 8], ebx
	MOV [ebp - 12], eax
	MOV [ebp - 16], ecx
_while_cond_2:
	MOV eax, [ebp - 16]
	CMP eax, DWORD PTR [ebp + 20]
	MOV eax, 0
	SETLE al
	TEST eax, eax
	JNZ _while_body_2
	JMP _end_while_2
_end_while_2:
	MOV eax, [ebp - 12]
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
	sub esp, 4
	CALL readInt
	MOV ebx, eax
	CMP ebx, 0
	MOV ebx, 0
	SETGE bl
	MOV [ebp - 4], eax
	TEST ebx, ebx
	JNZ _if_true_3
	JMP _if_false_3
_if_true_3:
	PUSH DWORD PTR [ebp - 4]
	CALL fibonacci
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
_if_false_3:
	LEA eax, .SC0
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	PUSH DWORD PTR [ebp - 4]
	CALL printInt
	ADD esp, 4
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_3:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

