root=/
all: libredhat-kernel.so

ASFLAGS=-D__KERNEL__ -D__ASSEMBLY__ -I../include -nostdlib -nostartfiles
CFLAGS=-Wall -D__KERNEL__ -I../include -nostdlib -nostartfiles -O2 -fomit-frame-pointer
soname=libredhat-kernel.so.1
dummyver=.0.0
extraver=.0.1

so_objs=aio_syscalls.o

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
	ln -sf /lib/$(soname)$(dummyver) $(root)/usr/lib/libredhat-kernel.so

clean:
	rm -f *.o *.so myln $(soname)

# test app
myln: myln.c libredhat-kernel.so Makefile
	cc -g -o myln myln.c -L. -lredhat-kernel
