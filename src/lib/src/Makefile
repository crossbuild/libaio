root=/
all: libredhat-kernel.so

ASFLAGS=-D__KERNEL__ -D__ASSEMBLY__ -I../include -nostdlib -nostartfiles
CFLAGS=-D__KERNEL__ -I../include -nostdlib -nostartfiles
soname=libredhat-kernel.so.1
dummyver=.0.0
extraver=.0.1

so_objs=vsysaddr.o kso_init.o

# We can't autogenerate or we'll depend on running a kernel with this
# already installed
make_stub_vsysaddr.S:
	rm -f vsysaddr.S
	echo '#include "stub.S"' >vsysaddr.S
	awk -- "/^bfff.* vsys_/ { print \"dynamic_syscall(\"\$$3 \",0x\" \$$1 \")\"; }" <System.map >>vsysaddr.S

vsysaddr.o: vsysaddr.S

$(soname): $(so_objs) libredhat-kernel.map
	gcc -nostdlib -nostartfiles -shared -Wl,--version-script=libredhat-kernel.map -Wl,-soname=$(soname) -o $@  $(so_objs)
	strip $@

libredhat-kernel.so: $(soname)
	cp -f $< $@

install:
	install -D -m 755 $(soname) $(root)/lib/kernel/stub/$(soname)$(extraver)
	install -D -m 755 $(soname) $(root)/lib/$(soname)$(dummyver)
	ln -sf $(soname)$(extraver) $(root)/lib/kernel/stub/libredhat-kernel.so
	mkdir -p $(root)/usr/lib
	ln -sf /lib/libredhat-kernel.so $(root)/usr/lib/libredhat-kernel.so

clean:
	rm -f *.o *.so myln $(soname)

# test app
myln: myln.c libredhat-kernel.so Makefile
	cc -g -o myln myln.c -L. -lredhat-kernel
