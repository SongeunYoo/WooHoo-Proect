#include	<stdio.h>

#define DECKLENGTH 4
#define STORELENGTH 10

int plate[DECKLENGTH][DECKLENGTH];
int item1 = 0, item2 = 0;
int overcount;
int stored_deck[STORELENGTH][DECKLENGTH][DECKLENGTH];
int storeEnd = 0, storeStart = 0;

void store_deck();
void go_back();

int overCount();
int item1();

void go_up();
void go_down();
void go_left();
void go_right();

int main(void)
{


  return 0;
}

void store_deck()//저장해주는 함수입니다.
{
	for (int i = 0; i < DECKLENGTH; i++)
		for (int j = 0; j < DECKLENGTH; j++)
			stored_deck[storeStart][i][j] = plate[i][j];

	if ((++storeStart)%STORELENGTH == storeEnd)
		storeEnd++;
}

void go_back()//혹은 return 값을 int로 해서 -1이 return될 경우 go_back을 실행하는 쪽에서 오류문 출력하도록 하는 것도 가능합니다.(약간의 수정 필요)
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
}

void go_down()
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

void go_left()
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

void go_right()
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

int overCount () {
	for (int i=0, i<4, i++) { 					//빈칸이 있는지 확인
		for (int j=0, j<4, j++) {
			if (plate[i][j] == 0)
				return 0;
		}
	}

	for (int i=0, i<3, i++) { 					//세로로 동일한 값이 있는지 확인
		for (int j=0, j<4, j++) {
			if (plate[i][j] == plate[i+1][j])
				return 0;
		}
	}

	for (int j=0, j<3, j++) { 					//가로로 동일한 값이 있는지 확인
		for (int i=0, i<4, i++) {
			if (plate[i][j] == plate[i][j+1])
				return 0;
		}
	}

*빈칸도 없고 연속된 블럭도 없을 경우 아이템을 쓰게 해줄지 말지 결정하기

	if (item1 != 0 || item2 == 0)
		return 0;
	else
		return 1;
}

int item1()
{
	for (int i=0, i<4, i++) {
		for (int j=0, j<4, j++) { 				//전체적으로 훑어서
			if (plate[i][j] == 1 || plate[i][j] == 2) {	//1과 2 찾아내기
				plate[i][j] = 0; 		//0으로 바꿈
			}
		}
	}
	item1--;
}
