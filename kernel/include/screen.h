#ifndef SCREEN_H
#define SCREEN_H

#include "../include/ports.h"

#define VIDEO_BASE 0xb8000
#define WHITE_ON_BLACK 0x0f
#define BLUE_ON_BLACK 0x01
#define GREEN_ON_BLACK 0x0a
#define CYAN_ON_BLACK 0x03
#define RED_ON_BLACK 0x04
#define PURPLE_ON_BLACK 0x05
#define LBLUE_ON_BLACK 0x09
#define ERROR_MSG_COLOR 0x40

#define WIDTH 80
#define HEIGHT 25

#define VIDEO_SIZE WIDTH*HEIGHT*2

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

unsigned int getScreenOffset(int x, int y);
unsigned int getCursorOffset();
void setCursorOffset(unsigned int offset);
void clearScreen();

#endif
