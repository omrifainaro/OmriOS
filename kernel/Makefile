objs = main.o kernelbase.o drivers/screen.o drivers/ports.o drivers/keyboard.o drivers/idt.o drivers/core.o utils/utils.o drivers/isrs.o drivers/irq.o drivers/timer.o utils/print.o

C_FLAGS = --freestanding -c -m32 -fno-pie

all: ${objs}
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 ${objs} --oformat binary
	#ld -T link.ld -m elf_i386 -o kernel.bin ${objs} --oformat binary

%.o: %.c
	gcc ${C_FLAGS} $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

clean:
	rm -fr *.o
	rm -fr *.bin
	rm -fr drivers/*.o
	rm -fr utils/*.o
	rm -fr include/*.o
