#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>

static void h1(int s){

	write(1,"@",1);
}


int main(){



signal(SIGINT,h1);

for(int i = 0;i<11;i++){

	write(1,"*",1);
	sleep(1);

}



exit(0);
}
