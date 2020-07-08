#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

void printing(int argc, char *argv[])
{
	DIR *dp;
	char *dir;
	struct dirent *d;
	struct stat buf;
	int success=0;

	if( argc==1 )
	{
		dir=".";
	}
	else dir=argv[1];

	if( (dp=opendir(dir))==NULL )
	{
		perror(dir);
		exit(1);
	}
	int count=0;
	printf("< Normal files locate in working directory >\n");
	while( (d=readdir(dp))!=NULL )
	{
		if( d->d_type==8 )
		{
			printf("%s \t", d->d_name);
			count++;
			if( count==2)
			{
				printf("\n");
				count=0;
			}
			if( chmod(d->d_name, 0775)!=0 )
			{
				success=-1;	
			}

		}
	}
	printf("\n");
	if( success==-1 )
	{
		printf("Fail to change the mode");
	}
	else
	{
		printf("Sucess to change the mode");
	}

	printf("\n");
	closedir(dp);
	exit(0);
}
