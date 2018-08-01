;bx - string
print_string:
	mov ah, 0x0e
	print_char:
		mov al, [bx]
		cmp al, 0
		jz ender
		inc bx
		int 0x10
		jmp print_char 	
	ender:
		ret