#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<glob.h>
#include<string.h>

#define PATHSIZE 1024

static int path_noloop(const char*path){
	char * num;
	num = strrchr(path,'/');
	if(num == NULL){return -1;}
	if(strcmp(num+1,".")==0 || strcmp(num+1,"..")==0){
		return -1;
	}
	return 1;

}

static int64_t mydu(const char *path){
	int64_t sum=0;
	struct stat srec;
	char path1[PATHSIZE];
	char path2[PATHSIZE];
	glob_t globres;
	int i;
	if(lstat(path,&srec)<0){
	
	exit(1);
	}
	if(!S_ISDIR(srec.st_mode)){
		return srec.st_blocks;
	}
	
	strncpy(path1,path,PATHSIZE);
	strncat(path1,"/*",PATHSIZE);
	strncpy(path2,path,PATHSIZE);
	strncat(path2,"/.*",PATHSIZE);

	glob(path1,0,NULL,&globres);
	glob(path2,GLOB_APPEND,NULL,&globres);
	sum = 0;
	for(i=0;i<globres.gl_pathc;i++){
		if(path_noloop(globres.gl_pathv[i])){

			sum+=mydu(globres.gl_pathv[i]);
		}

	}
	
	sum += srec.st_blocks;
	globfree(&globres);
	return sum;


}

int main(int argc, char **argv){

if(argc <2){
	printf("Usege.....\n");
	exit(1);
}



printf("%lld\n",mydu(argv[1])/2);


exit(0);
}
