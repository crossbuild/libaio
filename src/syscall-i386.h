#define __NR_io_setup		245
#define __NR_io_destroy		246
#define __NR_io_getevents	247
#define __NR_io_submit		248
#define __NR_io_cancel		249

#define io_syscall1(type, name, type1, arg1)				\
	type name(type1 arg1)						\
	{								\
		long __ret;						\
		__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
			"0" (__NR_##name), "b" (arg1));			\
		return __ret;						\
	}

#define io_syscall2(type, name, type1, arg1, type2, arg2)		\
	type name(type1 arg1, type2 arg2)				\
	{								\
		long __ret;						\
		__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
			"0" (__NR_##name), "b" (arg1), "c" (arg2));	\
		return __ret;						\
	}

#define io_syscall3(type, name, type1, arg1, type2, arg2, type3, arg3)	\
	type name(type1 arg1, type2 arg2, type3 arg3)			\
	{								\
		long __ret;						\
		__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
			"0" (__NR_##name), "b" (arg1), "c" (arg2),	\
			"d" (arg3)					\
			);						\
		return __ret;						\
	}

#define io_syscall4(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4)	\
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4)	\
	{								\
		long __ret;						\
		__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
			"0" (__NR_##name), "b" (arg1), "c" (arg2),	\
			"d" (arg3), "S" (arg4)				\
			);						\
		return __ret;						\
	}

#define io_syscall5(type, name, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5)	\
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5)	\
	{								\
		long __ret;						\
		__asm__ __volatile__("int $0x80" : "=a" (__ret) :	\
			"0" (__NR_##name), "b" (arg1), "c" (arg2),	\
			"d" (arg3), "S" (arg4), "D" (arg5)		\
			);						\
		return __ret;						\
	}

