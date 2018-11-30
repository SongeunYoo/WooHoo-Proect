//실행파일 혼자 확인해보기 위한 메인함수입니다
#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>

void main()
{
       rank();
}

int rank(){
    int fd;
    
    printf("\033[?25l\033[2J");
    //fd = open("testfile", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    //write(fd,"3",300);
    printf("\033[m");
    //printf("\033[H\n");
    
    /*
    int board[SIZE][SIZE];
    
    initBoard(board);//initiallize to 0
    LoadPlayBoard(board);
     */
}
