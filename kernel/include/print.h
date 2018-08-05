#ifndef PRINT_H
#define PRINT_H
#include "../include/screen.h"

void printHex(unsigned int value);
void printChar(char c, int x, int y, char style);
void printString(char* string, char style);
void printInteger(unsigned int num);
void printStringAt(char* string, int x, int y, char style);

#endif
