/* libaio Linux async I/O interface

   compat-0_1.c : compatibility symbols for libaio 0.1.x-0.3.x

   Copyright 2002 Red Hat, Inc.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */
#include <stdlib.h>
#include <asm/errno.h>

#include "libaio.h"
#include "vsys_def.h"

#include "syscall.h"


/*
 * Compatible interfaces that still need an entry point.
 */

SYMVER(compat0_1_io_queue_init, io_queue_init, 0.1);
int compat0_1_io_queue_init(int maxevents, io_context_t *ctxp)
{
	return io_queue_init(maxevents, ctxp);
}

SYMVER(compat0_1_io_queue_run, io_queue_run, 0.1);
int compat0_1_io_queue_run(io_context_t ctx)
{
	return io_queue_run(ctx);
}

SYMVER(compat0_1_io_submit, io_submit, 0.1);
int compat0_1_io_submit(io_context_t ctx, long nr, struct iocb **iocbs)
{
	return io_submit(ctx, nr, iocbs);
}

/* ABI change.  Provide partial compatibility on this one for now. */
SYMVER(compat0_1_io_cancel, io_cancel, 0.1);
int compat0_1_io_cancel(io_context_t ctx, struct iocb *iocb)
{
	struct io_event event;

	/* FIXME: the old ABI would return the event on the completion queue */
	return io_cancel(ctx, iocb, &event);
}

SYMVER(compat0_1_io_queue_wait, io_queue_wait, 0.1);
int compat0_1_io_queue_wait(io_context_t ctx, struct timespec *when)
{
	struct timespec timeout;
	if (when)
		timeout = *when;
	return io_getevents(ctx, 0, 0, NULL, when ? &timeout : NULL);
}

SYMVER(compat0_1_io_queue_release, io_queue_release, 0.1);
int compat0_1_io_queue_release(io_context_t ctx)
{
	return io_destroy(ctx);
}

/* ABI change.  Provide backwards compatibility for this one. */
SYMVER(compat0_1_io_getevents, io_getevents, 0.1);
int compat0_1_io_getevents(io_context_t ctx_id, long nr,
		       struct io_event *events,
		       const struct timespec *const_timeout)
{
	struct timespec timeout;
	if (const_timeout)
		timeout = *const_timeout;
	return io_getevents(ctx_id, 1, nr, events,
			const_timeout ? &timeout : NULL);
}

