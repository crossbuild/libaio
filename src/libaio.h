/* /usr/include/libaio.h
 *
 * Copyright 2000,2001,2002 Red Hat.
 *
 * Written by Benjamin LaHaise <bcrl@redhat.com>
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, provided that the above copyright
 * notice appears in all copies.  This software is provided without any
 * warranty, express or implied.  Red Hat makes no representations about
 * the suitability of this software for any purpose.
 *
 * IN NO EVENT SHALL RED HAT BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF
 * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF RED HAT HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * RED HAT DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND
 * RED HAT HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 */
#ifndef __LIBAIO_H
#define __LIBAIO_H
#include <asm/types.h>
#include <string.h>

struct timespec;
struct sockaddr;
struct iovec;
struct iocb;

typedef struct io_context *io_context_t;

typedef enum io_iocb_cmd {
	IO_CMD_PREAD = 0,
	IO_CMD_PWRITE = 1,

	IO_CMD_FSYNC = 2,
	IO_CMD_FDSYNC = 3,

	IO_CMD_POLL = 5,
} io_iocb_cmd_t;

#if defined(__i386__) /* little endian, 32 bits */
#define PADDED(x, y)	x, y
#define PADDEDptr(x, y)	x; unsigned y
#else
#error	endian?
#endif

struct io_iocb_poll {
	int	PADDED(events, __pad1);
};	/* result code is the set of result flags or -'ve errno */

struct io_iocb_sockaddr {
	struct sockaddr *addr;
	int		len;
};	/* result code is the length of the sockaddr, or -'ve errno */

struct io_iocb_common {
	void		*buf;
	unsigned	__pad1;
	long		nbytes;
	unsigned	__pad2;
	long long	offset;
	long long	__pad3, __pad4;
};	/* result code is the amount read or -'ve errno */

struct io_iocb_vector {
	const struct iovec	*vec;
	int			nr;
	long long		offset;
};	/* result code is the amount read or -'ve errno */

struct iocb {
	void		PADDEDptr(*data, __pad1);	/* Return in the io completion event */
	unsigned	PADDED(key, __pad2);	/* For use in identifying io requests */

	short		aio_lio_opcode;	
	short		aio_reqprio;
	int		aio_fildes;

	union {
		struct io_iocb_common		c;
		struct io_iocb_vector		v;
		struct io_iocb_poll		poll;
		struct io_iocb_sockaddr	saddr;
	} u;
};

struct io_event {
	unsigned	PADDED(data, __pad1);
	unsigned	PADDED(obj,  __pad2);
	unsigned	PADDED(res,  __pad3);
	unsigned	PADDED(res2, __pad4);
};

#undef PADDED
#undef PADDEDptr

typedef void (*io_callback_t)(io_context_t ctx, struct iocb *iocb, long res, long res2);

extern int io_queue_init(int maxevents, io_context_t *ctxp);
extern int io_queue_grow(io_context_t ctx, int new_maxevents);
extern int io_queue_release(io_context_t ctx);
extern int io_queue_wait(io_context_t ctx, struct timespec *timeout);
extern int io_queue_run(io_context_t ctx);
extern int io_submit(io_context_t ctx, int nr, struct iocb *ios[]);
extern int io_cancel(io_context_t ctx, struct iocb *iocb);

static inline void io_set_callback(struct iocb *iocb, io_callback_t cb)
{
	iocb->data = cb;
}

static inline void io_prep_pread(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
{
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_PREAD;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = buf;
	iocb->u.c.nbytes = count;
	iocb->u.c.offset = offset;
}

static inline void io_prep_pwrite(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
{
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_PWRITE;
	iocb->aio_reqprio = 0;
	iocb->u.c.buf = buf;
	iocb->u.c.nbytes = count;
	iocb->u.c.offset = offset;
}

static inline void io_prep_poll(struct iocb *iocb, int fd, int events)
{
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_POLL;
	iocb->aio_reqprio = 0;
	memset(&iocb->u, 0, sizeof(iocb->u));
	iocb->u.poll.events = events;
}

static inline int io_poll(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd, int events)
{
	io_set_callback(iocb, cb);
	io_prep_poll(iocb, fd, events);
	return io_submit(ctx, 1, &iocb);
}

static inline void io_prep_fsync(struct iocb *iocb, int fd)
{
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_FSYNC;
	iocb->aio_reqprio = 0;
	memset(&iocb->u, 0, sizeof(iocb->u));
}

static inline int io_fsync(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd)
{
	io_set_callback(iocb, cb);
	io_prep_fsync(iocb, fd);
	return io_submit(ctx, 1, &iocb);
}

static inline void io_prep_fdsync(struct iocb *iocb, int fd)
{
	iocb->aio_fildes = fd;
	iocb->aio_lio_opcode = IO_CMD_FDSYNC;
	iocb->aio_reqprio = 0;
	memset(&iocb->u, 0, sizeof(iocb->u));
}

static inline int io_fdsync(io_context_t ctx, struct iocb *iocb, io_callback_t cb, int fd)
{
	io_set_callback(iocb, cb);
	io_prep_fdsync(iocb, fd);
	return io_submit(ctx, 1, &iocb);
}

#endif
