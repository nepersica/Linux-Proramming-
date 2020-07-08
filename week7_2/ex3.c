#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdlib.h>

int main() 
{ 
	int fd1[2], fd2[2]; 
	pid_t pid; 
	pipe(fd1); 
	pipe(fd2); 
	pid=fork(); 
	if(pid) 
	{ 
		int status, sum, i; 
		close(fd1[1]); 
		close(fd2[0]); 
		for(sum=0,i=1;i<=250;i++) 
			sum+=i;
	        printf("Sum of 1~250 at First Child process = %d\n", sum); 
		write(fd2[1], &sum, sizeof(sum)); 
		waitpid(pid, &status, 0); 
		read(fd1[0], &sum, sizeof(sum)); 
		printf("Final sum at Seond Child process = %d\n", sum); 
	}
       	else
       	{ 
		int sum1, i, sum2, sum;
	       	close(fd1[0]); 
		close(fd2[1]); 
		read(fd2[0], &sum1, sizeof(sum)); 
		for(i=251;i<=500;i++) 
			sum2+=i; 
	        printf("Sum of 250~500 at Parent process = %d\n", sum2); 
		sum = sum1+sum2;
		write(fd1[1], &sum, sizeof(sum));
	       	exit(0); 
	} 
}

