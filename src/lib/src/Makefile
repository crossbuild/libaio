all: libredhat-kernel.so

ASFLAGS=-D__KERNEL__ -D__ASSEMBLY__ -I../include -nostdlib -nostartfiles
CFLAGS=-D__KERNEL__ -I../include -nostdlib -nostartfiles

so_objs=vsysaddr.o kso_init.o

vsysaddr.S: ../System.map stub.S Makefile
	rm -f vsysaddr.S
	echo '#include "stub.S"' >vsysaddr.S
	awk -- "/^bfff.* vsys_/ { print \"dynamic_syscall(\"\$$3 \",0x\" \$$1 \")\"; }" <../System.map >>vsysaddr.S

vsysaddr.o: vsysaddr.S

kso_init.o: ../include/linux/compile.h

libredhat-kernel.so.1: $(so_objs) libredhat-kernel.map
	gcc -nostdlib -nostartfiles -shared -Wl,--version-script=libredhat-kernel.map -o $@  $(so_objs)
	cp $@ $@.save
	strip $@

libredhat-kernel.so: libredhat-kernel.so.1
	ln -sf $< $@

clean:
	rm -f *.o libredhat-kernel.so myln libredhat-kernel.so.1 vsysaddr.S

# test app
myln: myln.c libredhat-kernel.so Makefile
	cc -g -o myln myln.c -L. -lredhat-kernel
