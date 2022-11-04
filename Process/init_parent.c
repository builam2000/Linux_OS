#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
    pid_t id;
    id = fork();
    if(id<0){
        perror("Error:");
        exit(EXIT_FAILURE);
    }
    if(id == 0)
    {
        printf("Enter child process!\n");
        sleep(5);
        printf("Child Process ID: %d\n",getpid());
        printf("Parent id: %d \n",getppid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("In parent: \n");
        printf("Child Process ID in parent: %d\n",id);
        printf("Parent id in parent: %d \n",getpid());
        printf("Parent process will be terminated\n");
        return;
    }
}