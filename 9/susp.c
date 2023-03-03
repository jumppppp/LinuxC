#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

static void h1(int s)
{

    write(1, "@", 1);
}

int main()
{
    sigset_t set, oset, saveset;
    signal(SIGINT, h1);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
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

        sigsuspend(&oset); //xia mian de yu ju deng yu zhe ju hua(atomic operation)
        // signal_t tempset;
        // sigprocmask(SIG_SETMASK, &oset, &tempset);
        // pause();
        // sigprocmask(SIG_SETMASK,&tempset,NULL)
    }
    sigprocmask(SIG_SETMASK, &saveset, NULL);
    exit(0);
}
