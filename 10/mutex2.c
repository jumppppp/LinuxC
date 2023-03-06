#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TMAX 50
#define FILENAME "tmp1"
static int temp;
static pthread_t plist[TMAX];
static pthread_mutex_t mut[TMAX];
static int next(int n){
    if(n+1==TMAX)
        return 0;
    return n+1;
}

static void *func1(void *p)
{
    int n = (int)p;
    int c = 'a' + (int)n;

    while (1)
    {
        pthread_mutex_lock(mut+n);
        fprintf(stdout, "%c", c);
        fflush(stdout);
        pthread_mutex_unlock(mut+next(n));
    }

    pthread_exit(NULL);
}
int main()
{
    alarm(5);
    pthread_t tid;
    for (int i = 0; i < TMAX; i++)
    {
        pthread_mutex_init(mut+i,NULL);
        pthread_mutex_lock(mut+i);
        int err = pthread_create(&tid, NULL, func1, (void *)i);
        if (err)
        {
            exit(1);
        }
        plist[i] = tid;
        pthread_mutex_unlock(mut+i);
    }
    for (int i = 0; i < TMAX; i++)
    {
        pthread_join(plist[i], NULL);
    }
    pthread_mutex_destroy(mut);

    exit(0);
}
