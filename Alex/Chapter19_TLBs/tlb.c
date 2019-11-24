#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

int main (int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage ./tlb <NUMPAGES> <NUMTRIALS>\n");
		return 1;
	}
	int numpages = atoi(argv[1]);
	int trials = atoi(argv[2]);
	struct timespec start, end, res;
	cpu_set_t set;
	int cpu = 0;
	//setting CPU-Affinity
        CPU_ZERO(&set);
        CPU_SET(cpu, &set);
        while (sched_setaffinity(getpid(), sizeof(set), &set) == 0) {
                cpu++;
		CPU_SET(cpu, &set);
        }
	//getting size of page:
	int pagesize = getpagesize();
	//how many ints fit in one int
	//index 0 is page 0, index jump is page 1
	int jump = pagesize / sizeof(int);
	//getting precision of clock_gettime()
	if(clock_getres(CLOCK_MONOTONIC_RAW, &res) != 0) {
		fprintf(stderr, "getres failed");
		return 1;
	}
	//creating array to test tlb initialized with 0
	//array should be loaded in tlb since it has been initialized.
	int *a = (int *) calloc(pagesize * numpages, sizeof(int));

	/*printing presicion of clock:
	unsigned long prec = res.tv_sec * 1000000000 + res.tv_nsec;
	printf("precision of clock is: %lu ns\n", prec);*/

	//measuring loop time:
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int j = 0; j < trials; j++) {
                for (int i = 0; i < numpages * jump; i += jump) {
                }
        }
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	unsigned long loop = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

	//start measuring:
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for (int j = 0; j < trials; j++) {
		for (int i = 0; i < numpages * jump; i += jump) {
			a[i] += 1;
		}
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	//end measuring
	unsigned long diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec - loop;
	unsigned long aver = (diff / numpages) / trials;
	printf("%d,%lu\n", numpages, aver);
	return 0;
}
