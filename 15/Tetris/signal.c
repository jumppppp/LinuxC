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
#define map_r 17
#define map_c 34
static int map_one[map_r][map_c];
struct xy_t
{
    int x;
    int y;
};

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
    for (int i = 0; i < map_r; i++)
    {
        for (int j = 0; j < map_c; j++)
        {
            if (i == 0 || i == map_r - 1)
            {
                map_one[i][j] = 1;
            }
            if (j == 0 || j == map_c - 1)
            {
                map_one[i][j] = 1;
            }
        }
    }
}
struct xy_t *demos(void)
{
    struct xy_t *demo1 = (struct xy_t *)malloc(8 * sizeof(struct xy_t));
    int k = 0;
    for (int num = 0; num < 8; num++)
    {

        demo1[num].x = 3;
        demo1[num].y = 10 + k;
        k++;
    }
    return demo1;
}
static void cat_map(void)
{
    fprintf(stdout, "\33[20;1H\33[0m");
    for (int i = 0; i < map_r; i++)
    {
        for (int j = 0; j < map_c; j++)
        {
            printf("%d", map_one[i][j]);
            fflush(NULL);
        }
        printf("\n");
    }
}
void draw(void)
{
    for (int i = 1; i < map_r - 1; i++)
    {
        for (int j = 1; j < map_c - 1; j++)
        {
            if (map_one[i][j] == 1)
            {
                fprintf(stdout, "\33[%d;%dH\33[44;35mM", i + row, j + column);
            }
            else
            {
                fprintf(stdout, "\33[%d;%dH\33[0m ", i + row, j + column);
            }
        }
    }
    fprintf(stdout, "\33[0m");
}
void load_draw(struct xy_t *demo)
{
    struct xy_t *me = demo;
    for (int i = 0; i < 8; i++)
    {
        map_one[me[i].x][me[i].y] = 1;
    }
    draw();
}
void remove_draw(struct xy_t *demo)
{
    struct xy_t *me = demo;

    for (int i = 1; i < map_r-1; i++)
    {
        for (int j = 1; j <map_c-1; j++)
        {
            if (map_one[i][j] == 1)
            {
                if (map_one[i + 1][j] == 1)
                {
                    goto r1;
                }
                else
                {
                }
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        map_one[me[i].x][me[i].y] = 0;
    }
r1:
    draw();
}
static void h1(int s)
{

    alarm(1);
}
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
    struct xy_t *demo1 = demos();

    load_draw(demo1);

    sleep(2);

    remove_draw(demo1);

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
