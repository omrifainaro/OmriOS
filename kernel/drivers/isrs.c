#include "../include/system.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isrsInstall(){
  addIdtGate(0, (unsigned int)isr0, 0x08, 0x8E);
  addIdtGate(1, (unsigned int)isr1, 0x08, 0x8E);
  addIdtGate(2, (unsigned int)isr2, 0x08, 0x8E);
  addIdtGate(3, (unsigned int)isr3, 0x08, 0x8E);
  addIdtGate(4, (unsigned int)isr4, 0x08, 0x8E);
  addIdtGate(5, (unsigned int)isr5, 0x08, 0x8E);
  addIdtGate(6, (unsigned int)isr6, 0x08, 0x8E);
  addIdtGate(7, (unsigned int)isr7, 0x08, 0x8E);
  addIdtGate(8, (unsigned int)isr8, 0x08, 0x8E);
  addIdtGate(9, (unsigned int)isr9, 0x08, 0x8E);
  addIdtGate(10, (unsigned int)isr10, 0x08, 0x8E);
  addIdtGate(11, (unsigned int)isr11, 0x08, 0x8E);
  addIdtGate(12, (unsigned int)isr12, 0x08, 0x8E);
  addIdtGate(13, (unsigned int)isr13, 0x08, 0x8E);
  addIdtGate(14, (unsigned int)isr14, 0x08, 0x8E);
  addIdtGate(15, (unsigned int)isr15, 0x08, 0x8E);
  addIdtGate(16, (unsigned int)isr16, 0x08, 0x8E);
  addIdtGate(17, (unsigned int)isr17, 0x08, 0x8E);
  addIdtGate(18, (unsigned int)isr18, 0x08, 0x8E);
  addIdtGate(19, (unsigned int)isr19, 0x08, 0x8E);
  addIdtGate(20, (unsigned int)isr20, 0x08, 0x8E);
  addIdtGate(21, (unsigned int)isr21, 0x08, 0x8E);
  addIdtGate(22, (unsigned int)isr22, 0x08, 0x8E);
  addIdtGate(23, (unsigned int)isr23, 0x08, 0x8E);
  addIdtGate(24, (unsigned int)isr24, 0x08, 0x8E);
  addIdtGate(25, (unsigned int)isr25, 0x08, 0x8E);
  addIdtGate(26, (unsigned int)isr26, 0x08, 0x8E);
  addIdtGate(27, (unsigned int)isr27, 0x08, 0x8E);
  addIdtGate(28, (unsigned int)isr28, 0x08, 0x8E);
  addIdtGate(29, (unsigned int)isr29, 0x08, 0x8E);
  addIdtGate(30, (unsigned int)isr30, 0x08, 0x8E);
  addIdtGate(31, (unsigned int)isr31, 0x08, 0x8E);
  printString("All isrs are now handled!\n", GREEN_ON_BLACK);
}

unsigned char* exceptionMsgs[] = { //need to fix global variable problem
  "Division By Zero Exception\n",
  "Debug Exception\n",
  "Maskable Interrupt Exception\n",
  "Breakpoint Exception\n",
  "Into Detected Overflow Exception\n",
  "Out of Bounds Exception\n",
  "Invalid Opcode Exception\n",
  "Coprocessor Exception\n",
  "Double Fault Exception\n",
  "Coprocessor Segment Overrun Exception\n",
  "0Bad TSS Exception\n",
  "Segment t Present Exception\n",
  "Stack Fault Exception\n",
  "General Protection Fault Exception\n",
  "Page Fault Exception\n",
  "Unkwn Interrupt Exception\n",
  "Coprocessor Fault Exception\n",
  "Alignment Check Exception (+)\n",
  "Machine Check Exception (Pentium/+)\n",
  "Reserved Exceptions\n",
};
void faultHandler(PSTACK_SNAPSHOT r){
  printString("Fault recieved - ", RED_ON_BLACK);
  if(r->intNum < 32){
    if(r->intNum > 19)
      r->intNum = 19;
    printString(exceptionMsgs[r->intNum], RED_ON_BLACK);
    printString("\n", WHITE_ON_BLACK);
    __asm__("sti");
    for(;;);
  }
}
