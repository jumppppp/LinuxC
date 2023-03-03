#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<syslog.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#define NNAME "/home/test/linuxc/9/null"
#define FNAME "/home/test/linuxc/9/out"
static FILE * fp;
static int  deamon_n1(void){
	int fd;
	pid_t pid;
	fflush(NULL);
	pid = fork();
	if (pid<0){
		perror("fork()");
		return -1;
	}
	if (pid>0){
		exit(0);
	}
	FILE *ffp;

	ffp = fopen(NNAME,"w");
	if(ffp == NULL)
	{
		perror("fopen2()");
		return -1;
	}
	fclose(ffp);
	fd = open(NNAME,O_RDWR);
	if(fd<0){
		perror("open()");
		return -1;
	}
	dup2(fd,0);
	dup2(fd,1);
	dup2(fd,2);
	if (fd>2)
		close(fd);
	pid_t pid2;
	
	pid2 = setsid();
	printf("%d\n",pid2);
	chdir("/");
	//	umask(0);
	return 0;

}
static void daemon_exit(int s)
{
	if(s==SIGINT){

	}else if (s=SIGQUIT){

	}else if(s=SIGTERM){

	}
	fclose(fp);
	closelog();
}


int main(){

	struct sigaction sa;
	sa.sa_handler = daemon_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,SIGQUIT);
	sigaddset(&sa.sa_mask,SIGTERM);
	sigaddset(&sa.sa_mask,SIGINT);
	sa.sa_flags = 0;
	sigaction(SIGINT,&sa,NULL);
	// signal(SIGINT,daemon_exit);
	// signal(SIGQUIT,daemon_exit);
	// signal(SIGTERM,daemon_exit);
	openlog("mydaemon",LOG_PID,LOG_DAEMON);
	
	if (deamon_n1()){
		syslog(LOG_ERR,"daemon_n1() failed!");

	}else{
		syslog(LOG_INFO,"daemon_n1 ok!");
	}
	fp = fopen(FNAME,"w");
	if(fp==NULL){
		syslog(LOG_ERR,"fopen():%s",strerror(errno));
		exit(1);
	}
	syslog(LOG_INFO,"%s was opened.",FNAME);
	for(int i=0;i>=0;i++){
		fprintf(fp,"%d\n",i);
		fflush(fp);

		sleep(1);
	}

	exit(0);
}
