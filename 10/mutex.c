#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define TMAX 100
#define FILENAME "tmp1"
static pthread_t plist[TMAX];
static void *func1(void *)
{
    char linebuf[1024];
    FILE *fp;
    fp = fopen(FILENAME,"r+");
    if(fp ==NULL){
        exit(1);
    }
    fgets(linebuf,1024,fp);
    fseek(fp,0,SEEK_SET);
    fprintf(fp,"%d",(atoi(linebuf)+1));
    fclose(fp);
    pthread_exit(NULL);
}
int main()
{
    pthread_t tid;
    for (int i = 0; i < TMAX; i++)
    {
        int err = pthread_create(&tid, NULL, func1, NULL);
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

    exit(0);
}
