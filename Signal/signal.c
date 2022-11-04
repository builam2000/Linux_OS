#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sigHandler(int sig)
{
    printf("Hello world \n");
}

int  main(void)
{
	int k = 0;
	sigset_t newmask, oldmask, pendmask;
    signal(SIGINT, sigHandler);
	sigemptyset(&newmask);
	sigaddset(&newmask, 2);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	perror("SIG_BLOCK error");
	while(1)
	{
		if (sigpending(&pendmask) < 0)
			perror("sigpending error");
		if (sigismember(&pendmask, 2))
		{
			printf("\n2 pending\n");
            sigprocmask(SIG_UNBLOCK,&newmask,&oldmask);
			//break;
		}
	}
}