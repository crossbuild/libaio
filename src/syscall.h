#include <sys/syscall.h>

#define _SYMSTR(str)	#str
#define SYMSTR(str)	_SYMSTR(str)

#define SYMVER(compat_sym, orig_sym, ver_sym)	\
	__asm__(".symver " SYMSTR(compat_sym) "," SYMSTR(orig_sym) "@LIBAIO_" SYMSTR(ver_sym));

#define DEFSYMVER(compat_sym, orig_sym, ver_sym)	\
	__asm__(".symver " SYMSTR(compat_sym) "," SYMSTR(orig_sym) "@@LIBAIO_" SYMSTR(ver_sym));

#if defined(__i386__)
#include "syscall-i386.h"
#elif defined(__x86_64__)
#include "syscall-x86_64.h"
#elif defined(__ia64__)
#include "syscall-ia64.h"
#elif defined(__PPC__)
#include "syscall-ppc.h"
#elif defined(__s390__)
#include "syscall-s390.h"
#else
#error "add syscall-arch.h"
#endif


#define io_syscall1(type, fname, sname, type1, arg1)	\
	type fname(type1 arg1)				\
	{						\
		return syscall(__NR_##sname, arg1);	\
	}

#define io_syscall2(type, fname, sname, type1, arg1, type2, arg2)	\
	type fname(type1 arg1, type2 arg2)				\
	{								\
		return syscall(__NR_##sname, arg1, arg2);		\
	}

#define io_syscall3(type, fname, sname, type1, arg1, type2, arg2, type3, arg3) \
	type fname(type1 arg1, type2 arg2, type3 arg3)			\
	{								\
		return syscall(__NR_##sname, arg1, arg2, arg3);		\
	}

#define io_syscall4(type, fname, sname, type1, arg1, type2, arg2, type3, arg3, type4, arg4) \
	type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4)	\
	{								\
		return syscall(__NR_##sname, arg1, arg2, arg3, arg4);	\
	}

#define io_syscall5(type, fname, sname, type1, arg1, type2, arg2, type3, arg3, type4, arg4, type5, arg5) \
	type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
	{								\
		return syscall(__NR_##sname, arg1, arg2, arg3, arg4, arg5); \
	}
