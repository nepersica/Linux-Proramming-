#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main ()
{
	pid_t pid;

	pid = fork ();
	
	if (pid > 0) {
		sleep(20);
	}
	else {
		exit (0);
	}
	return 0;
}
