#include	<stdio.h>
#include	<stdlib.h>

#define DECKLENGTH 4
#define STORELENGTH 10
#define MAX 40

int plate[DECKLENGTH][DECKLENGTH];
int plate2[DECKLENGTH][DECKLENGTH];
int item1 = 0, item2 = 0, item2_1, item2_2;
int overcount;
int stored_deck[STORELENGTH][DECKLENGTH][DECKLENGTH];
int storeEnd = 0, storeStart = 0, storeEnd2 = 0, storeStart2 = 0;

void store_deck(int stored_deck[DECKLENGTH][DECKLENGTH], int plate[DECKLENGTH][DECKLENGTH], int storeEnd, int storeStart);
void go_back(int stored_deck[DECKLENGTH][DECKLENGTH], int plate[DECKLENGTH][DECKLENGTH], int storeEnd, int storeStart, int item2);

int overCount(int plate[DECKLENGTH][DECKLENGTH]);
int item1(int plate[DECKLENGTH][DECKLENGTH], int item1);

void go_up(int plate[DECKLENGTH][DECKLENGTH]);
void go_down(int plate[DECKLENGTH][DECKLENGTH]);
void go_left(int plate[DECKLENGTH][DECKLENGTH]);
void go_right(int plate[DECKLENGTH][DECKLENGTH]);

void for_one_player();
void for_2players();
void for_player1();
void for_player2();

int rank(int score);
void new_random(int table[DECKLENGTH][DECKLENGTH]);

void block_sum_up(int plate[DECKLENGTH][DECKLENGTH]);
void block_sum_down(int plate[DECKLENGTH][DECKLENGTH]);
void block_sum_right(int plate[DECKLENGTH][DECKLENGTH]);
void block_sum_left(int plate[DECKLENGTH][DECKLENGTH]);

void for_2players()
{
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
	
	new_random(plate[DECKLENGTH][DECKLENGTH]);
	new_random(plate[DECKLENGTH][DECKLENGTH]);

	while(EndGame)
	{
		new_random(plate[DECKLENGTH][DECKLENGTH]);
		check = getchar();
		switch(check)
		{
			case 1:
			{
				item1(plate2[DECKLENGTH][DECKLENGTH], item1);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart, item2);
				break; //item1
			}
			case 2:
			{
				go_back(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break; //item2, go back
			}
			case 97: //a
			case 68: //<
			{
				go_left(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_left(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break;
			}	
			case 100: //d
			case 67: //>
			{
				go_right(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_right(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break;
			}
			case 115: //s
			case 66: //down
			{
				go_down(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_down(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break;
			}
			case 119: //w
			case 65: //up
			{
				go_up(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_up(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break;
			}
			default: 	check = 0;
		}
		if (check == 0)
			continue;

		overcount = overCount(plate[DECKLENGTH][DECKLENGTH]);

		if (overcount == -1)
		{
			rank(score);
			EndGame = 0;
		}
	}
}

void for_player1()
{
	char check;
	int score = 0, EndGame = 1;
	
	new_random(plate[DECKLENGTH][DECKLENGTH]);
	new_random(plate[DECKLENGTH][DECKLENGTH]);
	
	while(EndGame)
	{
		new_random(plate[DECKLENGTH][DECKLENGTH]);
		check = getchar();
		switch(check)
		{
			case 1:
			{
				item1(plate2[DECKLENGTH][DECKLENGTH], item1);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart, item2);
				break; //item1
			}
			case 2:
			{
				go_back(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd, storeStart);
				break; //item2, go back
			}
			case 97: // a
			{
				go_left(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_left(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}	
			case 100: // d
			{
				go_right(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_right(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			case 115: //s
			{
				go_down(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_down(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			case 119: //w
			{
				go_up(plate[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_up(plate[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			default: 	check = 0;
		}
		if (check == 0)
			continue;

		overcount = overCount(plate[DECKLENGTH][DECKLENGTH]);

		if (overcount == -1)
		{
			rank(score);
			//랭킹 출력
			EndGame = 0;
		}
	}
}

void for_player2()
{
	char check;
	int score = 0, EndGame = 1;
	
	new_random(plate2[DECKLENGTH][DECKLENGTH]);
	new_random(plate2[DECKLENGTH][DECKLENGTH]);
	
	while(EndGame)
	{
		new_random(plate2[DECKLENGTH][DECKLENGTH]);
		check = getchar();
		switch(check)
		{
			case 1:
			{
				item1(plate2[DECKLENGTH][DECKLENGTH], item2_1);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2, item2_2);
				break; //item1
			}
			case 2:
			{
				go_back(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break; //item2, go back
			}
			case 68: // <
			{
				go_left(plate2[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_left(plate2[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}	
			case 67: // >
			{
				go_right(plate2[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_right(plate2[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			case 66: //down
			{
				go_down(plate2[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_down(plate2[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			case 65: //up
			{
				go_up(plate2[DECKLENGTH][DECKLENGTH]); //이동
				//병합 + 점수 계산
				go_up(plate2[DECKLENGTH][DECKLENGTH]); //이동
				store_deck(plate2[DECKLENGTH][DECKLENGTH], storeEnd2, storeStart2);
				break;
			}
			default: 	check = 0;
		}
		if (check == 0)
			continue;

		overcount = overCount(plate2[DECKLENGTH][DECKLENGTH]);

		if (overcount == -1)
		{
			rank(score2);
			EndGame = 0;
		}
	}
}

void store_deck(int stored_deck[DECKLENGTH][DECKLENGTH], int plate[DECKLENGTH][DECKLENGTH], int storeEnd, int storeStart)//저장해주는 함수입니다.
{
	for (int i = 0; i < DECKLENGTH; i++)
		for (int j = 0; j < DECKLENGTH; j++)
			stored_deck[storeStart][i][j] = plate[i][j];

	if ((++storeStart)%STORELENGTH == storeEnd)
		storeEnd++;
}

void go_back(int stored_deck[DECKLENGTH][DECKLENGTH], int plate[DECKLENGTH][DECKLENGTH], int storeEnd, int storeStart, int item2)//혹은 return 값을 int로 해서 -1이 return될 경우 go_back을 실행하는 쪽에서 오류문 출력하도록 하는 것도 가능합니다.(약간의 수정 필요)
{
	int temp = 0;

	if (storeStart == storeEnd)
	{
		printf("Cannot go back to the previous state.\n");
		return;
	}

	if (--storeStart < 0)
		storeStart = STORELENGTH - 1;

	for (int i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
		{
			plate[i][j] = stored_deck[storeStart][i][j];
		}
	}
	item2--;
}

void go_down(int plate[DECKLENGTH][DECKLENGTH])
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = DECKLENGTH - 1 ; j >= 0; j--)
			for (int k = j; k < DECKLENGTH - 1; k++)
				if (plate[k + 1][i] == 0)
				{
					plate[k + 1][i] = plate[k][i];
					plate[k][i] = 0;
				}
}

void go_left(int plate[DECKLENGTH][DECKLENGTH])
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = 1 ; j < DECKLENGTH; j++)
			for (int k = j; k > 0; k--)
				if (plate[i][k - 1] == 0)
				{
					plate[i][k - 1] = plate[i][k];
					plate[i][k] = 0;
				}
}

void go_right(int plate[DECKLENGTH][DECKLENGTH])
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = DECKLENGTH - 1 ; j >= 0; j--)
			for (int k = j; k < DECKLENGTH - 1; k++)
				if (plate[i][k + 1] == 0)
				{
					plate[i][k + 1] = deck[i][k];
					plate[i][k] = 0;
				}
}

int overCount (int plate[DECKLENGTH][DECKLENGTH]) {
	for (int i=0, i<DECKLENGTH, i++) { 					//빈칸이 있는지 확인
		for (int j=0, j<DECKLENGTH, j++) {
			if (plate[i][j] == 0)
				return 0;
		}
	}

	for (int i=0, i<DECKLENGTH-1, i++) { 					//세로로 동일한 값이 있는지 확인
		for (int j=0, j<DECKLENGTH, j++) {
			if (plate[i][j] == plate[i+1][j])
				return 0;
		}
	}

	for (int j=0, j<DECKLENGTH-1, j++) { 					//가로로 동일한 값이 있는지 확인
		for (int i=0, i<DECKLENGTH, i++) {
			if (plate[i][j] == plate[i][j+1])
				return 0;
		}
	}

//빈칸도 없고 연속된 블럭도 없을 경우 아이템을 쓰게 해줄지 말지 결정하기

	if (item1 != 0 || item2 == 0)
		return 0;
	else
		return 1;
}

int item1(int plate[DECKLENGTH][DECKLENGTH], int item1)
{
	for (int i=0, i<DECKLENGTH, i++) {
		for (int j=0, j<DECKLENGTH, j++) { 				//전체적으로 훑어서
			if (plate[i][j] == 1 || plate[i][j] == 2) {	//1과 2 찾아내기
				plate[i][j] = 0; 		//0으로 바꿈
			}
		}
	}
	item1--;
}

int rank(int score)
{
	int fd;
	char username[MAX];
	
	printf("Enter Your Name : ");
	scanf("%s",&username);	
    
	fd = open("ranklist.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);	/* then open */
    
 	write(fd,score,300);
	write(fd,username,300);
}

void new_random(int table[DECKLENGTH][DECKLENGTH])
{
	int b;
	int* p0[DECKLENGTH * DECKLENGTH]={0};

	for(int i=0, b=0;i<DECKLENGTH;i++){
	    for(int j=0;j<DECKLENGTH;j++)
 	       if(table[i][j] == 0){
        	    p0[b]=&table[i][j];
		       b++;
	       }
	}
	*p0[rand()%(b)]=(rand()%100<80)?1:2;
}

void block_sum_up(int plate[DECKLENGTH][DECKLENGTH])
{
}
void block_sum_down(int plate[DECKLENGTH][DECKLENGTH])
{
}
void block_sum_right(int plate[DECKLENGTH][DECKLENGTH])
{
	
}
void block_sum_left(int plate[DECKLENGTH][DECKLENGTH])
{
	
}





