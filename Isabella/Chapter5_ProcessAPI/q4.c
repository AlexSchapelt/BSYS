#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
        int rc = fork();
        if(rc < 0) { 
           fprintf(stderr, "fork failed\n");
           exit(1);
        } else if (rc == 0) {
	const char *list = "ls"; 
        char *p[2]; //pointer
	p[0] = strdup("/bin/ls"); //Aufruf des programmes
	p[1] = NULL; //end of file
	
	//execvp(p[0], p); 	 //Auflistung
	//execv(p[0], p);		//Auflistung
	//execl("/bin/ls", list, (char *) NULL);
	//execlp("/bin/ls", list, (char *) NULL);
	execle("/bin/ls", list, (char *) NULL, getenv("environ"));
 	//execvpe(p[0], list, (char *) NULL, getenv("environ"));

	fprintf(stderr, "this shouldn't print out\n");
        } else { }
        return 0;
}


