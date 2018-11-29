#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/wait.h>

int lowest_score = 0;
int score = 0;

int main()
{
    if( score > lowest_score)//refresh ranklist
        rank();
}

int rank(){
    int fd;
    
    fd = open("ranklist", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    printf("%d\n",score);
    write(fd,score,300);
}
