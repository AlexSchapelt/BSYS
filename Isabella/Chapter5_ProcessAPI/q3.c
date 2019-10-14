#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
        printf("hello world (pid:%d)\n", (int) getpid());
        int rc = fork();
        if(rc < 0) {	//fork failed
                fprintf(stderr, "fork failed\n");
                exit(1);
        } else if (rc == 0) { // child (new process)
        printf ("hello (pid:%d)\n", (int) getpid());
        } else {
	sleep(1);
        printf("goodybe (pid:%d)\n", (int) getpid());
        }
        return 0;
}



