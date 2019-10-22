#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
	int rc = fork();
	if (rc < 0) {

	} else if (rc == 0) {
		close(1);
		int err = printf("testing closed stdout\n");
		exit(0);
	} else {
		wait(NULL);
		printf("child ran\n");
	}
	return 0;
}
