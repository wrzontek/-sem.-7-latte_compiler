.intel_syntax noprefix
.section  .rodata
.SC0:
	.string ""
.SC1:
	.string "/* world"
.SC2:
	.string "="
.SC3:
	.string "hello */"
.text
.globl main
main:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	PUSH 10
	CALL fac
	ADD esp, 4
	MOV ebx, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV ebx, eax
	PUSH 10
	CALL rfac
	ADD esp, 4
	MOV edi, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV edi, eax
	PUSH 10
	CALL mfac
	ADD esp, 4
	MOV esi, eax
	PUSH eax
	CALL printInt
	ADD esp, 4
	MOV esi, eax
	PUSH 10
	CALL ifac
	ADD esp, 4
	PUSH eax
	PUSH eax
	CALL printInt
	ADD esp, 4
_t1:
	MOV [ebp - 4], DWORD PTR 10
	MOV [ebp - 8], DWORD PTR 1
	JMP _while_cond_2
_while_body_2:
	MOV eax, [ebp - 8]
	IMUL eax, DWORD PTR [ebp - 4]
	MOV ebx, [ebp - 4]
	SUB ebx, 1
	MOV [ebp - 4], ebx
	MOV [ebp - 8], eax
_while_cond_2:
	MOV eax, [ebp - 4]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_2
	JMP _end_while_2
_end_while_2:
	PUSH DWORD PTR [ebp - 8]
	CALL printInt
	ADD esp, 4
_after_t1:
	PUSH 60
	LEA eax, .SC2
	PUSH eax
	CALL repStr
	ADD esp, 8
	MOV ebx, eax
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV ebx, eax
	LEA eax, .SC3
	PUSH eax
	CALL printString
	ADD esp, 4
	MOV edi, eax
	LEA eax, .SC1
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

fac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV eax, [ebp + 20]
	MOV [ebp - 4], eax
	MOV [ebp - 8], DWORD PTR 1
	JMP _while_cond_3
_while_body_3:
	MOV eax, [ebp - 8]
	IMUL eax, DWORD PTR [ebp - 4]
	MOV ebx, [ebp - 4]
	SUB ebx, 1
	MOV [ebp - 4], ebx
	MOV [ebp - 8], eax
_while_cond_3:
	MOV eax, [ebp - 4]
	CMP eax, 0
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _while_body_3
	JMP _end_while_3
_end_while_3:
	MOV eax, [ebp - 8]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

rfac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_4
	JMP _if_false_4
_if_true_4:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_4:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, eax
	PUSH eax
	CALL rfac
	ADD esp, 4
	MOV ebx, [ebp + 20]
	IMUL ebx, eax
	MOV eax, ebx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_4:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

mfac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_5
	JMP _if_false_5
_if_true_5:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_5:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, eax
	PUSH eax
	CALL nfac
	ADD esp, 4
	MOV ebx, [ebp + 20]
	IMUL ebx, eax
	MOV eax, ebx
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_5:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

nfac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 4
	MOV eax, [ebp + 20]
	CMP eax, 0
	MOV eax, 0
	SETNE al
	TEST eax, eax
	JNZ _if_true_6
	JMP _if_false_6
_if_true_6:
	MOV eax, [ebp + 20]
	SUB eax, 1
	MOV ebx, eax
	PUSH eax
	CALL mfac
	ADD esp, 4
	IMUL eax, DWORD PTR [ebp + 20]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_if_false_6:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_6:
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

ifac:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	PUSH DWORD PTR [ebp + 20]
	PUSH 1
	CALL ifac2f
	ADD esp, 8
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

ifac2f:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 8
	MOV eax, [ebp + 20]
	CMP eax, DWORD PTR [ebp + 24]
	MOV eax, 0
	SETE al
	TEST eax, eax
	JNZ _if_true_7
	JMP _end_if_7
_if_true_7:
	MOV eax, [ebp + 20]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_7:
	MOV eax, [ebp + 20]
	CMP eax, DWORD PTR [ebp + 24]
	MOV eax, 0
	SETG al
	TEST eax, eax
	JNZ _if_true_8
	JMP _end_if_8
_if_true_8:
	MOV eax, 1
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret
_end_if_8:
	MOV eax, [ebp + 20]
	ADD eax, DWORD PTR [ebp + 24]
	SAR eax, 1
	MOV ebx, eax
	PUSH eax
	PUSH DWORD PTR [ebp + 20]
	CALL ifac2f
	ADD esp, 8
	ADD ebx, 1
	MOV edi, eax
	PUSH DWORD PTR [ebp + 24]
	PUSH ebx
	CALL ifac2f
	ADD esp, 8
	IMUL edi, eax
	MOV eax, edi
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

repStr:
	push ebx
	push edi
	push esi
	push ebp
	mov ebp, esp
	sub esp, 16
	LEA eax, .SC0
	MOV [ebp - 12], DWORD PTR 0
	MOV [ebp - 16], eax
	JMP _while_cond_9
_while_body_9:
	PUSH DWORD PTR [ebp + 20]
	PUSH DWORD PTR [ebp - 16]
	CALL _stringsConcat
	ADD esp, 8
	MOV ebx, [ebp - 12]
	ADD ebx, 1
	MOV [ebp - 12], ebx
	MOV [ebp - 16], eax
_while_cond_9:
	MOV eax, [ebp - 12]
	CMP eax, DWORD PTR [ebp + 24]
	MOV eax, 0
	SETL al
	TEST eax, eax
	JNZ _while_body_9
	JMP _end_while_9
_end_while_9:
	MOV eax, [ebp - 16]
	mov esp, ebp
	pop ebp
	pop esi
	pop edi
	pop ebx
	ret

