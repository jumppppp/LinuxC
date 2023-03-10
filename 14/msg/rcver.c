#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "proto.h"
int main()
{
    key_t key;
    struct msg_st rbuf;
    key = ftok(KEYPATH, KEYPROJ);
    if (key < 0)
    {
        perror("ftok");
        exit(1);
    }
    int msg_id = msgget(key, IPC_CREAT | 0600);
    while (1)
    {
        msgrcv(msg_id, &rbuf, sizeof(rbuf), 0, 0);
        printf("name=%s\n", rbuf.name);
    }

    msgctl(msg_id,IPC_RMID,NULL);
    exit(0);
}
