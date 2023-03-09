#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
static int strlen(char *str1)
{
    int count = 0;
    for (int i = 0; str1[i] != '\0'; i++)
    {
        count++;
    }
    return count;
}
int main(int argc, char *argv[])
{
    int fd;
    struct stat statres;
    char *str;
    if (argc < 2)
    {
        printf("usege...");
    }
    fd = open(argv[1], O_RDONLY);
    if (fstat(fd, &statres) < 0)
    {
        exit(1);
    }
    str = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (str == MAP_FAILED)
    {
        exit(1);
    }
    close(fd);
    write(1, str, statres.st_size);
    printf("%d\n", statres.st_size);
    printf("%d\n", strlen(str));
    exit(0);
}
