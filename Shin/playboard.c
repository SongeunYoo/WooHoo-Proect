#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
int score=0;
int board[SIZE][SIZE]

void LoadColor(int value, char *color) {
    int code[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
    int *background = code;
    int *foreground = code+1;
    
    if (value > 0)
        while (value--) {
            if (background+2 < code + sizeof(code)) {
                background += 2;
                foreground += 2;
        }
    }
    snprintf(color,40,"\033[38;5;%d;48;5;%dm",*foreground,*background);//anprintf: String Buffer로 출력
}

void initBoard(){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++)
            board[i][j] = 0;
    }
}

void LoadPlayBoard() {
    int i,j;
    char c;
    char color[40]; //draw background color
    char reset[] = "\033[m"; //delete incorrect color
    
    printf("\033[?25l\033[2J");//clear the screen
    printf("Welcome to 2048 %17d pts\n\n",score);
    
    for (j=0;j<SIZE;j++) {
        for (i=0;i<SIZE;i++) {
            LoadColor(board[i][j],color);
            printf("%s",color);
            printf("       ");
            printf("%s",reset);
        }
        printf("\n");//first line
        
        for (i=0;i<SIZE;i++) {
            LoadColor(board[i][j],color);
            printf("%s",color);
            if (board[i][j]!=0) {
                printf("   %d   ",board[i][j]);
                //add color when data inserted
            }
            else {
                printf("   o   ");
            }
            printf("%s",reset);
        }
        printf("\n");//second line : data inserted
        
        for (i=0;i<SIZE;i++) {
            LoadColor(board[i][j],color);
            printf("%s",color);
            printf("       ");
            printf("%s",reset);
        }
        printf("\n");//third line
    }
    printf("\n");
}

