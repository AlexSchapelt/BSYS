#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		printf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		printf("hello\n");
	} else {
		sleep(1);
		printf("goodbye\n");
	}
	exit(0);
}
