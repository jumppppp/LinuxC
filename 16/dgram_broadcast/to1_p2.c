#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "proto2.h"
#include <arpa/inet.h>
#include<unistd.h>
int main()
{
    int so1;
    struct sockaddr_in laddr, raddr;
    struct msg_st *msg;
    socklen_t raddr_len;
    char ipstr[128];
    so1 = socket(AF_INET, SOCK_DGRAM, SO_BROADCAST);

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, "255.255.255.255", &laddr.sin_addr);
    int bres = bind(so1, (void *)&laddr, sizeof(laddr));
    size_t size = sizeof(struct msg_st)+NAMESIZE-1;
    msg = malloc(size);
    /*!!!*/
    raddr_len = sizeof(raddr);
    while (1)
    {
        recvfrom(so1, msg, size, 0, (void *)&raddr, &raddr_len);
        inet_ntop(AF_INET,&raddr.sin_addr,ipstr,128);
        printf("MESSAFE FROM %s:%d\n",ipstr,ntohs(raddr.sin_port));
        printf("NAME=%s\n",msg->name);
        printf("MATH=%d\n",ntohl(msg->math));
        printf("CHINESE=%d\n",ntohl(msg->chinese));
    }

    close(so1);
    exit(0);
}
