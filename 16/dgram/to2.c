#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "proto.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int so1;
    struct sockaddr_in laddr, raddr;
    char ipstr[128];
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, ("127.0.0.1"), &raddr.sin_addr);
    so1 = socket(AF_INET, SOCK_DGRAM, 0);
    struct msg_st sbuf;
    char tmp[128];
    while (1)
    {
        sprintf(tmp, "wang wei [%d]", rand() % 100);
        sprintf(sbuf.name, tmp);
        sbuf.chinese = htonl(rand() % 100);
        sbuf.math = htonl(rand() % 100);
        ssize_t res = sendto(so1, (void *)&sbuf, sizeof(sbuf), 0, (void *)&raddr, sizeof(raddr));
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
