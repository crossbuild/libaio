root=/
all: libredhat-kernel.so

ASFLAGS=-D__KERNEL__ -D__ASSEMBLY__ -I../include -nostdlib -nostartfiles
CFLAGS=-D__KERNEL__ -I../include -nostdlib -nostartfiles

so_objs=vsysaddr.o kso_init.o

# We can't autogenerate or we'll depend on running a kernel with this
# already installed
make_stub_vsysaddr.S:
	rm -f vsysaddr.S
	echo '#include "stub.S"' >vsysaddr.S
	awk -- "/^bfff.* vsys_/ { print \"dynamic_syscall(\"\$$3 \",0x\" \$$1 \")\"; }" <System.map >>vsysaddr.S

vsysaddr.o: vsysaddr.S

libredhat-kernel.so.1: $(so_objs) libredhat-kernel.map
	gcc -nostdlib -nostartfiles -shared -Wl,--version-script=libredhat-kernel.map -o $@  $(so_objs)
	strip $@

libredhat-kernel.so: libredhat-kernel.so.1
	cp -f $< $@

install:
	install -D -m 755 libredhat-kernel.so.1 $(root)/lib/kernel/stub/libredhat-kernel.so.1
	ln -sf libredhat-kernel.so.1 $(root)/lib/kernel/stub/libredhat-kernel.so

clean:
	rm -f *.o libredhat-kernel.so myln libredhat-kernel.so.1

# test app
myln: myln.c libredhat-kernel.so Makefile
	cc -g -o myln myln.c -L. -lredhat-kernel
