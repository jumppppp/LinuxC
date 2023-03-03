#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
puts("start!\n");

fflush(NULL);

pid_t pid;
pid = fork();

if (pid<0){
	perror("fork()");
	exit(1);
}
if (pid==0){
	execl("/usr/bin/sleep","apache2","100",NULL);
	perror("execl()");
	exit(0);
}
wait(NULL);
puts("end\n");








exit(0);
}
