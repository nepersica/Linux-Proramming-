#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* perm(mode_t mode)
{
        int i;
        static char perms[10] = "---------";

        for( i=0; i<3; i++ ) {
        if( mode & (S_IRUSR >> i*3) )
                perms[i*3] = 'r';
        if( mode & (S_IWUSR >> i*3) )
                perms[i*3+1] = 'w';
        if( mode & (S_IXUSR >> i*3) )
                perms[i*3+2] = 'x';
        }
        return(perms);
}

char type(mode_t mode)
{
        if( S_ISREG(mode) )
                return('-');
        if( S_ISDIR(mode) )
                return('d');
        if( S_ISCHR(mode) )
                return('c');
        if( S_ISBLK(mode) )
                return('b');
        if( S_ISLNK(mode) )
                return('l');
        if( S_ISFIFO(mode) )
                return('p');
        if( S_ISSOCK(mode) )
                return('s');
}

	
void printStat(char *pathname, char *file, struct stat *st)
{
	printf("%5d ", st->st_blocks);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3d ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
	printf("%9d ", st->st_size);
	printf("%.12s ", ctime(&st->st_mtime)+4);
	printf("%s", file);
}

int main(int argc, char **argv)
{
        DIR *dp;
        char *dir;
        struct stat st;
        struct dirent *d;
        char path[BUFSIZ+1];

        if( argc==1 )
                dir = ".";
        else dir = argv[1];

        if( (dp=opendir(dir))==NULL ) // 디렉토리 열기
                perror(dir);

        while( (d = readdir(dp))!=NULL ) { // 디렉토리의 각 파일에 대해
                sprintf(path, "%s/%s", dir, d->d_name); // 파일경로명 만들기
                if( lstat(path, &st) < 0 ) // 파일 상태 정보 가져오기
                        perror(path);
                printStat(path, d->d_name, &st); // 상태 정보 출력
                putchar('\n');
        }
        closedir(dp);

	int nResult=mkdir( "d", 0777 );
	if( nResult==-1 )
	{
		printf("We already have directory d\n");
	}
	else
	{
		printf("There is no direcotry d. Succeed to make it.\n");
	}
	

        exit(0);
}

