#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {
	struct timespec start, end;
	cpu_set_t set;
	int count = 100;
	int fdparrent[2], fdchild[2];
	unsigned long sec[count], nsec[count];

	//setting CPU-Affinity
	CPU_ZERO(&set);
	CPU_SET(2, &set);
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

	int rc = fork();
	char buf;
	char *send = "a";
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		return 1;
	} else if (rc == 0) {
		//child:
		for(int i = 0; i < count; ++i) {
			clock_gettime(CLOCK_REALTIME, &start);
			write(fdparrent[1], send, 1);
			read(fdchild[0], &buf, 1);
			clock_gettime(CLOCK_REALTIME, &end);
			sec[i] = end.tv_sec - start.tv_sec;
			nsec[i] = end.tv_nsec - start.tv_nsec;
		}
		unsigned long diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
		unsigned long sum = 0;
		for(int i = 0; i < count; ++i) {
			diff = sec[i] * 1000000000 + nsec[i];
			sum += diff;
			printf("Switch %d took %luns\n", (i + 1), diff/2);
		}
		printf("Context switch took %luns\n", sum/(count*2));
	} else {
		//parrent:
		for (int i = 0; i < count; ++i) {
			read(fdparrent[0], &buf, 1);
			write(fdchild[1], send, 1);
		}
	}
	close(fdparrent[0]);
	close(fdparrent[1]);
	close(fdchild[0]);
	close(fdchild[1]);
	return 0;
}
