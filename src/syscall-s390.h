#define __NR_io_setup		243
#define __NR_io_destroy		244
#define __NR_io_getevents	245
#define __NR_io_submit		246
#define __NR_io_cancel		247

#define _svc_clobber "2", "cc", "memory"

#ifdef __s390x__
#define __LR "lgr " /* 64 bit load register */
#else
#define __LR "lr	" /* 32 bit load register */
#endif

#define io_syscall0(type,fname,sname)				\
type fname(void) {						\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname)				\
		: _svc_clobber );				\
	return (type) __res;					\
}

#define io_syscall1(type,fname,sname,type1,arg1)		\
type fname(type1 arg1) {					\
	register type1 __arg1 asm("2") = arg1;			\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname),				\
		  "d" (__arg1)					\
		: _svc_clobber );				\
	return (type) __res;					\
}

#define io_syscall2(type,fname,sname,type1,arg1,type2,arg2)	\
type fname(type1 arg1, type2 arg2) {				\
	register type1 __arg1 asm("2") = arg1;			\
	register type2 __arg2 asm("3") = arg2;			\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname),				\
		  "d" (__arg1),					\
		  "d" (__arg2)					\
		: _svc_clobber );				\
	return (type) __res;					\
}

#define io_syscall3(type,fname,sname,type1,arg1,type2,arg2,	\
		    type3,arg3)					\
type fname(type1 arg1, type2 arg2, type3 arg3) {			\
	register type1 __arg1 asm("2") = arg1;			\
	register type2 __arg2 asm("3") = arg2;			\
	register type3 __arg3 asm("4") = arg3;			\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname),				\
		  "d" (__arg1),					\
		  "d" (__arg2),					\
		  "d" (__arg3)					\
		: _svc_clobber );				\
	return (type) __res;					\
}

#define io_syscall4(type,fname,sname,type1,arg1,type2,arg2,	\
		    type3,arg3,type4,arg4)			\
type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4) {	\
	register type1 __arg1 asm("2") = arg1;			\
	register type2 __arg2 asm("3") = arg2;			\
	register type3 __arg3 asm("4") = arg3;			\
	register type4 __arg4 asm("5") = arg4;			\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname),				\
		  "d" (__arg1),					\
		  "d" (__arg2),					\
		  "d" (__arg3),					\
		  "d" (__arg4)					\
		: _svc_clobber );				\
	return (type) __res;					\
}

#define io_syscall5(type,fname,sname,type1,arg1,type2,arg2,	\
		    type3,arg3,type4,arg4,type5,arg5)		\
type fname(type1 arg1, type2 arg2, type3 arg3, type4 arg4,	\
	   type5 arg5) {						\
	register type1 __arg1 asm("2") = arg1;			\
	register type2 __arg2 asm("3") = arg2;			\
	register type3 __arg3 asm("4") = arg3;			\
	register type4 __arg4 asm("5") = arg4;			\
	register type5 __arg5 asm("6") = arg5;			\
	long __res;						\
	__asm__ __volatile__ (					\
		"    svc %b1\n"					\
		"    "__LR" %0,2"				\
		: "=d" (__res)					\
		: "i" (__NR_##sname),				\
		  "d" (__arg1),					\
		  "d" (__arg2),					\
		  "d" (__arg3),					\
		  "d" (__arg4),					\
		  "d" (__arg5)					\
		: _svc_clobber );				\
	return (type) __res;					\
}
