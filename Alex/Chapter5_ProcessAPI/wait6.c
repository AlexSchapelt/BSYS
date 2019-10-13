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
		int w = waitpid(-1, NULL, 0);
		printf("Child's (PID:%d) wait returned: %d\n", (int) getpid(), w);
	} else {
		//waitpid is usefull, if a process has more children and
		//it matters which one the parrent has to wait.
		int w = waitpid(-1, NULL, 0);
		printf("Parre's (PID:%d) wait returned: %d\n", (int) getpid(), w);
	}
	exit(0);
}
