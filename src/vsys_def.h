extern int vsys_io_setup(unsigned nr_reqs, io_context_t *ctxp);
extern int vsys_io_destroy(io_context_t ctx);
extern int vsys_io_submit(io_context_t ctx, long nr, struct iocb *iocbs[]);
extern int vsys_io_cancel(io_context_t ctx, struct iocb *iocb);
extern int vsys_io_wait(io_context_t ctx, struct iocb *iocb, struct timespec *when);
extern int vsys_io_getevents(io_context_t ctx_id, long nr, struct io_event *events, struct timespec *timeout);

