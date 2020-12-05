#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int calculateSeatID(char * );
int pow(int, int);


int main()
{
	int i = 0, maxResult = 0, result = 0, done = 0;
	char buffer[10] =  {"\0"} ;
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2648) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	while (!done)
	{
		fscanf(fp, "%s", &buffer);

		result = calculateSeatID(&buffer[0]);
		if(result > maxResult)
			maxResult = result;

		if(feof(fp))
			done = 1;
	}

	printf("%d\n", maxResult);

	return 0;
}



int calculateSeatID(char boardingPass[])
{
	int row = 0, column = 0, seatID = 0, j = 0;

	for(int i = 6; i >=0; i--)
	{
		if(boardingPass[j] == 'B')
			row += pow(2, i);
		j++;
	}

	for(int i = 2; i >=0; i--)
		{
			if(boardingPass[j] == 'R')
				column += pow(2, i);
			j++;
		}

	seatID = row * 8 + column;

	return seatID ;
}

int pow(int b, int p)
{
	int x = 1;

	for(int i=0; i < p; i++)
		x*=b;

	return x;
}















