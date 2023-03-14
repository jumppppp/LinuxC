#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "myftp.h"
int main()
{
    key_t key1, key2;
    struct msg_path_st sp;
    struct msg_data_st sd;
    char *tmp;
    key1 = ftok(KEYPATH, KEYPROJ);
    if (key1 < 0)
    {
        perror("ftok");
        exit(1);
    }
    key2 = ftok(KEYPATH2, KEYPROJ2);
    if (key2 < 0)
    {
        perror("ftok");
        exit(1);
    }
    int msg_id1 = msgget(key1, IPC_CREAT | 0600);
    int msg_id2 = msgget(key2, IPC_CREAT | 0600);

    while (1)
    {
        printf("[$]-");
        int k = scanf("%s", tmp);
        if(k<0){
            perror("scanf()");
            exit(1);
        }
        strcpy(sp.path, tmp);
        printf("sp=%s\n", sp.path);

        msgsnd(msg_id1, &sp, sizeof(sp), 0);
        while (1)
        {
            msgrcv(msg_id2, &sd, sizeof(sd), 0, 0);
            printf("%d+%s", sd.datalen, sd.data);
            if (sd.datalen == 0)
            {
                printf("%d+%s", sd.datalen, sd.data);
                break;
            }
        }
    }
    msgctl(msg_id1, IPC_RMID, NULL);
    msgctl(msg_id2, IPC_RMID, NULL);
    exit(0);
}
