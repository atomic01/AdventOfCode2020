#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int pow(int, int);

int main()
{
	int i = 0, done = 0, row = 0, column = 0, seatID = 0, j = 0;
	char buffer =  '\0' ;
	char boardingPass[10] = {'\0'};
	int plane[128][8] = {0};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 498) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	while (!done)
	{
		fscanf(fp, "%s", &boardingPass);

		row = 0;
		column = 0;
		j=0;

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

		plane[row][column] = 1;

		if(feof(fp))
			done = 1;
	}

	for(int i = 0; i < 128; i++)
		for(int j = 0; j < 8; j++)
			if(plane[i][j] == 0 && plane[i][j+1] == 1 && plane[i][j-1] == 1)
				seatID = i*8 + j;

	printf("%d", seatID);

	return 0;
}

int pow(int b, int p)
{
	int x = 1;

	for(int i=0; i < p; i++)
		x*=b;

	return x;
}















