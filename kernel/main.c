#include "include/keyboard.h"
#include "include/system.h"
#include "include/timer.h"
#include "include/print.h"

void kmain(){
	int z = 2;
	int i = 2;
	char c;
	char* str = "Omri's OS (mini shell)\n";

	clearScreen();
	setCursorOffset(0);

	printString(str, BLUE_ON_BLACK);
	printString("[*] Installing a new idt - ", WHITE_ON_BLACK);
	idtInstall();
	printString("[*] Installing a new isr table - ", WHITE_ON_BLACK);
	isrsInstall();
	printString("[*] Intializing PICs and IRQs - ", WHITE_ON_BLACK);
	irqInstall();
	printString("[*] Installing PIT - ",WHITE_ON_BLACK);
	timerInstall();
	printString("[*] Installing keyboard - ",WHITE_ON_BLACK);
	keyboardInstall();
	printString("[*] Done intializing operating system!\n", LBLUE_ON_BLACK);
	__asm__("sti");

	while((c = getch()) != 'q')
		putchar(c, WHITE_ON_BLACK);

	i /= (z - 2);
	while(1);
}
