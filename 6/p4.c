#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define max 30005000
#define min 30000000
int main(){
	int i,j,mark;
	FILE * fp;
	fp = fopen("./tmp3","w");
	fclose(fp);
	fp = fopen("./tmp3","a+");
	fflush(NULL);
	int pp;	
	pid_t pid;
	for(i=min;i<max;i++){
		pid = fork();
		pp = i;
		if (pid==0){
			mark = 1;
			for(j=2;j<i/2;j++){
				if(i%j == 0){
					mark =0;
					break;			
				}
			}
			if(mark)
				fprintf(fp,"%d is that primer\n",i);
			fflush(fp);
			exit(0);
		}

	}	

	fclose(fp);
	printf("%d",pp);
	exit(0);

}
