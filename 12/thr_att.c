#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
static void *func(void *)
{
}
int main()
{
    pthread_t tid;
    int count;
    pthread_attr_t attr;
    size_t stack_size;
    pthread_attr_init(&attr);

    pthread_attr_getstacksize(&attr, &stack_size);
    printf("stack_size=%dM\n", stack_size / 1024 / 1024);
    pthread_attr_setstacksize(&attr, 2000000);
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("stack_size=%dM\n", stack_size / 1024 / 1024);
    while (1)
    {
        int err = pthread_create(&tid, NULL, func, NULL);
        if (err)
        {
            fprintf(stderr, "no\n");
            printf("count=%d\n", count);
            break;
        }
        count += 1;
    }

    exit(0);
}
