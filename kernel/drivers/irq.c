#include "../include/system.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void (*irqFuncs[16])(PSTACK_SNAPSHOT r) = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void irqInstallHandler(int irq, void (*handler)(PSTACK_SNAPSHOT r)) {
    irqFuncs[irq] = handler;
}

void irqUninstallHandler(int irq) {
    irqFuncs[irq] = 0;
}

void irqRemap(void) {
    writeBytePort(PIC1_CTRL_PRT, 0x11);
    writeBytePort(PIC2_CTRL_PRT, 0x11);
    writeBytePort(PIC1_DATA_PRT, 0x20);
    writeBytePort(PIC2_DATA_PRT, 0x28);
    writeBytePort(PIC1_DATA_PRT, 0x04);
    writeBytePort(PIC2_DATA_PRT, 0x02);
    writeBytePort(PIC1_DATA_PRT, 0x01);
    writeBytePort(PIC2_DATA_PRT, 0x01);
    writeBytePort(PIC1_DATA_PRT, 0x0);
    writeBytePort(PIC2_DATA_PRT, 0x0);
}

void irqInstall() {
    irqRemap();
    addIdtGate(32, (unsigned)irq0, 0x08, 0x8E);
    addIdtGate(33, (unsigned)irq1, 0x08, 0x8E);
    addIdtGate(34, (unsigned)irq2, 0x08, 0x8E);
    addIdtGate(35, (unsigned)irq3, 0x08, 0x8E);
    addIdtGate(36, (unsigned)irq4, 0x08, 0x8E);
    addIdtGate(37, (unsigned)irq5, 0x08, 0x8E);
    addIdtGate(38, (unsigned)irq6, 0x08, 0x8E);
    addIdtGate(39, (unsigned)irq7, 0x08, 0x8E);
    addIdtGate(40, (unsigned)irq8, 0x08, 0x8E);
    addIdtGate(41, (unsigned)irq9, 0x08, 0x8E);
    addIdtGate(42, (unsigned)irq10, 0x08, 0x8E);
    addIdtGate(43, (unsigned)irq11, 0x08, 0x8E);
    addIdtGate(44, (unsigned)irq12, 0x08, 0x8E);
    addIdtGate(45, (unsigned)irq13, 0x08, 0x8E);
    addIdtGate(46, (unsigned)irq14, 0x08, 0x8E);
    addIdtGate(47, (unsigned)irq15, 0x08, 0x8E);
    printString("PICs initialized, irqs are now blank!\n", GREEN_ON_BLACK);
}

void irqHandler(PSTACK_SNAPSHOT snap)
{
  //printString("IRQ called!", WHITE_ON_BLACK);
  void (*handler)(PSTACK_SNAPSHOT snap);

  handler = irqFuncs[snap->intNum - 32];
  if (handler) {
    handler(snap);
  }
  else{
    printString("Unhandled irq called", 0x40);
  }

  if (snap->intNum >= 40){
    writeBytePort(PIC2_CTRL_PRT, 0x20);
  }

  writeBytePort(PIC1_CTRL_PRT, 0x20);
}
