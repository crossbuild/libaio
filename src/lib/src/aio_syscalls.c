/* libaio Linux async I/O interface
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

#include "../../libaio.h"
#include "../../vsys_def.h"

#include "syscall-i386.h"

#include <asm/errno.h>


int vsys_io_setup(unsigned nr_reqs, io_context_t *ctxp)
{
	return syscall2(__NR_io_setup, nr_reqs, ctxp);
}

int vsys_io_destroy(io_context_t ctx)
{
	return syscall1(__NR_io_destroy, ctx);
}

int vsys_io_submit(io_context_t ctx, long nr, struct iocb *iocbs[])
{
	return syscall3(__NR_io_submit, ctx, nr, iocbs);
}

static inline int real_sys_io_cancel(io_context_t ctx, struct iocb *iocb, struct io_event *event)
{
	return syscall3(__NR_io_cancel, ctx, iocb, event);
}

/* ABI change.  Provide partial compatibility on this one for now. */
int vsys_io_cancel(io_context_t ctx, struct iocb *iocb)
{
	struct io_event event;

	/* FIXME: the old ABI would return the event on the completion queue */
	return real_sys_io_cancel(ctx, iocb, &event);
}

int vsys_io_wait(io_context_t ctx, struct iocb *iocb, const struct timespec *when)
{
	return -ENOSYS;
}


/* ABI change.  Provide backwards compatibility for this one. */
static inline long real_sys_io_getevents(io_context_t ctx_id, long min_nr,
		long nr, struct io_event *events, struct timespec *timeout)
{
	return syscall5(__NR_io_getevents, ctx_id, min_nr, nr, events, timeout);
}

int vsys_io_getevents(io_context_t ctx_id, long nr, struct io_event *events,
		       const struct timespec *const_timeout)
{
	struct timespec timeout;
	if (const_timeout)
		timeout = *const_timeout;
	return real_sys_io_getevents(ctx_id, 1, nr, events,
			const_timeout ? &timeout : NULL);
}

