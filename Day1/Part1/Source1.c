#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int i = 0, result = 0;
	char buffer =  '\0' ;
	FILE* fp = fopen("Puzzle1.txt", "r+");
	int array[200] = {0};

	while (i < 1459) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}


	i=0;
	while (!feof(fp))
	{
		fscanf(fp, "%d", &array[i]);
		i++;
	}

	for(int i = 0; i < 200; i++)
	{
		for(int j = i+1; j < 200; j++)
		{
			if(array[i] + array[j] == 2020)
			{
				result = array[i] * array[j];
				printf("%d = %d * %d", result, array[i], array[j]);

			}
		}
	}


	return 0;
}
