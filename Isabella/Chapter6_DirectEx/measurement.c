
//return 0 for success
//return -1 for failure
//(clockid_t clock_id, struct timespec *tp)
//return the current value tp for the specified clock, clock_id
//hi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

int main(int args, char *argv[]){

	int result;
	struct timespec start, end;
	

	if(clock_gettime(CLOCK_REALTIME, &start) == -1) {
		perror("clock: failure");
		exit(EXIT_FAILURE);
	}


	if(clock_gettime(CLOCK_REALTIME, &end) == -1) {
                perror("clock: failure");
                exit(EXIT_FAILURE);
        }

	for(int i = 0; i < 10000; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		clock_gettime(CLOCK_REALTIME, &end);
	}

	result = (end.tv_nsec - start.tv_nsec);
	printf("time: %d\n", result);
	return (EXIT_SUCCESS);

     return 0;
}
