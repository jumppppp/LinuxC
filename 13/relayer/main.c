#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "relayer.h"
#define TTY1 "./tty1"
#define TTY2 "./tty2"
#define TTY3 "./tty3"
#define TTY4 "./tty4"
int main()
{
    int fd1, fd2, fd3, fd4;
    fd1 = open(TTY1, O_RDWR);
    if (fd1 < 0)
    {
        printf("nofd1\n");
        exit(1);
    }

    fd2 = open(TTY2, O_RDWR );
    if (fd2 < 0)
    {
        printf("nofd2\n");
        exit(1);
    }
    fd3 = open(TTY3, O_RDWR);
    if (fd3 < 0)
    {
        printf("nofd3\n");
        exit(1);
    }

    fd4 = open(TTY4, O_RDWR );
    if (fd4 < 0)
    {
        printf("nofd4\n");
        exit(1);
    }

    int job1 = rel_addjob(fd1, fd2);
    if (job1 < 0)
    {
        printf("nojob1\n");
        exit(1);
    }
    int job2 = rel_addjob(fd3, fd4);
    if (job2 < 0)
    {
        printf("nojob2\n");
        exit(1);
    }

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    exit(0);
}
