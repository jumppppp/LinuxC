#include <stdio.h>
#include <stdlib.h>
#include "mytbf.h"
#include <unistd.h>
#include <signal.h>
#include <errno.h>

typedef void (*sighandler_t)(int);
static struct mytbf_st *job[MYTBF_MAX];
static int inited = 0;
static sighandler_t alarm_save;
struct mytbf_st
{

	int cps;
	int burst;
	int token;
	int pos;
};
static int get_free_pos(void)
{

	for (int i = 0; i < MYTBF_MAX; i++)
	{
		if (job[i] == NULL)
		{
			return i;
		}
		
	}
	return -1;
}

static void module_unload(void)
{

	signal(SIGALRM, alarm_save);
	alarm(0);
	for (int i = 0; i < MYTBF_MAX; i++)
		free(job[i]);
}

static void h1(int s)
{
	alarm(1);
	for (int i = 0; i < MYTBF_MAX; i++)
	{
		if (job[i] != NULL)
		{
			job[i]->token += job[i]->cps;
			if (job[i]->token > job[i]->burst)
			{

				job[i]->token = job[i]->burst;
			}
		}
	}
}

static void module_load(void)
{

	alarm_save = signal(SIGALRM, h1);
	alarm(1);
	atexit(module_unload);
}

mytbf_t *mytbf_init(int cps, int burst)
{
	if (!inited)
	{
		module_load();
		inited = 1;
	}
	int pos;
	struct mytbf_st *me;
	pos = get_free_pos();
	if (pos < 0)
		return NULL;
	me = malloc(sizeof(*me));
	if (me == NULL)
	{
		return NULL;
	}
	me->token = 0;
	me->cps = cps;
	me->burst = burst;
	me->pos = pos;
	job[pos] = me;
	return me;
}

static int min(int a, int b)
{

	if (a < b)
		return a;
	return b;
}
int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
	struct mytbf_st *me = ptr;
	int n;
	if (size <= 0)
	{
		return -EINVAL;
	}
	while (me->token <= 0)
		pause();
	n = min(me->token, size);
	me->token -= n;
	return n;
}
int mytbf_returntoken(mytbf_t *ptr, int size)
{
	struct mytbf_st *me = ptr;

	if (size <= 0)
	{
		return -EINVAL;
	}
	me->token += size;
	if (me->token > me->burst)
	{
		me->token = me->burst;
	}
	return size;
}

int mytbf_destroy(mytbf_t *ptr)
{

	struct mytbf_st *me = ptr;
	job[me->pos] = NULL;
	free(ptr);
	return 0;
}
