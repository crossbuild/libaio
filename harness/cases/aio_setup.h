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

void sync_submit(struct iocb *iocb, struct io_event *event)
{
	struct iocb *iocbs[] = { iocb };
	int res;

	/* 30 second timeout should be enough */
	struct timespec	ts;
	ts.tv_sec = 30;
	ts.tv_nsec = 0;

	res = io_submit(io_ctx, 1, iocbs);
	if (res != 1) {
		printf("sync_submit: io_submit res=%d [%s]\n", res, strerror(-res));
		exit(3);
	}

	res = io_getevents(io_ctx, 1, event, &ts);
	if (res != 1) {
		printf("sync_submit: io_getevents res=%d [%s]\n", res, strerror(-res));
		exit(3);
	}
}

#define SETUP	aio_setup(1024)
