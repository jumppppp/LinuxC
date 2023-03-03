#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include<string.h>
// posix mod
static void *func(void *)
{
    puts("gogogo");
    pthread_exit(NULL);
}
int main()
{
    puts("start!");
    pthread_t *tid;
    int i = pthread_create(tid, NULL, func, NULL);
    if(i){
        fprintf(stderr,"pthread_create():%s\n",strerror(i));
    }

    pthread_join(*tid,NULL);
    puts("end!");
    exit(0);
}
