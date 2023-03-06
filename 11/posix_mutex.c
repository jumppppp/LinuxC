#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define LEFT 30000000
#define RIGHT 30005000
#define MAX_P 100
#define MAX_L 51200
static int num = 0;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_t plist[MAX_L];
static void *thr_prime(void *p)
{
    while (1)
    {
        int mark = 1;
        pthread_mutex_lock(&mut);
        while (num == 0)
        {
            pthread_mutex_unlock(&mut);
            sched_yield();
            pthread_mutex_lock(&mut);
        }
        if (num == -1)
        {
            pthread_mutex_unlock(&mut);
            break;
        }
        int i = num;
        num = 0;
        pthread_mutex_unlock(&mut);
        for (int j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark)
        {
            printf("[%d]%d\n", (int)p,i);
        }
    }
    pthread_exit(p);
}
static int find_pos(void)
{
    for (int i = 0; i < MAX_L; i++)
    {

        //printf("<%d>",plist[i]);
        if (plist[i] == 0)
        {
            return i;
        }
    }
    return -1;
}
int main()
{

    int err;
    int pos;
    for (int i = 0; i <= MAX_P; i++)
    {
        pthread_t tid;
        err = pthread_create(&tid, NULL, thr_prime, (void*)i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            printf("count={{%d}}\n", i);
            exit(1);
        }
        pthread_mutex_lock(&mut);
        pos = find_pos();
        
        // printf("<%d>", pos);
        if (pos == -1)
        {
            printf("find_pos_no!");
            exit(1);
        }
        plist[pos] = tid;
        pthread_mutex_unlock(&mut);
        // printf("[%d]",plist[pos]);
    }
    for (int i = LEFT; i < RIGHT; i++)
    {
        pthread_mutex_lock(&mut);
        while (num != 0)
        {
            pthread_mutex_unlock(&mut);
            sched_yield();
            pthread_mutex_lock(&mut);
        }
        num = i;
        pthread_mutex_unlock(&mut);
    }
    pthread_mutex_lock(&mut);
    while (num != 0)
    {
        pthread_mutex_unlock(&mut);
        sched_yield();
        pthread_mutex_lock(&mut);
    }
    num = -1;
    pthread_mutex_unlock(&mut);
    for (int i = 0; plist[i] == 0; i++)
    {
        pthread_join(plist[i], NULL);
    }
    pthread_mutex_destroy(&mut);
    exit(0);
}
