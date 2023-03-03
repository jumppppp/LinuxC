#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>

int main(int argc,char * argv[]){

	//pass
	struct passwd *pw;

	pw = getpwuid(atoi(argv[1]));
	printf("pw_name=%s\npw_passwd=%s\npw_uid=%d\npw_gid=%d\npw_gecos=%s\npw_dir=%s\npw_shell=%s\n",pw->pw_name,pw->pw_passwd,pw->pw_uid,pw->pw_gid,pw->pw_gecos,pw->pw_dir,pw->pw_shell);

	




exit(0);
}
