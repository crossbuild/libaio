#define _SYMSTR(str)	#str
#define SYMSTR(str)	_SYMSTR(str)

#define SYMVER(compat_sym, orig_sym, ver_sym)	\
	__asm__(".symver " SYMSTR(compat_sym) "," SYMSTR(orig_sym) "@LIBAIO_" SYMSTR(ver_sym));

#if defined(__i386__)
#include "syscall-i386.h"
#elif defined(__ia64__)
#include "syscall-ia64.h"
#else
#error "add syscall-arch.h"
#endif

