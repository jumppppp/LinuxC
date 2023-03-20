#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <wait.h>
#define PORT "2000"
#define PORCNUM 10
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
    char buf[1024] = {0};
    char ch;
    pid_t pid;
    FILE *fp;
    while (1)
    {
        int newsd = accept(so1, (void *)&kaddr, &kaddr_len);
        for (int i = 0; i < PORCNUM; i++)
        {
            pid = fork();
            if (pid == 0)
            {
                fp = fdopen(newsd, "r+");
                fprintf(fp, "%s\n", "kkk");
                int i = 0;
                while (fscanf(fp, "%c", &ch) > 0)
                {
                    buf[i] = ch;
                    i++;
                }
                // fscanf(fp, "%s", buf);
                fprintf(stdout, "%s\n", buf);
                fclose(fp);
                close(newsd);

                exit(0);
            }
        }
        for (int i = 0; i < PORCNUM; i++)
        {
            wait(NULL);
        }
    }
    close(so1);
    exit(0);
}
