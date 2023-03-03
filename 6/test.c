#include<stdio.h>
#include<stdlib.h>
#define OL "hello"
int main(){
void * pl=&OL;
printf("**=%d\n*=%d\n*(void **)(&x)=%d\n*(x)=%d\n",&pl,&OL,*(void**)(&pl),*(&OL));




exit(0);
}
