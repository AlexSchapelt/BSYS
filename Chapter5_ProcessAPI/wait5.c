#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		int w = wait(NULL);
		printf("Child's (PID:%d) wait returned: %d\n", (int) getpid(), w);
	} else {
		int w = wait(NULL);
		printf("Parre's (PID:%d) wait returned: %d\n", (int) getpid(), w);
	}
	exit(0);
}
