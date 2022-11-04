#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sz,seek_pos = 0;
    char buf[100];
    int fd = open("input.txt",O_RDWR);
    if(fd < 0)
    {
        perror("Error occured during open!\n");
        exit(1);
    }

    seek_pos = lseek(fd,0,SEEK_SET);
    printf("Initial offset position: %d\n",seek_pos);

    seek_pos = lseek(fd,2,SEEK_CUR);
    printf("After 1st: %d\n",seek_pos);

    seek_pos = lseek(fd,8,SEEK_CUR);
    printf("After 2nd: %d\n",seek_pos);

    sz = read(fd,buf,10);
    buf[sz] = '\0';
    printf("Read str: %s\n",buf);

    seek_pos = lseek(fd,0,SEEK_END);
    printf("Offset position after SEEK_END: %d\n",seek_pos);

    sz = write(fd,"HelloLam\n",9);
    close(fd);

    return 0;
}