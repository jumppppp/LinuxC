#include <stdio.h>
#include <stdlib.h>
#include "anytimer.h"
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
static struct job_queue_t *jobs[JOB_MAX];
static volatile sig_atomic_t ksec = 0;
struct job_t
{
	int sec;
	at_jobfunc_t *jobp;
	void *arg;
	int lock;
};
struct job_queue_t
{
	struct job_t *job_one;
	int pos;
};
static int get_free_pos(void)
{
	for (int i = 0; i < JOB_MAX; i++)
	{
		if (jobs[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}
static int get_free(void)
{
	for (int i = 0; i < JOB_MAX; i++)
	{
		// printf("<%d>",jobs[i]);
		//  jobs[i] == NULL
	}
}
int at_addjob(int sec, at_jobfunc_t *jobp, void *arg)
{
	get_free();
	struct job_t *me;
	me = malloc(sizeof(*me));
	// printf("me=%d\n", me);
	if (me == NULL)
	{
		return -1;
	}
	me->sec = sec;
	me->jobp = jobp;
	me->arg = arg;
	me->lock = 1;
	struct job_queue_t *job_me;
	int pos;
	pos = get_free_pos();
	// printf("pos=%d\n", pos);
	if (pos < 0)
		return -1;
	job_me = malloc(sizeof(*job_me));
	// printf("job_me=%d\n", job_me);
	if (job_me == NULL)
	{
		return -1;
	}
	job_me->job_one = me;
	job_me->pos = pos;
	jobs[pos] = job_me;

	return job_me->pos;
}
static void h1(int s)
{
	ksec = 1;
}
static void load_alarm()
{
	signal(SIGALRM, h1);
	struct itimerval t1;
	struct itimerval *t2 = NULL;
	t1.it_interval.tv_sec = 1;
	t1.it_interval.tv_usec = 0;
	t1.it_value.tv_sec = 1;
	t1.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &t1, t2);
	for (int id = 0; id < JOB_MAX; id++)
	{
		if (jobs[id] != NULL)
		{
			struct job_queue_t *job_me;
			job_me = jobs[id];
			struct job_t *me;
			me = job_me->job_one;
			while (1)
			{
				if (me->sec == 0)
				{
					me->jobp((char *)me->arg);
					break;
				}
				else
				{
					if (ksec)
					{
						me->sec = me->sec - 1;
						ksec = 0;
					}
					else
					{
						pause();
					}
				}
			}
		}
	}
}
int at_startjob(void)
{
	for (int id = 0; id < JOB_MAX; id++)
	{
		if (jobs[id] != NULL)
		{
			struct job_queue_t *job_me;
			if (jobs[id] == NULL)
			{
				return -1;
			}
			job_me = jobs[id];
			struct job_t *me;
			me = job_me->job_one;
			printf("---------------->\n|sec=%d\n|jobp=%d\n|arg=%s\n|lock=%d\n---------------->\n", me->sec, me->jobp, me->arg, me->lock);
		}
	}
	load_alarm();
	return 0;
}
int at_canceljob(int id)
{
	struct job_queue_t *job_me;
	if (jobs[id] == NULL)
	{
		return -1;
	}
	job_me = jobs[id];
	struct job_t *me;
	me = job_me->job_one;
	free(me);
	jobs[id] = NULL;
	me = NULL;
	free(job_me);
	job_me = NULL;
	return 0;
}

int at_waitjob(int id)
{
}
