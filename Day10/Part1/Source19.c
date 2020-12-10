#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 95

int testAdapters(int *);
void sortArray(int * );

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

	i = 1;
	while (!done)
	{
		fscanf(fp, "%d%c", &number, &buffer);
		if(feof(fp))
			done = 1;
		adapterList[i] = number;
		i++;

	}

	sortArray(&adapterList[0]);
	result = testAdapters(&adapterList[0]);
	printf("%d\n", result);

	return 0;
}

void sortArray(int *array )
{
	int temp = 0;

	for(int i = 0; i < sizeOfsample; i++)
	{
		for(int j = i+1; j < sizeOfsample; j++)
		{
			if(array[j] < array[i])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}


int testAdapters(int *adapterList)
{
	int result = 0;
	int memory[3] = {0,0,1};

	for(int i = 0; i < sizeOfsample - 1; i++)
		memory[adapterList[i+1] - adapterList[i] - 1]++;

	return memory[0] * memory[2];
}

