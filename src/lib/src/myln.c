#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main ()
{
	long ctx = 0;
	extern long vsys_io_setup(long, long *);
	unsigned char *bob = (void*)&vsys_io_setup;
	long ret;
	int i;
	printf("%p\n", bob);
	//printf("%p\n", mmap(0, 65536, PROT_READ | PROT_EXEC, MAP_SHARED,
	//	open("/dev/vsys", O_RDONLY), 0));
	//for (i=0; i<16; i++)
	//	printf(" %02x\n", bob[i]);
	//printf("\n");

	ret = vsys_io_setup(100, &ctx);

	printf("ret=%ld, ctx=0x%lx\n", ret, ctx);
	return 0;
}
