#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{

	int x=0, y=1, i=2, input, z;
	printf("Program to find Fibonacci Series");
	printf("Input: ");
	scanf("%d", &input);

	pid_t pid = fork();
	if (pid == 0)
	{
	    printf("Fibonacci Series up to %d: \n", input);
	    printf("%d ", y);
	    while (i <= input) 
	    {
	        i = i+1;
		z = x+y;
       		printf("%d ", z);
	        x=y;
	        y=z;
       		
	    }
	    printf("\nChild ends\n");
	 }
	 else 
	 {
        	printf("Parent is waiting for child to complete...\n");
	        waitpid(pid, NULL, 0);
        	printf("Parent ends\n");
	 }
	 return 0;
}
