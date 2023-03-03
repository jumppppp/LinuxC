#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){

	puts("begin!");
	fflush(NULL);
	execl("/home/test/linuxc/6/p2","p2",NULL);
	perror("execl");
	exit(1);
	puts("end");
	fflush(NULL);
	exit(0);

}
