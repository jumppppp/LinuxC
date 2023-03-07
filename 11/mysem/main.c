#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "mysem.h"
#define LEFT 30000000
#define RIGHT 30005000
#define sem_max 10
#define maxn (RIGHT-LEFT+1)
static mysem_t *sem;
static pthread_t plist[maxn];
static pthread_mutex_t mut_pos = PTHREAD_MUTEX_INITIALIZER;
static void *thr_prime(void *p)
{

    int i = (int)p;
    pthread_mutex_lock(&mut_pos);
    int mark = 1;
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
        sleep(5);   //the test
    int val = mysem_add(sem, 1);
    pthread_mutex_unlock(&mut_pos);

    pthread_exit(p);
}
int main()
{
    sem = mysem_init(sem_max);
    int err;
    int pos;

    for (int i = LEFT; i <= RIGHT; i++)
    {
        int val = mysem_sub(sem, 1);
        err = pthread_create(plist+(i-LEFT), NULL, thr_prime, (void *)i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            printf("count={{%d}}\n", i);
            exit(1);
        }
    }
    for (int i = LEFT; i<=RIGHT; i++)
    {
        pthread_join(plist[i-LEFT],NULL);
    }
    mysem_destory(sem);
    exit(0);
}
