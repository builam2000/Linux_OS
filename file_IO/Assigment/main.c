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

void main()
{
    char buff[1024];
    int number_char;
    number_char = read(STDIN_FILENO,buff,sizeof(buff));
    if(number_char<0)
    {
        perror("Error when reading!\n");
    }

    number_char = write(STDOUT_FILENO,buff,number_char);
    if(number_char<0)
    {
        perror("Error when writing!\n");
    }
}