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
