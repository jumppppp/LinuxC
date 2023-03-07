#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define TTY1 "./tty1"
#define TTY2 "./tty2"

static int relay(int fd1,int fd2){

}
int main()
{
    int fd1, fd2;
    fd1 = open(TTY1, O_RDWR);
    if (fd1 < 0)
        exit(1);
    fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
    if (fd2 < 0)
        exit(1);
    
    relay(fd1,fd2);
close(fd1);
close(fd2);
    exit(0);
}
