#include<stdio.h>
#include <stdlib.h>
int main(){
	
	FILE *fp;
	int ok;
	fp = fopen("tmp","w");

	if(fp==NULL){
		perror("fopen()");
		exit(0);
	}
	ok = fseek(fp,2000000,SEEK_SET);
	perror("fseek()");
	fprintf(stdout,"%d",ok);
	fclose(fp);

	

	exit(0);





}

