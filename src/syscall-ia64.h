#define __NR_io_setup		1238
#define __NR_io_destroy		1239
#define __NR_io_getevents	1240
#define __NR_io_submit		1241
#define __NR_io_cancel		1242

#define syscall5(nr, a, b, c, d, e)	__ia64_raw_syscall(nr, a, b, c, d, e)
#define syscall4(nr, a, b, c, d)	syscall5(nr, a, b, c, d, 0)
#define syscall3(nr, a, b, c)		syscall4(nr, a, b, c, 0)
#define syscall2(nr, a, b)		syscall3(nr, a, b, 0)
#define syscall1(nr, a)			syscall2(nr, a, 0)

