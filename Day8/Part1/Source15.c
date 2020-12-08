#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 626

int findInfiniteLoop(char *);

int main()
{
	int i = 0, j = 0, done = 0, result = 0;
	char buffer =  '\0' ;
	char program[sizeOfsample][10] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2525) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%c", &buffer);
		if(feof(fp))
			done = 1;
		else
		{
			if(buffer!='\n')
			{
				program[j][i] = buffer;
				i++;
			}
			else
			{
				i = 0;
				j++;
			}
		}
	}

	result = findInfiniteLoop(&program[0][0]);
	printf("%d\n", result);

	return 0;
}

int findInfiniteLoop(char *program)
{
	int accumulator = 0, i = 0, j = 0, endOfCommand = 0, commandValue = 0;
	short int commandExecutionCounter[sizeOfsample] = {0};
	char commandValueBuffer[5] = {'\0'};



	while(i < sizeOfsample && commandExecutionCounter[i]==0)
	{
	    commandExecutionCounter[i]++;
	    
		if( strstr( (program + i*10), "nop") != NULL)
			i++;
		else
		{
			j=0;
			while(*((program +i*10) + 5 + j) != '\0')
			{
				commandValueBuffer[j] = *((program +i*10) + 5 + j);
				j++;
			}
			commandValue = atoi(commandValueBuffer);
			if( *((program +i*10) + 4) == '-' )
				commandValue -= 2*commandValue;

			if(strstr((program + i*10), "jmp") != NULL)
				i += commandValue - 1;
			else if(strstr((program + i*10), "acc") != NULL)
				accumulator += commandValue;

			memset(commandValueBuffer, '\0', 5*sizeof(char));
			i++;
		}
	}

	return accumulator;
}

