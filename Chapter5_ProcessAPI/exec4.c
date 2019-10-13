#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed");
		exit(1);
	} else if (rc == 0) {
		const char *ls = "ls";
		char *lsargs[2];
		lsargs[0] = strdup("/bin/ls");
		lsargs[1] = NULL;
		//execl("/bin/ls", ls, (char *) NULL);
		//execlp("/bin/ls", ls, (char *) NULL);
		//execle("/bin/ls", ls, (char *) NULL, getenv("environ"));
		//execv(lsargs[0], lsargs);
		//execvp(lsargs[0], lsargs);
		execvpe(lsargs[0], lsargs, getenv("environ"));
		fprintf(stderr, "ls failed with error: %d\n", errno);
	} else { }
	exit(0);
}
