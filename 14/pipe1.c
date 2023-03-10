#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PIPESIZE 1024
#define BUFSIZE 1024

int main()
{

    int pd[2];
    int k = pipe(pd);
    int fd = open("tmp1",O_RDWR|O_CREAT); 
    pd[1]=fd;
    char buf[BUFSIZE];
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("nofork\n");
        exit(1);
    }
    if (pid == 0)
    {
        printf("child\n");
        while (1)
        {
            int len = read(pd[0], buf, BUFSIZE);
            write(1, buf, len);
        }
        close(pd[0]);
    }
    if (pid > 0)
    {
        printf("parent\n");
        while (1)
        {
            write(pd[1], "fuck you\t", 9);
            sleep(1);
        }
        close(pd[1]);
        wait(NULL);
    }
    exit(0);
}

