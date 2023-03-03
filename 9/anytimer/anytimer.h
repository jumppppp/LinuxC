#ifndef ANYTIMER_H__
#define ANYTIMER_H__
#define JOB_MAX 1024

typedef void at_jobfunc_t(char *);

int at_addjob(int sec,at_jobfunc_t *jobp,void *arg);

int at_startjob();
int at_canceljob(int id);

int at_waitjob(int id);

#endif