#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
	int fd = open("./open1.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	int rc = fork();
	if (rc < 0) {
		printf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("Child writing in file\n");
		write (fd, strdup("Child process wrote here\n"), 25);
	} else {
		printf("Parre writing in file\n");
		write (fd, strdup("Parre process wrote here\n"), 25);
	}
	close(fd);
	exit(0);
}
