#define __NR_io_setup		206
#define __NR_io_destroy		207
#define __NR_io_getevents	208
#define __NR_io_submit		209
#define __NR_io_cancel		210

#define io_syscall1(type, fname, sname, type1, arg1)			\
	type fname(type1 arg1)						\
	{								\
		long __ret;						\
		__asm__ __volatile__("syscall" : "=a" (__ret) :	\
			"0" (__NR_##sname), "D" (arg1));		\
		return __ret;						\
	}

#define io_syscall2(type, fname, sname, type1, arg1, type2, arg2)	\
	type fname(type1 arg1, type2 arg2)				\
	{								\
		long __ret;						\
		__asm__ __volatile__("syscall" : "=a" (__ret) :	\
			"0" (__NR_##sname), "D" (arg1), "S" (arg2));	\
		return __ret;						\
	}

#define io_syscall3(type, fname, sname, type1, arg1, type2, arg2, type3, arg3)	\
	type fname(type1 arg1, type2 arg2, type3 arg3)			\
	{								\
		long __ret;						\
		__asm__ __volatile__("syscall" : "=a" (__ret) :	\
			"0" (__NR_##sname), "D" (arg1), "S" (arg2),	\
			"d" (arg3)					\
			);						\
		return __ret;						\
	}

#define io_syscall4(type, fname, sname, type1, arg1, type2, arg2, type3, arg3, type4, arg4)	\
	type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4)	\
	{								\
		long __ret;						\
		__asm__ __volatile__("movq %5,%%r10 ; syscall" : "=a" (__ret) :	\
			"0" (__NR_##sname), "D" (arg1), "S" (arg2),	\
			"d" (arg3), "g" (arg4)				\
			);						\
		return __ret;						\
	}

#define io_syscall5(type, fname, sname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)	\
	type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
	{								\
		long __ret;						\
		__asm__ __volatile__("movq %5,%%r10 ; movq %6,%%r8 ; syscall" : "=a" (__ret) :	\
			"0" (__NR_##sname), "D" (arg1), "S" (arg2),	\
			"d" (arg3), "g" (arg4), "g" (arg5)		\
			);						\
		return __ret;						\
	}

