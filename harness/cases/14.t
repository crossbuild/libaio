#include "aio_setup.h"
#include <sys/mman.h>

#define SIZE 768*1024*1024

//just submit an I/O

int test_main(void)
{
        char *buf;
        int rwfd;
        int res;
        long size;
        struct iocb iocb;
        struct iocb *iocbs[] = { &iocb };
        int loop = 10;
        int i;

        size = SIZE;

        printf("size = %ld\n", size);

        rwfd = open("testdir/rwfile", O_RDWR);          assert(rwfd != 
-1);
        res = ftruncate(rwfd, 0);                       assert(res == 0);
        buf = malloc(size);                             assert(buf != 
NULL);

        for(i=0;i<loop;i++) {

                switch(i%2) {
                case 0:
                        io_prep_pwrite(&iocb, rwfd, buf, size, 0);
                        break;
                case 1:
                        io_prep_pread(&iocb, rwfd, buf, size, 0);
                }

                res = io_submit(io_ctx, 1, iocbs);
                if (res != 1) {
                        printf("submit: io_submit res=%d [%s]\n", res, 
strerror(-res));
                        return res;
                }
        }

        res = ftruncate(rwfd, 0);                       assert(res == 0);

        exit(0);

}


