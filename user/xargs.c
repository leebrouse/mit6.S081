#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

void ExecuteXargs(char *argv[],char* args[MAXARG]){
    int p[2];
    if (pipe(p)==-1)
    {
        fprintf(2,"error when call pipe\n");
        exit(-1);
    }

    int pid=fork();
    if (pid<0)
    {
        fprintf(2,"error when call fork\n");
    }else if (pid==0){
        //child process
        close(p[0]);
        close(p[1]);
        exec(argv[1],args);

        exit(-1);
    }else{
        //parent process    
        wait(0);
    }
}

int main(int argc, char *argv[])
{
     if (argc < 3)
     {
        printf("Xargs requires at least 3 args\n");
        exit(-1);
     }

    char buffer[512];
    char *args[MAXARG];
    args[0]=argv[1];
    while (1)
    {
        gets(buffer,512);
        if (buffer[0]=='\0')
        {
            break;
        }

        buffer[strlen(buffer)-1]='\0';

        for (int i = 2; i < argc; i++)
        {
            args[i-1]=argv[i];
        }

        args[argc-1]=buffer;
        args[argc]=0;

        ExecuteXargs(argv,args);
    }
    exit(0);
}
