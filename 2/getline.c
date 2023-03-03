#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char * argv[]){

	FILE *fp;
	char * linebuf;
	size_t linesize;
	if(argc<2){
		fprintf(stderr,"Usege ...");
		exit(1);

	}
	fp = fopen(argv[1],"r");
	if(fp==NULL){
		perror("fopen()");
		exit(1);
	}
	while(1){
	if(getline(&linebuf,&linesize,fp) <0){
		break;
	}else{
		linebuf = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

	}
	
	fprintf(stdout,"linebuf=%s,linesize1=%d,linesize2=%d\n",linebuf,strlen(linebuf),linesize);
	}








exit(0);
}

