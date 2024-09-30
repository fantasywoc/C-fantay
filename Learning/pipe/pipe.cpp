#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        int pid;
        int fd[2];
        char r_buf[128] = {0};

        if ((pipe(fd)) == -1) {     //创建管道
                perror("pipe fail");
                exit(-1);
        }

        if ((pid = fork()) == -1) {     //创建进程
                perror("fork fail");
                exit(-1);
        }

        if (pid > 0) {      //父进程
                close(fd[0]);   //关闭读端
                write(fd[1], "hallo world!", strlen("hallo world!"));   //往管道里写
                close(fd[1]);   //关闭管道
        } else if (pid == 0) {
                close(fd[1]);   //关闭写端
                read(fd[0], r_buf, 128);    //读取管道中的数据
                printf("%s\n", r_buf);      //打印数据
                close(fd[0]);       //关闭管道
        }

        return 0;
}
