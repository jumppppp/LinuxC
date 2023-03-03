#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

#define FAT "/etc/"

int main(){
struct dirent *cur;
DIR * dp;	
dp = opendir(FAT);


while((cur = readdir(dp)) != NULL){

puts(cur->d_name);


}

closedir(dp);


exit(0);
}
