/* 4.t
- read of descriptor without read permission (4.t)
- write to descriptor without write permission (4.t)
- check that O_APPEND writes actually append

*/
#include "aio_setup.h"

#define SIZE	512
#define READ	'r'
#define WRITE	'w'
int attempt(int fd, void *buf, int count, int rw, int expect)
{
	struct iocb iocb;
	int res;

	switch(rw) {
	case READ:	io_prep_pread (&iocb, fd, buf, count, 0); break;
	case WRITE:	io_prep_pwrite(&iocb, fd, buf, count, 0); break;
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
	char buf[SIZE];
	int rofd, wofd, rwfd;
	int	status = 0, res;

	memset(buf, 0, SIZE);

	rofd = open("rofile", O_RDONLY);	assert(rofd != -1);
	wofd = open("wofile", O_WRONLY);	assert(wofd != -1);
	rwfd = open("rwfile", O_RDWR);		assert(rwfd != -1);

	status |= attempt(rofd, buf, SIZE, WRITE, -EBADF);
	status |= attempt(wofd, buf, SIZE,  READ, -EBADF);
	status |= attempt(rwfd, buf, SIZE, WRITE, SIZE);
	status |= attempt(rwfd, buf, SIZE,  READ, SIZE);

	rwfd = open("rwfile", O_RDWR | O_APPEND);	assert(rwfd != -1);
	res = ftruncate(rwfd, 0);			assert(res == 0);
	status |= attempt(rwfd, buf,    SIZE,   READ, 0);
	status |= attempt(rwfd, "1234",    4,  WRITE, 4);
	status |= attempt(rwfd, "5678",    4,  WRITE, 4);
	memset(buf, 0, SIZE);
	status |= attempt(rwfd,    buf, SIZE,   READ, 8);
	printf("read after append: [%s]\n", buf);
	assert(memcmp(buf, "12345678", 8) == 0);

	return status;
}

