/* io_submit
 */
#include <libaio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "vsys_def.h"

int io_queue_run(io_context_t ctx)
{
	static struct timespec timeout = { 0, 0 };
	struct io_event event;
	int ret;

	/* FIXME: batch requests */
	while (1 == (ret = vsys_io_getevents(ctx, 1, &event, &timeout))) {
		io_callback_t cb = (io_callback_t)event.data;
		struct iocb *iocb = (struct iocb *)event.obj;

		cb(ctx, iocb, event.res, event.res2);
	}

	return ret;
}
