/* io_submit
 */
#define NO_SYSCALL_ERRNO
#include <linux/types.h>
#include <libaio.h>
#include <errno.h>

#include "vsys_def.h"

struct timespec;

int io_queue_wait(io_context_t ctx, struct timespec *timeout)
{
	return vsys_io_getevents(ctx, 0, NULL, timeout);
}
