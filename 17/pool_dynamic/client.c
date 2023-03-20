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
int main(int argc,char **argv)
{

    int so1 = socket(AF_INET, SOCK_STREAM, 0);
    char  tmp[1024];
    if (so1 < 0)
    {
        exit(1);
    }
    char ipstr[128];
    struct sockaddr_in kaddr;
    kaddr.sin_family=AF_INET;
    kaddr.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET,"127.0.0.1",&kaddr.sin_addr);

    connect(so1,(void * )&kaddr,sizeof(kaddr));
    FILE *fp = fdopen(so1,"r+");
    if (fp==NULL){
        printf("NO1\n");
        exit(1);

    }
    int res = fscanf(fp,"%s",tmp);
    if (res<0){
        printf("NO2\n");
        exit(1);
    }
    printf("res=%lld\n",tmp);
    fclose(fp);
    exit(0);
}
