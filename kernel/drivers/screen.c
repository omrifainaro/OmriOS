#include "../include/screen.h"

unsigned int getScreenOffset(int x, int y){
  return 2 * ((y * WIDTH) + x);
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
