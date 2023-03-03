#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define MRT (SIGRTMIN+6)
static void h1(int s)
{

    write(1, "@", 1);
}

int main()
{
    sigset_t set, oset, saveset;
    signal(MRT,h1);
    sigemptyset(&set);
    sigaddset(&set, MRT);
    sigprocmask(SIG_UNBLOCK, &set, &saveset);
    for (int i = 0; i < 1000; i++)
    {
        sigprocmask(SIG_BLOCK, &set, &oset);
        for (int j = 0; j < 6; j++)
        {

            write(1, "*", 1);
            sleep(1);
        }
        write(1, "\n", 1);

        sigsuspend(&oset); 
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);
    exit(0);
}





