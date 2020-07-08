#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd, fflags, n;
	char linebuf[256];
	char stdnum[256];
	if( (fd=open("/dev/tty", O_RDONLY|O_NDELAY))==-1 )
	{
		perror("open");
		exit(1);
	}

	printf("Enter your First name within 5 seconds.\n");
	sleep( 5 );
	read(fd, linebuf, 256);
	if( read(fd,linebuf,256)==-1 )
	{
		printf("Input time over. Program closed\n");
		exit(1);
	}

	fflags = fcntl(fd, F_GETFL,0);
	fflags &= ~O_NDELAY;
	fcntl(fd, F_SETFL, fflags);

	switch (linebuf)
	{
		case Seungah:
			printf("Your student number is 201714083");
			break;
		case Minsang:
			printf("Your student number is 201400000")
			break;
	default:
		break;
	}
}
			
