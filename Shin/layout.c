#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>

#define SIZE 4
uint32_t score=0;

void getColor(uint8_t value, char *color, size_t length) {
    uint8_t original[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
    uint8_t *background = original+0;
    uint8_t *foreground = original+1;
    if (value > 0) while (value--) {
        if (background+2<original+sizeof(original)) {
            background+=2;
            foreground+=2;
        }
    }
    snprintf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);
}

void drawBoard(uint8_t board[SIZE][SIZE]) {
    uint8_t x,y;
    char c;
    char color[40], reset[] = "\033[m";
    printf("\033[H");
    
    printf("Welcome to 2048 %17d pts\n\n",score);
    
    for (y=0;y<SIZE;y++) {
        for (x=0;x<SIZE;x++) {
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");
            printf("%s",reset);
        }
        printf("\n");
        for (x=0;x<SIZE;x++) {
            getColor(board[x][y],color,40);
            printf("%s",color);
            if (board[x][y]!=0) {
                char s[8];
                snprintf(s,8,"%u",(uint32_t)1<<board[x][y]);
                uint8_t t = 7-strlen(s);
                printf("%*s%s%*s",t-t/2,"",s,t/2,"");
            } else {
                printf("   ·   ");
            }
            printf("%s",reset);
        }
        printf("\n");
        for (x=0;x<SIZE;x++) {
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");
            printf("%s",reset);
        }
        printf("\n");
    }
    printf("\n");
}

void setBufferedInput(bool enable) {
    static bool enabled = true;
    static struct termios old;
    struct termios new;
    
    if (enable && !enabled) {
        // restore the former settings
        tcsetattr(STDIN_FILENO,TCSANOW,&old);
        // set the new state
        enabled = true;
    } else if (!enable && enabled) {
        // get the terminal settings for standard input
        tcgetattr(STDIN_FILENO,&new);
        // we want to keep the old setting to restore them at the end
        old = new;
        // disable canonical mode (buffered i/o) and local echo
        new.c_lflag &=(~ICANON & ~ECHO);
        // set the new settings immediately
        tcsetattr(STDIN_FILENO,TCSANOW,&new);
        // set the new state
        enabled = false;
    }
}

void addRandom(uint8_t board[SIZE][SIZE]) {
    static bool initialized = false;
    uint8_t x,y;
    uint8_t r,len=0;
    uint8_t n,list[SIZE*SIZE][2];
    
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }
    
    for (x=0;x<SIZE;x++) {
        for (y=0;y<SIZE;y++) {
            if (board[x][y]==0) {
                list[len][0]=x;
                list[len][1]=y;
                len++;
            }
        }
    }
    
    if (len>0) {
        r = rand()%len;
        x = list[r][0];
        y = list[r][1];
        n = (rand()%10)/9+1;
        board[x][y]=n;
    }
}

void initBoard(uint8_t board[SIZE][SIZE]) {
    uint8_t x,y;
    for (x=0;x<SIZE;x++) {
        for (y=0;y<SIZE;y++) {
            board[x][y]=0;
        }
    }
    addRandom(board);
    addRandom(board);
    drawBoard(board);
    score = 0;
}


int main(int argc, char *argv[]) {
    uint8_t board[SIZE][SIZE];
    
    //initBoard(board);
    signal(SIGINT, signal_callback_handler);
    setBufferedInput(false);
    drawBoard(board);
    
    return 1;
}
