#ifndef RELAYER_H_
#define RELAYER_H_
#define REL_JOBMAX 1024
enum{
    STATE_OVER,
    STATE_RUN,
    STATE_CANCEL,
};
struct rel_stat_st{
    int state;
    int fd1;
    int fd2l;
};
int rel_addjob(int fd1,int fd2);

int rel_celjob(int fd1,int fd2);

int rel_waitjob(int id,struct rel_stat_st *rs);

int rel_statjob(int id,struct rel_stat_st * rs);

#endif