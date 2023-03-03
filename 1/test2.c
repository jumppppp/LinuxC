//fopen de can shu r ,r+ ,w ,w+, a, a+,(b) byte
// ,but ,in the linux byte is steam
//
#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
void main(){

	FILE * filep;
	filep = fopen("tmp","r");
	if(filep==NULL){
	
	//	perror("fopen");
		char * charp;
		charp = strerror(errno);
		fprintf(stderr,"fopen():%s\n",charp);
		exit(1);
		
	}
	puts("ok");
	exit(0);


}
