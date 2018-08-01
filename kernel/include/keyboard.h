#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../include/system.h"

#define STDIN_SIZE 100
#define KEYBOARD_CTRL_PRT 0x64
#define KEYBOARD_DATA_PRT 0x60

void keyboardHandler(PSTACK_SNAPSHOT snap);
void keyboardInstall();
char getch();

#endif
