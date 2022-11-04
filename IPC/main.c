/*
Write a program that uses two pipes to enable bidirectional communication
between a parent and child process. The parent process should loop reading a
block of text from standard input and use one of the pipes to send the text to the
child, which converts it to uppercase and sends it back to the parent via the other
pipe. The parent reads the data coming back from the child and echoes it on
standard output before continuing around the loop once more.
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#define BUF_SIZE 100
static void pexit(const char *fCall);
int main(int argc, char *argv[])
{
    int i,count = 0;
    int pfd_first[2];
    int pfd_second[2];
    ssize_t numread;
    
    char buf[BUF_SIZE];
    char return_buf[BUF_SIZE];

    if(pipe(pfd_first) == -1)pexit("Error to create pipe1");

    printf("Sucessful to create pipe first\n");

    if(pipe(pfd_second) == -1)pexit("Error to create pipe2");
    printf("Sucessful to create pipe second\n");
    
    /*Parent: write to child; child will convert into uppercase*/
    switch (fork())
    {
    case -1:
        pexit("Error while fork");
    case 0:
        /*Read end pipe for child*/
        if(close(pfd_first[1])==-1)pexit("Error to close write rear for child");
        if(close(pfd_second[0])==-1)pexit("Error to close read end of child"); 
        
        for(;;)
        {
            memset(buf,0,100);

            numread = read(pfd_first[0],buf,BUF_SIZE);
            //printf("Ok, numread: %d,%s\n",numread,buf);
            /*Check for error while read*/
            if (numread == -1)pexit("Error when read");
            if (numread == 0)
            {
                if(close(pfd_second[1])==-1)pexit("Error to close write end of child"); 
                break; /* End-of-file */
            }
            printf("Str: %s\n",buf);
            /*Convert to UPPERCASE*/
            for (i = 0; buf[i]!='\0'; i++) 
            {
                if(buf[i] >= 'a' && buf[i] <= 'z') 
                {
                    buf[i] = buf[i] -32;
                }
            }

            if(write(pfd_second[1],buf,numread) != numread)
                pexit("chile partial/failed write converted string");
        }
        exit(EXIT_SUCCESS);
     
    default:
        if(close(pfd_first[0]) == -1)pexit("Error to close read rear for parent");     
        if(close(pfd_second[1]) == -1)pexit("Error to close write rear for parent");

        for(;;)
        {
            char str[100]={0};
            printf("\nEnter string:");
            scanf("%s",str);
            printf("\n");
            if(write(pfd_first[1],str,strlen(str)) != strlen(str))
                pexit("parent partial/failed write input string to pipe");
            printf("Success to send data\n");
            
            ssize_t return_number = read(pfd_second[0],return_buf,100);
            write(STDOUT_FILENO,return_buf,return_number);
            memset(buf,0,100);
            count++;
            if(count == 5) break;         
        }
        if(close(pfd_first[1]) == -1)pexit("Error to close write rear for parent");  
        wait(NULL);   
        exit(EXIT_SUCCESS);
    }

}

static void
pexit(const char *fCall) {
	perror(fCall);
	exit(EXIT_FAILURE);
}