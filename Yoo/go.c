#include	<stdio.h>

#define DECKLENGTH 4

int deck[4][4] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

void go_up();
void go_down();
void go_left();
void go_right();

int main(void)
{
	for (int  i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
			printf("%d", deck[i][j]);
		printf("\n");
	}
	printf("\n");

	go_up();
	for (int  i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
			printf("%d", deck[i][j]);
		printf("\n");
	}
	printf("\n");

	go_down();
	for (int  i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
			printf("%d", deck[i][j]);
		printf("\n");
	}
	printf("\n");

	go_left();
	for (int  i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
			printf("%d", deck[i][j]);
		printf("\n");
	}
	printf("\n");

	go_right();
	for (int  i = 0; i < DECKLENGTH; i++)
	{
		for (int j = 0; j < DECKLENGTH; j++)
			printf("%d", deck[i][j]);
		printf("\n");
	}

	return 0;
}

void go_up()
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = 1 ; j < DECKLENGTH; j++)
			for (int k = j; k > 0; k--)
				if (deck[k - 1][i] == 0)
				{
					deck[k - 1][i] = deck[k][i];
					deck[k][i] = 0;
				}
}

void go_down()
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = DECKLENGTH - 1 ; j >= 0; j--)
			for (int k = j; k < DECKLENGTH - 1; k++)
				if (deck[k + 1][i] == 0)
				{
					deck[k + 1][i] = deck[k][i];
					deck[k][i] = 0;
				}
}

void go_left()
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = 1 ; j < DECKLENGTH; j++)
			for (int k = j; k > 0; k--)
				if (deck[i][k - 1] == 0)
				{
					deck[i][k - 1] = deck[i][k];
					deck[i][k] = 0;
				}
}

void go_right()
{
	for (int i = 0 ; i < DECKLENGTH; i++)
		for (int j = DECKLENGTH - 1 ; j >= 0; j--)
			for (int k = j; k < DECKLENGTH - 1; k++)
				if (deck[i][k + 1] == 0)
				{
					deck[i][k + 1] = deck[i][k];
					deck[i][k] = 0;
				}
}
