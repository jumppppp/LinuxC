#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
#include "proto.h"
int main()
{
    key_t key;
    struct msg_st sbuf;
    sbuf.mtype = 1;
    strcpy(sbuf.name,"test/0\0pp");
    sbuf.math = 100;
    sbuf.chinese = 90;
    key =ftok(KEYPATH,KEYPROJ);
    int msg_id = msgget(key,0);
    msgsnd(msg_id,&sbuf,sizeof(sbuf),0);
    printf("OK\n");

    exit(0);
}
