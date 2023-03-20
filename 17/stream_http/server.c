#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#define PORT "2000"
void server_job(int sd)
{
    char buf[256];
    int len = sprintf(buf, "%lld\n", (long long)time(NULL));
    ssize_t res = send(sd, buf, len, 0);
    if (res < 0)
    {
        perror("send()");
    }
}
int main()
{

    int so1 = socket(AF_INET, SOCK_STREAM, 0);
    if (so1 < 0)
    {
        exit(1);
    }
    int val = 1;
    setsockopt(so1, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    char ipstr[128];
    struct sockaddr_in laddr, kaddr;
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
    bind(so1, (void *)&laddr, sizeof(laddr));
    listen(so1, 200);
    socklen_t kaddr_len = sizeof(kaddr);
    pid_t pid;
    while (1)
    {
        int newsd = accept(so1, (void *)&kaddr, &kaddr_len);

        pid = fork();
        if (pid < 0)
        {
            exit(1);
        }
  
        if (pid == 0)
        {
            close(so1);
            inet_ntop(AF_INET, &kaddr.sin_addr, ipstr, 128);
            printf("%s:%d\n", ipstr, ntohs(kaddr.sin_port));
            server_job(newsd);
            close(newsd);
            exit(0);
        }else{
            close(newsd);
        }
    }
    close(so1);
    exit(0);
}
