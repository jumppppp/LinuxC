#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mysem.h"
struct mysem_st
{
    int val;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};
mysem_t *mysem_init(int initval)
{
    struct mysem_st *me;
    me = malloc(sizeof(*me));
    if (me == NULL)
    {
        return NULL;
        exit(1);
    }
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);
    me->val = initval;
    return me;
}

int mysem_add(mysem_t *ptr, int val)
{
    struct mysem_st *me = ptr;
    pthread_mutex_lock(&me->mut);

    me->val += val;
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return val;
}

int mysem_sub(mysem_t *ptr, int val)
{
    struct mysem_st *me = ptr;
    pthread_mutex_lock(&me->mut);
    while (me->val < val)
    {
        pthread_cond_wait(&me->cond, &me->mut);
    }
    me->val -= val;

    pthread_mutex_unlock(&me->mut);
    return val;
}

int mysem_destory(mysem_t *ptr)
{
    struct mysem_st *me = ptr;
    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);
    free(me);
    return 0;
}