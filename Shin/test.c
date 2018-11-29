#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/wait.h>

void main()
{
       rank();
}

int rank(){
    int fd;
    
    fd = open("testfile", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    write(fd,"3",300);
}
