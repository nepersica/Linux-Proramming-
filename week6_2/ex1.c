#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
     
    pid_t childPid;
    int i;
     
    childPid = fork();
     
    if(childPid > 0) 
    {  // 부모 프로세스
        printf("Parent PID : %ld, pid : %d\n",(long)getpid(), childPid);
        sleep(2);
        printf("Terminate Parent Process\n");
        exit(0);
    }
    else if(childPid == 0)
    {  // 자식 코드
        printf("Start Child Process\n");
         
        for(i=0;i<5;i++) {
            printf("Child PID : %ld Parent PID : %ld\n",(long)getpid(), (long)getppid());
            sleep(1);
        }
         
        printf("Terminate Child Process\n");
        exit(0);
    }
    else {  // fork 실패
        perror("Fail to fork\n");
        return -1;
    }
     
    return 0;
}
