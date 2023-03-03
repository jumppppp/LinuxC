//fopen de can shu r ,r+ ,w ,w+, a, a+,(b) byte
// ,but ,in the linux byte is steam
//
#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
void main(){
	int count =0;
	FILE * filep;
	while(1){
		filep = fopen("tmp","w");
		if(filep==NULL){
			char * charp;
			charp = strerror(errno);
			fprintf(stderr,"fopen():%s\n",charp);
			break;
		
		}
		count++;

	}
	printf("count:%d\n",count);
	exit(0);


}
