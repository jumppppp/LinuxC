#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char **argv)
{


if(argc<2){printf("Usege...");exit(1);}
int fd;

fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);


lseek(fd,5LL*1024*1024*1024,SEEK_SET);
write(fd,"",1);
close(fd);

exit(0);
}

