#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int x = 100;
	int rc = fork();
	if(rc < 0) {
		printf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0) {
		printf("Child process (PID:%d): x=%d\n", (int) getpid(), x);
		x =  101;
		printf("Child process (PID:%d): x=%d\n", (int) getpid(), x);
	} else {
		printf("Parre process (PID:%d): x=%d\n", (int) getpid(), x);
                x =  102;
                printf("Parre process (PID:%d): x=%d\n", (int) getpid(), x);
	}
	return 0;
}
