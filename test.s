	MOV _reg_eax, 0
	MOV _reg_ebx, 0
	MOV _reg_ecx, 0
	ADD _reg_eax, 1
	ADD _reg_ebx, 1
	ADD _reg_ecx, 1

	MOV _reg_edi, _reg_ebx // edi = a
	SUB _reg_ebx, _reg_eax // ebx = a - b == t
	SUB _reg_edi, _reg_ecx // edi = a - c == u
	ADD _reg_ebx, _reg_edi // ebx = t + u == v
	ADD _reg_ebx, _reg_edi // ebx = v + u == d
