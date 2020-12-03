#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int i = 0, j= 0;
	int result[5] = {0,0,0,0,0};
	long int endResult = 1;
	char buffer =  '\0' ;
	FILE* fp = fopen("Puzzle.txt", "r+");
	char toboggan[31][323] = {"\0"};
	int slopes[2][5] = {{1,1,1,1,2}, {1,3,5,7,1}};
	int endOfALine = 0;
	while (i < 670) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!feof(fp))
	{
		j = 0;
		endOfALine = 0;

		while(endOfALine==0)
		{
			fscanf(fp, "%c", &buffer);
			if(buffer != '\n' && !feof(fp))
				toboggan[j][i] = buffer;
			else
				endOfALine = 1;
			j++;
		}
		i++;
	}


	for( int slopeCounter = 0; slopeCounter < 5; slopeCounter++)
	{
		i=0;
		j=0;
		while( i < 323)
		{
			if(toboggan[j][i] == '#')
				result[slopeCounter]++;

			i+=slopes[0][slopeCounter];
			if(j + slopes[1][slopeCounter] > 30)
				j =j + slopes[1][slopeCounter] - 31;
			else
				j+=slopes[1][slopeCounter];
		}

	}

	for(int i = 0; i < 5; i++)
		endResult = endResult * result[i];

	printf("%ld\n",endResult);


	return 0;
}
