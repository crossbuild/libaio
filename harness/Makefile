# foo.
TEST_SRCS:=$(shell find cases/ -name \*.t)
PROGS:=$(patsubst %.t,%.p,$(TEST_SRCS))
HARNESS_SRCS:=main.c
# io_queue.c

CFLAGS=-Wall -g -O -laio -lredhat-kernel
#-lpthread -lrt

all: $(PROGS)

$(PROGS): %.p: %.t $(HARNESS_SRCS)
	$(CC) $(CFLAGS) -DTEST_NAME=\"$<\" -o $@ main.c

clean:
	rm -f $(PROGS) *.o runtests.out rofile wofile rwfile

rofile:
	touch $@
	chmod 400 $@

wofile:
	touch $@
	chmod 200 $@

rwfile:
	touch $@
	chmod 600 $@

check: $(PROGS) rofile rwfile wofile
	./runtests.sh $(PROGS)

