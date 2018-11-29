#include	<stdio.h>
#include	<unistd.h>	/* for execlp */
#include	<stdlib.h>	/* for exit   */
#include	<fcntl.h>
#include	<sys/wait.h>

int lowest_score = 0;

int main()
{
    rank(2048);
}

int rank(int score){
    int fd;
    
    fd = open("ranklist", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    write(fd, score, 12);

}
