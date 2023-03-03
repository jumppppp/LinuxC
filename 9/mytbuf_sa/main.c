#include<stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>
#include"mytbf.h"
#include<string.h>
#define cps 10
#define BUFSIZE 1024
#define burst_max 1000
int main(int argc,char *argv[]){

        FILE *fp1;
        int ch;
        if(argc <2){
                fprintf(stderr,"Usege:./main src speed(defalut 10)");
                exit(1);
        }
        mytbf_t *tbf;
	tbf = mytbf_init(atoi(argv[2]),burst_max);
        if (tbf ==NULL){
                fprintf(stderr,"mytbf_init()");
                exit(1);
        }
        fp1 = fopen(argv[1],"r");
	if(fp1 == NULL){
		perror("fopen");
		exit(1);
	}
	int j = 0;
        int size;
        int ret;
        int di;
        while(1){
		size = mytbf_fetchtoken(tbf,BUFSIZE);
                if (size<0){
                        fprintf(stderr,"mytbf_fetchtoken():%s\n",strerror(-size));
                        exit(1);
                }
                //printf("%d\n",(int)size);
                di = 0;
                for(int i = 0;i<size;i++){
                        ch= fgetc(fp1);
                        if(ch==EOF){
                                break;
                        }
                        fprintf(stdout,"%c",ch);
                        fflush(NULL);
                        di++;
                }
                //printf("<<%d>>",size-di);
                ret = mytbf_returntoken(tbf,size-di);
                if (size-di>0){
                        break;
                }
        }
	mytbf_destroy(tbf);
        fclose(fp1);
        exit(0);

}

