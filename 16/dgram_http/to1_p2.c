#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "proto2.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
int main()
{
    int so1;
    struct sockaddr_in laddr, raddr;
    struct msg_st *msg;
    socklen_t raddr_len;
    char ipstr[128];
    so1 = socket(AF_INET, SOCK_DGRAM, 0);
    struct ip_mreqn val;
    inet_pton(AF_INET, MGROUP, &val.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &val.imr_address);
    val.imr_ifindex = if_nametoindex("eth0");
    setsockopt(so1, IPPROTO_IP, IP_ADD_MEMBERSHIP, &val, sizeof(val));
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
    int bres = bind(so1, (void *)&laddr, sizeof(laddr));
    size_t size = sizeof(struct msg_st) + NAMESIZE - 1;
    msg = malloc(size);
    /*!!!*/
    raddr_len = sizeof(raddr);
    while (1)
    {
        recvfrom(so1, msg, size, 0, (void *)&raddr, &raddr_len);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, 128);
        printf("MESSAFE FROM %s:%d\n", ipstr, ntohs(raddr.sin_port));
        if (ntohl(msg->math) > 10)
        {
            printf("NAME=%s\n", msg->name);
            printf("MATH=%d\n", ntohl(msg->math));
            printf("CHINESE=%d\n", ntohl(msg->chinese));
        }
        else
        {
            printf("%d so low\n", ntohl(msg->math));
        }
    }

    close(so1);
    exit(0);
}
