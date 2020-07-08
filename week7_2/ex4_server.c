#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 1024
 
int main(){
    
    int fd1, fd2, ex_fd;            // 파일 디스크립터
    char msg[MAXLINE];            // 메시지 버퍼
    int status;                // 프로세스 상태
    
    printf("[SERVER] SERVER INIT\n");
    printf("[SERVER] PIPE_1 INIT\n");    // 파이프 1 생성

    if(mkfifo("./chatfifo01", 0666) == -1) {
        perror("mkfifo_1\n");
        exit(1);
    }
    printf("[SERVER] PIPE_2 INIT\n");    // 파이프 2 생성

    if(mkfifo("./chatfifo02", 0666) == -1) {
        perror("mkfifo_2\n");
        exit(2);
    }

    printf("[SERVER] PIPE_1, PIPE_2 OPEN\n");        // 파이프 1,2 열기
    fd1 = open("./chatfifo01", O_WRONLY);
    fd2 = open("./chatfifo02", O_RDONLY);

    if(fd1 == -1 || fd2 == -1) {
        perror("open\n");
        exit(3);
    }

    printf("[SERVER] CLIENT ACCESS THE PROGRAM\n");    // 클라이언트 접속 알림
    while(1){
        memset(msg, '\0', MAXLINE);        // 버퍼 초기화
        read(fd2, msg, MAXLINE);        // 파이프에서 쉘 명령어 읽어서 버퍼에 저장
        if(strstr(msg, "exit") != NULL)        // exit를 입력하면 프로그램 종료
            break;
 
        //쉘 명령어 사용해서 나온 결과 저장하기 위한 파일
        ex_fd = open("cmd_data", O_CREAT| O_TRUNC| O_WRONLY, 0666);
        dup2(ex_fd, 1); // 출력 재지정
        close(ex_fd);    // 파일닫음
        system(msg);    // 입력받은 쉘 명령어 실행 (fork,exec,wait)
        
        //결과 가져와서 버퍼에 씀
        if( 0 < ( ex_fd = open("cmd_data", O_RDONLY, 0600)))
        {
            read(ex_fd, msg, MAXLINE);
            close(ex_fd);
        }
        //파이프에 버퍼내용 넣어줌
        write(fd1, msg, strlen(msg)+1);
    }
    printf("[SERVER] PIPE CLOSE\n");
    close(fd1); // 파이프 닫기
    close(fd2);
    printf("[SERVER] PIPE DESTROYED\n");
    unlink("chatfifo01"); // 파이프 제거
    unlink("chatfifo02");
    printf("[SERVER] SERVER EXIT\n"); //프로그램 종료
}

