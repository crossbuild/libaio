#include <linux/compile.h>
#include <linux/types.h>
#include <asm/unistd.h>
#include <asm/fcntl.h>
#include <asm/mman.h>
#include <asm/a.out.h>

char libredhat_kernel_enosys = 1;	/* the asm in stub.S depends on this */

long _init(void)
{
	static char unique[] = { LINUX_UNIQUE_BYTES };
	int errno;
	long addr;
	int fd;
	int i;

	_syscall6(int, mmap2, unsigned long, addr, unsigned long, len,
        	  unsigned long, prot, unsigned long, flags,
        	  unsigned long, fd, unsigned long, pgoff)
	_syscall2(long, munmap, unsigned long, addr, size_t, len)
	_syscall2(int, open, const char *, name, int, flags)
	_syscall1(int, close, int, fd)

	if (sizeof(unique) != 16)
		return -1;

	fd = open("/dev/vsys", O_RDONLY);
	if (-1 == fd)
		return -1;

	addr = mmap2(0, VSYSCALL_SIZE, PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0);
	if (-1 == addr)
		return -1;

	close(fd);

	for (i=0; i<sizeof(unique); i++)
		if (unique[i] != ((char *)addr)[i]) {
			munmap(addr, VSYSCALL_SIZE);
			return -1;
		}

	/* okay, all the syscalls we provide are now good */
	libredhat_kernel_enosys = 0;
	return 0;
}

