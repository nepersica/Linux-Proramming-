#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct flock lock;
	int fd;
	char command[100];
	if( (fd = open(argv[1], O_RDWR))==-1 )  
	{
		perror(argv[1]);
		exit(1);
	}

	lock.l_type=F_WRLCK;
	lock.l_whence=0;
	lock.l_start = 0L;
	lock.l_len = 0L;

	if( fcntl(fd, F_SETLK, &lock) == -1)  
	{
		if (errno == EACCES)  
		{
			printf("%s busy -- try later\n", argv[1]);
			exit(2);
		}
		else 
		{
			perror(argv[1]);
			exit(3);
		}
	}
	sprintf(command, "vi %s\n", argv[1]);
	system(command);
	lock.l_type = F_UNLCK;  
	fcntl(fd, F_SETLK, &lock);
	close(fd);

	printf("Lock the file");

	exit(0);
}
