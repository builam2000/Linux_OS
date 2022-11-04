#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
static void sigHandler(int sig)
{
    static int count = 0;
    /* UNSAFE: This handler uses non-async-signal-safe functions
    (printf(), exit(); see Section 21.1.2) */
    if (sig == SIGINT) {
    count++;
    printf("Caught SIGINT (%d)\n", count);
    return; /* Resume execution at point of interruption */
    }
    /* Must be SIGQUIT - print a message and terminate the process */
    printf("Caught SIGQUIT - that's all folks!\n");
    exit(0);
}
int
main(int argc, char *argv[])
{
    /* Establish same handler for SIGINT and SIGQUIT */
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        perror("signal");
    if (signal(SIGQUIT, sigHandler) == SIG_ERR)
        perror("signal");
    for (;;) /* Loop forever, waiting for signals */
        pause(); /* Block until a signal is caught */
}