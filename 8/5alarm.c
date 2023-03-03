#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
static volatile int loop =1;
static void h1(int s){

	loop=0;
}

int main(){
	alarm(5);
	signal(SIGALRM,h1);
	int64_t count;

	while(loop)
		count++;
		
	printf("%lld\n",count);




exit(0);
}
