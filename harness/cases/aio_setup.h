io_context_t	io_ctx;
#define BAD_CTX	((io_context_t)-1)

void aio_setup(int n)
{
	int res = io_queue_init(n, &io_ctx);
	if (res != 0) {
		printf("io_queue_setup(%d) returned %d (%s)\n",
			n, res, strerror(-res));
		exit(3);
	}
}

int sync_submit(struct iocb *iocb)
{
	struct io_event event;
	struct iocb *iocbs[] = { iocb };
	int res;

	/* 30 second timeout should be enough */
	struct timespec	ts;
	ts.tv_sec = 30;
	ts.tv_nsec = 0;

	res = io_submit(io_ctx, 1, iocbs);
	if (res != 1) {
		printf("sync_submit: io_submit res=%d [%s]\n", res, strerror(-res));
		return res;
	}

	res = io_getevents(io_ctx, 1, &event, &ts);
	if (res != 1) {
		printf("sync_submit: io_getevents res=%d [%s]\n", res, strerror(-res));
		return res;
	}
	return event.res;
}

#define SETUP	aio_setup(1024)


#define READ	'r'
#define WRITE	'w'
int attempt_rw(int fd, void *buf, int count, long long pos, int rw, int expect)
{
	struct iocb iocb;
	int res;

	switch(rw) {
	case READ:	io_prep_pread (&iocb, fd, buf, count, pos); break;
	case WRITE:	io_prep_pwrite(&iocb, fd, buf, count, pos); break;
	}

	printf("expect %3d: (%c), res = ", expect, rw);
	fflush(stdout);
	res = sync_submit(&iocb);
	printf("%3d [%s]%s\n", res, (res <= 0) ? strerror(-res) : "Success",
		(res != expect) ? " -- FAILED" : "");
	if (res != expect)
		return 1;

	return 0;
}

