#include "../include/timer.h"

void timerPhase(int hz) {
  int d = BIG_T / hz;
  writeBytePort(PIT_CTRL_PRT, 0x36);
  writeBytePort(PIT_DATA_PRT, d & 0xff);
  writeBytePort(PIT_DATA_PRT, d >> 8);
}

static int systemTicks = 0;
//running in 18.222hz
void timerHandler(PSTACK_SNAPSHOT snap) {
    systemTicks++;

    // if (systemTicks % 100  == 0) {
    //     printString("Second passed\n", WHITE_ON_BLACK);
    // }
}

void timerInstall() {
    irqInstallHandler(0, timerHandler);
    printString("irq0 - programmable interval timer!\n", GREEN_ON_BLACK);
    timerPhase(100);
}
