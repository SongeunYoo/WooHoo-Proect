#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<pthread.h>
#include	<curses.h>
#include	<fcntl.h>
#include	<ctype.h>
#include	<time.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/wait.h>
#include    <termios.h>


#define oops(m,x)	{ perror(m); exit(x); }
#define DECKLENGTH 4
#define STORELENGTH 10
#define MAX 40
#define RANKCOUNT 50

typedef struct deck {
    int plate[DECKLENGTH][DECKLENGTH];
    int stored_deck[STORELENGTH][DECKLENGTH][DECKLENGTH], stored_score[STORELENGTH];
    int score;
    int standardScore[2];
    int storeEnd, storeStart;
    int item1, item2;
    int overcount;
    int newNum;
    int over;
} deck;

deck deck1, deck2;
char getMessage[RANKCOUNT][MAX];

void store_deck(deck *deck);
void go_back(deck *deck);

int overCount(deck *deck);
void delete_01(deck *deck);

void go_up(deck *deck);
void go_down(deck *deck);
void go_left(deck *deck);
void go_right(deck *deck);

void for_one_player();
void for_two_players();

void new_random(deck *deck);
void give_item(deck *deck);

void block_sum_up(deck *deck);
void block_sum_down(deck *deck);
void block_sum_right(deck *deck);
void block_sum_left(deck *deck);

void LoadPlayBoard(deck *deck);
void LoadPlayBoard2();

void store_rank(deck *deck);
void store_rank_for_2p();
void rank();
void print_rank();
void sort_rank(int pipe[2]);
void store_sorted_rank(int pipe[2]);

void echo_on();

int main(void)
{
    //메인 화면 curse로 불러내기
    
    char check;
    clear();
    
    initscr();
    addstr("\n\n");
    
    addstr("		1 : One Player 2048\n\n");
    addstr("		2 : Two Player 2048\n\n");
    addstr("		3 : View Ranking of Previous Players\n\n");
    refresh();
    
    while (1)
    {
        check = getchar();
        
        switch (check)
        {
            case '1': for_one_player(); break;
            case '2': for_two_players(); break;
            case '3': rank(); break;
            default: continue;
        }
    }
    return 0;
}

void for_one_player()
{
    char check;
    int EndGame = 1;
    
    //1인용 창 띄우기
    deck1.newNum = 1;
    new_random(&deck1);
    deck1.newNum = 1;
    
    deck1.standardScore[0] = 100;
    deck1.standardScore[1] = 500;
    deck1.item2 = 1;
    
    while (EndGame)
    {
        new_random(&deck1);
        LoadPlayBoard(&deck1);
        check = getch();
        
        switch (check)
        {
            case '1':
            {
                delete_01(&deck1);
                break; //item1
            }
            case '2':
            {
                go_back(&deck1);
                break; //item2, go back
            }
            case 97: //a
            {
                go_left(&deck1); //이동
                block_sum_left(&deck1);//병합 + 점수 계산
                if (deck1.newNum) go_left(&deck1); //이동
                break;
            }
            case 100: //d
            {
                go_right(&deck1); //이동
                block_sum_right(&deck1);//병합 + 점수 계산
                if (deck1.newNum) go_right(&deck1); //이동
                break;
            }
            case 115: //s
            {
                go_down(&deck1); //이동
                block_sum_down(&deck1); //병합 + 점수 계산
                if (deck1.newNum) go_down(&deck1); //이동
                break;
            }
            case 119: //w
            {
                go_up(&deck1); //이동
                block_sum_up(&deck1); //병합 + 점수 계산
                if (deck1.newNum) go_up(&deck1); //이동
                break;
            }
            default: 	check = 0; break;
        }
        
        if (check == 0)
            continue;
        
        store_deck(&deck1);
        give_item(&deck1);;
        
        deck1.overcount = overCount(&deck1);
        if (deck1.overcount == 1)
        {
            store_rank(&deck1);
            EndGame = 0;
            break;
        }
    }
}

void for_two_players()
{
    char check;
    int EndGame = 1;
    
    deck1.newNum = 1;
    new_random(&deck1);
    deck1.newNum = 1;
    deck1.standardScore[0] = 100;
    deck1.standardScore[1] = 500;
    deck1.item2 = 1;

    deck2.newNum = 1;
    new_random(&deck2);
    deck2.newNum = 1;
    deck2.standardScore[0] = 100;
    deck2.standardScore[1] = 500;
    deck2.item2 = 1;
    
    while (EndGame)
    {
        new_random(&deck1);
        new_random(&deck2);
        LoadPlayBoard2();
        check = getch();
        
        switch (check)
        {
            case '1':
            {
                delete_01(&deck1);
                break; //item1
            }
            case '2':
            {
                go_back(&deck1);
                break; //item2, go back
            }
            case 97: //a
            case 65: //A
            {
                go_left(&deck1); //이동
                block_sum_left(&deck1);//병합 + 점수 계산
                if (deck1.newNum) go_left(&deck1); //이동
                break;
            }
            case 100: //d
            case 68: //D
            {
                go_right(&deck1); //이동
                block_sum_right(&deck1);//병합 + 점수 계산
                if (deck1.newNum) go_right(&deck1); //이동
                break;
            }
            case 115: //s
            case 83: //S
            {
                go_down(&deck1); //이동
                block_sum_down(&deck1); //병합 + 점수 계산
                if (deck1.newNum) go_down(&deck1); //이동
                break;
            }
            case 119: //w
            case 87: //W
            {
                go_up(&deck1); //이동
                block_sum_up(&deck1); //병합 + 점수 계산
                if (deck1.newNum) go_up(&deck1); //이동
                break;
            }

           case '0':
            {
                delete_01(&deck2);
                break; //item1
            }
            case '9':
            {
                go_back(&deck2);
                break; //item2, go back
            }
            case 106: //j
            case 74: //J
            {
                go_left(&deck2); //이동
                block_sum_left(&deck2);//병합 + 점수 계산
                if (deck2.newNum) go_left(&deck2); //이동
                break;
            }
            case 108: //l
            case 76: //L
            {
                go_right(&deck2); //이동
                block_sum_right(&deck2);//병합 + 점수 계산
                if (deck2.newNum) go_right(&deck2); //이동
                break;
            }
            case 107: //k
            case 75: //K
            {
                go_down(&deck2); //이동
                block_sum_down(&deck2); //병합 + 점수 계산
                if (deck2.newNum) go_down(&deck2); //이동
                break;
            }
            case 105: //i
            case 73: //I
            {
                go_up(&deck2); //이동
                block_sum_up(&deck2); //병합 + 점수 계산
                if (deck2.newNum) go_up(&deck2); //이동
                break;
            }
            default: 	check = 0; break;
        }
        
        if (check == 0)
            continue;
        
        store_deck(&deck1);
        give_item(&deck1);

        store_deck(&deck2);
        give_item(&deck2);
        
        deck1.overcount = overCount(&deck1);
        deck2.overcount = overCount(&deck2);

        if (deck1.overcount == 1)
        {
            deck1.over = 1;
            if (deck2.over == 1)
	    {
		EndGame = 0;
                store_rank_for_2p();
	    }
        }

        if (deck2.overcount == 1)
        {
            deck2.over = 1;
            if (deck1.over == 1)
	    {
		EndGame = 0;
                store_rank_for_2p();
	    }
        }
    }
}

void store_deck(deck *deck)//저장해주는 함수입니다.
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 0; j < DECKLENGTH; j++)
            deck->stored_deck[deck->storeStart][i][j] = deck->plate[i][j];
    deck->stored_score[deck->storeStart] = deck->score;
    
    deck->storeStart = (++deck->storeStart) % STORELENGTH;
    
    if (deck->storeStart == deck->storeEnd)
        deck->storeEnd++;
}

void go_back(deck *deck)//혹은 return 값을 int로 해서 -1이 return될 경우 go_back을 실행하는 쪽에서 오류문 출력하도록 하는 것도 가능합니다.(약간의 수정 필요)
{
    int temp = 0;
    if (deck->item2 < 1)
    	return;
    if (deck->storeStart == deck->storeEnd)
    {
        printf("Cannot go back to the previous state.\n");
        return;
    }
    
    if (--deck->storeStart < 0)
        deck->storeStart = STORELENGTH - 1;
    
    temp = deck->storeStart - 1;
    if (temp < 0)
        temp = STORELENGTH - 1;
    
    for (int i = 0; i < DECKLENGTH; i++)
    {
        for (int j = 0; j < DECKLENGTH; j++)
        {
            deck->plate[i][j] = deck->stored_deck[temp][i][j];
        }
    }
    deck->score = deck->stored_score[temp];
    deck->item2--;
}

void go_up(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 1; j < DECKLENGTH; j++)
            for (int k = j; k > 0; k--)
                if (deck->plate[k - 1][i] == 0 && deck->plate[k][i] != 0)
                {
                    deck->plate[k - 1][i] = deck->plate[k][i];
                    deck->plate[k][i] = 0;
                    deck->newNum = 1;
                }
}

void go_down(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            for (int k = j; k < DECKLENGTH - 1; k++)
                if (deck->plate[k + 1][i] == 0 && deck->plate[k][i] != 0)
                {
                    deck->plate[k + 1][i] = deck->plate[k][i];
                    deck->plate[k][i] = 0;
                    deck->newNum = 1;
                }
}

void go_left(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 1; j < DECKLENGTH; j++)
            for (int k = j; k > 0; k--)
                if (deck->plate[i][k - 1] == 0 && deck->plate[i][k] != 0)
                {
                    deck->plate[i][k - 1] = deck->plate[i][k];
                    deck->plate[i][k] = 0;
                    deck->newNum = 1;
                }
}

void go_right(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            for (int k = j; k < DECKLENGTH - 1; k++)
                if (deck->plate[i][k + 1] == 0 && deck->plate[i][k] != 0)
                {
                    deck->plate[i][k + 1] = deck->plate[i][k];
                    deck->plate[i][k] = 0;
                    deck->newNum = 1;
                }
}

int overCount(deck *deck) {
    for (int i = 0; i < DECKLENGTH; i++) { 					//빈칸이 있는지 확인
        for (int j = 0; j < DECKLENGTH; j++) {
            if (deck->plate[i][j] == 0)
                return 0;
        }
    }
    
    for (int i = 0; i < DECKLENGTH - 1; i++) { 					//세로로 동일한 값이 있는지 확인
        for (int j = 0; j < DECKLENGTH; j++) {
            if (deck->plate[i][j] == deck->plate[i + 1][j])
                return 0;
        }
    }
    
    for (int j = 0; j < DECKLENGTH - 1; j++) { 					//가로로 동일한 값이 있는지 확인
        for (int i = 0; i < DECKLENGTH; i++) {
            if (deck->plate[i][j] == deck->plate[i][j + 1])
                return 0;
        }
    }
    
    //빈칸도 없고 연속된 블럭도 없을 경우 아이템을 쓰게 해줄지 말지 결정하기
    /*
     if (deck->item1 != 0 || deck->item2 == 0)
     return 0;
     else
     {
     */
    return 1;
    //}
}

void delete_01(deck *deck)
{
    if ( deck->item1 < 1)
	return;
    for (int i = 0; i < DECKLENGTH; i++) {
        for (int j = 0; j < DECKLENGTH; j++) { 				//전체적으로 훑어서
            if (deck->plate[i][j] == 1 || deck->plate[i][j] == 2) {	//1과 2 찾아내기
                deck->plate[i][j] = 0; 		//0으로 바꿈
            }
        }
    }
    deck->item1--;
}

void new_random(deck *deck)
{
    int b = 0, index;
    int p[16][2] = { 0 };
    
    if (deck->newNum == 0)
        return;
    
    srand(time(NULL));
    
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 0; j < DECKLENGTH; j++)
            if (deck->plate[i][j] == 0) {
                p[b][0] = i;
                p[b][1] = j;
                b++;
            }
    if (b != 0)
    {
        index = rand() % (b);
        deck->plate[p[index][0]][p[index][1]] = (rand() % 100 < 80) ? 1 : 2;
    }
    deck->newNum = 0;
    
    return;
}

void block_sum_up(deck *deck)
{
    for (int i = 0; i < DECKLENGTH - 1; i++)
        for (int j = 0; j < DECKLENGTH; j++)
            if (deck->plate[i][j] == deck->plate[i + 1][j] && deck->plate[i][j] != 0) // 이동할때 블럭값이 같으면
            {
                deck->plate[i][j] *= 2;
                deck->plate[i + 1][j] = 0;
                deck->score += deck->plate[i][j];
                deck->newNum = 1;
            }
}
void block_sum_down(deck *deck)
{
    for (int i = DECKLENGTH - 1; i>0; i--)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            if (deck->plate[i][j] == deck->plate[i - 1][j] && deck->plate[i][j] != 0)
            {
                deck->plate[i][j] *= 2;
                deck->plate[i - 1][j] = 0;
                deck->score += deck->plate[i][j];
                deck->newNum = 1;
            }
}
void block_sum_right(deck *deck)
{
    for (int j = DECKLENGTH - 1; j>0; j--)
        for (int i = DECKLENGTH - 1; i >= 0; i--)
            if (deck->plate[i][j] == deck->plate[i][j - 1] && deck->plate[i][j] != 0)
            {
                deck->plate[i][j] *= 2;
                deck->plate[i][j - 1] = 0;
                deck->score += deck->plate[i][j];
                deck->newNum = 1;
            }
}
void block_sum_left(deck *deck)
{
    for (int j = 0; j<DECKLENGTH - 1; j++)
        for (int i = 0; i<DECKLENGTH; i++)
            if (deck->plate[i][j] == deck->plate[i][j + 1] && deck->plate[i][j] != 0)
            {
                deck->plate[i][j] *= 2;
                deck->plate[i][j + 1] = 0;
                deck->score += deck->plate[i][j];
                deck->newNum = 1;
            }
}

void give_item(deck *deck) {
    
    if (deck->standardScore[0] <= deck->score) 		//점수가 아이템1 기준 점수보다 높으면
    {
        deck->item1++;			//아이템1 갯수 증가
        deck->standardScore[0] *= 2;		//아이템1 기준 점수는 100 증가
    }
    
    else if (deck->standardScore[1] <= deck->score)
    {
        deck->item2++;
        deck->standardScore[1] += 500;
    }
}

void LoadPlayBoard(deck *deck) {
    char c;
    
    clear();
    initscr();
    //open curses
    
    addstr("1: delete 1, 2 blocks\n");
    addstr("2: go back to the previous state. It can be 10 times.\n\n");
    addstr("2048 GAME\n");
    addstr("\n\n");
    
    printw("Your Score: %d\n", deck->score);
    printw("Item1:		%d	Item2:		%d\n", deck->item1, deck->item2);
    printw("Next Item1: 	%d	Next Item2:	%d\n\n\n", deck->standardScore[0], deck->standardScore[1]);
    
    refresh();
    
    for (int i = 0; i < DECKLENGTH; i++)
    {
        for (int j = 0; j < DECKLENGTH; j++)
        {
            addstr("	");
            printw("%d", deck->plate[i][j]);
        }
        addstr("\n\n");
    }
    refresh();
}

void LoadPlayBoard2() {
    char c;
    
    clear();
    initscr();
    //open curses
    
    addstr("Player1 - 1, Player2 - 0: delete 1, 2 blocks\n");
    addstr("Player1 - 8, Player2 - 9: go back to the previous state. It can be 10 times.\n\n");
    addstr("2048 GAME\n");
    addstr("\n\n");
    
    printw("Player1 Score:	%d		 | 	Player2 Score:	%d\n", deck1.score, deck2.score);
    printw("Item1:	%d	Item2:	%d	 | 	Item1:	%d	Item2:	%d\n", deck1.item1, deck1.item2, deck2.item1, deck2.item2);
    printw("Next:	%d	Next:	%d	 | 	Next:	%d	Next:	%d\n\n\n", deck1.standardScore[0], deck1.standardScore[1], deck2.standardScore[0], deck2.standardScore[1]);
    
    refresh();
    
    for (int i = 0; i < DECKLENGTH; i++)
    {

        if (deck1.over == 0)
        {
		for (int j = 0; j < DECKLENGTH; j++)
            		printw("%d	", deck1.plate[i][j]);

	}
	else
		for (int j = 0; j < DECKLENGTH; j++)
			addstr("	");

        addstr(" | ");

        if (deck2.over == 0)
        {
     	   for (int j = 0; j < DECKLENGTH; j++)
		printw("	%d", deck2.plate[i][j]);
	}

        addstr("\n\n");
    }
    refresh();
}


void store_rank(deck *deck)
{
    int fd;
    char score[MAX];
    char username[MAX];
    
    echo_on();
    sprintf(score, "%d", deck->score);
    printf("Enter Your Name : ");
    scanf("%s",username);
    
    fd = open("ranklist.txt", O_CREAT | O_RDWR | O_APPEND, 0644);	/* then open */
    
    write(fd,score,strlen(score));
    write(fd," ",1);
    write(fd,username,strlen(username));
    write(fd,"\n",1);
    
    rank();
}

void rank()
{
    int	pout[2], pid;
    FILE	*fout, *fdopen();
    
    if( pipe(pout) == -1 )
        oops("pipe failed", 1);
    
    if(( pid = fork()) == -1 )
        oops("cannot fork", 2);
    if( pid == 0 )				/* child is dc	*/
        sort_rank(pout);
    else {
        store_sorted_rank(pout);		/* parent is ui	*/
        wait(NULL);			/* wait for child */
    }
    
}

void store_sorted_rank(int pipe[2])
{
    FILE	*fpin, *fdopen();
    
    fpin  = fdopen( pipe[0], "r" );
    
    close(pipe[1]);
    
    for (int i = 0; i < RANKCOUNT; i++)
    {
        if (fgets( getMessage[i], BUFSIZ, fpin ) == NULL)
            break;
    }
    fclose(fpin);
    print_rank();
}

void sort_rank(int pipe[2])
{
    char	*arglist[4];
    
    if( dup2(pipe[1], 1) == -1 )
        oops("sort: cannot redirect stdin", 3);
    close(pipe[0]);
    close(pipe[1]);
    
    arglist[0] = "sort";
    arglist[1] = "-n";
    arglist[2] = "ranklist.txt";
    arglist[3] = 0;
    
    execvp("sort", arglist);
    perror("execvp");
}

void print_rank() {
    char c;
    
    clear();
    
    initscr();
    //open curses
    
    addstr("\n\n");
    
    refresh();
    
    addstr("		Ranking		\n\n");
    
    for (int i = 0; i < RANKCOUNT; i++)
    {
        addstr("	");
        printw("%s\n", getMessage[i]);
    }
    refresh();
    
    if (c = getch())
    {
        endwin();
        exit(1);
    }
}

void store_rank_for_2p()
{
    int fd;
    char score[2][MAX];
    char username[2][MAX];
    
    echo_on();
    
    sprintf(score[0], "%d", deck1.score);
    sprintf(score[1], "%d", deck2.score);
    printf("Enter Your Name for Player1 : ");
    scanf("%s",username[0]);
    printf("\nEnter Your Name for Player2 : ");
    scanf("%s",username[1]);
    
    fd = open("ranklist.txt", O_CREAT | O_RDWR | O_APPEND, 0644);	/* then open */
    
    write(fd,score[0],strlen(score[0]));
    write(fd," ",1);
    write(fd,username[0],strlen(username[0]));
    write(fd,"\n",1);
    write(fd,score[1],strlen(score[1]));
    write(fd," ",1);
    write(fd,username[1],strlen(username[1]));
    write(fd,"\n",1);
    
    rank();
}

void echo_on()
{
    struct termios ttystate;
    int c;
    
    
    c = tcgetattr(0,&ttystate);
    
    
    if(c == -1 ){
        perror("tcgetattr");
        exit(1);
    }
    ttystate.c_lflag |= ECHO;
    tcsetattr( 0, TCSANOW, &ttystate);
}
