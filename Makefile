all: boot.bin kernel/kernel.bin
	cat boot.bin kernel/kernel.bin > os_image

boot.bin: boot.asm
	nasm boot.asm -o boot.bin

kernel/kernel.bin: kernel/Makefile
	make -C kernel/

clean: kernel/kernel.bin boot.bin
	-rm *.bin
	-rm kernel/*.o
	-rm kernel/*.bin
	make -C kernel/ clean
