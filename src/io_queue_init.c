/* io_queue_init.c
 */
#include <libaio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "vsys_def.h"

int io_queue_init(int maxevents, io_context_t *ctxp)
{
	if (maxevents > 0) {
		*ctxp = NULL;
		return vsys_io_setup(maxevents, ctxp);
	}
	return -EINVAL;
}
