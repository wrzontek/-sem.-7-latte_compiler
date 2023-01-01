main:
	MOV _reg_eax, 0
	MOV _reg_ebx, 0
	MOV _reg_ecx, 0
	MOV _reg_edi, _reg_ebx
	SUB _reg_ebx, _reg_eax
	SUB _reg_edi, _reg_ecx
	ADD _reg_ebx, _reg_edi
	ADD _reg_ebx, _reg_edi
	MOV _reg_eax, _reg_ebx
f:
	MOV _reg_eax, [__arg_e]
	ADD _reg_eax, 1
