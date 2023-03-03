#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"anytimer.h"
#include<sys/types.h>
#include<unistd.h>
static void f1(char *arg){

	printf("f1=%s\n",arg);
}
static void f2(char *arg){

	printf("f2=%s\n",arg);
}
static void f3(char *arg){

	printf("f3=%s\n",arg);
}
int main(){

	puts("start!");
	int job1 = at_addjob(5,f1,"aaa");
	// if(job1 < 0){
	// 	fprintf(stderr,"at_addjob():%s\n",strerror(-job1));
	// 	exit(1);
	// }
	printf("job=%d\n",job1);

	// at_canceljob(job1);
	// at_canceljob(job1);
	// at_startjob(job1);
	int job2 = at_addjob(2,f2,"bbb");

	printf("job=%d\n",job2);
	// at_canceljob(job2);
	int job3 = at_addjob(7,f3,"ccc");
	printf("job=%d\n",job3);
	// at_canceljob(job3);
		at_startjob();
	puts("end.");

	exit(0);
}