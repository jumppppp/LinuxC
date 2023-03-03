#include<stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>

#define cip 10
static volatile int loop=1;
static void h1(int s){
	alarm(1);
	loop = 0;

}


int main(int argc,char *argv[]){

	signal(SIGALRM,h1);
	FILE *fp1;
	int ch;
	if(argc <2){
		fprintf(stderr,"Usege:./mycopy src");
		exit(1);
	}
	alarm(1);
	fp1 = fopen(argv[1],"r");
	if(fp1 == NULL){
		perror("fopen");
		exit(1);
	}
	int j = 0;
	while(1){
		//printf("%d::%d\n",j,loop);
		if(j%10==0){
			while(loop){
				pause();

			}
			loop=1;
		}else{
		ch= fgetc(fp1);
		if(ch==EOF){
			break;
		}
		fprintf(stdout,"%c",ch);
		fflush(NULL);
		}
		j++;
	}

	fclose(fp1);
	exit(0);

}
