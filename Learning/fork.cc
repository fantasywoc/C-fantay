#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // 调用 fork()
    pid = fork();

    // 检查 fork() 的返回值
    if (pid == -1) {
        // fork() 失败
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子进程
        printf("This is the child process. PID = %d\n", getpid());
        // 子进程可以执行一些任务...
        // 然后退出
        exit(0); // 子进程退出
    } else {
        // 父进程
        int status;
        printf("This is the parent process. Child PID = %d\n", pid);

        // 父进程可以继续执行其他任务...

        // 等待子进程结束
        waitpid(pid, &status, 0);

        // 检查子进程的退出状态
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }

        // 父进程继续执行或退出
        exit(0);
    }

    // 注意：这个 return 语句实际上只会被父进程执行，因为子进程已经通过 exit() 退出了。
    // 但由于父进程也会很快通过 exit(0) 退出，所以这个 return 语句在大多数情况下不会被执行到。
    return 0;
}