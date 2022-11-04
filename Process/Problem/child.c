#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char buff[] = "Hello Lam";
    if(argc != 2)
    {
        puts("incorrect pass argument");
		return -1;
    }
    fd = open(argv[1],O_RDWR|O_APPEND);
    if(fd < 0)
    {
        perror("Error while open a file");
        return -1;
    }
    ssize_t number_of_byte = write(fd,buff,sizeof(buff));
    printf("Number of bytes has been written: %d\n",number_of_byte);
    close(fd);
    return 0;
}