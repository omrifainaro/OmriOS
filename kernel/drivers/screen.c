#include "../include/screen.h"

static inline unsigned int getScreenOffset(int x, int y){
  return 2 * ((y * WIDTH) + x);
}

void printHex(unsigned int value){
  char* chars = "0123456789ABCDEF";
  int i = sizeof(int) * 2; //value in nibbles
  char cur;
  for(; i >= 0; value = value >> 4, i--){
    cur = (char) chars[value & 0xf];
    printChar(cur, i, 0, WHITE_ON_BLACK);
  }
}

void printString(char* string, char style){
  int i, y;
  short* memptr = (short*)(getCursorOffset() + VIDEO_BASE);
  for(i = 0; string[i]; i++){
    if(string[i] == '\n'){
      y = ((unsigned long)memptr - VIDEO_BASE) / (2*WIDTH) + 1;
      setCursorOffset(getScreenOffset(0, y));
      memptr = (short*)(getCursorOffset() + VIDEO_BASE);
      continue;
    }
    *memptr = string[i] | (style << 8);
    memptr++;
  }
  setCursorOffset((unsigned int)memptr - VIDEO_BASE);
  if((unsigned long)memptr > (VIDEO_BASE + VIDEO_SIZE)){
    memcpy((char*)memptr - VIDEO_SIZE, (char*)VIDEO_BASE, VIDEO_SIZE);
  }
}

void putchar(char c, char style){
  short* memptr = (short*)(getCursorOffset() + VIDEO_BASE);
  *memptr = c | (style << 8);
  memptr++;
  setCursorOffset((unsigned int)memptr - VIDEO_BASE);
}

void printInteger(unsigned int num){
  char integer[21];
  int i = 0;
  memset(integer, 0, 21);
  integer[0] = '0';
  while(num > 0 && i < 20){
    integer[i++] = (num % 10) + '0';
    num /= 10;
  }
  printString(integer, WHITE_ON_BLACK);
}

void printChar(char c, int x, int y, char style){
  unsigned int offset;
  char* memptr = (char*)VIDEO_BASE;
  offset = getScreenOffset(x, y);
  memptr[offset] = c;
  memptr[offset+1] = style;
}

unsigned int getCursorOffset(){
  writeBytePort(REG_SCREEN_CTRL, 14);
  unsigned int offset = readBytePort(REG_SCREEN_DATA) << 8;
  writeBytePort(REG_SCREEN_CTRL, 15);
  offset |= readBytePort(REG_SCREEN_DATA);
  return offset*2;
}

void setCursorOffset(unsigned int offset){
  offset /= 2;
  writeBytePort(REG_SCREEN_CTRL, 14); //High order byte offset
  writeBytePort(REG_SCREEN_DATA, offset >> 8);
  writeBytePort(REG_SCREEN_CTRL, 15);
  writeBytePort(REG_SCREEN_DATA, offset & 0xff);
}

void clearScreen(){
  int x, y;
  for(x = 0; x < WIDTH; x++){
    for (y = 0; y < HEIGHT; y++) {
      printChar(' ', x, y, WHITE_ON_BLACK);
    }
  }
}

void printStringAt(char* string, int x, int y, char style){
  int i;
  for(i = 0; string[i]; i++){
    printChar(string[i], x+i, y, style);
  }
}
