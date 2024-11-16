#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char*argv[]){
    if(argc!=2){
        printf("Error,Example:sleep 3\n");
        exit(-1);
    }

    int num= atoi(argv[1]);

    if(num<0){
        printf("Error argument,please again!\n");
        exit(-1);
    }
    sleep(num);
    exit(0);
}
















































