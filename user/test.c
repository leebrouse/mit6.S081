#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define MSGIZE 16
// echo hello | xargs echo bye
// bye hello
int main(int argc, char *argv[])
{
    // Q1:怎么获取前一个命令的标准化输出（当前命令的标准化输入）？ 
    char buf[MSGIZE];
    read(0, buf, MSGIZE); // 0/1/2 standard input/output/error
    //printf("获取当前标准化输入:%s\n", buf);

    // Q2:如何获取到自己的命令行参数？
    // init
    char *xargv[MAXARG];
    int xargc = 0;

    // 构筑一个新命令。
    for (int i = 0; i < argc; i++)
    {
        xargv[xargc] = argv[i];
        xargc++;
    }

    char *p = buf;
    for (int i = 0; i < MSGIZE; i++)
    {
        if (buf[i] == '\n')
        {
            int pid = fork();
            if (pid > 0)
            {
                p = &buf[i + 1];
                wait(0);
            }
            else
            {
                // Q3：如何使用exec去执行命令？
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;

                exec(xargv[0], xargv); // 在文档中有说：only returns if error.则若返回应该有错退出exit(1),0表正常退出，1表错误退出。
                exit(1);
            }
        }
    }
    wait(0);
    exit(0);
}
