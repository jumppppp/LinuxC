#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "proto2.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char ** argv)
{
    if(argc<2){
        printf("usege...");
        exit(1);
    }
    if(strlen(argv[1])>NAMESIZE){
        printf("so long name!");
        exit(1);
    }
    int so1;
    struct sockaddr_in laddr, raddr;
    char ipstr[128];
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, ("127.0.0.1"), &raddr.sin_addr);
    so1 = socket(AF_INET, SOCK_DGRAM, SO_BROADCAST);
    struct msg_st * sbufp;
    size_t size = sizeof(struct msg_st)+strlen(argv[1]);
    sbufp = malloc(size);
    char tmp[128];
    while (1)
    {
        sprintf(tmp, "%s [%d]", argv[1],rand() % 100);
        sprintf(sbufp->name, tmp);
        printf("%s\n",sbufp->name);
        sbufp->chinese = htonl(rand() % 100);
        sbufp->math = htonl(rand() % 100);
        ssize_t res = sendto(so1, (void *)sbufp, size, 0, (void *)&raddr, sizeof(raddr));
        if (res < 0)
        {
            perror("sendto()");
        }
        else
        {
            puts("OK!");
        }
        sleep(5);
    }
    close(so1);
    exit(0);
}
