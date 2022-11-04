/*
1. Write a program in 'C' on Linux environment, to perform the below.
a. Display the output string on screen without using 'printf' or any other library function call.
Hint: use system calls.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
/*
1. Lets assume a file named author.txt contains below text "This course is all about 
Linux system programming. The instructor of this course is Rohan" 
2. Now write a program in 'C' to change only the Name present in file from 'Rohan' 
to 'Mohan' hint make use of lseek()
*/

void main()
{
    int fd;
    int pos;
    fd = open("author.txt",O_RDWR);
    if(fd < 0)
    {
        perror("Error occured during open!\n");
        exit(1);
    }
    pos = lseek(fd,-5,SEEK_END);
    
    if(write(fd,"Mohan",5)<0)
    {
        perror("Fail to write into file :))) \n");
    }
    close(fd);

}