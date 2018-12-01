
//시작 선택화면 / 랭킹 파일 Handler

#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#defien MAX 4*10

int lowest_score = 0;
int score = 0;
char username[MAX];

int main()
{
    
    if( score > lowest_score)//refresh ranklist
        rank();
    
    //GAME OVER
    //SORT
    //PRINT
    
}

int rank(int score)
{
    int fd;
    char username[MAX];
    char *arglist[3];
    arglist[0] = "sort";
    arglist[1] = "ranklist";
    arglist[2] = 0;
    
    printf("Enter Your Name : ");
    scanf("%s",&username);
    
    fd = open("ranklist", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    
    write(fd,score,300);
    write(fd,username,300);
    
    execvp("sort", arglist);
}
