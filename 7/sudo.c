#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc,char **argv){

	pid_t pid;
	pid = fork();
	if(pid<0)
		exit(1);
	if(pid==0){
		setuid(atoi(argv[1]));
		execvp(argv[2],argv+2);

	}else{
		wait(NULL);
	}

	exit(0);
}
