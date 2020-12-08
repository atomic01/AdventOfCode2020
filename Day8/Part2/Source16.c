#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 626

int testProgram(char *);
int fixProgram(char *);

int main()
{
	int i = 0, j = 0, done = 0, result = 0;
	char buffer =  '\0' ;
	char program[sizeOfsample][10] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 1559) // to get past the text for the puzzle in the txt file where i stored the numbers
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

	result = fixProgram(&program[0][0]);
	printf("%d\n", result);

	return 0;
}

int fixProgram(char *program)
{
	int result = 0;

	for(int i = 0; i < sizeOfsample; i++)
	{
		if( strstr( (program + i*10), "nop") != NULL)
		{
			*((program +i*10) + 0) = 'j';
			*((program +i*10) + 1) = 'm';
			result = testProgram(program);
			if( result!=0)
				return result;
			else
			{
				*((program +i*10) + 0) = 'n';
				*((program +i*10) + 1) = 'o';
			}
		}
		else if( strstr( (program + i*10), "jmp") != NULL)
		{
			*((program +i*10) + 0) = 'n';
			*((program +i*10) + 1) = 'o';
			result = testProgram(program);
			if( result!=0)
				return result;
			else
			{
				*((program +i*10) + 0) = 'j';
				*((program +i*10) + 1) = 'm';
			}
		}
	}

	return result;
}

int testProgram(char *program)
{
	int accumulator = 0, i = 0, j = 0, endOfCommand = 0, commandValue = 0;
	short int commandExecutionCounter[sizeOfsample] = {0};
	char commandValueBuffer[5] = {'\0'};


	while( i < sizeOfsample && commandExecutionCounter[i]==0)
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

	if(i >= sizeOfsample)
		return accumulator;
	else
		return 0;
}


