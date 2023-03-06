#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "mysem.h"
#define LEFT 30000000
#define RIGHT 30000050
#define MAX_P 512
#define sem_max 10
static mysem_t *sem;
static pthread_t plist[MAX_P];
static pthread_mutex_t mut_pos = PTHREAD_MUTEX_INITIALIZER;
static void *thr_prime(void *p)
{
    pthread_mutex_lock(&mut_pos);
    int mark = 1;
    int i = *(int *)p;
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
        printf("%d\n", i);
    }
    int val = mysem_add(sem, 1);
    printf("val=<%d>\n", val);
    pthread_mutex_unlock(&mut_pos);
    pthread_exit(p);
}
static int find_pos(void)
{
    for (int i = 0; i < MAX_P; i++)
    {

        // printf("<%d>",plist[i]);
        if (plist[i] == 0)
        {
            return i;
        }
    }
    return -1;
}
int main()
{

    sem = mysem_init(sem_max);
    int err;
    int pos;
    for (int i = LEFT; i <= RIGHT; i++)
    {
        int val = mysem_sub(sem, 1);
        printf("val=[%d]\n", val);
        pthread_t tid;
        err = pthread_create(&tid, NULL, thr_prime, (void *)&i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            printf("count={{%d}}\n", i);
            exit(1);
        }
        pthread_mutex_lock(&mut_pos);
        pos = find_pos();
        printf("pos=<<<<<<<<<<%d\n", pos);
        if (pos == -1)
        {
            printf("find_pos_no!");
            exit(1);
        }
        plist[pos] = tid;
        pthread_mutex_unlock(&mut_pos);
        // printf("[%d]",plist[pos]);
    }
    for (int i = 0; plist[i] == 0; i++)
    {
        pthread_join(plist[i], NULL);
    }
    mysem_destory(sem);
    exit(0);
}
