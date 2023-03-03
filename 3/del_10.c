#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#define BUFFSIZE 1024

int main(){

	int fd1;
	int fd2;
	fd1 = open("demo",O_RDONLY);
	fd2 = open("demo",O_RDWR);
	off_t num;
	ssize_t num_size;
	char buf[BUFFSIZE];
	size_t size_1;
	//num_size = read(fd1,&buf,100);
	//fprintf(stdout,"%d\n%s\n",num_size,buf);
	lseek(fd1,20000000,SEEK_SET);
	int count=1;
	while(1){
	num_size = read(fd1,&buf,1);
	lseek(fd1,count,0);
	fprintf(stdout,"%d::%s\n",num_size,buf);
	if(buf=="\n"){
		count++;
	}
	if(num_size <0){
		break;
	}
	}
	fprintf(stdout,"%d\n",count);
	close(fd1);
	close(fd2);
	exit(0);

}
