#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for(int i = 0; i < 100; ++i) {
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	unsigned long diff = ((end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec);
	printf("gettime took: %lu\n", diff / 100);
	return 0;
}
