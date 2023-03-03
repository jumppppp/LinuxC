#include<stdio.h>
#include<stdlib.h>
void f1(void){
	
printf("111\n");

}
void f2(void){

printf("222\n");
}
int main(){

printf("1\n");

atexit(f1);
atexit(f2);



printf("x\n");
exit(0);
}
