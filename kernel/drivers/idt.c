#include "../include/system.h"

struct IDT_ENTRY{
  unsigned short loAddr;
  unsigned short segment;
  unsigned char zPadding;
  unsigned char flags;
  unsigned short hiAddr;
}__attribute__((packed));

struct IDT_PTR {
  unsigned short limit;
  unsigned int addr;
} __attribute__((packed));

struct IDT_ENTRY idt[IDT_SIZE];
struct IDT_PTR idtPtr;

extern void idtLoad();

void idtInstall(){
  idtPtr.limit = sizeof(struct IDT_PTR) * 256 - 1;
  idtPtr.addr = (unsigned int)&idt;
  memset((char*)&idt, 0, sizeof(struct IDT_PTR) * 256);
  idtLoad();
  printString("Idt table is loaded\n", GREEN_ON_BLACK);
}

void addIdtGate(unsigned char num, unsigned long addr, unsigned short segment, unsigned char flags){
  idt[num].loAddr = addr & 0xffff;
  idt[num].hiAddr = (addr >> 16) & 0xffff;
  idt[num].segment = segment;
  idt[num].flags = flags;
}
