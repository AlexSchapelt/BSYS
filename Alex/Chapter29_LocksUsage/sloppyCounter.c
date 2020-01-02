#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int numTs = 0;
int loops = 0;

typedef struct __counter_t {
	int global;
	pthread_mutex_t glock;
	int local[100/*numTs*/];
	pthread_mutex_t llock[100/*numTs*/];
	int threshold;
} counter_t;

typedef struct __args_t {
	counter_t *counter;
	int id;
} args_t;

void init(counter_t *c, int threshold) {
	c->threshold = threshold;
	c->global = 0;
	pthread_mutex_init(&c->glock, NULL);
	for (int i = 0; i < numTs; i++) {
		c->local[i] = 0;
		pthread_mutex_init(&c->llock[i], NULL);
	}
}

void update(counter_t *c, int threadID) {
	pthread_mutex_lock(&c->llock[threadID]);
	c->local[threadID]++;
	if (c->local[threadID] >= c->threshold) {
	        pthread_mutex_lock(&c->glock);
	        c->global += c->local[threadID];
	        pthread_mutex_unlock(&c->glock);
	        c->local[threadID] = 0;
        }
        pthread_mutex_unlock(&c->llock[threadID]);
}

int get(counter_t *c) {
	pthread_mutex_lock(&c->glock);
	int val = c->global;
	pthread_mutex_unlock(&c->glock);
	return val;
}

void *threads(void *arg) {
	args_t *args = (args_t *) arg;
        for(int i = 0; i < loops; ++i) {
                update(args->counter, args->id);
        }
        return NULL;
}

int main (int argc, char *argv[]) {
        if (argc != 3) {
                return -1;
        }
        loops = 1000;//atoi(argv[1]);
        numTs = 40;//atoi(argv[2]);
        pthread_t thread[numTs];
        struct timespec start, end;
        counter_t counter;
        init(&counter, 100);
	args_t tArgs[numTs];
	for(int i = 0; i < numTs; ++i) {
		tArgs[i].counter = &counter;
		tArgs[i].id = i;
	}

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for(int i = 0; i < numTs; ++i) {
                assert(pthread_create(&thread[i], NULL, threads, &tArgs[i]) == 0);
        }
        for(int i = 0; i < numTs; ++i) {
                assert(pthread_join(thread[i], NULL) == 0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        unsigned long time = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
        printf("counter = %d\ntook: %lu ns\n", get(&counter), time);
        return 0;
}

