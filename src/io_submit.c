/* io_submit
 */
#include <errno.h>
#include <libaio.h>
#include "vsys_def.h"

int io_submit(io_context_t ctx, int nr, struct iocb **iocbs)
{
	if (nr > 0)
		return vsys_io_submit(ctx, nr, iocbs);
	return -EINVAL;
}
