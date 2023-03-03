#include <stdio.h>
#include<stdlib.h>
#include<glob.h>


/*int errfunc_(char * errpath,int erno){
	puts(errpath);
	fprintf(stderr,"NO:%s\n",strerror(erno));
}*/


int main(int argc,char **argv){
	
	if(argc<2){
		printf("Uesge....");
		exit(1);
	}
	argv[1]="/etc/*";	
	int err;
	int i;
	glob_t globres;	
	err = glob(argv[1],0,NULL,&globres);
	if(err){printf("%d\n",err);exit(1);;}
	for(i=0;i<globres.gl_pathc;i++){
		puts(globres.gl_pathv[i]);
	}
	globfree(&globres);

	exit(0);
}
