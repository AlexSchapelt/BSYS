#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int counter = 0;
int loops = 0;

void *incr(void *l) {
	for(int i = 0; i < loops; ++i) {
		assert(pthread_mutex_lock(l) == 0);
		counter++;
		assert(pthread_mutex_unlock(l) == 0);
	}
	return NULL;
}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		return -1;
	}
	loops = atoi(argv[1]);
	int threads = atoi(argv[2]);

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_t thread[threads];
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for(int i = 0; i < threads; ++i) {
		assert(pthread_create(&thread[i], NULL, incr, &lock) == 0);
	}
	for (int i = 0; i < loops; ++i) {
                assert(pthread_mutex_lock(&lock) == 0);
                counter++;
                assert(pthread_mutex_unlock(&lock) == 0);

	}
	for(int i = 0; i < threads; ++i) {
                assert(pthread_join(thread[i], NULL) == 0);
        }
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	unsigned long time = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
	printf("counter = %d\ntook: %lu ns\n", counter, time);
	return 0;
}
