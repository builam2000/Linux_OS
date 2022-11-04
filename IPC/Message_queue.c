#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>

#define NOTIFY_SIG SIGUSR1
static void pexit(const char *fCall);
static void handler(int sig)
{
    char *buf = "Data has been enter empty message queue!\n";
    write(STDOUT_FILENO,buf,strlen(buf));
}

int main(int argc, char *argv[])
{
    struct sigevent sev;
    mqd_t mqd;
    struct mq_attr attr;
    void *buffer;
    ssize_t numRead;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;

    /*Create and open a MSG queue*/
    /*Employing nonblocking mode means that the while loop will terminate
    (mq_receive() will fail with the error EAGAIN) when we have emptied the queue.*/
    mqd = mq_open(argv[1], O_RDWR | O_CREAT | O_NONBLOCK , 0660, NULL);
    if (mqd == (mqd_t)-1)pexit("Fail to create/open msg queue\n");

    if(mq_getattr(mqd,&attr) == -1)
    {
        pexit("Failed to get attribute\n");
    }

    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)pexit("Fail to malloc\n");

    /* Block NOTIFY signal into a mask if it is come*/
    sigemptyset(&blockMask);
    sigaddset(&blockMask,NOTIFY_SIG);
    if(sigprocmask(SIG_BLOCK,&blockMask,NULL) == -1)pexit("sigprocmask");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(NOTIFY_SIG,&sa,NULL) == -1)pexit("Sigaction failed\n");


    /*set signal notified for message queue*/
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;
    if (mq_notify(mqd,&sev) == -1)
    {
        pexit("mq_notify failed :))\n");
    }

    sigemptyset(&emptyMask);

    while ((numRead = mq_receive(mqd, buffer, attr.mq_msgsize, NULL)) >= 0)
            printf("Read %ld bytes\n", (long) numRead);
    for(;;)
    {
        printf("Waiting for data comming in queue\n");
        /*perform another task :)))))*/
        /*if the signal comming, return immediately, if not block to wait for signal*/
        sigsuspend(&emptyMask); //wait for signal from msg queue :()

    /*setup notify again :0 */
        if (mq_notify(mqd,&sev) == -1)
        {
            pexit("mq_notify failed :))\n");
        }

        while((numRead = mq_receive(mqd,buffer,attr.mq_msgsize,NULL)) >= 0)
        {
            printf("Read %ld bytes \n",numRead);
        }
    }

}

static void pexit(const char *fCall) {
	perror(fCall);
	exit(EXIT_FAILURE);
}