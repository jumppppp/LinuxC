#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define max 30005000
#define min 30000000
int main(){
	int i,j,mark;
	FILE * fp;
	fp = fopen("./tmp2","w");
	fclose(fp);
	fp = fopen("./tmp2","a+");
	fflush(NULL);
	int fx = max-min;

	pid_t pid;
	for(i=min;i<max;i++){
		pid = fork();
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
			fx--;	
			exit(0);
		}

	}	
if(fx<0){

fclose(fp);

exit(0);}

}
