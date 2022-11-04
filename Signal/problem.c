/*
 program : block Ctrl + C from user 
check pendding using sigpendding to detect user press Ctrl + C
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
    sigset_t newmask, oldmask, pendingmask;
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
    {
        perror("SIG_BLOCK error");
    }
    while(1)
    {
        if(sigpending(&pendingmask)<0) //checking whether or not signal is pending in queue :))
        {
            perror("Error pending mask");
        }
        if(sigismember(&pendingmask,SIGINT))
        {
            printf("CAUGHT INT signal!!\n");
            break;
        }
    }

}