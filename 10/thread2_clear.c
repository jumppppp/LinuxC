#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
// posix mod
static void cle_f(void *p)
{
    puts(p);
}
static void *func(void *)
{
    puts("gogogo");
    pthread_cleanup_push(cle_f, "clear1");
    pthread_cleanup_push(cle_f, "clear2");
    pthread_cleanup_push(cle_f, "clear3");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}
int main()
{
    puts("start!");
    pthread_t *tid;
    int i = pthread_create(tid, NULL, func, NULL);
    if (i)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(i));
    }

    pthread_join(*tid, NULL);
    puts("end!");
    exit(0);
}
