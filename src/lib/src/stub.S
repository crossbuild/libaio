/* stub.S */
#include <asm/segment.h>
#include <asm/errno.h>

	.text

#define dynamic_syscall(x,a) \
	.globl	x				;\
	.align 16				;\
	x:					;\
		cmpb $0,libredhat_kernel_enosys	;\
		jne 1f				;\
		ljmp $__USER_CS, $a		;\
	1:					;\
		movl	$-ENOSYS,%eax		;\
		ret				;\
	.size	 x,.-x

