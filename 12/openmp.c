#include <stdio.h>
#include <stdlib.h>
int main()
{

#pragma omp parallel sections
    {
        #pragma omp section
        puts("hello world!");
        #pragma omp section
        puts("yes@");
    }
    

    exit(0);
}
