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
#include <limits.h>

int main(int argc, char **argv)
{
    mqd_t queue;
    struct mq_attr attrs;
    size_t msg_len;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <queuename> <message>\n", argv[0]);
        return 1;
    }

    queue = mq_open(argv[1], O_WRONLY | O_CREAT, 0660, NULL); // Open message queue with default attributes
    if (queue == (mqd_t)-1)
    {
        perror("mq_open");
        return 1;
    }

    if (mq_getattr(queue, &attrs) == -1)
    {
        perror("mq_getattr");
        mq_close(queue);
        return 1;
    }
    // print the attribute values
    printf("\n message queue mq_maxmsg = (%d), mq_msgsize is (%d)\n",(int)attrs.mq_maxmsg, (int)attrs.mq_msgsize);

    msg_len = strlen(argv[2]);
    if ( (long)msg_len > attrs.mq_msgsize)
    {
        fprintf(stderr, "Your message is too long for the queue.\n");
        mq_close(queue);
        return 1;
    }

    if (mq_send(queue, argv[2], strlen(argv[2]), 0) == -1) // 0 is the priority that can be set based on message priority 0 is least priority
    {
        perror("mq_send");
        mq_close(queue);
        return 1;
    }
    
    return 0;
}
