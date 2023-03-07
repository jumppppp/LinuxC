#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
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
    int len;
    int pos;
    char buf[BUFSIZE];
    char *err;
};
static void fsm_driver(struct fsm_st *fsm)
{
    switch (fsm->state)
    {
    case STATE_R:
        fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
        if (fsm->len == 0)
            fsm->state = STATE_T;
        else if (fsm->len < 0)
        {
            if (errno == EAGAIN)
                fsm->state = STATE_R;
            else
            {
                fsm->err = "read()";
                fsm->state = STATE_Ex;
            }
        }
        else
        {
            fsm->pos = 0;
            fsm->state = STATE_W;
        }
        break;
    case STATE_W:
        int ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
        if (ret < 0)
        {
            if (errno == EAGAIN)
            {
                fsm->state = STATE_W;
            }
            else
            {
                fsm->state = STATE_Ex;
                fsm->err = "write()";
            }
        }
        else
        {
            fsm->pos += ret;
            fsm->len -= ret;
            if (fsm->len == 0)
            {
                fsm->state = STATE_R;
            }
            else
            {
                fsm->state = STATE_W;
            }
        }
        break;
    case STATE_Ex:
    printf("%s\n",fsm->err);
        fsm->state = STATE_T;
    case STATE_T:
        break;
    default:
        abort();
        break;
    }
}
static void relay(int fd1, int fd2)
{
    int fd1_save, fd2_save;
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
    while (fsm12.state != STATE_T || fsm21.state != STATE_T)
    {
        fsm_driver(&fsm12);
        fsm_driver(&fsm21);
    }
    fcntl(fd1, F_SETFL, fd1_save);
    fcntl(fd2, F_SETFL, fd2_save);
}
int main()
{
    int fd1, fd2;
    fd1 = open(TTY1, O_RDWR);
    if (fd1 < 0)
    {
        printf("nofd1\n");
        exit(1);
    }

    fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
    if (fd2 < 0)
    {
        printf("nofd2\n");
        exit(1);
    }

    relay(fd1, fd2);

    close(fd1);
    close(fd2);
    exit(0);
}
