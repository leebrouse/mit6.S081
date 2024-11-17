#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define MSGSIZE 36
// #define ONE '1'
// #define  ZERO '0'

enum sta
{
    ONE = '1',
    ZERO = '0'
};

void prime(int pipe_read, int pipe_write)
{
    char buf[MSGSIZE];
    read(pipe_read, buf, MSGSIZE);
    int val = 0;
    for (int i = 0; i < MSGSIZE; i++)
    {
        if (buf[i] == ONE)
        {
            val = i;
            break;
        }
    }

    if (val == 0)
    {
        exit(0);
    }

    printf("prime %d\n", val);
    buf[val] = ZERO;

    for (int i = 0; i < MSGSIZE; i++)
    {
        if (i % val == 0)
        {
            buf[i] = ZERO;
        }
    }

    int pid = fork();
    if (pid < 0)
    {
        fprintf(2, "Error create process failed\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        prime(pipe_read, pipe_write);
        wait(0);
    }
    else
    {
        write(pipe_write, buf, MSGSIZE);
        wait(0);
    }
}

int main(int argc, char *argv[])
{
    int p[2];
    if (pipe(p) == -1)
    {
        fprintf(2, "Error When call the pipe\n");
        exit(-1);
    }

    int pid = fork();
    char nums[MSGSIZE];
    for (int i = 0; i < MSGSIZE; i++)
    {
        nums[i] = ONE;
    }

    if (pid < 0)
    {
        fprintf(2, "Error create process failed\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        prime(p[0], p[1]);
        wait(0);
    }
    else
    {
        nums[0] = ZERO;
        nums[1] = ZERO;
        write(p[1], nums, MSGSIZE);
        wait(0);
    }

    exit(0);
}
