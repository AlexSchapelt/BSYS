#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <sys/wait.h>

int cmpfunc(const void *p, const void *q)
{
    return (*(int*) p - *(int*) q);
}


int main(void) {
	struct timespec start, end;
	cpu_set_t set;
	int count = 100;
	int fdparrent[2], fdchild[2];
	unsigned long sec[count], nsec[count];

	//setting CPU-Affinity
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	if (sched_setaffinity(getpid(), sizeof(set), &set) != 0) {
		fprintf(stderr, "setaffinity failed with error %d\n", errno);
		return -1;
	}

	//init pipes
	if (pipe(fdparrent) != 0) {
		fprintf(stderr, "pipe failed\n");
		return 1;
	}
	if (pipe(fdchild) != 0) {
		fprintf(stderr, "pipe failed\n");
		return 1;
	}

	char buf;
	char *send = "a";
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		return 1;
	} else if (rc == 0) {
		//child:
		sched_yield();
		close(fdparrent[0]);
		close(fdchild[1]);
		for(int i = 0; i < count; ++i) {
			clock_gettime(CLOCK_MONOTONIC_RAW, &start);
			write(fdparrent[1], send, 1);
			read(fdchild[0], &buf, 1);
			clock_gettime(CLOCK_MONOTONIC_RAW, &end);
			sec[i] = end.tv_sec - start.tv_sec;
			nsec[i] = end.tv_nsec - start.tv_nsec;
		}
		unsigned long diff[count];
		unsigned long sum = 0;
		for(int i = 0; i < count; ++i) {
			diff[i] = sec[i] * 1000000000 + nsec[i] - 400;
		}
		qsort(diff, count, sizeof(unsigned long), cmpfunc);
		for(int i = 2; i < count-4; ++i) {
			sum += diff[i] / 2;
			printf("%lu\n", diff[i] / 2);
		}
		printf("Context switch takes %lu ns\n", sum/(count-4));
		exit(0);
	} else {
		//parrent:
		close(fdparrent[1]);
		close(fdchild[0]);
		for (int i = 0; i < count; ++i) {
			read(fdparrent[0], &buf, 1);
			write(fdchild[1], send, 1);
		}
		wait(NULL);
		exit(0);
	}
	close(fdparrent[0]);
	close(fdparrent[1]);
	close(fdchild[0]);
	close(fdchild[1]);
	return 0;
}
