[org 0x7c00]
KERNEL_OFFSET equ 0x1000
STACK_OFFSET equ 0x8000
start:
	mov [BOOT_DRIVE], dl ;Get the default boot drive from the bios
	mov bp, STACK_OFFSET
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print_string

	mov bx, MSG_LOAD_KERNEL
	call print_string
	mov bx, KERNEL_OFFSET ;Kernel physical memory address;
	mov dh, 17 ;size of our kernel (oversized lol)
	mov dl, [BOOT_DRIVE]
	call disk_load
	call switch_to_pm
	jmp $

%include "bits16/strings.asm"
%include "bits16/disk.asm"
%include "bits32/gdt.asm"
%include "bits16/switchtopm.asm"
%include "bits32/strings_pm.asm"

[bits 32]
BEGIN_PM:
	mov esi, MSG_PROT_MODE
	call print_string_pm
	jmp KERNEL_OFFSET

BOOT_DRIVE: db 0
MSG_REAL_MODE: db "Realmode 16 bit os omri's boot loader", 0xd, 0xa, 0
MSG_PROT_MODE: db "ProtecedMode 32 bit os is on!", 0
MSG_LOAD_KERNEL: db "MSG_LOAD_KERNEL", 0xd, 0xa, 0
times 510 - ($ - $$) db 0
dw 0xaa55
