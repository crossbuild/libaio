prefix=usr

CFLAGS=-nostdlib -nostartfiles -Wall -I. -g -fomit-frame-pointer -O2
SO_CFLAGS=-shared $(CFLAGS)
L_CFLAGS=$(CFLAGS)
LINK_FLAGS=-L. -lredhat-kernel

soname=libaio.so.1
all_targets += libaio.a $(soname)

all: $(all_targets)

libredhat-kernel.so:
	@$(MAKE) -C lib/src
	@cp lib/src/libredhat-kernel.so.1 ./
	@ln -sf libredhat-kernel.so.1 libredhat-kernel.so

libaio_srcs := io_queue_init.c io_submit.c io_cancel.c io_queue_wait.c
libaio_srcs += io_queue_run.c

libaio_objs := $(patsubst %.c,%.ol,$(libaio_srcs))
libaio_sobjs := $(patsubst %.c,%.os,$(libaio_srcs))

$(libaio_objs) $(libaio_sobjs): libaio.h vsys_def.h

%.os: %.c
	$(CC) $(SO_CFLAGS) -c -o $@ $<

%.ol: %.c
	$(CC) $(L_CFLAGS) -c -o $@ $<


libaio.a: $(libaio_objs)
	rm -f libaio.a
	ar r libaio.a $^
	ranlib libaio.a

$(soname): $(libaio_sobjs) libredhat-kernel.so
	$(CC) $(SO_CFLAGS) -Wl,--version-script=libaio.map -Wl,-soname=$(soname) -o $@ $^ $(LINK_FLAGS)

install: $(all_targets)
	@$(MAKE) -C lib/src install
	install -D -m 644 libaio.h $(prefix)/include/libaio.h
	install -D -m 644 libaio.a $(prefix)/lib/libaio.a
	install -D -m 755 $(soname) $(prefix)/lib/$(soname)
	ln -sf $(soname) $(prefix)/lib/libaio.so

$(libaio_objs): libaio.h

clean:
	rm -f $(all_targets) $(libaio_objs) $(libaio_sobjs) $(soname).new
	rm -f *.so *.a *.o
	rm -f lib/*.so*
	@$(MAKE) -C lib/src clean
