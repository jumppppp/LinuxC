#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
static int row = 2;
static int column = 4;
static int row_z = 16;
static int column_z = 32;
static int map_one[18][34];
struct xy_t
{
    int x;
    int y;
};
static void h1(int s)
{
    alarm(1);
}
static void init_load(void)
{

    fprintf(stdout, "\033[2J");
    fprintf(stdout, "\033[%d;%dH\033[43;32m==================================", row, column);
    for (int i = row + 1; i < row + row_z; i++)
    {
        fprintf(stdout, "\033[%d;%dH\033[43;32m||", i, column);
        fprintf(stdout, "\033[%d;%dH\033[43;32m||", i, column + column_z);
    }
    fprintf(stdout, "\033[%d;%dH\033[43;32m==================================", row + row_z, column);
    fprintf(stdout, "\33[0m");
    fprintf(stdout, "\33[%d;%dH", row + 1, column + column_z / 2);
}
static void init_map(void)
{
    for (int i = 0; i < row_z + 2; i++)
    {
        for (int j = 0; j < column_z + 2; j++)
        {
            if (i == 0 || i == row_z + 1)
            {
                map_one[i][j] = 1;
            }
            if (j == 0 || j == column_z + 1)
            {
                map_one[i][j] = 1;
            }
        }
    }
}
struct xy_t * demos(void)
{
    struct xy_t *demo1 = (struct xy_t * )malloc(8*sizeof(struct xy_t));
    int k =0;
    for (int num = 0; num < 8; num++)
    {
            
            demo1[num].x = 3;
            demo1[num].y = 10+k;
            k++;
    }
    return demo1;
}
static void cat_map(void)
{
    for (int i = 0; i < row_z + 2; i++)
    {
        for (int j = 0; j < column_z + 2; j++)
        {
            printf("%d ", map_one[i][j]);
            fflush(NULL);
        }
        printf("\n");
    }
}
void draw()
int main()
{
    init_load();
    struct termios tm_new, tm_old;
    tcgetattr(0, &tm_new);
    tcgetattr(0, &tm_old);
    tm_new.c_lflag = tm_new.c_lflag & ~(ICANON | ECHO);
    tm_new.c_cc[VMIN] = 1;
    tm_new.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tm_new);
    init_map();
    struct xy_t * demo1 = demos();
    for (int i=0;i<8;i++){
        printf("x=%d\ty=%d\n",demo1[i].x,demo1[i].y);
    }
    int ch;
    signal(SIGALRM, h1);
    alarm(1);

    while (1)
    {
        ch = getchar();
        switch (ch)
        {
        case 'Q':
            goto end;
        case 'w':
            printf("w");
            continue;
        case 's':
            printf("s");
            continue;
        case 'a':
            printf("a");
            continue;
        case 'd':
            printf("d");
            continue;
        }
        fflush(NULL);
    }
end:
    tcsetattr(0, TCSANOW, &tm_old);
    exit(0);
}
