/* 3.t
- io_submit/io_getevents with invalid addresses (3.t)

*/
#include "aio_setup.h"

int attempt(io_context_t ctx, long nr, struct iocb *ios[], int expect)
{
	int res;

	printf("expect %3d: io_submit(%10p, %3ld, %10p) = ", expect, ctx, nr, ios);
	fflush(stdout);
	res = io_submit(ctx, nr, ios);
	printf("%3d [%s]%s\n", res, (res <= 0) ? strerror(-res) : "",
		(res != expect) ? " -- FAILED" : "");
	if (res != expect)
		return 1;

	return 0;
}

int test_main(void)
{
	struct iocb a, b;
	struct iocb *good_ios[] = { &a, &b };
	struct iocb *bad1_ios[] = { NULL, &b };
	struct iocb *bad2_ios[] = { KERNEL_RW_POINTER, &a };
	int	status = 0;

	status |= attempt(BAD_CTX, 1,   good_ios, -EINVAL);
	status |= attempt( io_ctx, 0,   good_ios,       0);
	status |= attempt( io_ctx, 1,       NULL, -EFAULT);
	status |= attempt( io_ctx, 1, (void *)-1, -EFAULT);
	status |= attempt( io_ctx, 2,   bad1_ios, -EFAULT);
	status |= attempt( io_ctx, 2,   bad2_ios, -EFAULT);
	status |= attempt( io_ctx, -1,  good_ios, -EINVAL);

	return status;
}

