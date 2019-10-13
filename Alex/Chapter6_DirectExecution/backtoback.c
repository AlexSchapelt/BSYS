#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main (void) {
	struct timespec ts1, ts2, start, end;
	long long diff = 0;
	clock_gettime(CLOCK_REALTIME, &start);
	for (int i = 0; i < 1000; ++i) {
		clock_gettime(CLOCK_REALTIME, &ts1);
		clock_gettime(CLOCK_REALTIME, &ts2);
		//diff = ts2.tv_nsec - ts1.tv_nsec;
		//printf("Round %d time elapsed: %lld\n", i, diff);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	diff = end.tv_nsec - start.tv_nsec;
	printf("Overall time elapsed: %lld\n", diff);
	exit(0);
}
