/* 4.t
- read of descriptor without read permission (4.t)
- write to descriptor without write permission (4.t)

*/
#include "aio_setup.h"

#define SIZE	512
#define READ	'r'
#define WRITE	'w'
int attempt(int fd, int rw, int expect)
{
	char buf[SIZE];
	struct iocb iocb;
	int res;

	memset(buf, 0, SIZE);

	switch(rw) {
	case READ:	io_prep_pread (&iocb, fd, buf, SIZE, 0); break;
	case WRITE:	io_prep_pwrite(&iocb, fd, buf, SIZE, 0); break;
	}

	printf("expect %3d: (%c), res = ", expect, rw);
	fflush(stdout);
	res = sync_submit(&iocb);
	printf("%3d [%s]\n", res, (res <= 0) ? strerror(-res) : "Success");
	if (res != expect)
		return 1;

	return 0;
}

int test_main(void)
{
	int rofd, wofd, rwfd;
	int	status = 0;

	rofd = open("rofile", O_RDONLY);	assert(rofd != -1);
	wofd = open("wofile", O_WRONLY);	assert(wofd != -1);
	rwfd = open("rwfile", O_RDWR);		assert(rwfd != -1);

	status |= attempt(rofd, WRITE, -EBADF);
	status |= attempt(wofd,  READ, -EBADF);
	status |= attempt(rwfd, WRITE, SIZE);
	status |= attempt(rwfd,  READ, SIZE);

	return status;
}

