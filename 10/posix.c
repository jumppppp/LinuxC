#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define LEFT 30000000
#define RIGHT 30005000
#define MAX_P 65535

static pthread_t *plist[MAX_P];

static void *thr_prime(void *p)
{
    int mark =1;
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
        printf("%d", i);
    }
    pthread_exit(NULL);
}
static int find_pos(void)
{
    for (int i = 0; i < MAX_P; i++)
    {
        if (plist[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    
    printf("<<%d>>", 1);
    int err;
    int pos;
    pthread_t *tid=NULL;
    printf("<<%d>>",2);
    for (int i = LEFT; i <= RIGHT; i++)
    {
        err = pthread_create(tid, NULL, thr_prime, &i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
        pos = find_pos();
        printf("<<%d>>", pos);
        if (pos == -1)
        {
            printf("find_pos_no!");
            exit(1);
        }
        plist[pos] = tid;
    }
    for (int i = 0; plist[i] == NULL; i++)
    {
        pthread_join(*plist[i], NULL);
    }
    exit(0);
}
