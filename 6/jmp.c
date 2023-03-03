#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>
#include<stdint.h>
static jmp_buf save;	
//static char *buf="hello,world@";
static void c(void){
	
	printf("%s():start\n",__FUNCTION__);
//	printf("%s::%d\n",buf,buf);
	printf("%s() jmp now \n",__FUNCTION__);
	longjmp(save,6);
	printf("%s():end c()\n",__FUNCTION__);

}

static void b(void){
	
	printf("%s():start\n",__FUNCTION__);
	printf("%s():call c()\n",__FUNCTION__);

	c();
	printf("%s():c()\n",__FUNCTION__);
	printf("%s():end b()\n",__FUNCTION__);

}



static void a(void){
	
	printf("%s():start\n",__FUNCTION__);
	int rcc;
	rcc = setjmp(save);
	if(rcc==0){
		printf("%s():call b()\n",__FUNCTION__);
		b();
		printf("%s():b()\n",__FUNCTION__);
	}else{
	//	char * str1 = (char *)rcc;
	//	printf("char * =%d\n",sizeof(char *));
		printf("%s():jmp is %d\n",__FUNCTION__,rcc);
	}
	printf("%s():end a()\n",__FUNCTION__);


}	
int main(){
	
	printf("%s():start\n",__FUNCTION__);
	printf("%s():call a()\n",__FUNCTION__);
	a();
	printf("%s():a()\n",__FUNCTION__);
	printf("%s():end main()\n",__FUNCTION__);


exit(0);
}
