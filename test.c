#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int p[2]; // 用于保存读写文件描述符
    if (pipe(p) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork(); // 创建子进程

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) { // 子进程
        close(p[1]); // 关闭写端
        char buffer[100];
        read(p[0], buffer, sizeof(buffer)); // 从管道读取
        printf("Child process received: %s\n", buffer);
        close(p[0]); // 关闭读端
    } else { // 父进程
        close(p[0]); // 关闭读端
        char message[] = "Hello from parent process!";
        write(p[1], message, strlen(message) + 1); // 写入管道
        close(p[1]); // 关闭写端
    }

    return 0;
}
