//
// Created by 宋玉堂 on 2024/2/25.
//
//To know function，argument，what is system calls?
//Read chapter 1 p9-p20;
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char*argv[]){
    if(argc!=2){
        printf("Error,Example:sleep 3");
        exit(-1);
    }

    int num= atoi(argv[1]);

    if(num<0){
        printf("Error argument,please again!");
        exit(-1);
    }
    sleep(num);
    exit(0);
}
















































