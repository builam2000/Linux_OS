/*
description:
	using fork()
	child process write to file ( passed via argument)
	parent call child process via binary file using system function
	parent check status child process return and print string "ok" or "fail" depend 
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    if(argc != 2)
    {
        printf("Wrong when passing argument, try again!!\n");
        return -1;
    }
    
    pid = fork();
    if(pid < 0)
    {
        perror("Error:");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        printf("Enter child process");
        execl("./child","./child",argv[1],(char *)NULL);
        perror("Error while execl\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Parent process:");
        wait(&status);
        printf("status : %s\n" , (status == 0) ? "ok" : "fail");
    }
}