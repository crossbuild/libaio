#define __NR_io_setup		245
#define __NR_io_destroy		246
#define __NR_io_getevents	247
#define __NR_io_submit		248
#define __NR_io_cancel		249

#define syscall1(nr, a) ({					\
	long __ret;						\
	__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
		"0" (nr), "b" (a));				\
	__ret; })

#define syscall2(nr, a, b) ({					\
	long __ret;						\
	__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
		"0" (nr), "b" (a), "c" (b));			\
	__ret; })

#define syscall3(nr, a, b, c) ({				\
	long __ret;						\
	__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
		"0" (nr), "b" (a), "c" (b), "d" (c));		\
	__ret; })

#define syscall4(nr, a, b, c, d) ({				\
	long __ret;						\
	__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
		"0" (nr), "b" (a), "c" (b), "d" (c), "S" (d));	\
	__ret; })

#define syscall5(nr, a, b, c, d, e) ({				\
	long __ret;						\
	__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
		"0" (nr), "b" (a), "c" (b), "d" (c), "S" (d), "D" (e));	\
	__ret; })

