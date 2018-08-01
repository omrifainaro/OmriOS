#ifndef TIMER_H
#define TIMER_H
#include "../include/system.h"

#define BIG_T 1193180
#define PIT_CTRL_PRT 0x43
#define PIT_DATA_PRT 0x40

void timerPhase(int hz);
void timerHandler(PSTACK_SNAPSHOT snap);
void timerInstall();

#endif
