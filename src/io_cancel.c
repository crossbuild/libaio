/* io_cancel.c
 */
#include <libaio.h>
#include "vsys_def.h"

int io_cancel(io_context_t ctx, struct iocb *iocb)
{
	return vsys_io_cancel(ctx, iocb);
}
