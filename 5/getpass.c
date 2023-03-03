#include<stdio.h>
#include<stdlib.h>
#include<shadow.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char **argv){
char *input_pass;
char *c1;
struct spwd *s1;
input_pass = getpass("password:");

s1 = getspnam(argv[1]);	
c1 = crypt(input_pass,s1->sp_pwdp);
printf("%s\n",c1);
if (strcmp(s1->sp_pwdp,c1)==0){
	puts("ok");


}else{
puts("no");
}

exit(0);
}

