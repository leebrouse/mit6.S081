#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// pipe, fork, write, read, getpid
int main(int argc, char const *argv[])
{

    if (argc >= 2)
    {
        printf("Error,Example:pingpong\n");
        exit(-1);
    }

    int p[2];
    if (pipe(p) == -1)
    {
        printf("pipe error\n");
        exit(-1);
    }

    int pid = fork();
    char buffer[1] = "a";

    if (pid < 0)
    {
        printf("fork failed\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        // child process
        read(p[0], buffer, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], buffer, 1);
    }
    else
    {
        // father process
        write(p[1], buffer, 1);
        read(p[0], buffer, 1);
        printf("%d: received pong\n", getpid());
    }  

    exit(0);
    return 0;
}
