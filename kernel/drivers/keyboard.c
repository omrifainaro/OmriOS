#include "../include/keyboard.h"

static unsigned char keyboardLayout[128] =
{ //need to fix global variables
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0,
  ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char STDIN[STDIN_SIZE];
unsigned int count = 0;
void keyboardHandler(PSTACK_SNAPSHOT snap){
  unsigned char scancode;
  scancode = readBytePort(KEYBOARD_DATA_PRT);
  if (scancode & 0x80){
    //printString("Hit", WHITE_ON_BLACK);

  }
  else{
    count%=STDIN_SIZE;
    STDIN[count] = keyboardLayout[scancode];
    putchar(keyboardLayout[scancode], WHITE_ON_BLACK);
    count++;
  }
}

char getch(){
  unsigned int cur = count;
  while(count == cur);
  //printString("Got!", WHITE_ON_BLACK);
  return STDIN[cur];
}

extern void is_A20_on();
static void enableA20(){
  char a;
  register int ret asm("eax");
  is_A20_on();
  if(!ret)
    printString("A20 is off!", GREEN_ON_BLACK);
  else{
    printString("A20 is on!", GREEN_ON_BLACK);
    return;
  }
  a = readBytePort(0x92);
  a |= 2;
  writeBytePort(0x92, a);
}

void keyboardInstall(){
  //writeBytePort(0x21 , 0xFD);
  irqInstallHandler(1, keyboardHandler);
  printString("\n    ", WHITE_ON_BLACK);
  enableA20();
  printString("\n    irq1 keyboard ready\n", GREEN_ON_BLACK);
}
