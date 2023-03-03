#include<stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	FILE *fp1,*fp2;
	int ch;
	if(argc <3){
		fprintf(stderr,"Usege:./mycopy src dst");
		exit(1);
	}
	fp1 = fopen(argv[1],"r");
	if(fp1 == NULL){
		perror("fopen");
		exit(1);
	}

	fp2 = fopen(argv[2],"w");
	if(fp2 == NULL){
		fclose(fp1);
		perror("fopen");
		exit(1);
	}
	while(1){
		ch = fgetc(fp1);
		printf("ch=%d\n",ch);
		if(ch==EOF){
			break;
		}
		fputc(ch,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	exit(0);

}
