#include	<stdio.h>

#define DECKLENGTH 4
#define STORELENGTH 10 현재까지 저장되기 때문에, 실 저장 및 되돌리기 가능 횟수는 STORELENGTH-1이라고 봐야 합니다. 본 프로그램에 들어갈 때 저장하는 위치를 조정하면서 바꿀 수 있을 것 같습니다.

int deck[4][4];
int stored_deck[STORELENGTH][4][4];
int storeEnd = 0, storeStart = 0;

void store_deck();
void go_back();

int main(void) // 작동 확인을 위한 메인 함수입니다.
{

	for (int  count = 0; count < STORELENGTH + 5; count++)
	{
		printf("%d %d\n", storeEnd, storeStart);
		for (int  i = 0; i < DECKLENGTH; i++)
		{
			for (int j = 0; j < DECKLENGTH; j++)
				{deck[i][j] = count;
				printf("%d", deck[i][j]);}
		}
		store_deck();
		printf("\n");
	}

	printf("%d %d\n", storeEnd, storeStart);

	for (int  count = 0; count < STORELENGTH + 7; count++)
	{
		go_back();
		printf("%d %d\n", storeEnd, storeStart);
		for (int  i = 0; i < DECKLENGTH; i++)
		{
			for (int j = 0; j < DECKLENGTH; j++)
				printf("%d", deck[i][j]);
		}
		printf("\n");
	}
		
	return 0;
}

void store_deck()//저장해주는 함수입니다.
{
	for (int i = 0; i < DECKLENGTH; i++)
		for (int j = 0; j < DECKLENGTH; j++)
			stored_deck[storeStart][i][j] = deck[i][j];

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

	temp = storeStart - 1;

	if (temp < 0)
		temp = STORELENGTH - 1;

	for (int i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
		{
			deck[i][j] = stored_deck[temp][i][j];
		}
	}
}
