#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <alloca.h>
#include <ctype.h>
#include <execinfo.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>

#include "list.h"

struct a_list
{
	struct list_head list;
	int val;
	const char *str;
};

#define CORE_PATH "/var/crash"
#define ULIMIT_CORE "ulimit -c unlimited"
#define CMD "LD_SHOW_AUXV=1 LD_PRELOAD=/lib/aarch64-linux-gnu/libSegFault.so ./ludtm"

#define __HELP "--help"
#define __H "-h"

#define CMD_SIZE 512
#define PARAM_SIZE 128

#define CMP(KEYWORD, BUF) strncmp(KEYWORD, BUF, sizeof(KEYWORD)) == 0

static char devcourse_mailing_list[] =
	"Austin Kim <austindh.kim@gmail.com>,"
	"mike Seo <mikeseohyungjin@gmail.com>,"
	"kkk kkk <rnjsenwls1@gmail.com>,"
	"Hello Stock <kyle.seungchul@gmail.com>,"
	"Paran Lee <p4ranlee@gmail.com>";

void do_func(char[]);

#define SEGFAULT "segfault"
#define NULL_DEREFERENCE "null_dereference"
#define WRITE_WEIRED_AREA "write_weired_area"
#define STACK_CORRUPTION "stack_corruption"
#define STACK_OVERFLOW_RECURSIVE "stack_overflow_recursive"
#define STACK_OVERFLOW_OVERSIZE "stack_overflow_oversize"
#define HEAP_OVERFLOW "heap_overflow"
#define MEM_LEAK "mem_leak"
#define DOUBLE_FREE "double_free"
#define LIST_CONCURRENCY "list_concurrency"
#define WRONG_FUNTION_POINTER "wrong_funtion_pointer"

void segfault();
void null_dereference();
void write_weired_area();
void stack_corruption();
void stack_overflow_recursive();
void stack_overflow_oversize();
void heap_overflow();
void mem_leak();
void double_free();
void list_concurrency();
void wrong_funtion_pointer();

#define BIG_NUM 16384 * 2

void make_coredump(char buf[])
{
	printf("Do %s\n", buf);
	if (CMP(SEGFAULT, buf))
	{
		segfault();
	}
	else if (CMP(NULL_DEREFERENCE, buf))
	{
		null_dereference();
	}
	else if (CMP(WRITE_WEIRED_AREA, buf))
	{
		write_weired_area();
	}
	else if (CMP(STACK_CORRUPTION, buf))
	{
		stack_corruption();
	}
	else if (CMP(STACK_OVERFLOW_RECURSIVE, buf))
	{
		stack_overflow_recursive();
	}
	else if (CMP(STACK_OVERFLOW_OVERSIZE, buf))
	{
		stack_overflow_oversize();
	}
	else if (CMP(HEAP_OVERFLOW, buf))
	{
		heap_overflow();
	}
	else if (CMP(MEM_LEAK, buf))
	{
		mem_leak();
	}
	else if (CMP(DOUBLE_FREE, buf))
	{
		double_free();
	}
	else if (CMP(LIST_CONCURRENCY, buf))
	{
		list_concurrency();
	}
	else if (CMP(WRONG_FUNTION_POINTER, buf))
	{
		wrong_funtion_pointer();
	}
}

void segfault()
{
	int *a = 1;
	*a = 1;
}

void null_dereference()
{
	struct a_list *tmp = NULL;
	tmp->str = "i am groot";
	tmp->val = 0;
}

void write_weired_area()
{
	int *p = malloc(0);
	*(p + 0xffffffff) = 12345678;
}

void stack_corruption()
{
	int a;
	memset(&a, 0xdeadbeef, 0xdeadbeef);
}

static int stack_overflow_cnt = 0;

void stack_overflow_recursive()
{
	char iamroot[] = "iamroot";
	int cnt = stack_overflow_cnt++;
	stack_overflow_recursive();
}

void stack_overflow_oversize()
{
	typedef struct fat_struct
	{
		char str[BIG_NUM];
	} fat;

	fat bigboy[BIG_NUM] = { { {'B', }, }, };
	fat biggirl[BIG_NUM] = { { {'G', }, } };
}

void heap_overflow()
{
	char *pp = malloc(BIG_NUM);
	memset(pp, 'X', BIG_NUM * BIG_NUM);
}

void mem_leak()
{
	int i, n = 0;
	char *pp[BIG_NUM];

	for (n = 0; n < BIG_NUM * BIG_NUM; n++)
	{
		pp[n] = malloc(sizeof(devcourse_mailing_list) * 4);
		if (pp[n] == NULL)
			break;
	}
	printf("malloc failure after %d MiB\n", n);

	for (i = 0; i < n; i++)
	{
		snprintf(pp[i],
			devcourse_mailing_list,
			devcourse_mailing_list,
			devcourse_mailing_list,
			devcourse_mailing_list,
			"%s%s%s%s");
	}
}

void double_free() {
	struct a_list *tmp;
	tmp = (struct a_list *)malloc(sizeof(struct a_list));

	free(tmp);

	free(tmp);
}

void append(struct a_list *ptr, const char *str, int val)
{
	struct a_list *tmp;
	tmp = (struct a_list *)malloc(sizeof(struct a_list));

	if (!tmp)
	{
		perror("malloc");
		exit(1);
	}

	tmp->str = str;
	tmp->val = val;
	list_add_tail(&(tmp->list), &(ptr->list));
}

void list_use_case()
{
	struct a_list blist;
	struct a_list *iter;

	INIT_LIST_HEAD(&blist.list);

	/* add item to list */
	append(&blist, "NM", 87501);
	append(&blist, "CA", 94041);
	append(&blist, "IL", 60561);

	/* iterates list */
	list_for_each_entry(iter, &blist.list, list)
	{
		printf("%s %d\n", iter->str, iter->val);
	}

	/* remove all items in the list */
	while (!list_empty(&blist.list))
	{
		iter = list_entry(blist.list.next, struct a_list, list);
		list_del(&iter->list);
		free(iter);
	}

	return 0;
}

#ifndef NUM_THREADS
#define NUM_THREADS 2
#endif

static atomic_int counter = 0;

static int max_iter = 1000;

void *pr_thrd(void *thr_id)
{
	long tid;
	tid = (long)thr_id;
	printf("thread %ld started incrementing ID - %lu\n", tid, thrd_current());

	for (int i = 0; i < max_iter; ++i)
	{
		counter += 1;
		usleep(2000);
	}

	return NULL;
}

void concurrency_use_case()
{
	thrd_t threads[NUM_THREADS];
	int rc;
	long t;

	for (t = 0; t < NUM_THREADS; t++)
	{
		rc = thrd_create(&threads[t], (thrd_start_t)pr_thrd, (void *)t);
		if (rc == thrd_error)
		{
			printf("ERORR; thrd_create() call failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for (t = 0; t < NUM_THREADS; t++)
	{
		thrd_join(threads[t], NULL);
	}
	printf("count = %d\n", counter);

	thrd_exit(EXIT_SUCCESS);
}

static struct a_list dirty_list;

void *list_concurrency_dirty_thrd(void *thr_id)
{
	long tid;
	tid = (long)thr_id;
	printf("thread %ld started incrementing ID - %lu\n", tid, thrd_current());

	for (int i = 0; i < max_iter; ++i)
	{
		counter += 1;

		append(&dirty_list, "austindh.kim@gmail.com", 1);
		append(&dirty_list, "mikeseohyungjin@gmail.com", 2);
		append(&dirty_list, "rnjsenwls1@gmail.com", 3);
		append(&dirty_list, "kyle.seungchul@gmail.com", 4);
		append(&dirty_list, "p4ranlee@gmail.com", 5);

		struct a_list *iter;
		while (!list_empty(&dirty_list.list))
		{
			iter = list_entry(dirty_list.list.next, struct a_list, list);
			list_del(&iter->list);
			free(iter);
		}
	}

	return NULL;
}

void list_concurrency()
{
	thrd_t threads[NUM_THREADS];
	int rc;
	long t;

	for (t = 0; t < NUM_THREADS; t++)
	{
		rc = thrd_create(&threads[t], (thrd_start_t)list_concurrency_dirty_thrd, (void *)t);
		if (rc == thrd_error)
		{
			printf("ERORR; thrd_create() call failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for (t = 0; t < NUM_THREADS; t++)
	{
		thrd_join(threads[t], NULL);
	}
	printf("count = %d\n", counter);

	thrd_exit(EXIT_SUCCESS);
}

void fun(int a)
{
	printf("Value of a is %d\n", a);
}

void wrong_funtion_pointer()
{
	int notfun;
	void (*fun_ptr)(int) = &fun;
	(*fun_ptr)(10);
	int (*notfun_ptr)(char*) = &notfun;
	(*notfun_ptr)('i am groot');
}

void ssu_show_limit(int rlim_type, char *rlim_name);
void self_ulimit_core_setup();
int self_sys_core_setup();

#define ssu_show(limit) ssu_show_limit(limit, #limit)

void ssu_show_limit(int rlim_type, char *rlim_name)
{
	struct rlimit rlim;
	char cur[11], max[11];

	// 리소스 한계치를 얻어옴
	getrlimit(rlim_type, &rlim);

	// 무한대인지 아닌지 구분
	if (rlim.rlim_cur == RLIM_INFINITY)
		strcpy(cur, "infinity");
	else
		sprintf(cur, "%10ld", rlim.rlim_cur);

	// 무한대인지 아닌지 구분
	if (rlim.rlim_max == RLIM_INFINITY)
		strcpy(max, "infinity");
	else
		sprintf(cur, "%10ld", rlim.rlim_cur);

	printf("%15s : %10s %10s\n", rlim_name, cur, max);
}

void self_ulimit_core_setup()
{
	struct rlimit l;
	l.rlim_cur = RLIM_INFINITY;
	l.rlim_max = RLIM_INFINITY;
	int res = setrlimit(RLIMIT_CORE, &l);
	if (res < 0)
	{
		perror("setrlimit");
		exit(EXIT_FAILURE);
	}

	printf("Core dump size limit set to unlimited.\n");
}

int self_sys_core_setup()
{
	int ret;
	int fd;

	fd = open("/proc/sys/kernel/core_pattern", O_WRONLY);
	if (!fd)
	{
		perror("open core pattern fail");
		exit(EXIT_FAILURE);
	}

	dprintf(fd, "%s/%s", CORE_PATH, "core-%e.%p.%h.%t");
	close(fd);

	fd = open("/proc/sys/kernel/core_pipe_limit", O_WRONLY);
	if (!fd)
	{
		perror("open core pipe limit fail");
		exit(EXIT_FAILURE);
	}

	dprintf(fd, "%d", 0);
	close(fd);
}

int main(int argc, char *argv[])
{
	pid_t cpid, w;
	int status;
	char cmd[CMD_SIZE];
	char param[PARAM_SIZE];

	self_sys_core_setup();

	do
	{
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (cpid == 0) /* Code executed by child */
		{
			printf("Child PID is %ld\n", (long)getpid());
			if (argc == 1)
			{
				fgets(param, PARAM_SIZE, stdin);
				fflush(stdin);

				printf("%s\n", param);
				snprintf(cmd, sizeof(cmd), "%s && %s %s", ULIMIT_CORE, CMD, param);
				printf("%s\n", cmd);
				system(cmd);
			}
			else if(CMP(argv[1], __H) || CMP(argv[1], __HELP))
			{
				printf(
					"LUDTM(Linux User Dump Test Module)"
					"\n"
					"Make each dump:"
					"\n"
					" echo TYEP_OF_CRASH | ./ludtm"
					"\n"
					"Make various dump:"
					"\n"
					" echo segfault | ./ludtm"
					"\n"
					" echo null_dereference | ./ludtm"
					"\n"
					" echo write_weired_area | ./ludtm"
					"\n"
					" echo stack_corruption | ./ludtm"
					"\n"
					" echo stack_overflow_recursive | ./ludtm"
					"\n"
					" echo stack_overflow_oversize | ./ludtm"
					"\n"
					" echo heap_overflow | ./ludtm"
					"\n"
					" echo mem_leak | ./ludtm"
					"\n"
					" echo double_free | ./ludtm"
					"\n"
					" echo list_concurrency | ./ludtm"
					"\n"
					" echo wrong_funtion_pointer | ./ludtm"
					"\n"
				);
				exit(EXIT_SUCCESS);
			}
			else
			{
				make_coredump(argv[1]);
			}

			pause(); /* Wait for signals */
			_exit(atoi(argv[1]));
		}
		else /* Code executed by parent */
		{
			do
			{
				w = waitpid(cpid, &status, WUNTRACED);
				if (w == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
				if (WIFEXITED(status))
				{
					printf("exited, status=%d\n", WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					char cmd[CMD_SIZE];
					printf("killed by signal %d\n", WTERMSIG(status));
					snprintf(cmd, sizeof(cmd), "ls -ahl %s/core*", CORE_PATH);
					system(cmd);
				}
				else if (WIFSTOPPED(status))
				{
					printf("stopped by signal %d\n", WSTOPSIG(status));
				}

			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	} while (0);

	exit(EXIT_SUCCESS);
}
