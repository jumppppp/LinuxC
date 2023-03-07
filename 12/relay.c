#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFSIZE 1024
#define TTY1 "./tty1"
#define TTY2 "./tty2"
enum
{
    STATE_R = 1,
    STATE_W,
    STATE_Ex,
    STATE_T
};
struct fsm_st
{
    int state;
    int sfd;
    int dfd;
    char buf[BUFSIZE];
};
static int relay(int fd1, int fd2)
{
    int df1_save, fd2_save;
    struct fsm_st fsm12, fsm21;
    fd1_save = fcntl(fd1, F_GETFL);
    fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);
    fd2_save = fcntl(fd2, F_SETFL);
    fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);
    fsm12.state = STATE_R;
    fsm12.sfd = fd1;
    fsm12.dfd = fd2;
    fsm21.state = STATE_R;
    fsm21.sfd = fd2;
    fsm21.dfd = fd1;
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

    relay(fd1, fd2);

    close(fd1);
    close(fd2);
    exit(0);
}
