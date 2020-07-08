#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>

static jmp_buf env;
static void sigcatch(int);
void mysleep(int);

int main(int argc, char *argv[])
{
	int atoi(), unslept;
        void mysleep();

	signal(SIGINT, SIG_IGN);
	mysleep(atoi(argv[1]));
	printf("The %d second time out\n", atoi(argv[1]));
}

void mysleep(int seconds)
{
	void(*astat) ();
	int unslept = seconds;

	astat = signal(SIGALRM, sigcatch);
	if(setjmp(env)==0)
	{
		alarm(seconds);
		pause();
	}
	unslept = alarm(0);
	signal(SIGALRM, astat);
}

static void sigcatch(int sig)
{
	longjmp(env, 1);
}
	
