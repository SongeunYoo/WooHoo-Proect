
//시작 선택화면 / 랭킹 파일 Handler

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include    <curses.h>
#include    <fcntl.h>
#define MAX 4*10

int lowest_score = 0;
int score = 10;
char username[MAX];
char rank_data[10][MAX];
int rank_score[10];

int main()
{
    
    if( score > lowest_score)//refresh ranklist
        rank();
    
}

int rank(int score)
{
    int fd;
    char username[MAX];
    char *arglist[3];
    arglist[0] = "sort";
    arglist[1] = "ranklist.txt";
    arglist[2] = 0;
    
    //printf("Enter Your Name : ");
    scanf("%s",&username);
    
    fd = open("ranklist.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    
    write(fd,score,300);
    write(fd,username,300);
    
    //printf("%s\n",username);
    execvp("sort", arglist);
    
    return 0;
}
