#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	struct timeval start;
	struct timeval end;
	if (argc != 2) {
		fprintf(stderr, "usage measuresyscall numberOfCalls\n");
		exit(1);
	}
	int count = atoi(argv[1]);
	//schould be implemented for error handling, but could effect result:
	/*if(gettimeofday(&start, NULL) != 0) {
		fprintf(stderr, "gettimeofday failed\n");
		exit(1);
	}*/
	gettimeofday(&start, NULL);
	//for higher accuraccy, non-forloop solutions would be better
	//tiping  read() a couple times for example
	for (int i = 0; i < count; ++i) {
		read(0, NULL, 0);
	}

	//schould be implemented for error handling, but could effect result:
	/*if (gettimeofday(&end, NULL) != 0) {
		fprintf(stderr, "gettimeofday failed\n");
		exit(1);
	}*/
	gettimeofday(&end, NULL);
	long diff = (long) ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec) - (start.tv_usec));
	printf("time token: %ld\ntime per System Call: %f\n", diff, (diff / (double) count));
	exit(0);
}
