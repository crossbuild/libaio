#define __NR_io_setup		1025 //1238
#define __NR_io_destroy		1239
#define __NR_io_getevents	1240
#define __NR_io_submit		1241
#define __NR_io_cancel		1242

extern long __ia64_aio_raw_syscall(long a, long b, long c, long d, long e, long nr);
#if 0
static long __ia64_raw_syscall(nr, a, b, c, d, e)
{
	long dummy aa, bb, cc, dd, ee;

	__asm__("break __BREAK_SYSCALL\n"
		";;\n"
		"1:\n"
		: "out0" (aa),
		  "out1" (bb),
		  "out2" (cc),
		  "out3" (dd),
		  "out4" (ee),
		  "out5" (ff))
}
#endif

#define syscall5(nr, a, b, c, d, e)	__ia64_aio_raw_syscall(a, b, c, d, e, nr)
#define syscall4(nr, a, b, c, d)	syscall5(nr, a, b, c, d, 0)
#define syscall3(nr, a, b, c)		syscall4(nr, a, b, c, 0)
#define syscall2(nr, a, b)		syscall3(nr, a, b, 0)
#define syscall1(nr, a)			syscall2(nr, a, 0)

