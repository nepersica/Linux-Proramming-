#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 1024 
 
int main(){
    int fd1, fd2;        //파일 디스크립터
    char inmsg[MAXLINE];    //메시지 버퍼
 
    fd1 = open("./chatfifo01", O_RDONLY); //파이프 열기
    fd2 = open("./chatfifo02", O_WRONLY);
    if(fd1 == -1 || fd2 == -1) {
        perror("open\n");
        exit(1);
    }
    printf("[CLIENT] CLIENT OPEARTING\n");
    while(1) {
        printf("[SEUNG AH] : ");
        fgets(inmsg, MAXLINE, stdin);        // 명령어 입력
        write(fd2, inmsg, strlen(inmsg)+1);    // 파이프에 쓰기
 
        if(strstr(inmsg, "exit") != NULL)    // exit입력하면
            break;                //프로그램 종료
 
        read(fd1, inmsg, MAXLINE);        // 파이프에서 결과 읽어옴
        printf("[from SERVER] :\n%s\n", inmsg);// 결과 출력
    }
    close(fd1); //파이프 닫기
    close(fd2);
}

