[ bits 16]
switch_to_pm:
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1 ;turn on pe
	mov cr0, eax
	jmp CODE_SEG:init_pm ;far jump for initializing the cs register.

[ bits 32]
init_pm :
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp
	call BEGIN_PM
