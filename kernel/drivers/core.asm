%macro noErrorCodeExeceptionIsr 1
[global isr%1]
isr%1:
  cli
  push byte 0 ;in order to fix stack inconsistency problems
  push byte 0
  jmp isr_common_stub
%endmacro

%macro errorCodeExeceptionIsr 1
[global isr%1]
isr%1:
  cli
  push byte %1
  jmp isr_common_stub
%endmacro

%macro interruptRequest 2
[global irq%1]
irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

noErrorCodeExeceptionIsr 0
noErrorCodeExeceptionIsr 1
noErrorCodeExeceptionIsr 2
noErrorCodeExeceptionIsr 3
noErrorCodeExeceptionIsr 4
noErrorCodeExeceptionIsr 5
noErrorCodeExeceptionIsr 6
noErrorCodeExeceptionIsr 7
noErrorCodeExeceptionIsr 9
noErrorCodeExeceptionIsr 15
noErrorCodeExeceptionIsr 16
noErrorCodeExeceptionIsr 17
noErrorCodeExeceptionIsr 18
noErrorCodeExeceptionIsr 19
noErrorCodeExeceptionIsr 20
noErrorCodeExeceptionIsr 21
noErrorCodeExeceptionIsr 22
noErrorCodeExeceptionIsr 23
noErrorCodeExeceptionIsr 24
noErrorCodeExeceptionIsr 25
noErrorCodeExeceptionIsr 26
noErrorCodeExeceptionIsr 27
noErrorCodeExeceptionIsr 28
noErrorCodeExeceptionIsr 29
noErrorCodeExeceptionIsr 30
noErrorCodeExeceptionIsr 31

errorCodeExeceptionIsr 8
errorCodeExeceptionIsr 10
errorCodeExeceptionIsr 11
errorCodeExeceptionIsr 12
errorCodeExeceptionIsr 13
errorCodeExeceptionIsr 14

interruptRequest 0, 32
interruptRequest 1, 33
interruptRequest 2, 34
interruptRequest 3, 35
interruptRequest 4, 36
interruptRequest 5, 37
interruptRequest 6, 38
interruptRequest 7, 39
interruptRequest 8, 40
interruptRequest 9, 41
interruptRequest 10, 42
interruptRequest 11, 43
interruptRequest 12, 44
interruptRequest 13, 45
interruptRequest 14, 46
interruptRequest 15, 47

[extern faultHandler]
; Save processor state,
; set kernel mode segments,
; calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov eax, esp   ; Push us the stack
  push eax
  mov eax, faultHandler
  call eax       ; A special call, preserves the 'eip' register
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8     ; Cleans up the pushed error code and pushed ISR number
  sti
  iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

[extern irqHandler]
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irqHandler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iret

[global idtLoad]
[extern idtPtr]
idtLoad:
    lidt [idtPtr]
    ret


[global is_A20_on]
is_A20_on:
  pushad
  mov edi,0x112345  ;odd megabyte address.
  mov esi,0x012345  ;even megabyte address.
  mov [esi],esi     ;making sure that both addresses contain diffrent values.
  mov [edi],edi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi))
  cmpsd             ;compare addresses to see if the're equivalent.
  popad
  jne A20_on        ;if not equivalent , A20 line is set.
  mov eax, 0
  ret               ;if equivalent , the A20 line is cleared.
  A20_on:
    mov eax, 1
    ret
