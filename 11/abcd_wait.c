#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TMAX 50
#define FILENAME "tmp1"
static int num=0;
static int temp;
static pthread_t plist[TMAX];
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
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
        pthread_mutex_lock(&mut);
        while(num!=n){
            pthread_cond_wait(&cond,&mut);
        }
        fprintf(stdout, "%c", c);
        fflush(stdout);
        num = next(num);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mut);
    }

    pthread_exit(NULL);
}
int main()
{
    alarm(5);
    pthread_t tid;
    for (int i = 0; i < TMAX; i++)
    {

        int err = pthread_create(&tid, NULL, func1, (void *)i);
        if (err)
        {
            exit(1);
        }
        plist[i] = tid;
    }
    for (int i = 0; i < TMAX; i++)
    {
        pthread_join(plist[i], NULL);
    }
    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&cond);

    exit(0);
}
