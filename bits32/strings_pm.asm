VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;esi - string
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY
	print_loop:
		mov al, [esi]
		mov ah, WHITE_ON_BLACK
		cmp al, 0
		jz stop
		mov [edx], ax
		inc edx
		inc edx
		inc esi
		jmp print_loop
	stop:
		popa
		ret