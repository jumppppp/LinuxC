#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	pid_t pid1;
	printf("[%d]chat:\n",getpid());
	fflush(NULL);   /*!!!!!!!!!!!!*/
	pid1 = fork();
	if(pid1<0){
		perror("fork():");
	}else if(pid1==0){
		char c1='b';
	//	c1 = getchar();

		printf("[%d]chat:child::%c\n",getpid(),c1);
	}else{
		char c2='a';
	//	c2 = getchar();
		printf("[%d]chat:parent::%c\n",getpid(),c2);
	}
	printf("[%d]end:\n",getpid());




exit(0);
}
