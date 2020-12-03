#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int i = 0, j= 0, result = 0;
	char buffer =  '\0' ;
	FILE* fp = fopen("Puzzle.txt", "r+");
	char toboggan[31][323] = {"\0"};
	int endOfALine = 0;
	while (i < 3203) // to get past the text for the puzzle in the txt file where i stored the numbers
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

	i=0;
	j=0;
	while( i < 323)
	{
		if(toboggan[j][i] == '#')
			result++;

		i++;
		if(j + 3 > 30)
			j -=28;
		else
			j+=3;
	}

	printf("%d", result);


	return 0;
}
