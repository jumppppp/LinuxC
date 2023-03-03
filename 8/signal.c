#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
int main(){
signal(SIGINT,SIG_IGN);
for(int i = 0;i<11;i++){
	write(1,"*",1);
	sleep(1);
}
exit(0);
}
