#include "../include/ports.h"

unsigned char readBytePort(unsigned short port) {
// "=a" (result) means : put AL register in variable RESULT when finished
// "d" (port) means : load EDX with port
  unsigned char result ;
  __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result ;
}

void writeBytePort(unsigned short port, unsigned char data) {
  // "a" ( data ) means : load EAX with data
  // "d" ( port ) means : load EDX with port
  __asm__ ("out %%al , %%dx": :"a" (data), "d" (port));
}

unsigned short readWordPort(unsigned short port) {
  unsigned short result;
  __asm__ ("in %%dx, %%ax ":"=a"(result):"d"(port));
  return result;
}
void writeWordPort(unsigned short port, unsigned short data) {
  __asm__ ("out %%ax, %%dx": :"a"(data),"d"(port));
}
