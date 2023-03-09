#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
#define MEMSIZE 1024
int main()
{

    void *ptr;
    ptr = mmap(NULL, MEMSIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        strcpy(ptr, "hello!");
        munmap(ptr, MEMSIZE);
        exit(0);
    }
    else
    {
        wait(NULL);
        puts(ptr);
        munmap(ptr, MEMSIZE);
        exit(0);
    }
}
