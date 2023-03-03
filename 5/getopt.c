#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#define OUTSIZE 1024
#define FMTSIZE 1024
int main(int argc,char ** argv){
	
	FILE *fp=stdout;	
	time_t t1;
	time(&t1);
	struct tm *tm1;
	tm1 = localtime(&t1);
	char outstr[OUTSIZE];
	int c;
	char * fmtstr[FMTSIZE];
	while(1){

	c = getopt(argc,argv,"-H:MS");
	if (c<0){break;}
	switch(c){
		case 1:
			fp = fopen(argv[optind-1],"a+");
			if(fp==NULL){
				perror("fopen()");
				fp=stdout;
			}
			break;
		case 'H':
			if(strcmp(optarg,"12")==0)
				strncat(fmtstr,"%I(%p) ",FMTSIZE);
			else if(strcmp(optarg,"24")==0)
				strncat(fmtstr,"%H ",FMTSIZE);
			else
				fprintf(stderr,"NO");
			break;
		case 'M':
			strncat(fmtstr,"%M ",FMTSIZE);
			break;
		case 'S':
			strncat(fmtstr,"%S ",FMTSIZE);
			break;
		default:
			break;
	}


	}
	strftime(outstr,OUTSIZE,fmtstr,tm1);
	
      	fprintf(fp,"%s\n",outstr);
	if(fp!=stdout){
	fclose(fp);
	}



exit(0);
}
