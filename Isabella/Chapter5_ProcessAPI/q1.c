#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	printf("hello world (pid:%d)\n", (int) getpid());
	int x = 100;
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) { // child (new process)
	printf ("hello, I am a child (pid:%d) and have the value %d\n", (int) getpid(), x*100);
	} else {
	printf("hello, I am parent of %d (pid:%d) and have the value %d\n",
		rc, (int) getpid(), x+4);
	}
	return 0;
}

