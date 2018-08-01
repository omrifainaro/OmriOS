#ifndef SYSTEM_H
#define SYSTEM_H

#include "../include/ports.h"
#include "../include/screen.h"
#include "../utils/utils.h"
#include "../utils/linkedlist.h"

#define IDT_SIZE 256

#define PIC1_CTRL_PRT 0x20
#define PIC1_DATA_PRT 0x21
#define PIC2_CTRL_PRT 0xA0
#define PIC2_DATA_PRT 0xA1

typedef struct _STACK_SNAPSHOT {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* 'pusha' */
    unsigned int intNum, errCode;    /* 'push byte #' and errcode do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
} STACK_SNAPSHOT, *PSTACK_SNAPSHOT;

void idtInstall();
void addIdtGate(unsigned char num, unsigned long addr, unsigned short segment, unsigned char flags);

void isrsInstall();

void irqInstall();
void irqInstallHandler(int irq, void (*handler)(PSTACK_SNAPSHOT r));
void irqUninstallHandler(int irq);
void irqRemap(void);

#endif
