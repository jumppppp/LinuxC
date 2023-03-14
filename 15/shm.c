#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include<wait.h>
#include<sys/types.h>
#include<unistd.h>
static size_t st = 1024;
int main()
{

    int shmid = shmget(IPC_PRIVATE, st, 0600);
    pid_t pid;
    char *ptr;
    pid = fork();
    if (pid == 0)
    {
        ptr = shmat(shmid, NULL, 0);
        if (ptr == (void *)-1)
        {
            perror("shmat()");
            exit(1);
        }
        char * tmp ="sadsadsa";
        strcpy(ptr, tmp);
        shmdt(ptr);
        exit(0);
    }
    if (pid > 0)
    {
             wait(NULL);
        ptr = shmat(shmid, NULL, 0);
        if (ptr == (void *)-1)
        {
            perror("shmat()");
            exit(1);
        }
        puts(ptr);
        shmdt(ptr);
   
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
    }

    exit(0);
}
