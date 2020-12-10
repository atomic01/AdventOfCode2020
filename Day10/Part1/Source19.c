#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 94

int testAdapters(int *);
int findNextAdapter(int *, int );

int main()
{
	int i = 0, done = 0, result = 0, number = 0;
	char buffer =  '\0' ;
	int adapterList[sizeOfsample] = {0};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 3468) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%d%c", &number, &buffer);
		if(feof(fp))
			done = 1;
		adapterList[i] = number;
		i++;

	}

	result = testAdapters(&adapterList[0]);
	printf("%d\n", result);

	return 0;
}

int testAdapters(int *adapterList)
{
	int adapter = 0, prevAdapter = 0, result = 0;
	int memory[3] = {0,0,1};

	for(int i = 0; i < sizeOfsample; i++)
	{
		prevAdapter = adapter;
		adapter = findNextAdapter(&adapterList[0], adapter);
		result = adapter - prevAdapter;
		memory[result - 1]++;
	}

	return memory[0] * memory[2];
}

int findNextAdapter(int *adapterList, int adapter)
{
	for(int i = 1; i < 4; i++)
		for(int j = 0; j < sizeOfsample; j++)
			if( adapterList[j] == (adapter + i))
				return adapter + i;
}
