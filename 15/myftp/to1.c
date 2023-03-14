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
    int msg_id1 = msgget(key1, 0);
    int msg_id2 = msgget(key2, 0);
    while (1)
    {
        msgrcv(msg_id1, &sp, sizeof(sp), 0, 0);
        printf("path=%s\n", sp.path);

        FILE *fp = fopen(sp.path, "r");
        if (fp == NULL)
        {
            sd.datalen = 0;
            strcpy(sd.data, "no file!");
            msgsnd(msg_id2, &sd, sizeof(sd), 0);
            continue;
        }
        char buf[DATAMAX];
        while (fgets(buf, DATAMAX, fp) != NULL)
        {
            strcpy(sd.data, buf);
            sd.datalen = strlen(buf) + 1;
            msgsnd(msg_id2, &sd, sizeof(sd), 0);
        }
        sd.datalen = 0;
        strcpy(sd.data, "data end!\n");
        msgsnd(msg_id2, &sd, sizeof(sd), 0);
        fclose(fp);
    }
    exit(0);
}
