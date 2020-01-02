#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

int loops = 0;

typedef struct __counter_t {
   int value;
   pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
   c->value =0;
   assert(pthread_mutex_init(&c->lock, NULL) == 0);
}
void increment(counter_t *c) {
    assert(pthread_mutex_lock(&c->lock) == 0);
    c->value++;
    assert(pthread_mutex_unlock(&c->lock) == 0);
}

void *threads(void *arg) {
	for(int i = 0; i < loops; ++i) {
		increment(arg);
	}
	return NULL;
}

int main (int argc, char *argv[]) {
        if (argc != 3) {
                return -1;
        }
        loops = atoi(argv[1]);
        int numTs = atoi(argv[2]);
        pthread_t thread[numTs];
        struct timespec start, end;
	counter_t counter;
	init(&counter);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for(int i = 0; i < numTs; ++i) {
                assert(pthread_create(&thread[i], NULL, threads, &counter) == 0);
        }
        for(int i = 0; i < numTs; ++i) {
                assert(pthread_join(thread[i], NULL) == 0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        unsigned long time = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
        printf("counter = %d\ntook: %lu ns\n", counter.value, time);
        return 0;
}
