#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TMAX 11
#define FILENAME "tmp1"
static int temp;
static pthread_t plist[TMAX];
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static void *func1(void *p)
{

    pthread_mutex_lock(&mut);
    int c = 'a' + (int)p;
    while (1)
    {
        fprintf(stdout, "%c", c);
        fflush(stdout);
    }
    pthread_mutex_unlock(&mut);
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

    exit(0);
}
