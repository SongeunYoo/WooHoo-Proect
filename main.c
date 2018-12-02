#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<pthread.h>
#include	<curses.h>
#include	<fcntl.h>
#include	<ctype.h>

#define DECKLENGTH 4
#define STORELENGTH 10
#define MAX 40

typedef struct deck {
    int plate[DECKLENGTH][DECKLENGTH];
    int stored_deck[STORELENGTH][DECKLENGTH][DECKLENGTH], stored_score[STORELENGTH];
    int score;
    int standardScore[2];
    int storeEnd, storeStart;
    int item1, item2;
    int overcount;
    char userName[100];
} deck;

deck deck1, deck2;
int endFLAG = 0;

void store_deck(deck *deck);
void go_back(deck *deck);

int overCount(deck *deck);
int delete_01(deck *deck);

void go_up(deck *deck);
void go_down(deck *deck);
void go_left(deck *deck);
void go_right(deck *deck);

void for_one_player();
void for_two_players();
void for_player1();
void for_player2();

int rank(deck *deck);
void new_random(deck *deck);
void give_item(deck *deck);

void block_sum_up(deck *deck);
void block_sum_down(deck *deck);
void block_sum_right(deck *deck);
void block_sum_left(deck *deck);

void LoadPlayBoard(deck *deck);

int main(void)
{
    //메인 화면 curse로 불러내기
    
    char check;
    
    while (1)
    {
        check = getchar();
        
        switch (check)
        {
            case '1': for_one_player(); break;
            case '2': for_two_players(); break;
            default: continue;
        }
    }
    return 0;
}
void for_two_players()
{
    //2인용 창 띄우기
    pthread_t player1, player2;
    
    pthread_create(&player1, NULL, for_player1, NULL);
    pthread_create(&player2, NULL, for_player2, NULL);
    pthread_join(player1, NULL);
    pthread_join(player2, NULL);
}

void for_one_player()
{
    char check;
    int score = 0, EndGame = 1;
    
    //1인용 창 띄우기
    new_random(&deck1);

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
                store_deck(&deck1);
                break; //item1
            }
            case '2':
            {
                go_back(&deck1);
                store_deck(&deck1);
                break; //item2, go back
            }
            case 97: //a
            case 68: //<
            {
                go_left(&deck1); //이동
                block_sum_left(&deck1);//병합 + 점수 계산
                go_left(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 100: //d
            case 67: //>
            {
                go_right(&deck1); //이동
                block_sum_right(&deck1);//병합 + 점수 계산
                go_right(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 115: //s
            case 66: //down
            {
                go_down(&deck1); //이동
                block_sum_down(&deck1); //병합 + 점수 계산
                go_down(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 119: //w
            case 65: //up
            {
                go_up(&deck1); //이동
                block_sum_up(&deck1); //병합 + 점수 계산
                go_up(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            default: 	check = 0; break;
        }
        
        give_item(&deck1);
        
        if (check == 0)
            continue;
        
        deck1.overcount = overCount(&deck1);
        
        if (deck1.overcount == 1)
        {
            rank(&deck1);
            EndGame = 0;
            endFLAG = 1;
        }
    }
}

void for_player1()
{
    char check;
    int score = 0, EndGame = 1;
    
    new_random(&deck1);
    
    while (EndGame)
    {
        new_random(&deck1);
        check = getch();
        switch (check)
        {
            case '1':
            {
                delete_01(&deck1);
                store_deck(&deck1);
                break; //item1
            }
            case '2':
            {
                go_back(&deck1);
                store_deck(&deck1);
                break; //item2, go back
            }
            case 97: //a
            {
                go_left(&deck1); //이동
                block_sum_left(&deck1);//병합 + 점수 계산
                go_left(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 100: //d
            {
                go_right(&deck1); //이동
                block_sum_right(&deck1);//병합 + 점수 계산
                go_right(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 115: //s
            {
                go_down(&deck1); //이동
                block_sum_down(&deck1); //병합 + 점수 계산
                go_down(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            case 119: //w
            {
                go_up(&deck1); //이동
                block_sum_up(&deck1); //병합 + 점수 계산
                go_up(&deck1); //이동
                store_deck(&deck1);
                break;
            }
            default: 	check = 0;
        }
        
        give_item(&deck1);
        
        if (check == 0)
            continue;
        
        deck1.overcount = overCount(&deck1);
        
        if (deck1.overcount == -1)
        {
            rank(&deck1);
            EndGame = 0;
        }
    }
}

void for_player2()
{
    char check;
    int score = 0, EndGame = 1;
    
    new_random(&deck2);
    new_random(&deck2);
    
    while (EndGame)
    {
        new_random(&deck2);
        check = getch();
        switch (check)
        {
            case '1':
            {
                delete_01(&deck2);
                store_deck(&deck2);
                break; //item1
            }
            case '2':
            {
                go_back(&deck2);
                store_deck(&deck2);
                break; //item2, go back
            }
            case 97: //a
            case 68: //<
            {
                go_left(&deck2); //이동
                block_sum_left(&deck2);//병합 + 점수 계산
                go_left(&deck2); //이동
                store_deck(&deck2);
                break;
            }
            case 67: //>
            {
                go_right(&deck2); //이동
                block_sum_right(&deck2);//병합 + 점수 계산
                go_right(&deck2); //이동
                store_deck(&deck2);
                break;
            }
            case 66: //down
            {
                go_down(&deck2); //이동
                block_sum_down(&deck2); //병합 + 점수 계산
                go_down(&deck2); //이동
                store_deck(&deck2);
                break;
            }
            case 65: //up
            {
                go_up(&deck2); //이동
                block_sum_up(&deck2); //병합 + 점수 계산
                go_up(&deck2); //이동
                store_deck(&deck2);
                break;
            }
            default: 	check = 0;
        }
        
        give_item(&deck2);
        
        if (check == 0)
            continue;
        
        deck2.overcount = overCount(&deck2);
        
        if (deck2.overcount == -1)
        {
            rank(&deck2);
        }
    }
}

void store_deck(deck *deck)//저장해주는 함수입니다.
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 0; j < DECKLENGTH; j++)
            deck->stored_deck[deck->storeStart][i][j] = deck->plate[i][j];
    deck->stored_score[deck->storeStart] = deck->score;
    
    if ((++deck->storeStart) % STORELENGTH == deck->storeEnd)
        deck->storeEnd++;
}

void go_back(deck *deck)//혹은 return 값을 int로 해서 -1이 return될 경우 go_back을 실행하는 쪽에서 오류문 출력하도록 하는 것도 가능합니다.(약간의 수정 필요)
{
    int temp = 0;
    
    if (deck->storeStart == deck->storeEnd)
    {
        printf("Cannot go back to the previous state.\n");
        return;
    }
    
    if (--deck->storeStart < 0)
        deck->storeStart = STORELENGTH - 1;
    
    for (int i = 0; i < DECKLENGTH; i++)
    {
        for (int j = 0; j < DECKLENGTH; j++)
        {
            deck->plate[i][j] = deck->stored_deck[deck->storeStart][i][j];
        }
    }
    deck->score = deck->stored_score[deck->storeStart];
    deck->item2--;
}

void go_up(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 1; j < DECKLENGTH; j++)
            for (int k = j; k > 0; k--)
                if (deck->plate[k - 1][i] == 0)
                {
                    deck->plate[k - 1][i] = deck->plate[k][i];
                    deck->plate[k][i] = 0;
                }
}

void go_down(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            for (int k = j; k < DECKLENGTH - 1; k++)
                if (deck->plate[k + 1][i] == 0)
                {
                    deck->plate[k + 1][i] = deck->plate[k][i];
                    deck->plate[k][i] = 0;
                }
}

void go_left(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = 1; j < DECKLENGTH; j++)
            for (int k = j; k > 0; k--)
                if (deck->plate[i][k - 1] == 0)
                {
                    deck->plate[i][k - 1] = deck->plate[i][k];
                    deck->plate[i][k] = 0;
                }
}

void go_right(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            for (int k = j; k < DECKLENGTH - 1; k++)
                if (deck->plate[i][k + 1] == 0)
                {
                    deck->plate[i][k + 1] = deck->plate[i][k];
                    deck->plate[i][k] = 0;
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
    
    if (deck->item1 != 0 || deck->item2 == 0)
        return 0;
    else
    {
        endFLAG = 1;//GAME OVER: set flag
        return 1;
    }
}

int delete_01(deck *deck)
{
    for (int i = 0; i < DECKLENGTH; i++) {
        for (int j = 0; j < DECKLENGTH; j++) { 				//전체적으로 훑어서
            if (deck->plate[i][j] == 1 || deck->plate[i][j] == 2) {	//1과 2 찾아내기
                deck->plate[i][j] = 0; 		//0으로 바꿈
            }
        }
    }
    deck->item1--;
}

int rank(deck *deck)
{
    int fd;
    
    printf("Enter Your Name : ");
    scanf("%s", &deck->userName);
    
    fd = open("ranklist.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    
    write(fd, deck->score, 300);
    write(fd, deck->userName, 300);
}

void new_random(deck *deck)
{
	int b = 0, index;
	int p[16][2] = { 0 };
	
	for (int i = 0; i < DECKLENGTH; i++)
		for (int j = 0; j < DECKLENGTH; j++)
			if (deck->plate[i][j] == 0) {
				p[b][0] = i;
				p[b][1] = j;
				b++;
			}
	index = rand() % (b);
	deck->plate[p[index][0]][p[index][1]] = (rand() % 100 < 80) ? 1 : 2;

	return;
}

void block_sum_up(deck *deck)
{
    for (int i = 0; i < DECKLENGTH - 1; i++)
        for (int j = 0; j < DECKLENGTH; j++)
            if (deck->plate[i][j] == deck->plate[i + 1][j]) // 이동할때 블럭값이 같으면 
            {
                deck->plate[i][j] *= 2;
                deck->plate[i + 1][j] = 0;
                deck->score += deck->plate[i][j];
            }
}
void block_sum_down(deck *deck)
{
    for (int i = DECKLENGTH - 1; i>0; i--)
        for (int j = DECKLENGTH - 1; j >= 0; j--)
            if (deck->plate[i][j] == deck->plate[i - 1][j])
            {
                deck->plate[i][j] *= 2;
                deck->plate[i - 1][j] = 0;
                deck->score += deck->plate[i][j];
            }
}
void block_sum_right(deck *deck)
{
    for (int j = DECKLENGTH - 1; j>0; j--)
        for (int i = DECKLENGTH - 1; i >= 0; i--)
            if (deck->plate[i][j] == deck->plate[i][j - 1])
            {
                deck->plate[i][j] *= 2;
                deck->plate[i][j - 1] = 0;
                deck->score += deck->plate[i][j];
            }
}
void block_sum_left(deck *deck)
{
    for (int j = 0; j<DECKLENGTH - 1; j++)
        for (int i = 0; i<DECKLENGTH; i++)
            if (deck->plate[i][j] == deck->plate[i][j + 1])
            {
                deck->plate[i][j] *= 2;
                deck->plate[i][j + 1] = 0;
                deck->score += deck->plate[i][j];
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
    int i,j;
    char c;
    char color[40]; //draw background color
    char reset[] = "\033[m"; //delete incorrect color
    
    initscr();
    clear();
    //open curses
    
    addstr("1: delete 1, 2 blocks\n");
	addstr("2: go back to the previous state. It can be 10 times.\n\n");
	addstr("2048 GAME\n");
    addstr("\n\n");

	printw("Your Score: %d\n", deck->score);
    refresh();

	for (int i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
		{
			addstr("	");
                	printw("%d", deck->plate[i][j]);
                	addstr("	");
		}
		addstr("\n\n");
	}
    
    if(endFLAG == 1)
    {
        addstr("Preaa any key to exit\n");
        refresh();
        getch();
        endwin();
    }
}
