#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define LEFT 30000000
#define RIGHT 30050000
#define MAX_P 51200

static pthread_t plist[MAX_P];
struct thr_arg
{
    int arg;
};
static void *thr_prime(void *p)
{
    int mark = 1;
    int i = ((struct thr_arg *)p)->arg;

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

    int err;
    int pos;
    struct thr_arg *p;
    void *ptr;
    for (int i = LEFT; i <= RIGHT; i++)
    {
        p = malloc(sizeof(*p));
        if (p == 0)
        {
            exit(1);
        }
        p->arg = i;
        pthread_t tid;
        err = pthread_create(&tid, NULL, thr_prime, p);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            printf("count={{%d}}\n", i);
            exit(1);
        }
        pos = find_pos();
        // printf("<%d>", pos);
        if (pos == -1)
        {
            printf("find_pos_no!");
            exit(1);
        }
        plist[pos] = tid;
        // printf("[%d]",plist[pos]);
    }
    for (int i = 0; plist[i] == 0; i++)
    {
        pthread_join(plist[i], &ptr);
        free(ptr);
    }
    exit(0);
}
