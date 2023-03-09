#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#include <errno.h>
#define BUFSIZE 1024
#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
enum
{
    STATE_R = 1,
    STATE_W,
    STATE_AUTO,
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
        printf("%s\n", fsm->err);
        fsm->state = STATE_T;
    case STATE_T:
        break;
    default:
        abort();
        break;
    }
}
static int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
static void relay(int fd1, int fd2)
{
    int fd1_save, fd2_save;
    fd_set rset, wset;
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
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if (fsm12.state == STATE_R)
        {
            FD_SET(fsm12.sfd, &rset);
        }
        if (fsm12.state == STATE_W)
        {
            FD_SET(fsm12.dfd, &wset);
        }
        if (fsm21.state == STATE_R)
        {
            FD_SET(fsm21.sfd, &rset);
        }
        if (fsm21.state == STATE_W)
        {
            FD_SET(fsm21.dfd, &wset);
        }
        if (fsm12.state < STATE_AUTO || fsm21.state < STATE_AUTO)
        {
        select_v1:
            int s_stat = select(max(fd1, fd2), &rset, &wset, NULL, NULL);
            if (s_stat < 0)
            {
                if (errno == EINTR)
                {
                    goto select_v1;
                } 
                perror("select()");
                exit(1);
            }
        }
        if (FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset) || fsm12.state > STATE_AUTO)
        {
            fsm_driver(&fsm12);
        }
        if (FD_ISSET(fd2, &rset) || FD_ISSET(fd1, &wset) || fsm21.state > STATE_AUTO)
        {
            fsm_driver(&fsm21);
        }
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
    write(fd1, "tty11", 6);

    fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
    if (fd2 < 0)
    {
        printf("nofd2\n");
        exit(1);
    }
    write(fd2, "tty12", 6);
    relay(fd1, fd2);

    close(fd1);
    close(fd2);
    exit(0);
}
