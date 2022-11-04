#include <stdio.h>
#include <stdlib.h>
extern char **environ;
void main()
{
    char **ep;
    for(ep = environ; *ep != NULL; ep++)
    {
        puts(*ep);
    }
    //printf("PATH: %s\n",getenv("PATH"));
}