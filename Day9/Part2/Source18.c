#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 1000
#define preambleSize 25

int findAnomalyInXmas(long long  int *);
long long int findContiguousSet(long long int *, int);


int main()
{
	int i = 0, done = 0, result = 0;
	char buffer =  '\0' ;
	long long int number = 0;
	long long int xmas[sizeOfsample] = {0};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 752) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%lld%c", &number, &buffer);
		if(feof(fp))
			done = 1;
		xmas[i] = number;
		i++;

	}


	result = findAnomalyInXmas(&xmas[0]);
	result = findContiguousSet(&xmas[0], result);
	printf("%lld\n", result);

	return 0;
}

int findAnomalyInXmas(long long int *xmas)
{
	int result = 0;

	for(int i = preambleSize; i < sizeOfsample; i++)
	{
		for(int j = i - preambleSize; j < i; j++)
		{
			for(int z = j+1; z < i; z++)
				if( xmas[i] == xmas[j] + xmas[z])
					result = 1;
		}

		if(result != 0)
			result = 0;
		else
			return i;
	}
}

long long int findContiguousSet(long long int *xmas, int X)
{
	long long accumulator = 0;
	int j = 0, tempI = 0, tempJ=0, min = 0, max = 0;

	for(int i = 0; i < sizeOfsample; i++)
	{
		j = i;
		accumulator = 0;
		while(accumulator < xmas[X])
		{
			accumulator+=xmas[j];
			if(accumulator == xmas[X])
			{
				tempI = i;
				tempJ = j;
				i = sizeOfsample;
			}
			j++;
		}
	}

	min = xmas[tempI];
	max = xmas[tempI];
	for(int i = tempI; i <= tempJ; i++)
	{
		if(xmas[i] > max)
			max = xmas[i];
		if(xmas[i] < min)
			min = xmas[i];
	}

	return min + max;
}




