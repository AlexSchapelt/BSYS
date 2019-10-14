#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (void) { 
       	int fd = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	char *buf1 = "Hallo!";
	char *buf2 = "Moin!";
	int rc = fork();
        
	if(rc < 0) {
             fprintf(stderr, "fork failed\n");
             exit(1);
        } else if (rc == 0) {
             printf ("child: writes to the file\n");
	     write(fd, buf1, strlen(buf1)); 
        } else {
             printf("parent: writes to the file\n");
	     write(fd, buf2, strlen(buf2));
        }

        return 0;
}



