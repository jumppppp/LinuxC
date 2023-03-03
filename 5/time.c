#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define FNAME "./time_out"
#define BUFSIZE 1024
int main(){

	time_t t1;
	int rec;
	rec = time(&t1);
	printf("%d\n",t1);
	FILE * fp;
	char buf[BUFSIZE];
	struct tm *tm1;
	int count = 0;
	fp = fopen(FNAME,"a+");
	while(fgets(buf,BUFSIZE,fp) != NULL){
	 count++;
	}
	while(1)
	{
	time(&t1);
	tm1 = localtime(&t1);
	fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++count,\
			tm1->tm_year+1900,tm1->tm_mon+1,tm1->tm_mday,tm1->tm_hour,tm1->tm_min,tm1->tm_sec);
	sleep(1);
	fflush(fp);
	}
	fclose(fp);





exit(0);
}
