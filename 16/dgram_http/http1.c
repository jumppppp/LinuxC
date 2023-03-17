#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT "8080"
#define BUFSIZE 1024
int main()
{

    int so1 = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in laddr, raddr;
    char ipstr[128];
    socklen_t raddr_len;
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
    int bres = bind(so1, (void *)&laddr, sizeof(laddr));
    char buf[BUFSIZE];
    raddr_len = sizeof(raddr);
    while (1)
    {
        recvfrom(so1, buf, BUFSIZE, 0, (void *)&raddr, &raddr_len);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, 128);
        printf("MESSAFE FROM %s:%d\n", ipstr, ntohs(raddr.sin_port));
        printf("%d\n",buf);
    }
    exit(0);
}
