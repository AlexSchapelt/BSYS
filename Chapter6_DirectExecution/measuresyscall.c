#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct timespec start;
	struct timespec end;
	if (argc != 2) {
		fprintf(stderr, "usage measuresyscall numberOfCalls\n");
		exit(1);
	}
	int count = atoi(argv[1]);
	//schould be implemented for error handling, but could effect result:
	/*if(clock_gettime(CLOCK_REALTIME, &start); != 0) {
		fprintf(stderr, "gettimeofday failed\n");
		exit(1);
	}*/
	clock_gettime(CLOCK_REALTIME, &start);
	//for higher accuraccy, non-forloop solutions would be better
	//tiping  read() a couple times for example
	for (int i = 0; i < count; ++i) {
		read(0, NULL, 0);
	}

	//schould be implemented for error handling, but could effect result:
	/*if (clock_gettime(CLOCK_REALTIME, &end); != 0) {
		fprintf(stderr, "gettimeofday failed\n");
		exit(1);
	}*/
	clock_gettime(CLOCK_REALTIME, &end);
	long long diff = (long) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec) - (start.tv_nsec));
	printf("time token: %lld\ntime per System Call: %f\n", diff, (diff / (double) count+2));
	exit(0);
}
