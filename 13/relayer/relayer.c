#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include "relayer.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 1024
static pthread_mutex_t mut_rj = PTHREAD_MUTEX_INITIALIZER;
struct rel_job_st *rel_job[REL_JOBMAX];
static pthread_once_t one_load = PTHREAD_ONCE_INIT;
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
    int64_t count;
};
struct rel_job_st
{
    int fd1;
    int fd2;
    int job_state;
    struct fsm_st fsm12, fsm21;
    int fd1_save, fd2_save;
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
void *thr_relayer(void *p)
{
    while (1)
    {

        pthread_mutex_lock(&mut_rj);
        for (int i = 0; i < REL_JOBMAX; i++)
        {
            if (rel_job[i] != NULL)
            {
                if (rel_job[i]->job_state == STATE_RUN)
                {
                    fsm_driver(&rel_job[i]->fsm12);
                    fsm_driver(&rel_job[i]->fsm21);
                    if (rel_job[i]->fsm12.state == STATE_T && rel_job[i]->fsm21.state == STATE_T)
                    {
                        rel_job[i]->job_state=STATE_OVER;
                    }
                }
            }
        }
        pthread_mutex_unlock(&mut_rj);
    }
}
static int get_free_pos_unlocked(void)
{
    for (int i = 0; i < REL_JOBMAX; i++)
    {
        if (rel_job[i] != NULL)
        {
            return i;
        }
    }
    return -1;
}
static void module_load(void)
{
    pthread_t tid_relayer;
    int err = pthread_create(&tid_relayer, NULL, thr_relayer, NULL);
    if (err)
    {
        exit(1);
    }
}

int rel_addjob(int fd1, int fd2)
{

    pthread_once(&one_load, module_load);
    struct rel_job_st *me;
    me = malloc(sizeof(*me));
    me->fd1 = fd1;
    me->fd2 = fd2;
    me->job_state = STATE_RUN;
    me->fd1_save = fcntl(me->fd1, F_GETFL);
    fcntl(me->fd1, F_SETFL, me->fd1_save | O_NONBLOCK);
    me->fd2_save = fcntl(me->fd2, F_GETFL);
    fcntl(me->fd2, F_SETFL, me->fd2_save | O_NONBLOCK);
    me->fsm12.sfd = me->fd1;
    me->fsm12.dfd = me->fd2;
    me->fsm12.state = STATE_R;
    me->fsm21.sfd = me->fd2;
    me->fsm21.dfd = me->fd1;
    me->fsm21.state = STATE_R;
    pthread_mutex_lock(&mut_rj);
    int pos = get_free_pos_unlocked();
    if (pos < 0)
    {
        pthread_mutex_unlock(&mut_rj);
        fcntl(me->fd1, F_SETFL,me->fd1_save );
        fcntl(me->fd2, F_SETFL,me->fd2_save );
        free(me);
    }
    rel_job[pos]=me;
    pthread_mutex_unlock(&mut_rj);
}

int rel_celjob(int fd1, int fd2)
{
}

int rel_waitjob(int id, struct rel_stat_st *rs)
{
}

int rel_statjob(int id, struct rel_stat_st *rs)
{
}