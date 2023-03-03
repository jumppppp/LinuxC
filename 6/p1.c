#include<stdio.h>
#include<stdlib.h>
#define max 30005000
#define min 30000000
int main(){
	int i,j,mark;
	FILE * fp;
	fp = fopen("./tmp1","w");
	for(i=min;i<max;i++){
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




	}	
	fclose(fp);

	exit(0);
}
