#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<math.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>

static off_t flen(const char *fname){

	struct stat statres;
	if(stat(fname,&statres)<0){
		perror("stat()");
		exit(1);
	
	}
	return statres.st_size; 

}
static long long ftype(const char *fname){
	struct stat statres;
	if(stat(fname,&statres)<0){
		perror("stat()");
		exit(1);
	}

	return &(statres.st_mode);


}
static long long ftime(const char * fname){

	struct stat statrec;
	if(stat(fname,&statrec)<0){
		perror("stat()");
		exit(1);
	}
	printf("%X\n",&(statrec.st_ctime));
	return &(statrec.st_ctime);



}
int main(int argc,char **argv){
	
	if(argc<2){
	fprintf(stdout,"Uesge......");
	exit(1);
	}	
	printf("fsize=%d\n",flen(argv[1]));
	printf("ftype=%s\n",ftype(argv[1]));
	printf("ftime=%s\n",ctime(ftime(argv[1])));
	printf("ftime=%lld\n",ftime(argv[1]));
	return 0;
	exit(0);
}
