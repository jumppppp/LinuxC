#include<stdio.h>
#include<stdlib.h>

int main(){

FILE *fp;
int count=0;
while(1){
	fp = tmpfile();
	count++;
	// tmpnam
	fprintf(stdout,"%d\n",count);
	

}
fprintf(stdout,"%d\n",count);

exit(0);
}
