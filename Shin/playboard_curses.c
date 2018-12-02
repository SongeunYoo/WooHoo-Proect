/*
 playboard.c
 playboard main file
 curses output ver.
 without color
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <curses.h>

#define SIZE 4
int score=0;
int board[SIZE][SIZE];

void LoadColor(int value, char *color);


int main(void)
{
    LoadPlayBoard();
    
    return 0;
}

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
    
    initscr();
    clear();
    //open curses
    
    addstr("Welcome to 2048                ");
    addstr(score);
    addstr("\n\n");
    refresh();
    
    for (j=0;j<SIZE;j++) {
        for (i=0;i<SIZE;i++) {
            //LoadColor(board[i][j],color);
            //addstr(color);
            addstr("       ");
            //addstr(reset);
            refresh();
        }
        addstr("\n");//first line
        refresh();
        
        for (i=0;i<SIZE;i++) {
            //LoadColor(board[i][j],color);
            //addstr(color);
            refresh();
            if (board[i][j]!=0) {
                addstr("   ");
                addstr(board[i][j]);
                addstr("   ");
                refresh();
                //add color when data inserted
            }
            else {
                addstr("   o   ");
                refresh();
            }
            //addstr(reset);
            refresh();
        }
        addstr("\n");//second line : data inserted
        refresh();
        
        for (i=0;i<SIZE;i++) {//
            //LoadColor(board[i][j],color);
            //addstr(color);
            addstr("       ");
            //addstr(reset);
            refresh();
        }
        addstr("\n");//third line
        refresh();
    }
    addstr("\n");
    refresh();
    
    addstr("Preaa any key to exit\n");
    refresh();
    getch();
    endwin();
}
