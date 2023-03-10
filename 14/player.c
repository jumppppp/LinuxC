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
    int fd = open("tmp1", O_RDWR | O_CREAT);
    pd[1] = fd;
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
        dup2(pd[0], 0);
        close(pd[0]);
        open("./tmp2", O_RDWR | O_CREAT);
        dup2(fd, 1);
        dup2(fd, 2);
        execl("./bb.mp3", "mpg123", "-", NULL);
        perror("execl();");
        exit(1);
    }
    if (pid > 0)
    {
        printf("parent\n");
        close(pd[0]);

        write(pd[1], "fuck you\t", 9);
        sleep(1);
    }
    close(pd[1]);
    wait(NULL);

    exit(0);
}
