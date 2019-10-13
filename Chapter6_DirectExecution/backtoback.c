#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

int main (void) {
	struct timeval tv1;
	struct timeval tv2;
	struct timeval begin;
	struct timeval end;
	long diff = 0;
	gettimeofday(&begin, NULL);
	for (int i = 0; i < 1000; ++i) {
		gettimeofday(&tv1, NULL);
		gettimeofday(&tv2, NULL);
		//diff = (long) (tv2.tv_usec - tv1.tv_usec);
		//printf("Round %d time ellapsed: %ld\n", i, diff);
	}
	gettimeofday(&end, NULL);
	diff = (long) (end.tv_usec - begin.tv_usec);
	printf("Overall time ellapsed: %ld\n", diff);
	exit(0);
}
